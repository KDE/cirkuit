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
#include <iostream>
#include <QString>

using namespace Cirkuit;

BatchRun::BatchRun(KCmdLineArgs* args):
    m_inputFile(args->url(0).toLocalFile())
{
    QFileInfo inputFileInfo(m_inputFile);
    m_inputDir = inputFileInfo.path();
    
    if (args->isSet("f")) {
        m_outputFormat = Cirkuit::Format::fromExtension(args->getOption("f"));
    } else {
        m_outputFormat = Cirkuit::Format::Pdf;
    }
    
    m_outputFile = QDir::currentPath() + "/" + inputFileInfo.baseName() + m_outputFormat.extension();
    
    if (args->isSet("o")) {
        QFileInfo outputFileInfo(args->getOption("o"));
        if (outputFileInfo.isFile()) {
            if (outputFileInfo.path().isEmpty()) {
                m_outputFile = QDir::currentPath() + "/" + outputFileInfo.fileName();
            } else {
                m_outputFile = args->getOption("o");
            }
        } else {
            m_outputFile = outputFileInfo.path() + "/" + inputFileInfo.baseName() + m_outputFormat.extension();
        }
    }
    
    go();
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
    
    if (!input.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cout << qPrintable(ki18n("Input file cannot be opened. Aborting ...").toString());
        return;
    }
    
    Cirkuit::Document* doc = new Cirkuit::Document(input.readAll(), m_inputDir);
    
    Cirkuit::Backend* backend = Backend::autoChooseBackend(doc);
    Cirkuit::Generator* gen = backend->generator();
    gen->generate(doc, m_outputFormat);

    QFile::remove(m_outputFile);
    if (!QFile::copy(gen->formatPath(m_outputFormat), m_outputFile)) {
        std::cout << qPrintable(ki18n("The output file cannot be created. Sorry ...").toString());
    }
}
