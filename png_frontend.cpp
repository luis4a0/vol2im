#include "png_frontend.h"
#include "volumetric_structure.h"
#include <png.h>
#include <stdint.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>

// http://www.libpng.org/pub/png/libpng-1.2.5-manual.html#section-3
int pngRead(unsigned *numSlices,
            unsigned *xSize,
            unsigned *ySize,
            unsigned ****volume,
            const char *filename){

        FILE *fp=fopen(filename,"rb");
        if(!fp)
                return -1;
        /*png_bytep header;
        png_size_t number_to_check=8;
        fread(header,1,number_to_check,fp);
        int is_png=!png_sig_cmp(header,0,number_to_check);
        if(!is_png)
                return -2;
        */

        png_structp png_ptr=png_create_read_struct
                (PNG_LIBPNG_VER_STRING,NULL,NULL,NULL);
        if(!png_ptr)
                return -3;

        png_infop info_ptr=png_create_info_struct(png_ptr);
        if(!info_ptr){
                png_destroy_read_struct(&png_ptr,
                                (png_infopp)NULL,(png_infopp)NULL);
                return -4;
        }

        png_infop end_info=png_create_info_struct(png_ptr);
        if(!end_info){
                png_destroy_read_struct(&png_ptr, &info_ptr,(png_infopp)NULL);
                return -5;
        }

        png_init_io(png_ptr,fp);
        //png_set_sig_bytes(png_ptr,number_to_check);
        png_read_png(png_ptr,info_ptr,PNG_TRANSFORM_IDENTITY,NULL);
        //png_bytep *row_pointers[height];
        *xSize=png_get_image_width(png_ptr,info_ptr);
        *ySize=png_get_image_height(png_ptr,info_ptr);
        *numSlices=8*png_get_bit_depth(png_ptr,info_ptr);
        int pixel_size=1;
        png_bytep row_pointers[*ySize];
        for(int i=0;i<*ySize;++i)
                row_pointers[i]=
                        (png_bytep)png_malloc(png_ptr,(*xSize)*pixel_size);
        png_set_rows(png_ptr,info_ptr,row_pointers);
        // TODO: finish here!



        // Simulate reading a 4x4x4 cube. TODO: really read the file.
        *numSlices=4;
        *xSize=4;
        *ySize=4;
        *volume=initStructure(*xSize,*ySize,*numSlices);
        (*volume)[1][2][3]=1;
        (*volume)[3][2][3]=1;

        fclose(fp);
        return 0;
}
