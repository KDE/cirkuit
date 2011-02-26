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


#ifndef TEMPLATECHOOSEDIALOG_H
#define TEMPLATECHOOSEDIALOG_H

#include "ui_templatechooser.h"

#include <QAbstractListModel>

#include <KDialog>

class QListView;
namespace Cirkuit {
class TemplateManager;
}

class TemplateModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit TemplateModel(QObject* parent = 0);
    
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    
    void applyBackendFilter(const QString& backendName = QString());
    
private:
    QString m_backendFilter;
};

class TemplateChooseDialog : public KDialog
{
    Q_OBJECT
public:
    explicit TemplateChooseDialog(const QString& backendName = QString(), QWidget* parent = 0, Qt::WFlags flags = 0);
    
    KUrl selectedFile() const;
    
protected:
    TemplateModel* m_model;
    Ui::TemplateChooseBase m_ui;
    
    QString m_backend;
    KUrl m_selected;
    
protected slots:
    void changeCurrent(const QModelIndex& index);
    void copyTempFile(const QString& fileName);
    
    void downloadTemplate();
    void uploadTemplate();
    void editTemplate();
};

#endif // TEMPLATECHOOSEDIALOG_H
