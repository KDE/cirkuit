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

#include "backend_interface.h"  // plugins = backends
#include "document.h"

#include <QStringList>

#include <QUrl>
#include <QDebug>
#include <KServiceTypeTrader>
#include <KService>
#include <KConfigSkeleton>
#include <QDir>
#include <KPluginInfo>
#include <QPluginLoader>

class Cirkuit::BackendPrivate {
public:
    QString name;
    QString comment;
    QString icon;
    QUrl url;
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

QUrl Backend::url() const
{
    return d->url;
}

QString Backend::helpUrl() const
{
    return QString();
}

QString Backend::examplesUrl() const
{
    return QString();
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
    if (services.length() == 0)
    {
     qDebug() << "Plugins (Cirkuit/Backend services) not found";
    }

  
    KService::List::iterator iter;  // changed from const_iterator 2018
    QDir pluginsDir(BACKEND_INSTALL_DIR);
    for (iter = services.begin(); iter < services.end(); ++iter) {
        KService::Ptr service = *iter;
        QString libname(service->library());
        QPluginLoader loader(pluginsDir.absoluteFilePath(libname));
        QObject *obj = loader.instance();
        if (!obj) {
            qDebug() << "Error loading" << libname << loader.errorString();
            continue;    
        }

        Backend* backend = qobject_cast<Backend *>(obj);
        if (!backend) {
            qCritical() << "Error: Failed to create backend for" << libname;
            continue;
        }        

        KPluginInfo info(service);
        backend->d->name = info.name();
        backend->d->comment = info.comment();
        backend->d->icon = info.icon();
        backend->d->url = QUrl::fromLocalFile(info.website());
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


float Backend::identifyIndex(Cirkuit::Document* doc) const
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

Cirkuit::Backend* Cirkuit::Backend::autoChooseBackend(Document* doc)
{
    Backend* bb = getBackend("null");
    float best = 0.0;
    foreach (Backend* b, availableBackends()) {
        float index = b->identifyIndex(doc);
        qDebug() << "Identify index for backend " << b->name() << " = " << index;
        if (index > best) {
            bb = b;
            best = index;
        }
    }
    
    qDebug() << "And the winner is ... " << bb->name();
    return bb;
}
