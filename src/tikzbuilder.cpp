/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

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

#include "tikzbuilder.h"
#include "latexprocess.h"

#include <QDir>
#include <QFileInfo>
#include <KTemporaryFile>

#include <KTextEditor/Document>

TikzBuilder::TikzBuilder(KTextEditor::Document* doc, const QString& origDir, QObject* parent): GraphicsBuilder(doc,origDir,parent)
{
	m_tempFile = new KTemporaryFile;
	m_tempFile->setPrefix(m_workingDir->absolutePath()+"/");
	m_tempFile->setSuffix("");
	
	m_tempFile->open();
	m_tempFileInfo = new QFileInfo(m_tempFile->fileName());
}

TikzBuilder::~TikzBuilder()
{
	delete m_tempFile;
	delete m_tempFileInfo;
}

bool TikzBuilder::generatePdf()
{
	LatexProcess latexProcess(m_tempFileInfo->baseName(), "pdflatex");
	//QString latexDoc = QString("\\documentclass{article}\n\\begin{document}\n%1\n\\end{document}\n").arg("Hello");
	QString latexDoc = "\\documentclass{article}\n"
	"\\usepackage{tikz,amsmath,siunitx}\n"
	"\\usetikzlibrary{arrows,snakes,backgrounds,patterns,matrix,shapes,fit,calc,shadows,plotmarks}"
	"\\usepackage[graphics,tightpage,active]{preview}\n"
	"\\usepackage[siunitx]{circuitikz}"
	"\\PreviewEnvironment{tikzpicture}"
	"\\PreviewEnvironment{equation}"
	"\\PreviewEnvironment{equation*}"
	"\\newlength{\\imagewidth}"
	"\\newlength{\\imagescale}"
	"\\pagestyle{empty}\n"
	"\\thispagestyle{empty}\n"
	"\\begin{document}\n" +
	m_doc->text() +
	"\n\\end{document}\n";
	
	return latexProcess.build(latexDoc);
}

bool TikzBuilder::generateDvi()
{
	LatexProcess latexProcess(m_tempFileInfo->baseName(), "pdflatex");
	//QString latexDoc = QString("\\documentclass{article}\n\\begin{document}\n%1\n\\end{document}\n").arg("Hello");
	QString latexDoc = "\\documentclass{article}\n"
	"\\usepackage{tikz,amsmath,siunitx}\n"
	"\\usetikzlibrary{arrows,snakes,backgrounds,patterns,matrix,shapes,fit,calc,shadows,plotmarks}"
	"\\usepackage[graphics,tightpage,active]{preview}\n"
	"\\usepackage[siunitx]{circuitikz}"
	"\\PreviewEnvironment{tikzpicture}"
	"\\PreviewEnvironment{equation}"
	"\\PreviewEnvironment{equation*}"
	"\\newlength{\\imagewidth}"
	"\\newlength{\\imagescale}"
	"\\pagestyle{empty}\n"
	"\\thispagestyle{empty}\n"
	"\\begin{document}\n" +
	m_doc->text() +
	"\n\\end{document}\n";
	
	QStringList args;
	args << "-output-format=dvi";
	return latexProcess.build(latexDoc, args);
}

bool TikzBuilder::generateFormat(const QString& extension)
{
	if (extension == "pdf")
		return generatePdf();
	else if (extension == "png")
	{
		if (!generatePdf())
			return false;
		if (!generateEps())
			return false;
		if (!generatePng())
			return false;
	}
	else if (extension.contains("eps"))
	{
		if (!generatePdf())
			return false;
		if (!generateEps())
			return false;
	}
	else if (extension == "svg")
	{
		if (!generatePdf())
			return false;
		if (!generateSvg())
			return false;
	}
	else
		return false;
	
	return true;
}

bool TikzBuilder::generateEps()
{
	qDebug() << "Generating EPS...";
	ExternalProcess epstopdfproc("pdftops");
	QStringList epstopdfargs;
	epstopdfargs << "-eps" << m_tempFileInfo->baseName()+".pdf";
	if (!epstopdfproc.startWith("", epstopdfargs))
	{
		emit applicationError(epstopdfproc.appName(), epstopdfproc.readAllStandardError());
		qDebug() << epstopdfproc.readAllStandardOutput();
		qDebug() << epstopdfproc.readAllStandardError();
		return false;
	}
	
	return true;
}


