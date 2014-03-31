#include <iostream>
#include <cstring>
#include "png_backend.h"
#include "png_frontend.h"

void readVolumetricData(unsigned *numSlices,
                        unsigned *xSize,
                        unsigned *ySize,
                        unsigned ****volume,
                        const char *filename){
        std::cerr<<"reading from "<<filename<<std::endl;
        if(!pngRead(numSlices,xSize,ySize,volume,filename))
                std::cerr<<"ok"<<std::endl;
        else
                std::cerr<<"error!"<<std::endl;
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

typedef enum{
        PNG_RGBA,
        PNG_RGB,
        JPEG_RGB
}backend;

typedef enum{
        HMAP_PNG_GRAY,
        HMAP_PNG_ALPHA
}frontend;

int main(const int argc,const char** argv){
        // Default options.
        frontend fe=HMAP_PNG_GRAY;
        backend be=PNG_RGBA;
        // Read the command line.
        if(argc<2){
                std::cerr<<"Use -h option to see how to use "<<
                        argv[0]<<"."<<std::endl;
                return -1;
        }
        for(int i=1;i<argc;++i){
                // TODO: choose frontend and backend.
                if(!strcmp(argv[i],"-h")||!strcmp(argv[i],"--help")){
                        std::cerr<<
                                "usage: "<<argv[0]<<" input output [options]\n"
                                "where options are zero or more of:\n"
                                "-h, --help\t\tshow this message\n";
                        return -1;
                }
        }

        // Read slices 0 to 3
        unsigned startSlice=0;
        unsigned numSlices,xSize,ySize;
        // The volumetric data structure to store the read data.
        unsigned ***volume;
        readVolumetricData(&numSlices,&xSize,&ySize,&volume,argv[1]);
        // Print data to stdout.
        for(int s=0;s<numSlices;++s){
                std::cout<<"slice "<<s<<":"<<std::endl;
                printSlice(std::cout,s,xSize,ySize,volume);
        }
        saveSlicesToFile(startSlice,xSize,ySize,volume,argv[2]);
        return 0;
}
