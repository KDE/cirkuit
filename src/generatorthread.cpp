/*
    Copyright (C) 2010  Matteo Agostinelli <agostinelli@gmail.com>

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

#include "backend.h"
#include "generator.h"
#include "document.h"
#include "command.h"

#include "cirkuitsettings.h"
#include "generatorthread.h"

#include <KDebug>
#include <KLocalizedString>

using namespace Cirkuit;

GeneratorThread::GeneratorThread(const Cirkuit::Format& in, const Cirkuit::Format& out, Cirkuit::Document* doc, QObject* parent): QThread(parent)
{
    m_gen = 0;
    m_backend = 0;
    setup(in, out, m_backend, doc, false);
}

void GeneratorThread::run()
{ 
    Cirkuit::Backend* bestBackend = Backend::autoChooseBackend(m_doc);
    if (CirkuitSettings::autoSelectBackend()) {
        m_backend = bestBackend;
    }
    
    if (!m_backend) {
        kError() << i18n("No backend could be selected!");
        return;
    } else {
        kDebug() << m_backend->id();
        kDebug() << m_backend->name();
        kDebug() << m_backend->description();
    }
    
    m_gen = m_backend->generator();
    
    connect(m_gen, SIGNAL(previewReady(QImage)), this, SIGNAL(previewReady(QImage)));
    connect(m_gen, SIGNAL(error(QString,QString)), this, SIGNAL(error(QString,QString)));
    connect(m_gen, SIGNAL(output(QString,QString)), this, SIGNAL(output(QString,QString)));
    connect(m_gen, SIGNAL(fail()), this, SIGNAL(fail()));
    m_gen->setDocument(m_doc);
	m_gen->setResolution(CirkuitSettings::resolutionPpm());
    m_gen->convert(m_input, m_output);   
        
    if (m_output == Format::QtImage) {
        m_gen->render();
    }
    
    if (m_saveToFile) {
        emit fileReady(m_gen->formatPath(m_output));
    }
}

GeneratorThread::~GeneratorThread()
{
    delete m_gen;
}

void GeneratorThread::setup(const Cirkuit::Format& in, const Cirkuit::Format& out, Cirkuit::Backend* backend, Cirkuit::Document* doc, bool saveToFile)
{
    m_input = in;
    m_output = out;
    m_doc = doc;
    m_saveToFile = saveToFile;
    m_backend = backend;
}

Generator* GeneratorThread::generator()
{
    return m_gen;
}

