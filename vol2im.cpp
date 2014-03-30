#include <iostream>
#include <cstdlib>
#include <cstring>
#include "png_backend.h"

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

void readVolumetricData(const unsigned startSlice,
                        const unsigned numSlices,
                        const unsigned xSize,
                        const unsigned ySize,
                        unsigned ***volume){
        volume[1][2][3]=1;
        volume[3][2][3]=1;
        return;
}

std::ostream& printSlice(std::ostream &o,
                        const unsigned s,
                        const unsigned xSize,
                        const unsigned ySize,
                        unsigned ***volume){
        for(int i=0;i<xSize;++i){
                for(int j=0;j<ySize;++j){
                        o<<volume[s][i][j]<<' '<<std::flush;
                }
                o<<std::endl;
        }
        return o;
}

void saveSlicesToFile(const unsigned startSlice,
                      const unsigned xSize,
                      const unsigned ySize,
                      unsigned ***volume,
                      const char *filename){
        std::cerr<<"writing to "<<filename<<std::endl;
        if(!pngWrite(startSlice,xSize,ySize,volume,filename))
                std::cerr<<"ok"<<std::endl;
        else
                std::cerr<<"error!"<<std::endl;
        return;
}

int main(const int argc,const char** argv){
        if(argc<3){
                std::cerr<<"Use -h option to see how to use "<<
                        argv[0]<<"."<<std::endl;
                exit(-1);
        }
        for(int i=1;i<argc;++i){
                if(!strcmp(argv[i],"-h")||!strcmp(argv[i],"--help")){
                        std::cerr<<
                                "usage\n"<<argv[0]<<" input output [options]\n"
                                "where options are zero or more of:\n"
                                "-h, --help\t\tshow this message\n";
                        exit(-1);
                }
        }

        // Read slices 0 to 3
        unsigned startSlice=0;
        unsigned numSlices=4;
        unsigned xSize=4;
        unsigned ySize=4;
        // The volumetric data structure to store the read data.
        unsigned ***volume;
        // Initialize the data structure.
        volume=initStructure(xSize,ySize,numSlices);
        // Read data from the volume.
        readVolumetricData(startSlice,numSlices,xSize,ySize,volume);
        // Print data to stdout.
        for(int s=0;s<numSlices;++s){
                std::cout<<"slice "<<s<<":"<<std::endl;
                printSlice(std::cout,s,xSize,ySize,volume);
        }
        saveSlicesToFile(startSlice,xSize,ySize,volume,argv[2]);
        return 0;
}
