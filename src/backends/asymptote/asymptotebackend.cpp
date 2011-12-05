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

#include "asymptotebackend.h"
#include "asymptotedocumentsettings.h"
#include "asymptotegenerator.h"

#include "command.h"
#include "cirkuit_macros.h"
using namespace Cirkuit;

AsymptoteBackend::AsymptoteBackend(QObject* parent, const QList< QVariant > args): Backend(parent, args)
{
    kDebug()<<"Creating AsymptoteBackend";
}

bool AsymptoteBackend::checkRequirements() const
{
    Command asycmd("asy");
    return asycmd.checkExistence();
}

Cirkuit::DocumentSettings* AsymptoteBackend::documentSettings() const
{
    return new AsymptoteDocumentSettings;
}

Cirkuit::Generator* AsymptoteBackend::generator() const
{
    return new AsymptoteGenerator;
}

QString AsymptoteBackend::id() const
{
    return "asymptote";
}

QStringList AsymptoteBackend::identifyingWords() const
{
    QStringList list;
    list << "real" << "pair" << "path" << "draw";
    return list;
}

K_EXPORT_CIRKUIT_PLUGIN(asymptotebackend, AsymptoteBackend)
