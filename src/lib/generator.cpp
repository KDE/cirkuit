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

#include "generator.h"
#include "backend_interface.h"
#include "format.h"
#include "document.h"
#include "command.h"
#include "failcodes.h"

#include <QFileInfo>
#include <QDir>

#include <QStandardPaths>
#include <QTemporaryFile>
//#include <KNS3>
#include <kio/filecopyjob.h>
//#include <KIO/NetAccess>

using namespace Cirkuit;

class Cirkuit::GeneratorPrivate {
public:
    GeneratorPrivate() {
        backend = 0;
        tempFile = 0;
        tempFileInfo = 0;
        resolution = 300;
    }
    Backend* backend;
    QTemporaryFile* tempFile;
    QFileInfo* tempFileInfo;
    Document* document;
    int resolution;

    QString workingDir = QString();
};

Cirkuit::Generator::Generator(Cirkuit::Backend* backend, QObject* parent): QObject(parent), d(new GeneratorPrivate)
{
    d->backend = backend;
    createWorkingDir();
    createTempFiles();
}

Cirkuit::Generator::~Generator()
{
    delete d;
}

bool Cirkuit::Generator::createWorkingDir() const
{
    // Create temporary directory for work files. Return true if successful.
    d->workingDir = QStandardPaths::writableLocation(QStandardPaths::TempLocation) + QString("/cirkuit/build");
    QDir dir(d->workingDir);
    if  (dir.exists()) {return true;};
    bool b = QDir().mkpath(d->workingDir);
    return b;
}

inline QString
Cirkuit::Generator::getWorkingDir() const
{
    return d->workingDir; // excludes trailing slash
};

void Cirkuit::Generator::createTempFiles(const QString& suffix)
{
    delete d->tempFile;
    delete d->tempFileInfo;
    
    d->tempFile = new QTemporaryFile;
    d->tempFile->setFileTemplate(getWorkingDir() + "/XXXXXX" + suffix);
    d->tempFile->open();
    d->tempFileInfo = new QFileInfo(d->tempFile->fileName());
    qDebug() << "TEMPFILE" << d->tempFileInfo->absoluteFilePath();
}

bool Cirkuit::Generator::formatExists(const Cirkuit::Format& format) const
{
    if (d->tempFileInfo == 0) {
        return false;
    }
    
    QUrl formatUrl = QUrl(getWorkingDir());
    formatUrl.fromLocalFile(d->tempFileInfo->baseName() + format.extension());
    return QFile::exists(formatUrl.path());
}

QString Cirkuit::Generator::formatPath(const Cirkuit::Format& format) const
{
    QString filename;
    if (format.type() == Format::Png || format.type() == Format::Jpeg || format.type() == Format::Ppm) {
        filename = QString("%1-1%2").arg(d->tempFileInfo->baseName()).arg(format.extension());
    } else {
        filename = QString("%1%2").arg(d->tempFileInfo->baseName()).arg(format.extension());
    }
    return getWorkingDir() + "/" + filename;
}

void Generator::setDocument(Document* doc)
{
    d->document = doc;
}

void Generator::setResolution(int resolution)
{
    d->resolution = resolution;
}

Document* Generator::document() const
{
    return d->document;
}

int Generator::resolution() const
{
    return d->resolution;
}

bool Generator::execute(Cirkuit::Command* c)
{
    // c is subtyped from QProcess
    c->setWorkingDirectory(getWorkingDir());
    connect(c, SIGNAL(newStandardError(QString,QString)), this, SIGNAL(error(QString,QString)));
    qDebug() << "Executing " << c->name() << " with arguments " << c->args();
    
    if (!c->execute()) {
        qDebug() << c->name() << " failed";
        return false;
    }
    
    qDebug() << c->name() << " executed correctly";
    emit output(c->name(), c->stdOutput());
    return true;
}

int Cirkuit::Generator::convert(const Cirkuit::Format& in, const Cirkuit::Format& out)
{
    qDebug() << "Inside the converter..." << "in: " << in.type() << " " << in.extension() << ", out: " << out.type() << " " << out.extension();

    // this class doesn't know how to convert from source
    if (in == Format::Source || out == Format::Source || out == Format::Dvi) {
        qDebug() << "Cannot convert from/to source or to DVI";
        return Fail_unimplemented_conversion;
    }
    
    // Check that input and output formats are different
    if (in == out) {
        return NoFail;
    }
    
    // For cnoversion to another vector format, use an appropriate utility (must be installed), e.g.
    // dvips, ps2pdf, epstopdf.
    // For conversion to nonvector formats, the convert utility from the ImageMagick installation can be used.
    if (out == Format::QtImage) {
        return convert(in, Format::Pdf);
    }
    
    if (in == Format::Dvi) {
        if (out == Format::Postscript) {
            QStringList args;
            args << formatPath(in) << "-q" << QString("-o") << formatPath(Format::Postscript);
            if (!execute(new Command("dvips", "", args, this))) return Fail_dvips;
            return NoFail;
        } else if (out == Format::Eps) {
            QStringList args;
            QString tmpfn = QString("%1/%2-tmp.eps").arg(d->tempFileInfo->path()).arg(d->tempFileInfo->baseName());
            args << "-E" << formatPath(in) << "-q" << "-o" << tmpfn;
            qDebug() << args;
            if (!execute(new Command("dvips", "", args, this))) return Fail_dvips;
            args.clear();
            args << "--bbox"  << "--copy" << "--output" << formatPath(Format::Eps) << tmpfn;
            if (!execute(new Command("epstool", "", args, this))) return Fail_epstool;
            return NoFail;

        } else {
            int fail = convert(in,Format::Eps);
            if (fail!=NoFail) return fail;
            return convert(Format::Eps,out);
        }
    }
    
    if (in == Format::Postscript) {
        if (out == Format::Eps) {
            QStringList args;
            args << formatPath(in) << formatPath(Format::Eps);
            if (!execute(new Command("ps2epsi", "", args, this))) return Fail_ps2epsi;
            return NoFail;
        } else if (out == Format::Pdf) {
            QStringList args;
            args << formatPath(in) << formatPath(Format::Pdf);
            if (!execute(new Command("ps2pdf", "", args, this))) return Fail_ps2pdf;
            return NoFail;
        } else if (out == Format::Png) {
            int fail = convert(in,Format::Eps);
            if (fail!=NoFail) return fail;
            return convert(Format::Eps,Format::Png);
        } else {
            return Fail_unimplemented_conversion;;
        }     
    }
    
    if (in == Format::Eps) {
        if (out == Format::Postscript) {
            QStringList args;
            args << formatPath(in) << formatPath(Format::Postscript);
            if (!execute(new Command("ps2ps", "", args, this))) return Fail_ps2ps;
            return NoFail;
        } else if (out == Format::Pdf) {
            QStringList args;
            args << formatPath(in);
            if (!execute(new Command("epstopdf", "", args, this))) return Fail_epstopdf;
            return NoFail;
        } else {
            int fail = convert(in,Format::Pdf);
            if (fail!=NoFail) return fail;
            return convert(Format::Pdf,out);
        }
    }
    
    //Pdftoppm (poppler package) converts Portable Document Format (PDF) files to color image files in Portable Pixmap (PPM) format
    //It has options for jpg and png
    //ImageMagick would be an alternative (and is needed for gif).
    // Also use pdf2svg and pdftops.
    if (in == Format::Pdf) {
        if (out == Format::Svg) {
            QStringList args;
            args << formatPath(in) << formatPath(Format::Svg);
            if (!execute(new Command("pdf2svg", "", args, this))) return Fail_pdf2svg;
            return NoFail;
        } else if (out == Format::Png) {
            QStringList args;
            args << "-png" << "-r" << QString::number(d->resolution) << formatPath(in) << d->tempFileInfo->baseName();
            if (!execute(new Command("pdftoppm", "", args, this))) return Fail_poppler_pdftoppm;
            return NoFail;
        } else if (out == Format::Jpeg) {
            QStringList args;
            args << "-jpeg" << "-r" << QString::number(d->resolution) << formatPath(in) << d->tempFileInfo->baseName();
            if (!execute(new Command("pdftoppm", "", args, this))) return Fail_poppler_pdftoppm;
            return NoFail;
        } else if (out == Format::Gif) {
            int fail = convert(in,Format::Ppm);
            if (fail!=NoFail) return fail;
            return convert(Format::Ppm,out);
        } else if (out == Format::Ppm) {
            QStringList args;
            args << "-r" << QString::number(d->resolution) << formatPath(in) << d->tempFileInfo->baseName();
            if (!execute(new Command("pdftoppm", "", args, this))) return Fail_poppler_pdftoppm;
            return NoFail;
        } else if (out == Format::Eps) {
            QStringList args;
            args << "-eps" << formatPath(in) << formatPath(out);
            if (!execute(new Command("pdftops", "", args, this))) return Fail_pdftops;
            return NoFail;
        } else if (out == Format::Postscript) {
            QStringList args;
            args << formatPath(in) << formatPath(out);
            if (!execute(new Command("pdftops", "", args, this))) return Fail_pdftops;
            return NoFail;
        }
        //qDebug() << "Fail_unimplemented_conversion1 in generator.cpp";
        return Fail_unimplemented_conversion;
    }

    if (in == Format::Ppm) {
        if (out == Format::Gif) {
            QStringList args;
            args << formatPath(Format::Ppm) << formatPath(Format::Gif);
            if (!execute(new Command("convert", "", args, this))) return Fail_imagemagick_convert;
            return NoFail;
        }
    }
    //qDebug() << "Fail_unimplemented_conversion2 in generator.cpp";
    return Fail_unimplemented_conversion;
}

int Cirkuit::Generator::generate(Document* doc, const Cirkuit::Format& format)
{
    setDocument(doc);
    return convert(Format::Source, format);
}

Cirkuit::Backend* Cirkuit::Generator::backend() const
{
    return d->backend;
}

QTemporaryFile* Cirkuit::Generator::tempFile() const
{
    return d->tempFile;
}

QFileInfo* Cirkuit::Generator::tempFileInfo() const
{
    return d->tempFileInfo;
}
