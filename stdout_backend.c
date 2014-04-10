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

#include "stdout_backend.h"
#include <stdio.h>

void printSlice(FILE *o,
                const unsigned slice,
                const unsigned xSize,
                const unsigned ySize,
                voxel_t ***volume){
        unsigned i,j;
        for(i=0;i<xSize;++i){
                for(j=0;j<ySize;++j)
                        fprintf(o,"%d ",(unsigned)(volume[slice][i][j]));
                fprintf(o,"\n");
        }
}

void printSlices(FILE *o,
                 const unsigned numSlices,
                 const unsigned xSize,
                 const unsigned ySize,
                 voxel_t ***volume){
        unsigned s;
        for(s=0;s<numSlices;++s){
                fprintf(o,"slice %d:\n",s);
                printSlice(o,s,xSize,ySize,volume);
        }
}
