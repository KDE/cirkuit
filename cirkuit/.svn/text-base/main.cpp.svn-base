#include <KApplication>
#include <KAboutData>
#include <KCmdLineArgs>
#include <KLocalizedString>
#include <KMessageBox>
#include <QDebug>
#include "mainwindow.h"

int main (int argc, char *argv[])
{
  KAboutData aboutData( "cirkuit", "Cirkuit", ki18n("Cirkuit"), "0.1.3", ki18n("A simple KDE frontend for Circuit Macros by J. D. Aplevich. <p>Visit the <a href=http://www.ece.uwaterloo.ca/~aplevich/Circuit_macros>Circuit Macros website</a> for further informations"), KAboutData::License_GPL, ki18n("(c) 2009 Matteo Agostinelli"));
  aboutData.addAuthor(ki18n("Matteo Agostinelli"), ki18n("Maintainer"), "agostinelli@gmail.com");
  KCmdLineArgs::init( argc, argv, &aboutData );

  KCmdLineOptions options;
  options.add("+[file]", ki18n("Document to open")); //new
  KCmdLineArgs::addCmdLineOptions( options );
  
  KApplication app;
  MainWindow* window = new MainWindow();

  KCmdLineArgs *args = KCmdLineArgs::parsedArgs();
	if (args->count())
	{
		window->loadFile(args->url(0).url());
	}

	window->show();

	return app.exec();
}
