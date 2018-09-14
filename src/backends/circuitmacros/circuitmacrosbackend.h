/*
    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 2
    of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA  02110-1301, USA.

    ---
    Copyright (C) 2011 Matteo Agostinelli <agostinelli@gmail.com>
 */

#ifndef CIRCUITMACROSBACKEND_H
#define CIRCUITMACROSBACKEND_H

#include "backend_interface.h"

#include <QList>
#include <QVariant>
#include <KCoreConfigSkeleton>

namespace Cirkuit 
{
    class DocumentSettings;
    class Generator;
}

class CircuitMacrosBackend : public Cirkuit::Backend
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "circuitmacrosbackend" FILE "circuitmacrosbackend.json")
  Q_INTERFACES(Cirkuit::Backend)


public:
    explicit CircuitMacrosBackend( QObject* parent = 0, const QList<QVariant> args = QList<QVariant>());
    ~CircuitMacrosBackend();

    virtual bool checkRequirements() const;
    
    Cirkuit::DocumentSettings* documentSettings() const;
    Cirkuit::Generator* generator() const;
    virtual KConfigSkeleton* config() const;
    virtual KConfigSkeletonItem* configTemplateUrl() const;
    virtual QWidget* settingsWidget(QWidget* parent) const;
    
    virtual QString helpUrl() const;
    virtual QString examplesUrl() const;
    
    QString id() const;
    
protected:
    virtual QStringList identifyingWords() const;
};


#endif /* CIRCUITMACROSBACKEND_H */
