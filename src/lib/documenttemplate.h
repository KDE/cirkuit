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

#ifndef DOCUMENTTEMPLATE_H
#define DOCUMENTTEMPLATE_H

#include "cirkuit_export.h"

#include <QObject>

namespace Cirkuit
{

/**
 * A class for managing the templates used during the
 * creation of the graphic object
 */
class CIRKUIT_EXPORT DocumentTemplate : public QObject
{
    Q_OBJECT
public:
    /**
     * Default constructor.
     * @param path is the path of the template file
     */
    DocumentTemplate(const QString& path, QObject* parent = 0);
    
    /**
     * Inserts the code into the template. The point of insertion
     * should be denoted by keyword in the template itself.
     * @param code the code to be inserted
     * @param keyword the keyword in the template that will be substituted by the code. The default value is <!CODE!>
     * @return the resulting text
     */
    QString insert(const QString& code, const QString& keyword = "<!CODE!>");
    
private:
    QString m_path;
};

}
#endif // DOCUMENTTEMPLATE_H
