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
    enum DocumentType {
        CircuitMacros,
        Tikz,
        Circuitikz,
        Gnuplot,
        Unknown
    };
    
    GraphicsDocument(DocumentType type = CircuitMacros, QObject* parent = 0);    
    
    QString initialText();
    int initialCursorPosition();
    
    void setType(DocumentType);
    DocumentType type() const;
    
    void identify();
    
protected:
    DocumentType m_type;
};

#endif // GRAPHICSDOCUMENT_H
