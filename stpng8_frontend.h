#ifndef VOL2IM_STPNG8_FRONTEND_H
#define VOL2IM_STPNG8_FRONTEND_H

#include "volumetric_structure.h"

int stpng8Read(unsigned*,
               unsigned*,
               voxel_t****,
               const char*,
               const char*,
               const char*,
               const char*);

#endif // VOL2IM_STPNG8_FRONTEND_H
