/***************************************************************************
*   Copyright (C) 2012 by Matteo Agostinelli                              *
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
#include <QString>
#include <QObject>
#include "format.h"

class KCmdLineArgs;

namespace Cirkuit
{
    class Generator;
    class Document;
    class Backend;
}

class BatchRun: public QObject
{
    Q_OBJECT
    
public:
    BatchRun(KCmdLineArgs* args);
    
    void go();
    void initializeBackends();
    
private:
    QString m_inputFile, m_outputFile, m_inputDir;
    Cirkuit::Backend* m_backend;
    Cirkuit::Format m_outputFormat;
};