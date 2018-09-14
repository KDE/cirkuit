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
#include "logparser.h"
#include "dpiclogparser.h"
#include "failcodes.h"

#include <QDir>

#include <QDebug>
#include <QProcess>
#include <QTemporaryFile>
#include <QStandardPaths>


using namespace Cirkuit;

CircuitMacrosGenerator::CircuitMacrosGenerator(Cirkuit::Backend* backend, QObject* parent): Generator(backend, parent)
{
    createTempFiles(".m4");
}

CircuitMacrosGenerator::~CircuitMacrosGenerator()
{

}

int CircuitMacrosGenerator::convert(const Cirkuit::Format& in, const Cirkuit::Format& out)
{
    
    // Check if the conversion can be handled by the super-class
    int fail = Cirkuit::Generator::convert(in, out);
    if (fail==NoFail) return NoFail;
    if (fail != Fail_unimplemented_conversion) return fail;

    qDebug() << "Inside the CircuitMacros generator...";

    if (in == Format::Source) {
        tempFile()->open();
        QTextStream tmpStream(tempFile());
        tmpStream << document()->text();
        tempFile()->close();    
        
        QStringList m4args;
        // Specify library directory (the circuit macros) with -I
        // Assume we have a recent m4 installed
        m4args << QString("-I") << QStandardPaths::locate(QStandardPaths::GenericDataLocation,
                                                          "cirkuit/circuit_macros",QStandardPaths::LocateDirectory);

        if (CircuitMacrosSettings::picInterpreter() == CircuitMacrosSettings::EnumPicInterpreter::dpic_ps) {
            m4args << QString("pstricks.m4");
        } else if (CircuitMacrosSettings::picInterpreter() == CircuitMacrosSettings::EnumPicInterpreter::dpic_pgf) {
            m4args << QString("pgf.m4");
        } else if (CircuitMacrosSettings::picInterpreter() == CircuitMacrosSettings::EnumPicInterpreter::gpic) {
            m4args << QString("gpic.m4");
        }
        m4args << QString("libcct.m4") << tempFileInfo()->fileName();

        Command* m4command = new Command("m4", "", m4args);
     //   m4command->setEnvironment(env);
        m4command->setWorkingDirectory(getWorkingDir()); // the working directory is searched first by m4
        if (!execute(m4command)) return Fail_m4;
        
        QString m4out = m4command->stdOutput();
        
        Command* picCommand;
        QStringList picArgs;
        if (CircuitMacrosSettings::picInterpreter() == CircuitMacrosSettings::EnumPicInterpreter::dpic_ps) {
            picArgs << "-p";        
            picCommand = new Command("dpic", m4out, picArgs);
            picCommand->setLogParser(new DpicLogParser);
            if (!execute(picCommand)) return Fail_dpic;
        } else if (CircuitMacrosSettings::picInterpreter() == CircuitMacrosSettings::EnumPicInterpreter::dpic_pgf) {
            picArgs << "-g";       
            picCommand = new Command("dpic", m4out, picArgs);
            picCommand->setLogParser(new DpicLogParser);
            if (!execute(picCommand)) return Fail_dpic;
        } else {
            picArgs << "-t";       
            picCommand = new Command("pic", m4out, picArgs);
            if (!execute(picCommand)) return Fail_pic;
        }

            
        QString picout = picCommand->stdOutput();
        
        // if the desired output is the TeX source, dump it 
        if (out == Format::Tex) {
            QFile fileout(formatPath(Format::Tex));
            fileout.open(QFile::WriteOnly);
            QTextStream stream(&fileout);
            stream << picout;
            fileout.close();
            return NoFail;
        }
        
        QStringList environment = QProcess::systemEnvironment();
        // LaTeX searches (in order) circuit_macros dir, dir that contains editor document, local dir
        // The search of circuit_macros is needed to find boxdims.sty
        QString dirString = QString("TEXINPUTS=%1:%2:.:").arg(QStandardPaths::locate(QStandardPaths::GenericDataLocation,
                               "cirkuit/circuit_macros/",QStandardPaths::LocateDirectory)).arg(QDir(document()->directory()).absolutePath());
        environment << dirString;
        
        QStringList latexArgs;
        foreach (const QString& arg, CircuitMacrosSettings::latexargs()) {
            latexArgs << arg;
        }
        latexArgs << QString("-jobname=%1").arg(tempFileInfo()->baseName());
       
        QString latexDoc;        
        Command* latexCmd;
        if (CircuitMacrosSettings::picInterpreter() == CircuitMacrosSettings::EnumPicInterpreter::dpic_pgf) {
            DocumentTemplate latexTemplate(CircuitMacrosSettings::tikztemplateurl().path());
            latexDoc = latexTemplate.insert(picout);
            latexCmd = new Command("pdflatex", latexDoc, latexArgs);
            latexCmd->setWorkingDirectory(getWorkingDir());
            latexCmd->setEnvironment(environment);
            latexCmd->setLogParser(new LatexLogParser);
            if (!execute(latexCmd)) return Fail_LateXExec;
        } else {
            DocumentTemplate latexTemplate(CircuitMacrosSettings::templateurl().path());
            latexDoc = latexTemplate.insert(picout);
            latexCmd = new Command("latex", latexDoc, latexArgs);
            latexCmd->setWorkingDirectory(getWorkingDir());
            latexCmd->setEnvironment(environment);
            latexCmd->setLogParser(new LatexLogParser);
            if (!execute(latexCmd)) Fail_PdfLateXExec;
        }              

    
        // Now that a PDF or DVI has been generated, convert it to the
        // desired output format
        
        if (CircuitMacrosSettings::picInterpreter() == CircuitMacrosSettings::EnumPicInterpreter::dpic_pgf)
        {
            if (!QFileInfo(formatPath(Format::Pdf)).exists()) // check we have the pdf file in temp directory.
            {
               return Fail_PdfLateXNoOutput;
            }
            return Generator::convert(Format::Pdf, out);
        } else
        {
            if (!QFileInfo(formatPath(Format::Dvi)).exists()) // check we have the dvi file in temp directory.
            {
               return Fail_LateXNoOutput;
            }
            return Generator::convert(Format::Dvi, out);
        }
        return NoFail;
        
    }
    
    return NoFail; // nothing to be done
}
