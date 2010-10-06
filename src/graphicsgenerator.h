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
    GraphicsGenerator(const QString& origDir = "", QObject* parent = 0);
    virtual ~GraphicsGenerator();
    
    //! An enum of the supported formats
    enum Format {
        Source,
        Dvi,
        Postscript,
        Pdf,
        Eps,
        QtImage,
        Png,
        Jpeg,
        Svg,
        Unknown
    };
    
    //! Check if a format is present in the working directory
    bool formatExists(Format format) const;
    //! Return the full path to a file which represent a format
    QString filePath(Format format) const;
    
    static QString extension(Format format);
    static Format format(const QString& extension);
    
public slots:
    //! Clear the command queue
    void clear();
    
    //! Convert a format into another. Note that you need to call start() to actually do something
    virtual bool convert(Format in, Format out);
    //! Generates a format from source
    virtual bool generate(const QString& source, Format format = GraphicsGenerator::Pdf);
    //! Run the command queue
    bool start();
    //! Set the source
    void setSource(const QString& source);
    
    //! Render the image using poppler
    bool render();
    
signals:
    void success();
    void fail();
    void error(const QString& appname, const QString& msg);
    void output(const QString& appname, const QString& msg);
    void previewReady(const QImage&);
    
protected:
    QList<Command*> m_commands;
    KTemporaryFile* m_tempFile;
    QFileInfo* m_tempFileInfo;
    QDir* m_workingDir;
    QDir* m_origDir;
    QString m_source;
    
    void createTempSource(const QString& extension);
    bool execute(Command* c);
};

class GeneratorThread : public QThread
{
    Q_OBJECT
public:
    GeneratorThread(GraphicsGenerator::Format in, GraphicsGenerator::Format out, GraphicsDocument* doc = 0, QObject* parent = 0);
    ~GeneratorThread();
    
    void run();
    GraphicsGenerator* builder();
    
protected:
    GraphicsGenerator::Format m_input, m_output;
    
public slots:
    void setup(GraphicsGenerator::Format in, GraphicsGenerator::Format out, GraphicsDocument* doc, const QString& origDir = QString(), bool saveToFile = false);
    
signals:
    void previewReady(const QImage);
    void fileReady(const QString);
    
    void error(const QString& appname, const QString& msg);
    void output(const QString& appname, const QString& msg);
    void fail();
    
private:
    GraphicsDocument* m_doc;
    GraphicsGenerator* m_gen;
    QString m_origDir;
    bool m_saveToFile;
};

#endif // GRAPHICSGENERATOR_H
