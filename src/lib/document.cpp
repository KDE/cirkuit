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

#include "document.h"
#include "backend.h"

using namespace Cirkuit;

class Cirkuit::DocumentPrivate {
public:
    DocumentPrivate() {
        directory.clear();
        settings = new DocumentSettings;
    }
    QString directory;
    DocumentSettings* settings;
};

Cirkuit::EditorDocument::EditorDocument(QObject* parent): KTextEditor::Document(parent)
{
}

EditorDocument::~EditorDocument()
{
    delete d;
}

QString EditorDocument::directory() const
{
    return url().directory();
}

int EditorDocument::initialLineNumber() const
{
    return d->settings->initialLineNumber;
}

QString EditorDocument::initialText() const
{
    return d->settings->initialText;
}

void EditorDocument::initialize()
{
    d = new DocumentPrivate;
}

void EditorDocument::applySettings(DocumentSettings* settings)
{
    d->settings = settings;
}

Cirkuit::Document* EditorDocument::document() const
{
    return new Cirkuit::Document(text(), directory());
}

Document::Document(const QString& text, const QString& directory): m_text(text), m_directory(directory), QObject()
{
    
}

Document::Document(EditorDocument* doc): m_text(doc->text()), m_directory(doc->directory()), QObject()
{

}

QString Document::text() const
{
    return m_text;
}

QString Document::directory() const
{
    return m_directory;
}
