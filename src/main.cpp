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

#include <QApplication>
#include <KAboutData>
#include <QCommandLineParser>
#include <KLocalizedString>
#include "cirkuitconfig.h"
#include "mainwindow.h"
#include <QDebug>
#include <QCoreApplication>

int main (int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setApplicationName("Cirkuit");
    QApplication::setApplicationVersion(VERSION);
    KLocalizedString::setApplicationDomain("cirkuit");

    // For internationalisation look at doc.qt.io.qt-5/internationalisation.html
    QString a1 = i18n("An application to generate publication-ready figures. It is a KDE frontend for Circuit Macros by J. D. Aplevich, TikZ and Gnuplot.");
    QString a2 = i18n("Visit the <a href=http://www.ece.uwaterloo.ca/~aplevich/Circuit_macros>Circuit Macros</a> and <a href=http://www.texample.net/tikz>TikZ</a> websites for further information.");

    KAboutData aboutData ( I18N_NOOP("cirkuit"),
                                i18n("Cirkuit"),
                                QString(VERSION),
                                QString(a1),
                                KAboutLicense::GPL,
                                QString(a2),
                                i18n("(c) 2011 Matteo Agostinelli)"),
                                QString("https://wwwu.uni-klu.ac.at/magostin/cirkuit.html") );

   aboutData.addAuthor(QString("Matteo Agostinelli"),
                       i18n("Main author"),
                       QString(""),
                       QString("https://wwwu.uni-klu.ac.at/magostin/cirkuit.html"),
                       QString(""));

    KAboutData::setApplicationData(aboutData);
    QCommandLineParser parser;
  //  parser.addOptions( "+[file]", ki18n("Document to open") );
    parser.process(app);

    const QStringList args = parser.positionalArguments();

   // QApplication app;

    MainWindow* window = new MainWindow();
    window->show();

    if (args.size()) {
        window->loadFile( args.first() );    
}
    return app.exec();
}
