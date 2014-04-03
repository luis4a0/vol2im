#ifndef VOL2IM_STDOUT_BACKEND
#define VOL2IM_STDOUT_BACKEND

#include <iostream>
#include "volumetric_structure.h"

std::ostream& printSlices(std::ostream&,
                          const unsigned,
                          const unsigned,
                          const unsigned,
                          voxel_t***);

#endif // VOL2IM_STDOUT_BACKEND
