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

#include "latexbuilder.h"

#include <KTextEditor/Document>
#include <KStandardDirs>
#include <QProcess>
#include <QDebug>

LatexBuilder::LatexBuilder(QObject* parent): QObject(parent)
{
	m_latexProcess = new QProcess(this);
	m_latexProcess->setWorkingDirectory(KStandardDirs::locateLocal("data", "cirkuit/build/", false));
}

bool LatexBuilder::buildDoc(KTextEditor::Document* doc)
{
	QString text = doc->text();
	
	m_latexProcess->start("latex");
	
	if (!m_latexProcess->waitForStarted())
		return false;
	
	m_latexProcess->write(text.toLatin1());
	m_latexProcess->closeWriteChannel();
	
	if (!m_latexProcess->waitForFinished())
		return false;
	
	m_latexOutput = m_latexProcess->readAllStandardOutput();
	
	qDebug() << m_latexOutput;
}
