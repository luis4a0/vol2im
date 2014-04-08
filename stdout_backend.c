#include "stdout_backend.h"
#include <stdio.h>

void printSlice(FILE *o,
                const unsigned slice,
                const unsigned xSize,
                const unsigned ySize,
                voxel_t ***volume){
        int i,j;
        for(i=0;i<xSize;++i){
                for(j=0;j<ySize;++j){
                        fprintf(o,"%d ",(unsigned)(volume[slice][i][j]));
                        //o<<(unsigned)(volume[slice][i][j])<<' '<<std::flush;
                }
                fprintf(o,"\n");
                //o<<std::endl;
        }
}

void printSlices(FILE *o,
                 const unsigned numSlices,
                 const unsigned xSize,
                 const unsigned ySize,
                 voxel_t ***volume){
        int s;
        for(s=0;s<numSlices;++s){
                fprintf(o,"slice %d:\n",s);
                //std::cout<<"slice "<<s<<":"<<std::endl;
                printSlice(o,s,xSize,ySize,volume);
        }
}
