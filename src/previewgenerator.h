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

#ifndef PREVIEWGENERATOR_H
#define PREVIEWGENERATOR_H

#include <QThread>
#include <QImage>

class GraphicsDocument;
class GraphicsBuilder;

class PreviewGenerator : public QThread
{
    Q_OBJECT
public:
    PreviewGenerator(QObject* parent = 0);
    void setDocument(GraphicsDocument* doc, const QString& origDir = "");
    void clearTempFiles();

    QImage preview();
    GraphicsBuilder* builder() const {
        return m_builder;
    }
    
    void run();
    void generatePreview();

    
signals:
    void applicationError(const QString& app, const QString& msg);
    void applicationMessage(const QString& app, const QString& msg);
    void failed();

protected:
    GraphicsBuilder* m_builder;
    GraphicsDocument* m_doc;
    QString m_origDir;
    
    QImage m_image;
};

#endif // PREVIEWGENERATOR_H
