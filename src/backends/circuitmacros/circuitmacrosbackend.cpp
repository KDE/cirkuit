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

#include "circuitmacrosbackend.h"
#include "circuitmacrosgenerator.h"
#include "circuitmacrosdocumentsettings.h"
#include "settings.h"
#include "settingswidget.h"

#include <QDebug>

#include <KProcess>

CircuitMacrosBackend::CircuitMacrosBackend( QObject* parent, const QList<QVariant> args ) : Cirkuit::Backend( parent )
{
    Q_UNUSED(args)
    qDebug()<<"Creating CircuitMacrosBackend";
}

CircuitMacrosBackend::~CircuitMacrosBackend()
{
    qDebug()<<"Destroying CircuitMacrosBackend";
}

bool CircuitMacrosBackend::checkRequirements() const
{
    return true;
}

QString CircuitMacrosBackend::id() const
{
    return "circuitmacros";
}

Cirkuit::DocumentSettings* CircuitMacrosBackend::documentSettings() const
{
    return new CircuitMacrosDocumentSettings();
}

Cirkuit::Generator* CircuitMacrosBackend::generator() const
{
    return new CircuitMacrosGenerator();
}

KConfigSkeleton* CircuitMacrosBackend::config() const
{
    return CircuitMacrosSettings::self();
}

QWidget* CircuitMacrosBackend::settingsWidget(QWidget* parent) const
{
    return new CircuitMacrosSettingsWidget(parent);
}

QStringList CircuitMacrosBackend::identifyingWords() const
{
    QStringList words;
    words << ".PS" << ".PE" << "cct_init" << "resistor";
    return words;
}

QString CircuitMacrosBackend::examplesUrl() const
{
    return QStandardPaths::locate(QStandardPaths::GenericDataLocation, "cirkuit/circuit_macros/examples/examples.ps",QStandardPaths::LocateFile);
}

QString CircuitMacrosBackend::helpUrl() const
{
    return QStandardPaths::locate(QStandardPaths::GenericDataLocation, "cirkuit/circuit_macros/doc/Circuit_macros.pdf",QStandardPaths::LocateFile);
}

KConfigSkeletonItem* CircuitMacrosBackend::configTemplateUrl() const
{
    if (CircuitMacrosSettings::picInterpreter() == CircuitMacrosSettings::EnumPicInterpreter::dpic_pgf) {
        return config()->findItem("tikztemplateurl");
    }
    
    return Backend::configTemplateUrl();
}


