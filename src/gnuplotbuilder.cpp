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
#include <KTextEditor/Document>
#include <QRegExp>
#include <QFile>

GnuplotBuilder::GnuplotBuilder(KTextEditor::Document* doc, const QString& origDir, QObject* parent): GraphicsBuilder(doc, origDir, parent)
{

}

bool GnuplotBuilder::generateFormat(const QString& extension)
{
	if (extension == "pdf")
		return generateDvi();
	
	return generateDvi();
}

bool GnuplotBuilder::generateDvi()
{
	ExternalProcess gnuplot("gnuplot");
	QStringList gnuplot_args;
	
	QRegExp regex1("[\'\"]([\\w\\./\\-]+)[\'\"]");
	
	QStringList origFileNames;
	QStringList lines = m_doc->text().split("\n");
	foreach (QString line, lines)
	{
		int pos = 0;
		while ((pos = regex1.indexIn(line,pos)) != -1)
		{
			QString capture = regex1.cap(1);
			
			if (QFile::exists(m_origDir + "/" + capture))
				origFileNames << capture;
			pos += regex1.matchedLength();
		}
	}
	
	qDebug() << origFileNames;
	QString gnuplot_input = m_doc->text();
	
	foreach (QString fileName, origFileNames)
		gnuplot_input = gnuplot_input.replace(fileName, QString("builddir/%1").arg(fileName));
	
		
	//qDebug() << gnuplot_input;
// 	if (!gnuplot.startWith(m_doc->text(), gnuplot_args))
// 		emit applicationError(gnuplot.appName(), gnuplot.readAllStandardError());
	
	QString gnuplot_out = gnuplot.readAllStandardOutput();
}


