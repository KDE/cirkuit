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

#include "tikzbackend.h"
#include "documenttemplate.h"
#include "command.h"
#include "cirkuitsettings.h"

#include <KStandardDirs>
#include <QProcess>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QDebug>

TikzGenerator::TikzGenerator(const QString& origDir, QObject* parent): GraphicsGenerator(origDir, parent)
{
    createTempSource(".tex");
}

bool TikzGenerator::convert(GraphicsGenerator::Format in, GraphicsGenerator::Format out)
{
    // Check if the conversion can be handled by the super-class
    bool done = GraphicsGenerator::convert(in, out);
    if (done) {
        return true;
    }
    
    qDebug() << "Inside the TikZ backend...";
    
    if (in == Source) {
        DocumentTemplate tikzTemplate(CirkuitSettings::tikztemplateurl().path());
        QString latexDoc = tikzTemplate.insert(m_source);
        
        if (out == Tex) {
            QFile fileout(filePath(Tex));
            fileout.open(QFile::WriteOnly);
            QTextStream stream(&fileout);
            stream << m_source;
            fileout.close();
            return true;
        }
        
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

