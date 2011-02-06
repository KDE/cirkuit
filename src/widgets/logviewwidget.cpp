/*
    Copyright (C) 2009  Matteo Agostinelli <agostinelli@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "logviewwidget.h"

#include <KTextEdit>

LogViewWidget::LogViewWidget ( const QString & title, QWidget* parent, Qt::WindowFlags flags ) : QDockWidget ( title, parent, flags )
{
    m_textEdit = new KTextEdit(this);
    m_textEdit->setReadOnly(true);
    QPalette palette;
    palette.setColor(QPalette::Background, Qt::white);
    m_textEdit->setPalette(palette);
    
    setWidget(m_textEdit);
}

void LogViewWidget::clear()
{
    m_textEdit->clear();
}

QSize LogViewWidget::sizeHint() const
{
    return QSize(300, 50);;
}


void LogViewWidget::displayError ( const QString& app, const QString& msg )
{
    if (msg.isEmpty()) return;
    
    m_textEdit->setFontWeight(QFont::Bold);
    m_textEdit->setTextColor(Qt::red);
    m_textEdit->insertPlainText(QString("[%1]\n").arg(app));
    m_textEdit->setFontWeight(QFont::Normal);
    m_textEdit->insertPlainText(msg + "\n\n");
    m_textEdit->setTextColor(Qt::black);
    
    show();
}

void LogViewWidget::displayMessage ( const QString& app, const QString& msg )
{
    if (msg.isEmpty()) return;
    
    m_textEdit->setFontWeight(QFont::Bold);
    m_textEdit->insertPlainText(QString("[%1]\n").arg(app));
    m_textEdit->setFontWeight(QFont::Normal);
    m_textEdit->insertPlainText(msg + "\n\n");
}
