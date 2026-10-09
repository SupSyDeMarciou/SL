# SupSyLibraries
This C library acts as a bundle of multiple useful libraries for helping with linear arithmetics, generic structures and others.

# Dependencies
This library is entirely written by myself, no dependencies to be found !

However, depending on the C standard and wether POSIX is used, some functions may not be defined and some macros may not be used. Indeed, a very limited number of functions make use of `_Generic` *(a C23 extension)*, `nanosleep` *(a POSIX standard function)* and some others.

The library has been compiled using **Cland** and **GCC** in projects using `-std=c99`, `-std=c11`, `-std=c23`, `-std=gnu99` and `-std=gnu23`. 

# How to use
This library is header only in the vain of the STB libraries. Therefore, you can simply do the following :
```C
#define SL_IMPLEMENTATION       // Define this marco to enable the definitions of every function in the SL. Define it only once in your project to avoid redefinition conflicts.
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

In addition, some functions and macros are only intended to be used by the **SL** and are thus prefixed with a double underscore (`__SL_...`) to signify this. 

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

All of the generic types can be configured to use a custom allocator when they need to expand/free their memory footprint. This allocator is generaly assigned by using a type's constructor with suffix `A` (ex: `listCreateA(...)` creates an empty list with custom allocator).

### *allocator.h*
This file defines the custom allocator type recognized throughout the **SL** (`SL_allocator`), as well as some macros to incorporate it with the standard library's allocator (refered to as the `std_allocator` or simply `NULL` in the **SL**).

An allocator can be created using the `allocator_(...)` constructor.

> The following macros are defined to create allocator-independent code : 
> - `SL_aalloc(alloc, size)`: allocate a chunk of data.
> - `SL_azalloc(alloc, size)`: allocate a chunk of data which is zero-initialized.
> - `SL_arealloc(alloc, ptr, newsize)`: reallocate an already allocated chunk of data.
> - `SL_afree(alloc, ptr)`: free an allocated chunk of data.
> - `SL_aclone(alloc, ptr, size)`: clone an allocated chunk of data.

### *arena.h*
This file defines a simple implementation of an arena allocator using the **SL** allocator representation. Being a simple arena allocator, it only supports allocating new memory and not freeing parts of memory, however it can grow like a dynamic array by a `page_size` (define as a constructor parameter) everytime an allocation does not fit the current sector.

> The arena implements the following functions :
> - Constructor: `SL_arenaCreate`. 
> - Dstructor: `SL_arenaDestroy`.

### *array.h*

This file defines the dynamic array type (`SL_array(T)`) and the slice type (`SL_slice(T)`), as well as some functions to manipulate them in a type independent manner. All read-only functions can be used with both arrays or slices indiscriminetly, but memory manipulating functions should only be used with dynamic arrays (as slices don't contain the information necessary for memory resizing).  
To define a new array, use the declarative macro:
```C
// Define an array and a slice of type T
SL_DEF_ARRAY(T);

// The array type and slice type can now be accessed using
SL_array(T) array = {0}; // Empty array is a valid array
SL_array(T) array = SL_arrayCreate(T, ...); // Preallocate capacity
SL_slice(T) slice = SL_slicev(T, ...); 

// The `SL_array(T)` and `SL_slice(T)` types have the following definitions :
typedef struct SL_array(T) { 
    T *data;
    usize count;
    usize capa; 
    sl_allocator *alloc;
} SL_array(T);

typedef struct SL_slice(T) { 
    T *data;
    usize count;
} SL_slice(T);
```
As you can see, the array keeps track of its capacity and its allocator to efficiently grow (it doubles in size whenever it's full to allow for amortised *O(1)* insertion).

> The array implements the following functions :
> - Slice constructors: `SL_slice_` *(wrap C array)*, `SL_slicev` *(wrap arbitrary arguments)*, `SL_slicea` *(take a sectionn of a dynamic array)*.
> - Array constructors: `SL_arrayCreate`, `SL_arrayCreateA`, `SL_arrayDestroy`, `SL_arrayClone`, `SL_arrayCloneA`, `SL_arrayWrap`, `SL_arrayWrap_var`, `SL_arrayFrom`, `SL_arrayFromA`, `SL_arrayFrom_var`, `SL_arrayFromA_var`. **The `wrap` functions don't allocate any data but directly use the provided array, the resulting array is thus not necessarily safe when used with memory manipulating functions (especially in the case of wrapped static array)**.
> - Accessors: `SL_arrayFirst` *(pointer to first element)*, `SL_arrayLast` *(pointer to last element)*, `SL_arrayAt` *(pointer to element at index)*.
> - Data insertion/deletion: `SL_arrayInsert_range` *(insert within the array)*, `SL_arrayInsert`, `SL_arrayInsert_var`, `SL_arrayAdd_range` *(insert at end of array)*, `SL_arrayAdd`, `SL_arrayAdd_var`, `SL_arrayCat` *(concatenation)*, `SL_arrayRemove_range` *(remove within the array)*, `SL_arrayRemove`, `SL_arrayRemove_unordered` *(remove without keeping order (faster than ordered remove))*, `SL_arrayPop` *(remove and return value)*.
> - Data rearanging: `SL_arraySort` *(using quicksort)*, `SL_arrayFill` *(set all elements to same value)*, `SL_arrayReserve` *(pre-allocate certain capacity)*.
> - Printing and putting: `SL_arrayPrintf_full`, `SL_arrayPrintf`, `SL_putArray_full`, `SL_putArray`.  

<br>

> In addition, the `SL_aforeach` loop is introduced as a simpler replacement for a `for` loop across every element :
> ```C
> // Create a static array 
> SL_slice(iv2) vectors = SL_slicev(iv2, iv2_right, iv2_up, iv2_one);
> 
> // Print the array before the loop
> SL_put("[BEFORE LOOP] vectors = ", SL_putArray_full(vectors, FMT_V2("%d"), vector, XPD_V2(*vector)), "\n");
> // Expect: "[BEFORE LOOP] vectors = array[v2(1, 0), v2(0, 1), v2(1, 1)]\n"
> 
> SL_aforeach(var, vectors) // Litteraly "for each `vector` in `vector` do {...}"
> {
>     if (aindex(var) == 1 && var->y == 0) *var = iv2_(5, 5);
>     //  ~~~~~~~~~~~~~~
>     //  Litteraly "index of variable `vector` in the looping array" 
> }
> // Print the array after the loop
> SL_put("[AFTER LOOP] vectors = ", SL_putArray_full(vectors, FMT_V2("%d"), vector, XPD_V2(*vector)), "\n");
> // Expect: "[AFTER LOOP] vectors = array[v2(1, 0), v2(5, 5), v2(1, 1)]\n"
> //                                                 ~~~~~~~~
> ```
> `SL_aforeach` related additions:  
> - `SL_aindex` *(index of loop variable in loop array)*
> - `SL_aindex_in` *(index of a variable in an array)*


### *list.h*

This file defines the linked list type (`SL_list(T)`) and the doubly linked list type (`SL_dlist(T)`), as well as some functions to manipulate them in a type independent manner. Every function appart from constructors can be called with linked lists and doubly linked lists indiscriminetly. 
To define a new list, use the declarative macro:
```C
// Define an list and a dlist of type T
SL_DEF_LIST(T);

// The list type and dlist type can now be accessed using
SL_list(T)  list  = {0}; // Empty list is a valid list
SL_dlist(T) dlist = SL_dlistCreateA(T, ...); // Create list with allocator assigned

// The `SL_list(T)` and `SL_dlist(T)` types have the following definitions :
typedef struct T_list_node { 
    struct T_list_node *next;
    T data; 
} T_list_node;
typedef struct SL_list(T) { 
    T_list_node *first, *last; 
    usize count; 
    sl_allocator *alloc; 
} SL_list(T);

typedef struct T_dlist_node {
    struct T_dlist_node *next, *prev; 
    type data;
} T_dlist_node;
typedef struct SL_dlist(T) {
    T_dlist_node *first, *last; 
    usize count; 
    sl_allocator *alloc; 
} SL_dlist(T)
```
The list and dlist types have the same structure, only the associated node structures change to either only reference the next item *(list)* or both the previous and next item *(dlist)*.

> The array implements the following functions :
> - Constructors/Destructors: `SL_listCreateA`, `SL_dlistCreateA`, `SL_listClear`.
> - Accessors: `SL_listFirst` *(pointer to first element)*, `SL_listLast` *(pointer to last element)*, `SL_listAt` *(pointer to element at index)*.
> - Data insertion/deletion: `SL_listInsert` *(insert within the list)*, `SL_listAdd` *(insert at end of list)*, `SL_listAdd_first` *(insert at start of list)*, `SL_listRemove` *(remove within the list)*, `SL_listRemove_ref`, `SL_listPop` *(remove and return value)*.
> - Printing and putting: `SL_listPrintf_full`, `SL_listPrintf`, `SL_putList_full`, `SL_putList`.

<br>

> In addition, the `SL_lforeach` loop is introduced as a simpler replacement for a `for` loop across every element :
> ```C
> // Create a simple linked list 
> SL_list(iv2) vectors = {0};
> SL_listAdd(vectors, iv2_right);
> SL_listAdd(vectors, iv2_up);
> SL_listAdd(vectors, iv2_one);
> 
> // Print the list before the loop
> SL_put("[BEFORE LOOP] vectors = ", SL_putList_full(vectors, FMT_V2("%d"), vector, XPD_V2(*vector)), "\n");
> // Expect: "[BEFORE LOOP] vectors = list[v2(1, 0), v2(0, 1), v2(1, 1)]\n"
> 
> SL_lforeach(var, vectors) // Litteraly "for each `vector` in `vector` do {...}"
> {
>     if (lindex(var) == 1 && var->y == 0) *var = iv2_(5, 5);
>     //  ~~~~~~~~~~~~~~
>     //  Litteraly "index of variable `vector` in the looping list" 
> }
> // Print the list after the loop
> SL_put("[AFTER LOOP] vectors = ", SL_putList_full(vectors, FMT_V2("%d"), vector, XPD_V2(*vector)), "\n");
> // Expect: "[AFTER LOOP] vectors = list[v2(1, 0), v2(5, 5), v2(1, 1)]\n"
> //                                                 ~~~~~~~~
> ```
> `SL_lforeach` related additions:
> - `SL_lindex` *(index of loop variable in loop array)*
> - `SL_lnext` *(pointer to element after loop variable)*
> - `SL_dlprev` *(pointer to element before loop variable)*

### *dict.h*

This file defines the dictionnary type (`SL_dist(K, T)`) as well as some functions to manipulate them in a type independent manner.
To define a new dictionnary, use the declarative macro:
```C
// Define a dictionnary with key of type K and value of type T
SL_DEF_DICT(K, T);

// The dict type can now be accessed using
SL_dict(K, T) dict = SL_dictCreate(K, T, ...); // Create a dictionnary with pre-allocated buckets

// The `SL_dict(K, T)` type has the following definition :
typedef struct SL_dict(K, T)_bucket { 
    struct SL_dict(K, T)_bucket *next; 
    K key;
    T value;
} SL_dict(K, T)_bucket; // Basicaly a linked list node

typedef struct SL_dict(K, T) {
    SL_dict(K, T)_bucket **data;
    usize count, capa;
    SL_allocator *alloc;
    
    usize (*hash)(const K *);
    int   (*cmp)(const K *, const K *);
} SL_dict(K, T)
```
**/!\\ THE EMPTY DICT IS NOT A VALID DICT /!\\**  
The dictionnary keeps track of a key comparison function and a key hashing function. When using the standard constructors, the functions declared using `SL_DEF_CMP_FUNC` and `SL_DEF_HASH_FUNC` for the considered key type. These can be overriden using `SL_dictCreate_full` :
```C
SL_DEF_CMP_FUNC(K, key_a, key_b) {
    return *key_a == *key_b;
}
SL_DEF_HASH_FUNC(K, key) {
    return (usize)key ^ ((usize)key << 8);
}

SL_dict(K, T) dict_basic = SL_dictCreate(K, T, 256);
// <=>
SL_dict(K, T) dict_specific = SL_dictCreate_full(K, T, K_cmp, K_hash, 256);
```

> The array implements the following functions :
> - Constructors/Destructors: `SL_dictCreate`, `SL_dictCreate_full` *(specify hash and comparison functions)*, `SL_dictCreateA`, `SL_dictCreateA_full`, `SL_dictClear` *(free buckets)*, `SL_dictDestroy` *(free every resource taken by dict)*.
> - Data accessing/insertion/deletion: `SL_dictGet` *(pointer to element associated with a key)*, `SL_dictAdd` *(insert value associated with a key)*, `SL_dictRemove` *(remove value associated with a key)*, `SL_dictKey` *(get key associated with value reference)*.
> - Using dictionnary functions: `SL_dictHash` *(use dict's hash function)*, `SL_dictHash2`, `SL_dictCmp` *(use dict's comparison function)*, `SL_dictCmp2`.
> - Printing and putting: ***TO COMPLETE***

<br>

> In addition, the `SL_dforeach` loop is introduced as a simpler replacement for a `for` loop across every element :
> ```C
> SL_dict(SL_ptr(char), iv2) vectors = SL_dictCreate(SL_ptr(char), iv2, 3);
> SL_dictAdd(vectors, "right", iv2_right);
> SL_dictAdd(vectors, "up",    iv2_up);
> SL_dictAdd(vectors, "one",   iv2_one);
> 
> SL_dforeach(pair, vectors) // Litteraly "for each `pair` in `vector` do {...}"
> {
>     if (SL_dictCmp(pair->key, "up") && pair->value.y == 0) pair->value = iv2_(5, 5);
> }
> ```

### *tupple.h*
This file defines tupples of types. It was created as a thought but is never used throughout my projects, I wonder if I should remove it...

### *string.h*
***TODO: WRITE DOCUMENTATION WHEN IT WILL BE MOVED***

## *Misc*

As stated before, this module is a bundle of ideas which are not really connected together in a meaningful way. It touches upon asynchronous programming, IO manipulation, logging and TUI utilities.

### *log.h*
This file defines a simple logger implementation with error levels.
> You can define a logger for a file using :
> ```C
> SL_DEF_LOGGER(logger_name, "Logger Title", SL_LOG_LVL_ERROR);
> //            ^            ^               ^
> //            |            |               Log level
> //            |            Title displayed in logs
> //            Name of the logger variable
>
> // You can now log things
> SL_logI("Information log!");
> SL_logW("Warning log, with a number: %d!", 10);
> SL_logE("Error log!");
> SL_todo("TODO: fix this example"); // The program will terminate on a todo
> ```

### *async.h*
This file defines utilities regarding asynchronous programming.

> When using POSIX, it defines:  
> - `SL_sleep_n` *(sleep nanoseconds)*, `SL_sleep_u` *(sleep microseconds)* and `SL_sleep_m` *(sleep milliseconds)*. **These are alternatives to `nanosleep`**.

> In addition, an alternative synthax for thread instanciation is defined using `SL_DEF_ASYNC`. Here is an example showing everything in action :
> ```C
> // This is an example function we want to call asynchronously
> int foo(int x, bool y) {
>     if (y) return x;
>     SL_sleep_m(1000);
>     return x - 1;
> }
>
> // To make `foo` callable from a different thread, we will create an async caller for `foo` using the following macro
> SL_DEF_ASYNC(foo, int, x, bool, y);
>
> // We can now start a thread running `foo`
> SL_task(foo) fooTask = async(foo)(10, false);
> // Check for task status
> if (SL_taskStatus(fooTask) != SL_TASK_DONE) put("Task not yet complete!\n"); 
> // And join back to get return value and free 
> int return_value;
> if (SL_await(fooTask, &return_value)) 
>     put("Task successfuly completed, returned %d\n", return_value);
> else 
>     put("Task failed!\n");
> ```

### *io.h*
This file defines constructs for string manipulation and basic file manipulation.

> - Temporary and new formatted strings: `SL_tmpf` *(temporary formated)*, `SL_strf` *(new formated)*. **(i) The value of `SL_tmpf` is valid until the next non-empty call**.
> - String manipulation; `SL_strtrsfrm` *(string transform)*, `SL_strupper` *(to uppercase)*, `SL_strlower` *(to lowercase)*, `SL_strstart` *(wether string starts with factor)*, `SL_strend` *(wether string ends with factor)*.
> - Read/write whole files: `SL_readEntireFile`, `SL_writeEntireFile`.

> As a more generic alternative, `io.h` introduces the `sl_stream` structure which abstracts aways the target for `fprintf`/`sprintf` operations. In combination with `gprintf` *(generic printf)* and `SL_vgprintf` *(variadic version)*, it makes code independent of the stream's underlying representation :
> ```C
> sl_stream target = sl_stream(...); // Either another sl_stream, a char* or a FILE*
> gprintf(target, "This would be the same no matter the nature of `target`!\n");
> ```
> ### ***/!\\ `sl_stream` relies on c23 standard for `_Generic` /!\\***

> `io.h` also introduces the *put* method as a generalized *print*. Specificaly, it introduces `SL_gput` *(put with target stream)* and `SL_put` *(puts to `stdout`)* as well as the macros to make any generic printing function compatible. It works as follows:
> ```C
> // Lets say we have a generic print function for a struct T
> int T_gprint(sl_stream target, T to_print);
>
> // To make it `put` compatible, we define the following macro
> #define putT(val) SL_PUT_WRAPPER(T_gprint(SL_PUT_TARGET, val))
> //                ^                       ^
> //                |                       The target stream of current `put` statement
> //                Wrapper around out print function 
>
> // We can now use it within a `put` statement
> T t = ...;
> SL_put("Trying to put %d type T: ", 1, putT(t), "\n");
> ```
> The `put` environment works as a succession of calls to `gprintf` and put-compatible functions, that's why the `1` in the example above is still printed at the `"%d"` and directly follows the string in the arguments of `SL_put`.

> Finaly, as simple examples for how one would use the `sl_stream`, `gprintf` and `put` concepts, the following functions are provided:
> - `SL_gprintBin` *(print binary representation)*, `SL_printBin` *(to stdout)*, `SL_putBin` *(in `put` environment)*.
> - `SL_gprintHex` *(print hexadecimal representation)*, `SL_printHex` *(to stdout)*, `SL_putHex` *(in `put` environment)*.

### *tui.h*

***TODO: WRITE DOCUMENTATION WHEN MORE IS DONE***

## BONUS: Procedural generation of header files

The `generate` folder contains generation source files for `vector.h`, `quaternion.h`, `matrix.h` and `sl_all.h`. The common structures and functions between every generator file are found within `generate.h`.