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

#ifndef CIRCUITMACROSMANAGER_H
#define CIRCUITMACROSMANAGER_H

#include <QObject>


class CircuitMacrosManager : public QObject
{
    Q_OBJECT

public:
    CircuitMacrosManager();

    bool checkExistence() const;
    void downloadLatest();

    QString installedVersion() const;
    void checkOnlineVersion();

private slots:
    void unpackCircuitMacros();
    void configureCircuitMacros();
    void readVersion();

    QString findVersion(const QString& filename) const;

signals:
    void newVersionAvailable(const QString&);
    void configured();
};

#endif // CIRCUITMACROSMANAGER_H
