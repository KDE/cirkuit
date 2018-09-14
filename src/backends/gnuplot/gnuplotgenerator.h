/*
    Copyright (C) 2011 Matteo Agostinelli <agostinelli@gmail.com>

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


#ifndef GNUPLOTGENERATOR_H
#define GNUPLOTGENERATOR_H

#include "generator.h"
#include "format.h"

class GnuplotGenerator : public Cirkuit::Generator
{

public:
    explicit GnuplotGenerator(Cirkuit::Backend* backend = 0, QObject* parent = 0);
    virtual ~GnuplotGenerator();
    
    virtual int convert(const Cirkuit::Format& in, const Cirkuit::Format& out);
};

#endif // GNUPLOTGENERATOR_H
