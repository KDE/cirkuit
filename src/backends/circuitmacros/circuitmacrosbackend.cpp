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

#include "kdebug.h"

#include "cirkuit_macros.h"
#include "cirkuit_circuitmacrosbackend_debug.h"

#include <KProcess>

CircuitMacrosBackend::CircuitMacrosBackend( QObject* parent, const QList<QVariant> args ) : Cirkuit::Backend( parent )
{
    Q_UNUSED(args)
    qCDebug(CIRKUIT_DEBUG)<<"Creating CircuitMacrosBackend";
}

CircuitMacrosBackend::~CircuitMacrosBackend()
{
    qCDebug(CIRKUIT_DEBUG)<<"Destroying CircuitMacrosBackend";
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

KUrl CircuitMacrosBackend::examplesUrl() const
{
    return KStandardDirs::locateLocal("data", "cirkuit/circuit_macros/examples/examples.ps");
}

KUrl CircuitMacrosBackend::helpUrl() const
{
    return KStandardDirs::locateLocal("data", "cirkuit/circuit_macros/doc/CMman.pdf");
}

KConfigSkeletonItem* CircuitMacrosBackend::configTemplateUrl() const
{
    if (CircuitMacrosSettings::picInterpreter() == CircuitMacrosSettings::EnumPicInterpreter::dpic_pgf) {
        return config()->findItem("tikztemplateurl");
    }
    
    return Backend::configTemplateUrl();
}

K_EXPORT_CIRKUIT_PLUGIN(circuitmacrosbackend, CircuitMacrosBackend)

#include "circuitmacrosbackend.moc"