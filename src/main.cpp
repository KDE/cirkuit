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

#include <KAboutData>
#include <QApplication>
#include <QCommandLineParser>
#include <KLocalizedString>

#include "cirkuitconfig.h"
#include "mainwindow.h"

int main (int argc, char *argv[])
{
    QApplication app(argc, argv); // must be created first for translation to work

    /* setup localization */
    KLocalizedString::setApplicationDomain("cirkuit"); /* connect to translation catalog */

    /* setup application's about-data */
    KAboutData aboutData(QStringLiteral("cirkuit"), i18n("Cirkuit"), QStringLiteral(VERSION),
                         i18n("An application to generate publication-ready figures. "
                              "It is a KDE frontend for Circuit Macros by J. D. Aplevich, TikZ and Gnuplot."),
                         KAboutLicense::GPL, i18n("(c) 2011 Matteo Agostinelli"),
                         i18n("Visit the <a href=http://www.ece.uwaterloo.ca/~aplevich/Circuit_macros>Circuit Macros</a> and "
                              "<a href=http://www.texample.net/tikz>TikZ</a> websites for further information.")
                         );
    aboutData.addAuthor(i18n("Matteo Agostinelli"), i18n("Maintainer"),
                        QStringLiteral("matteo@agostinelli.me"), QStringLiteral("http://agostinelli.me")
                        );
    aboutData.setHomepage(QStringLiteral("http://projects.kde.org/cirkuit"));
    KAboutData::setApplicationData(aboutData); /* install data in already created QApplication instance */

    /* create KDE-typical commandline parser with optional 'file' argument */
    QCommandLineParser parser;
    aboutData.setupCommandLine(&parser); /* add description and standard options like version, author, etc. */
    parser.addPositionalArgument(QStringLiteral("file"), i18n("Document to open."), i18n("[file]")); /* add 'file' arg */

    /* parse the command line */
    parser.process(app);
    aboutData.processCommandLine(&parser); /* handle all standard KDE options */
    const QStringList args = parser.positionalArguments(); /* get all passed optional arguments */

    /* create and show the gui */
    MainWindow* window = new MainWindow();
    if (!args.isEmpty()) {
        /* 'file' argument */
        const QString fileArg = args.at(0); /* only the first one is used, others are ignored */
        window->loadFile(QUrl::fromLocalFile(fileArg)); /* open passed file and trigger preview generation */
    }
    window->show();

    return app.exec();
}
