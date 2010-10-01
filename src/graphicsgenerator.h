/*
    Copyright (C) 2010  Matteo Agostinelli <agostinelli@gmail.com>

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

#ifndef GRAPHICSGENERATOR_H
#define GRAPHICSGENERATOR_H

#include <QThread>

class QImage;
class Command;
class GraphicsDocument;

class KTemporaryFile;
class QFileInfo;
class QDir;

/*!
 * The class which is responsible of generating graphics in different formats. It can generate
 * a graphic file from source code or convert between different formats
 */
class GraphicsGenerator : public QObject
{
    Q_OBJECT
public:
    //! Constructor
    GraphicsGenerator(QObject* parent = 0);
    
    //! An enum of the supported formats
    enum Format {
        Source,
        Dvi,
        Postscript,
        Pdf,
        Eps,
        QtImage,
        Png,
        Unknown
    };
    
    //! Check if a format is present in the working directory
    bool formatExists(Format format) const;
    //! Return the full path to a file which represent a format
    QString filePath(Format format) const;
    
public slots:
    void readOutput();
    
    //! Clear the command queue
    void clear();
    
    //! Convert a format into another. Note that you need to call start() to actually do something
    bool convert(Format in, Format out);
    //! Generates a format from source
    bool generate(Format format = GraphicsGenerator::Pdf);
    //! Run the command queue
    bool start();
    
signals:
    void success();
    void fail();
    void error(const QString&);
    void output(const QString&);
    
protected:
    QList<Command*> m_commands;
    KTemporaryFile* m_tempFile;
    QFileInfo* m_tempFileInfo;
    QDir* m_workingDir;
    
    static QString extension(Format format);
    
    Format m_input;
    Format m_output;
};

class GeneratorThread : public QThread
{
    Q_OBJECT
public:
    GeneratorThread(GraphicsGenerator::Format in, GraphicsGenerator::Format out, GraphicsDocument* doc = 0, QObject* parent = 0);
    
    void run();
    
protected:
    GraphicsGenerator::Format m_input, m_output;
    
public slots:
    void setDocument(GraphicsDocument* doc);
    void printMessage(const QString&);
    
signals:
    void previewReady(QImage);
    
private:
    GraphicsDocument* m_doc;
};

#endif // GRAPHICSGENERATOR_H
