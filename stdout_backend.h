#ifndef VOL2IM_STDOUT_BACKEND
#define VOL2IM_STDOUT_BACKEND

#include <stdio.h>
#include "volumetric_structure.h"

void printSlices(FILE*,const unsigned,const unsigned,const unsigned,voxel_t***);

#endif /* VOL2IM_STDOUT_BACKEND */
