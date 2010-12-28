/*
    Copyright (C) 2009  Matteo Agostinelli <agostinelli@gmail.com>

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

#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "cirkuit_export.h"

#include <KTextEditor/Document>

namespace Cirkuit
{
class Backend;    
class DocumentPrivate;

class CIRKUIT_EXPORT Document : public KTextEditor::Document
{
    Q_OBJECT
public:
    explicit Document(QObject* parent = 0);
    virtual ~Document();
    
    QString initialText() const;
    int initialLineNumber() const;
    QString directory() const;
    
public slots:
    void setDirectory(const QString& directory);
    
protected:
    DocumentPrivate* d;
};

}
#endif // DOCUMENT_H
