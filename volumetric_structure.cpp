#include "volumetric_structure.h"
#include <cstdlib>

unsigned*** initStructure(const unsigned xSize,
                          const unsigned ySize,
                          const unsigned numSlices){
        unsigned ***volume=(unsigned***)malloc(sizeof(unsigned**)*numSlices);
        for(int i=0;i<numSlices;++i){
                volume[i]=(unsigned**)malloc(sizeof(unsigned*)*xSize);
                for(int j=0;j<xSize;++j){
                        volume[i][j]=(unsigned*)calloc(ySize,sizeof(unsigned));
                }
        }
        return volume;
}
