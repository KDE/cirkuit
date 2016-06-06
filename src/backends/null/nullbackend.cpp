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
    Copyright (C) 2009 Alexander Rieder <alexanderrieder@gmail.com>
    Copyright (C) 2011 Matteo Agostinelli <agostinelli@gmail.com>
 */

#include "nullbackend.h"
#include "nullgenerator.h"
#include "nulldocumentsettings.h"

#include "kdebug.h"

#include "cirkuit_macros.h"

NullBackend::NullBackend( QObject* parent, const QList<QVariant> args ) : Cirkuit::Backend( parent )
{
    Q_UNUSED(args)
    qCDebug(CIRKUIT_DEBUG)<<"Creating NullBackend";
}

NullBackend::~NullBackend()
{
    qCDebug(CIRKUIT_DEBUG)<<"Destroying NullBackend";
}

bool NullBackend::checkRequirements() const
{
    return false;
}

QString NullBackend::id() const
{
    return "null";
}

Cirkuit::DocumentSettings* NullBackend::documentSettings() const
{
    return new NullDocumentSettings();
}

Cirkuit::Generator* NullBackend::generator() const
{
    return new NullGenerator();
}


K_EXPORT_CIRKUIT_PLUGIN(nullbackend, NullBackend)
