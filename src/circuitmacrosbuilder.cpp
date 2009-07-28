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

CircuitMacrosBuilder::CircuitMacrosBuilder(QObject* parent): GraphicsBuilder(parent)
{
	
}


void CircuitMacrosBuilder::build(KTextEditor::Document* doc, const QString& origDir)
{
	tempFile = new KTemporaryFile;
	tempFile->setPrefix(workingDir->absolutePath() + "/");
	tempFile->setSuffix(".m4");
	
	tempFile->open();
	tempFileInfo = new QFileInfo(tempFile->fileName());
	
	generateDvi(doc, origDir);
	generateEps();
	generatePdf();	
	
	delete tempFile;
}

QString CircuitMacrosBuilder::generateDvi(KTextEditor::Document* doc, const QString& origDir)
{
	QTextStream out(tempFile);
	out << doc->text();
	tempFile->close();
	
	QStringList env = QProcess::systemEnvironment();
	env 	<< QString("M4PATH=%1:%2").arg(KStandardDirs::locateLocal("data", "cirkuit/circuit_macros/", false)).arg(origDir);
	
	ExternalProcess m4proc("m4");
	QStringList m4args;
	m4args << KStandardDirs::locateLocal("data", "cirkuit/circuit_macros/libcct.m4", false)
	<< KStandardDirs::locateLocal("data", "cirkuit/circuit_macros/pstricks.m4", false)
	<< tempFileInfo->fileName();
	
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
	
	LatexProcess latexProcess(tempFileInfo->baseName());
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
	latexProcess.build(latexDoc);
	
	return tempFileInfo->baseName() + ".dvi";
}

QString CircuitMacrosBuilder::generateEps()
{
	ExternalProcess dvipsproc("dvips");
	QStringList dvipsargs;
	dvipsargs << "-Ppdf" << "-G0" << "-E" << tempFileInfo->baseName()+".dvi" << "-o" << tempFileInfo->baseName()+".eps";
	if (!dvipsproc.startWith("", dvipsargs))
	{
		emit applicationError(dvipsproc.appName(), dvipsproc.readAllStandardError());
		qDebug() << dvipsproc.readAllStandardOutput();
		qDebug() << dvipsproc.readAllStandardError();
	}
	
	return tempFileInfo->baseName() + ".eps";
}

QString CircuitMacrosBuilder::generatePdf()
{
	ExternalProcess epstopdfproc("epstopdf");
	QStringList epstopdfargs;
	epstopdfargs << tempFileInfo->baseName()+".eps";
	if (!epstopdfproc.startWith("", epstopdfargs))
	{
		emit applicationError(epstopdfproc.appName(), epstopdfproc.readAllStandardError());
		qDebug() << epstopdfproc.readAllStandardOutput();
		qDebug() << epstopdfproc.readAllStandardError();
	}
	
	return tempFileInfo->baseName() + ".pdf";
}

