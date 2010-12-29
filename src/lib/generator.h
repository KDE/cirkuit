/*
    Copyright (C) 2009  Matteo Agostinelli <agostinelli@gmail.com>

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

#ifndef GENERATOR_H
#define GENERATOR_H

#include "cirkuit_export.h"
#include "format.h"

#include <QImage>

class QFileInfo;
class KTemporaryFile;

namespace Cirkuit
{
class Document;
class Command;
class Backend;
class GeneratorPrivate;

class CIRKUIT_EXPORT Generator : public QObject
{
    Q_OBJECT
public:
    explicit Generator(Cirkuit::Backend* backend = 0, QObject* parent = 0);
    virtual ~Generator();
    
    static KUrl workingDir();
    
    //! Check if a format is present in the working directory
    bool formatExists(const Format& format) const;
    //! Return the full path to a file which represent a format
    QString formatPath(const Format& format) const;
    
protected slots:
    void createTempFiles(const QString& suffix = QString(".tmp"));
    bool execute(Cirkuit::Command* c);
    
public slots:
    //! Clear the command queue
    void clear();
    
    //! Convert a format into another. Note that you need to call start() to actually do something
    virtual bool convert(const Format& in, const Format& out);
    //! Generates a format from source
    virtual bool generate(Document* doc, const Format& format = Format::Pdf);
    //! Run the command queue
    bool start();
    
    //! Set the source document
    void setDocument(Document* doc);
    //! Set the resolution of the generated graphics
    void setResolution(int resolution);
    
    Document* document() const;
    int resolution() const;
    
    //! Render the image using poppler
    bool render();
    
signals:
    void success();
    void fail();
    void error(const QString& appname, const QString& msg);
    void output(const QString& appname, const QString& msg);
    void previewReady(const QImage&);
    
protected:
    KTemporaryFile* tempFile() const;
    QFileInfo* tempFileInfo() const;
    Cirkuit::Backend* backend() const;
    
protected:
    GeneratorPrivate* d;
};

}
#endif // DOCUMENT_H
