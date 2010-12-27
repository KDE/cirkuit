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

#include "circuitmacrosmanager.h"

#include <KStandardDirs>
#include <KTar>
#include <KNotification>
#include <KLocale>

#include <QFile>
#include <QUrl>
#include <QDebug>
#include <QMessageBox>
#include <QProcess>
#include <QBuffer>

#include <kio/netaccess.h>
#include <cirkuitsettings.h>

CircuitMacrosManager::CircuitMacrosManager(): QObject()
{
    //progressNotify = new KNotification("Download progress");
    //progressNotify->setComponentData(KComponentData("cirkuit"));
}

bool CircuitMacrosManager::checkExistence() const
{
    QStringList paths;
    paths << KStandardDirs::locateLocal("data", "cirkuit/circuit_macros/libcct.m4", true)
          << KStandardDirs::locate("data", "cirkuit/circuit_macros/libcct.m4");
    
    
    foreach(QString cm_path, paths) {
        if (QFile::exists(cm_path)) {
            return true;
        }
    }
    
    return false;
}

void CircuitMacrosManager::downloadLatest()
{
    QString filename = KStandardDirs::locateLocal("data", "cirkuit/Circuit_macros.tar.gz", true);
      
    if( !KIO::NetAccess::download(KUrl("http://www.ece.uwaterloo.ca/~aplevich/Circuit_macros/Circuit_macros.tar.gz"), filename, 0)) {
        kDebug() << KIO::NetAccess::lastErrorString();
        return;
    }

    KTar tarfile(filename);
    tarfile.open(QIODevice::ReadOnly);
    
    const KArchiveDirectory* root = tarfile.directory();
    
    const KArchiveDirectory* mainDir = (KArchiveDirectory*) root->entry(root->entries().at(0));
    mainDir->copyTo(KStandardDirs::locateLocal("data", "cirkuit/circuit_macros/", true), true);

    configureCircuitMacros();
    
    emit(configured());
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

    foreach (QString arg, args) {
        QProcess::startDetached("make", QStringList(arg), KStandardDirs::locateLocal("data", "cirkuit/circuit_macros/", false));
    }

    QFile::remove(KStandardDirs::locateLocal("data", "cirkuit/Circuit_macros.tar.gz", false));
    qDebug() << "Circuit macros configured";
}

QString CircuitMacrosManager::installedVersion() const
{
    if (!checkExistence()) {
        return "";
    }
    QString filename = KStandardDirs::locateLocal("data", "cirkuit/circuit_macros/README", false);

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return "";
    }
    return findVersion(file.readAll());
}

void CircuitMacrosManager::checkOnlineVersion()
{
    QString filename = KStandardDirs::locateLocal("data", "cirkuit/README", true);
      
    if( !KIO::NetAccess::download(KUrl("http://www.ece.uwaterloo.ca/~aplevich/Circuit_macros/README"), filename, 0)) {
        kDebug() << KIO::NetAccess::lastErrorString();
        return;
    }
    
    QString onlineVersion = findVersion(filename);
    qDebug() << "ONLINE version: " << onlineVersion;

    if (onlineVersion > installedVersion()) {
        emit newVersionAvailable(onlineVersion);
    }
}

QString CircuitMacrosManager::findVersion(const QString& filename) const
{
    QFile file(filename);
    QByteArray byteArray = file.readAll();
    
    bool versionStringFound = false;

    QRegExp rx("Version (\\d\\.\\d+)");
    QString version = "";

    QString content(byteArray);

    if (content.contains(rx)) {
        versionStringFound = true;
        version = rx.cap(1);
    }

    return version;
}

void CircuitMacrosManager::configureIntepreter()
{
    QStringList args;
    
    if (CirkuitSettings::picInterpreter() == CirkuitSettings::EnumPicInterpreter::dpic_ps) {
        args << "psdefault";
    } else if (CirkuitSettings::picInterpreter() == CirkuitSettings::EnumPicInterpreter::dpic_pgf) {
        args << "pgfdefault";
    } else if (CirkuitSettings::picInterpreter() == CirkuitSettings::EnumPicInterpreter::gpic) {
        args << "gpicdefault";
    }

    QProcess::startDetached("make", args, KStandardDirs::locateLocal("data", "cirkuit/circuit_macros/", false));
}

