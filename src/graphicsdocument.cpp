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

GraphicsDocument::GraphicsDocument(DocumentType type, QObject* parent): Document(parent)
{
    setType(type);
}

void GraphicsDocument::setType(GraphicsDocument::DocumentType t)
{
    m_type = t;
}

GraphicsDocument::DocumentType GraphicsDocument::type() const
{
    return m_type;
}

int GraphicsDocument::initialCursorPosition()
{
    switch (m_type) {
        case CircuitMacros:
            return 3;
        case Circuitikz:
        case Tikz:
            return 1;
        case Gnuplot:
            return 1;
        case Unknown:
            return 0;
    }
    
    return 0;
}

QString GraphicsDocument::initialText()
{
    switch (m_type) {
        case CircuitMacros:
            return QString(".PS\ncct_init\n\n\n\n.PE");  
        case Circuitikz:
        case Tikz:
            return QString("\\begin{tikzpicture}\n\n\\end{tikzpicture}");
        case Gnuplot:
            return QString("set terminal lua tikz\n");
        case Unknown:
            return QString("");
    }
    
    return QString("");
}

GraphicsDocument::DocumentType GraphicsDocument::identify()
{
    QString text = this->text();
    if (text.contains(".PS") || text.contains("cct_init") || text.contains(".PE")) {
        m_type = CircuitMacros;
    } else if (text.contains("set terminal")) {
        m_type = Gnuplot;
    } else if (text.contains("circuitikz")) {
        m_type = Circuitikz;
    } else if (text.contains("\\begin{") || text.contains("tikzpicture")) {
        m_type = Tikz;
    } else {
        m_type = Unknown;
    }
    
    return m_type;
}


