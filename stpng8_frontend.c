#include "png_frontend.h"
#include <png.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Open one png file and return its size.
int pngSize(unsigned *xSize,unsigned *ySize,const char *filename){
        int i,j;
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
        fclose(fp);
}

// Read one slice from the file and put it on the structure. The file is
// assumed to be a grayscale png.
int stpng8ReadSlice(unsigned nSlice,
                    unsigned xSize,
                    unsigned ySize,
                    voxel_t ****volume,
                    const char *filename){
        int i,j;
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

        png_read_update_info(png_ptr,info_ptr);

        if(setjmp(png_jmpbuf(png_ptr)))
                return -7;

        int pixel_size=1;
        png_bytep row_pointers[ySize];
        for(i=0;i<ySize;++i){
                row_pointers[i]=
                        (png_bytep)png_malloc(png_ptr,xSize*pixel_size);
                        //(png_byte*)malloc(png_get_rowbytes(png_ptr,info_ptr));
        }
        //png_set_rows(png_ptr,info_ptr,row_pointers);
        png_read_image(png_ptr,row_pointers);
        for(i=0;i<ySize;++i)
                for(j=0;j<xSize;++j)
                        (*volume)[nSlice][j][i]=row_pointers[i][j];

        fclose(fp);
        return 0;
}

int stpng8Read(unsigned *xSize,
               unsigned *ySize,
               voxel_t ****volume,
               const char *filename1,
               const char *filename2,
               const char *filename3,
               const char *filename4){
        // Determine the size of the first image (others must have the same
        // size).
        pngSize(xSize,ySize,filename1);
        // Init the volumetric structure, with only four slices.
        *volume=initStructure(*xSize,*ySize,4);
        stpng8ReadSlice(0,*xSize,*ySize,volume,filename1);
        stpng8ReadSlice(1,*xSize,*ySize,volume,filename2);
        stpng8ReadSlice(2,*xSize,*ySize,volume,filename3);
        stpng8ReadSlice(3,*xSize,*ySize,volume,filename4);

        return 0;
}
