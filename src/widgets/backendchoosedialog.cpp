/*
    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 2
    of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA  02110-1301, USA.

    ---
    Copyright (C) 2009 Alexander Rieder <alexanderrieder@gmail.com>
    Copyright (C) 2011 Matteo Agostinelli <agostinelli@gmail.com>
 */

#include <KLocalizedString>
#include <KIconLoader>
#include "backendchoosedialog.h"
#include "lib/backend_interface.h"

const char* BackendChooseDialog::descriptionTemplate = I18N_NOOP("<h1>%1</h1>" \
                                                                 "<div>%2</div><br/>" \
                                                                 "<div>See <a href=\"%3\">%3</a> for more information</div>");

BackendChooseDialog::BackendChooseDialog(const QString& backendName, QWidget* parent) : QDialog(parent)
{
    setBackend(backendName);
    setWindowTitle(i18n("Backend selection"));
    
    QWidget* w=new QWidget(this);
    m_ui.setupUi(w);
    m_ui.backendList->setIconSize(QSize(KIconLoader::SizeMedium, KIconLoader::SizeMedium));
    connect(m_ui.backendList, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), this, SLOT(updateDescription()));
    connect(m_ui.backendList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(accept()));

    foreach(Cirkuit::Backend* backend, Cirkuit::Backend::availableBackends()) {
        if (!backend->checkRequirements()) {
            continue;
        }
        QListWidgetItem* item=new QListWidgetItem(m_ui.backendList);
        item->setText(backend->name());
        item->setIcon(QIcon(backend->icon()));
        m_ui.backendList->addItem(item);
        if (m_ui.backendList->currentItem() == 0) {
            m_ui.backendList->setCurrentItem(item);
        }

        if (*backend == m_backend) {
            m_ui.backendList->setCurrentItem(item);
        }
    }

 //   setMainWidget(w); // for KDialog

    w->setLayout(m_ui.gridLayout);

    connect(this, SIGNAL(accepted()), this, SLOT(onAccept()));
}

BackendChooseDialog::~BackendChooseDialog()
{
}

void BackendChooseDialog::setBackend(const QString& backendName)
{
    m_backend = backendName;
}

void BackendChooseDialog::onAccept()
{
    m_backend = m_ui.backendList->currentItem()->text();
    emit backendSelected(m_backend);
    
    if (m_ui.makeDefault->isChecked()) {
        emit defaultBackendSelected(m_backend);
    }
}

void BackendChooseDialog::updateDescription()
{
    Cirkuit::Backend* current=Cirkuit::Backend::getBackend( m_ui.backendList->currentItem()->text() );
    m_ui.descriptionView->setHtml(i18n(BackendChooseDialog::descriptionTemplate, current->name(), current->description(), current->url().url()));
}

QString BackendChooseDialog::backendName()
{
    return m_backend;
}

