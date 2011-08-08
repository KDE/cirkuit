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

#include "command.h"
#include "logparser.h"

#include <QFileInfo>
#include <QDir>
#include <QStringListIterator>
#include <KDebug>
#include <KProcess>
#include <KStandardDirs>

using namespace Cirkuit;

class Cirkuit::CommandPrivate {
public:
    QString name, input;
    QString stderr, stdout;
    QStringList args;
    LogParser* logParser;
    
    CommandPrivate() {
        logParser = 0;
    }
};

Command::Command(const QString& name, const QString& input, const QStringList& args, QObject* parent): KProcess(parent), d(new CommandPrivate)
{
    d->name = name;
    setLogParser(new LogParser);
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

void Command::setLogParser(LogParser* parser)
{
    delete d->logParser;
    
    d->logParser = parser;
    connect(d->logParser, SIGNAL(message(QString)), this, SLOT(newMessage(QString)));
    connect(d->logParser, SIGNAL(error(QString)), this, SLOT(newError(QString)));
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
        
    if (!parseLog()) return false;
    
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

bool Command::parseLog()
{
    d->stdout = readAllStandardOutput();
    d->stderr = readAllStandardError();

    return d->logParser->parse(d->stdout, d->stderr);
}

void Command::newError(const QString& msg)
{
    emit newStandardError(d->name, msg);
}

void Command::newMessage(const QString& msg)
{
    emit newStandardOutput(d->name, msg);
}
