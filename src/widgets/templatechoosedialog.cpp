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
using namespace Cirkuit;

TemplateModel::TemplateModel(QObject* parent): QAbstractListModel(parent)
{
    m_backendFilter = QString();
}

int TemplateModel::rowCount(const QModelIndex& parent) const
{
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

TemplateChooseDialog::TemplateChooseDialog(const QString& backendName, QWidget* parent, Qt::WFlags flags): KDialog(parent, flags)
{
    kDebug() << "FILTERING " << backendName;
    m_model = new TemplateModel(this);
    m_model->applyBackendFilter(backendName);
    
    QWidget* w=new QWidget(this);
    m_ui.setupUi(w);
    m_ui.listView->setModel(m_model);
    
    m_ui.btnAdd->setIcon(KIcon("list-add"));
    m_ui.btnEdit->setIcon(KIcon("document-edit"));
    m_ui.btnDownload->setIcon(KIcon("get-hot-new-stuff"));
    m_ui.btnUpload->setIcon(KIcon("get-hot-new-stuff"));
  
    m_ui.btnEdit->setEnabled(false);
    m_ui.btnUpload->setEnabled(false);
    m_ui.comboBackend->setCurrentItem(backendName, true);
    setMainWidget(w);
    
    setWindowTitle(i18n("Template manager"));
    
    connect(m_ui.listView, SIGNAL(clicked(QModelIndex)), this, SLOT(changeCurrent(QModelIndex)));
    connect(m_ui.btnDownload, SIGNAL(clicked(bool)), this, SLOT(downloadTemplate()));
    connect(m_ui.btnUpload, SIGNAL(clicked(bool)), this, SLOT(uploadTemplate()));
}

void TemplateChooseDialog::changeCurrent(const QModelIndex& index)
{    
    if (!index.isValid()) return;
    
    m_ui.btnEdit->setEnabled(true);
    m_ui.btnUpload->setEnabled(true);
    m_selected = m_model->data(index, Qt::UserRole).value<KUrl>();
}

KUrl TemplateChooseDialog::selectedFile() const
{
    return m_selected;
}

void TemplateChooseDialog::downloadTemplate()
{
    KNS3::DownloadDialog dialog("cirkuit_template.knsrc");
    dialog.exec();
    foreach (const KNS3::Entry& e,  dialog.changedEntries()) {
        kDebug() << "Changed Entry: " << e.name();
    }
}

void TemplateChooseDialog::uploadTemplate()
{
    if (!m_ui.listView->currentIndex().isValid()) return;
    
    KNS3::UploadDialog dialog("cirkuit_template.knsrc");
    dialog.setUploadFile(m_selected);
    dialog.setUploadName("A template for Cirkuit");
    dialog.setDescription("This is an example of a template for Cirkuit");
    dialog.exec();
}


