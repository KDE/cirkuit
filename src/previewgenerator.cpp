/***************************************************************************
*   Copyright (C) 2009 by Matteo Agostinelli                              *
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
*   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
***************************************************************************/

#include "previewgenerator.h"
#include "tikzbuilder.h"
#include "gnuplotbuilder.h"
#include "graphicsbuilder.h"
#include "graphicsdocument.h"

#include <poppler-qt4.h>

#include <KStandardDirs>
#include <QDir>
#include <QImage>
#include <KMessageBox>
#include <KLocalizedString>

PreviewGenerator::PreviewGenerator(QObject* parent): QThread(parent)
{
    m_builder = 0;
}

void PreviewGenerator::setDocument(GraphicsDocument* doc, const QString& origDir)
{
    m_doc = doc;
    m_origDir = origDir;
}

void PreviewGenerator::run()
{ 
    delete m_builder;    
    clearTempFiles();

    switch (m_doc->identify()) {
        case GraphicsDocument::CircuitMacros:
//            m_builder = new CircuitMacrosBuilder(m_doc,m_origDir);
            break;
        case GraphicsDocument::Gnuplot:
            m_builder = new GnuplotBuilder(m_doc,m_origDir);
            break;
        case GraphicsDocument::Tikz:
            m_builder = new TikzBuilder(m_doc,m_origDir,false);
            break;
        case GraphicsDocument::Circuitikz:
            m_builder = new TikzBuilder(m_doc,m_origDir,true);
            break;
        case GraphicsDocument::Unknown:
        default:
            m_builder = 0;
            emit failed();
            break;        
    }
    
    if (m_builder) {
        connect(m_builder, SIGNAL(applicationError(const QString&, const QString&)),
                    this,  SIGNAL(applicationError(const QString&, const QString&)));
        connect(m_builder, SIGNAL(applicationMessage(const QString&, const QString&)), 
                    this,  SIGNAL(applicationMessage(const QString&, const QString&)));
        
        m_builder->generateFormat("pdf");
        generatePreview();
    }    
}

void PreviewGenerator::clearTempFiles()
{
    QDir dir(KStandardDirs::locateLocal("data", "cirkuit/build/", false));

    QStringList tempFiles = dir.entryList(QDir::Files);

    foreach (QString tempFile, tempFiles) {
        dir.remove(tempFile);
    }
    dir.rmdir(dir.canonicalPath());
}

QImage PreviewGenerator::preview()
{
    return m_image;
}

void PreviewGenerator::generatePreview()
{
    QString pdfPath = m_builder->filePath("pdf");

    Poppler::Document* document = Poppler::Document::load(pdfPath);
    if (!document || document->isLocked()) {
        delete document;
        return;
    }

    // Access page of the PDF file
    Poppler::Page* pdfPage = document->page(0);  // Document starts at page 0
    if (pdfPage == 0) {
        return;
    }

    // Generate a QImage of the rendered page
    m_image = pdfPage->renderToImage(600,600);

    delete pdfPage;
    delete document;
}