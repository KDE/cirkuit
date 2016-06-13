/***************************************************************************
*   Copyright (C) 2011 by Matteo Agostinelli                              *
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
*   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.          *
***************************************************************************/

#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "cirkuit_export.h"

#include <KTextEditor/Document>

namespace Cirkuit
{
class DocumentPrivate;

// TODO Rename file

/** 
 * A class containing the initial settings of a document. This 
 * class should be reimplemented by each backend to define 
 * appropriate initial conditions.
 * 
 * @author Matteo Agostinelli
 */
class DocumentSettings {
public:
    /**
     * Default constructor. Initial text is an empty string
     */    
    DocumentSettings() {
        initialText.clear();
        initialLineNumber = 0;
    }
    
    //! The initial text, inserted when a new document is created
    QString initialText;
    //! The line where the cursor will be placed when a new document is created
    int initialLineNumber;
};

}
#endif // DOCUMENT_H
