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
		GraphicsBuilder(QObject* parent = 0);
		
		virtual void build(KTextEditor::Document* doc, const QString& origDir="") = 0;
		bool fileExists(const QString& extension);
		
		virtual QString generatedPath(const QString& extension) const;
		
	signals:
		void applicationError(const QString&, const QString&);
				
	protected:
		KTemporaryFile* tempFile;
		QFileInfo* tempFileInfo;
		
		QDir* workingDir;
};

#endif // GRAPHICSBUILDER_H
