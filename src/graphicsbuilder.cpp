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

#include "graphicsbuilder.h"
#include <KStandardDirs>
#include <QDir>

GraphicsBuilder::GraphicsBuilder(QObject* parent): QObject(parent), tempFileInfo(0)
{
	tempFile = 0;
	
	workingDir = new QDir(KStandardDirs::locateLocal("data", "cirkuit/build/", true));
}


bool GraphicsBuilder::fileExists(const QString& extension)
{
	if (tempFileInfo == 0)
		return false;
	
	return workingDir->exists(tempFileInfo->baseName() + extension);
}

QString GraphicsBuilder::generatedPath(const QString& extension) const
{
	if (tempFileInfo == 0)
		return "";
	
	return workingDir->canonicalPath() + "/" + tempFileInfo->baseName() + extension;
}