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

#include "pstricksgenerator.h"

#include "document.h"
#include "documenttemplate.h"
#include "command.h"
#include "settings.h"
#include "logparser.h"
#include "failcodes.h"
#include <QDir>

#include <QDebug>
#include <QProcess>
//#include <QTemporaryFile>
//#include <QStandardPaths>

using namespace Cirkuit;

PstricksGenerator::PstricksGenerator(Backend* backend, QObject* parent): Generator(backend, parent)
{

}

PstricksGenerator::~PstricksGenerator()
{

}

int PstricksGenerator::convert(const Cirkuit::Format& in, const Cirkuit::Format& out)
{

    // Check if the conversion can be handled by the super-class
    int fail = Cirkuit::Generator::convert(in, out);
    if (fail==NoFail) return NoFail;
    if (fail != Fail_unimplemented_conversion) return fail;

    qDebug() << "Inside the PsTricks backend...";

    if (in == Format::Source) {
        DocumentTemplate pstTemplate(PstricksSettings::templateurl().path());
        QString latexDoc = pstTemplate.insert(document()->text());
        
        if (out == Format::Tex) {
            QFile fileout(formatPath(Format::Tex));
            fileout.open(QFile::WriteOnly);
            QTextStream stream(&fileout);
            stream << document()->text();
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
        foreach (const QString& arg, PstricksSettings::latexargs()) {
            latexArgs << arg;
        }
        latexArgs << QString("-jobname=%1").arg(tempFileInfo()->baseName());

        Command* latexCmd = new Command("latex", latexDoc, latexArgs);
        latexCmd->setWorkingDirectory(getWorkingDir());
        latexCmd->setEnvironment(environment);
        latexCmd->setLogParser(new LatexLogParser);
        if (!execute(latexCmd)) return Fail_LateXExec;
        // check we have the dvi file in temp directory.
        if (!QFileInfo(formatPath(Format::Dvi)).exists()) return Fail_LateXNoOutput;
        return convert(Format::Dvi, out);
    }
    
    return NoFail; // Nothing to be done
}
