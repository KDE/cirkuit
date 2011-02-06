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

#include "command.h"

#include <QFileInfo>
#include <QDir>
#include <QStringListIterator>
#include <KDebug>
#include <KProcess>
#include <KStandardDirs>
#include <KDebug>

using namespace Cirkuit;

class Cirkuit::CommandPrivate {
public:
    QString name, input;
    QString stderr, stdout;
    QStringList args;
};

Command::Command(const QString& name, const QString& input, const QStringList& args, QObject* parent): KProcess(parent), d(new CommandPrivate)
{
    d->name = name;
    setOutputChannelMode(SeparateChannels);
    setInput(input);
    setArgs(args);
}

Command::~Command()
{
    // destroy the d-pointer
    delete d;
}

QStringList Command::args() const
{
    return d->args;
}

QString Command::input() const
{
    return d->input;
}

QString Command::name() const
{
    return d->name;
}

void Command::setArgs(const QStringList& args)
{
    d->args = args;
}

void Command::setInput(const QString& input)
{
    d->input = input;
}

bool Command::execute(const QString& input, const QStringList& args)
{   
    if (!input.isEmpty()) setInput(input);
    if (!args.isEmpty()) setArgs(args);
    
    if (!checkExistence()) {
        kError() << "Program not found!!";
        return false;
    }
    
    setProgram(d->name, d->args);
    start();
    
    if (!waitForStarted()) {
        return false;
    }
    
    write(d->input.toLatin1());
    closeWriteChannel();
    
    if (!waitForFinished()) {
        return false;   
    }
        
    parseStandardOutput();
    
    if (!d->stdout.isEmpty()) emit newStandardOutput(d->name, d->stderr);
    if (!d->stderr.isEmpty()) {
        emit newStandardError(d->name, d->stderr);
        return false;
    }    

    return true;
}

bool Command::checkExistence() const
{
    return KStandardDirs::findExe(d->name) != QString();
}

QString Command::stdError() const
{
    return d->stderr;
}

QString Command::stdOutput() const
{
    return d->stdout;
}

bool Command::checkExistence(const QString& name)
{
    return KStandardDirs::findExe(name) != QString();
}

void Command::parseStandardOutput()
{
    QString stdout = readAllStandardOutput();
    QString stderr = readAllStandardError();
    
    d->stdout = stdout;
    d->stderr = stderr;
    
    if (d->name.contains("latex", Qt::CaseInsensitive)) {
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
    }
}
