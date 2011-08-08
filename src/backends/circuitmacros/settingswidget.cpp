/***************************************************************************
*   Copyright (C) 2011 by Matteo Agostinelli                              *
*   agostinelli@gmail.com                                                 *
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
*   This program is distributed in the hope that it will be useful,       *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
*   GNU General Public License for more details.                          *
*                                                                         *
*   You should have received a copy of the GNU General Public License     *
*   along with this program; if not, write to the                         *
*   Free Software Foundation, Inc.,                                       *
*   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.          *
***************************************************************************/

#include "settingswidget.h"
#include "settings.h"

CircuitMacrosSettingsWidget::CircuitMacrosSettingsWidget(QWidget* parent, Qt::WindowFlags f): QWidget(parent, f)
{
    setupUi(this);
    
    CircuitMacrosSettings::self()->readConfig();
    kcfg_templateurl->setUrl(CircuitMacrosSettings::templateurl());
    kcfg_tikztemplateurl->setUrl(CircuitMacrosSettings::tikztemplateurl());
    setVisibleTemplateChooser(kcfg_PicInterpreter->currentIndex());
    connect(kcfg_PicInterpreter, SIGNAL(currentIndexChanged(int)), this, SLOT(setVisibleTemplateChooser(int)));
}

void CircuitMacrosSettingsWidget::setVisibleTemplateChooser(int index)
{
    kcfg_templateurl->setVisible(index != 1);
    lbl_template->setVisible(index != 1);
      
    kcfg_tikztemplateurl->setVisible(index == 1);
    lbl_tikztemplate->setVisible(index == 1);
}

