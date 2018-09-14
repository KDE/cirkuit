/*
    Copyright (C) 2011  Matteo Agostinelli <agostinelli@gmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include "templatechoosedialog.h"
#include <QListView>
#include <QDebug>
//#include <KNS3/DownloadDialog>
//#include <KNS3/UploadDialog>
#include "documenttemplate.h"
#include <QTemporaryFile>
#include <QStandardPaths>
#include <QTextStream>
#include <KIO/CopyJob>
#include <KIO/DeleteJob>
#include <KLocalizedString>
#include <QFileInfo>
#include <KDirWatch>
#include <KRun>
#include <QInputDialog>
#include <QDir>
#include <QMimeType>
#include <QMimeDatabase>
#include <KWidgetsAddons/KMessageBox>

using namespace Cirkuit;

void TemplateModel::DeleteRow(const QModelIndex& index, const int row)
{
    beginRemoveRows(index, row, row);
    removeRows(row, 1);
    endRemoveRows();
}

TemplateModel::TemplateModel(QObject* parent): QAbstractListModel(parent)
{
    m_backendFilter.clear();
}

int TemplateModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return TemplateManager::availableTemplates(m_backendFilter).count();
}

QVariant TemplateModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() > TemplateManager::availableTemplates(m_backendFilter).count()) {
        return QVariant();
    }
    
    switch (role) {
        case Qt::DisplayRole:
            return TemplateManager::availableTemplates(m_backendFilter).at(index.row())->getDocFn();
        case Qt::UserRole:
            return TemplateManager::availableTemplates(m_backendFilter).at(index.row())->getDocFnPath();
        default:
            return QVariant();
    }
}

void TemplateModel::applyBackendFilter(const QString& backendName)
{
    if (m_backendFilter == backendName) {
        return;
    }
    beginResetModel();
    m_backendFilter.clear();
    m_backendFilter = backendName;
    endResetModel();

}

void TemplateModel::refresh()
{
    beginResetModel();
    TemplateManager::scanTemplates();
    endResetModel();
}

TemplateChooseDialog::TemplateChooseDialog(const QString& backendName, const QUrl& cur_selection, QWidget* parent,
                                           Qt::WindowFlags flags): QDialog(parent, flags)
{
    m_selected = cur_selection;
    qDebug() << "FILTERING " << backendName;    
    setWindowTitle(i18n("Template manager"));
    m_model = new TemplateModel(this);
    m_model->refresh();
    m_model->applyBackendFilter(backendName); 
    m_backend = backendName;
    
    QWidget* w=new QWidget(this);
    m_ui.setupUi(w);
    m_ui.listView->setModel(m_model);


    qDebug() << "Looking for" << m_selected;
    int nrows = m_model->rowCount();
    if (nrows>0)
      {
        QModelIndex m_idx2 = m_model->index(0, 0);
        for (int i=0; i<nrows; ++i)
        {
           QModelIndex m_idx = m_model->index(i, 0);
           QUrl m_row = m_model->data(m_idx, Qt::UserRole).value<QUrl>();
           if (cur_selection == m_row ) {  m_idx2 =  m_idx; }
        }
        m_ui.listView->setCurrentIndex(m_idx2);
        m_selected = m_model->data(m_idx2, Qt::UserRole).value<QUrl>();
      }
    
    m_ui.btnAdd->setIcon(QIcon::fromTheme("list-add"));
    m_ui.btnRemove->setIcon(QIcon::fromTheme("list-remove"));
    m_ui.btnEdit->setIcon(QIcon::fromTheme("document-edit"));
   // m_ui.btnDownload->setIcon(QIcon::fromTheme("get-hot-new-stuff"));
   // m_ui.btnUpload->setIcon(QIcon::fromTheme("get-hot-new-stuff"));
  
    if (nrows==0)
    {
       m_ui.btnEdit->setEnabled(false);
       m_ui.btnRemove->setEnabled(false);
    };
    if (m_ui.comboBackend->findText(backendName)<0)  { m_ui.comboBackend->addItem(backendName);}
    m_ui.comboBackend->setCurrentIndex(0);
    w->setLayout(m_ui.gridLayout);

    // Use signals to update the listView (of template files) ifa deletion or creation occurs
    // The removeTemplate() and editTemplate() functions also call update().
    //
    KDirWatch* dirWatch = new KDirWatch;
    dirWatch->addDir(QStandardPaths::locate(QStandardPaths::AppDataLocation, "templates", QStandardPaths::LocateDirectory));
    connect(dirWatch, SIGNAL(dirty(QString)), this, SLOT(update(QString)));

    connect(m_ui.listView, SIGNAL(clicked(QModelIndex)), this, SLOT(changeCurrent(QModelIndex)));
   // connect(m_ui.btnDownload, SIGNAL(clicked(bool)), this, SLOT(downloadTemplate()));
   // connect(m_ui.btnUpload, SIGNAL(clicked(bool)), this, SLOT(uploadTemplate()));
    connect(m_ui.btnEdit, SIGNAL(clicked(bool)), this, SLOT(editTemplate()));
    connect(m_ui.btnAdd, SIGNAL(clicked(bool)), this, SLOT(addTemplate()));
    connect(m_ui.btnRemove, SIGNAL(clicked(bool)), this, SLOT(removeTemplate()));
    connect(m_ui.buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(m_ui.buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

void TemplateChooseDialog::changeCurrent(const QModelIndex& index)
{        
    m_ui.btnEdit->setEnabled(index.isValid());
   // m_ui.btnUpload->setEnabled(index.isValid());
    m_ui.btnRemove->setEnabled(index.isValid());
    
    if (index.isValid()) {
        readUrlSelected(index);
    } else {
        m_selected = QUrl();
    }
    qDebug() << "Selected" << m_selected;
}


QUrl TemplateChooseDialog::selectedFile() const
{
    return m_selected;
}

void TemplateChooseDialog::readUrlSelected(const QModelIndex& index)
{
    if (!index.isValid()) {
        return;
    }
    
    m_selected = m_model->data(index, Qt::UserRole).value<QUrl>();
}

// New scheme (calls editor on actual file)
void TemplateChooseDialog::editTemplate()
{
    if (!m_selected.isValid()) return;

    QString fnpath(m_selected.path());
    //QMimeDatabase db;
    //const QString mimtype = db.mimeTypeForFile(Finfo.fileName()).name();
    const QString mimtype("text/plain");
    KRun::runUrl(QUrl(fnpath), mimtype, this, KRun::RunFlags());
}


/*
void TemplateChooseDialog::copyTempFile(const QString& fileName)
{
    QUrl dest = QString("templates/%1").arg(m_selected.fileName()));
    
    if (QFile::exists(dest, KNS3::DestinationSide)) {
        bool ok = QFile::remove(dest);
    }
    bool ok = QFile::copy(fileName, dest);  // changed. Need full paths.
    update();
}
*/


void TemplateChooseDialog::addTemplate()
{
    bool ok = false;
    QString name = QInputDialog::getText(this, i18n("Template name"), i18n("Insert the template name"), QLineEdit::Normal, "template.ckt", &ok);
    
    if (!ok || name.isEmpty()) return;

    QDir dir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + QString("/templates/"));
    if (!dir.exists()) {dir.mkpath(".");}
    QString s = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + QString("/templates/%1").arg(name);
    QUrl newUrl = QUrl(s);

    QFile newTemplate(newUrl.path());
    if (!newTemplate.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "File already exists.";
        return;
    }

    QTextStream out(&newTemplate);
    out << "%%backend="<< m_backend << "%%\n";
    
    newTemplate.close();
    m_selected = newUrl;
    editTemplate();
    update();
}



void TemplateChooseDialog::removeTemplate()
{
    readUrlSelected(m_ui.listView->currentIndex());
    
    if (KMessageBox::warningContinueCancel(this, i18n("Do you really want to delete the selected template?"), 
            i18n("Confirm deletion"), 
            KStandardGuiItem::remove()) != KMessageBox::Continue) {
        return;
    }
    
    QFile Fn(m_selected.toString());
    bool ok = Fn.remove();
    if (!ok)
     {
         KMessageBox::error(this, i18n("The file could not be removed (check permissions?)."),
                             i18n("Error deleting file"), 0);
         return;
     }

    QModelIndex index = m_ui.listView->currentIndex();
    //m_model->DeleteRow(index, index.row());  // does not work
    update();          // so these three lines instead (also grey out button if needed)
    index = m_ui.listView->currentIndex();
    m_selected = m_model->data(index, Qt::UserRole).value<QUrl>();
}

void TemplateChooseDialog::update(const QString& dummy)
{
    m_model->refresh();
    int nrows = m_model->rowCount();
    if (nrows==0)
    {
       m_ui.btnEdit->setEnabled(false);
       m_ui.btnRemove->setEnabled(false);
    }
    else
    {
       m_ui.btnEdit->setEnabled(true);
       m_ui.btnRemove->setEnabled(true);
    };


}


/*
// Omit this for now.
void TemplateChooseDialog::downloadTemplate()
{
    QPointer<KNS3::DownloadDialog> dialog = new KNS3::DownloadDialog("cirkuit_template.knsrc");
    dialog->exec();
    foreach (const KNS3::Entry& e,  dialog->changedEntries()) {
        qDebug() << "Changed Entry: " << e.name();
    }
}

void TemplateChooseDialog::uploadTemplate()
{
    if (!m_ui.listView->currentIndex().isValid()) return;

    KNS3::UploadDialog dialog("cirkuit_template.knsrc");
    dialog.setUploadFile(m_selected);
    dialog.setUploadName("A template for Cirkuit");
    dialog.exec();
}
*/


// Old scheme - open a copy coied to /tmp
/*
void TemplateChooseDialog::editTemplate()
{
    if (!m_selected.isValid()) return;

    // Get a temporary filename
    QTemporaryFile* tempFile = new QTemporaryFile;
    tempFile->open(); // The name is not set until the file is opened.
    QFileInfo Finfo(tempFile->fileName());
    tempFile->close();
    tempFile->remove();

    // Create the temporary file in subdir of TempLocation
    QString DestDir = QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/cirkuit/templates";
    QDir dir(DestDir);
    if (!dir.exists()) {dir.mkpath(".");}
    tempFile->setFileTemplate(DestDir);
    QString fnpath = DestDir + '/' + Finfo.fileName();

    bool ok =  QFile::copy(m_selected.path(), fnpath);
    if (ok) {
        KDirWatch* dirWatch = new KDirWatch;
        dirWatch->addFile(fnpath);
        connect(dirWatch, SIGNAL(dirty(QString)), this, SLOT(copyTempFile(QString)));
        //QMimeDatabase db;
        //const QString mimtype = db.mimeTypeForFile(Finfo.fileName()).name();
        const QString mimtype("text/plain");
        KRun::runUrl(QUrl(fnpath), mimtype, this, KRun::RunFlags());
    }
    else
     { qDebug() << "Failed to copy" << m_selected.path() << "to" << fnpath; }
}
*/
