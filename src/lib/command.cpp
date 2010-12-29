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
    
    d->stderr = readAllStandardError();
    d->stdout = readAllStandardOutput();
    
    if (!d->stderr.isEmpty()) emit newStandardError(d->name, d->stderr);
    if (!d->stdout.isEmpty()) emit newStandardOutput(d->name, d->stderr);

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
