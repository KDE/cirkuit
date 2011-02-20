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

class KConfigSkeletonItem;
class KUrl;
class KConfigSkeleton;

namespace Cirkuit
{
class DocumentSettings;
class Document;
class Generator;

class BackendPrivate;
    
/**
 * The Backend class provides access to information about the backend.
 * It provides access the features supported by the backend, and most 
 * notably a factory method to create a new Generator.
 * It needs to be subclassed by all Backends.
 *
 * @author Matteo Agostinelli
 * @author Alexander Rieder
 */
class CIRKUIT_EXPORT Backend : public QObject
{
    Q_OBJECT
protected:
    /**
     * Default constructor. Should not be invoked directly. Use the static member getBackend() instead
     */
    explicit Backend(QObject* parent = 0, const QList<QVariant>& args = QList<QVariant>());
    /**
     * Default destructor
     */
    virtual ~Backend();
    
    /**
     * Calculates the probabiliy that the document passed as argument can be processed by the backend
     * @param doc the document
     * @return a floating point number ranging from 0 to 1, where 0 stands for lowest probabiliy and 
     * 1 is the maximum
     */
    virtual float identifyIndex(Cirkuit::Document* doc) const;
    /**
     * A list of keywords that can be used to identify the backend (see code from existing backends).
     * This function should be re-implemented by each backend to define its own list.
     * @return the list of keywords
     */
    virtual QStringList identifyingWords() const;
    
public:
    /**
     * Checks if the requirements for the backend are met (e.g. check for runtime 
     * dependencies
     * @return true if the requirements are met, false otherwise
     */
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
     * Returns an Url pointing to the Examples of the Backend
     * The method should be overwritten by all Backends(who have an online help)
     * @return Url of the examples
     */
    virtual KUrl examplesUrl() const;
    
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
    
    /**
     * Returns a KConfigItem object, containing the url of the
     * the template used by the backend. You need to override
     * this method only if the template url item is not named "templateurl"
     * or if there are multiple templates for a single backend.
     * @return a KConfigSkeletonItem object, for configuring the template URL
     */
    virtual KConfigSkeletonItem* configTemplateUrl() const;
    
    /**
     * Returns the Document Settings for the backend
     * @return the Document Settings
     */
    virtual Cirkuit::DocumentSettings* documentSettings() const;
    
   /**
     * Access the generator class which is responsible for the actual generation of the graphics
     * @return the generator
     */
    virtual Cirkuit::Generator* generator() const;
    
    /**
     * Returns a list of the names of all the installed and enabled backends
     * @return a list of the names of all the installed and enabled backends
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
    static Backend* getBackend(const QString& name);
    /**
     * Automatically choose the best backend, based on the current document
     * @param doc a Cirkuit document
     * @return the best backend for the given document
     */
    static Backend* autoChooseBackend(Cirkuit::Document* doc);
    
    /** 
     * Overloaded operator to check if the id or the name of the backend
     * corresponds to the given QString @p rhs
     * @param rhs a backend id or name
     * @return @p true if the name or id corresponds
     */
    bool operator==(const QString& rhs) const;
    
  private:
    BackendPrivate* d;
};

}

#endif // BACKEND_H
