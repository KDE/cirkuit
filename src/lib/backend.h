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

#ifndef BACKEND_H
#define BACKEND_H

#include "cirkuit_export.h"

#include <QtCore/QObject>
#include <QVariant>

class KUrl;
class KConfigSkeleton;

namespace Cirkuit
{
class BackendPrivate;
    
class CIRKUIT_EXPORT Backend : public QObject
{
    Q_OBJECT
protected:
    explicit Backend(QObject* parent = 0, const QList<QVariant>& args = QList<QVariant>());
    virtual ~Backend();
    
public:
    virtual bool checkRequirements() const;
    
    /**
     * Returns a unique string to identify this backend.
     * @return string to identify backend
     */
    virtual QString id() const = 0;
    
    //Stuff extracted from the .desktop file
    /**
     * Returns the name of the backend
     * @return the backends name
     */
    QString name() const;
    /**
     * Returns a short comment about the backend.
     * @return comment about the backend
     */
    QString comment() const;
    /**
     * Returns the icon to use with this backend
     * @return name of the icon
     */
    QString icon() const;
    /**
     * Returns the Url of the Homepage for the Backend
     * @return the url
     */
    KUrl url() const;
    /**
     * Returns an Url pointing to the Help of the Backend
     * The method should be overwritten by all Backends(who have an online help)
     * @return Url of the help
     */
    virtual KUrl helpUrl() const;
    
    /**
     * Returns a longer description of the Backend, e.g. purpose, strengths etc.
     * It should help the user to decide between the different Backends
     * @return a description of the backend. It can contain html
     */
    virtual QString description() const;
    /**
     * Returns a Widget for configuring this backend
     * @return Widget for usage in the Settings dialog
     */
    virtual QWidget* settingsWidget(QWidget* parent) const;
    /**
     * Returns a KConfig object, containing all the settings,
     * the backend might need
     * @return a KConfigSkeleton object, for configuring this backend
     */
    virtual KConfigSkeleton* config() const;
    
    virtual QString initialText() const;    
    virtual int initialLineNumber() const;    
    
    /**
     * Returns a list of the names of all the installed and enabled backends
     * @return a list of the names of all the installed and enabled backends
     * @see isEnabled()
     */
    static QStringList listAvailableBackends();
    /**
     * Returns Pointers to all the installed backends
     * @return Pointers to all the installed backends
     */
    static QList<Backend*> availableBackends();
    /**
     * Returns the backend with the given name, or null if it isn't found
     * @return the backend with the given name, or null if it isn't found
     */
    static Backend* createBackend(const QString& name);
    
    static Backend* autoChooseBackend(const QString& text);
    
  private:
    BackendPrivate* d;
};

}

#endif // BACKEND_H
