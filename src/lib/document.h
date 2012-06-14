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
class CIRKUIT_EXPORT Document;

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

/**
 * The Document class represent a document of the text editor. 
 * The creation of the class is managed by the Kate Part, therefore
 * the constructor should not be called directly. For the same reason
 * a separate DocumentSettings class has been added to personalize
 * the initial settings of the document, depending on the selected
 * backend.
 *
 * @author Matteo Agostinelli
 */
class CIRKUIT_EXPORT EditorDocument : public KTextEditor::Document
{
    Q_OBJECT
public:
    /** 
     * Destructor
     */
    virtual ~EditorDocument();
    
    /**
     * The initial text of the document. It is set by the 
     * DocumentSettings,
     */
    QString initialText() const;
    int initialLineNumber() const;
    QString directory() const;
    
    Cirkuit::Document* document() const;
    
public slots:
    void applySettings(DocumentSettings* settings);
    
    void initialize();
    
protected:
    explicit EditorDocument(QObject* parent = 0);
    
    DocumentPrivate* d;
};

class CIRKUIT_EXPORT Document : public QObject
{
    Q_OBJECT
    
public:
    Document(const QString& text, const QString& directory);
    Document(Cirkuit::EditorDocument* doc);
    
    QString directory() const;
    QString text() const;
    
protected:
    QString m_text, m_directory;
};

}
#endif // DOCUMENT_H
