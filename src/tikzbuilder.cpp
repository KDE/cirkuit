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

TikzBuilder::TikzBuilder(QObject* parent): GraphicsBuilder(parent)
{
	
}

void TikzBuilder::build(KTextEditor::Document* doc, const QString& origDir)
{
	tempFile = new KTemporaryFile;
	tempFile->setPrefix(workingDir->absolutePath());
	tempFile->setSuffix("");
	
	tempFile->open();
	tempFileInfo = new QFileInfo(tempFile->fileName());
	
	LatexProcess latexProcess(tempFileInfo->baseName(), "pdflatex");
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
	doc->text() +
	"\n\\end{document}\n";
	latexProcess.build(latexDoc);
	
	delete tempFile;
}

