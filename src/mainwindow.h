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
#include "graphicsdocument.h"
#include "graphicsgenerator.h"

namespace KTextEditor
{
    class Document;
    class View;
}

class LivePreviewWidget;
class GeneratorThread;
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
    void showPreview(const QImage& image);
    void saveFileToDisk(const QString& path);
    void openPreview();

    void newDocument(GraphicsDocument::DocumentType);
    void newCmDocument();
    void newGnuplotDocument();
    void newTikzDocument();

    void updateTitle();
    void updateConfiguration();
    void configure();
    void builtNotification();
    void failedNotification();

    void showManual();
    void showExamples();

    void checkCircuitMacros();
    void circuitMacrosConfigured();
    void askIfUpgrade(const QString&);
    void reset();

private:
    void setupActions();

    KTextEditor::View *m_view;
    GraphicsDocument *m_doc;
    QTimer* m_updateTimer;
    QStringList mimeTypes;
    KUrl m_currentFile;
    KRecentFilesAction* recentFilesAction;
    CircuitMacrosManager* cmm;
    QString m_tempSavePath;

    QString m_windowTitle;
    LivePreviewWidget *m_livePreviewWidget;
    GeneratorThread* m_generator;

public slots:
    void loadFile(const KUrl& url);
    void displayError(const QString& app, const QString& msg);
    void displayMessage(const QString& app, const QString& msg);

protected:
    void closeEvent(QCloseEvent *event);
};

#endif
