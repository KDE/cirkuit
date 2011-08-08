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

#include <KDebug>
#include <knewstuff3/downloaddialog.h>
#include <knewstuff3/uploaddialog.h>

#include "lib/documenttemplate.h"
#include <KTemporaryFile>
#include <KStandardDirs>
#include <KIO/NetAccess>
#include <QFileInfo>
#include <KRun>
#include <KDirWatch>
#include <KInputDialog>
#include <KMessageBox>

using namespace Cirkuit;

TemplateModel::TemplateModel(QObject* parent): QAbstractListModel(parent)
{
    m_backendFilter = QString();
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
            return TemplateManager::availableTemplates(m_backendFilter).at(index.row())->name();
        case Qt::UserRole:
            return TemplateManager::availableTemplates(m_backendFilter).at(index.row())->path();
        default:
            return QVariant();
    }
}

void TemplateModel::applyBackendFilter(const QString& backendName)
{
    if (m_backendFilter == backendName) {
        return;
    }
    m_backendFilter = backendName;
    reset();
}

void TemplateModel::refresh()
{
    TemplateManager::scanTemplates();
    reset();
}

TemplateChooseDialog::TemplateChooseDialog(const QString& backendName, QWidget* parent, Qt::WFlags flags): KDialog(parent, flags)
{
    kDebug() << "FILTERING " << backendName;
    m_model = new TemplateModel(this);
    m_model->applyBackendFilter(backendName);
    
    QWidget* w=new QWidget(this);
    m_ui.setupUi(w);
    m_ui.listView->setModel(m_model);
    
    m_ui.btnAdd->setIcon(KIcon("list-add"));
    m_ui.btnRemove->setIcon(KIcon("list-remove"));
    m_ui.btnEdit->setIcon(KIcon("document-edit"));
    m_ui.btnDownload->setIcon(KIcon("get-hot-new-stuff"));
    m_ui.btnUpload->setIcon(KIcon("get-hot-new-stuff"));
  
    m_ui.btnEdit->setEnabled(false);
    m_ui.btnUpload->setEnabled(false);
    m_ui.btnRemove->setEnabled(false);
    m_ui.comboBackend->setCurrentItem(backendName, true);
    setMainWidget(w);
    
    setWindowTitle(i18n("Template manager"));
    
    connect(m_ui.listView, SIGNAL(clicked(QModelIndex)), this, SLOT(changeCurrent(QModelIndex)));
    connect(m_ui.btnDownload, SIGNAL(clicked(bool)), this, SLOT(downloadTemplate()));
    connect(m_ui.btnUpload, SIGNAL(clicked(bool)), this, SLOT(uploadTemplate()));
    connect(m_ui.btnEdit, SIGNAL(clicked(bool)), this, SLOT(editTemplate()));
    connect(m_ui.btnAdd, SIGNAL(clicked(bool)), this, SLOT(addTemplate()));
    connect(m_ui.btnRemove, SIGNAL(clicked(bool)), this, SLOT(removeTemplate()));
}

void TemplateChooseDialog::changeCurrent(const QModelIndex& index)
{        
    m_ui.btnEdit->setEnabled(index.isValid());
    m_ui.btnUpload->setEnabled(index.isValid());
    m_ui.btnRemove->setEnabled(index.isValid());
    
    if (index.isValid()) {
        readUrlSelected(index);
    } else {
        m_selected = KUrl();
    }
}

KUrl TemplateChooseDialog::selectedFile() const
{
    return m_selected;
}

void TemplateChooseDialog::readUrlSelected(const QModelIndex& index)
{
    if (!index.isValid()) {
        return;
    }
    
    m_selected = m_model->data(index, Qt::UserRole).value<KUrl>();
}

void TemplateChooseDialog::downloadTemplate()
{
    QPointer<KNS3::DownloadDialog> dialog = new KNS3::DownloadDialog("cirkuit_template.knsrc");
    dialog->exec();
    foreach (const KNS3::Entry& e,  dialog->changedEntries()) {
        kDebug() << "Changed Entry: " << e.name();
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

void TemplateChooseDialog::editTemplate()
{
    if (!m_selected.isValid()) return;
    
    KTemporaryFile* tempFile = new KTemporaryFile;
    tempFile->setPrefix(KStandardDirs::locateLocal("tmp", "cirkuit/templates/", true));
    tempFile->open();
    QFileInfo tempFileInfo(tempFile->fileName());
    tempFile->close();
    tempFile->remove();
    delete tempFile;
    
    if (KIO::NetAccess::file_copy(m_selected, tempFileInfo.absoluteFilePath(), this)) {
        KDirWatch* dirWatch = new KDirWatch;
        dirWatch->addFile(tempFileInfo.absoluteFilePath());
        connect(dirWatch, SIGNAL(dirty(QString)), this, SLOT(copyTempFile(QString)));
        KRun::runUrl(tempFileInfo.absoluteFilePath(), "text/plain", 0);
    }
}

void TemplateChooseDialog::copyTempFile(const QString& fileName)
{
    KUrl dest = KStandardDirs::locateLocal("appdata", QString("templates/%1").arg(m_selected.fileName()));
    
    if (KIO::NetAccess::exists(dest, false, this)) {
        KIO::NetAccess::del(dest, this);
    }
    KIO::NetAccess::file_copy(fileName, dest, this);
    update();
}

void TemplateChooseDialog::addTemplate()
{
    bool ok = false;
    QString name = KInputDialog::getText(i18n("Template name"), i18n("Insert the template name"), "template.ckt", &ok);
    
    if (!ok || name.isEmpty()) return;
    
    KUrl newUrl = KStandardDirs::locateLocal("appdata", QString("templates/%1").arg(name));
    
    QFile newTemplate(newUrl.path());
    if (!newTemplate.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }
    
    QTextStream out(&newTemplate);
    out << "%%backend=<INSERT_BACKEND>%%\n"; 
    
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
    
    KIO::NetAccess::del(m_selected, this);
    update();
}

void TemplateChooseDialog::update()
{
    m_model->refresh();
}
