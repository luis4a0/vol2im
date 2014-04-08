#include <stdio.h>
#include <string.h>
#include "volumetric_structure.h"
#include "png_backend.h"
#include "stdout_backend.h"
#include "png_frontend.h"
#include "stpng8_frontend.h"

// The frontend specifies the input file type of the program.
typedef enum{
        HMAP_PNG_GRAY,  // a height map in a gray png image
        FOUR_SLICES_PNG_GRAY  // four slices in gray png images
}frontend;

// The backend specifies the output file type.
typedef enum{
        PNG_RGBA,
        PNG_RGB,
        JPEG_RGB,
        STDOUT
}backend;

int main(const int argc,const char** argv){
        // Default options.
        frontend fe=HMAP_PNG_GRAY;
        backend be=PNG_RGBA;
        int inFilePos=1;
        int outFilePos=2;
        int i;
        // Read the command line.
        if(argc<2){
                fprintf(stderr,"Use -h option to see how to use %s.\n",argv[0]);
                return -1;
        }
        for(i=1;i<argc;++i){
                if(!strcmp(argv[i],"-h")||!strcmp(argv[i],"--help")){
                        fprintf(stderr,"usage: %s [-i input|-4i inputs] [-o output] [options]\nwhere options are zero or more of:\n-p\t\tprint the data structure to stdout\n-h, --help\t\tshow this message\n",argv[0]);
                        return -1;
                }
                if(!strcmp(argv[i],"-i")){
                        fe=HMAP_PNG_GRAY;
                        inFilePos=i+1;
                }
                if(!strcmp(argv[i],"-4i")){
                        fe=FOUR_SLICES_PNG_GRAY;
                        inFilePos=i+1;
                }
                if(!strcmp(argv[i],"-p"))
                        be=STDOUT;
                if(!strcmp(argv[i],"-o")){
                        be=PNG_RGBA;
                        outFilePos=i+1;
                }
        }

        unsigned startSlice=0;
        unsigned numSlices,xSize,ySize;
        // The volumetric data structure to store the read data.
        voxel_t ***volume;
        switch(fe){
                case HMAP_PNG_GRAY:
                        pngRead(&numSlices,
                                &xSize,
                                &ySize,
                                &volume,
                                argv[inFilePos]);
                        break;
                case FOUR_SLICES_PNG_GRAY:
                        stpng8Read(&xSize,
                                   &ySize,
                                   &volume,
                                   argv[inFilePos],
                                   argv[inFilePos+1],
                                   argv[inFilePos+2],
                                   argv[inFilePos+3]);
                        break;
                default:
                        fprintf(stderr,"no input type specified\n");
                        return -1;
                        break;
        }
        switch(be){
                case PNG_RGBA:
                        pngWrite(startSlice,
                                 xSize,
                                 ySize,
                                 volume,
                                 argv[outFilePos]);
                        break;
                case STDOUT:
                        printSlices(stdout,numSlices,xSize,ySize,volume);
                        break;
                default:
                        fprintf(stderr,"no output type specified\n");
                        return -1;
                        break;
        }
        return 0;
}
