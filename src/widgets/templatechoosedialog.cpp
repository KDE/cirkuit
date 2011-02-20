/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2011  Matteo Agostinelli <matteo.agostinelli@uni-klu.ac.at>

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
    m_view = new QListView(this);
    m_view->setModel(m_model);
    setMainWidget(m_view);
    
    connect(m_view, SIGNAL(clicked(QModelIndex)), this, SLOT(changeCurrent(QModelIndex)));
}

void TemplateChooseDialog::changeCurrent(const QModelIndex& index)
{    
    m_selected = m_model->data(index, Qt::UserRole).value<KUrl>();
    kDebug() << "New selection: " << m_selected;
}

KUrl TemplateChooseDialog::selectedFile() const
{
    return m_selected;
}

