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
        directory = QString();
        settings = new DocumentSettings;
    }
    QString directory;
    DocumentSettings* settings;
};

Cirkuit::Document::Document(QObject* parent): KTextEditor::Document(parent)
{
}

Document::~Document()
{
    delete d;
}

QString Document::directory() const
{
    return url().directory();
}

int Document::initialLineNumber() const
{
    return d->settings->initialLineNumber;
}

QString Document::initialText() const
{
    return d->settings->initialText;
}

void Document::initialize()
{
    d = new DocumentPrivate;
}

void Document::applySettings(DocumentSettings* settings)
{
    d->settings = settings;
}

