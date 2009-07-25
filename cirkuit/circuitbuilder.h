#ifndef CIRCUITBUILDER_H
#define CIRCUITBUILDER_H

#include <QObject>
#include <KUrl>

class QProcess;
class ExternalBinManager;

class CircuitBuilder : public QObject
{
  Q_OBJECT
  public:
    CircuitBuilder(const QString& interpreter = "");
    
    QString picInterpreter() const { return mPicInterpreter; }
    void setPicInterpreter(const QString& interpreter) { mPicInterpreter = interpreter; }
    
    void build(const KUrl& url, const QString& origDir = "");
    
    QString epsFilePath() const;
    QString pdfFilePath() const;
    QString pngFilePath() const;
    QString pstFilePath() const;
	 QString psFilePath() const;
	 QString svgFilePath() const;
    
  private:
    QString mPicInterpreter;  
    QProcess *buildProcess;
    KUrl tempFileUrl;
    ExternalBinManager* mngr;
	 
	 bool checkApps(const QStringList& apps) const;
    
  signals:
    void previewBuilt(const QImage&);
    void buildFinished();
    
  protected slots:
    void processFinished();
};

#endif
