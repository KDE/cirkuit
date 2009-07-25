#ifndef MAINWINDOW_H
#define MAINWINDOW_H
 
#include <KXmlGuiWindow>
#include <KTextEdit>
#include <KUrl>

class QLabel;
class KRecentFilesAction;
class QTimer;
class CircuitBuilder;
class LivePreviewWidget;
class CircuitMacrosManager;
 
class MainWindow : public KXmlGuiWindow
{
  Q_OBJECT
  public:
    MainWindow(QWidget *parent=0);
	 ~MainWindow();
   
  private:
	  KTextEdit* textArea;
	  QLabel* lineNumberLabel;
	  void setupActions();
	  KRecentFilesAction* recentFilesAction;
	  LivePreviewWidget* liveWidget;
	  QString fileName;
	  QTimer *updateTimer;
	  QString tempFileName;
	  CircuitBuilder* builder;
	  CircuitMacrosManager* cmm;
	  QStringList mimeTypes;
	
	  bool askIfModified();
    
  public slots:
    bool loadFile(const KUrl&);
    bool saveFile(const QString&, bool temporary = false);
        
  protected slots:
    void openSlot(const KUrl& url = KUrl());
    void clearSlot();
    bool saveSlot();
    void configureSlot();
    void updateConfiguration();
    bool saveAsSlot();
    bool isUntitled() const;
    
    void exportToPdf();
    void exportToEps();
    void exportToPng();
    void exportToPst();
	 void exportToPs();
	 void exportToSvg();
    void previewEps();

    void updateModifiedStatus(bool b = true);
    void setCurrentFile(const QString&);
    
    void createLivePreviewWidget();
    void build();
    
    void updatePreview(const QImage&);
    
    void showManual();
    void showExamples();
    void showTwoTermDialog();

	void checkCircuitMacros();
	void circuitMacrosConfigured();
	void askIfUpgrade(const QString&);
	
	void setCurrentLineNumber();
    
  protected:
    void closeEvent(QCloseEvent *event);
};
 
#endif
