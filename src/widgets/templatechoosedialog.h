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

#include<QComboBox>
#include<QPushButton>
#include <QAbstractListModel>
#include <QDialog>
#include <QUrl>
#include "ui_templatechooser.h"

namespace Cirkuit {
}

class TemplateModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit TemplateModel(QObject* parent = 0);
    
    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    
    void applyBackendFilter(const QString& backendName = QString());
    void refresh();
    virtual void DeleteRow(const QModelIndex& index, const int row);
    
private:
    QString m_backendFilter;
};

class TemplateChooseDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TemplateChooseDialog(const QString& backendName = QString(), const QUrl& cur_selection = QUrl(), QWidget* parent = 0, Qt::WindowFlags flags = 0);
    
    QUrl selectedFile() const;
    
protected:
    TemplateModel* m_model;
    Ui::TemplateChooseBase m_ui;
    
    QString m_backend;
    QUrl m_selected = QUrl();
    
protected slots:
    void changeCurrent(const QModelIndex& index);
    void update(const QString& dummy = QString());
    void readUrlSelected(const QModelIndex& index);
    
   // void downloadTemplate();
   // void uploadTemplate();
    void editTemplate();
    void addTemplate();
    void removeTemplate();
};

#endif // TEMPLATECHOOSEDIALOG_H
