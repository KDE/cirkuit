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

#include "tikzbackend.h"
#include "tikzgenerator.h"
#include "tikzdocumentsettings.h"
#include "settings.h"
#include "ui_settings.h"

#include "kdebug.h"

#include "cirkuit_macros.h"

#include <KProcess>

TikzBackend::TikzBackend( QObject* parent, const QList<QVariant> args ) : Cirkuit::Backend( parent )
{
    Q_UNUSED(args)
    kDebug()<<"Creating TikzBackend";
}

TikzBackend::~TikzBackend()
{
    kDebug()<<"Destroying TikzBackend";
}

bool TikzBackend::checkRequirements() const
{
    return true;
}

QString TikzBackend::id() const
{
    return "tikz";
}

Cirkuit::DocumentSettings* TikzBackend::documentSettings() const
{
    return new TikzDocumentSettings();
}

Cirkuit::Generator* TikzBackend::generator() const
{
    return new TikzGenerator();
}

KConfigSkeleton* TikzBackend::config() const
{
    return TikzSettings::self();
}

QWidget* TikzBackend::settingsWidget(QWidget* parent) const
{
    QWidget* widget=new QWidget(parent);
    Ui::TikzSettingsBase s;
    s.setupUi(widget);
    return widget;
}

K_EXPORT_CIRKUIT_PLUGIN(tikzbackend, TikzBackend)
