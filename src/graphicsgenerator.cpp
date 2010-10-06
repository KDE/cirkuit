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

#include "graphicsgenerator.h"
#include "graphicsdocument.h"
#include "command.h"
#include "circuitmacrosbackend.h"

#include <poppler-qt4.h>

#include <KStandardDirs>
#include <KTemporaryFile>
#include <QDir>
#include <QImage>

#include <QDebug>
#include "tikzbackend.h"

GraphicsGenerator::GraphicsGenerator(const QString& origDir, QObject* parent): QObject(parent), m_source(QString())
{    
    m_workingDir = new QDir(KStandardDirs::locateLocal("tmp", "cirkuit/build/", true));
    m_origDir = new QDir(origDir);
}

GraphicsGenerator::~GraphicsGenerator()
{
    delete m_workingDir;
    delete m_origDir;
    delete m_tempFile;
    delete m_tempFileInfo;
}

void GraphicsGenerator::createTempSource(const QString& extension)
{
    m_tempFile = new KTemporaryFile;
    m_tempFile->setPrefix(m_workingDir->absolutePath() + "/");
    m_tempFile->setSuffix(extension);
    
    m_tempFile->open();
    m_tempFileInfo = new QFileInfo(m_tempFile->fileName());
}

void GraphicsGenerator::setSource(const QString& source)
{
    m_source = source;
}

bool GraphicsGenerator::convert(GraphicsGenerator::Format in, GraphicsGenerator::Format out)
{
    qDebug() << "Inside the converter..." << "in: " << in << " out: " << out;
    
    // this class doesn't know how to convert from source
    if (in == Source || out == Source || out == Dvi) {
        return false;
    }
    
    // Check that input and output formats are different
    if (in == out) {
        return true;
    }
    
    if (out == QtImage) {
        return convert(in, Pdf);
    }
    
    if (in == Dvi) {
        if (out == Postscript) {
            QStringList args;
            args << filePath(in) << "-q" << QString("-o %1").arg(filePath(Postscript));
            m_commands.append(new Command("dvips", "", args, this));
            return true;
        } else if (out == Eps) {
            QStringList args;
            args << "-E" << filePath(in) << "-q" << "-o" << filePath(Eps);
            m_commands.append(new Command("dvips", "", args, this));
            return true;
        } else {
            bool b = true;
            if (!convert(in,Eps)) b = false;
            if (!convert(Eps,out)) b = false;
            return b;
        }
    }
    
    if (in == Postscript) {
        if (out == Eps) {
            QStringList args;
            args << filePath(in) << filePath(Eps);
            m_commands.append(new Command("ps2epsi", "", args, this));
            return true;
        } else if (out == Pdf) {
            QStringList args;
            args << filePath(in) << filePath(Pdf);
            m_commands.append(new Command("ps2pdf", "", args, this));
            return true;
        } else if (out == Png) {
            bool b = true;
            if (!convert(in,Eps)) b = false;
            if (!convert(Eps,Png)) b = false;
            return b;
        } else {
            return false;
        }     
    }
    
    if (in == Eps) {
        if (out == Postscript) {
            QStringList args;
            args << filePath(in) << filePath(Postscript);
            m_commands.append(new Command("ps2ps", "", args, this));
            return true;
        } else if (out == Pdf) {
            QStringList args;
            args << filePath(in);// << QString("--outfile=%1").arg(filePath(Pdf));
            m_commands.append(new Command("epstopdf", "", args, this));
            return true;
        } else {
            bool b = true;
            if (!convert(in,Pdf)) b = false;
            if (!convert(Pdf,out)) b = false;
            return b;
        }   
    }
    
    if (in == Pdf) {
        if (out == Svg) {
            QStringList args;
            args << filePath(in) << filePath(Svg);
            m_commands.append(new Command("pdf2svg", "", args, this));
            return true;
        } else if (out == Png) {
            QStringList args;
            args << "-png" << "-r 300" << filePath(in) << m_tempFileInfo->baseName();
            m_commands.append(new Command("pdftoppm", "", args, this));
            return true;
        } else if (out == Jpeg) {
            QStringList args;
            args << "-jpeg" << "-r 300" << filePath(in) << m_tempFileInfo->baseName();
            m_commands.append(new Command("pdftoppm", "", args, this));
            return true;
        } else if (out == Eps) {
            QStringList args;
            args << "-eps" << filePath(in) << filePath(out);
            m_commands.append(new Command("pdftops", "", args, this));
            return true;
        } else if (out == Postscript) {
            QStringList args;
            args << filePath(in) << filePath(out);
            m_commands.append(new Command("pdftops", "", args, this));
            return true;
        }
    }
    
    return true;
}

bool GraphicsGenerator::start()
{
    bool success = true;
    for (int i = 0; i < m_commands.count(); i++) {
        if (!execute(m_commands[i])) success = false;
    }
    
    clear();
    return success;
}

bool GraphicsGenerator::execute(Command* c)
{
    bool success = true;
    c->setWorkingDirectory(m_workingDir->absolutePath());
    qDebug() << "Executing " << c->name() << " with arguments " << c->args();
    
    if (!c->execute()) {
        emit fail();
        success = false;
    }
    
    QString stderr = c->readAllStandardError();
    QString stdout = c->readAllStandardOutput();
    
    c->setStdErr(stderr);
    c->setStdOut(stdout);
    
    if (!stderr.isEmpty()) {
        emit error(c->name(), stderr);
    }
    if (!stdout.isEmpty()) {
        emit output(c->name(), stdout);
    }
    
    return success;
}

bool GraphicsGenerator::generate(const QString& source, GraphicsGenerator::Format format)
{
    setSource(source);
    return convert(Source, format);
}

void GraphicsGenerator::clear()
{
    // clear the existing command queue
    foreach (Command* c, m_commands) {
        delete c;
    }
    m_commands.clear();
}

bool GraphicsGenerator::formatExists(GraphicsGenerator::Format format) const
{
    if (m_tempFileInfo == 0) {
        return false;
    }
    
    return m_workingDir->exists(m_tempFileInfo->baseName() + GraphicsGenerator::extension(format));
}

QString GraphicsGenerator::extension(GraphicsGenerator::Format format)
{
    switch (format) {
        case Source:
            return ".cir";
        case Dvi:
            return ".dvi";
        case Postscript:
            return ".ps";
        case Pdf:
            return ".pdf";
        case Eps:
            return ".eps";
        case Png:
            return ".png";
        case Jpeg:
            return ".jpg";
        case Svg:
            return ".svg";
        case QtImage:
        case Unknown:
        default:
            return "";
    }
}

GraphicsGenerator::Format GraphicsGenerator::format(const QString& extension)
{
    if (extension.contains("pdf")) {
        return Pdf;
    } else if (extension.contains("cir")) {
        return Source;
    } else if (extension.contains("dvi")) {
        return Dvi;
    } else if (extension.contains("eps")) {
        return Eps;
    } else if (extension.contains("ps")) {
        return Postscript;
    } else if (extension.contains("png")) {
        return Png;
    } else if (extension.contains("jpg")) {
        return Jpeg;
    } else if (extension.contains("svg")) {
        return Svg;
    }
    
    return Unknown;
}

QString GraphicsGenerator::filePath(GraphicsGenerator::Format format) const
{
    if (format == Png || format == Jpeg) {
        return QString("%1/%2-1%3").arg(m_workingDir->canonicalPath()).arg(m_tempFileInfo->baseName()).arg(GraphicsGenerator::extension(format));
    } else {
        return QString("%1/%2%3").arg(m_workingDir->canonicalPath()).arg(m_tempFileInfo->baseName()).arg(GraphicsGenerator::extension(format));
    }
}

bool GraphicsGenerator::render()
{
    if (!formatExists(Pdf)) {
        return false;
    }

    Poppler::Document* document = Poppler::Document::load(filePath(Pdf));
    if (!document || document->isLocked()) {
        delete document;
        return false;
    }

    // Access page of the PDF file
    Poppler::Page* pdfPage = document->page(0);  // Document starts at page 0
    if (pdfPage == 0) {
        return false;
    }

    // Generate a QImage of the rendered page
    QImage m_image = pdfPage->renderToImage(600,600);
    emit previewReady(m_image);

    delete pdfPage;
    delete document;
    
    return true;
}


GeneratorThread::GeneratorThread(GraphicsGenerator::Format in, GraphicsGenerator::Format out, GraphicsDocument* doc, QObject* parent): QThread(parent)
{
    setup(in,out,doc,QString(),false);
    m_gen = 0;
}

void GeneratorThread::run()
{
    delete m_gen;
    qDebug() << "IDENTIFICATION: " << m_doc->identify();
    
    if (m_doc->identify() == GraphicsDocument::CircuitMacros) {
        m_gen = new CircuitMacrosGenerator(m_origDir);
    } else if (m_doc->identify() == GraphicsDocument::Tikz || m_doc->identify() == GraphicsDocument::Circuitikz) {
        m_gen = new TikzGenerator(m_origDir);
    }
    
    connect(m_gen, SIGNAL(previewReady(QImage)), this, SIGNAL(previewReady(QImage)));
    connect(m_gen, SIGNAL(error(QString,QString)), this, SIGNAL(error(QString,QString)));
    connect(m_gen, SIGNAL(output(QString,QString)), this, SIGNAL(output(QString,QString)));
    connect(m_gen, SIGNAL(fail()), this, SIGNAL(fail()));
    m_gen->setSource(m_doc->text().toLatin1());
    m_gen->convert(m_input, m_output);   
    m_gen->start();
    
    if (m_output == GraphicsGenerator::QtImage) {
        m_gen->render();
    }
    
    if (m_saveToFile) {
        emit fileReady(m_gen->filePath(m_output));
    }
}

GeneratorThread::~GeneratorThread()
{
    delete m_gen;
}

void GeneratorThread::setup(GraphicsGenerator::Format in, GraphicsGenerator::Format out, GraphicsDocument* doc, const QString& origDir, bool saveToFile)
{
    m_input = in;
    m_output = out;
    m_doc = doc;
    m_origDir = origDir;
    m_saveToFile = saveToFile;
}

GraphicsGenerator* GeneratorThread::builder()
{
    return m_gen;
}

