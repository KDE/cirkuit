/*
    Copyright (C) 2011 Matteo Agostinelli <agostinelli@gmail.com>

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

#ifndef CIRKUIT_EXPORT_H
#define CIRKUIT_EXPORT_H

// needed for KDE_EXPORT and KDE_IMPORT macros
#include <kdemacros.h>

#ifndef CIRKUIT_EXPORT
# if defined(MAKE_CIRKUITLIBS_LIB)
// We are building this library
#  define CIRKUIT_EXPORT KDE_EXPORT
# else
// We are using this library
#  define CIRKUIT_EXPORT KDE_IMPORT
# endif
#endif

# ifndef CIRKUIT_EXPORT_DEPRECATED
#  define CIRKUIT_EXPORT_DEPRECATED KDE_DEPRECATED CIRKUIT_EXPORT
# endif

#endif /* CIRKUIT_EXPORT_H */