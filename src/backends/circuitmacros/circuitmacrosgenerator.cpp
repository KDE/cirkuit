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

#include "circuitmacrosgenerator.h"

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

CircuitMacrosGenerator::CircuitMacrosGenerator(Cirkuit::Backend* backend, QObject* parent): Generator(backend, parent)
{
    createTempFiles(".m4");
}

CircuitMacrosGenerator::~CircuitMacrosGenerator()
{

}

bool CircuitMacrosGenerator::convert(const Cirkuit::Format& in, const Cirkuit::Format& out)
{
      // Check if the conversion can be handled by the super-class
    bool done = Cirkuit::Generator::convert(in, out);
    if (done) {
        return true;
    }
    
    kDebug() << "Inside the CircuitMacros generator...";
    
    if (in == Format::Source) {
        tempFile()->open();
        QTextStream tmpStream(tempFile());
        tmpStream << document()->text();
        tempFile()->close();    
        
        QStringList env = KProcess::systemEnvironment();
        env << QString("M4PATH=%1:%2").arg(KStandardDirs::locate("data", "cirkuit/circuit_macros/")).arg(QDir(document()->directory()).absolutePath());
                
        QStringList m4args;
        if (CircuitMacrosSettings::picInterpreter() == CircuitMacrosSettings::EnumPicInterpreter::dpic_ps) {
            m4args << KStandardDirs::locate("data", "cirkuit/circuit_macros/pstricks.m4");
        } else if (CircuitMacrosSettings::picInterpreter() == CircuitMacrosSettings::EnumPicInterpreter::dpic_pgf) {
            m4args << KStandardDirs::locate("data", "cirkuit/circuit_macros/pgf.m4");
        } else if (CircuitMacrosSettings::picInterpreter() == CircuitMacrosSettings::EnumPicInterpreter::gpic) {
            m4args << KStandardDirs::locate("data", "cirkuit/circuit_macros/gpic.m4");
        }
        m4args << KStandardDirs::locate("data", "cirkuit/circuit_macros/libcct.m4")
               << tempFileInfo()->fileName();

        Command* m4command = new Command("m4", "", m4args);
        m4command->setEnvironment(env);
        m4command->setWorkingDirectory(workingDir().path());
        if (!execute(m4command)) return false;
        
        QString m4out = m4command->stdOutput();
        
        Command* picCommand;
        if (CircuitMacrosSettings::picInterpreter() == CircuitMacrosSettings::EnumPicInterpreter::dpic_ps) {
            QStringList picargs;
            picargs << "-p";
            
            picCommand = new Command("dpic", m4out, picargs);
        } else if (CircuitMacrosSettings::picInterpreter() == CircuitMacrosSettings::EnumPicInterpreter::dpic_pgf) {
            QStringList picargs;
            picargs << "-g";
            
            picCommand = new Command("dpic", m4out, picargs);
        } else {
            QStringList picargs;
            picargs << "-t";
            
            picCommand = new Command("pic", m4out, picargs);
        }       
        if (!execute(picCommand)) return false;
            
        QString picout = picCommand->stdOutput();
        
        // if the desired output is the TeX source, dump it 
        if (out == Format::Tex) {
            QFile fileout(formatPath(Format::Tex));
            fileout.open(QFile::WriteOnly);
            QTextStream stream(&fileout);
            stream << picout;
            fileout.close();
            return true;
        }
        
        QStringList environment = QProcess::systemEnvironment();
        // the following enviroment variable is needed to find boxdims.sty in the circuit maaros distribution
        QString dirString = QString("TEXINPUTS=.:%1:%2:").arg(KStandardDirs::locate("data", "cirkuit/circuit_macros/")).arg(QDir(document()->directory()).absolutePath());
        environment << dirString;
        
        QStringList latexArgs;
        latexArgs << QString("-jobname=%1").arg(tempFileInfo()->baseName());
       
        QString latexDoc;        
        Command* latexCmd;
        if (CircuitMacrosSettings::picInterpreter() == CircuitMacrosSettings::EnumPicInterpreter::dpic_pgf) {
            DocumentTemplate latexTemplate(CircuitMacrosSettings::cmtikztemplateurl().path());
            latexDoc = latexTemplate.insert(picout);
            latexCmd = new Command("pdflatex", latexDoc, latexArgs);
        } else {
            DocumentTemplate latexTemplate(CircuitMacrosSettings::cmtemplateurl().path());
            latexDoc = latexTemplate.insert(picout);
            latexCmd = new Command("latex", latexDoc, latexArgs);
        }              
        latexCmd->setWorkingDirectory(workingDir().path());
        latexCmd->setEnvironment(environment);
        if (!execute(latexCmd)) return false;
    
        // Now that a DVI has been generated, convert it to the
        // desired output format
        
        if (CircuitMacrosSettings::picInterpreter() == CircuitMacrosSettings::EnumPicInterpreter::dpic_pgf) {        
            Generator::convert(Format::Pdf, out);
        } else {
            Generator::convert(Format::Dvi, out);
        }
    }
    
    return false;
}
