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

#include "graphicsdocument.h"

GraphicsDocument::GraphicsDocument(QObject* parent): Document(parent)
{

}


CircuitMacrosDocument::CircuitMacrosDocument(QObject* parent): QObject(parent)
{

}

QString CircuitMacrosDocument::initialize()
{
	return ".PS\ncct_init\n\n\n\n.PE";	
}

TikzDocument::TikzDocument(QObject* parent): QObject(parent)
{

}

QString TikzDocument::initialize()
{
	return "\\begin{tikzpicture}\n\n\\end{tikzpicture}";
}


