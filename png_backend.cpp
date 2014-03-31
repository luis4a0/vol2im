#include "png_backend.h"
#include <png.h>
#include <stdint.h>
#include <cstdlib>
#include <cstdio>

// http://www.libpng.org/pub/png/libpng-1.2.5-manual.html#section-4
int pngWrite(const unsigned startSlice,
             const unsigned xSize,
             const unsigned ySize,
             unsigned ***volume,
             const char *filename){

        FILE *fp=fopen(filename,"wb");
        if(!fp)
                return -1;

        png_structp png_ptr=png_create_write_struct
                (PNG_LIBPNG_VER_STRING,NULL,NULL,NULL);
        if(!png_ptr)
                return -2;

        png_infop info_ptr=png_create_info_struct(png_ptr);
        if(!info_ptr){
                png_destroy_write_struct(&png_ptr,(png_infopp)NULL);
                return -3;
        }
        if (setjmp(png_jmpbuf(png_ptr))){
                png_destroy_write_struct(&png_ptr,&info_ptr);
                fclose(fp);
                return -4;
        }

        png_set_IHDR(png_ptr,
                     info_ptr,
                     xSize, // width
                     ySize, // height
                     8, // depth
                     PNG_COLOR_TYPE_RGB_ALPHA, // 4-channel=RGBA
                     PNG_INTERLACE_NONE,
                     PNG_COMPRESSION_TYPE_DEFAULT,
                     PNG_FILTER_TYPE_DEFAULT);

        png_set_compression_level(png_ptr,0);

        int pixel_size=4;
        png_byte **row_pointers=(png_byte**)
                png_malloc(png_ptr,ySize*sizeof(png_byte*));
        for (int y=0;y<ySize;++y){
                png_byte *row=(png_byte*)
                        png_malloc(png_ptr,sizeof(uint8_t)*xSize*pixel_size);
                row_pointers[y]=row;
                for(int x=0;x<xSize;++x){
                        *row++=volume[startSlice  ][x][y]*255;
                        *row++=volume[startSlice+1][x][y]*255;
                        *row++=volume[startSlice+2][x][y]*255;
                        *row++=volume[startSlice+3][x][y]*255;
                }
        }

        png_init_io(png_ptr,fp);
        png_set_rows(png_ptr,info_ptr,row_pointers);
        png_write_png(png_ptr,info_ptr,PNG_TRANSFORM_IDENTITY,NULL);

        fclose(fp);

        for(int y=0;y<ySize;y++){
                png_free(png_ptr,row_pointers[y]);
        }
        png_free(png_ptr,row_pointers);

        return 0;
}
