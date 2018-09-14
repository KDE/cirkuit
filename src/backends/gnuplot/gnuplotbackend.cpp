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

#include "gnuplotbackend.h"
#include "gnuplotgenerator.h"
#include "gnuplotdocumentsettings.h"
#include "settings.h"
#include "ui_settings.h"

#include <QDebug>
#include <KProcess>

GnuplotBackend::GnuplotBackend( QObject* parent, const QList<QVariant> args ) : Cirkuit::Backend( parent )
{
    Q_UNUSED(args)
    qDebug()<<"Creating GnuplotBackend";
}

GnuplotBackend::~GnuplotBackend()
{
    qDebug()<<"Destroying GnuplotBackend";
}

bool GnuplotBackend::checkRequirements() const
{
    return true;
}

QString GnuplotBackend::id() const
{
    return "gnuplot";
}

Cirkuit::DocumentSettings* GnuplotBackend::documentSettings() const
{
    return new GnuplotDocumentSettings();
}

Cirkuit::Generator* GnuplotBackend::generator() const
{
    return new GnuplotGenerator();
}

KConfigSkeleton* GnuplotBackend::config() const
{
    return GnuplotSettings::self();
}

QWidget* GnuplotBackend::settingsWidget(QWidget* parent) const
{
    QWidget* widget=new QWidget(parent);
    Ui::GnuplotSettingsBase s;
    s.setupUi(widget);
    return widget;
}

QStringList GnuplotBackend::identifyingWords() const
{
    QStringList words;
    words << "set terminal" << "plot" << "using";
    return words;
}

QString GnuplotBackend::helpUrl() const
{
    return QString("http://www.gnuplot.info/documentation.html");
}

QString GnuplotBackend::examplesUrl() const
{
    return QString("http://gnuplot.sourceforge.net/demo/");
}


