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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <KParts/MainWindow>
#include <QtGui/QKeyEvent>
#include <KUrl>

class ImageView;
class LogViewWidget;
namespace KTextEditor
{
    class Document;
    class View;
}

namespace Cirkuit
{
    class Document;
    class Backend;
}

class LivePreviewWidget;
class GeneratorThread;
class QTimer;
class KRecentFilesAction;
class KToggleAction;
class KAction;
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
	void newFile();
    void saveAsFile(const KUrl& url);
    void saveAs();
    void save();
    void substituteSaveAsAction();
    void exportFile();

    void documentModified(KTextEditor::Document*);
    void buildPreview();
    void showPreview(const QImage& image);
    void saveFileToDisk(const QString& path);
    void openPreview();
    void openPreviewFile();

    void newDocument(const QString& backendName = QString());

    void updateTitle();
    void updateConfiguration();
    void updateZoomToFit();
    void configure();
    void configureKeyBindings();
    void configureToolbars();
    void builtNotification();
    void failedNotification();

    void showManual();
    void showExamples();

    void checkCircuitMacros();
    void circuitMacrosConfigured();
    void askIfUpgrade(const QString&);
    void reset();
    void openHelpUrl(const KUrl& url);
    
    void initializeBackend();
    void setDefaultBackend(const QString& backend);

private:
    void setupActions();

    KTextEditor::View *m_view;
    Cirkuit::Document *m_doc;
    Cirkuit::Backend *m_backend;
    QTimer* m_updateTimer;
    QStringList mimeTypes;
    KUrl m_currentFile;
    
    KRecentFilesAction* recentFilesAction;
    KToggleAction* zoomFitPageAction;
    KAction* zoomFitAction;
    
    CircuitMacrosManager* cmm;
    QString m_tempSavePath;

    QString m_windowTitle;
    LivePreviewWidget *m_livePreviewWidget;
    ImageView* m_imageView;
    LogViewWidget* m_logViewWidget;
    GeneratorThread* m_generator;

public slots:
    void loadFile(const KUrl& url);

protected:
    void closeEvent(QCloseEvent *event);
};

#endif
