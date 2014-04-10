/*

vol2im embeds volumetric data in images. Copyright (C) 2014 Luis Peñaranda.

This program is free software: you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <stdio.h>
#include <string.h>
#include "volumetric_structure.h"
#include "png_backend.h"
#include "stdout_backend.h"
#include "png_frontend.h"
#include "stpng8_frontend.h"
#include "stpng816_frontend.h"

/* The frontend specifies the input file type of the program. */
typedef enum{
        HMAP_PNG_GRAY,  /* a height map in a gray png image */
        FOUR_SLICES_PNG_GRAY,   /* four slices in gray png images */
        SIXTEEN_SLICES_PNG_GRAY /* sixteen slices produce Warhol-like output! */
}frontend;

/* The backend specifies the output file type. */
typedef enum{
        PNG_RGBA,
        PNG_RGB,
        JPEG_RGB,
        STDOUT
}backend;

int license(char *progname,FILE *f){
        fprintf(f,"%s copyright (C) 2014 Luis Peñaranda. This program comes with ABSOLUTELY NO WARRANTY. This is free software, and you are welcome to redistribute it under certain conditions. For details, see the file COPYING, included with %s, or refer to http://www.gnu.org/licenses to obtain the license.\n",progname,progname);
    return 0;
}

int main(const int argc,const char** argv){
        /* Name of the program. */
        char *progname="vol2im";
        /* Default options. */
        frontend fe;
        backend be;
        int inFilePos,outFilePos,i;
        /* Read the command line. */
        if(argc<2){
                fprintf(stderr,"Use -h option to see how to use %s.\n",argv[0]);
                return -1;
        }
        inFilePos=1;
        outFilePos=2;
        fe=HMAP_PNG_GRAY;
        be=PNG_RGBA;
        for(i=1;i<argc;++i){
                if(!strcmp(argv[i],"-l")||!strcmp(argv[i],"--license")){
                        license(progname,stderr);
                        return -1;
                }
                if(!strcmp(argv[i],"-h")||!strcmp(argv[i],"--help")){
                        fprintf(stderr,"usage: %s [-i input|-4i inputs|-16i inputs] [-o output] [options]\nwhere options are zero or more of:\n-p, --print\tprint the data structure to stdout\n-h, --help\tshow this message\n-l, --license\tshow information about the license\n",argv[0]);
                        return -2;
                }
                if(!strcmp(argv[i],"-i")){
                        fe=HMAP_PNG_GRAY;
                        inFilePos=i+1;
                }
                if(!strcmp(argv[i],"-4i")){
                        fe=FOUR_SLICES_PNG_GRAY;
                        inFilePos=i+1;
                }
                if(!strcmp(argv[i],"-16i")){
                        fe=SIXTEEN_SLICES_PNG_GRAY;
                        inFilePos=i+1;
                }
                if(!strcmp(argv[i],"-p")||!strcmp(argv[i],"--print"))
                        be=STDOUT;
                if(!strcmp(argv[i],"-o")){
                        be=PNG_RGBA;
                        outFilePos=i+1;
                }
        }

        unsigned startSlice=0;
        unsigned numSlices,xSize,ySize;
        /* The volumetric data structure to store the read data. */
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
                case SIXTEEN_SLICES_PNG_GRAY:
                        stpng8Read16(&xSize,
                                     &ySize,
                                     &volume,
                                     argv+inFilePos);
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
