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

#include "graphicsbuilder.h"
#include "externalprocess.h"

#include <KStandardDirs>
#include <QDir>
#include <QDebug>

GraphicsBuilder::GraphicsBuilder(KTextEditor::Document* doc, const QString& origDir, QObject* parent): QObject(parent), m_doc(doc), m_origDir(origDir)
{
	m_tempFile = 0;
	m_tempFileInfo = 0;
	
	m_workingDir = new QDir(KStandardDirs::locateLocal("data", "cirkuit/build/", true));
}

bool GraphicsBuilder::fileExists(const QString& extension) const
{
	if (m_tempFileInfo == 0)
		return false;
	
	return m_workingDir->exists(m_tempFileInfo->baseName() + "." + extension);
}

QString GraphicsBuilder::filePath(const QString& extension) const
{
	if (fileExists(extension))
		return QString("%1/%2.%3").arg(m_workingDir->canonicalPath()).arg(m_tempFileInfo->baseName()).arg(extension);
	
	return "";
}

bool GraphicsBuilder::generatePng()
{
	qDebug() << "Generating PNG...";
	ExternalProcess epstopngproc("convert");
	QStringList epstopngargs;
	epstopngargs << "-density" << "300" << m_tempFileInfo->baseName()+".eps" << m_tempFileInfo->baseName()+".png";
	if (!epstopngproc.startWith("", epstopngargs))
	{
		emit applicationError(epstopngproc.appName(), epstopngproc.readAllStandardError());
		qDebug() << epstopngproc.readAllStandardOutput();
		qDebug() << epstopngproc.readAllStandardError();
		return false;
	}
	
	return true;
}

bool GraphicsBuilder::generateSvg()
{
	qDebug() << "Generating SVG...";
	ExternalProcess pdftosvgproc("pdf2svg");
	QStringList pdftosvgargs;
	pdftosvgargs << m_tempFileInfo->baseName()+".pdf" << m_tempFileInfo->baseName()+".svg";
	if (!pdftosvgproc.startWith("", pdftosvgargs))
	{
		emit applicationError(pdftosvgproc.appName(), pdftosvgproc.readAllStandardError());
		qDebug() << pdftosvgproc.readAllStandardOutput();
		qDebug() << pdftosvgproc.readAllStandardError();
		return false;
	}
	
	return true;
}

