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
#include <QDebug>
#include <cstdlib>

#include <KProcess>

using namespace Cirkuit;

Command::Command(const QString& name, const QString& input, const QStringList& args, QObject* parent): KProcess(parent)
{
    m_name = name;
    setOutputChannelMode(SeparateChannels);
    setInput(input);
    setArgs(args);
}

QStringList Command::args() const
{
    return m_args;
}

QString Command::input() const
{
    return m_input;
}

QString Command::name() const
{
    return m_name;
}

void Command::setArgs(const QStringList& args)
{
    m_args = args;
}

void Command::setInput(const QString& input)
{
    m_input = input;
}

bool Command::execute(const QString& input, const QStringList& args)
{   
    if (!input.isEmpty()) setInput(input);
    if (!args.isEmpty()) setArgs(args);
    
    if (!checkExistence()) {
        qDebug() << "Program not found!!";
        return false;
    }
    
    setProgram(m_name, m_args);
    start();
    
    if (!waitForStarted()) {
        return false;
    }
    
    write(m_input.toLatin1());
    closeWriteChannel();
    
    if (!waitForFinished()) {
        return false;   
    }

    return true;
}

bool Command::checkExistence() const
{
    QString pathEnv = getenv("PATH");
    QStringList pathDirs = pathEnv.split(":");
    
    bool found = false;
    foreach (QString dir, pathDirs) {
        if (checkExistenceInDir(dir)) {
            found = true;
        }
    }
        
    return found;
}

bool Command::checkExistenceInDir(const QString& dirname) const
{
    QFileInfo fileinfo(QDir(dirname),m_name);
    return fileinfo.exists();
}

QString Command::stderr() const
{
    return m_stderr;
}

QString Command::stdout() const
{
    return m_stdout;
}

void Command::setStdErr(const QString& stderr)
{
    m_stderr = stderr;
}

void Command::setStdOut(const QString& stdout)
{
    m_stdout = stdout;
}

