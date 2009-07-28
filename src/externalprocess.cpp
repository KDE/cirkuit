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
#include "externalprocess.h"

#include <stdexcept>
#include <cstdlib>
#include <KLocale>
#include <KStandardDirs>
#include <QFileInfo>
#include <QDir>
#include <QDebug>

ExternalProcess::ExternalProcess(const QString& externalApp, QObject* parent): QProcess(parent), m_appName(externalApp)
{
	if (!checkExistence(externalApp))
	{
		qDebug("PROGRAM NOT FOUND!!!!");		
	}
	
	setWorkingDirectory(KStandardDirs::locateLocal("data", "cirkuit/build/", false));
}

bool ExternalProcess::checkExistence(const QString& appname) const
{
	QString pathEnv = getenv("PATH");
	QStringList pathDirs = pathEnv.split(":");
	
	bool found = false;
	foreach (QString dir, pathDirs)
		if (checkPresenceInDir(appname, dir))
			found = true;
		
	return found;
}

bool ExternalProcess::checkPresenceInDir(const QString& appname, const QString& dirname) const
{
	QFileInfo fileinfo(QDir(dirname),appname);
	return fileinfo.exists();
}


bool ExternalProcess::startWith(const QString& input, const QStringList& args)
{	
	start(m_appName, args);
	
	if (!waitForStarted())
		return false;
	
	write(input.toLatin1());
	closeWriteChannel();
	
	if (!waitForFinished())
		return false;	
	
	return true;
}
