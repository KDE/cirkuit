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


#ifndef LOGPARSER_H
#define LOGPARSER_H

#include "cirkuit_export.h"

#include <QObject>

namespace Cirkuit {
class LogParserPrivate;
class Command;

/**
 * The LogParser class analyzes the output (standard output and standard error)
 * of a command and tries to interpret it and extract errors and messages.
 * 
 * @author Matteo Agostinelli
 */
class CIRKUIT_EXPORT LogParser: public QObject
{
    Q_OBJECT
public:
    /**
     * Default constructor
     */
    explicit LogParser(QObject* parent = 0);

    ~LogParser();

public slots:
    /**
     * Parse a command (which is already executed)
     * @param c the command
     * @returns true if there are no errors
     */
    bool parse(Command* c);
    /**
     * Overloaded function that takes the standard output and errors as inputs
     * @param stdout the standard output of a command
     * @param stderr the standard error of a command
     * @returns true if there are no errors
     */
    virtual bool parse(const QString& stdout, const QString& stderr = QString());
    
    /**
     * Appends a new message to the error log
     * @param msg the message
     */
    void appendError(const QString& msg);
    /**
     * Appends a new message to the output log
     * @param msg the message
     */
    void appendMessage(const QString& msg);
    
    /**
     * Returns the current error log
     */
    QString stdError() const;
    /**
     * Returns the current output log
     */
    QString stdOutput() const;
    
signals:
    /**
     * Signal emitted when a new (non critical) message is extracted
     */
    void message(const QString&);
    /**
     * Signal emitted when a critical error has been found
     */
    void error(const QString&);
    
protected:
    LogParserPrivate* d;
};

/**
 * The default LaTeX parser
 */
class CIRKUIT_EXPORT LatexLogParser: public LogParser
{
    Q_OBJECT
public:
    explicit LatexLogParser(QObject* parent = 0);
    
public slots:
    bool parse(const QString& stdout, const QString& stderr = QString());
};

}

#endif // LOGPARSER_H
