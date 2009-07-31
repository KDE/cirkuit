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

#include "circuitmacrosbuilder.h"
#include "latexprocess.h"
#include "externalprocess.h"

#include <KTextEditor/Document>
#include <KStandardDirs>
#include <KTemporaryFile>
#include <QFileInfo>
#include <QTextStream>
#include <QDir>

CircuitMacrosBuilder::CircuitMacrosBuilder(KTextEditor::Document* doc, const QString& origDir, QObject* parent): GraphicsBuilder(doc, origDir, parent)
{
	m_tempFile = new KTemporaryFile;
	m_tempFile->setPrefix(m_workingDir->absolutePath() + "/");
	m_tempFile->setSuffix(".m4");
	
	m_tempFile->open();
	m_tempFileInfo = new QFileInfo(m_tempFile->fileName());
}

CircuitMacrosBuilder::~CircuitMacrosBuilder()
{
	delete m_tempFile;
	delete m_tempFileInfo;
}

bool CircuitMacrosBuilder::generateFormat(const QString& extension)
{
	if (extension == "pdf")
	{
		if (!generateDvi())
			return false;
		if (!generateEps())
			return false;
		if (!generatePdf())
			return false;
	}
	else if (extension.contains("eps"))
	{
		if (!generateDvi())
			return false;
		if (!generateEps())
			return false;
	}
	else if (extension == "dvi")
	{
		return generateDvi();
	}
	else if (extension == "png")
	{
		if (!generateDvi())
			return false;
		if (!generateEps())
			return false;
		if (!generatePdf())
			return false;
		if (!generatePng())
			return false;
	}
	else if (extension == "svg")
	{
		if (!generateDvi())
			return false;
		if (!generateEps())
			return false;
		if (!generatePdf())
			return false;
		if (!generateSvg())
			return false;
	}
	else
		return false;
	
	return true;
}

bool CircuitMacrosBuilder::generateDvi()
{
	qDebug() << "Generating DVI...";
	QTextStream out(m_tempFile);
	out << m_doc->text();
	m_tempFile->close();
	
	QStringList env = QProcess::systemEnvironment();
	env 	<< QString("M4PATH=%1:%2").arg(KStandardDirs::locateLocal("data", "cirkuit/circuit_macros/", false)).arg(m_origDir);
	
	ExternalProcess m4proc("m4");
	QStringList m4args;
	m4args << KStandardDirs::locateLocal("data", "cirkuit/circuit_macros/libcct.m4", false)
	<< KStandardDirs::locateLocal("data", "cirkuit/circuit_macros/pstricks.m4", false)
	<< m_tempFileInfo->fileName();
	
	m4proc.setEnvironment(env);
	if (!m4proc.startWith("", m4args))
		emit applicationError(m4proc.appName(), m4proc.readAllStandardError());
	
	QString m4out = m4proc.readAllStandardOutput();
	
	ExternalProcess picproc("dpic");
	QStringList picargs;
	picargs << "-p";
	
	if (!picproc.startWith(m4out, picargs))
		emit applicationError(picproc.appName(), picproc.readAllStandardError());
	QString picout = picproc.readAllStandardOutput();
	
	LatexProcess latexProcess(m_tempFileInfo->baseName());
	//QString latexDoc = QString("\\documentclass{article}\n\\begin{document}\n%1\n\\end{document}\n").arg("Hello");
	QString latexDoc = "\\documentclass{article}\n\\usepackage{pstricks,pst-eps,boxdims,graphicx,ifpdf,pst-grad,amsmath}\n"
	"\\pagestyle{empty}\n"
	"\\thispagestyle{empty}\n"
	"\\begin{document}\n"
	"\\newbox\\graph\n"
	"\\begin{TeXtoEPS}\n" +
	picout +
	"\\box\n"
	"\\graph\n"
	"\\end{TeXtoEPS}\n"
	"\\end{document}\n";
	
	return latexProcess.build(latexDoc);
}


