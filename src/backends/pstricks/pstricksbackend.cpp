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

#include "pstricksbackend.h"
#include "pstricksdocumentsettings.h"
#include "pstricksgenerator.h"
#include "settings.h"
#include "ui_settings.h"

#include <QDebug>

PstricksBackend::PstricksBackend(QObject* parent, const QList< QVariant > args): Backend(parent, args)
{
    Q_UNUSED(args)
    qDebug() << "Creating PstricksBackend";
}

PstricksBackend::~PstricksBackend()
{
    qDebug() << "Destroying Pstricksbackend";
}

QString PstricksBackend::id() const
{
    return QString("pstricks");
}

bool PstricksBackend::checkRequirements() const
{
    return true;
}

QStringList PstricksBackend::identifyingWords() const
{
    QStringList words;
    words << "pspicture" << "psline" << "psset" << "pscurve" << "\\begin" << "\\end";
    return words;
}

QString PstricksBackend::helpUrl() const
{
    return QString("http://mirror.ctan.org/graphics/pstricks/base/doc/pstricks-doc.pdf");
}

QString PstricksBackend::examplesUrl() const
{
    return QString("http://tug.org/PSTricks/main.cgi?file=examples");
}

Cirkuit::DocumentSettings* PstricksBackend::documentSettings() const
{
    return new PstricksDocumentSettings;
}

KConfigSkeleton* PstricksBackend::config() const
{
    return PstricksSettings::self();
}

QWidget* PstricksBackend::settingsWidget(QWidget* parent) const
{
    QWidget* widget=new QWidget(parent);
    Ui::PstricksSettingsBase s;
    s.setupUi(widget);
    return widget;
}

Cirkuit::Generator* PstricksBackend::generator() const
{
    return new PstricksGenerator();
}

