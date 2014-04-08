#include "png_frontend.h"
#include <png.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// http://www.libpng.org/pub/png/libpng-1.2.5-manual.html#section-3
int pngRead(unsigned *numSlices,
            unsigned *xSize,
            unsigned *ySize,
            voxel_t ****volume,
            const char *filename){

        int i,j,k;
        // Open file.
        FILE *fp=fopen(filename,"rb");
        if(!fp)
                return -1;
        // Read the header of the file.
        unsigned char header[8];
        png_size_t number_to_check=8;
        if(fread(header,1,8,fp)!=(unsigned long)ftell(fp))
                return -2;
        // Check the file is valid.
        if(png_sig_cmp(header,0,number_to_check))
                return -3;
        // Initialize.
        png_structp png_ptr=
                png_create_read_struct(PNG_LIBPNG_VER_STRING,NULL,NULL,NULL);
        if(!png_ptr)
                return -4;
        //
        png_infop info_ptr=png_create_info_struct(png_ptr);
        if(!info_ptr){
                png_destroy_read_struct(&png_ptr,
                                        (png_infopp)NULL,
                                        (png_infopp)NULL);
                return -5;
        }
        //
        if(setjmp(png_jmpbuf(png_ptr)))
                return -6;
        //
        png_init_io(png_ptr,fp);
        png_set_sig_bytes(png_ptr,number_to_check);
        png_read_info(png_ptr,info_ptr);
        png_byte color_type=png_get_color_type(png_ptr,info_ptr);
        png_byte bit_depth=png_get_bit_depth(png_ptr,info_ptr);
        *xSize=png_get_image_width(png_ptr,info_ptr);
        *ySize=png_get_image_height(png_ptr,info_ptr);
        *numSlices=(unsigned)(powf(2.f,png_get_bit_depth(png_ptr,info_ptr)));

        png_read_update_info(png_ptr,info_ptr);

        *volume=initStructure(*xSize,*ySize,*numSlices);
        if(setjmp(png_jmpbuf(png_ptr)))
                return -7;

        int pixel_size=1;
        png_bytep row_pointers[*ySize];
        for(i=0;i<*ySize;++i){
                row_pointers[i]=
                        (png_bytep)png_malloc(png_ptr,(*xSize)*pixel_size);
                        //(png_byte*)malloc(png_get_rowbytes(png_ptr,info_ptr));
        }
        //png_set_rows(png_ptr,info_ptr,row_pointers);
        png_read_image(png_ptr,row_pointers);
        for(i=0;i<*ySize;++i){
                for(j=0;j<*xSize;++j)
                        for(k=0;k<*numSlices;++k){
                                if(row_pointers[i][j]>=k)
                                        (*volume)[k][j][i]=255;
                                else
                                        (*volume)[k][j][i]=0;
                        }
        }

        fclose(fp);
        return 0;
}
