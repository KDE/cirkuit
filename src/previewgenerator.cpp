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
#include "circuitmacrosbuilder.h"
#include "tikzbuilder.h"
#include "graphicsbuilder.h"

#include <poppler-qt4.h>

#include <KTextEditor/Document>
#include <KStandardDirs>
#include <QDir>
#include <QImage>

PreviewGenerator::PreviewGenerator(QObject* parent): QObject(parent)
{
	m_builder = 0;
}

void PreviewGenerator::build(KTextEditor::Document* doc, const QString& origDir)
{
	if (m_builder)
	{
		delete m_builder;
		m_builder = 0;
	}
	
	clearTempFiles();
	
	if (doc->text().contains(".PS") || doc->text().contains("cct_init") || doc->text().contains(".PE"))
	{
		// this is a circuit macros document
		m_builder = new CircuitMacrosBuilder(doc,origDir);
	}
	else //if (doc->text().contains("\\begin{tikzpicture}"))
	{
		// this is a Tikz document
		m_builder = new TikzBuilder(doc,origDir);
	}
	
	if (m_builder)
	{
		connect(m_builder, SIGNAL(applicationError(const QString&, const QString&)),
							    SIGNAL(applicationError(const QString&, const QString&)));
		m_builder->generateFormat("pdf");
	}
}

void PreviewGenerator::clearTempFiles()
{
	QDir dir(KStandardDirs::locateLocal("data", "cirkuit/build/", false));
	
	QStringList tempFiles = dir.entryList(QDir::Files);
	
	foreach (QString tempFile, tempFiles)
		dir.remove(tempFile);
	
	dir.rmdir(dir.canonicalPath());
}

QImage PreviewGenerator::preview()
{
	QImage image;
	QString pdfPath = m_builder->filePath("pdf");
	
	Poppler::Document* document = Poppler::Document::load(pdfPath);
	if (!document || document->isLocked()) 
	{
		delete document;
		return image;
	}
	
	// Access page of the PDF file
	Poppler::Page* pdfPage = document->page(0);  // Document starts at page 0
	if (pdfPage == 0) 
	{
		return image;
	}
	
	// Generate a QImage of the rendered page
	image = pdfPage->renderToImage(600,600);
	
	delete pdfPage;
	delete document;
	
	return image;
}

