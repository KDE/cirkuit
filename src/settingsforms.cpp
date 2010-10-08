/*
    Copyright (C) 2009  Matteo Agostinelli <agostinelli@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "settingsforms.h"

CirkuitBackendForm::CirkuitBackendForm(QWidget* parent): QWidget(parent)
{
    setupUi(this);
    setVisibleTemplateChooser(kcfg_PicInterpreter->currentIndex());
    connect(kcfg_PicInterpreter, SIGNAL(currentIndexChanged(int)), this, SLOT(setVisibleTemplateChooser(int)));    
}

void CirkuitBackendForm::setVisibleTemplateChooser(int index)
{
    kcfg_cmtemplateurl->setVisible(index != 1);
    lbl_cmtemplate->setVisible(index != 1);
      
    kcfg_cmtikztemplateurl->setVisible(index == 1);
    lbl_cmtikztemplate->setVisible(index == 1);
}

CirkuitGeneralForm::CirkuitGeneralForm(QWidget* parent): QWidget(parent)
{
    setupUi(this);
}
