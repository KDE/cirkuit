/*
    <one line to give the library's name and an idea of what it does.>
    Copyright (C) 2011  Matteo Agostinelli <matteo.agostinelli@aau.at>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include <KDebug>

#include "asymptotegenerator.h"
#include "document.h"
#include "command.h"

#include <QFileInfo>
#include <KTemporaryFile>
using namespace Cirkuit;

AsymptoteGenerator::AsymptoteGenerator(Cirkuit::Backend* backend, QObject* parent): Generator(backend, parent)
{

}

bool AsymptoteGenerator::convert(const Cirkuit::Format& in, const Cirkuit::Format& out)
{
    // Check if the conversion can be handled by the super-class
    bool done = Generator::convert(in, out);
    if (done) return true;
    
    kDebug() << "Inside the Asymptote backend...";
    
    if (in == Format::Source) {
        QTextStream stream(tempFile());
        
        QString asyOutputFile = tempFileInfo()->baseName() + ".pdf";
        
        QStringList args;
        args << "-f" << "pdf" << "-o" << asyOutputFile << tempFileInfo()->fileName();
        Command* asycmd = new Command("asy", QString(), args);
        
        stream << document()->text();
        tempFile()->close();
        
        if (!execute(asycmd)) return false;
        
        if (out == Format::Pdf) {
            return true;
        } else {
            return Generator::convert(Format::Pdf, out);
        }
    }
    
    return false;
}

