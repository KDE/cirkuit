/***************************************************************************
*   Copyright (C) 2012 by Matteo Agostinelli                              *
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
#include "batchrun.h"
#include "backend.h"
#include "document.h"
#include "cirkuitsettings.h"
#include <generator.h>

#include <QStringList>
#include <KDebug>
#include <KApplication>
#include <KCmdLineArgs>
#include <QFile>
#include <QDir>

using namespace Cirkuit;

BatchRun::BatchRun(KCmdLineArgs* args):
    m_inputFile(args->url(0).toLocalFile())
{

}

void BatchRun::initializeBackends()
{
    kDebug() << Cirkuit::Backend::listAvailableBackends();
    m_backend = Cirkuit::Backend::getBackend(CirkuitSettings::defaultBackend());
    
    if (!m_backend) {
        kDebug() << "The default backend has not been found";
        if (Cirkuit::Backend::listAvailableBackends().count() < 1) {
            kDebug() << "No backends available...";
            return;
        } else {
            // try falling back to the first available backend
            m_backend = Cirkuit::Backend::getBackend(Cirkuit::Backend::listAvailableBackends().at(0));
            if (!m_backend) {
                // this shouldn't happen
                return;
            }
        }
    }
}

void BatchRun::go()
{
    initializeBackends();
 
    kDebug() << "INPUT: " << m_inputFile;
    QFile input(m_inputFile);
    if (!input.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    Cirkuit::Document* doc = new Cirkuit::Document(input.readAll(), m_inputFile);
    
    Cirkuit::Backend* backend = Backend::autoChooseBackend(doc);
    Cirkuit::Generator* gen = backend->generator();
    gen->generate(doc, Format::Pdf);
    
    QFileInfo inputFileInfo(m_inputFile);
    
    QFile::copy(gen->formatPath(Format::Pdf), QDir::currentPath() + "/" + inputFileInfo.baseName() + ".pdf");
}

