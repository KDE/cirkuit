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

#ifndef GRAPHICSDOCUMENT_H
#define GRAPHICSDOCUMENT_H

#include <KTextEditor/Document>

class GraphicsDocument : public KTextEditor::Document
{
	public:
		GraphicsDocument(QObject* parent = 0);
};

class CircuitMacrosDocument: public QObject
{
	public:
		CircuitMacrosDocument(QObject* parent = 0);
		
	public slots:
		static QString initialize();
};

class TikzDocument: public QObject
{
	public:
		TikzDocument(QObject* parent = 0);
		
	public slots:
		static QString initialize();
};

class GnuplotDocument: public QObject
{
	public:
		GnuplotDocument(QObject* parent = 0);
		
	public slots:
		static QString initialize();
};

#endif // GRAPHICSDOCUMENT_H
