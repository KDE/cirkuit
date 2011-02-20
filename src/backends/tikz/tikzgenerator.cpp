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

#include "tikzgenerator.h"

#include "document.h"
#include "documenttemplate.h"
#include "command.h"
#include "settings.h"
#include "logparser.h"

#include <QDir>

#include <KDebug>
#include <KProcess>
#include <KTemporaryFile>
#include <KStandardDirs>

using namespace Cirkuit;

TikzGenerator::TikzGenerator(Backend* backend, QObject* parent): Generator(backend, parent)
{

}

TikzGenerator::~TikzGenerator()
{

}

bool TikzGenerator::convert(const Cirkuit::Format& in, const Cirkuit::Format& out)
{
    // Check if the conversion can be handled by the super-class
    bool done = Generator::convert(in, out);
    if (done) {
        return true;
    }
    
    kDebug() << "Inside the TikZ backend...";
    
    if (in == Format::Source) {
        DocumentTemplate tikzTemplate(TikzSettings::templateurl().path());
        QString latexDoc = tikzTemplate.insert(document()->text());
        
        if (out == Format::Tex) {
            QFile fileout(formatPath(Format::Tex));
            fileout.open(QFile::WriteOnly);
            QTextStream stream(&fileout);
            stream << document()->text();
            fileout.close();
            return true;
        }
        
        QStringList environment = QProcess::systemEnvironment();
        // the following enviroment variable is needed to find boxdims.sty in the circuit maaros distribution
        QString dirString = QString("TEXINPUTS=.:%1:").arg(QDir(document()->directory()).absolutePath());
        environment << dirString;
        
        QStringList latexArgs;
        foreach (QString arg, TikzSettings::latexargs()) {
            latexArgs << arg;
        }
        latexArgs << QString("-jobname=%1").arg(tempFileInfo()->baseName());
        
        Command* latexCmd = new Command("pdflatex", latexDoc, latexArgs);
        latexCmd->setWorkingDirectory(workingDir().path());
        latexCmd->setEnvironment(environment);
        latexCmd->setLogParser(new LatexLogParser);
        if (!execute(latexCmd)) return false;
        
        return convert(Format::Pdf, out);
    }
    
    return convert(Format::Pdf, out);
}
