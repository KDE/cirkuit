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

#include "format.h"

#include <QMimeType>

using namespace Cirkuit;

class Cirkuit::FormatPrivate {
public:
    Format::Type type;
};

Format::Format(): d(new FormatPrivate)
{

}

Format::Format(const Type& type): QObject(), d(new FormatPrivate)
{
    d->type = type;
}

Format::Format(const Format& other): QObject(), d(new FormatPrivate)
{
    d->type = other.d->type;
}

Format::~Format()
{
    delete d;
}

Format& Format::operator=(const Format& other)
{
    this->d->type = other.d->type;
    return *this;
}

bool Format::operator==(const Format& other) const
{
    return type() == other.type();
}

Format::Type Cirkuit::Format::type() const
{
    return d->type;
}

QString Format::extension() const
{
    switch (d->type) {
        case Source:
            return ".cir";
        case Dvi:
            return ".dvi";
        case Postscript:
            return ".ps";
        case Pdf:
            return ".pdf";
        case Eps:
            return ".eps";
        case Png:
            return ".png";
        case Jpeg:
            return ".jpg";
        case Svg:
            return ".svg";
        case Gif:
            return ".gif";
        case Tex:
            return ".tex";
        case Ppm:
            return ".ppm";
        case QtImage:
        case Unknown:
        default:
            return "";
    }
}

Format Format::fromExtension(const QString& extension)
{
    if (extension.contains("pdf")) {
        return Format(Pdf);
    } else if (extension.contains("cir")) {
        return Format(Source);
    } else if (extension.contains("dvi")) {
        return Format(Dvi);
    } else if (extension.contains("eps")) {
        return Format(Eps);
    } else if (extension.contains("ps")) {
        return Format(Postscript);
    } else if (extension.contains("png")) {
        return Format(Png);
    } else if (extension.contains("jpg") || extension.contains("jpeg")) {
        return Format(Jpeg);
    } else if (extension.contains("svg")) {
        return Format(Svg);
    } else if (extension.contains("gif")) {
        return Format(Gif);
    } else if (extension.contains("tex")) {
        return Format(Tex);
    }
    
    return Format(Unknown);
}

Format Format::fromMimeType(const QMimeType &mime)
{
    const QStringList patterns = mime.globPatterns();
    foreach(const QString pattern, patterns) {
        const QString extension = pattern.mid(1); //remove the * from the glob
        Format f = fromExtension(extension);
        if (f == Unknown)
            continue;
        return f;
    }
    return Unknown;
}

