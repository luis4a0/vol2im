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

#include "stpng8_frontend.h"
#include "stpng816_frontend.h"
#include <png.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int stpng8Read16(unsigned *xSize,
                 unsigned *ySize,
                 voxel_t ****volume,
                 const char **files){
        unsigned i;
        /* Read the first image to determine its size (assuming all the 16
        images have the same size).*/
        pngSize(xSize,ySize,files[0]);
        /* Init the volumetric structure, with only four slices; each slice
        will contain four input images. */
        *volume=initStructure(*xSize*2,*ySize*2,4);
        for(i=0;i<4;++i){
                stpng8ReadSlice(i,*xSize,*ySize,0,0,volume,files[4*i]);
                stpng8ReadSlice(i,*xSize,*ySize,0,*xSize,volume,files[4*i+1]);
                stpng8ReadSlice(i,*xSize,*ySize,*ySize,*xSize,volume,
                                files[4*i+2]);
                stpng8ReadSlice(i,*xSize,*ySize,*ySize,0,volume,files[4*i+3]);
        }
        /* Set the correct file size for the backend to write. */
        *xSize*=2;
        *ySize*=2;
        return 0;
}
