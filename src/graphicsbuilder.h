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
#ifndef GRAPHICSBUILDER_H
#define GRAPHICSBUILDER_H

#include <QObject>

class KTemporaryFile;
class QFileInfo;
class QDir;

namespace KTextEditor
{
class Document;
}

class GraphicsBuilder : public QObject
{
    Q_OBJECT
public:
    GraphicsBuilder(KTextEditor::Document* doc, const QString& origDir="", QObject* parent = 0);

    bool fileExists(const QString& extension) const;
    QString filePath(const QString& extension) const;

public slots:
    //virtual void build() = 0;
    virtual bool generateFormat(const QString& extension) = 0;

signals:
    void applicationError(const QString&, const QString&);
	 void applicationMessage(const QString&, const QString&);

protected slots:
    virtual bool generatePng(bool fromPdf = false);
    virtual bool generateSvg();
    virtual bool generateEps();
    virtual bool generatePdf();

protected:
    KTextEditor::Document* m_doc;
    QString m_origDir;
    KTemporaryFile* m_tempFile;
    QFileInfo* m_tempFileInfo;

    QDir* m_workingDir;
};

#endif // GRAPHICSBUILDER_H
