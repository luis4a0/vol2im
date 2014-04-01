#ifndef VOL2IM_PNG_BACKEND_H
#define VOL2IM_PNG_BACKEND_H

#include "volumetric_structure.h"

int pngWrite(const unsigned,
             const unsigned,
             const unsigned,
             voxel_t***,
             const char*);

#endif // VOL2IM_PNG_BACKEND_H
