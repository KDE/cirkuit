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

/**
 * Namespace collecting classes of the Cirkuit Libraries
 */
namespace Cirkuit
{    
class CommandPrivate;

/**
 * The Command class is a wrapper around KProcess with additional
 * functions to handle standard input and output and checks for the
 * existence of the main executable
 *
 * @author Matteo Agostinelli
 */
class CIRKUIT_EXPORT Command : public KProcess
{
    Q_OBJECT
public:
     /**
     * Create a new Command. 
     * @param name the name of the command to call
     * @param input optional input to the command
     * @param args optional arguments
     * @param parent optional parent
     */
    Command(const QString& name, const QString& input = "", const QStringList& args = QStringList(), QObject* parent = 0);
    /**
     * Destructor
     */
    virtual ~Command();
    
    /**
     * Checks for the existence of the executable command in the system path
     * @return true if the executable is found, false otherwise
     */
    bool checkExistence() const;
    
    /**
     * Access the name of the executable command
     * @return a string with the name
     */
    QString name() const;
    /**
     * Access the (optional) input of the command
     * @return the input to the command (empty if no input is given)
     */
    QString input() const;
    /**
     * The arguments provided to the command
     * @return a list with the arguments
     */
    QStringList args() const;
    
    /** 
     * Sets the input to be given to the command
     * @param input a string containing the input
     */
    void setInput(const QString& input);
    /**
     * Sets the arguments to the command
     * @param args a list of arguments
     */
    void setArgs(const QStringList& args);
    
    /** 
     * Return the standard error. Can be called multiple times without re-reading the standard error of the command
     * @return the standard error of the last execution of the command
     */
    QString stdError() const;
    /** 
     * Return the standard output. Can be called multiple times without re-reading the standard output of the command
     * @return the standard output of the last execution of the command
     */
    QString stdOutput() const;
    
public slots:
    /** 
     * Executes the command, waits for the end of the execution and reads the standard error and output
     * @param input optional input
     * @param args optional arguments
     * @return true if the command has executed correctly, false otherwise
     */
    bool execute(const QString& input = QString(), const QStringList& args = QStringList()); 
               
private:
    CommandPrivate* d;
};

}

#endif // COMMAND_H
