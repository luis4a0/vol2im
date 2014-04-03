#include "stdout_backend.h"

std::ostream& printSlice(std::ostream &o,
                         const unsigned slice,
                         const unsigned xSize,
                         const unsigned ySize,
                         voxel_t ***volume){
        for(int i=0;i<xSize;++i){
                for(int j=0;j<ySize;++j){
                        o<<(unsigned)(volume[slice][i][j])<<' '<<std::flush;
                }
                o<<std::endl;
        }
        return o;
}

std::ostream& printSlices(std::ostream &o,
                          const unsigned numSlices,
                          const unsigned xSize,
                          const unsigned ySize,
                          voxel_t ***volume){
        // Print data to stdout.
        for(int s=0;s<numSlices;++s){
                std::cout<<"slice "<<s<<":"<<std::endl;
                printSlice(o,s,xSize,ySize,volume);
        }
}
