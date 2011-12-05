/*
    <one line to give the library's name and an idea of what it does.>
    Copyright (C) 2011  Matteo Agostinelli <matteo.agostinelli@aau.at>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/


#ifndef ASYMPTOTEGENERATOR_H
#define ASYMPTOTEGENERATOR_H

#include <generator.h>


class AsymptoteGenerator : public Cirkuit::Generator
{
public:
    explicit AsymptoteGenerator(Cirkuit::Backend* backend = 0, QObject* parent = 0);\
    
    virtual bool convert(const Cirkuit::Format& in, const Cirkuit::Format& out);
};

#endif // ASYMPTOTEGENERATOR_H
