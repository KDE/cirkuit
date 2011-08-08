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

#include "circuitmacrosmanager.h"

#include <QFile>

#include <KStandardDirs>
#include <KTar>
#include <KLocale>
#include <KIO/Job>
#include <KIO/NetAccess>
#include <KProcess>

#include <cirkuitsettings.h>

CircuitMacrosManager::CircuitMacrosManager(): QObject()
{

}

bool CircuitMacrosManager::checkExistence() const
{
    QStringList paths;
    paths << KStandardDirs::locateLocal("data", "cirkuit/circuit_macros/libcct.m4", true)
          << KStandardDirs::locate("data", "cirkuit/circuit_macros/libcct.m4");
    
    
    foreach(const QString& cm_path, paths) {
        if (QFile::exists(cm_path)) {
            return true;
        }
    }
    
    return false;
}

void CircuitMacrosManager::downloadLatest()
{
    KUrl origin = KUrl("http://www.ece.uwaterloo.ca/~aplevich/Circuit_macros/Circuit_macros.tar.gz");
    KUrl dest = KStandardDirs::locateLocal("data", "cirkuit/Circuit_macros.tar.gz", true);

    KIO::Job* getJob = KIO::file_copy(origin, dest, -1, KIO::Overwrite | KIO::HideProgressInfo);
    connect( getJob, SIGNAL( result( KJob * ) ), this, SLOT( unpackCircuitMacros()) );
}

void CircuitMacrosManager::unpackCircuitMacros()
{
    KTar tarfile(KStandardDirs::locateLocal("data", "cirkuit/Circuit_macros.tar.gz", true));
    tarfile.open(QIODevice::ReadOnly);
    
    const KArchiveDirectory* root = tarfile.directory();
    
    const KArchiveDirectory* mainDir = (KArchiveDirectory*) root->entry(root->entries().at(0));
    mainDir->copyTo(KStandardDirs::locateLocal("data", "cirkuit/circuit_macros/", true), true);

    configureCircuitMacros();
}

void CircuitMacrosManager::configureCircuitMacros()
{
    QString homelibFilename = KStandardDirs::locateLocal("data", "cirkuit/circuit_macros/homelib.txt", false);
    QString defineString = QString("`define(`HOMELIB_',`%1')')").arg(KStandardDirs::locateLocal("data", "cirkuit/circuit_macros/", false));

    QFile homelibFile(homelibFilename);
    if (!homelibFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }
    QTextStream out(&homelibFile);
    out << defineString << "\n";

    homelibFile.close();

    QStringList args;
    args << "homelib";
    KProcess configProcess;
    configProcess.setProgram("make", args);
    configProcess.setWorkingDirectory(KStandardDirs::locateLocal("data", "cirkuit/circuit_macros/"));
    configProcess.startDetached();

    QFile::remove(KStandardDirs::locateLocal("data", "cirkuit/Circuit_macros.tar.gz", false));
    kDebug() << "Circuit macros configured";
    emit(configured());
}

QString CircuitMacrosManager::installedVersion() const
{
    if (!checkExistence()) {
        return "";
    }
    
    QString filename = KStandardDirs::locateLocal("data", "cirkuit/circuit_macros/README", false);
    return findVersion(filename);
}

void CircuitMacrosManager::checkOnlineVersion()
{
    KUrl origin = KUrl("http://www.ece.uwaterloo.ca/~aplevich/Circuit_macros/README");
    KUrl dest = KStandardDirs::locateLocal("tmp", "cirkuit/README", true);

    KIO::Job* getJob = KIO::file_copy(origin, dest, -1, KIO::Overwrite | KIO::HideProgressInfo);
    connect( getJob, SIGNAL( result( KJob * ) ), this, SLOT( readVersion()) );
}

void CircuitMacrosManager::readVersion()
{     
    QString onlineVersion = findVersion(KStandardDirs::locateLocal("tmp", "cirkuit/README", false));
    QString installVersion = installedVersion();
    kDebug() << "ONLINE version: " << onlineVersion;
    kDebug() << "INSTALLED version: " << installVersion;

    if (onlineVersion > installVersion) {
        emit newVersionAvailable(onlineVersion);
    }
}

QString CircuitMacrosManager::findVersion(const QString& filename) const
{
    QFile file(filename);
    if (!file.open(QFile::ReadOnly)) {
        return "";
    }
    
    QByteArray byteArray = file.readAll();
    
    QRegExp rx("Version (\\d\\.\\d+)");
    QString version = "";

    QString content(byteArray);

    if (content.contains(rx)) {
        version = rx.cap(1);
    }

    return version;
}

