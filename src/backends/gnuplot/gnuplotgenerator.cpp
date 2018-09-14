/*
    Copyright (C) 2011 Matteo Agostinelli <agostinelli@gmail.com>

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

#include "gnuplotgenerator.h"

#include "document.h"
#include "documenttemplate.h"
#include "command.h"
#include "settings.h"
#include "failcodes.h"

#include <QDir>

#include <QDebug>
#include <QProcess>
#include <QTemporaryFile>
//#include <QStandardPaths>

using namespace Cirkuit;

GnuplotGenerator::GnuplotGenerator(Backend* backend, QObject* parent): Generator(backend, parent)
{

}

GnuplotGenerator::~GnuplotGenerator()
{

}

int GnuplotGenerator::convert(const Cirkuit::Format& in, const Cirkuit::Format& out)
{
    // Check if the conversion can be handled by the super-class
    int fail = Cirkuit::Generator::convert(in, out);
    if (fail==NoFail) return NoFail;
    if (fail != Fail_unimplemented_conversion) return fail;
    
    qDebug() << "Inside the Gnuplot backend...";
    
    if (in == Format::Source) {
        QTextStream stream(tempFile());
    
        QStringList args;
        args << tempFileInfo()->fileName();
        Command* gnuplot = new Command("gnuplot", QString(), args);
        
        // Regexp to match filenames
        QRegExp regex1("[\'\"]([\\w\\./\\-]+)[\'\"]");
        // Regexp to match math expressions
        QRegExp regex2("[\'\"]\\$(.+)\\$[\'\"]");
    
        QStringList origFileNames;
        QStringList lines = document()->text().split('\n');
    
        QString gnuplotOutputFile = tempFileInfo()->baseName() + ".tex";
        stream << "set output '" + gnuplotOutputFile + "'\n";
    
        foreach (QString line, lines) {
            int pos = 0;
            while ((pos = regex1.indexIn(line,pos)) != -1) {
                QString capture = regex1.cap(1);
                
                if (QFile::exists(QDir(document()->directory()).absolutePath() + '/' + capture)) {
                    if (!line.startsWith(QLatin1String("set output"))) {
                        origFileNames << capture;
                        line = line.replace(capture, QString("%1/%2").arg(QDir(document()->directory()).absolutePath()).arg(capture));
                    }
                }
                
                if (line.simplified().startsWith(QLatin1String("set output"))) {
                    line = QString("");
                }
                
                pos += regex1.matchedLength();
            }

            pos = 0;
            while ((pos = regex2.indexIn(line,pos)) != -1) {
                QString capture = regex2.cap(1);
                QString escaped = QString(capture).replace("\\", "\\\\");

                line = line.replace(capture, escaped);

                pos += regex2.matchedLength();
            }

            stream << line + '\n';
        }
        tempFile()->close();
    
        if (!execute(gnuplot)) return Fail_gnuplot;
        
        if (out == Format::Tex) {
            return NoFail;
        }
    
        DocumentTemplate gpTemplate(GnuplotSettings::templateurl().path());
        QString latexDoc = gpTemplate.insert(gnuplotOutputFile);
        
        QStringList environment = QProcess::systemEnvironment();
        // LaTeX searches (in order) circuit_macros dir, dir that contains editor document, local dir
        // The search of circuit_macros is needed to find boxdims.sty
        QString dirString = QString("TEXINPUTS=%1:%2:.:").arg(QStandardPaths::locate(QStandardPaths::GenericDataLocation,
                               "cirkuit/circuit_macros/",QStandardPaths::LocateDirectory)).arg(QDir(document()->directory()).absolutePath());

        environment << dirString;
        
        QStringList latexArgs;
        latexArgs << QString("-jobname=%1").arg(tempFileInfo()->baseName());
        
        Command* latexCmd = new Command("latex", latexDoc, latexArgs);
        latexCmd->setWorkingDirectory(getWorkingDir());
        latexCmd->setEnvironment(environment);

        if (!execute(latexCmd)) return Fail_LateXExec;

        if (!QFileInfo(formatPath(Format::Dvi)).exists()) // check we have the dvi file in temp directory.
        {
           return Fail_LateXNoOutput;
        };
        
        return convert(Format::Dvi, out);
    }
    
    return convert(Format::Dvi, out);
}


/*
 *         Command* latexCmd = new Command("pdflatex", latexDoc, latexArgs);
        latexCmd->setWorkingDirectory(getWorkingDir());
        latexCmd->setEnvironment(environment);

        if (!execute(latexCmd)) return Fail_PdfLateXExec;

        if (!QFileInfo(formatPath(Format::Pdf)).exists()) // check we have the pdf file in temp directory.
        {
           return Fail_LateXNoOutput;
        };

        return convert(Format::Pdf, out);
    }

    return convert(Format::Pdf, out);
}

*/
