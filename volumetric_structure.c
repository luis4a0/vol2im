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

#include "volumetric_structure.h"
#include <stdlib.h>

voxel_t*** initStructure(const unsigned xSize,
                         const unsigned ySize,
                         const unsigned numSlices){
        voxel_t*** volume=(voxel_t***)malloc(sizeof(voxel_t**)*numSlices);
        unsigned i,j;
        for(i=0;i<numSlices;++i){
                volume[i]=(voxel_t**)malloc(sizeof(voxel_t*)*xSize);
                for(j=0;j<xSize;++j){
                        volume[i][j]=(voxel_t*)calloc(ySize,sizeof(voxel_t));
                }
        }
        return volume;
}
