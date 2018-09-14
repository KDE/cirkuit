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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <KParts/MainWindow>
#include <QtGui/QKeyEvent>
#include <QUrl>
#include <KMessageWidget>
#include <KLocalizedString>

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

class PreviewWidget;
class GeneratorThread;
class QTimer;
class KRecentFilesAction;
class KMessageWidget;
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
    void saveAsFile(const QString&);
    void saveAs();
    void save();
    void exportFile();

    void documentModified(KTextEditor::Document*);
    void buildPreview();
    void showPreview(const QImage&);
    void saveFileToDisk(const QString&);
    void openPreview();
    void openPreviewFile();
    void openTemplateManager();

    void newDocument(const QString& backendName = QString());

    void updateTitle();
    void updateConfiguration();
    void configure();
    void configureKeyBindings();
    void configureToolbars();
    void builtNotification();
    void failedNotification(const int);

    void showManual();
    void showExamples();
    // void downloadExamples();
    // void uploadExample();
    // void openExample();

    void checkCircuitMacros();
    void circuitMacrosConfigured();
    void askIfUpgrade(const QString&);
    void mainreset();
    void openHelpUrl(const QString& fnpath);
    
    void initializeBackend();
    void setDefaultBackend(const QString& backend);
    
    void backendChanged(const QString& backendName);
    void showMessage(KMessageWidget*);

    void loadFileFromUrl2(const QUrl&, const QString&);

private:
    void setupActions();

    KTextEditor::View *m_view;
    Cirkuit::Document *m_doc;
    Cirkuit::Backend *m_backend;
    QTimer* m_updateTimer;
    QStringList mimeTypes;
    QString m_currentFile;
    QString m_dirCurrentEditorFile;

    KMessageWidget* m_messageWidget;
    KRecentFilesAction* recentFilesAction;
    
    CircuitMacrosManager* cmm;
    QString m_tempSavePath;

    QString m_windowTitle;
    PreviewWidget *m_previewWidget;
    ImageView* m_imageView;
    LogViewWidget* m_logViewWidget;
    GeneratorThread* m_generator;
    
    bool m_firstRun;

public slots:
    void loadFile(const QString&);
    void loadFileFromUrl(const QUrl&);


protected:
    void closeEvent(QCloseEvent *event);

};

#endif
