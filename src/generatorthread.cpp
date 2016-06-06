/***************************************************************************
*   Copyright (C) 2011 by Matteo Agostinelli                              *
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
#include "generatorthread.h"

#include "backend.h"
#include "generator.h"
#include "document.h"
#include "command.h"
#include "cirkuitsettings.h"
#include "renderthread.h"

#include "cirkuit_debug.h"
#include <KLocalizedString>

using namespace Cirkuit;

GeneratorThread::GeneratorThread(QObject* parent): QThread(parent)
{
    m_previewUrl.clear();
    m_backend = 0;
    m_doc = 0;
    m_scaleFactor = 1.0;
    m_render = new RenderThread;
    connect(m_render, SIGNAL(previewReady(QImage)), this, SIGNAL(previewReady(QImage)));
}

void GeneratorThread::run()
{ 
    Cirkuit::Backend* bestBackend = Backend::autoChooseBackend(m_doc);
    if (CirkuitSettings::autoSelectBackend()) {
        if (bestBackend->id() != m_backend->id()) {
            m_backend = bestBackend;
            emit backendChanged(m_backend->name());
        }
    }
    
    if (!m_backend) {
        qCCritical(CIRKUIT_DEBUG) << i18n("No backend could be selected!");
        return;
    } else {
        qCDebug(CIRKUIT_DEBUG) << m_backend->id();
        qCDebug(CIRKUIT_DEBUG) << m_backend->name();
        qCDebug(CIRKUIT_DEBUG) << m_backend->description();
    }
    
    Cirkuit::Generator* gen = m_backend->generator();
    
    connect(gen, SIGNAL(error(QString,QString)), this, SIGNAL(error(QString,QString)));
    connect(gen, SIGNAL(error(QString,QString)), this, SLOT(quit()));
    connect(gen, SIGNAL(output(QString,QString)), this, SIGNAL(output(QString,QString)));
    connect(gen, SIGNAL(fail()), this, SIGNAL(fail()));
    gen->setDocument(m_doc);
    gen->setResolution(CirkuitSettings::resolutionPpm());
    if (!gen->convert(m_input, m_output)) {
        emit fail();
        return;
    }
    
    m_previewUrl = gen->formatPath(Format::Pdf);
    emit previewUrl(m_previewUrl);
    if (m_output == Format::QtImage) {   
        m_render->generatePreview(gen->formatPath(Format::Pdf), m_scaleFactor);
    }
    
    if (m_saveToFile) {
        emit fileReady(gen->formatPath(m_output));
    }
    
    emit success();
}

GeneratorThread::~GeneratorThread()
{
    delete m_render;
}

void GeneratorThread::setScaleFactor(double scaleFactor)
{
    m_scaleFactor = scaleFactor;
}

void GeneratorThread::generate(const Cirkuit::Format& in, const Cirkuit::Format& out, Cirkuit::Backend* backend, Cirkuit::Document* doc, bool saveToFile, double scaleFactor)
{
    m_input = in;
    m_output = out;
    m_doc = doc;
    m_saveToFile = saveToFile;
    m_backend = backend;
    setScaleFactor(scaleFactor);
    start(LowPriority);
}

QString GeneratorThread::previewUrl() const
{
    return m_previewUrl;
}

