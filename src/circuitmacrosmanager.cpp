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

#include <QStandardPaths>
#include <KTar>
#include <KIO/FileCopyJob>
//#include <KNS3/DownloadDialog>
//#include <KNS3/UploadDialog>
#include <QProcess>
#include <QDebug>
#include <cirkuitsettings.h>
#include <QDir>

CircuitMacrosManager::CircuitMacrosManager(): QObject()
{

}

bool CircuitMacrosManager::checkExistence() const
{
    QStringList paths;

    paths << QStandardPaths::locate(QStandardPaths::GenericDataLocation, "cirkuit/circuit_macros", QStandardPaths::LocateDirectory)
          << QStandardPaths::locateAll(QStandardPaths::GenericDataLocation, "cirkuit/circuit_macros/libcct.m4", QStandardPaths::LocateFile);
    
    
    foreach(const QString& cm_path, paths) {
        if (QFile::exists(cm_path)) {
            return true;
        }
    }
    
    return false;
}

void CircuitMacrosManager::downloadLatest()
{
    QUrl origin = QUrl("http://www.ece.uwaterloo.ca/~aplevich/Circuit_macros/Circuit_macros.tar.gz");
    QString DestDir  = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + "/cirkuit";
    QDir dir(DestDir);
    if (!dir.exists()) {dir.mkpath(".");}
    qDebug() << "Cirkuit macros will be saved in " << DestDir;
    QUrl dest = QUrl::fromLocalFile(DestDir+"/Circuit_macros.tar.gz");
    KIO::Job* getJob = KIO::file_copy(origin, dest, -1, KIO::Overwrite | KIO::HideProgressInfo);
    connect( getJob, SIGNAL(result(KJob*)), this, SLOT(unpackCircuitMacros()) );
}

void CircuitMacrosManager::unpackCircuitMacros()
{
    qDebug () << QStandardPaths::locate(QStandardPaths::GenericDataLocation, "cirkuit/Circuit_macros.tar.gz", QStandardPaths::LocateFile);
    KTar tarfile(QStandardPaths::locate(QStandardPaths::GenericDataLocation, "cirkuit/Circuit_macros.tar.gz", QStandardPaths::LocateFile));
    bool ok = tarfile.open(QIODevice::ReadOnly);
    if (!ok) {qDebug() << "Error: Circuit_macros.tar.gz not present !!";}

    QString DestDir  = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + "/cirkuit/circuit_macros";
    QDir dir(DestDir);
    if (!dir.exists()) {dir.mkpath(".");}
    qDebug() << DestDir;
    const KArchiveDirectory* root = tarfile.directory();
    const KArchiveDirectory* mainDir = (KArchiveDirectory*) root->entry(root->entries().at(0));
    mainDir->copyTo( DestDir, true);
    configureCircuitMacros();
}

void CircuitMacrosManager::configureCircuitMacros()
{
    qDebug() << "Configuring macros ...";
    QString homelibLocation = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + "/cirkuit/circuit_macros";
    QDir dir(homelibLocation);
    if (!dir.exists()) {dir.mkpath(".");}

    // code below from vs 0.4.3 for creating file homelib.txt in circuit_macros directory now seems to be unnecessary
 /*
    QFile homelibFile(homelibLocation+"/homelib.txt");
    if (!homelibFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }

    QString defineString = QString("`define(`HOMELIB_',`%1')')").arg(homelibLocation);
    QTextStream out(&homelibFile);
    out << defineString << "\n";
    homelibFile.close();

    QStringList args;
    args << "homelib";

    QProcess configProcess;
    configProcess.setWorkingDirectory(QStandardPaths::locate(QStandardPaths::GenericDataLocation, "cirkuit/circuit_macros/",
                                      QStandardPaths::LocateDirectory));
    configProcess.startDetached("make", args);
*/
    QFile::remove(QStandardPaths::locate(QStandardPaths::GenericDataLocation, QString("cirkuit/Circuit_macros.tar.gz"), QStandardPaths::LocateFile));
    qDebug() << "Circuit macros configured";
    emit(configured());
}

QString CircuitMacrosManager::installedVersion() const
{
    if (!checkExistence()) {
        return "";
    }
    
    QString filename = QStandardPaths::locate(QStandardPaths::GenericDataLocation, QString("cirkuit/circuit_macros/README"), QStandardPaths::LocateFile);
    return findVersion(filename);
}

void CircuitMacrosManager::checkOnlineVersion()
{
    QString origin = QString("http://www.ece.uwaterloo.ca/~aplevich/Circuit_macros/README");
    QString dest = QStandardPaths::locate(QStandardPaths::TempLocation, "cirkuit/README", QStandardPaths::LocateFile);

    KIO::Job* getJob = KIO::file_copy(QUrl(origin), QUrl(dest), -1, KIO::Overwrite | KIO::HideProgressInfo);
    connect( getJob, SIGNAL(result(KJob*)), this, SLOT(readVersion()) );
}

void CircuitMacrosManager::readVersion()
{     
    QString onlineVersion = findVersion(QStandardPaths::locate(QStandardPaths::TempLocation, QString("cirkuit/README"), QStandardPaths::LocateFile));
    QString installVersion = installedVersion();
    qDebug() << "ONLINE version: " << onlineVersion;
    qDebug() << "INSTALLED version: " << installVersion;

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

