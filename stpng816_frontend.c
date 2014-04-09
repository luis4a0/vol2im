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
                stpng8ReadSlice(i,*xSize,*ySize,*ySize,0,volume,files[4*i+2]);
                stpng8ReadSlice(i,*xSize,*ySize,*ySize,*xSize,volume,
                                files[4*i+3]);
        }
        /* Set the correct file size for the backend to write. */
        *xSize*=2;
        *ySize*=2;
        return 0;
}
