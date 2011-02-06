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

#include "logparser.h"
#include "command.h"

#include <KDebug>

using namespace Cirkuit;

class Cirkuit::LogParserPrivate 
{
public:
    QString stderr;
    QString stdout;
};

LogParser::LogParser(QObject* parent): QObject(parent), d(new LogParserPrivate)
{
}

bool LogParser::parse(Command* c)
{
    return parse(c->stdOutput(), c->stdError());
}

bool LogParser::parse(const QString& stdout, const QString& stderr)
{
    d->stderr = stderr;
    d->stdout = stdout;
    
    emit message(stdout);
    emit error(stderr);
    
    return d->stderr.isEmpty();
}

LatexLogParser::LatexLogParser(QObject* parent): LogParser(parent)
{

}

bool LatexLogParser::parse(const QString& stdout, const QString& stderr)
{
    kDebug() << "Parsing LaTeX log";
    QList<QRegExp> keywordPatterns;
    keywordPatterns << QRegExp("(\\S*):(\\d+): (.*$)")
        << QRegExp("Undefined control sequence")
        << QRegExp("LaTeX Warning:") << QRegExp("LaTeX Error:")
        << QRegExp("Runaway argument?")
        << QRegExp("Missing character: .*!") << QRegExp("Error:");
        
    QStringList logLines = stdout.split(QChar('\n'));
    int i = 0;
            
    QString logLine;
    while (i < logLines.count()) {
        logLine = logLines[i++];
        if (keywordPatterns.at(0).indexIn(logLine) > -1) {
            // show error message and correct line number
//          QString lineNum = QString::number(keywordPatterns[0].cap(2).toInt() - m_templateStartLineNumber);
            QString lineNum = QString::number(keywordPatterns[0].cap(2).toInt());
            const QString errorMsg = keywordPatterns[0].cap(3);
            d->stderr += "[LaTeX] Line " + lineNum + ": " + errorMsg;

            // while we don't get a line starting with "l.<number> ...", we have to add the line to the first error message
            QRegExp rx("^l\\.(\\d+)(.*)");
            logLine = logLines[++i];
            while (rx.indexIn(logLine) < 0 && i < logLines.count()) {
                if (logLine.isEmpty())
                    d->stderr += "\n[LaTeX] Line " + lineNum + ": ";
                if (!logLine.startsWith(QLatin1String("Type"))) // don't add lines that invite the user to type a command, since we are not in the console
                    d->stderr += logLine;
                logLine = logLines[++i];
            }
            d->stderr += '\n';
            if (i >- logLines.count()) break;

            // add the line starting with "l.<number> ..." and the next line
            lineNum = QString::number(rx.cap(1).toInt() - 7);
            logLine = "l." + lineNum + rx.cap(2);
            d->stderr += logLine + '\n';
            d->stderr += logLines[++i] + '\n';
        } else {
            for (int j = 1; j < keywordPatterns.size(); ++j) {
                if (logLine.contains(keywordPatterns.at(j))) {
                    d->stderr += logLine + '\n';
                    d->stderr += logLines[++i] + '\n';
                    d->stderr += logLines[++i] + '\n';
                    break;
                }
            }
        }
    }
    if (!d->stderr.isEmpty()) {
        emit error(d->stderr);
    }
    
    return d->stderr.isEmpty();
}

void LogParser::appendError(const QString& msg)
{
    d->stderr.append(msg);
}

void LogParser::appendMessage(const QString& msg)
{
    d->stdout.append(msg);
}

QString LogParser::stdError() const
{
    return d->stderr;
}

QString LogParser::stdOutput() const
{
    return d->stdout;
}
