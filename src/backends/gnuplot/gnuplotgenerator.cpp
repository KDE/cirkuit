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

#include <QDir>

#include <KDebug>
#include <KProcess>
#include <KTemporaryFile>
#include <KStandardDirs>

using namespace Cirkuit;

GnuplotGenerator::GnuplotGenerator(Backend* backend, QObject* parent): Generator(backend, parent)
{

}

GnuplotGenerator::~GnuplotGenerator()
{

}

bool GnuplotGenerator::convert(const Cirkuit::Format& in, const Cirkuit::Format& out)
{
     // Check if the conversion can be handled by the super-class
    bool done = Generator::convert(in, out);
    if (done) {
        return true;
    }
    
    kDebug() << "Inside the Gnuplot backend...";
    
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
        QStringList lines = document()->text().split("\n");
    
        QString gnuplotOutputFile = tempFileInfo()->baseName() + ".tex";
        stream << "set output '" + gnuplotOutputFile + "'\n";
    
        foreach (QString line, lines) {
            int pos = 0;
            while ((pos = regex1.indexIn(line,pos)) != -1) {
                QString capture = regex1.cap(1);
                
                if (QFile::exists(QDir(document()->directory()).absolutePath() + "/" + capture)) {
                    if (!line.startsWith("set output")) {
                        origFileNames << capture;
                        line = line.replace(capture, QString("%1/%2").arg(QDir(document()->directory()).absolutePath()).arg(capture));
                    }
                }
                
                if (line.simplified().startsWith("set output")) {
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

            stream << line + "\n";
        }
        tempFile()->close();
    
        execute(gnuplot);
        
        if (out == Format::Tex) {
            return true;
        }
    
        DocumentTemplate gpTemplate(GnuplotSettings::gptemplateurl().path());
        QString latexDoc = gpTemplate.insert(gnuplotOutputFile);
        
        QStringList environment = QProcess::systemEnvironment();
        // the following enviroment variable is needed to find boxdims.sty in the circuit maaros distribution
        QString dirString = QString("TEXINPUTS=.:%1:").arg(QDir(document()->directory()).absolutePath());
        environment << dirString;
        
        QStringList latexArgs;
        latexArgs << QString("-jobname=%1").arg(tempFileInfo()->baseName());
        
        Command* latexCmd = new Command("pdflatex", latexDoc, latexArgs);
        latexCmd->setWorkingDirectory(workingDir().path());
        latexCmd->setEnvironment(environment);
        execute(latexCmd);
        
        return convert(Format::Pdf, out);
    }
    
    return convert(Format::Pdf, out);
}
