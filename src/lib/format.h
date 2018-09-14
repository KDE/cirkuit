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


#ifndef FORMAT_H
#define FORMAT_H

#include "cirkuit_export.h"

#include <QObject>
//#include <QMimeType>

namespace Cirkuit {
class FormatPrivate;

/**
 * A class that is used to model the different graphic/text formats used in the application
 */
class CIRKUIT_EXPORT Format : public QObject
{
public:
    //! An enum of the supported formats
    enum Type {
        Source,
        Dvi,
        Postscript,
        Pdf,
        Eps,
        QtImage,
        Png,
        Jpeg,
        Svg,
        Ppm,
        Gif,
        Tex,
        Html,
        Unknown
    };
   
    //! Default constructor
    Format();
    /** 
     * Constructor with initialization
     * @param type the type
     */
    Format(const Type& type);
    Format(const Format& other);
    virtual ~Format();
    virtual Format& operator=(const Format& other);
    virtual bool operator==(const Format& other) const;
    
    //! The format type
    Type type() const;
    //! The default extension
    QString extension() const;
    
    /**
     * Create a format based on its main extension
     * @param extension the main extension
     * @return the corresponding format
     */
    static Format fromExtension(const QString& extension);
    /**
     * Create a format based on its mimetype
     * @param mime the mime type
     * @return the corresponding format
     */
    //static Format fromMimeType(QMimeType mime);
private:
    FormatPrivate* d;
};

}
#endif // FORMAT_H
