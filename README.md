# SupSyLibraries
This C library acts as a bundle of multiple useful libraries for helping with linear arithmetics, generic structures and others.

# Dependencies
This library is entirely written by myself, no dependencies to be found ! However, it was only tested with Clang and GCC for C23.

# How to use
This library is header only in the vain of the STB libraries. Therefore, you can simply do the following :
```C
#define SL_IMPLEMENTATION       // Define this marco to enable the definitions of every function in the SL. Define it only once in your project to avoid redefinitions.
#define SL_STRIP_PREFIX         // Define this macro to remove almost every `SL_` or `sl_` prefix (these prefixes act like a namespace)

#include "SL/sl.h"              // Includes everything in the SL as recursive includes to every header
// or
#include "SL/sl_all.h"          // Includes everything in the SL from this single header (which is a concatenation of every file in the library generated automaticaly)
// or
#include "SL/struct/array.h"    // Only includes the relevant headers to make this header work.
```

> ### /!\ Be careful, some files are proceduraly generated and can get quite big so they might slow down your text editor if you open them (particularily `sl_all.h`, `vector.h` and `matrix.h`) /!\

# Structure of the library
## Files
The library is divided into three main modules :
- **Math**: structures and functions which are useful for linear algebra, 3D graphics and basic arithmetic. It contains `math.h`, `vector.h`, `quaternion.h`, `matrix.h`, `block_matrix.h`, `noise.h` and `algorithm.h`
- **Struct**: useful structures, some of which are *generic* and can thus be reused with any user-defined type. It contains `allocator.h`, `array.h`, `list.h`, `dict.h`, `arena.h`, `string.h` and `tupple.h`
- **Misc**: miscellaneous utility files which are only bundled together because they didn't fit the above two categories. It contains `async.h`, `io.h`, `log.h`, `tui.h`

Additionnaly `base.h` defines shared definitions accross most headers.

## Synthax overview
Everything in the library is prefixed by either `SL_` (functions and macros) or `sl_` (types). This prefix, serving as a namespace, can be removed by defining `SL_STRIP_PREFIX`. This system is heavily inspired by Tsoding's nob.h.

The code base is written with the following synthax :
- Types are `snake_case`
- Constants and global static variables are `SNAKE_CASE`
- Functions are by default `camelCase`, and their "*overloads*" are separated using an underscore (ex: `functionName_overload(...)`). This allows me to synthaxically group similar functions together. 
- Functions operating on a specific type are prefixed by the type name (ex: `fv2add(...)` does an addition between two 2D vectors of floats)
- Some types have contructors which are either called `type {type}_(...)` (may have an overload letter in place of the `_`) or `type {type}Create(...)` depending on wether the initialization is done at compile-time or during the run-time. In these instances the `{type}` may become `camelCase` instead of `snake_case`.
- Declarative macros used to define new compound types like dynamic arrays or linked lists use are called `DEF_{compound_type}(...)`.

# Content overview
### *base.h*
This file serves as the lowest level include, thus it includes the standard library headers and defines constructs shared by the other headers.

It defines many aliases to builtin types (`int{n}_t -> i{n}`, `uint{n}_t -> u{n}`, `float -> f32`, `double -> f64`, *etc...*), and their pointer types (the generic structures like dynamic arrays heavely rely on having *typedef-ed* names each type so this is a compromise). It defines :
- `usize`, `ssize`: aliases for `size_t` and `ssize_t`. 
- `i8`, `i16`, `i32`, `i64`, `u8`, `u16`, `u32`, `u64`, `uint`: aliases for builtin sized integer types.
- `f16`, `f32`, `f64`, `f128`: aliases for floating-point number types.
- `ch8`, `ch16`, `ch32`: aliases for sized character types.

It also defines the error management constructs (`SL_ERROR`, `SL_strerr`) and memory-related constructs like the macro `new(...)` which allocates and fills the allocation with its input or `memclone` (on which `new` is based).

## *Math*

The math module defines vector, matrice and quaternion structures and operations, as well as utilities for basic number manipulation and noise generation.

A convention is used troughout the module :
- `s` suffix : overload of a binary operation on which the second operand is now a scalar (ex: `fv2mul` does component-wise multiplication of two 2D float vectors, whereas `fv2muls` scaled the 2D vector by a float).
- `_u` suffix : at least one operand is assumed to be of unit length (useful to reduce normalisation operations when unecessary).
- `S` prefix or suffix : the first or second operand is scaled by a scalar value.
- `M` prefix or suffix : the first or second operand is multiplied by a value of the same type.

**(i) The files `vector.h`, `quaternion.h` and `matrix.h` are proceduraly generated using the scripts in the `/generate` folder.**

### *math.h*

This file defines constants and operations on core C types like `u32` and `double` (`d`). 

> The constants:
> `PI`, `TAU` *(2 pi)*, `E`, `PHI` *(golden ratio)*, `DEG_TO_RAD` *(conversion between degree and radians)*, `RAD_TO_DEG`.

> The operations :
> - Min and max: `SL_umin`, `SL_u64min`, `SL_imin`, `SL_i64min`, `SL_fmin`, `SL_dmin`, `SL_umax`, `SL_u64max`, `SL_imax`, `SL_i64max`, `SL_fmax`, `SL_dmax`.
> - Sign: `SL_isign`, `SL_i64sign`, `SL_fsign`, `SL_dsign`.
> - Bit reinterpretation: `SL_inplaceU32ToFloat`, `SL_inplaceFloatToU32`, `SL_inplaceU64ToDouble`, `SL_inplaceDoubleToU64`, `SL_inplaceU32ToFloat01` *(only uses bits in the mantissa to keep output normalized)*, `SL_inplaceU64ToDouble01`.
> - Random: `SL_u32hash_PCG`, `SL_u32srand`, `SL_u32rand`, `SL_u32rand_in`, `SL_frand`, `SL_drand`, `SL_frand_in`, `SL_drand_in`.
> - `SL_fstep`, `SL_dstep`, `SL_flerp`, `SL_dlerp`, `SL_fclamp`, `SL_dclamp`.

### *vector.h*

This file defines vectors of 2, 3, 4 and an arbitrary number of components for the types `bool` (`b`), `i8`, `u8`, `i16`, `u16`, `i32`, `u32`, `i64`, `u64`, `float` (`f`) and `double` (`d`). Therefore :
- `fv2` is a vector of two floats.
- `bv4` is a vector of four booleans.
- `i64v` is a vector of i64 of arbitrary component count.

For a vector of type `T` and dimension 4, the structure is:
```C
typedef union {
    T data[4];
    struct {
        union { T x, r, u; };
        union { T y, g, v; };
        union { T z, b, s; };
        union { T w, a, t; };
    };
    struct {
        union { T __x0, __r0, __u0; };
        union { Tv2 yz, gb, vs; };
        union { T __w0, __a0, __t0; };
    };
    struct {
        union { Tv2 xy, rb, uv; };
        union { Tv2 zw, ba, st; };
    };
    struct {
        union { Tv3 xyz, rgb, uvs; };
        union { T __w1, __a1, __t1; };
    };
    struct {
        union { T __x1, __r1, __u1; };
        union { Tv3 yzw, gba, vst; };
    };
} Tv4;
```
For a vector of type `T` and arbitrary dimension, the structure simply is:
```C
typedef struct {
    const usize count; 
    T *data;
} Tv;
```

The ***SL*** makes heavy use of `union` to create aliases in arithmetic types, so that a `fv4` may be used as an extended 3D coordinate (`.xyzw`), a color (`.rgba`) or a 4D UV coordinate (`.uvst`). In addition, you can extract sub-vectors from largers ones using this `union` trick (`.yz` extracts the middle `fv2` of a `fv4`) which acts as a weak form of the GLSL swizzling.

> Many operations are defined on vectors :  
> `add` *(addition)*, `addS`, `addSM`, `Sadd`, `sub` *(subtraction)*, `subS`, `subSM`, `Ssub`,
> `mul` *(multiplication)*, `muls`, `div` *(division)*, `divs`, `equ` *(equality)*, `neg` *(negation)*, `abs` *(absolute value)*, `mix` *(addition of vectors, each scaled by a scalar)*, `min`, `max`, [**`mul`, `div`, `abs`, `min` and `max` are component-wise operations**],
> `dot` *(dot product)*, `len` *(euclidean length)*, `len_sqr` *(squared euclidean length)*, `len_max` *(infinite length, aka. max component)*, `len_manh` *(manhattan or taxicab length)*, `dist` *(length of the difference of two vectors)*.

> In addition, some functions are only defined for specifix types of vectors:
> - Non-boolean types - `refl{_u}` *(reflection around axis)*, `align{_u}` *(projection on axis)*, `proj{_u}` *(projection on plane orthogonal to axis)*, `mod` *(modulus)*, `mods`.
> - Real types - `norm` *(normalization)*, `floor`, `ceil`, `frac` *(fractional part)*, `lerp` *(linear interpolation)*, `serp` *(spherical interpolation)*. **`floor`, `ceil` and `frac` are component-wise operations**.
> - Integer types - `and`, `or`, `xor`, `not`, `lshft` *(left shift)*, `lshfts`, `rshft` *(right shift)*, `rshfts`. **These are component-wise operations**.
> - 2D and 3D signed types - `cross` *(cross product)*. **In 2D, returns the *sin* of the angle formed by the two vectors**.
> - `fv2`, `dv2` - `angle`, `from_angle`, `rot`, `rot_sc`, `rot_cs`: vector pointing *angle* ways from positive X direction, angle from the positive X direction, rotate vector by angle or (*sin*, *cos*) pair.
> - `fv3`, `dv3` - `from_yawPitch`

### *quaternion.h*
This file defines quaternions of floats (`fq`) and doubles (`dq`). These are mainly used for their interesting properties regarding 3D rotations.  
Here is the definition of `fq` (`dq` is the same but with `double`): 
```C
typedef union {
    float data[4];
    struct { float a, b, c, d; };
    struct { float w, x, y, z; };
    struct { float r; union { fv3 iv; struct { float i, j, k; }; }; };
    fv4 fv4;
} fq;
```
`union`s are once again used for aliasing as it can be useful to consider quaternions either as a 4D vector or as a real component and an imaginary 3D vector.

> Quaternions implement the following operations:  
> `equ`, `add`, `sub`, `mul`, `muls`, `neg`, `len_sqr`, `len`, `norm`, `trsp` *(transposition)*, `inv` *(inversion)*, `div`, `exp` *(**e** raised to the operand)*, `ln` *(natural logarithm of the operand)*, `ln_u`, `pow` *(first operand to the power of the second operand)*, `pow_u`, `rot` *(rotation of a 3D vector)*, `serp`, `serp_u`.

> The following conversions are also defined for quaternions and 3D rotation representations:  
> `{from|to}_euler` *(euler angles in roll-pitch-yaw order)*, `{from|to}_axisAngle`, `from_fromTo` *(rotation to align starting vector to destination vector)*

### `matrix.h`

I can't be bothered for now...

## *Struct*

This module defines generic structure types like dynamic arrays, linked lists, dictionnaries and tupples, as well as custom allocators and sized strings.

All of the generic types can be configured to use a custom allocator when they need to expand/free their memory footprint.


### *array.h*

This file defines the dynamic array type and the slice type, as well as and some functions to manipulate them in a type independent manner. All read-only functions can be used with both arrays or slices indiscriminetly.  
To define a new array, use the declarative macro:
```C
// Define an array of type T
SL_DEF_ARRAY(T);

// The array type and slice type can now be accessed using
SL_array(T) array = SL_arrayCreate(...);
SL_slice(T) slice = SL_slicev(T, ...); 
```





## BONUS: Procedural generation of header files