/***************************************************************************
*   Copyright (C) 2011 by Matteo Agostinelli                              *
*   agostinelli@gmail.com                                                 *
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
*   This program is distributed in the hope that it will be useful,       *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
*   GNU General Public License for more details.                          *
*                                                                         *
*   You should have received a copy of the GNU General Public License     *
*   along with this program; if not, write to the                         *
*   Free Software Foundation, Inc.,                                       *
*   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.          *
***************************************************************************/

#include "documenttemplate.h"
#include <QTextStream>
#include <QFile>
#include <QRegExp>

#include <KDebug>
#include <KGlobal>
#include <KStandardDirs>
#include <QDir>

using namespace Cirkuit;

class Cirkuit::DocumentTemplatePrivate
{
public:
    KUrl path;
    QString backend;
};

DocumentTemplate::DocumentTemplate(const KUrl& path, QObject* parent): QObject(parent), d(new DocumentTemplatePrivate)
{
    d->path = path;
    readBackend();
}

KUrl DocumentTemplate::path() const
{
    return d->path;
}

void DocumentTemplate::readBackend() const
{
    d->backend.clear();
    
    QFile file(d->path.path());
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);
    
    QString line = stream.readLine().toLower();
    QRegExp regExp("%%backend=(\\w+)%%");
    while (line != QString()) {
        if (regExp.indexIn(line) > -1) {
            d->backend = regExp.cap(1);
        }
        line = stream.readLine().toLower();
    }
}

QString DocumentTemplate::backend() const
{
    return d->backend;
}

QString DocumentTemplate::name() const
{
    return d->path.fileName();
}

QString DocumentTemplate::insert(const QString& code, const QString& keyword)
{
    QFile file(d->path.path());
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);
    QString output = stream.readAll().replace(keyword, code, Qt::CaseInsensitive);
    file.close();
    return output;
}

bool DocumentTemplate::operator==(const Cirkuit::DocumentTemplate& rhs) const
{
    return this->path().fileName() == rhs.path().fileName();
}

static QList<DocumentTemplate*> templateCache;

TemplateManager::TemplateManager(QObject* parent): QObject(parent)
{

}

QList< DocumentTemplate* > TemplateManager::availableTemplates(const QString& backend, bool forceRescan)
{
    //if we already have all templates cached, just return the cache.
    //otherwise create the available templates
    if (!templateCache.isEmpty() && !forceRescan) {
        return backendFilter(templateCache, backend);
    }
    
    scanTemplates();    
    return backendFilter(templateCache, backend);
}

bool TemplateManager::checkDuplicate(DocumentTemplate* t)
{
    bool duplicate = false;
    foreach(DocumentTemplate* item, templateCache) {
        if (*item == *t) {
            duplicate = true;
        }
    }
    return duplicate;
}

QList< DocumentTemplate* > TemplateManager::backendFilter(const QList<DocumentTemplate*>& list, const QString& backend)
{
    if (backend.isEmpty()) {
        return list;
    }
    
    QList<DocumentTemplate*> filtered;
    foreach(DocumentTemplate* item, list) {
        if (QString::compare(item->backend(), backend, Qt::CaseInsensitive) == 0) {
           filtered << item; 
        }
    }
    
    return filtered;
}

void TemplateManager::scanTemplates()
{
    templateCache.clear();
    QDir templates;
    DocumentTemplate* t;
    QStringList dirs = KGlobal::dirs()->findDirs("appdata", "templates");
    
    for(QStringList::iterator i = dirs.begin(); i != dirs.end(); ++i) {
        templates = QDir(*i);
        
        for (uint j = 0; j < templates.count(); ++j) {
            KUrl fileUrl(templates.path() + '/' + templates[j]);
            t = new DocumentTemplate(fileUrl);
            
            if (t->backend().isEmpty() || checkDuplicate(t)) {
                delete t;
                continue;
            }
            
            templateCache.append(t);
        }
    }
}

