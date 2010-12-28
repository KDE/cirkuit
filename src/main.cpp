/***************************************************************************
*   Copyright (C) 2010 by Matteo Agostinelli                              *
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

#include <KApplication>
#include <KAboutData>
#include <KCmdLineArgs>

#include "mainwindow.h"

int main (int argc, char *argv[])
{
    KAboutData aboutData( "cirkuit", "cirkuit", ki18n("Cirkuit"), "0.4-dev", ki18n("An application to generate publication-ready figures. It is a KDE frontend for Circuit Macros by J. D. Aplevich, TikZ and Gnuplot. <p>Visit the <a href=http://www.ece.uwaterloo.ca/~aplevich/Circuit_macros>Circuit Macros</a> and <a href=http://www.texample.net/tikz>TikZ</a> websites for further information."), KAboutData::License_GPL, ki18n("(c) 2010 Matteo Agostinelli"));
    aboutData.addAuthor(ki18n("Matteo Agostinelli"), ki18n("Maintainer"), "matteo@agostinelli.me", "http://agostinelli.me");
    aboutData.setHomepage("http://projects.kde.org/cirkuit");
    KCmdLineArgs::init( argc, argv, &aboutData );

    KCmdLineOptions options;
    options.add("+[file]", ki18n("Document to open"));
    KCmdLineArgs::addCmdLineOptions( options );

    KApplication app;
    MainWindow* window = new MainWindow();

    KCmdLineArgs *args = KCmdLineArgs::parsedArgs();
    if (args->count()) {
        window->loadFile(args->url(0).url());
    }

    window->show();

    return app.exec();
}
