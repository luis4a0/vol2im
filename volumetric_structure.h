#ifndef VOL2IM_VOLUMETRIC_STRUCTURE_H
#define VOL2IM_VOLUMETRIC_STRUCTURE_H

#define voxel_t unsigned char

// Returns an empty data structure. The inputs are the desired dimensions.
voxel_t*** initStructure(const unsigned,const unsigned,const unsigned);

#endif // VOL2IM_VOLUMETRIC_STRUCTURE_H
