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
