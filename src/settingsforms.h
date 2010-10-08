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

#ifndef SETTINGSFORMS_H
#define SETTINGSFORMS_H

#include "ui_cirkuit_general_settings.h"
#include "ui_cirkuit_backend_settings.h"

class CirkuitGeneralForm : public QWidget, public Ui::CirkuitGeneralForm
{
    public:
        CirkuitGeneralForm(QWidget *parent = 0);
};

class CirkuitBackendForm : public QWidget, public Ui::CirkuitBackendForm
{
    Q_OBJECT
    private slots:
        void setVisibleTemplateChooser(int index);
        
    public:
        CirkuitBackendForm(QWidget *parent = 0);
};

#endif 