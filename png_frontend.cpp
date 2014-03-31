#include "png_frontend.h"
#include "volumetric_structure.h"
#include <png.h>
#include <stdint.h>
#include <cstdlib>
#include <cstdio>

int pngRead(unsigned *numSlices,
            unsigned *xSize,
            unsigned *ySize,
            unsigned ****volume,
            const char *filename){
        // Simulate reading a 4x4x4 cube. TODO: really read the file.
        *numSlices=4;
        *xSize=4;
        *ySize=4;
        *volume=initStructure(*xSize,*ySize,*numSlices);
        (*volume)[1][2][3]=1;
        (*volume)[3][2][3]=1;
        return 0;
}
