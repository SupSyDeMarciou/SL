#ifndef __SL_NOISE_H
#define __SL_NOISE_H

/*
 *  NOISE: basic noise generating functions. 
 *  
 *  TODO:
 *  - Perlin noise
 *  - Octave perlin noise
 *  - Voronoi noise
 *  - Octave voronoi noise
 * 
*/

#include <SL/math/vector.h>



#ifdef SL_IMPLEMENTATION
SL_header float perlin2D(fv2 p)
{
    SL_terminate(-1, "[UNIMPLEMENTED]");

    fv2 ip  = SL_fv2floor(p), fp = SL_fv2frac(p);
    // fv2 sfp = ...
    
}
#endif
#endif // __SL_NOISE_H