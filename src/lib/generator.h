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

/**
 * The Generator class is responsible for the generation of the graphical output. 
 * It provides instructions on how to generate a desired Format from the source 
 * code entered by the user. The Generator is also able to convert among different
 * graphical formats via external tools.
 * 
 * The Generator must be redefined by each Backend in order to produce the 
 * desired output from the source code.
 * 
 * @author Matteo Agostinelli
 */
class CIRKUIT_EXPORT Generator : public QObject
{
    Q_OBJECT
public:
    /**
     * Default constructor, with an optional pointer to the backend
     * @param backend a pointer to a backend
     */
    explicit Generator(Cirkuit::Backend* backend = 0, QObject* parent = 0);
    /**
     * Default destructor
     */
    virtual ~Generator();
    
    /**
     * This function returns the temporary working directory where all the 
     * conversions will take place.
     * @return the url of the working directory
     */
    static KUrl workingDir();
    
    /**
     * Check if a format is present in the working directory
     * @param format the desired format
     * @return true if the specified format is found in the working directory
     */
    bool formatExists(const Format& format) const;
    /**
     * Return the full path to the file representing the specified format
     * @param format the desired format
     * @return the path to the file corresponding to the format
     */
    QString formatPath(const Format& format) const;
    
protected slots:
    /**
     * Create the initial temporary files where the source code will be written
     * @param suffix the suffix of the temporary files
     */ 
    void createTempFiles(const QString& suffix = QString(".tmp"));
    /**
     * Executes a Command
     * @param command the command
     * @return true if the command is executed successfully, false otherwise
     */ 
    bool execute(Cirkuit::Command* command);
    
public slots:    
    /**
     * Convert a format into another. Note that this function only generate the command queue. 
     * You need to call start() to actually execute the queue
     * @param input the input format
     * @param output the output format
     * @return true if the operation is successful
     */
    virtual bool convert(const Format& input, const Format& output);
    /**
     * Similar to convert, but the starting point is the source code defined in the document
     * @param doc the document holding the source code
     * @param output the output format
     * @return true if the operation is successful
     */
    virtual bool generate(Document* doc, const Format& output = Format::Pdf);
    
    /**
     * Sets the current document
     * @param doc the document
     */
    void setDocument(Document* doc);
    
    /**
     * Gets the current document
     * @return the current document
     */
    Document* document() const;
    
    /**
     * Sets the resolution of the graphic (when applicable)
     * @param resolution the resolution
     */
    void setResolution(int resolution);
    
    /** 
     * Returns the resolution
     * @return the resolution
     */
    int resolution() const;
    
    /**
     * Render the graphic and generate a QImage. This is an async call, 
     * the result will be emitted through the previewReady signal
     */
    bool render();
    
signals:
    /**
     * Signal emitted if the generation was successful
     */
    void success();
    /**
     * Signal emitted if the generation failed
     */
    void fail();
    /**
     * Signal emitted when an error occurs
     * @param appname the application that caused the error
     * @param msg the error message
     */
    void error(const QString& appname, const QString& msg);
    /**
     * Signal emitted when an output is generated
     * @param appname the application that generated the output
     * @param msg the output of the application
     */
    void output(const QString& appname, const QString& msg);
    /**
     * This signal is emitted when the preview has been generated and 
     * it is ready
     * @param image the rendered image
     */    
    void previewReady(const QImage& image);
    
protected:
    /**
     * A temporary file
     */
    KTemporaryFile* tempFile() const;
    /**
     * Informations about the temporary file
     */
    QFileInfo* tempFileInfo() const;
    /**
     * A pointer to the current backend
     */
    Cirkuit::Backend* backend() const;
  
    GeneratorPrivate* d;
};

}
#endif // DOCUMENT_H
