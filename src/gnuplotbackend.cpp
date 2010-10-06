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

#include "gnuplotbackend.h"
#include "documenttemplate.h"
#include "command.h"

#include <KStandardDirs>
#include <QProcess>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include <KTemporaryFile>

GnuplotGenerator::GnuplotGenerator(const QString& origDir, QObject* parent): GraphicsGenerator(origDir, parent)
{
    createTempSource(".gp");
}

bool GnuplotGenerator::convert(GraphicsGenerator::Format in, GraphicsGenerator::Format out)
{
    // Check if the conversion can be handled by the super-class
    bool done = GraphicsGenerator::convert(in, out);
    if (done) {
        return true;
    }
    
    qDebug() << "Inside the Gnuplot backend...";
    
    if (in == Source) {
        QTextStream stream(m_tempFile);
    
        QStringList args;
        args << m_tempFileInfo->fileName();
        Command* gnuplot = new Command("gnuplot", QString(), args);
        
        QRegExp regex1("[\'\"]([\\w\\./\\-]+)[\'\"]");
    
        QStringList origFileNames;
        QStringList lines = m_source.split("\n");
    
        QString gnuplotOutputFile = m_tempFileInfo->baseName() + ".lua";
        stream << "set output '" + gnuplotOutputFile + "'\n";
    
        foreach (QString line, lines) {
            int pos = 0;
            while ((pos = regex1.indexIn(line,pos)) != -1) {
                QString capture = regex1.cap(1);
                
                if (QFile::exists(m_origDir->absolutePath() + "/" + capture)) {
                    if (!line.startsWith("set output")) {
                        origFileNames << capture;
                        line = line.replace(capture, QString("%1/%2").arg(m_origDir->absolutePath()).arg(capture));
                    }
                }
                
                if (line.simplified().startsWith("set output")) {
                    line = QString("");
                }
                
                pos += regex1.matchedLength();
            }
            stream << line + "\n";
        }
        m_tempFile->close();
    
        execute(gnuplot);
    
        DocumentTemplate gpTemplate(KStandardDirs::locate("data", "cirkuit/templates/gnuplot_latex.ckt"));
        QString latexDoc = gpTemplate.insert(gnuplotOutputFile);
        
        QStringList environment = QProcess::systemEnvironment();
        // the following enviroment variable is needed to find boxdims.sty in the circuit maaros distribution
        QString dirString = QString("TEXINPUTS=.:%1:").arg(m_origDir->absolutePath());
        environment << dirString;
        
        QStringList latexArgs;
        latexArgs << QString("-jobname=%1").arg(m_tempFileInfo->baseName());
        
        Command* latexCmd = new Command("pdflatex", latexDoc, latexArgs);
        latexCmd->setWorkingDirectory(m_workingDir->absolutePath());
        latexCmd->setEnvironment(environment);
        execute(latexCmd);
        
        return convert(Pdf, out);
    }
    
    return convert(Pdf, out);
}

