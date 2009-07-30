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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <KParts/MainWindow>
#include <QtGui/QKeyEvent>
#include <KUrl>

namespace KTextEditor
{
	class Document;
	class View;
}

class LivePreviewWidget;
class PreviewGenerator;
class QTimer;
class KRecentFilesAction;
class GraphicsDocument;
class CircuitMacrosManager;

class MainWindow : public KParts::MainWindow
{
	Q_OBJECT
	
	public:
		MainWindow(QWidget *parent=0);
		
	private slots:
		void clear();
		void openFile();
		void saveAsFile(const KUrl& url);
		void saveAs();
		void save();
		void substituteSaveAsAction();
		void exportFile();
		
		void documentModified(KTextEditor::Document*);
		void buildPreview();
		void openPreview();
		
		void newCmDocument();
		void newTikzDocument();
		
		void updateTitle();
		void updateConfiguration();
		void configure();
		void startBuildNotification();
		
		void showManual();
		void showExamples();
		
		void checkCircuitMacros();
		void circuitMacrosConfigured();
		void askIfUpgrade(const QString&);
		
	private:
		void setupActions();
		
		KTextEditor::View *m_view;
		GraphicsDocument *m_doc;
		QTimer* m_updateTimer;
		QStringList mimeTypes;
		KUrl m_currentFile;
		KRecentFilesAction* recentFilesAction;
		CircuitMacrosManager* cmm;
		
		QString m_windowTitle;
		LivePreviewWidget *m_livePreviewWidget;
		PreviewGenerator *m_generator;
		
	public slots:
		void loadFile(const KUrl& url);
		void displayError(const QString& app, const QString& msg);
		
	protected:
		void closeEvent(QCloseEvent *event);
};

#endif
