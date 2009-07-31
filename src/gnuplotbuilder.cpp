/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/
#include "gnuplotbuilder.h"
#include "externalprocess.h"
#include "latexprocess.h"

#include <KTextEditor/Document>
#include <KTemporaryFile>
#include <QRegExp>
#include <QFile>
#include <QFileInfo>
#include <QDir>

GnuplotBuilder::GnuplotBuilder(KTextEditor::Document* doc, const QString& origDir, QObject* parent): GraphicsBuilder(doc, origDir, parent)
{
	m_tempFile = new KTemporaryFile;
	m_tempFile->setPrefix(m_workingDir->absolutePath() + "/");
	m_tempFile->setSuffix(".gp");
	
	m_tempFile->open();
	m_tempFileInfo = new QFileInfo(m_tempFile->fileName());
}

GnuplotBuilder::~GnuplotBuilder()
{
	delete m_tempFile;
	delete m_tempFileInfo;
}

bool GnuplotBuilder::generateFormat(const QString& extension)
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

bool GnuplotBuilder::generateDvi()
{
	QTextStream out(m_tempFile);
		
	ExternalProcess gnuplot("gnuplot");
	QStringList gnuplot_args;
	gnuplot_args << m_tempFileInfo->fileName();
	
	QRegExp regex1("[\'\"]([\\w\\./\\-]+)[\'\"]");
	
	QStringList origFileNames;
	QStringList lines = m_doc->text().split("\n");
	
	QString gnuplot_outputfile;
	foreach (QString line, lines)
	{
		int pos = 0;
		while ((pos = regex1.indexIn(line,pos)) != -1)
		{
			QString capture = regex1.cap(1);
			
			if (QFile::exists(m_origDir + "/" + capture))
			{
				if (!line.startsWith("set output"))
				{
					origFileNames << capture;
					line = line.replace(capture, QString("%1/%2").arg(m_origDir).arg(capture));
				}
				else
					gnuplot_outputfile = capture;
			}
			pos += regex1.matchedLength();
		}
		out << line + "\n";
	}
	m_tempFile->close();
	
	qDebug() << origFileNames;			
	qDebug() << gnuplot_outputfile;

	if (!gnuplot.startWith("", gnuplot_args))
 		emit applicationError(gnuplot.appName(), gnuplot.readAllStandardError());
	
	QString gnuplot_out = gnuplot.readAllStandardOutput();
	
	LatexProcess latexProcess(m_tempFileInfo->baseName());
	//QString latexDoc = QString("\\documentclass{article}\n\\begin{document}\n%1\n\\end{document}\n").arg("Hello");
	QString latexDoc = "\\documentclass{article}\n"
	"\\usepackage{graphicx}\n"
	"\\pagestyle{empty}\n"
	"\\thispagestyle{empty}\n"
	"\\begin{document}\n"
	"\\newbox\\graph\n"
	"\\input " + gnuplot_outputfile + "\n"
	"\\box\n"
	"\\graph\n"
	"\\end{document}\n";
	
	return latexProcess.build(latexDoc);
}




