/*
    Copyright (C) 2011  Matteo Agostinelli <agostinelli@gmail.com>

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

#ifndef COMMAND_H
#define COMMAND_H

#include "cirkuit_export.h"

#include <KProcess>

namespace Cirkuit
{    
class CommandPrivate;

class CIRKUIT_EXPORT Command : public KProcess
{
    Q_OBJECT
public:
    Command(const QString& name, const QString& input = "", const QStringList& args = QStringList(), QObject* parent = 0);
    
    bool checkExistence() const;
    
    QString name() const;
    QString input() const;
    QStringList args() const;
    
    void setInput(const QString& input);
    void setArgs(const QStringList& args);
    
    QString stderr() const;
    QString stdout() const;
    
public slots:
    bool execute(const QString& input = QString(), const QStringList& args = QStringList()); 
               
private:
    CommandPrivate* d;
};

}

#endif // COMMAND_H
