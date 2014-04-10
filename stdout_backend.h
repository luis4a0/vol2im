/*

vol2im embeds volumetric data in images. Copyright (C) 2014 Luis Peñaranda.

This program is free software: you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef VOL2IM_STDOUT_BACKEND
#define VOL2IM_STDOUT_BACKEND

#include <stdio.h>
#include "volumetric_structure.h"

void printSlices(FILE*,const unsigned,const unsigned,const unsigned,voxel_t***);

#endif /* VOL2IM_STDOUT_BACKEND */
