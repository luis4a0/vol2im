#include "volumetric_structure.h"
#include <stdlib.h>

voxel_t*** initStructure(const unsigned xSize,
                         const unsigned ySize,
                         const unsigned numSlices){
        voxel_t*** volume=(voxel_t***)malloc(sizeof(voxel_t**)*numSlices);
        int i,j;
        for(i=0;i<numSlices;++i){
                volume[i]=(voxel_t**)malloc(sizeof(voxel_t*)*xSize);
                for(j=0;j<xSize;++j){
                        volume[i][j]=(voxel_t*)calloc(ySize,sizeof(voxel_t));
                }
        }
        return volume;
}
