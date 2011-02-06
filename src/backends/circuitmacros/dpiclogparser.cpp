/*
    Copyright (C) 2011  Matteo Agostinelli <agostinelli@gmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include "dpiclogparser.h"

#include "command.h"
using namespace Cirkuit;

DpicLogParser::DpicLogParser(QObject* parent): LogParser(parent)
{

}

bool DpicLogParser::parse(const QString& stdout, const QString& stderr)
{
    Q_UNUSED(stderr);
    QRegExp pattern = QRegExp("dpic:.+ERROR.+");
    
    QStringList logLines = stdout.split(QChar('\n'));
    int i = 0;
            
    QString logLine;
    
    while (i < logLines.count()) {
        logLine = logLines[i++];
        if (logLine.contains(pattern)) {
            appendError(logLine + '\n');
            appendError(logLines[i-3] + '\n'); 
            break;
        }
    }
    if (!stdError().isEmpty()) {
        emit error(stdError());
        return false;
    }
    
    return true;
}
