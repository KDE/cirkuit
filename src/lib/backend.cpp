/*
    Copyright (C) 2009 Alexander Rieder <alexanderrieder@gmail.com>
    Copyright (C) 2011 Matteo Agostinelli <agostinelli@gmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include "backend.h"

#include "cirkuitlib_debug.h"
#include "document.h"

#include <QStringList>

#include <KUrl>
#include <KServiceTypeTrader>
#include <KService>
#include <KConfigSkeleton>
#include <KPluginMetaData>

class Cirkuit::BackendPrivate {
public:
    QString name;
    QString comment;
    QString icon;
    KUrl url;
};

using namespace Cirkuit;

static QList<Backend*> backendCache = QList<Backend*>();

Backend::Backend(QObject* parent, const QList<QVariant>& args): QObject(parent), d(new BackendPrivate)
{
    Q_UNUSED(args);
}

Backend::~Backend()
{
    delete d;
}

bool Backend::checkRequirements() const
{
    return false;
}

QString Backend::name() const
{
    return d->name;
}

QString Backend::comment() const
{
    return d->comment;
}

QString Backend::description() const
{
    return comment();
}

QString Backend::icon() const
{
    return d->icon;
}

KUrl Backend::url() const
{
    return d->url;
}

KUrl Backend::helpUrl() const
{
    return KUrl();
}

KUrl Backend::examplesUrl() const
{
    return KUrl();
}

bool Backend::operator==(const QString& rhs) const
{
    return QString::compare(id(), rhs, Qt::CaseInsensitive) == 0 || QString::compare(name(), rhs, Qt::CaseInsensitive) == 0;
}


QWidget* Backend::settingsWidget(QWidget* parent) const
{
    Q_UNUSED(parent)
    return 0;
}

KConfigSkeleton* Backend::config() const
{
    return 0;
}

KConfigSkeletonItem* Backend::configTemplateUrl() const
{
    if (!config()) return 0;
    
    return config()->findItem("templateurl");
}

QStringList Backend::listAvailableBackends()
{
    QList<Backend* > backends=availableBackends();
    QStringList l;
    foreach (Backend* b, backends) {
        if (b->checkRequirements()) {
            l << b->name();
        }
    }

    return l;
}

QList<Backend*> Backend::availableBackends()
{
    //if we already have all backends Cached, just return the cache.
    //otherwise create the available backends
    if (!backendCache.isEmpty()) {
        return backendCache;
    }

    KService::List services;
    KServiceTypeTrader* trader = KServiceTypeTrader::self();

    services = trader->query("Cirkuit/Backend");
    
    KService::List::const_iterator iter;
    for (iter = services.constBegin(); iter < services.constEnd(); ++iter) {
        QString error;
        KService::Ptr service = *iter;
        
        KPluginLoader loader(service->library());
        KPluginFactory *factory = loader.factory();
        if (!factory) {
            qCWarning(CIRKUIT_DEBUG) << "error: " << error;
            continue;    
        }
        
        Backend* backend = factory->create<Backend>(0);
        if (!backend) {
            qCWarning(CIRKUIT_DEBUG) << "error: " << error;
            continue;
        }        
   
        KPluginMetaData info(loader);
        backend->d->name = info.name();
        backend->d->comment = info.description();
        backend->d->icon = info.iconName();
        backend->d->url = info.website();
        backendCache << backend;
    }
    return backendCache;
}

Backend* Backend::getBackend(const QString& name)
{
    QList<Backend*> backends = availableBackends();
    foreach(Backend* b, backends) {
        if (*b == name) {
            return b;
        }
    }

    return 0;
}

Cirkuit::DocumentSettings* Cirkuit::Backend::documentSettings() const
{
    return 0;
}

Generator* Backend::generator() const
{
    return 0;
}

QStringList Backend::identifyingWords() const
{
    QStringList words;
    return words;
}


float Backend::identifyIndex(KTextEditor::Document* doc) const
{
    if (identifyingWords().count() < 1) {
        return 0.0;
    }
    
    int total = 0;
    int hits = 0;
    
    foreach (const QString& word, identifyingWords()) {
        if (doc->text().contains(word, Qt::CaseInsensitive)) ++hits;
        ++total;
    }
    
    return (1.00*hits)/total;
}

Cirkuit::Backend* Cirkuit::Backend::autoChooseBackend(KTextEditor::Document* doc)
{
    Backend* bb = getBackend("null");
    float best = 0.0;
    foreach (Backend* b, availableBackends()) {
        float index = b->identifyIndex(doc);
        qCDebug(CIRKUIT_DEBUG) << "Identify index for backend " << b->name() << " = " << index;
        if (index > best) {
            bb = b;
            best = index;
        }
    }
    
    qCDebug(CIRKUIT_DEBUG) << "And the winner is ... " << bb->name();
    return bb;
}
