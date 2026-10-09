#ifndef _SL_VECTOR_H_
#define _SL_VECTOR_H_

#include "../base.h"

#include "math.h"

#define SL_XPD_V(V)  (V).count, (V).data
#define SL_XPD_V2(V) (V).x, (V).y
#define SL_XPD_V3(V) (V).x, (V).y, (V).z
#define SL_XPD_V4(V) (V).x, (V).y, (V).z, (V).w

#define SL_FMT_V2(fmt) "v2("fmt", "fmt")"
#define SL_FMT_V3(fmt) "v3("fmt", "fmt", "fmt")"
#define SL_FMT_V4(fmt) "v4("fmt", "fmt", "fmt", "fmt")"

#define SL_vsize(V) (sizeof(V) / sizeof(((typeof(V) *)(NULL))->data[0]))

#pragma region I8

/// @brief Vector of i8 with arbitrary dimension
typedef struct {
    const usize count;
    i8 *data;
} i8v;

/// @brief Vector of i8 with dimension 2
typedef union {
    i8 data[2];
    struct {
        union { i8 x, r, u; };
        union { i8 y, g, v; };
    };
} i8v2;

#define SL_i8v2_zero  ((i8v2){.x =  0, .y =  0})
#define SL_i8v2_one   ((i8v2){.x =  1, .y =  1})
#define SL_i8v2_right ((i8v2){.x =  1, .y =  0})
#define SL_i8v2_up    ((i8v2){.x =  0, .y =  1})
#define SL_i8v2_left  ((i8v2){.x = -1, .y =  0})
#define SL_i8v2_down  ((i8v2){.x =  0, .y = -1})

/// @brief Vector of i8 with dimension 3
typedef union {
    i8 data[3];
    struct {
        union { i8 x, r, u; };
        union { i8 y, g, v; };
        union { i8 z, b, s; };
    };
    struct {
        union { i8 __x, __r, __u; };
        union { i8v2 yz, gb, vs; };
    };
    struct {
        union { i8v2 xy, rg, uv; };
        union { i8 __z, __b, __s; };
    };
} i8v3;

#define SL_i8v3_zero  ((i8v3){.x =  0, .y =  0, .z =  0})
#define SL_i8v3_one   ((i8v3){.x =  1, .y =  1, .z =  1})
#define SL_i8v3_right ((i8v3){.x =  1, .y =  0, .z =  0})
#define SL_i8v3_up    ((i8v3){.x =  0, .y =  1, .z =  0})
#define SL_i8v3_forw  ((i8v3){.x =  0, .y =  0, .z =  1})
#define SL_i8v3_left  ((i8v3){.x = -1, .y =  0, .z =  0})
#define SL_i8v3_down  ((i8v3){.x =  0, .y = -1, .z =  0})
#define SL_i8v3_back  ((i8v3){.x =  0, .y =  0, .z = -1})

/// @brief Vector of i8 with dimension 4
typedef union {
    i8 data[4];
    struct {
        union { i8 x, r, u; };
        union { i8 y, g, v; };
        union { i8 z, b, s; };
        union { i8 w, a, t; };
    };
    struct {
        union { i8 __x0, __r0, __u0; };
        union { i8v2 yz, gb, vs; };
        union { i8 __w0, __a0, __t0; };
    };
    struct {
        union { i8v2 xy, rb, uv; };
        union { i8v2 zw, ba, st; };
    };
    struct {
        union { i8v3 xyz, rgb, uvs; };
        union { i8 __w1, __a1, __t1; };
    };
    struct {
        union { i8 __x1, __r1, __u1; };
        union { i8v3 yzw, gba, vst; };
    };
} i8v4;

#define SL_i8v4_zero  ((i8v4){.x = 0, .y = 0, .z = 0, .w = 0})
#define SL_i8v4_one   ((i8v4){.x = 1, .y = 1, .z = 1, .w = 1})

#define SL_i8v4_white  ((i8v4){.x = 1, .y = 1, .z = 1, .w = 1})
#define SL_i8v4_black  ((i8v4){.x = 0, .y = 0, .z = 0, .w = 1})
#define SL_i8v4_red    ((i8v4){.x = 1, .y = 0, .z = 0, .w = 1})
#define SL_i8v4_green  ((i8v4){.x = 0, .y = 1, .z = 0, .w = 1})
#define SL_i8v4_blue   ((i8v4){.x = 0, .y = 0, .z = 1, .w = 1})
#define SL_i8v4_yellow ((i8v4){.x = 1, .y = 1, .z = 0, .w = 1})
#define SL_i8v4_cyan   ((i8v4){.x = 0, .y = 1, .z = 1, .w = 1})
#define SL_i8v4_purple ((i8v4){.x = 1, .y = 0, .z = 1, .w = 1})



#define SL_i8v2_(X, Y)       ((i8v2){.x = X, .y = Y})
#define SL_i8v3_(X, Y, Z)    ((i8v3){.x = X, .y = Y, .z = Z})
#define SL_i8v4_(X, Y, Z, W) ((i8v4){.x = X, .y = Y, .z = Z, .w = W})

#define SL_i8v2s(S)          ((i8v2){.x = S, .y = S})
#define SL_i8v3s(S)          ((i8v3){.x = S, .y = S, .z = S})
#define SL_i8v4s(S)          ((i8v4){.x = S, .y = S, .z = S, .w = S})

#define SL_i8vv(V)           ((i8v){.count = vsize(V), .data = (V).data})
#define SL_i8v2v(V, ...)     ((i8v2){.x = (V).x, .y = (V).y})
#define SL_i8v3v(V, ...)     ((i8v3){.x = (V).x, .y = (V).y, .z = (SL_vsize(V) >= 3 ? (V).data[2] : (0, ##__VA_ARGS__))})
#define SL_i8v4v(V, ...)     ((i8v4){.x = (V).x, .y = (V).y, .z = (SL_vsize(V) >= 3 ? (V).data[2] : ((const float[]){0, ##__VA_ARGS__, 0})[1]), .w = (SL_vsize(V) >= 4 ? (V).data[3] : ((const float[]){0, ##__VA_ARGS__, 0, 0})[2])})



/// @brief Equality of two i8v
/// @note All vectors are assumed to be of size 'count'
SL_header bool SL_i8vequ_(i8* lhs, i8* rhs, usize count)
#if defined(SL_IMPLEMENTATION)
{
    bool dest = true;
    for (usize i = 0; i < count; ++i) dest &= lhs[i] == rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Equality of two i8v
/// @note All vectors are assumed to be of size 'count'
SL_header bool SL_i8vequ(i8v lhs, i8v rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i8vequ_(lhs.data, rhs.data, lhs.count);
}
#else
;
#endif
/// @brief Equality of two i8v2
SL_header bool SL_i8v2equ(i8v2 lhs, i8v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}
#else
;
#endif
/// @brief Equality of two i8v3
SL_header bool SL_i8v3equ(i8v3 lhs, i8v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}
#else
;
#endif
/// @brief Equality of two i8v4
SL_header bool SL_i8v4equ(i8v4 lhs, i8v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
}
#else
;
#endif
/// @brief Addition of two i8v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8* SL_i8vadd_(i8* lhs, i8* rhs, i8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] + rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Addition of two i8v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8v SL_i8vadd(i8v lhs, i8v rhs, i8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i8vadd_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two i8v2
SL_header i8v2 SL_i8v2add(i8v2 lhs, i8v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v2) {
        .x = lhs.x + rhs.x,
        .y = lhs.y + rhs.y
    };
}
#else
;
#endif
/// @brief Addition of two i8v3
SL_header i8v3 SL_i8v3add(i8v3 lhs, i8v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v3) {
        .x = lhs.x + rhs.x,
        .y = lhs.y + rhs.y,
        .z = lhs.z + rhs.z
    };
}
#else
;
#endif
/// @brief Addition of two i8v4
SL_header i8v4 SL_i8v4add(i8v4 lhs, i8v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v4) {
        .x = lhs.x + rhs.x,
        .y = lhs.y + rhs.y,
        .z = lhs.z + rhs.z,
        .w = lhs.w + rhs.w
    };
}
#else
;
#endif
/// @brief Difference of two i8v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8* SL_i8vsub_(i8* lhs, i8* rhs, i8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] - rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Difference of two i8v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8v SL_i8vsub(i8v lhs, i8v rhs, i8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i8vsub_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two i8v2
SL_header i8v2 SL_i8v2sub(i8v2 lhs, i8v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v2) {
        .x = lhs.x - rhs.x,
        .y = lhs.y - rhs.y
    };
}
#else
;
#endif
/// @brief Difference of two i8v3
SL_header i8v3 SL_i8v3sub(i8v3 lhs, i8v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v3) {
        .x = lhs.x - rhs.x,
        .y = lhs.y - rhs.y,
        .z = lhs.z - rhs.z
    };
}
#else
;
#endif
/// @brief Difference of two i8v4
SL_header i8v4 SL_i8v4sub(i8v4 lhs, i8v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v4) {
        .x = lhs.x - rhs.x,
        .y = lhs.y - rhs.y,
        .z = lhs.z - rhs.z,
        .w = lhs.w - rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of two i8v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8* SL_i8vmul_(i8* lhs, i8* rhs, i8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise multiplication of two i8v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8v SL_i8vmul(i8v lhs, i8v rhs, i8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i8vmul_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise multiplication of two i8v2
SL_header i8v2 SL_i8v2mul(i8v2 lhs, i8v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v2) {
        .x = lhs.x * rhs.x,
        .y = lhs.y * rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of two i8v3
SL_header i8v3 SL_i8v3mul(i8v3 lhs, i8v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v3) {
        .x = lhs.x * rhs.x,
        .y = lhs.y * rhs.y,
        .z = lhs.z * rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of two i8v4
SL_header i8v4 SL_i8v4mul(i8v4 lhs, i8v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v4) {
        .x = lhs.x * rhs.x,
        .y = lhs.y * rhs.y,
        .z = lhs.z * rhs.z,
        .w = lhs.w * rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of a i8v with a scalar
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8* SL_i8vmuls_(i8* lhs, i8 rhs, i8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * rhs;
    return dest;
}
#else
;
#endif
/// @brief Component-wise multiplication of a i8v with a scalar
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8v SL_i8vmuls(i8v lhs, i8 rhs, i8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i8vmuls_(lhs.data, rhs, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise multiplication of a i8v2 with a scalar
SL_header i8v2 SL_i8v2muls(i8v2 lhs, i8 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v2) {
        .x = lhs.x * rhs,
        .y = lhs.y * rhs
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of a i8v3 with a scalar
SL_header i8v3 SL_i8v3muls(i8v3 lhs, i8 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v3) {
        .x = lhs.x * rhs,
        .y = lhs.y * rhs,
        .z = lhs.z * rhs
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of a i8v4 with a scalar
SL_header i8v4 SL_i8v4muls(i8v4 lhs, i8 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v4) {
        .x = lhs.x * rhs,
        .y = lhs.y * rhs,
        .z = lhs.z * rhs,
        .w = lhs.w * rhs
    };
}
#else
;
#endif
/// @brief Component-wise division of two i8v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8* SL_i8vdiv_(i8* lhs, i8* rhs, i8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] / rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise division of two i8v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8v SL_i8vdiv(i8v lhs, i8v rhs, i8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i8vdiv_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise division of two i8v2
SL_header i8v2 SL_i8v2div(i8v2 lhs, i8v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v2) {
        .x = lhs.x / rhs.x,
        .y = lhs.y / rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise division of two i8v3
SL_header i8v3 SL_i8v3div(i8v3 lhs, i8v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v3) {
        .x = lhs.x / rhs.x,
        .y = lhs.y / rhs.y,
        .z = lhs.z / rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise division of two i8v4
SL_header i8v4 SL_i8v4div(i8v4 lhs, i8v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v4) {
        .x = lhs.x / rhs.x,
        .y = lhs.y / rhs.y,
        .z = lhs.z / rhs.z,
        .w = lhs.w / rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise division of a i8v with a scalar
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8* SL_i8vdivs_(i8* lhs, i8 rhs, i8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] / rhs;
    return dest;
}
#else
;
#endif
/// @brief Component-wise division of a i8v with a scalar
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8v SL_i8vdivs(i8v lhs, i8 rhs, i8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i8vdivs_(lhs.data, rhs, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise division of a i8v2 with a scalar
SL_header i8v2 SL_i8v2divs(i8v2 lhs, i8 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v2) {
        .x = lhs.x / rhs,
        .y = lhs.y / rhs
    };
}
#else
;
#endif
/// @brief Component-wise division of a i8v3 with a scalar
SL_header i8v3 SL_i8v3divs(i8v3 lhs, i8 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v3) {
        .x = lhs.x / rhs,
        .y = lhs.y / rhs,
        .z = lhs.z / rhs
    };
}
#else
;
#endif
/// @brief Component-wise division of a i8v4 with a scalar
SL_header i8v4 SL_i8v4divs(i8v4 lhs, i8 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v4) {
        .x = lhs.x / rhs,
        .y = lhs.y / rhs,
        .z = lhs.z / rhs,
        .w = lhs.w / rhs
    };
}
#else
;
#endif
/// @brief Addition of two i8v with lhs scaled by a i8
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8* SL_i8vaddS_(i8* lhs, i8* rhs, i8 s, i8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] + rhs[i] * s;
    return dest;
}
#else
;
#endif
/// @brief Addition of two i8v with lhs scaled by a i8
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8v SL_i8vaddS(i8v lhs, i8v rhs, i8 s, i8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i8vaddS_(lhs.data, rhs.data, s, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two i8v2 with lhs scaled by a i8
SL_header i8v2 SL_i8v2addS(i8v2 lhs, i8v2 rhs, i8 s)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v2) {
        .x = lhs.x + rhs.x * s,
        .y = lhs.y + rhs.y * s
    };
}
#else
;
#endif
/// @brief Addition of two i8v3 with lhs scaled by a i8
SL_header i8v3 SL_i8v3addS(i8v3 lhs, i8v3 rhs, i8 s)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v3) {
        .x = lhs.x + rhs.x * s,
        .y = lhs.y + rhs.y * s,
        .z = lhs.z + rhs.z * s
    };
}
#else
;
#endif
/// @brief Addition of two i8v4 with lhs scaled by a i8
SL_header i8v4 SL_i8v4addS(i8v4 lhs, i8v4 rhs, i8 s)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v4) {
        .x = lhs.x + rhs.x * s,
        .y = lhs.y + rhs.y * s,
        .z = lhs.z + rhs.z * s,
        .w = lhs.w + rhs.w * s
    };
}
#else
;
#endif
/// @brief Difference of two i8v with lhs scaled by a i8
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8* SL_i8vsubS_(i8* lhs, i8* rhs, i8 s, i8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] - rhs[i] * s;
    return dest;
}
#else
;
#endif
/// @brief Difference of two i8v with lhs scaled by a i8
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8v SL_i8vsubS(i8v lhs, i8v rhs, i8 s, i8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i8vsubS_(lhs.data, rhs.data, s, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two i8v2 with lhs scaled by a i8
SL_header i8v2 SL_i8v2subS(i8v2 lhs, i8v2 rhs, i8 s)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v2) {
        .x = lhs.x - rhs.x * s,
        .y = lhs.y - rhs.y * s
    };
}
#else
;
#endif
/// @brief Difference of two i8v3 with lhs scaled by a i8
SL_header i8v3 SL_i8v3subS(i8v3 lhs, i8v3 rhs, i8 s)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v3) {
        .x = lhs.x - rhs.x * s,
        .y = lhs.y - rhs.y * s,
        .z = lhs.z - rhs.z * s
    };
}
#else
;
#endif
/// @brief Difference of two i8v4 with lhs scaled by a i8
SL_header i8v4 SL_i8v4subS(i8v4 lhs, i8v4 rhs, i8 s)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v4) {
        .x = lhs.x - rhs.x * s,
        .y = lhs.y - rhs.y * s,
        .z = lhs.z - rhs.z * s,
        .w = lhs.w - rhs.w * s
    };
}
#else
;
#endif
/// @brief Addition of two i8v with lhs multiplied with a i8
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8* SL_i8vaddM_(i8* lhs, i8* rhs, i8* m, i8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] + rhs[i] * m[i];
    return dest;
}
#else
;
#endif
/// @brief Addition of two i8v with lhs multiplied with a i8
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8v SL_i8vaddM(i8v lhs, i8v rhs, i8v m, i8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i8vaddM_(lhs.data, rhs.data, m.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two i8v2 with lhs multiplied with a i8
SL_header i8v2 SL_i8v2addM(i8v2 lhs, i8v2 rhs, i8v2 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v2) {
        .x = lhs.x + rhs.x * m.x,
        .y = lhs.y + rhs.y * m.y
    };
}
#else
;
#endif
/// @brief Addition of two i8v3 with lhs multiplied with a i8
SL_header i8v3 SL_i8v3addM(i8v3 lhs, i8v3 rhs, i8v3 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v3) {
        .x = lhs.x + rhs.x * m.x,
        .y = lhs.y + rhs.y * m.y,
        .z = lhs.z + rhs.z * m.z
    };
}
#else
;
#endif
/// @brief Addition of two i8v4 with lhs multiplied with a i8
SL_header i8v4 SL_i8v4addM(i8v4 lhs, i8v4 rhs, i8v4 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v4) {
        .x = lhs.x + rhs.x * m.x,
        .y = lhs.y + rhs.y * m.y,
        .z = lhs.z + rhs.z * m.z,
        .w = lhs.w + rhs.w * m.w
    };
}
#else
;
#endif
/// @brief Difference of two i8v with lhs multiplied with a i8
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8* SL_i8vsubM_(i8* lhs, i8* rhs, i8* m, i8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] - rhs[i] * m[i];
    return dest;
}
#else
;
#endif
/// @brief Difference of two i8v with lhs multiplied with a i8
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8v SL_i8vsubM(i8v lhs, i8v rhs, i8v m, i8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i8vsubM_(lhs.data, rhs.data, m.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two i8v2 with lhs multiplied with a i8
SL_header i8v2 SL_i8v2subM(i8v2 lhs, i8v2 rhs, i8v2 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v2) {
        .x = lhs.x - rhs.x * m.x,
        .y = lhs.y - rhs.y * m.y
    };
}
#else
;
#endif
/// @brief Difference of two i8v3 with lhs multiplied with a i8
SL_header i8v3 SL_i8v3subM(i8v3 lhs, i8v3 rhs, i8v3 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v3) {
        .x = lhs.x - rhs.x * m.x,
        .y = lhs.y - rhs.y * m.y,
        .z = lhs.z - rhs.z * m.z
    };
}
#else
;
#endif
/// @brief Difference of two i8v4 with lhs multiplied with a i8
SL_header i8v4 SL_i8v4subM(i8v4 lhs, i8v4 rhs, i8v4 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v4) {
        .x = lhs.x - rhs.x * m.x,
        .y = lhs.y - rhs.y * m.y,
        .z = lhs.z - rhs.z * m.z,
        .w = lhs.w - rhs.w * m.w
    };
}
#else
;
#endif
/// @brief Addition of two i8v with lhs scaled by i8 and multiplied with a i8
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8* SL_i8vaddSM_(i8* lhs, i8* rhs, i8 s, i8* m, i8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] + rhs[i] * s * m[i];
    return dest;
}
#else
;
#endif
/// @brief Addition of two i8v with lhs scaled by i8 and multiplied with a i8
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8v SL_i8vaddSM(i8v lhs, i8v rhs, i8 s, i8v m, i8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i8vaddSM_(lhs.data, rhs.data, s, m.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two i8v2 with lhs scaled by i8 and multiplied with a i8
SL_header i8v2 SL_i8v2addSM(i8v2 lhs, i8v2 rhs, i8 s, i8v2 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v2) {
        .x = lhs.x + rhs.x * s * m.x,
        .y = lhs.y + rhs.y * s * m.y
    };
}
#else
;
#endif
/// @brief Addition of two i8v3 with lhs scaled by i8 and multiplied with a i8
SL_header i8v3 SL_i8v3addSM(i8v3 lhs, i8v3 rhs, i8 s, i8v3 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v3) {
        .x = lhs.x + rhs.x * s * m.x,
        .y = lhs.y + rhs.y * s * m.y,
        .z = lhs.z + rhs.z * s * m.z
    };
}
#else
;
#endif
/// @brief Addition of two i8v4 with lhs scaled by i8 and multiplied with a i8
SL_header i8v4 SL_i8v4addSM(i8v4 lhs, i8v4 rhs, i8 s, i8v4 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v4) {
        .x = lhs.x + rhs.x * s * m.x,
        .y = lhs.y + rhs.y * s * m.y,
        .z = lhs.z + rhs.z * s * m.z,
        .w = lhs.w + rhs.w * s * m.w
    };
}
#else
;
#endif
/// @brief Difference of two i8v with lhs scaled by i8 and multiplied with a i8
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8* SL_i8vsubSM_(i8* lhs, i8* rhs, i8 s, i8* m, i8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] - rhs[i] * s * m[i];
    return dest;
}
#else
;
#endif
/// @brief Difference of two i8v with lhs scaled by i8 and multiplied with a i8
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8v SL_i8vsubSM(i8v lhs, i8v rhs, i8 s, i8v m, i8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i8vsubSM_(lhs.data, rhs.data, s, m.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two i8v2 with lhs scaled by i8 and multiplied with a i8
SL_header i8v2 SL_i8v2subSM(i8v2 lhs, i8v2 rhs, i8 s, i8v2 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v2) {
        .x = lhs.x - rhs.x * s * m.x,
        .y = lhs.y - rhs.y * s * m.y
    };
}
#else
;
#endif
/// @brief Difference of two i8v3 with lhs scaled by i8 and multiplied with a i8
SL_header i8v3 SL_i8v3subSM(i8v3 lhs, i8v3 rhs, i8 s, i8v3 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v3) {
        .x = lhs.x - rhs.x * s * m.x,
        .y = lhs.y - rhs.y * s * m.y,
        .z = lhs.z - rhs.z * s * m.z
    };
}
#else
;
#endif
/// @brief Difference of two i8v4 with lhs scaled by i8 and multiplied with a i8
SL_header i8v4 SL_i8v4subSM(i8v4 lhs, i8v4 rhs, i8 s, i8v4 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v4) {
        .x = lhs.x - rhs.x * s * m.x,
        .y = lhs.y - rhs.y * s * m.y,
        .z = lhs.z - rhs.z * s * m.z,
        .w = lhs.w - rhs.w * s * m.w
    };
}
#else
;
#endif
/// @brief Addition of two i8v with rhs scaled by a i8
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8* SL_i8vSadd_(i8* lhs, i8 s, i8* rhs, i8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * s + rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Addition of two i8v with rhs scaled by a i8
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8v SL_i8vSadd(i8v lhs, i8 s, i8v rhs, i8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i8vSadd_(lhs.data, s, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two i8v2 with rhs scaled by a i8
SL_header i8v2 SL_i8v2Sadd(i8v2 lhs, i8 s, i8v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v2) {
        .x = lhs.x * s + rhs.x,
        .y = lhs.y * s + rhs.y
    };
}
#else
;
#endif
/// @brief Addition of two i8v3 with rhs scaled by a i8
SL_header i8v3 SL_i8v3Sadd(i8v3 lhs, i8 s, i8v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v3) {
        .x = lhs.x * s + rhs.x,
        .y = lhs.y * s + rhs.y,
        .z = lhs.z * s + rhs.z
    };
}
#else
;
#endif
/// @brief Addition of two i8v4 with rhs scaled by a i8
SL_header i8v4 SL_i8v4Sadd(i8v4 lhs, i8 s, i8v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v4) {
        .x = lhs.x * s + rhs.x,
        .y = lhs.y * s + rhs.y,
        .z = lhs.z * s + rhs.z,
        .w = lhs.w * s + rhs.w
    };
}
#else
;
#endif
/// @brief Difference of two i8v with rhs scaled by a i8
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8* SL_i8vSsub_(i8* lhs, i8 s, i8* rhs, i8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * s - rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Difference of two i8v with rhs scaled by a i8
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8v SL_i8vSsub(i8v lhs, i8 s, i8v rhs, i8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i8vSsub_(lhs.data, s, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two i8v2 with rhs scaled by a i8
SL_header i8v2 SL_i8v2Ssub(i8v2 lhs, i8 s, i8v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v2) {
        .x = lhs.x * s - rhs.x,
        .y = lhs.y * s - rhs.y
    };
}
#else
;
#endif
/// @brief Difference of two i8v3 with rhs scaled by a i8
SL_header i8v3 SL_i8v3Ssub(i8v3 lhs, i8 s, i8v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v3) {
        .x = lhs.x * s - rhs.x,
        .y = lhs.y * s - rhs.y,
        .z = lhs.z * s - rhs.z
    };
}
#else
;
#endif
/// @brief Difference of two i8v4 with rhs scaled by a i8
SL_header i8v4 SL_i8v4Ssub(i8v4 lhs, i8 s, i8v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v4) {
        .x = lhs.x * s - rhs.x,
        .y = lhs.y * s - rhs.y,
        .z = lhs.z * s - rhs.z,
        .w = lhs.w * s - rhs.w
    };
}
#else
;
#endif
/// @brief Weighted sum of two i8v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8* SL_i8vmix_(i8* lhs, i8 lhs_w, i8* rhs, i8 rhs_w, i8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * lhs_w + rhs[i] * rhs_w;
    return dest;
}
#else
;
#endif
/// @brief Weighted sum of two i8v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8v SL_i8vmix(i8v lhs, i8 lhs_w, i8v rhs, i8 rhs_w, i8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i8vmix_(lhs.data, lhs_w, rhs.data, rhs_w, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Weighted sum of two i8v2
SL_header i8v2 SL_i8v2mix(i8v2 lhs, i8 lhs_w, i8v2 rhs, i8 rhs_w)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v2) {
        .x = lhs.x * lhs_w + rhs.x * rhs_w,
        .y = lhs.y * lhs_w + rhs.y * rhs_w
    };
}
#else
;
#endif
/// @brief Weighted sum of two i8v3
SL_header i8v3 SL_i8v3mix(i8v3 lhs, i8 lhs_w, i8v3 rhs, i8 rhs_w)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v3) {
        .x = lhs.x * lhs_w + rhs.x * rhs_w,
        .y = lhs.y * lhs_w + rhs.y * rhs_w,
        .z = lhs.z * lhs_w + rhs.z * rhs_w
    };
}
#else
;
#endif
/// @brief Weighted sum of two i8v4
SL_header i8v4 SL_i8v4mix(i8v4 lhs, i8 lhs_w, i8v4 rhs, i8 rhs_w)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v4) {
        .x = lhs.x * lhs_w + rhs.x * rhs_w,
        .y = lhs.y * lhs_w + rhs.y * rhs_w,
        .z = lhs.z * lhs_w + rhs.z * rhs_w,
        .w = lhs.w * lhs_w + rhs.w * rhs_w
    };
}
#else
;
#endif
/// @brief Negation of a i8v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8* SL_i8vneg_(i8* v, i8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = -v[i];
    return dest;
}
#else
;
#endif
/// @brief Negation of a i8v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8v SL_i8vneg(i8v v, i8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i8vneg_(v.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Negation of a i8v2
SL_header i8v2 SL_i8v2neg(i8v2 v)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v2) {
        .x = -v.x,
        .y = -v.y
    };
}
#else
;
#endif
/// @brief Negation of a i8v3
SL_header i8v3 SL_i8v3neg(i8v3 v)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v3) {
        .x = -v.x,
        .y = -v.y,
        .z = -v.z
    };
}
#else
;
#endif
/// @brief Negation of a i8v4
SL_header i8v4 SL_i8v4neg(i8v4 v)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v4) {
        .x = -v.x,
        .y = -v.y,
        .z = -v.z,
        .w = -v.w
    };
}
#else
;
#endif
/// @brief Component-wise absolute value of a i8v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8* SL_i8vabs_(i8* v, i8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = v[i] < 0 ? -v[i] : v[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise absolute value of a i8v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8v SL_i8vabs(i8v v, i8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i8vabs_(v.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise absolute value of a i8v2
SL_header i8v2 SL_i8v2abs(i8v2 v)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v2) {
        .x = v.x < 0 ? -v.x : v.x,
        .y = v.y < 0 ? -v.y : v.y
    };
}
#else
;
#endif
/// @brief Component-wise absolute value of a i8v3
SL_header i8v3 SL_i8v3abs(i8v3 v)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v3) {
        .x = v.x < 0 ? -v.x : v.x,
        .y = v.y < 0 ? -v.y : v.y,
        .z = v.z < 0 ? -v.z : v.z
    };
}
#else
;
#endif
/// @brief Component-wise absolute value of a i8v4
SL_header i8v4 SL_i8v4abs(i8v4 v)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v4) {
        .x = v.x < 0 ? -v.x : v.x,
        .y = v.y < 0 ? -v.y : v.y,
        .z = v.z < 0 ? -v.z : v.z,
        .w = v.w < 0 ? -v.w : v.w
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two i8v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8* SL_i8vmin_(i8* lhs, i8* rhs, i8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] < rhs[i] ? lhs[i] : rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise minimum of two i8v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8v SL_i8vmin(i8v lhs, i8v rhs, i8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i8vmin_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise minimum of two i8v2
SL_header i8v2 SL_i8v2min(i8v2 lhs, i8v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v2) {
        .x = lhs.x < rhs.x ? lhs.x : rhs.x,
        .y = lhs.y < rhs.y ? lhs.y : rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two i8v3
SL_header i8v3 SL_i8v3min(i8v3 lhs, i8v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v3) {
        .x = lhs.x < rhs.x ? lhs.x : rhs.x,
        .y = lhs.y < rhs.y ? lhs.y : rhs.y,
        .z = lhs.z < rhs.z ? lhs.z : rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two i8v4
SL_header i8v4 SL_i8v4min(i8v4 lhs, i8v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v4) {
        .x = lhs.x < rhs.x ? lhs.x : rhs.x,
        .y = lhs.y < rhs.y ? lhs.y : rhs.y,
        .z = lhs.z < rhs.z ? lhs.z : rhs.z,
        .w = lhs.w < rhs.w ? lhs.w : rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two i8v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8* SL_i8vmax_(i8* lhs, i8* rhs, i8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] > rhs[i] ? lhs[i] : rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise maximum of two i8v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8v SL_i8vmax(i8v lhs, i8v rhs, i8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i8vmax_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise maximum of two i8v2
SL_header i8v2 SL_i8v2max(i8v2 lhs, i8v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v2) {
        .x = lhs.x > rhs.x ? lhs.x : rhs.x,
        .y = lhs.y > rhs.y ? lhs.y : rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two i8v3
SL_header i8v3 SL_i8v3max(i8v3 lhs, i8v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v3) {
        .x = lhs.x > rhs.x ? lhs.x : rhs.x,
        .y = lhs.y > rhs.y ? lhs.y : rhs.y,
        .z = lhs.z > rhs.z ? lhs.z : rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two i8v4
SL_header i8v4 SL_i8v4max(i8v4 lhs, i8v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v4) {
        .x = lhs.x > rhs.x ? lhs.x : rhs.x,
        .y = lhs.y > rhs.y ? lhs.y : rhs.y,
        .z = lhs.z > rhs.z ? lhs.z : rhs.z,
        .w = lhs.w > rhs.w ? lhs.w : rhs.w
    };
}
#else
;
#endif
/// @brief Dot product of two i8v
/// @note All vectors are assumed to be of size 'count'
SL_header i64 SL_i8vdot_(i8* lhs, i8* rhs, usize count)
#if defined(SL_IMPLEMENTATION)
{
    i64 dest = 0;
    for (usize i = 0; i < count; ++i) dest += lhs[i] * rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Dot product of two i8v
/// @note All vectors are assumed to be of size 'count'
SL_header i64 SL_i8vdot(i8v lhs, i8v rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i8vdot_(lhs.data, rhs.data, lhs.count);
}
#else
;
#endif
/// @brief Dot product of two i8v2
SL_header i64 SL_i8v2dot(i8v2 lhs, i8v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}
#else
;
#endif
/// @brief Dot product of two i8v3
SL_header i64 SL_i8v3dot(i8v3 lhs, i8v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}
#else
;
#endif
/// @brief Dot product of two i8v4
SL_header i64 SL_i8v4dot(i8v4 lhs, i8v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}
#else
;
#endif
/// @brief Maximum component of a i8v
/// @note All vectors are assumed to be of size 'count'
SL_header i64 SL_i8vlen_max_(i8* v, usize count)
#if defined(SL_IMPLEMENTATION)
{
    i64 dest = 0;
    for (usize i = 0; i < count; ++i) dest = llabs(v[i]) > dest ? llabs(v[i]) : dest;
    return dest;
}
#else
;
#endif
/// @brief Maximum component of a i8v
/// @note All vectors are assumed to be of size 'count'
SL_header i64 SL_i8vlen_max(i8v v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i8vlen_max_(v.data, v.count);
}
#else
;
#endif
/// @brief Maximum component of a i8v2
SL_header i64 SL_i8v2len_max(i8v2 v)
#if defined(SL_IMPLEMENTATION)
{
    v = SL_i8v2abs(v);
    return v.x > v.y ? v.x : v.y;
}
#else
;
#endif
/// @brief Maximum component of a i8v3
SL_header i64 SL_i8v3len_max(i8v3 v)
#if defined(SL_IMPLEMENTATION)
{
    v = SL_i8v3abs(v);
    return v.x > v.y ? (v.x > v.z ? v.x : v.z) : (v.y > v.z ? v.y : v.z);
}
#else
;
#endif
/// @brief Maximum component of a i8v4
SL_header i64 SL_i8v4len_max(i8v4 v)
#if defined(SL_IMPLEMENTATION)
{
    v = SL_i8v4abs(v);
    return v.x > v.y ? (v.x > v.z ? (v.x > v.w ? v.x : v.w) : (v.z > v.w ? v.z : v.w)) : (v.y > v.z ? (v.y > v.w ? v.y : v.w) : (v.z > v.w ? v.z : v.w));
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a i8v
/// @note All vectors are assumed to be of size 'count'
SL_header i64 SL_i8vlen_manh_(i8* v, usize count)
#if defined(SL_IMPLEMENTATION)
{
    i64 dest = 0;
    for (usize i = 0; i < count; ++i) dest += llabs(v[i]);
    return dest;
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a i8v
/// @note All vectors are assumed to be of size 'count'
SL_header i64 SL_i8vlen_manh(i8v v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i8vlen_manh_(v.data, v.count);
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a i8v2
SL_header i64 SL_i8v2len_manh(i8v2 v)
#if defined(SL_IMPLEMENTATION)
{
    v = SL_i8v2abs(v);
    return v.x + v.y;
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a i8v3
SL_header i64 SL_i8v3len_manh(i8v3 v)
#if defined(SL_IMPLEMENTATION)
{
    v = SL_i8v3abs(v);
    return v.x + v.y + v.z;
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a i8v4
SL_header i64 SL_i8v4len_manh(i8v4 v)
#if defined(SL_IMPLEMENTATION)
{
    v = SL_i8v4abs(v);
    return v.x + v.y + v.z + v.w;
}
#else
;
#endif
/// @brief Squared euclidean length of a i8v
/// @note All vectors are assumed to be of size 'count'
SL_header i64 SL_i8vlen_srq_(i8* v, usize count)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i8vdot_(v, v, count);
}
#else
;
#endif
/// @brief Squared euclidean length of a i8v
/// @note All vectors are assumed to be of size 'count'
SL_header i64 SL_i8vlen_srq(i8v v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i8vlen_srq_(v.data, v.count);
}
#else
;
#endif
/// @brief Square length of a i8v2
SL_header i64 SL_i8v2len_sqr(i8v2 v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i8v2dot(v, v);
}
#else
;
#endif
/// @brief Square length of a i8v3
SL_header i64 SL_i8v3len_sqr(i8v3 v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i8v3dot(v, v);
}
#else
;
#endif
/// @brief Square length of a i8v4
SL_header i64 SL_i8v4len_sqr(i8v4 v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i8v4dot(v, v);
}
#else
;
#endif
/// @brief Euclidean length of a i8v
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_i8vlen_(i8* v, usize count)
#if defined(SL_IMPLEMENTATION)
{
    return sqrt(SL_i8vdot_(v, v, count));
}
#else
;
#endif
/// @brief Euclidean length of a i8v
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_i8vlen(i8v v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i8vlen_(v.data, v.count);
}
#else
;
#endif
/// @brief Euclidean length of a i8v2
SL_header double SL_i8v2len(i8v2 v)
#if defined(SL_IMPLEMENTATION)
{
    return sqrt(SL_i8v2dot(v, v));
}
#else
;
#endif
/// @brief Euclidean length of a i8v3
SL_header double SL_i8v3len(i8v3 v)
#if defined(SL_IMPLEMENTATION)
{
    return sqrt(SL_i8v3dot(v, v));
}
#else
;
#endif
/// @brief Euclidean length of a i8v4
SL_header double SL_i8v4len(i8v4 v)
#if defined(SL_IMPLEMENTATION)
{
    return sqrt(SL_i8v4dot(v, v));
}
#else
;
#endif
/// @brief Euclidean distance bewteen two i8v
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_i8vdist_(i8* lhs, i8* rhs, usize count)
#if defined(SL_IMPLEMENTATION)
{
    double accum = 0;
    for (int i = 0; i < count; ++i) accum += (lhs[i] - rhs[i]) * (lhs[i] - rhs[i]);
    return sqrt(accum);
}
#else
;
#endif
/// @brief Euclidean distance bewteen two i8v
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_i8vdist(i8v lhs, i8v rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i8vdist_(lhs.data, rhs.data, lhs.count);
}
#else
;
#endif
/// @brief Euclidean distance between two i8v2
SL_header double SL_i8v2dist(i8v2 lhs, i8v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i8v2len(SL_i8v2sub(lhs, rhs));
}
#else
;
#endif
/// @brief Euclidean distance between two i8v3
SL_header double SL_i8v3dist(i8v3 lhs, i8v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i8v3len(SL_i8v3sub(lhs, rhs));
}
#else
;
#endif
/// @brief Euclidean distance between two i8v4
SL_header double SL_i8v4dist(i8v4 lhs, i8v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i8v4len(SL_i8v4sub(lhs, rhs));
}
#else
;
#endif
/// @brief Reflection of i8v2 v around vector i8v2 n
SL_header i8v2 SL_i8v2refl(i8v2 v, i8v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i8v2subS(v, n, 2.0 * SL_i8v2dot(v, n) / SL_i8v2dot(n, n));
}
#else
;
#endif
/// @brief Reflection of i8v3 v around vector i8v3 n
SL_header i8v3 SL_i8v3refl(i8v3 v, i8v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i8v3subS(v, n, 2.0 * SL_i8v3dot(v, n) / SL_i8v3dot(n, n));
}
#else
;
#endif
/// @brief Reflection of i8v4 v around vector i8v4 n
SL_header i8v4 SL_i8v4refl(i8v4 v, i8v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i8v4subS(v, n, 2.0 * SL_i8v4dot(v, n) / SL_i8v4dot(n, n));
}
#else
;
#endif
/// @brief Reflection of i8v2 v around vector i8v2 n assumed to be of unit length
SL_header i8v2 SL_i8v2refl_u(i8v2 v, i8v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i8v2subS(v, n, 2.0 * SL_i8v2dot(v, n));
}
#else
;
#endif
/// @brief Reflection of i8v3 v around vector i8v3 n assumed to be of unit length
SL_header i8v3 SL_i8v3refl_u(i8v3 v, i8v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i8v3subS(v, n, 2.0 * SL_i8v3dot(v, n));
}
#else
;
#endif
/// @brief Reflection of i8v4 v around vector i8v4 n assumed to be of unit length
SL_header i8v4 SL_i8v4refl_u(i8v4 v, i8v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i8v4subS(v, n, 2.0 * SL_i8v4dot(v, n));
}
#else
;
#endif
/// @brief Get component of i8v2 v in direction i8v2 n
SL_header i8v2 SL_i8v2align(i8v2 v, i8v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i8v2muls(n, SL_i8v2dot(v, n) / SL_i8v2dot(n, n));
}
#else
;
#endif
/// @brief Get component of i8v3 v in direction i8v3 n
SL_header i8v3 SL_i8v3align(i8v3 v, i8v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i8v3muls(n, SL_i8v3dot(v, n) / SL_i8v3dot(n, n));
}
#else
;
#endif
/// @brief Get component of i8v4 v in direction i8v4 n
SL_header i8v4 SL_i8v4align(i8v4 v, i8v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i8v4muls(n, SL_i8v4dot(v, n) / SL_i8v4dot(n, n));
}
#else
;
#endif
/// @brief Get component of i8v2 v in direction i8v2 n assumed to be of unit length
SL_header i8v2 SL_i8v2align_u(i8v2 v, i8v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i8v2muls(n, SL_i8v2dot(v, n));
}
#else
;
#endif
/// @brief Get component of i8v3 v in direction i8v3 n assumed to be of unit length
SL_header i8v3 SL_i8v3align_u(i8v3 v, i8v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i8v3muls(n, SL_i8v3dot(v, n));
}
#else
;
#endif
/// @brief Get component of i8v4 v in direction i8v4 n assumed to be of unit length
SL_header i8v4 SL_i8v4align_u(i8v4 v, i8v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i8v4muls(n, SL_i8v4dot(v, n));
}
#else
;
#endif
/// @brief Project i8v2 v on plane with normal i8v2 n
SL_header i8v2 SL_i8v2proj(i8v2 v, i8v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i8v2sub(v, SL_i8v2align(v, n));
}
#else
;
#endif
/// @brief Project i8v3 v on plane with normal i8v3 n
SL_header i8v3 SL_i8v3proj(i8v3 v, i8v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i8v3sub(v, SL_i8v3align(v, n));
}
#else
;
#endif
/// @brief Project i8v4 v on plane with normal i8v4 n
SL_header i8v4 SL_i8v4proj(i8v4 v, i8v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i8v4sub(v, SL_i8v4align(v, n));
}
#else
;
#endif
/// @brief Project i8v2 v on plane with normal i8v2 n
SL_header i8v2 SL_i8v2proj_u(i8v2 v, i8v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i8v2sub(v, SL_i8v2align_u(v, n));
}
#else
;
#endif
/// @brief Project i8v3 v on plane with normal i8v3 n
SL_header i8v3 SL_i8v3proj_u(i8v3 v, i8v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i8v3sub(v, SL_i8v3align_u(v, n));
}
#else
;
#endif
/// @brief Project i8v4 v on plane with normal i8v4 n
SL_header i8v4 SL_i8v4proj_u(i8v4 v, i8v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i8v4sub(v, SL_i8v4align_u(v, n));
}
#else
;
#endif
/// @brief Component-wise modulo of a i8v by scalar n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8* SL_i8vmods_(i8* v, i8 n, i8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = v[i] % n;
    return dest;
}
#else
;
#endif
/// @brief Component-wise modulo of a i8v by scalar n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8v SL_i8vmods(i8v v, i8 n, i8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i8vmods_(v.data, n, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise modulo of a i8v2 by scalar n
SL_header i8v2 SL_i8v2mods(i8v2 v, i8 n)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v2) {
        .x = v.x % n,
        .y = v.y % n
    };
}
#else
;
#endif
/// @brief Component-wise modulo of a i8v3 by scalar n
SL_header i8v3 SL_i8v3mods(i8v3 v, i8 n)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v3) {
        .x = v.x % n,
        .y = v.y % n,
        .z = v.z % n
    };
}
#else
;
#endif
/// @brief Component-wise modulo of a i8v4 by scalar n
SL_header i8v4 SL_i8v4mods(i8v4 v, i8 n)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v4) {
        .x = v.x % n,
        .y = v.y % n,
        .z = v.z % n,
        .w = v.w % n
    };
}
#else
;
#endif
/// @brief Component-wise modulo of a i8v by i8v n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8* SL_i8vmod_(i8* v, i8* n, i8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = v[i] % n[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise modulo of a i8v by i8v n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8v SL_i8vmod(i8v v, i8v n, i8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i8vmod_(v.data, n.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise modulo of a i8v2 by i8v2 n
SL_header i8v2 SL_i8v2mod(i8v2 v, i8v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v2) {
        .x = v.x % n.x,
        .y = v.y % n.y
    };
}
#else
;
#endif
/// @brief Component-wise modulo of a i8v3 by i8v3 n
SL_header i8v3 SL_i8v3mod(i8v3 v, i8v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v3) {
        .x = v.x % n.x,
        .y = v.y % n.y,
        .z = v.z % n.z
    };
}
#else
;
#endif
/// @brief Component-wise modulo of a i8v4 by i8v4 n
SL_header i8v4 SL_i8v4mod(i8v4 v, i8v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v4) {
        .x = v.x % n.x,
        .y = v.y % n.y,
        .z = v.z % n.z,
        .w = v.w % n.w
    };
}
#else
;
#endif
/// @brief Cross-product of two i8v2
SL_header i64 SL_i8v2cross(i8v2 lhs, i8v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x * rhs.y - lhs.y * rhs.x;
}
#else
;
#endif
/// @brief Cross-product of two i8v3
SL_header i8v3 SL_i8v3cross(i8v3 lhs, i8v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v3) {
        .x = lhs.y * rhs.z - lhs.z * rhs.y,
        .y = lhs.z * rhs.x - lhs.x * rhs.z,
        .z = lhs.x * rhs.y - lhs.y * rhs.x
    };
}
#else
;
#endif
/// @brief Component-wise binary AND of two i8v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8* SL_i8vand_(i8* lhs, i8* rhs, i8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] & rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary AND of two i8v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8v SL_i8vand(i8v lhs, i8v rhs, i8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i8vand_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary AND of two i8v2
SL_header i8v2 SL_i8v2and(i8v2 lhs, i8v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v2) {
        .x = lhs.x & rhs.x,
        .y = lhs.y & rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise binary AND of two i8v3
SL_header i8v3 SL_i8v3and(i8v3 lhs, i8v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v3) {
        .x = lhs.x & rhs.x,
        .y = lhs.y & rhs.y,
        .z = lhs.z & rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise binary AND of two i8v4
SL_header i8v4 SL_i8v4and(i8v4 lhs, i8v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v4) {
        .x = lhs.x & rhs.x,
        .y = lhs.y & rhs.y,
        .z = lhs.z & rhs.z,
        .w = lhs.w & rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise binary OR of two i8v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8* SL_i8vor_(i8* lhs, i8* rhs, i8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] | rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary OR of two i8v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8v SL_i8vor(i8v lhs, i8v rhs, i8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i8vor_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary OR of two i8v2
SL_header i8v2 SL_i8v2or(i8v2 lhs, i8v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v2) {
        .x = lhs.x | rhs.x,
        .y = lhs.y | rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise binary OR of two i8v3
SL_header i8v3 SL_i8v3or(i8v3 lhs, i8v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v3) {
        .x = lhs.x | rhs.x,
        .y = lhs.y | rhs.y,
        .z = lhs.z | rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise binary OR of two i8v4
SL_header i8v4 SL_i8v4or(i8v4 lhs, i8v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v4) {
        .x = lhs.x | rhs.x,
        .y = lhs.y | rhs.y,
        .z = lhs.z | rhs.z,
        .w = lhs.w | rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise binary XOR of two i8v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8* SL_i8vxor_(i8* lhs, i8* rhs, i8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] ^ rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary XOR of two i8v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8v SL_i8vxor(i8v lhs, i8v rhs, i8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i8vxor_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary XOR of two i8v2
SL_header i8v2 SL_i8v2xor(i8v2 lhs, i8v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v2) {
        .x = lhs.x ^ rhs.x,
        .y = lhs.y ^ rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise binary XOR of two i8v3
SL_header i8v3 SL_i8v3xor(i8v3 lhs, i8v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v3) {
        .x = lhs.x ^ rhs.x,
        .y = lhs.y ^ rhs.y,
        .z = lhs.z ^ rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise binary XOR of two i8v4
SL_header i8v4 SL_i8v4xor(i8v4 lhs, i8v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v4) {
        .x = lhs.x ^ rhs.x,
        .y = lhs.y ^ rhs.y,
        .z = lhs.z ^ rhs.z,
        .w = lhs.w ^ rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise binary NOT of a i8v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8* SL_i8vnot_(i8* v, i8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = ~v[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary NOT of a i8v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8v SL_i8vnot(i8v v, i8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i8vnot_(v.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary NOT of a i8v2
SL_header i8v2 SL_i8v2not(i8v2 v)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v2) {
        .x = ~v.x,
        .y = ~v.y
    };
}
#else
;
#endif
/// @brief Component-wise binary NOT of a i8v3
SL_header i8v3 SL_i8v3not(i8v3 v)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v3) {
        .x = ~v.x,
        .y = ~v.y,
        .z = ~v.z
    };
}
#else
;
#endif
/// @brief Component-wise binary NOT of a i8v4
SL_header i8v4 SL_i8v4not(i8v4 v)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v4) {
        .x = ~v.x,
        .y = ~v.y,
        .z = ~v.z,
        .w = ~v.w
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a i8v by integer n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8* SL_i8vlshfts_(i8* lhs, i8 rhs, i8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] << rhs;
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a i8v by integer n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8v SL_i8vlshfts(i8v lhs, i8 rhs, i8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i8vlshfts_(lhs.data, rhs, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a i8v2 by integer n
SL_header i8v2 SL_i8v2lshfts(i8v2 lhs, i8 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v2) {
        .x = lhs.x << rhs,
        .y = lhs.y << rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a i8v3 by integer n
SL_header i8v3 SL_i8v3lshfts(i8v3 lhs, i8 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v3) {
        .x = lhs.x << rhs,
        .y = lhs.y << rhs,
        .z = lhs.z << rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a i8v4 by integer n
SL_header i8v4 SL_i8v4lshfts(i8v4 lhs, i8 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v4) {
        .x = lhs.x << rhs,
        .y = lhs.y << rhs,
        .z = lhs.z << rhs,
        .w = lhs.w << rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a i8v by i8v n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8* SL_i8vlshft_(i8* lhs, i8* rhs, i8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] << rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a i8v by i8v n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8v SL_i8vlshft(i8v lhs, i8v rhs, i8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i8vlshft_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a i8v2 by i8v2 n
SL_header i8v2 SL_i8v2lshft(i8v2 lhs, i8v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v2) {
        .x = lhs.x << rhs.x,
        .y = lhs.y << rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a i8v3 by i8v3 n
SL_header i8v3 SL_i8v3lshft(i8v3 lhs, i8v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v3) {
        .x = lhs.x << rhs.x,
        .y = lhs.y << rhs.y,
        .z = lhs.z << rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a i8v4 by i8v4 n
SL_header i8v4 SL_i8v4lshft(i8v4 lhs, i8v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v4) {
        .x = lhs.x << rhs.x,
        .y = lhs.y << rhs.y,
        .z = lhs.z << rhs.z,
        .w = lhs.w << rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a i8v by interger n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8* SL_i8vrshfts_(i8* lhs, i8 rhs, i8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] >> rhs;
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a i8v by interger n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8v SL_i8vrshfts(i8v lhs, i8 rhs, i8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i8vrshfts_(lhs.data, rhs, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a i8v2 by interger n
SL_header i8v2 SL_i8v2rshfts(i8v2 lhs, i8 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v2) {
        .x = lhs.x >> rhs,
        .y = lhs.y >> rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a i8v3 by interger n
SL_header i8v3 SL_i8v3rshfts(i8v3 lhs, i8 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v3) {
        .x = lhs.x >> rhs,
        .y = lhs.y >> rhs,
        .z = lhs.z >> rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a i8v4 by interger n
SL_header i8v4 SL_i8v4rshfts(i8v4 lhs, i8 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v4) {
        .x = lhs.x >> rhs,
        .y = lhs.y >> rhs,
        .z = lhs.z >> rhs,
        .w = lhs.w >> rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a i8v by i8v n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8* SL_i8vrshft_(i8* lhs, i8* rhs, i8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] >> rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a i8v by i8v n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i8v SL_i8vrshft(i8v lhs, i8v rhs, i8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i8vrshft_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a i8v2 by i8v2 n
SL_header i8v2 SL_i8v2rshft(i8v2 lhs, i8v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v2) {
        .x = lhs.x >> rhs.x,
        .y = lhs.y >> rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a i8v3 by i8v3 n
SL_header i8v3 SL_i8v3rshft(i8v3 lhs, i8v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v3) {
        .x = lhs.x >> rhs.x,
        .y = lhs.y >> rhs.y,
        .z = lhs.z >> rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a i8v4 by i8v4 n
SL_header i8v4 SL_i8v4rshft(i8v4 lhs, i8v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i8v4) {
        .x = lhs.x >> rhs.x,
        .y = lhs.y >> rhs.y,
        .z = lhs.z >> rhs.z,
        .w = lhs.w >> rhs.w
    };
}
#else
;
#endif
#pragma endregion I8
#pragma region I16

/// @brief Vector of i16 with arbitrary dimension
typedef struct {
    const usize count;
    i16 *data;
} i16v;

/// @brief Vector of i16 with dimension 2
typedef union {
    i16 data[2];
    struct {
        union { i16 x, r, u; };
        union { i16 y, g, v; };
    };
} i16v2;

#define SL_i16v2_zero  ((i16v2){.x =  0, .y =  0})
#define SL_i16v2_one   ((i16v2){.x =  1, .y =  1})
#define SL_i16v2_right ((i16v2){.x =  1, .y =  0})
#define SL_i16v2_up    ((i16v2){.x =  0, .y =  1})
#define SL_i16v2_left  ((i16v2){.x = -1, .y =  0})
#define SL_i16v2_down  ((i16v2){.x =  0, .y = -1})

/// @brief Vector of i16 with dimension 3
typedef union {
    i16 data[3];
    struct {
        union { i16 x, r, u; };
        union { i16 y, g, v; };
        union { i16 z, b, s; };
    };
    struct {
        union { i16 __x, __r, __u; };
        union { i16v2 yz, gb, vs; };
    };
    struct {
        union { i16v2 xy, rg, uv; };
        union { i16 __z, __b, __s; };
    };
} i16v3;

#define SL_i16v3_zero  ((i16v3){.x =  0, .y =  0, .z =  0})
#define SL_i16v3_one   ((i16v3){.x =  1, .y =  1, .z =  1})
#define SL_i16v3_right ((i16v3){.x =  1, .y =  0, .z =  0})
#define SL_i16v3_up    ((i16v3){.x =  0, .y =  1, .z =  0})
#define SL_i16v3_forw  ((i16v3){.x =  0, .y =  0, .z =  1})
#define SL_i16v3_left  ((i16v3){.x = -1, .y =  0, .z =  0})
#define SL_i16v3_down  ((i16v3){.x =  0, .y = -1, .z =  0})
#define SL_i16v3_back  ((i16v3){.x =  0, .y =  0, .z = -1})

/// @brief Vector of i16 with dimension 4
typedef union {
    i16 data[4];
    struct {
        union { i16 x, r, u; };
        union { i16 y, g, v; };
        union { i16 z, b, s; };
        union { i16 w, a, t; };
    };
    struct {
        union { i16 __x0, __r0, __u0; };
        union { i16v2 yz, gb, vs; };
        union { i16 __w0, __a0, __t0; };
    };
    struct {
        union { i16v2 xy, rb, uv; };
        union { i16v2 zw, ba, st; };
    };
    struct {
        union { i16v3 xyz, rgb, uvs; };
        union { i16 __w1, __a1, __t1; };
    };
    struct {
        union { i16 __x1, __r1, __u1; };
        union { i16v3 yzw, gba, vst; };
    };
} i16v4;

#define SL_i16v4_zero  ((i16v4){.x = 0, .y = 0, .z = 0, .w = 0})
#define SL_i16v4_one   ((i16v4){.x = 1, .y = 1, .z = 1, .w = 1})

#define SL_i16v4_white  ((i16v4){.x = 1, .y = 1, .z = 1, .w = 1})
#define SL_i16v4_black  ((i16v4){.x = 0, .y = 0, .z = 0, .w = 1})
#define SL_i16v4_red    ((i16v4){.x = 1, .y = 0, .z = 0, .w = 1})
#define SL_i16v4_green  ((i16v4){.x = 0, .y = 1, .z = 0, .w = 1})
#define SL_i16v4_blue   ((i16v4){.x = 0, .y = 0, .z = 1, .w = 1})
#define SL_i16v4_yellow ((i16v4){.x = 1, .y = 1, .z = 0, .w = 1})
#define SL_i16v4_cyan   ((i16v4){.x = 0, .y = 1, .z = 1, .w = 1})
#define SL_i16v4_purple ((i16v4){.x = 1, .y = 0, .z = 1, .w = 1})



#define SL_i16v2_(X, Y)       ((i16v2){.x = X, .y = Y})
#define SL_i16v3_(X, Y, Z)    ((i16v3){.x = X, .y = Y, .z = Z})
#define SL_i16v4_(X, Y, Z, W) ((i16v4){.x = X, .y = Y, .z = Z, .w = W})

#define SL_i16v2s(S)          ((i16v2){.x = S, .y = S})
#define SL_i16v3s(S)          ((i16v3){.x = S, .y = S, .z = S})
#define SL_i16v4s(S)          ((i16v4){.x = S, .y = S, .z = S, .w = S})

#define SL_i16vv(V)           ((i16v){.count = vsize(V), .data = (V).data})
#define SL_i16v2v(V, ...)     ((i16v2){.x = (V).x, .y = (V).y})
#define SL_i16v3v(V, ...)     ((i16v3){.x = (V).x, .y = (V).y, .z = (SL_vsize(V) >= 3 ? (V).data[2] : (0, ##__VA_ARGS__))})
#define SL_i16v4v(V, ...)     ((i16v4){.x = (V).x, .y = (V).y, .z = (SL_vsize(V) >= 3 ? (V).data[2] : ((const float[]){0, ##__VA_ARGS__, 0})[1]), .w = (SL_vsize(V) >= 4 ? (V).data[3] : ((const float[]){0, ##__VA_ARGS__, 0, 0})[2])})



/// @brief Equality of two i16v
/// @note All vectors are assumed to be of size 'count'
SL_header bool SL_i16vequ_(i16* lhs, i16* rhs, usize count)
#if defined(SL_IMPLEMENTATION)
{
    bool dest = true;
    for (usize i = 0; i < count; ++i) dest &= lhs[i] == rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Equality of two i16v
/// @note All vectors are assumed to be of size 'count'
SL_header bool SL_i16vequ(i16v lhs, i16v rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i16vequ_(lhs.data, rhs.data, lhs.count);
}
#else
;
#endif
/// @brief Equality of two i16v2
SL_header bool SL_i16v2equ(i16v2 lhs, i16v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}
#else
;
#endif
/// @brief Equality of two i16v3
SL_header bool SL_i16v3equ(i16v3 lhs, i16v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}
#else
;
#endif
/// @brief Equality of two i16v4
SL_header bool SL_i16v4equ(i16v4 lhs, i16v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
}
#else
;
#endif
/// @brief Addition of two i16v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16* SL_i16vadd_(i16* lhs, i16* rhs, i16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] + rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Addition of two i16v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16v SL_i16vadd(i16v lhs, i16v rhs, i16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i16vadd_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two i16v2
SL_header i16v2 SL_i16v2add(i16v2 lhs, i16v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v2) {
        .x = lhs.x + rhs.x,
        .y = lhs.y + rhs.y
    };
}
#else
;
#endif
/// @brief Addition of two i16v3
SL_header i16v3 SL_i16v3add(i16v3 lhs, i16v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v3) {
        .x = lhs.x + rhs.x,
        .y = lhs.y + rhs.y,
        .z = lhs.z + rhs.z
    };
}
#else
;
#endif
/// @brief Addition of two i16v4
SL_header i16v4 SL_i16v4add(i16v4 lhs, i16v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v4) {
        .x = lhs.x + rhs.x,
        .y = lhs.y + rhs.y,
        .z = lhs.z + rhs.z,
        .w = lhs.w + rhs.w
    };
}
#else
;
#endif
/// @brief Difference of two i16v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16* SL_i16vsub_(i16* lhs, i16* rhs, i16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] - rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Difference of two i16v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16v SL_i16vsub(i16v lhs, i16v rhs, i16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i16vsub_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two i16v2
SL_header i16v2 SL_i16v2sub(i16v2 lhs, i16v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v2) {
        .x = lhs.x - rhs.x,
        .y = lhs.y - rhs.y
    };
}
#else
;
#endif
/// @brief Difference of two i16v3
SL_header i16v3 SL_i16v3sub(i16v3 lhs, i16v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v3) {
        .x = lhs.x - rhs.x,
        .y = lhs.y - rhs.y,
        .z = lhs.z - rhs.z
    };
}
#else
;
#endif
/// @brief Difference of two i16v4
SL_header i16v4 SL_i16v4sub(i16v4 lhs, i16v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v4) {
        .x = lhs.x - rhs.x,
        .y = lhs.y - rhs.y,
        .z = lhs.z - rhs.z,
        .w = lhs.w - rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of two i16v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16* SL_i16vmul_(i16* lhs, i16* rhs, i16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise multiplication of two i16v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16v SL_i16vmul(i16v lhs, i16v rhs, i16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i16vmul_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise multiplication of two i16v2
SL_header i16v2 SL_i16v2mul(i16v2 lhs, i16v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v2) {
        .x = lhs.x * rhs.x,
        .y = lhs.y * rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of two i16v3
SL_header i16v3 SL_i16v3mul(i16v3 lhs, i16v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v3) {
        .x = lhs.x * rhs.x,
        .y = lhs.y * rhs.y,
        .z = lhs.z * rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of two i16v4
SL_header i16v4 SL_i16v4mul(i16v4 lhs, i16v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v4) {
        .x = lhs.x * rhs.x,
        .y = lhs.y * rhs.y,
        .z = lhs.z * rhs.z,
        .w = lhs.w * rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of a i16v with a scalar
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16* SL_i16vmuls_(i16* lhs, i16 rhs, i16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * rhs;
    return dest;
}
#else
;
#endif
/// @brief Component-wise multiplication of a i16v with a scalar
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16v SL_i16vmuls(i16v lhs, i16 rhs, i16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i16vmuls_(lhs.data, rhs, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise multiplication of a i16v2 with a scalar
SL_header i16v2 SL_i16v2muls(i16v2 lhs, i16 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v2) {
        .x = lhs.x * rhs,
        .y = lhs.y * rhs
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of a i16v3 with a scalar
SL_header i16v3 SL_i16v3muls(i16v3 lhs, i16 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v3) {
        .x = lhs.x * rhs,
        .y = lhs.y * rhs,
        .z = lhs.z * rhs
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of a i16v4 with a scalar
SL_header i16v4 SL_i16v4muls(i16v4 lhs, i16 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v4) {
        .x = lhs.x * rhs,
        .y = lhs.y * rhs,
        .z = lhs.z * rhs,
        .w = lhs.w * rhs
    };
}
#else
;
#endif
/// @brief Component-wise division of two i16v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16* SL_i16vdiv_(i16* lhs, i16* rhs, i16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] / rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise division of two i16v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16v SL_i16vdiv(i16v lhs, i16v rhs, i16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i16vdiv_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise division of two i16v2
SL_header i16v2 SL_i16v2div(i16v2 lhs, i16v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v2) {
        .x = lhs.x / rhs.x,
        .y = lhs.y / rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise division of two i16v3
SL_header i16v3 SL_i16v3div(i16v3 lhs, i16v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v3) {
        .x = lhs.x / rhs.x,
        .y = lhs.y / rhs.y,
        .z = lhs.z / rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise division of two i16v4
SL_header i16v4 SL_i16v4div(i16v4 lhs, i16v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v4) {
        .x = lhs.x / rhs.x,
        .y = lhs.y / rhs.y,
        .z = lhs.z / rhs.z,
        .w = lhs.w / rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise division of a i16v with a scalar
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16* SL_i16vdivs_(i16* lhs, i16 rhs, i16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] / rhs;
    return dest;
}
#else
;
#endif
/// @brief Component-wise division of a i16v with a scalar
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16v SL_i16vdivs(i16v lhs, i16 rhs, i16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i16vdivs_(lhs.data, rhs, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise division of a i16v2 with a scalar
SL_header i16v2 SL_i16v2divs(i16v2 lhs, i16 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v2) {
        .x = lhs.x / rhs,
        .y = lhs.y / rhs
    };
}
#else
;
#endif
/// @brief Component-wise division of a i16v3 with a scalar
SL_header i16v3 SL_i16v3divs(i16v3 lhs, i16 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v3) {
        .x = lhs.x / rhs,
        .y = lhs.y / rhs,
        .z = lhs.z / rhs
    };
}
#else
;
#endif
/// @brief Component-wise division of a i16v4 with a scalar
SL_header i16v4 SL_i16v4divs(i16v4 lhs, i16 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v4) {
        .x = lhs.x / rhs,
        .y = lhs.y / rhs,
        .z = lhs.z / rhs,
        .w = lhs.w / rhs
    };
}
#else
;
#endif
/// @brief Addition of two i16v with lhs scaled by a i16
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16* SL_i16vaddS_(i16* lhs, i16* rhs, i16 s, i16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] + rhs[i] * s;
    return dest;
}
#else
;
#endif
/// @brief Addition of two i16v with lhs scaled by a i16
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16v SL_i16vaddS(i16v lhs, i16v rhs, i16 s, i16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i16vaddS_(lhs.data, rhs.data, s, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two i16v2 with lhs scaled by a i16
SL_header i16v2 SL_i16v2addS(i16v2 lhs, i16v2 rhs, i16 s)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v2) {
        .x = lhs.x + rhs.x * s,
        .y = lhs.y + rhs.y * s
    };
}
#else
;
#endif
/// @brief Addition of two i16v3 with lhs scaled by a i16
SL_header i16v3 SL_i16v3addS(i16v3 lhs, i16v3 rhs, i16 s)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v3) {
        .x = lhs.x + rhs.x * s,
        .y = lhs.y + rhs.y * s,
        .z = lhs.z + rhs.z * s
    };
}
#else
;
#endif
/// @brief Addition of two i16v4 with lhs scaled by a i16
SL_header i16v4 SL_i16v4addS(i16v4 lhs, i16v4 rhs, i16 s)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v4) {
        .x = lhs.x + rhs.x * s,
        .y = lhs.y + rhs.y * s,
        .z = lhs.z + rhs.z * s,
        .w = lhs.w + rhs.w * s
    };
}
#else
;
#endif
/// @brief Difference of two i16v with lhs scaled by a i16
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16* SL_i16vsubS_(i16* lhs, i16* rhs, i16 s, i16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] - rhs[i] * s;
    return dest;
}
#else
;
#endif
/// @brief Difference of two i16v with lhs scaled by a i16
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16v SL_i16vsubS(i16v lhs, i16v rhs, i16 s, i16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i16vsubS_(lhs.data, rhs.data, s, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two i16v2 with lhs scaled by a i16
SL_header i16v2 SL_i16v2subS(i16v2 lhs, i16v2 rhs, i16 s)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v2) {
        .x = lhs.x - rhs.x * s,
        .y = lhs.y - rhs.y * s
    };
}
#else
;
#endif
/// @brief Difference of two i16v3 with lhs scaled by a i16
SL_header i16v3 SL_i16v3subS(i16v3 lhs, i16v3 rhs, i16 s)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v3) {
        .x = lhs.x - rhs.x * s,
        .y = lhs.y - rhs.y * s,
        .z = lhs.z - rhs.z * s
    };
}
#else
;
#endif
/// @brief Difference of two i16v4 with lhs scaled by a i16
SL_header i16v4 SL_i16v4subS(i16v4 lhs, i16v4 rhs, i16 s)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v4) {
        .x = lhs.x - rhs.x * s,
        .y = lhs.y - rhs.y * s,
        .z = lhs.z - rhs.z * s,
        .w = lhs.w - rhs.w * s
    };
}
#else
;
#endif
/// @brief Addition of two i16v with lhs multiplied with a i16
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16* SL_i16vaddM_(i16* lhs, i16* rhs, i16* m, i16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] + rhs[i] * m[i];
    return dest;
}
#else
;
#endif
/// @brief Addition of two i16v with lhs multiplied with a i16
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16v SL_i16vaddM(i16v lhs, i16v rhs, i16v m, i16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i16vaddM_(lhs.data, rhs.data, m.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two i16v2 with lhs multiplied with a i16
SL_header i16v2 SL_i16v2addM(i16v2 lhs, i16v2 rhs, i16v2 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v2) {
        .x = lhs.x + rhs.x * m.x,
        .y = lhs.y + rhs.y * m.y
    };
}
#else
;
#endif
/// @brief Addition of two i16v3 with lhs multiplied with a i16
SL_header i16v3 SL_i16v3addM(i16v3 lhs, i16v3 rhs, i16v3 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v3) {
        .x = lhs.x + rhs.x * m.x,
        .y = lhs.y + rhs.y * m.y,
        .z = lhs.z + rhs.z * m.z
    };
}
#else
;
#endif
/// @brief Addition of two i16v4 with lhs multiplied with a i16
SL_header i16v4 SL_i16v4addM(i16v4 lhs, i16v4 rhs, i16v4 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v4) {
        .x = lhs.x + rhs.x * m.x,
        .y = lhs.y + rhs.y * m.y,
        .z = lhs.z + rhs.z * m.z,
        .w = lhs.w + rhs.w * m.w
    };
}
#else
;
#endif
/// @brief Difference of two i16v with lhs multiplied with a i16
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16* SL_i16vsubM_(i16* lhs, i16* rhs, i16* m, i16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] - rhs[i] * m[i];
    return dest;
}
#else
;
#endif
/// @brief Difference of two i16v with lhs multiplied with a i16
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16v SL_i16vsubM(i16v lhs, i16v rhs, i16v m, i16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i16vsubM_(lhs.data, rhs.data, m.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two i16v2 with lhs multiplied with a i16
SL_header i16v2 SL_i16v2subM(i16v2 lhs, i16v2 rhs, i16v2 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v2) {
        .x = lhs.x - rhs.x * m.x,
        .y = lhs.y - rhs.y * m.y
    };
}
#else
;
#endif
/// @brief Difference of two i16v3 with lhs multiplied with a i16
SL_header i16v3 SL_i16v3subM(i16v3 lhs, i16v3 rhs, i16v3 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v3) {
        .x = lhs.x - rhs.x * m.x,
        .y = lhs.y - rhs.y * m.y,
        .z = lhs.z - rhs.z * m.z
    };
}
#else
;
#endif
/// @brief Difference of two i16v4 with lhs multiplied with a i16
SL_header i16v4 SL_i16v4subM(i16v4 lhs, i16v4 rhs, i16v4 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v4) {
        .x = lhs.x - rhs.x * m.x,
        .y = lhs.y - rhs.y * m.y,
        .z = lhs.z - rhs.z * m.z,
        .w = lhs.w - rhs.w * m.w
    };
}
#else
;
#endif
/// @brief Addition of two i16v with lhs scaled by i16 and multiplied with a i16
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16* SL_i16vaddSM_(i16* lhs, i16* rhs, i16 s, i16* m, i16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] + rhs[i] * s * m[i];
    return dest;
}
#else
;
#endif
/// @brief Addition of two i16v with lhs scaled by i16 and multiplied with a i16
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16v SL_i16vaddSM(i16v lhs, i16v rhs, i16 s, i16v m, i16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i16vaddSM_(lhs.data, rhs.data, s, m.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two i16v2 with lhs scaled by i16 and multiplied with a i16
SL_header i16v2 SL_i16v2addSM(i16v2 lhs, i16v2 rhs, i16 s, i16v2 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v2) {
        .x = lhs.x + rhs.x * s * m.x,
        .y = lhs.y + rhs.y * s * m.y
    };
}
#else
;
#endif
/// @brief Addition of two i16v3 with lhs scaled by i16 and multiplied with a i16
SL_header i16v3 SL_i16v3addSM(i16v3 lhs, i16v3 rhs, i16 s, i16v3 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v3) {
        .x = lhs.x + rhs.x * s * m.x,
        .y = lhs.y + rhs.y * s * m.y,
        .z = lhs.z + rhs.z * s * m.z
    };
}
#else
;
#endif
/// @brief Addition of two i16v4 with lhs scaled by i16 and multiplied with a i16
SL_header i16v4 SL_i16v4addSM(i16v4 lhs, i16v4 rhs, i16 s, i16v4 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v4) {
        .x = lhs.x + rhs.x * s * m.x,
        .y = lhs.y + rhs.y * s * m.y,
        .z = lhs.z + rhs.z * s * m.z,
        .w = lhs.w + rhs.w * s * m.w
    };
}
#else
;
#endif
/// @brief Difference of two i16v with lhs scaled by i16 and multiplied with a i16
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16* SL_i16vsubSM_(i16* lhs, i16* rhs, i16 s, i16* m, i16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] - rhs[i] * s * m[i];
    return dest;
}
#else
;
#endif
/// @brief Difference of two i16v with lhs scaled by i16 and multiplied with a i16
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16v SL_i16vsubSM(i16v lhs, i16v rhs, i16 s, i16v m, i16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i16vsubSM_(lhs.data, rhs.data, s, m.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two i16v2 with lhs scaled by i16 and multiplied with a i16
SL_header i16v2 SL_i16v2subSM(i16v2 lhs, i16v2 rhs, i16 s, i16v2 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v2) {
        .x = lhs.x - rhs.x * s * m.x,
        .y = lhs.y - rhs.y * s * m.y
    };
}
#else
;
#endif
/// @brief Difference of two i16v3 with lhs scaled by i16 and multiplied with a i16
SL_header i16v3 SL_i16v3subSM(i16v3 lhs, i16v3 rhs, i16 s, i16v3 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v3) {
        .x = lhs.x - rhs.x * s * m.x,
        .y = lhs.y - rhs.y * s * m.y,
        .z = lhs.z - rhs.z * s * m.z
    };
}
#else
;
#endif
/// @brief Difference of two i16v4 with lhs scaled by i16 and multiplied with a i16
SL_header i16v4 SL_i16v4subSM(i16v4 lhs, i16v4 rhs, i16 s, i16v4 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v4) {
        .x = lhs.x - rhs.x * s * m.x,
        .y = lhs.y - rhs.y * s * m.y,
        .z = lhs.z - rhs.z * s * m.z,
        .w = lhs.w - rhs.w * s * m.w
    };
}
#else
;
#endif
/// @brief Addition of two i16v with rhs scaled by a i16
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16* SL_i16vSadd_(i16* lhs, i16 s, i16* rhs, i16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * s + rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Addition of two i16v with rhs scaled by a i16
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16v SL_i16vSadd(i16v lhs, i16 s, i16v rhs, i16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i16vSadd_(lhs.data, s, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two i16v2 with rhs scaled by a i16
SL_header i16v2 SL_i16v2Sadd(i16v2 lhs, i16 s, i16v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v2) {
        .x = lhs.x * s + rhs.x,
        .y = lhs.y * s + rhs.y
    };
}
#else
;
#endif
/// @brief Addition of two i16v3 with rhs scaled by a i16
SL_header i16v3 SL_i16v3Sadd(i16v3 lhs, i16 s, i16v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v3) {
        .x = lhs.x * s + rhs.x,
        .y = lhs.y * s + rhs.y,
        .z = lhs.z * s + rhs.z
    };
}
#else
;
#endif
/// @brief Addition of two i16v4 with rhs scaled by a i16
SL_header i16v4 SL_i16v4Sadd(i16v4 lhs, i16 s, i16v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v4) {
        .x = lhs.x * s + rhs.x,
        .y = lhs.y * s + rhs.y,
        .z = lhs.z * s + rhs.z,
        .w = lhs.w * s + rhs.w
    };
}
#else
;
#endif
/// @brief Difference of two i16v with rhs scaled by a i16
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16* SL_i16vSsub_(i16* lhs, i16 s, i16* rhs, i16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * s - rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Difference of two i16v with rhs scaled by a i16
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16v SL_i16vSsub(i16v lhs, i16 s, i16v rhs, i16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i16vSsub_(lhs.data, s, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two i16v2 with rhs scaled by a i16
SL_header i16v2 SL_i16v2Ssub(i16v2 lhs, i16 s, i16v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v2) {
        .x = lhs.x * s - rhs.x,
        .y = lhs.y * s - rhs.y
    };
}
#else
;
#endif
/// @brief Difference of two i16v3 with rhs scaled by a i16
SL_header i16v3 SL_i16v3Ssub(i16v3 lhs, i16 s, i16v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v3) {
        .x = lhs.x * s - rhs.x,
        .y = lhs.y * s - rhs.y,
        .z = lhs.z * s - rhs.z
    };
}
#else
;
#endif
/// @brief Difference of two i16v4 with rhs scaled by a i16
SL_header i16v4 SL_i16v4Ssub(i16v4 lhs, i16 s, i16v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v4) {
        .x = lhs.x * s - rhs.x,
        .y = lhs.y * s - rhs.y,
        .z = lhs.z * s - rhs.z,
        .w = lhs.w * s - rhs.w
    };
}
#else
;
#endif
/// @brief Weighted sum of two i16v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16* SL_i16vmix_(i16* lhs, i16 lhs_w, i16* rhs, i16 rhs_w, i16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * lhs_w + rhs[i] * rhs_w;
    return dest;
}
#else
;
#endif
/// @brief Weighted sum of two i16v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16v SL_i16vmix(i16v lhs, i16 lhs_w, i16v rhs, i16 rhs_w, i16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i16vmix_(lhs.data, lhs_w, rhs.data, rhs_w, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Weighted sum of two i16v2
SL_header i16v2 SL_i16v2mix(i16v2 lhs, i16 lhs_w, i16v2 rhs, i16 rhs_w)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v2) {
        .x = lhs.x * lhs_w + rhs.x * rhs_w,
        .y = lhs.y * lhs_w + rhs.y * rhs_w
    };
}
#else
;
#endif
/// @brief Weighted sum of two i16v3
SL_header i16v3 SL_i16v3mix(i16v3 lhs, i16 lhs_w, i16v3 rhs, i16 rhs_w)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v3) {
        .x = lhs.x * lhs_w + rhs.x * rhs_w,
        .y = lhs.y * lhs_w + rhs.y * rhs_w,
        .z = lhs.z * lhs_w + rhs.z * rhs_w
    };
}
#else
;
#endif
/// @brief Weighted sum of two i16v4
SL_header i16v4 SL_i16v4mix(i16v4 lhs, i16 lhs_w, i16v4 rhs, i16 rhs_w)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v4) {
        .x = lhs.x * lhs_w + rhs.x * rhs_w,
        .y = lhs.y * lhs_w + rhs.y * rhs_w,
        .z = lhs.z * lhs_w + rhs.z * rhs_w,
        .w = lhs.w * lhs_w + rhs.w * rhs_w
    };
}
#else
;
#endif
/// @brief Negation of a i16v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16* SL_i16vneg_(i16* v, i16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = -v[i];
    return dest;
}
#else
;
#endif
/// @brief Negation of a i16v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16v SL_i16vneg(i16v v, i16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i16vneg_(v.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Negation of a i16v2
SL_header i16v2 SL_i16v2neg(i16v2 v)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v2) {
        .x = -v.x,
        .y = -v.y
    };
}
#else
;
#endif
/// @brief Negation of a i16v3
SL_header i16v3 SL_i16v3neg(i16v3 v)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v3) {
        .x = -v.x,
        .y = -v.y,
        .z = -v.z
    };
}
#else
;
#endif
/// @brief Negation of a i16v4
SL_header i16v4 SL_i16v4neg(i16v4 v)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v4) {
        .x = -v.x,
        .y = -v.y,
        .z = -v.z,
        .w = -v.w
    };
}
#else
;
#endif
/// @brief Component-wise absolute value of a i16v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16* SL_i16vabs_(i16* v, i16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = v[i] < 0 ? -v[i] : v[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise absolute value of a i16v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16v SL_i16vabs(i16v v, i16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i16vabs_(v.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise absolute value of a i16v2
SL_header i16v2 SL_i16v2abs(i16v2 v)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v2) {
        .x = v.x < 0 ? -v.x : v.x,
        .y = v.y < 0 ? -v.y : v.y
    };
}
#else
;
#endif
/// @brief Component-wise absolute value of a i16v3
SL_header i16v3 SL_i16v3abs(i16v3 v)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v3) {
        .x = v.x < 0 ? -v.x : v.x,
        .y = v.y < 0 ? -v.y : v.y,
        .z = v.z < 0 ? -v.z : v.z
    };
}
#else
;
#endif
/// @brief Component-wise absolute value of a i16v4
SL_header i16v4 SL_i16v4abs(i16v4 v)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v4) {
        .x = v.x < 0 ? -v.x : v.x,
        .y = v.y < 0 ? -v.y : v.y,
        .z = v.z < 0 ? -v.z : v.z,
        .w = v.w < 0 ? -v.w : v.w
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two i16v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16* SL_i16vmin_(i16* lhs, i16* rhs, i16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] < rhs[i] ? lhs[i] : rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise minimum of two i16v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16v SL_i16vmin(i16v lhs, i16v rhs, i16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i16vmin_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise minimum of two i16v2
SL_header i16v2 SL_i16v2min(i16v2 lhs, i16v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v2) {
        .x = lhs.x < rhs.x ? lhs.x : rhs.x,
        .y = lhs.y < rhs.y ? lhs.y : rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two i16v3
SL_header i16v3 SL_i16v3min(i16v3 lhs, i16v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v3) {
        .x = lhs.x < rhs.x ? lhs.x : rhs.x,
        .y = lhs.y < rhs.y ? lhs.y : rhs.y,
        .z = lhs.z < rhs.z ? lhs.z : rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two i16v4
SL_header i16v4 SL_i16v4min(i16v4 lhs, i16v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v4) {
        .x = lhs.x < rhs.x ? lhs.x : rhs.x,
        .y = lhs.y < rhs.y ? lhs.y : rhs.y,
        .z = lhs.z < rhs.z ? lhs.z : rhs.z,
        .w = lhs.w < rhs.w ? lhs.w : rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two i16v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16* SL_i16vmax_(i16* lhs, i16* rhs, i16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] > rhs[i] ? lhs[i] : rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise maximum of two i16v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16v SL_i16vmax(i16v lhs, i16v rhs, i16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i16vmax_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise maximum of two i16v2
SL_header i16v2 SL_i16v2max(i16v2 lhs, i16v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v2) {
        .x = lhs.x > rhs.x ? lhs.x : rhs.x,
        .y = lhs.y > rhs.y ? lhs.y : rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two i16v3
SL_header i16v3 SL_i16v3max(i16v3 lhs, i16v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v3) {
        .x = lhs.x > rhs.x ? lhs.x : rhs.x,
        .y = lhs.y > rhs.y ? lhs.y : rhs.y,
        .z = lhs.z > rhs.z ? lhs.z : rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two i16v4
SL_header i16v4 SL_i16v4max(i16v4 lhs, i16v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v4) {
        .x = lhs.x > rhs.x ? lhs.x : rhs.x,
        .y = lhs.y > rhs.y ? lhs.y : rhs.y,
        .z = lhs.z > rhs.z ? lhs.z : rhs.z,
        .w = lhs.w > rhs.w ? lhs.w : rhs.w
    };
}
#else
;
#endif
/// @brief Dot product of two i16v
/// @note All vectors are assumed to be of size 'count'
SL_header i64 SL_i16vdot_(i16* lhs, i16* rhs, usize count)
#if defined(SL_IMPLEMENTATION)
{
    i64 dest = 0;
    for (usize i = 0; i < count; ++i) dest += lhs[i] * rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Dot product of two i16v
/// @note All vectors are assumed to be of size 'count'
SL_header i64 SL_i16vdot(i16v lhs, i16v rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i16vdot_(lhs.data, rhs.data, lhs.count);
}
#else
;
#endif
/// @brief Dot product of two i16v2
SL_header i64 SL_i16v2dot(i16v2 lhs, i16v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}
#else
;
#endif
/// @brief Dot product of two i16v3
SL_header i64 SL_i16v3dot(i16v3 lhs, i16v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}
#else
;
#endif
/// @brief Dot product of two i16v4
SL_header i64 SL_i16v4dot(i16v4 lhs, i16v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}
#else
;
#endif
/// @brief Maximum component of a i16v
/// @note All vectors are assumed to be of size 'count'
SL_header i64 SL_i16vlen_max_(i16* v, usize count)
#if defined(SL_IMPLEMENTATION)
{
    i64 dest = 0;
    for (usize i = 0; i < count; ++i) dest = llabs(v[i]) > dest ? llabs(v[i]) : dest;
    return dest;
}
#else
;
#endif
/// @brief Maximum component of a i16v
/// @note All vectors are assumed to be of size 'count'
SL_header i64 SL_i16vlen_max(i16v v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i16vlen_max_(v.data, v.count);
}
#else
;
#endif
/// @brief Maximum component of a i16v2
SL_header i64 SL_i16v2len_max(i16v2 v)
#if defined(SL_IMPLEMENTATION)
{
    v = SL_i16v2abs(v);
    return v.x > v.y ? v.x : v.y;
}
#else
;
#endif
/// @brief Maximum component of a i16v3
SL_header i64 SL_i16v3len_max(i16v3 v)
#if defined(SL_IMPLEMENTATION)
{
    v = SL_i16v3abs(v);
    return v.x > v.y ? (v.x > v.z ? v.x : v.z) : (v.y > v.z ? v.y : v.z);
}
#else
;
#endif
/// @brief Maximum component of a i16v4
SL_header i64 SL_i16v4len_max(i16v4 v)
#if defined(SL_IMPLEMENTATION)
{
    v = SL_i16v4abs(v);
    return v.x > v.y ? (v.x > v.z ? (v.x > v.w ? v.x : v.w) : (v.z > v.w ? v.z : v.w)) : (v.y > v.z ? (v.y > v.w ? v.y : v.w) : (v.z > v.w ? v.z : v.w));
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a i16v
/// @note All vectors are assumed to be of size 'count'
SL_header i64 SL_i16vlen_manh_(i16* v, usize count)
#if defined(SL_IMPLEMENTATION)
{
    i64 dest = 0;
    for (usize i = 0; i < count; ++i) dest += llabs(v[i]);
    return dest;
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a i16v
/// @note All vectors are assumed to be of size 'count'
SL_header i64 SL_i16vlen_manh(i16v v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i16vlen_manh_(v.data, v.count);
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a i16v2
SL_header i64 SL_i16v2len_manh(i16v2 v)
#if defined(SL_IMPLEMENTATION)
{
    v = SL_i16v2abs(v);
    return v.x + v.y;
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a i16v3
SL_header i64 SL_i16v3len_manh(i16v3 v)
#if defined(SL_IMPLEMENTATION)
{
    v = SL_i16v3abs(v);
    return v.x + v.y + v.z;
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a i16v4
SL_header i64 SL_i16v4len_manh(i16v4 v)
#if defined(SL_IMPLEMENTATION)
{
    v = SL_i16v4abs(v);
    return v.x + v.y + v.z + v.w;
}
#else
;
#endif
/// @brief Squared euclidean length of a i16v
/// @note All vectors are assumed to be of size 'count'
SL_header i64 SL_i16vlen_srq_(i16* v, usize count)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i16vdot_(v, v, count);
}
#else
;
#endif
/// @brief Squared euclidean length of a i16v
/// @note All vectors are assumed to be of size 'count'
SL_header i64 SL_i16vlen_srq(i16v v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i16vlen_srq_(v.data, v.count);
}
#else
;
#endif
/// @brief Square length of a i16v2
SL_header i64 SL_i16v2len_sqr(i16v2 v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i16v2dot(v, v);
}
#else
;
#endif
/// @brief Square length of a i16v3
SL_header i64 SL_i16v3len_sqr(i16v3 v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i16v3dot(v, v);
}
#else
;
#endif
/// @brief Square length of a i16v4
SL_header i64 SL_i16v4len_sqr(i16v4 v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i16v4dot(v, v);
}
#else
;
#endif
/// @brief Euclidean length of a i16v
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_i16vlen_(i16* v, usize count)
#if defined(SL_IMPLEMENTATION)
{
    return sqrt(SL_i16vdot_(v, v, count));
}
#else
;
#endif
/// @brief Euclidean length of a i16v
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_i16vlen(i16v v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i16vlen_(v.data, v.count);
}
#else
;
#endif
/// @brief Euclidean length of a i16v2
SL_header double SL_i16v2len(i16v2 v)
#if defined(SL_IMPLEMENTATION)
{
    return sqrt(SL_i16v2dot(v, v));
}
#else
;
#endif
/// @brief Euclidean length of a i16v3
SL_header double SL_i16v3len(i16v3 v)
#if defined(SL_IMPLEMENTATION)
{
    return sqrt(SL_i16v3dot(v, v));
}
#else
;
#endif
/// @brief Euclidean length of a i16v4
SL_header double SL_i16v4len(i16v4 v)
#if defined(SL_IMPLEMENTATION)
{
    return sqrt(SL_i16v4dot(v, v));
}
#else
;
#endif
/// @brief Euclidean distance bewteen two i16v
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_i16vdist_(i16* lhs, i16* rhs, usize count)
#if defined(SL_IMPLEMENTATION)
{
    double accum = 0;
    for (int i = 0; i < count; ++i) accum += (lhs[i] - rhs[i]) * (lhs[i] - rhs[i]);
    return sqrt(accum);
}
#else
;
#endif
/// @brief Euclidean distance bewteen two i16v
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_i16vdist(i16v lhs, i16v rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i16vdist_(lhs.data, rhs.data, lhs.count);
}
#else
;
#endif
/// @brief Euclidean distance between two i16v2
SL_header double SL_i16v2dist(i16v2 lhs, i16v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i16v2len(SL_i16v2sub(lhs, rhs));
}
#else
;
#endif
/// @brief Euclidean distance between two i16v3
SL_header double SL_i16v3dist(i16v3 lhs, i16v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i16v3len(SL_i16v3sub(lhs, rhs));
}
#else
;
#endif
/// @brief Euclidean distance between two i16v4
SL_header double SL_i16v4dist(i16v4 lhs, i16v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i16v4len(SL_i16v4sub(lhs, rhs));
}
#else
;
#endif
/// @brief Reflection of i16v2 v around vector i16v2 n
SL_header i16v2 SL_i16v2refl(i16v2 v, i16v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i16v2subS(v, n, 2.0 * SL_i16v2dot(v, n) / SL_i16v2dot(n, n));
}
#else
;
#endif
/// @brief Reflection of i16v3 v around vector i16v3 n
SL_header i16v3 SL_i16v3refl(i16v3 v, i16v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i16v3subS(v, n, 2.0 * SL_i16v3dot(v, n) / SL_i16v3dot(n, n));
}
#else
;
#endif
/// @brief Reflection of i16v4 v around vector i16v4 n
SL_header i16v4 SL_i16v4refl(i16v4 v, i16v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i16v4subS(v, n, 2.0 * SL_i16v4dot(v, n) / SL_i16v4dot(n, n));
}
#else
;
#endif
/// @brief Reflection of i16v2 v around vector i16v2 n assumed to be of unit length
SL_header i16v2 SL_i16v2refl_u(i16v2 v, i16v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i16v2subS(v, n, 2.0 * SL_i16v2dot(v, n));
}
#else
;
#endif
/// @brief Reflection of i16v3 v around vector i16v3 n assumed to be of unit length
SL_header i16v3 SL_i16v3refl_u(i16v3 v, i16v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i16v3subS(v, n, 2.0 * SL_i16v3dot(v, n));
}
#else
;
#endif
/// @brief Reflection of i16v4 v around vector i16v4 n assumed to be of unit length
SL_header i16v4 SL_i16v4refl_u(i16v4 v, i16v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i16v4subS(v, n, 2.0 * SL_i16v4dot(v, n));
}
#else
;
#endif
/// @brief Get component of i16v2 v in direction i16v2 n
SL_header i16v2 SL_i16v2align(i16v2 v, i16v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i16v2muls(n, SL_i16v2dot(v, n) / SL_i16v2dot(n, n));
}
#else
;
#endif
/// @brief Get component of i16v3 v in direction i16v3 n
SL_header i16v3 SL_i16v3align(i16v3 v, i16v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i16v3muls(n, SL_i16v3dot(v, n) / SL_i16v3dot(n, n));
}
#else
;
#endif
/// @brief Get component of i16v4 v in direction i16v4 n
SL_header i16v4 SL_i16v4align(i16v4 v, i16v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i16v4muls(n, SL_i16v4dot(v, n) / SL_i16v4dot(n, n));
}
#else
;
#endif
/// @brief Get component of i16v2 v in direction i16v2 n assumed to be of unit length
SL_header i16v2 SL_i16v2align_u(i16v2 v, i16v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i16v2muls(n, SL_i16v2dot(v, n));
}
#else
;
#endif
/// @brief Get component of i16v3 v in direction i16v3 n assumed to be of unit length
SL_header i16v3 SL_i16v3align_u(i16v3 v, i16v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i16v3muls(n, SL_i16v3dot(v, n));
}
#else
;
#endif
/// @brief Get component of i16v4 v in direction i16v4 n assumed to be of unit length
SL_header i16v4 SL_i16v4align_u(i16v4 v, i16v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i16v4muls(n, SL_i16v4dot(v, n));
}
#else
;
#endif
/// @brief Project i16v2 v on plane with normal i16v2 n
SL_header i16v2 SL_i16v2proj(i16v2 v, i16v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i16v2sub(v, SL_i16v2align(v, n));
}
#else
;
#endif
/// @brief Project i16v3 v on plane with normal i16v3 n
SL_header i16v3 SL_i16v3proj(i16v3 v, i16v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i16v3sub(v, SL_i16v3align(v, n));
}
#else
;
#endif
/// @brief Project i16v4 v on plane with normal i16v4 n
SL_header i16v4 SL_i16v4proj(i16v4 v, i16v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i16v4sub(v, SL_i16v4align(v, n));
}
#else
;
#endif
/// @brief Project i16v2 v on plane with normal i16v2 n
SL_header i16v2 SL_i16v2proj_u(i16v2 v, i16v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i16v2sub(v, SL_i16v2align_u(v, n));
}
#else
;
#endif
/// @brief Project i16v3 v on plane with normal i16v3 n
SL_header i16v3 SL_i16v3proj_u(i16v3 v, i16v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i16v3sub(v, SL_i16v3align_u(v, n));
}
#else
;
#endif
/// @brief Project i16v4 v on plane with normal i16v4 n
SL_header i16v4 SL_i16v4proj_u(i16v4 v, i16v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i16v4sub(v, SL_i16v4align_u(v, n));
}
#else
;
#endif
/// @brief Component-wise modulo of a i16v by scalar n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16* SL_i16vmods_(i16* v, i16 n, i16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = v[i] % n;
    return dest;
}
#else
;
#endif
/// @brief Component-wise modulo of a i16v by scalar n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16v SL_i16vmods(i16v v, i16 n, i16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i16vmods_(v.data, n, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise modulo of a i16v2 by scalar n
SL_header i16v2 SL_i16v2mods(i16v2 v, i16 n)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v2) {
        .x = v.x % n,
        .y = v.y % n
    };
}
#else
;
#endif
/// @brief Component-wise modulo of a i16v3 by scalar n
SL_header i16v3 SL_i16v3mods(i16v3 v, i16 n)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v3) {
        .x = v.x % n,
        .y = v.y % n,
        .z = v.z % n
    };
}
#else
;
#endif
/// @brief Component-wise modulo of a i16v4 by scalar n
SL_header i16v4 SL_i16v4mods(i16v4 v, i16 n)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v4) {
        .x = v.x % n,
        .y = v.y % n,
        .z = v.z % n,
        .w = v.w % n
    };
}
#else
;
#endif
/// @brief Component-wise modulo of a i16v by i16v n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16* SL_i16vmod_(i16* v, i16* n, i16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = v[i] % n[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise modulo of a i16v by i16v n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16v SL_i16vmod(i16v v, i16v n, i16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i16vmod_(v.data, n.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise modulo of a i16v2 by i16v2 n
SL_header i16v2 SL_i16v2mod(i16v2 v, i16v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v2) {
        .x = v.x % n.x,
        .y = v.y % n.y
    };
}
#else
;
#endif
/// @brief Component-wise modulo of a i16v3 by i16v3 n
SL_header i16v3 SL_i16v3mod(i16v3 v, i16v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v3) {
        .x = v.x % n.x,
        .y = v.y % n.y,
        .z = v.z % n.z
    };
}
#else
;
#endif
/// @brief Component-wise modulo of a i16v4 by i16v4 n
SL_header i16v4 SL_i16v4mod(i16v4 v, i16v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v4) {
        .x = v.x % n.x,
        .y = v.y % n.y,
        .z = v.z % n.z,
        .w = v.w % n.w
    };
}
#else
;
#endif
/// @brief Cross-product of two i16v2
SL_header i64 SL_i16v2cross(i16v2 lhs, i16v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x * rhs.y - lhs.y * rhs.x;
}
#else
;
#endif
/// @brief Cross-product of two i16v3
SL_header i16v3 SL_i16v3cross(i16v3 lhs, i16v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v3) {
        .x = lhs.y * rhs.z - lhs.z * rhs.y,
        .y = lhs.z * rhs.x - lhs.x * rhs.z,
        .z = lhs.x * rhs.y - lhs.y * rhs.x
    };
}
#else
;
#endif
/// @brief Component-wise binary AND of two i16v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16* SL_i16vand_(i16* lhs, i16* rhs, i16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] & rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary AND of two i16v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16v SL_i16vand(i16v lhs, i16v rhs, i16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i16vand_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary AND of two i16v2
SL_header i16v2 SL_i16v2and(i16v2 lhs, i16v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v2) {
        .x = lhs.x & rhs.x,
        .y = lhs.y & rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise binary AND of two i16v3
SL_header i16v3 SL_i16v3and(i16v3 lhs, i16v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v3) {
        .x = lhs.x & rhs.x,
        .y = lhs.y & rhs.y,
        .z = lhs.z & rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise binary AND of two i16v4
SL_header i16v4 SL_i16v4and(i16v4 lhs, i16v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v4) {
        .x = lhs.x & rhs.x,
        .y = lhs.y & rhs.y,
        .z = lhs.z & rhs.z,
        .w = lhs.w & rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise binary OR of two i16v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16* SL_i16vor_(i16* lhs, i16* rhs, i16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] | rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary OR of two i16v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16v SL_i16vor(i16v lhs, i16v rhs, i16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i16vor_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary OR of two i16v2
SL_header i16v2 SL_i16v2or(i16v2 lhs, i16v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v2) {
        .x = lhs.x | rhs.x,
        .y = lhs.y | rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise binary OR of two i16v3
SL_header i16v3 SL_i16v3or(i16v3 lhs, i16v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v3) {
        .x = lhs.x | rhs.x,
        .y = lhs.y | rhs.y,
        .z = lhs.z | rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise binary OR of two i16v4
SL_header i16v4 SL_i16v4or(i16v4 lhs, i16v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v4) {
        .x = lhs.x | rhs.x,
        .y = lhs.y | rhs.y,
        .z = lhs.z | rhs.z,
        .w = lhs.w | rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise binary XOR of two i16v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16* SL_i16vxor_(i16* lhs, i16* rhs, i16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] ^ rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary XOR of two i16v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16v SL_i16vxor(i16v lhs, i16v rhs, i16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i16vxor_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary XOR of two i16v2
SL_header i16v2 SL_i16v2xor(i16v2 lhs, i16v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v2) {
        .x = lhs.x ^ rhs.x,
        .y = lhs.y ^ rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise binary XOR of two i16v3
SL_header i16v3 SL_i16v3xor(i16v3 lhs, i16v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v3) {
        .x = lhs.x ^ rhs.x,
        .y = lhs.y ^ rhs.y,
        .z = lhs.z ^ rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise binary XOR of two i16v4
SL_header i16v4 SL_i16v4xor(i16v4 lhs, i16v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v4) {
        .x = lhs.x ^ rhs.x,
        .y = lhs.y ^ rhs.y,
        .z = lhs.z ^ rhs.z,
        .w = lhs.w ^ rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise binary NOT of a i16v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16* SL_i16vnot_(i16* v, i16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = ~v[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary NOT of a i16v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16v SL_i16vnot(i16v v, i16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i16vnot_(v.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary NOT of a i16v2
SL_header i16v2 SL_i16v2not(i16v2 v)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v2) {
        .x = ~v.x,
        .y = ~v.y
    };
}
#else
;
#endif
/// @brief Component-wise binary NOT of a i16v3
SL_header i16v3 SL_i16v3not(i16v3 v)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v3) {
        .x = ~v.x,
        .y = ~v.y,
        .z = ~v.z
    };
}
#else
;
#endif
/// @brief Component-wise binary NOT of a i16v4
SL_header i16v4 SL_i16v4not(i16v4 v)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v4) {
        .x = ~v.x,
        .y = ~v.y,
        .z = ~v.z,
        .w = ~v.w
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a i16v by integer n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16* SL_i16vlshfts_(i16* lhs, i16 rhs, i16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] << rhs;
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a i16v by integer n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16v SL_i16vlshfts(i16v lhs, i16 rhs, i16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i16vlshfts_(lhs.data, rhs, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a i16v2 by integer n
SL_header i16v2 SL_i16v2lshfts(i16v2 lhs, i16 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v2) {
        .x = lhs.x << rhs,
        .y = lhs.y << rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a i16v3 by integer n
SL_header i16v3 SL_i16v3lshfts(i16v3 lhs, i16 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v3) {
        .x = lhs.x << rhs,
        .y = lhs.y << rhs,
        .z = lhs.z << rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a i16v4 by integer n
SL_header i16v4 SL_i16v4lshfts(i16v4 lhs, i16 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v4) {
        .x = lhs.x << rhs,
        .y = lhs.y << rhs,
        .z = lhs.z << rhs,
        .w = lhs.w << rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a i16v by i16v n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16* SL_i16vlshft_(i16* lhs, i16* rhs, i16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] << rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a i16v by i16v n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16v SL_i16vlshft(i16v lhs, i16v rhs, i16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i16vlshft_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a i16v2 by i16v2 n
SL_header i16v2 SL_i16v2lshft(i16v2 lhs, i16v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v2) {
        .x = lhs.x << rhs.x,
        .y = lhs.y << rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a i16v3 by i16v3 n
SL_header i16v3 SL_i16v3lshft(i16v3 lhs, i16v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v3) {
        .x = lhs.x << rhs.x,
        .y = lhs.y << rhs.y,
        .z = lhs.z << rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a i16v4 by i16v4 n
SL_header i16v4 SL_i16v4lshft(i16v4 lhs, i16v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v4) {
        .x = lhs.x << rhs.x,
        .y = lhs.y << rhs.y,
        .z = lhs.z << rhs.z,
        .w = lhs.w << rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a i16v by interger n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16* SL_i16vrshfts_(i16* lhs, i16 rhs, i16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] >> rhs;
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a i16v by interger n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16v SL_i16vrshfts(i16v lhs, i16 rhs, i16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i16vrshfts_(lhs.data, rhs, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a i16v2 by interger n
SL_header i16v2 SL_i16v2rshfts(i16v2 lhs, i16 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v2) {
        .x = lhs.x >> rhs,
        .y = lhs.y >> rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a i16v3 by interger n
SL_header i16v3 SL_i16v3rshfts(i16v3 lhs, i16 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v3) {
        .x = lhs.x >> rhs,
        .y = lhs.y >> rhs,
        .z = lhs.z >> rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a i16v4 by interger n
SL_header i16v4 SL_i16v4rshfts(i16v4 lhs, i16 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v4) {
        .x = lhs.x >> rhs,
        .y = lhs.y >> rhs,
        .z = lhs.z >> rhs,
        .w = lhs.w >> rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a i16v by i16v n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16* SL_i16vrshft_(i16* lhs, i16* rhs, i16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] >> rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a i16v by i16v n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i16v SL_i16vrshft(i16v lhs, i16v rhs, i16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i16vrshft_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a i16v2 by i16v2 n
SL_header i16v2 SL_i16v2rshft(i16v2 lhs, i16v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v2) {
        .x = lhs.x >> rhs.x,
        .y = lhs.y >> rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a i16v3 by i16v3 n
SL_header i16v3 SL_i16v3rshft(i16v3 lhs, i16v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v3) {
        .x = lhs.x >> rhs.x,
        .y = lhs.y >> rhs.y,
        .z = lhs.z >> rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a i16v4 by i16v4 n
SL_header i16v4 SL_i16v4rshft(i16v4 lhs, i16v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i16v4) {
        .x = lhs.x >> rhs.x,
        .y = lhs.y >> rhs.y,
        .z = lhs.z >> rhs.z,
        .w = lhs.w >> rhs.w
    };
}
#else
;
#endif
#pragma endregion I16
#pragma region I32

/// @brief Vector of i32 with arbitrary dimension
typedef struct {
    const usize count;
    i32 *data;
} i32v;

/// @brief Vector of i32 with dimension 2
typedef union {
    i32 data[2];
    struct {
        union { i32 x, r, u; };
        union { i32 y, g, v; };
    };
} i32v2;

#define SL_i32v2_zero  ((i32v2){.x =  0, .y =  0})
#define SL_i32v2_one   ((i32v2){.x =  1, .y =  1})
#define SL_i32v2_right ((i32v2){.x =  1, .y =  0})
#define SL_i32v2_up    ((i32v2){.x =  0, .y =  1})
#define SL_i32v2_left  ((i32v2){.x = -1, .y =  0})
#define SL_i32v2_down  ((i32v2){.x =  0, .y = -1})

/// @brief Vector of i32 with dimension 3
typedef union {
    i32 data[3];
    struct {
        union { i32 x, r, u; };
        union { i32 y, g, v; };
        union { i32 z, b, s; };
    };
    struct {
        union { i32 __x, __r, __u; };
        union { i32v2 yz, gb, vs; };
    };
    struct {
        union { i32v2 xy, rg, uv; };
        union { i32 __z, __b, __s; };
    };
} i32v3;

#define SL_i32v3_zero  ((i32v3){.x =  0, .y =  0, .z =  0})
#define SL_i32v3_one   ((i32v3){.x =  1, .y =  1, .z =  1})
#define SL_i32v3_right ((i32v3){.x =  1, .y =  0, .z =  0})
#define SL_i32v3_up    ((i32v3){.x =  0, .y =  1, .z =  0})
#define SL_i32v3_forw  ((i32v3){.x =  0, .y =  0, .z =  1})
#define SL_i32v3_left  ((i32v3){.x = -1, .y =  0, .z =  0})
#define SL_i32v3_down  ((i32v3){.x =  0, .y = -1, .z =  0})
#define SL_i32v3_back  ((i32v3){.x =  0, .y =  0, .z = -1})

/// @brief Vector of i32 with dimension 4
typedef union {
    i32 data[4];
    struct {
        union { i32 x, r, u; };
        union { i32 y, g, v; };
        union { i32 z, b, s; };
        union { i32 w, a, t; };
    };
    struct {
        union { i32 __x0, __r0, __u0; };
        union { i32v2 yz, gb, vs; };
        union { i32 __w0, __a0, __t0; };
    };
    struct {
        union { i32v2 xy, rb, uv; };
        union { i32v2 zw, ba, st; };
    };
    struct {
        union { i32v3 xyz, rgb, uvs; };
        union { i32 __w1, __a1, __t1; };
    };
    struct {
        union { i32 __x1, __r1, __u1; };
        union { i32v3 yzw, gba, vst; };
    };
} i32v4;

#define SL_i32v4_zero  ((i32v4){.x = 0, .y = 0, .z = 0, .w = 0})
#define SL_i32v4_one   ((i32v4){.x = 1, .y = 1, .z = 1, .w = 1})

#define SL_i32v4_white  ((i32v4){.x = 1, .y = 1, .z = 1, .w = 1})
#define SL_i32v4_black  ((i32v4){.x = 0, .y = 0, .z = 0, .w = 1})
#define SL_i32v4_red    ((i32v4){.x = 1, .y = 0, .z = 0, .w = 1})
#define SL_i32v4_green  ((i32v4){.x = 0, .y = 1, .z = 0, .w = 1})
#define SL_i32v4_blue   ((i32v4){.x = 0, .y = 0, .z = 1, .w = 1})
#define SL_i32v4_yellow ((i32v4){.x = 1, .y = 1, .z = 0, .w = 1})
#define SL_i32v4_cyan   ((i32v4){.x = 0, .y = 1, .z = 1, .w = 1})
#define SL_i32v4_purple ((i32v4){.x = 1, .y = 0, .z = 1, .w = 1})



#define SL_i32v2_(X, Y)       ((i32v2){.x = X, .y = Y})
#define SL_i32v3_(X, Y, Z)    ((i32v3){.x = X, .y = Y, .z = Z})
#define SL_i32v4_(X, Y, Z, W) ((i32v4){.x = X, .y = Y, .z = Z, .w = W})

#define SL_i32v2s(S)          ((i32v2){.x = S, .y = S})
#define SL_i32v3s(S)          ((i32v3){.x = S, .y = S, .z = S})
#define SL_i32v4s(S)          ((i32v4){.x = S, .y = S, .z = S, .w = S})

#define SL_i32vv(V)           ((i32v){.count = vsize(V), .data = (V).data})
#define SL_i32v2v(V, ...)     ((i32v2){.x = (V).x, .y = (V).y})
#define SL_i32v3v(V, ...)     ((i32v3){.x = (V).x, .y = (V).y, .z = (SL_vsize(V) >= 3 ? (V).data[2] : (0, ##__VA_ARGS__))})
#define SL_i32v4v(V, ...)     ((i32v4){.x = (V).x, .y = (V).y, .z = (SL_vsize(V) >= 3 ? (V).data[2] : ((const float[]){0, ##__VA_ARGS__, 0})[1]), .w = (SL_vsize(V) >= 4 ? (V).data[3] : ((const float[]){0, ##__VA_ARGS__, 0, 0})[2])})



/// @brief Equality of two i32v
/// @note All vectors are assumed to be of size 'count'
SL_header bool SL_i32vequ_(i32* lhs, i32* rhs, usize count)
#if defined(SL_IMPLEMENTATION)
{
    bool dest = true;
    for (usize i = 0; i < count; ++i) dest &= lhs[i] == rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Equality of two i32v
/// @note All vectors are assumed to be of size 'count'
SL_header bool SL_i32vequ(i32v lhs, i32v rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i32vequ_(lhs.data, rhs.data, lhs.count);
}
#else
;
#endif
/// @brief Equality of two i32v2
SL_header bool SL_i32v2equ(i32v2 lhs, i32v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}
#else
;
#endif
/// @brief Equality of two i32v3
SL_header bool SL_i32v3equ(i32v3 lhs, i32v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}
#else
;
#endif
/// @brief Equality of two i32v4
SL_header bool SL_i32v4equ(i32v4 lhs, i32v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
}
#else
;
#endif
/// @brief Addition of two i32v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32* SL_i32vadd_(i32* lhs, i32* rhs, i32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] + rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Addition of two i32v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32v SL_i32vadd(i32v lhs, i32v rhs, i32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i32vadd_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two i32v2
SL_header i32v2 SL_i32v2add(i32v2 lhs, i32v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v2) {
        .x = lhs.x + rhs.x,
        .y = lhs.y + rhs.y
    };
}
#else
;
#endif
/// @brief Addition of two i32v3
SL_header i32v3 SL_i32v3add(i32v3 lhs, i32v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v3) {
        .x = lhs.x + rhs.x,
        .y = lhs.y + rhs.y,
        .z = lhs.z + rhs.z
    };
}
#else
;
#endif
/// @brief Addition of two i32v4
SL_header i32v4 SL_i32v4add(i32v4 lhs, i32v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v4) {
        .x = lhs.x + rhs.x,
        .y = lhs.y + rhs.y,
        .z = lhs.z + rhs.z,
        .w = lhs.w + rhs.w
    };
}
#else
;
#endif
/// @brief Difference of two i32v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32* SL_i32vsub_(i32* lhs, i32* rhs, i32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] - rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Difference of two i32v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32v SL_i32vsub(i32v lhs, i32v rhs, i32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i32vsub_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two i32v2
SL_header i32v2 SL_i32v2sub(i32v2 lhs, i32v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v2) {
        .x = lhs.x - rhs.x,
        .y = lhs.y - rhs.y
    };
}
#else
;
#endif
/// @brief Difference of two i32v3
SL_header i32v3 SL_i32v3sub(i32v3 lhs, i32v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v3) {
        .x = lhs.x - rhs.x,
        .y = lhs.y - rhs.y,
        .z = lhs.z - rhs.z
    };
}
#else
;
#endif
/// @brief Difference of two i32v4
SL_header i32v4 SL_i32v4sub(i32v4 lhs, i32v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v4) {
        .x = lhs.x - rhs.x,
        .y = lhs.y - rhs.y,
        .z = lhs.z - rhs.z,
        .w = lhs.w - rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of two i32v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32* SL_i32vmul_(i32* lhs, i32* rhs, i32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise multiplication of two i32v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32v SL_i32vmul(i32v lhs, i32v rhs, i32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i32vmul_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise multiplication of two i32v2
SL_header i32v2 SL_i32v2mul(i32v2 lhs, i32v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v2) {
        .x = lhs.x * rhs.x,
        .y = lhs.y * rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of two i32v3
SL_header i32v3 SL_i32v3mul(i32v3 lhs, i32v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v3) {
        .x = lhs.x * rhs.x,
        .y = lhs.y * rhs.y,
        .z = lhs.z * rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of two i32v4
SL_header i32v4 SL_i32v4mul(i32v4 lhs, i32v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v4) {
        .x = lhs.x * rhs.x,
        .y = lhs.y * rhs.y,
        .z = lhs.z * rhs.z,
        .w = lhs.w * rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of a i32v with a scalar
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32* SL_i32vmuls_(i32* lhs, i32 rhs, i32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * rhs;
    return dest;
}
#else
;
#endif
/// @brief Component-wise multiplication of a i32v with a scalar
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32v SL_i32vmuls(i32v lhs, i32 rhs, i32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i32vmuls_(lhs.data, rhs, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise multiplication of a i32v2 with a scalar
SL_header i32v2 SL_i32v2muls(i32v2 lhs, i32 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v2) {
        .x = lhs.x * rhs,
        .y = lhs.y * rhs
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of a i32v3 with a scalar
SL_header i32v3 SL_i32v3muls(i32v3 lhs, i32 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v3) {
        .x = lhs.x * rhs,
        .y = lhs.y * rhs,
        .z = lhs.z * rhs
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of a i32v4 with a scalar
SL_header i32v4 SL_i32v4muls(i32v4 lhs, i32 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v4) {
        .x = lhs.x * rhs,
        .y = lhs.y * rhs,
        .z = lhs.z * rhs,
        .w = lhs.w * rhs
    };
}
#else
;
#endif
/// @brief Component-wise division of two i32v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32* SL_i32vdiv_(i32* lhs, i32* rhs, i32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] / rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise division of two i32v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32v SL_i32vdiv(i32v lhs, i32v rhs, i32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i32vdiv_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise division of two i32v2
SL_header i32v2 SL_i32v2div(i32v2 lhs, i32v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v2) {
        .x = lhs.x / rhs.x,
        .y = lhs.y / rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise division of two i32v3
SL_header i32v3 SL_i32v3div(i32v3 lhs, i32v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v3) {
        .x = lhs.x / rhs.x,
        .y = lhs.y / rhs.y,
        .z = lhs.z / rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise division of two i32v4
SL_header i32v4 SL_i32v4div(i32v4 lhs, i32v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v4) {
        .x = lhs.x / rhs.x,
        .y = lhs.y / rhs.y,
        .z = lhs.z / rhs.z,
        .w = lhs.w / rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise division of a i32v with a scalar
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32* SL_i32vdivs_(i32* lhs, i32 rhs, i32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] / rhs;
    return dest;
}
#else
;
#endif
/// @brief Component-wise division of a i32v with a scalar
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32v SL_i32vdivs(i32v lhs, i32 rhs, i32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i32vdivs_(lhs.data, rhs, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise division of a i32v2 with a scalar
SL_header i32v2 SL_i32v2divs(i32v2 lhs, i32 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v2) {
        .x = lhs.x / rhs,
        .y = lhs.y / rhs
    };
}
#else
;
#endif
/// @brief Component-wise division of a i32v3 with a scalar
SL_header i32v3 SL_i32v3divs(i32v3 lhs, i32 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v3) {
        .x = lhs.x / rhs,
        .y = lhs.y / rhs,
        .z = lhs.z / rhs
    };
}
#else
;
#endif
/// @brief Component-wise division of a i32v4 with a scalar
SL_header i32v4 SL_i32v4divs(i32v4 lhs, i32 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v4) {
        .x = lhs.x / rhs,
        .y = lhs.y / rhs,
        .z = lhs.z / rhs,
        .w = lhs.w / rhs
    };
}
#else
;
#endif
/// @brief Addition of two i32v with lhs scaled by a i32
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32* SL_i32vaddS_(i32* lhs, i32* rhs, i32 s, i32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] + rhs[i] * s;
    return dest;
}
#else
;
#endif
/// @brief Addition of two i32v with lhs scaled by a i32
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32v SL_i32vaddS(i32v lhs, i32v rhs, i32 s, i32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i32vaddS_(lhs.data, rhs.data, s, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two i32v2 with lhs scaled by a i32
SL_header i32v2 SL_i32v2addS(i32v2 lhs, i32v2 rhs, i32 s)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v2) {
        .x = lhs.x + rhs.x * s,
        .y = lhs.y + rhs.y * s
    };
}
#else
;
#endif
/// @brief Addition of two i32v3 with lhs scaled by a i32
SL_header i32v3 SL_i32v3addS(i32v3 lhs, i32v3 rhs, i32 s)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v3) {
        .x = lhs.x + rhs.x * s,
        .y = lhs.y + rhs.y * s,
        .z = lhs.z + rhs.z * s
    };
}
#else
;
#endif
/// @brief Addition of two i32v4 with lhs scaled by a i32
SL_header i32v4 SL_i32v4addS(i32v4 lhs, i32v4 rhs, i32 s)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v4) {
        .x = lhs.x + rhs.x * s,
        .y = lhs.y + rhs.y * s,
        .z = lhs.z + rhs.z * s,
        .w = lhs.w + rhs.w * s
    };
}
#else
;
#endif
/// @brief Difference of two i32v with lhs scaled by a i32
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32* SL_i32vsubS_(i32* lhs, i32* rhs, i32 s, i32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] - rhs[i] * s;
    return dest;
}
#else
;
#endif
/// @brief Difference of two i32v with lhs scaled by a i32
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32v SL_i32vsubS(i32v lhs, i32v rhs, i32 s, i32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i32vsubS_(lhs.data, rhs.data, s, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two i32v2 with lhs scaled by a i32
SL_header i32v2 SL_i32v2subS(i32v2 lhs, i32v2 rhs, i32 s)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v2) {
        .x = lhs.x - rhs.x * s,
        .y = lhs.y - rhs.y * s
    };
}
#else
;
#endif
/// @brief Difference of two i32v3 with lhs scaled by a i32
SL_header i32v3 SL_i32v3subS(i32v3 lhs, i32v3 rhs, i32 s)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v3) {
        .x = lhs.x - rhs.x * s,
        .y = lhs.y - rhs.y * s,
        .z = lhs.z - rhs.z * s
    };
}
#else
;
#endif
/// @brief Difference of two i32v4 with lhs scaled by a i32
SL_header i32v4 SL_i32v4subS(i32v4 lhs, i32v4 rhs, i32 s)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v4) {
        .x = lhs.x - rhs.x * s,
        .y = lhs.y - rhs.y * s,
        .z = lhs.z - rhs.z * s,
        .w = lhs.w - rhs.w * s
    };
}
#else
;
#endif
/// @brief Addition of two i32v with lhs multiplied with a i32
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32* SL_i32vaddM_(i32* lhs, i32* rhs, i32* m, i32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] + rhs[i] * m[i];
    return dest;
}
#else
;
#endif
/// @brief Addition of two i32v with lhs multiplied with a i32
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32v SL_i32vaddM(i32v lhs, i32v rhs, i32v m, i32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i32vaddM_(lhs.data, rhs.data, m.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two i32v2 with lhs multiplied with a i32
SL_header i32v2 SL_i32v2addM(i32v2 lhs, i32v2 rhs, i32v2 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v2) {
        .x = lhs.x + rhs.x * m.x,
        .y = lhs.y + rhs.y * m.y
    };
}
#else
;
#endif
/// @brief Addition of two i32v3 with lhs multiplied with a i32
SL_header i32v3 SL_i32v3addM(i32v3 lhs, i32v3 rhs, i32v3 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v3) {
        .x = lhs.x + rhs.x * m.x,
        .y = lhs.y + rhs.y * m.y,
        .z = lhs.z + rhs.z * m.z
    };
}
#else
;
#endif
/// @brief Addition of two i32v4 with lhs multiplied with a i32
SL_header i32v4 SL_i32v4addM(i32v4 lhs, i32v4 rhs, i32v4 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v4) {
        .x = lhs.x + rhs.x * m.x,
        .y = lhs.y + rhs.y * m.y,
        .z = lhs.z + rhs.z * m.z,
        .w = lhs.w + rhs.w * m.w
    };
}
#else
;
#endif
/// @brief Difference of two i32v with lhs multiplied with a i32
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32* SL_i32vsubM_(i32* lhs, i32* rhs, i32* m, i32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] - rhs[i] * m[i];
    return dest;
}
#else
;
#endif
/// @brief Difference of two i32v with lhs multiplied with a i32
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32v SL_i32vsubM(i32v lhs, i32v rhs, i32v m, i32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i32vsubM_(lhs.data, rhs.data, m.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two i32v2 with lhs multiplied with a i32
SL_header i32v2 SL_i32v2subM(i32v2 lhs, i32v2 rhs, i32v2 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v2) {
        .x = lhs.x - rhs.x * m.x,
        .y = lhs.y - rhs.y * m.y
    };
}
#else
;
#endif
/// @brief Difference of two i32v3 with lhs multiplied with a i32
SL_header i32v3 SL_i32v3subM(i32v3 lhs, i32v3 rhs, i32v3 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v3) {
        .x = lhs.x - rhs.x * m.x,
        .y = lhs.y - rhs.y * m.y,
        .z = lhs.z - rhs.z * m.z
    };
}
#else
;
#endif
/// @brief Difference of two i32v4 with lhs multiplied with a i32
SL_header i32v4 SL_i32v4subM(i32v4 lhs, i32v4 rhs, i32v4 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v4) {
        .x = lhs.x - rhs.x * m.x,
        .y = lhs.y - rhs.y * m.y,
        .z = lhs.z - rhs.z * m.z,
        .w = lhs.w - rhs.w * m.w
    };
}
#else
;
#endif
/// @brief Addition of two i32v with lhs scaled by i32 and multiplied with a i32
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32* SL_i32vaddSM_(i32* lhs, i32* rhs, i32 s, i32* m, i32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] + rhs[i] * s * m[i];
    return dest;
}
#else
;
#endif
/// @brief Addition of two i32v with lhs scaled by i32 and multiplied with a i32
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32v SL_i32vaddSM(i32v lhs, i32v rhs, i32 s, i32v m, i32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i32vaddSM_(lhs.data, rhs.data, s, m.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two i32v2 with lhs scaled by i32 and multiplied with a i32
SL_header i32v2 SL_i32v2addSM(i32v2 lhs, i32v2 rhs, i32 s, i32v2 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v2) {
        .x = lhs.x + rhs.x * s * m.x,
        .y = lhs.y + rhs.y * s * m.y
    };
}
#else
;
#endif
/// @brief Addition of two i32v3 with lhs scaled by i32 and multiplied with a i32
SL_header i32v3 SL_i32v3addSM(i32v3 lhs, i32v3 rhs, i32 s, i32v3 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v3) {
        .x = lhs.x + rhs.x * s * m.x,
        .y = lhs.y + rhs.y * s * m.y,
        .z = lhs.z + rhs.z * s * m.z
    };
}
#else
;
#endif
/// @brief Addition of two i32v4 with lhs scaled by i32 and multiplied with a i32
SL_header i32v4 SL_i32v4addSM(i32v4 lhs, i32v4 rhs, i32 s, i32v4 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v4) {
        .x = lhs.x + rhs.x * s * m.x,
        .y = lhs.y + rhs.y * s * m.y,
        .z = lhs.z + rhs.z * s * m.z,
        .w = lhs.w + rhs.w * s * m.w
    };
}
#else
;
#endif
/// @brief Difference of two i32v with lhs scaled by i32 and multiplied with a i32
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32* SL_i32vsubSM_(i32* lhs, i32* rhs, i32 s, i32* m, i32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] - rhs[i] * s * m[i];
    return dest;
}
#else
;
#endif
/// @brief Difference of two i32v with lhs scaled by i32 and multiplied with a i32
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32v SL_i32vsubSM(i32v lhs, i32v rhs, i32 s, i32v m, i32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i32vsubSM_(lhs.data, rhs.data, s, m.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two i32v2 with lhs scaled by i32 and multiplied with a i32
SL_header i32v2 SL_i32v2subSM(i32v2 lhs, i32v2 rhs, i32 s, i32v2 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v2) {
        .x = lhs.x - rhs.x * s * m.x,
        .y = lhs.y - rhs.y * s * m.y
    };
}
#else
;
#endif
/// @brief Difference of two i32v3 with lhs scaled by i32 and multiplied with a i32
SL_header i32v3 SL_i32v3subSM(i32v3 lhs, i32v3 rhs, i32 s, i32v3 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v3) {
        .x = lhs.x - rhs.x * s * m.x,
        .y = lhs.y - rhs.y * s * m.y,
        .z = lhs.z - rhs.z * s * m.z
    };
}
#else
;
#endif
/// @brief Difference of two i32v4 with lhs scaled by i32 and multiplied with a i32
SL_header i32v4 SL_i32v4subSM(i32v4 lhs, i32v4 rhs, i32 s, i32v4 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v4) {
        .x = lhs.x - rhs.x * s * m.x,
        .y = lhs.y - rhs.y * s * m.y,
        .z = lhs.z - rhs.z * s * m.z,
        .w = lhs.w - rhs.w * s * m.w
    };
}
#else
;
#endif
/// @brief Addition of two i32v with rhs scaled by a i32
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32* SL_i32vSadd_(i32* lhs, i32 s, i32* rhs, i32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * s + rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Addition of two i32v with rhs scaled by a i32
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32v SL_i32vSadd(i32v lhs, i32 s, i32v rhs, i32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i32vSadd_(lhs.data, s, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two i32v2 with rhs scaled by a i32
SL_header i32v2 SL_i32v2Sadd(i32v2 lhs, i32 s, i32v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v2) {
        .x = lhs.x * s + rhs.x,
        .y = lhs.y * s + rhs.y
    };
}
#else
;
#endif
/// @brief Addition of two i32v3 with rhs scaled by a i32
SL_header i32v3 SL_i32v3Sadd(i32v3 lhs, i32 s, i32v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v3) {
        .x = lhs.x * s + rhs.x,
        .y = lhs.y * s + rhs.y,
        .z = lhs.z * s + rhs.z
    };
}
#else
;
#endif
/// @brief Addition of two i32v4 with rhs scaled by a i32
SL_header i32v4 SL_i32v4Sadd(i32v4 lhs, i32 s, i32v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v4) {
        .x = lhs.x * s + rhs.x,
        .y = lhs.y * s + rhs.y,
        .z = lhs.z * s + rhs.z,
        .w = lhs.w * s + rhs.w
    };
}
#else
;
#endif
/// @brief Difference of two i32v with rhs scaled by a i32
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32* SL_i32vSsub_(i32* lhs, i32 s, i32* rhs, i32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * s - rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Difference of two i32v with rhs scaled by a i32
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32v SL_i32vSsub(i32v lhs, i32 s, i32v rhs, i32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i32vSsub_(lhs.data, s, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two i32v2 with rhs scaled by a i32
SL_header i32v2 SL_i32v2Ssub(i32v2 lhs, i32 s, i32v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v2) {
        .x = lhs.x * s - rhs.x,
        .y = lhs.y * s - rhs.y
    };
}
#else
;
#endif
/// @brief Difference of two i32v3 with rhs scaled by a i32
SL_header i32v3 SL_i32v3Ssub(i32v3 lhs, i32 s, i32v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v3) {
        .x = lhs.x * s - rhs.x,
        .y = lhs.y * s - rhs.y,
        .z = lhs.z * s - rhs.z
    };
}
#else
;
#endif
/// @brief Difference of two i32v4 with rhs scaled by a i32
SL_header i32v4 SL_i32v4Ssub(i32v4 lhs, i32 s, i32v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v4) {
        .x = lhs.x * s - rhs.x,
        .y = lhs.y * s - rhs.y,
        .z = lhs.z * s - rhs.z,
        .w = lhs.w * s - rhs.w
    };
}
#else
;
#endif
/// @brief Weighted sum of two i32v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32* SL_i32vmix_(i32* lhs, i32 lhs_w, i32* rhs, i32 rhs_w, i32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * lhs_w + rhs[i] * rhs_w;
    return dest;
}
#else
;
#endif
/// @brief Weighted sum of two i32v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32v SL_i32vmix(i32v lhs, i32 lhs_w, i32v rhs, i32 rhs_w, i32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i32vmix_(lhs.data, lhs_w, rhs.data, rhs_w, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Weighted sum of two i32v2
SL_header i32v2 SL_i32v2mix(i32v2 lhs, i32 lhs_w, i32v2 rhs, i32 rhs_w)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v2) {
        .x = lhs.x * lhs_w + rhs.x * rhs_w,
        .y = lhs.y * lhs_w + rhs.y * rhs_w
    };
}
#else
;
#endif
/// @brief Weighted sum of two i32v3
SL_header i32v3 SL_i32v3mix(i32v3 lhs, i32 lhs_w, i32v3 rhs, i32 rhs_w)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v3) {
        .x = lhs.x * lhs_w + rhs.x * rhs_w,
        .y = lhs.y * lhs_w + rhs.y * rhs_w,
        .z = lhs.z * lhs_w + rhs.z * rhs_w
    };
}
#else
;
#endif
/// @brief Weighted sum of two i32v4
SL_header i32v4 SL_i32v4mix(i32v4 lhs, i32 lhs_w, i32v4 rhs, i32 rhs_w)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v4) {
        .x = lhs.x * lhs_w + rhs.x * rhs_w,
        .y = lhs.y * lhs_w + rhs.y * rhs_w,
        .z = lhs.z * lhs_w + rhs.z * rhs_w,
        .w = lhs.w * lhs_w + rhs.w * rhs_w
    };
}
#else
;
#endif
/// @brief Negation of a i32v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32* SL_i32vneg_(i32* v, i32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = -v[i];
    return dest;
}
#else
;
#endif
/// @brief Negation of a i32v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32v SL_i32vneg(i32v v, i32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i32vneg_(v.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Negation of a i32v2
SL_header i32v2 SL_i32v2neg(i32v2 v)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v2) {
        .x = -v.x,
        .y = -v.y
    };
}
#else
;
#endif
/// @brief Negation of a i32v3
SL_header i32v3 SL_i32v3neg(i32v3 v)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v3) {
        .x = -v.x,
        .y = -v.y,
        .z = -v.z
    };
}
#else
;
#endif
/// @brief Negation of a i32v4
SL_header i32v4 SL_i32v4neg(i32v4 v)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v4) {
        .x = -v.x,
        .y = -v.y,
        .z = -v.z,
        .w = -v.w
    };
}
#else
;
#endif
/// @brief Component-wise absolute value of a i32v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32* SL_i32vabs_(i32* v, i32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = v[i] < 0 ? -v[i] : v[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise absolute value of a i32v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32v SL_i32vabs(i32v v, i32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i32vabs_(v.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise absolute value of a i32v2
SL_header i32v2 SL_i32v2abs(i32v2 v)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v2) {
        .x = v.x < 0 ? -v.x : v.x,
        .y = v.y < 0 ? -v.y : v.y
    };
}
#else
;
#endif
/// @brief Component-wise absolute value of a i32v3
SL_header i32v3 SL_i32v3abs(i32v3 v)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v3) {
        .x = v.x < 0 ? -v.x : v.x,
        .y = v.y < 0 ? -v.y : v.y,
        .z = v.z < 0 ? -v.z : v.z
    };
}
#else
;
#endif
/// @brief Component-wise absolute value of a i32v4
SL_header i32v4 SL_i32v4abs(i32v4 v)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v4) {
        .x = v.x < 0 ? -v.x : v.x,
        .y = v.y < 0 ? -v.y : v.y,
        .z = v.z < 0 ? -v.z : v.z,
        .w = v.w < 0 ? -v.w : v.w
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two i32v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32* SL_i32vmin_(i32* lhs, i32* rhs, i32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] < rhs[i] ? lhs[i] : rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise minimum of two i32v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32v SL_i32vmin(i32v lhs, i32v rhs, i32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i32vmin_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise minimum of two i32v2
SL_header i32v2 SL_i32v2min(i32v2 lhs, i32v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v2) {
        .x = lhs.x < rhs.x ? lhs.x : rhs.x,
        .y = lhs.y < rhs.y ? lhs.y : rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two i32v3
SL_header i32v3 SL_i32v3min(i32v3 lhs, i32v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v3) {
        .x = lhs.x < rhs.x ? lhs.x : rhs.x,
        .y = lhs.y < rhs.y ? lhs.y : rhs.y,
        .z = lhs.z < rhs.z ? lhs.z : rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two i32v4
SL_header i32v4 SL_i32v4min(i32v4 lhs, i32v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v4) {
        .x = lhs.x < rhs.x ? lhs.x : rhs.x,
        .y = lhs.y < rhs.y ? lhs.y : rhs.y,
        .z = lhs.z < rhs.z ? lhs.z : rhs.z,
        .w = lhs.w < rhs.w ? lhs.w : rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two i32v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32* SL_i32vmax_(i32* lhs, i32* rhs, i32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] > rhs[i] ? lhs[i] : rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise maximum of two i32v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32v SL_i32vmax(i32v lhs, i32v rhs, i32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i32vmax_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise maximum of two i32v2
SL_header i32v2 SL_i32v2max(i32v2 lhs, i32v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v2) {
        .x = lhs.x > rhs.x ? lhs.x : rhs.x,
        .y = lhs.y > rhs.y ? lhs.y : rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two i32v3
SL_header i32v3 SL_i32v3max(i32v3 lhs, i32v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v3) {
        .x = lhs.x > rhs.x ? lhs.x : rhs.x,
        .y = lhs.y > rhs.y ? lhs.y : rhs.y,
        .z = lhs.z > rhs.z ? lhs.z : rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two i32v4
SL_header i32v4 SL_i32v4max(i32v4 lhs, i32v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v4) {
        .x = lhs.x > rhs.x ? lhs.x : rhs.x,
        .y = lhs.y > rhs.y ? lhs.y : rhs.y,
        .z = lhs.z > rhs.z ? lhs.z : rhs.z,
        .w = lhs.w > rhs.w ? lhs.w : rhs.w
    };
}
#else
;
#endif
/// @brief Dot product of two i32v
/// @note All vectors are assumed to be of size 'count'
SL_header i64 SL_i32vdot_(i32* lhs, i32* rhs, usize count)
#if defined(SL_IMPLEMENTATION)
{
    i64 dest = 0;
    for (usize i = 0; i < count; ++i) dest += lhs[i] * rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Dot product of two i32v
/// @note All vectors are assumed to be of size 'count'
SL_header i64 SL_i32vdot(i32v lhs, i32v rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i32vdot_(lhs.data, rhs.data, lhs.count);
}
#else
;
#endif
/// @brief Dot product of two i32v2
SL_header i64 SL_i32v2dot(i32v2 lhs, i32v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}
#else
;
#endif
/// @brief Dot product of two i32v3
SL_header i64 SL_i32v3dot(i32v3 lhs, i32v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}
#else
;
#endif
/// @brief Dot product of two i32v4
SL_header i64 SL_i32v4dot(i32v4 lhs, i32v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}
#else
;
#endif
/// @brief Maximum component of a i32v
/// @note All vectors are assumed to be of size 'count'
SL_header i64 SL_i32vlen_max_(i32* v, usize count)
#if defined(SL_IMPLEMENTATION)
{
    i64 dest = 0;
    for (usize i = 0; i < count; ++i) dest = llabs(v[i]) > dest ? llabs(v[i]) : dest;
    return dest;
}
#else
;
#endif
/// @brief Maximum component of a i32v
/// @note All vectors are assumed to be of size 'count'
SL_header i64 SL_i32vlen_max(i32v v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i32vlen_max_(v.data, v.count);
}
#else
;
#endif
/// @brief Maximum component of a i32v2
SL_header i64 SL_i32v2len_max(i32v2 v)
#if defined(SL_IMPLEMENTATION)
{
    v = SL_i32v2abs(v);
    return v.x > v.y ? v.x : v.y;
}
#else
;
#endif
/// @brief Maximum component of a i32v3
SL_header i64 SL_i32v3len_max(i32v3 v)
#if defined(SL_IMPLEMENTATION)
{
    v = SL_i32v3abs(v);
    return v.x > v.y ? (v.x > v.z ? v.x : v.z) : (v.y > v.z ? v.y : v.z);
}
#else
;
#endif
/// @brief Maximum component of a i32v4
SL_header i64 SL_i32v4len_max(i32v4 v)
#if defined(SL_IMPLEMENTATION)
{
    v = SL_i32v4abs(v);
    return v.x > v.y ? (v.x > v.z ? (v.x > v.w ? v.x : v.w) : (v.z > v.w ? v.z : v.w)) : (v.y > v.z ? (v.y > v.w ? v.y : v.w) : (v.z > v.w ? v.z : v.w));
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a i32v
/// @note All vectors are assumed to be of size 'count'
SL_header i64 SL_i32vlen_manh_(i32* v, usize count)
#if defined(SL_IMPLEMENTATION)
{
    i64 dest = 0;
    for (usize i = 0; i < count; ++i) dest += llabs(v[i]);
    return dest;
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a i32v
/// @note All vectors are assumed to be of size 'count'
SL_header i64 SL_i32vlen_manh(i32v v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i32vlen_manh_(v.data, v.count);
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a i32v2
SL_header i64 SL_i32v2len_manh(i32v2 v)
#if defined(SL_IMPLEMENTATION)
{
    v = SL_i32v2abs(v);
    return v.x + v.y;
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a i32v3
SL_header i64 SL_i32v3len_manh(i32v3 v)
#if defined(SL_IMPLEMENTATION)
{
    v = SL_i32v3abs(v);
    return v.x + v.y + v.z;
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a i32v4
SL_header i64 SL_i32v4len_manh(i32v4 v)
#if defined(SL_IMPLEMENTATION)
{
    v = SL_i32v4abs(v);
    return v.x + v.y + v.z + v.w;
}
#else
;
#endif
/// @brief Squared euclidean length of a i32v
/// @note All vectors are assumed to be of size 'count'
SL_header i64 SL_i32vlen_srq_(i32* v, usize count)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i32vdot_(v, v, count);
}
#else
;
#endif
/// @brief Squared euclidean length of a i32v
/// @note All vectors are assumed to be of size 'count'
SL_header i64 SL_i32vlen_srq(i32v v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i32vlen_srq_(v.data, v.count);
}
#else
;
#endif
/// @brief Square length of a i32v2
SL_header i64 SL_i32v2len_sqr(i32v2 v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i32v2dot(v, v);
}
#else
;
#endif
/// @brief Square length of a i32v3
SL_header i64 SL_i32v3len_sqr(i32v3 v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i32v3dot(v, v);
}
#else
;
#endif
/// @brief Square length of a i32v4
SL_header i64 SL_i32v4len_sqr(i32v4 v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i32v4dot(v, v);
}
#else
;
#endif
/// @brief Euclidean length of a i32v
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_i32vlen_(i32* v, usize count)
#if defined(SL_IMPLEMENTATION)
{
    return sqrt(SL_i32vdot_(v, v, count));
}
#else
;
#endif
/// @brief Euclidean length of a i32v
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_i32vlen(i32v v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i32vlen_(v.data, v.count);
}
#else
;
#endif
/// @brief Euclidean length of a i32v2
SL_header double SL_i32v2len(i32v2 v)
#if defined(SL_IMPLEMENTATION)
{
    return sqrt(SL_i32v2dot(v, v));
}
#else
;
#endif
/// @brief Euclidean length of a i32v3
SL_header double SL_i32v3len(i32v3 v)
#if defined(SL_IMPLEMENTATION)
{
    return sqrt(SL_i32v3dot(v, v));
}
#else
;
#endif
/// @brief Euclidean length of a i32v4
SL_header double SL_i32v4len(i32v4 v)
#if defined(SL_IMPLEMENTATION)
{
    return sqrt(SL_i32v4dot(v, v));
}
#else
;
#endif
/// @brief Euclidean distance bewteen two i32v
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_i32vdist_(i32* lhs, i32* rhs, usize count)
#if defined(SL_IMPLEMENTATION)
{
    double accum = 0;
    for (int i = 0; i < count; ++i) accum += (lhs[i] - rhs[i]) * (lhs[i] - rhs[i]);
    return sqrt(accum);
}
#else
;
#endif
/// @brief Euclidean distance bewteen two i32v
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_i32vdist(i32v lhs, i32v rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i32vdist_(lhs.data, rhs.data, lhs.count);
}
#else
;
#endif
/// @brief Euclidean distance between two i32v2
SL_header double SL_i32v2dist(i32v2 lhs, i32v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i32v2len(SL_i32v2sub(lhs, rhs));
}
#else
;
#endif
/// @brief Euclidean distance between two i32v3
SL_header double SL_i32v3dist(i32v3 lhs, i32v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i32v3len(SL_i32v3sub(lhs, rhs));
}
#else
;
#endif
/// @brief Euclidean distance between two i32v4
SL_header double SL_i32v4dist(i32v4 lhs, i32v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i32v4len(SL_i32v4sub(lhs, rhs));
}
#else
;
#endif
/// @brief Reflection of i32v2 v around vector i32v2 n
SL_header i32v2 SL_i32v2refl(i32v2 v, i32v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i32v2subS(v, n, 2.0 * SL_i32v2dot(v, n) / SL_i32v2dot(n, n));
}
#else
;
#endif
/// @brief Reflection of i32v3 v around vector i32v3 n
SL_header i32v3 SL_i32v3refl(i32v3 v, i32v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i32v3subS(v, n, 2.0 * SL_i32v3dot(v, n) / SL_i32v3dot(n, n));
}
#else
;
#endif
/// @brief Reflection of i32v4 v around vector i32v4 n
SL_header i32v4 SL_i32v4refl(i32v4 v, i32v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i32v4subS(v, n, 2.0 * SL_i32v4dot(v, n) / SL_i32v4dot(n, n));
}
#else
;
#endif
/// @brief Reflection of i32v2 v around vector i32v2 n assumed to be of unit length
SL_header i32v2 SL_i32v2refl_u(i32v2 v, i32v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i32v2subS(v, n, 2.0 * SL_i32v2dot(v, n));
}
#else
;
#endif
/// @brief Reflection of i32v3 v around vector i32v3 n assumed to be of unit length
SL_header i32v3 SL_i32v3refl_u(i32v3 v, i32v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i32v3subS(v, n, 2.0 * SL_i32v3dot(v, n));
}
#else
;
#endif
/// @brief Reflection of i32v4 v around vector i32v4 n assumed to be of unit length
SL_header i32v4 SL_i32v4refl_u(i32v4 v, i32v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i32v4subS(v, n, 2.0 * SL_i32v4dot(v, n));
}
#else
;
#endif
/// @brief Get component of i32v2 v in direction i32v2 n
SL_header i32v2 SL_i32v2align(i32v2 v, i32v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i32v2muls(n, SL_i32v2dot(v, n) / SL_i32v2dot(n, n));
}
#else
;
#endif
/// @brief Get component of i32v3 v in direction i32v3 n
SL_header i32v3 SL_i32v3align(i32v3 v, i32v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i32v3muls(n, SL_i32v3dot(v, n) / SL_i32v3dot(n, n));
}
#else
;
#endif
/// @brief Get component of i32v4 v in direction i32v4 n
SL_header i32v4 SL_i32v4align(i32v4 v, i32v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i32v4muls(n, SL_i32v4dot(v, n) / SL_i32v4dot(n, n));
}
#else
;
#endif
/// @brief Get component of i32v2 v in direction i32v2 n assumed to be of unit length
SL_header i32v2 SL_i32v2align_u(i32v2 v, i32v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i32v2muls(n, SL_i32v2dot(v, n));
}
#else
;
#endif
/// @brief Get component of i32v3 v in direction i32v3 n assumed to be of unit length
SL_header i32v3 SL_i32v3align_u(i32v3 v, i32v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i32v3muls(n, SL_i32v3dot(v, n));
}
#else
;
#endif
/// @brief Get component of i32v4 v in direction i32v4 n assumed to be of unit length
SL_header i32v4 SL_i32v4align_u(i32v4 v, i32v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i32v4muls(n, SL_i32v4dot(v, n));
}
#else
;
#endif
/// @brief Project i32v2 v on plane with normal i32v2 n
SL_header i32v2 SL_i32v2proj(i32v2 v, i32v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i32v2sub(v, SL_i32v2align(v, n));
}
#else
;
#endif
/// @brief Project i32v3 v on plane with normal i32v3 n
SL_header i32v3 SL_i32v3proj(i32v3 v, i32v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i32v3sub(v, SL_i32v3align(v, n));
}
#else
;
#endif
/// @brief Project i32v4 v on plane with normal i32v4 n
SL_header i32v4 SL_i32v4proj(i32v4 v, i32v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i32v4sub(v, SL_i32v4align(v, n));
}
#else
;
#endif
/// @brief Project i32v2 v on plane with normal i32v2 n
SL_header i32v2 SL_i32v2proj_u(i32v2 v, i32v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i32v2sub(v, SL_i32v2align_u(v, n));
}
#else
;
#endif
/// @brief Project i32v3 v on plane with normal i32v3 n
SL_header i32v3 SL_i32v3proj_u(i32v3 v, i32v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i32v3sub(v, SL_i32v3align_u(v, n));
}
#else
;
#endif
/// @brief Project i32v4 v on plane with normal i32v4 n
SL_header i32v4 SL_i32v4proj_u(i32v4 v, i32v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i32v4sub(v, SL_i32v4align_u(v, n));
}
#else
;
#endif
/// @brief Component-wise modulo of a i32v by scalar n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32* SL_i32vmods_(i32* v, i32 n, i32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = v[i] % n;
    return dest;
}
#else
;
#endif
/// @brief Component-wise modulo of a i32v by scalar n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32v SL_i32vmods(i32v v, i32 n, i32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i32vmods_(v.data, n, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise modulo of a i32v2 by scalar n
SL_header i32v2 SL_i32v2mods(i32v2 v, i32 n)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v2) {
        .x = v.x % n,
        .y = v.y % n
    };
}
#else
;
#endif
/// @brief Component-wise modulo of a i32v3 by scalar n
SL_header i32v3 SL_i32v3mods(i32v3 v, i32 n)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v3) {
        .x = v.x % n,
        .y = v.y % n,
        .z = v.z % n
    };
}
#else
;
#endif
/// @brief Component-wise modulo of a i32v4 by scalar n
SL_header i32v4 SL_i32v4mods(i32v4 v, i32 n)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v4) {
        .x = v.x % n,
        .y = v.y % n,
        .z = v.z % n,
        .w = v.w % n
    };
}
#else
;
#endif
/// @brief Component-wise modulo of a i32v by i32v n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32* SL_i32vmod_(i32* v, i32* n, i32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = v[i] % n[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise modulo of a i32v by i32v n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32v SL_i32vmod(i32v v, i32v n, i32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i32vmod_(v.data, n.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise modulo of a i32v2 by i32v2 n
SL_header i32v2 SL_i32v2mod(i32v2 v, i32v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v2) {
        .x = v.x % n.x,
        .y = v.y % n.y
    };
}
#else
;
#endif
/// @brief Component-wise modulo of a i32v3 by i32v3 n
SL_header i32v3 SL_i32v3mod(i32v3 v, i32v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v3) {
        .x = v.x % n.x,
        .y = v.y % n.y,
        .z = v.z % n.z
    };
}
#else
;
#endif
/// @brief Component-wise modulo of a i32v4 by i32v4 n
SL_header i32v4 SL_i32v4mod(i32v4 v, i32v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v4) {
        .x = v.x % n.x,
        .y = v.y % n.y,
        .z = v.z % n.z,
        .w = v.w % n.w
    };
}
#else
;
#endif
/// @brief Cross-product of two i32v2
SL_header i64 SL_i32v2cross(i32v2 lhs, i32v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x * rhs.y - lhs.y * rhs.x;
}
#else
;
#endif
/// @brief Cross-product of two i32v3
SL_header i32v3 SL_i32v3cross(i32v3 lhs, i32v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v3) {
        .x = lhs.y * rhs.z - lhs.z * rhs.y,
        .y = lhs.z * rhs.x - lhs.x * rhs.z,
        .z = lhs.x * rhs.y - lhs.y * rhs.x
    };
}
#else
;
#endif
/// @brief Component-wise binary AND of two i32v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32* SL_i32vand_(i32* lhs, i32* rhs, i32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] & rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary AND of two i32v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32v SL_i32vand(i32v lhs, i32v rhs, i32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i32vand_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary AND of two i32v2
SL_header i32v2 SL_i32v2and(i32v2 lhs, i32v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v2) {
        .x = lhs.x & rhs.x,
        .y = lhs.y & rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise binary AND of two i32v3
SL_header i32v3 SL_i32v3and(i32v3 lhs, i32v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v3) {
        .x = lhs.x & rhs.x,
        .y = lhs.y & rhs.y,
        .z = lhs.z & rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise binary AND of two i32v4
SL_header i32v4 SL_i32v4and(i32v4 lhs, i32v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v4) {
        .x = lhs.x & rhs.x,
        .y = lhs.y & rhs.y,
        .z = lhs.z & rhs.z,
        .w = lhs.w & rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise binary OR of two i32v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32* SL_i32vor_(i32* lhs, i32* rhs, i32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] | rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary OR of two i32v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32v SL_i32vor(i32v lhs, i32v rhs, i32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i32vor_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary OR of two i32v2
SL_header i32v2 SL_i32v2or(i32v2 lhs, i32v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v2) {
        .x = lhs.x | rhs.x,
        .y = lhs.y | rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise binary OR of two i32v3
SL_header i32v3 SL_i32v3or(i32v3 lhs, i32v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v3) {
        .x = lhs.x | rhs.x,
        .y = lhs.y | rhs.y,
        .z = lhs.z | rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise binary OR of two i32v4
SL_header i32v4 SL_i32v4or(i32v4 lhs, i32v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v4) {
        .x = lhs.x | rhs.x,
        .y = lhs.y | rhs.y,
        .z = lhs.z | rhs.z,
        .w = lhs.w | rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise binary XOR of two i32v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32* SL_i32vxor_(i32* lhs, i32* rhs, i32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] ^ rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary XOR of two i32v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32v SL_i32vxor(i32v lhs, i32v rhs, i32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i32vxor_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary XOR of two i32v2
SL_header i32v2 SL_i32v2xor(i32v2 lhs, i32v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v2) {
        .x = lhs.x ^ rhs.x,
        .y = lhs.y ^ rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise binary XOR of two i32v3
SL_header i32v3 SL_i32v3xor(i32v3 lhs, i32v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v3) {
        .x = lhs.x ^ rhs.x,
        .y = lhs.y ^ rhs.y,
        .z = lhs.z ^ rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise binary XOR of two i32v4
SL_header i32v4 SL_i32v4xor(i32v4 lhs, i32v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v4) {
        .x = lhs.x ^ rhs.x,
        .y = lhs.y ^ rhs.y,
        .z = lhs.z ^ rhs.z,
        .w = lhs.w ^ rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise binary NOT of a i32v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32* SL_i32vnot_(i32* v, i32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = ~v[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary NOT of a i32v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32v SL_i32vnot(i32v v, i32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i32vnot_(v.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary NOT of a i32v2
SL_header i32v2 SL_i32v2not(i32v2 v)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v2) {
        .x = ~v.x,
        .y = ~v.y
    };
}
#else
;
#endif
/// @brief Component-wise binary NOT of a i32v3
SL_header i32v3 SL_i32v3not(i32v3 v)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v3) {
        .x = ~v.x,
        .y = ~v.y,
        .z = ~v.z
    };
}
#else
;
#endif
/// @brief Component-wise binary NOT of a i32v4
SL_header i32v4 SL_i32v4not(i32v4 v)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v4) {
        .x = ~v.x,
        .y = ~v.y,
        .z = ~v.z,
        .w = ~v.w
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a i32v by integer n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32* SL_i32vlshfts_(i32* lhs, i32 rhs, i32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] << rhs;
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a i32v by integer n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32v SL_i32vlshfts(i32v lhs, i32 rhs, i32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i32vlshfts_(lhs.data, rhs, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a i32v2 by integer n
SL_header i32v2 SL_i32v2lshfts(i32v2 lhs, i32 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v2) {
        .x = lhs.x << rhs,
        .y = lhs.y << rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a i32v3 by integer n
SL_header i32v3 SL_i32v3lshfts(i32v3 lhs, i32 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v3) {
        .x = lhs.x << rhs,
        .y = lhs.y << rhs,
        .z = lhs.z << rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a i32v4 by integer n
SL_header i32v4 SL_i32v4lshfts(i32v4 lhs, i32 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v4) {
        .x = lhs.x << rhs,
        .y = lhs.y << rhs,
        .z = lhs.z << rhs,
        .w = lhs.w << rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a i32v by i32v n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32* SL_i32vlshft_(i32* lhs, i32* rhs, i32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] << rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a i32v by i32v n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32v SL_i32vlshft(i32v lhs, i32v rhs, i32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i32vlshft_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a i32v2 by i32v2 n
SL_header i32v2 SL_i32v2lshft(i32v2 lhs, i32v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v2) {
        .x = lhs.x << rhs.x,
        .y = lhs.y << rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a i32v3 by i32v3 n
SL_header i32v3 SL_i32v3lshft(i32v3 lhs, i32v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v3) {
        .x = lhs.x << rhs.x,
        .y = lhs.y << rhs.y,
        .z = lhs.z << rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a i32v4 by i32v4 n
SL_header i32v4 SL_i32v4lshft(i32v4 lhs, i32v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v4) {
        .x = lhs.x << rhs.x,
        .y = lhs.y << rhs.y,
        .z = lhs.z << rhs.z,
        .w = lhs.w << rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a i32v by interger n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32* SL_i32vrshfts_(i32* lhs, i32 rhs, i32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] >> rhs;
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a i32v by interger n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32v SL_i32vrshfts(i32v lhs, i32 rhs, i32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i32vrshfts_(lhs.data, rhs, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a i32v2 by interger n
SL_header i32v2 SL_i32v2rshfts(i32v2 lhs, i32 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v2) {
        .x = lhs.x >> rhs,
        .y = lhs.y >> rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a i32v3 by interger n
SL_header i32v3 SL_i32v3rshfts(i32v3 lhs, i32 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v3) {
        .x = lhs.x >> rhs,
        .y = lhs.y >> rhs,
        .z = lhs.z >> rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a i32v4 by interger n
SL_header i32v4 SL_i32v4rshfts(i32v4 lhs, i32 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v4) {
        .x = lhs.x >> rhs,
        .y = lhs.y >> rhs,
        .z = lhs.z >> rhs,
        .w = lhs.w >> rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a i32v by i32v n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32* SL_i32vrshft_(i32* lhs, i32* rhs, i32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] >> rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a i32v by i32v n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i32v SL_i32vrshft(i32v lhs, i32v rhs, i32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i32vrshft_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a i32v2 by i32v2 n
SL_header i32v2 SL_i32v2rshft(i32v2 lhs, i32v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v2) {
        .x = lhs.x >> rhs.x,
        .y = lhs.y >> rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a i32v3 by i32v3 n
SL_header i32v3 SL_i32v3rshft(i32v3 lhs, i32v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v3) {
        .x = lhs.x >> rhs.x,
        .y = lhs.y >> rhs.y,
        .z = lhs.z >> rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a i32v4 by i32v4 n
SL_header i32v4 SL_i32v4rshft(i32v4 lhs, i32v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32v4) {
        .x = lhs.x >> rhs.x,
        .y = lhs.y >> rhs.y,
        .z = lhs.z >> rhs.z,
        .w = lhs.w >> rhs.w
    };
}
#else
;
#endif
#pragma endregion I32
#pragma region I64

/// @brief Vector of i64 with arbitrary dimension
typedef struct {
    const usize count;
    i64 *data;
} i64v;

/// @brief Vector of i64 with dimension 2
typedef union {
    i64 data[2];
    struct {
        union { i64 x, r, u; };
        union { i64 y, g, v; };
    };
} i64v2;

#define SL_i64v2_zero  ((i64v2){.x =  0, .y =  0})
#define SL_i64v2_one   ((i64v2){.x =  1, .y =  1})
#define SL_i64v2_right ((i64v2){.x =  1, .y =  0})
#define SL_i64v2_up    ((i64v2){.x =  0, .y =  1})
#define SL_i64v2_left  ((i64v2){.x = -1, .y =  0})
#define SL_i64v2_down  ((i64v2){.x =  0, .y = -1})

/// @brief Vector of i64 with dimension 3
typedef union {
    i64 data[3];
    struct {
        union { i64 x, r, u; };
        union { i64 y, g, v; };
        union { i64 z, b, s; };
    };
    struct {
        union { i64 __x, __r, __u; };
        union { i64v2 yz, gb, vs; };
    };
    struct {
        union { i64v2 xy, rg, uv; };
        union { i64 __z, __b, __s; };
    };
} i64v3;

#define SL_i64v3_zero  ((i64v3){.x =  0, .y =  0, .z =  0})
#define SL_i64v3_one   ((i64v3){.x =  1, .y =  1, .z =  1})
#define SL_i64v3_right ((i64v3){.x =  1, .y =  0, .z =  0})
#define SL_i64v3_up    ((i64v3){.x =  0, .y =  1, .z =  0})
#define SL_i64v3_forw  ((i64v3){.x =  0, .y =  0, .z =  1})
#define SL_i64v3_left  ((i64v3){.x = -1, .y =  0, .z =  0})
#define SL_i64v3_down  ((i64v3){.x =  0, .y = -1, .z =  0})
#define SL_i64v3_back  ((i64v3){.x =  0, .y =  0, .z = -1})

/// @brief Vector of i64 with dimension 4
typedef union {
    i64 data[4];
    struct {
        union { i64 x, r, u; };
        union { i64 y, g, v; };
        union { i64 z, b, s; };
        union { i64 w, a, t; };
    };
    struct {
        union { i64 __x0, __r0, __u0; };
        union { i64v2 yz, gb, vs; };
        union { i64 __w0, __a0, __t0; };
    };
    struct {
        union { i64v2 xy, rb, uv; };
        union { i64v2 zw, ba, st; };
    };
    struct {
        union { i64v3 xyz, rgb, uvs; };
        union { i64 __w1, __a1, __t1; };
    };
    struct {
        union { i64 __x1, __r1, __u1; };
        union { i64v3 yzw, gba, vst; };
    };
} i64v4;

#define SL_i64v4_zero  ((i64v4){.x = 0, .y = 0, .z = 0, .w = 0})
#define SL_i64v4_one   ((i64v4){.x = 1, .y = 1, .z = 1, .w = 1})

#define SL_i64v4_white  ((i64v4){.x = 1, .y = 1, .z = 1, .w = 1})
#define SL_i64v4_black  ((i64v4){.x = 0, .y = 0, .z = 0, .w = 1})
#define SL_i64v4_red    ((i64v4){.x = 1, .y = 0, .z = 0, .w = 1})
#define SL_i64v4_green  ((i64v4){.x = 0, .y = 1, .z = 0, .w = 1})
#define SL_i64v4_blue   ((i64v4){.x = 0, .y = 0, .z = 1, .w = 1})
#define SL_i64v4_yellow ((i64v4){.x = 1, .y = 1, .z = 0, .w = 1})
#define SL_i64v4_cyan   ((i64v4){.x = 0, .y = 1, .z = 1, .w = 1})
#define SL_i64v4_purple ((i64v4){.x = 1, .y = 0, .z = 1, .w = 1})



#define SL_i64v2_(X, Y)       ((i64v2){.x = X, .y = Y})
#define SL_i64v3_(X, Y, Z)    ((i64v3){.x = X, .y = Y, .z = Z})
#define SL_i64v4_(X, Y, Z, W) ((i64v4){.x = X, .y = Y, .z = Z, .w = W})

#define SL_i64v2s(S)          ((i64v2){.x = S, .y = S})
#define SL_i64v3s(S)          ((i64v3){.x = S, .y = S, .z = S})
#define SL_i64v4s(S)          ((i64v4){.x = S, .y = S, .z = S, .w = S})

#define SL_i64vv(V)           ((i64v){.count = vsize(V), .data = (V).data})
#define SL_i64v2v(V, ...)     ((i64v2){.x = (V).x, .y = (V).y})
#define SL_i64v3v(V, ...)     ((i64v3){.x = (V).x, .y = (V).y, .z = (SL_vsize(V) >= 3 ? (V).data[2] : (0, ##__VA_ARGS__))})
#define SL_i64v4v(V, ...)     ((i64v4){.x = (V).x, .y = (V).y, .z = (SL_vsize(V) >= 3 ? (V).data[2] : ((const float[]){0, ##__VA_ARGS__, 0})[1]), .w = (SL_vsize(V) >= 4 ? (V).data[3] : ((const float[]){0, ##__VA_ARGS__, 0, 0})[2])})



/// @brief Equality of two i64v
/// @note All vectors are assumed to be of size 'count'
SL_header bool SL_i64vequ_(i64* lhs, i64* rhs, usize count)
#if defined(SL_IMPLEMENTATION)
{
    bool dest = true;
    for (usize i = 0; i < count; ++i) dest &= lhs[i] == rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Equality of two i64v
/// @note All vectors are assumed to be of size 'count'
SL_header bool SL_i64vequ(i64v lhs, i64v rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i64vequ_(lhs.data, rhs.data, lhs.count);
}
#else
;
#endif
/// @brief Equality of two i64v2
SL_header bool SL_i64v2equ(i64v2 lhs, i64v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}
#else
;
#endif
/// @brief Equality of two i64v3
SL_header bool SL_i64v3equ(i64v3 lhs, i64v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}
#else
;
#endif
/// @brief Equality of two i64v4
SL_header bool SL_i64v4equ(i64v4 lhs, i64v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
}
#else
;
#endif
/// @brief Addition of two i64v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64* SL_i64vadd_(i64* lhs, i64* rhs, i64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] + rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Addition of two i64v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64v SL_i64vadd(i64v lhs, i64v rhs, i64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i64vadd_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two i64v2
SL_header i64v2 SL_i64v2add(i64v2 lhs, i64v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v2) {
        .x = lhs.x + rhs.x,
        .y = lhs.y + rhs.y
    };
}
#else
;
#endif
/// @brief Addition of two i64v3
SL_header i64v3 SL_i64v3add(i64v3 lhs, i64v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v3) {
        .x = lhs.x + rhs.x,
        .y = lhs.y + rhs.y,
        .z = lhs.z + rhs.z
    };
}
#else
;
#endif
/// @brief Addition of two i64v4
SL_header i64v4 SL_i64v4add(i64v4 lhs, i64v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v4) {
        .x = lhs.x + rhs.x,
        .y = lhs.y + rhs.y,
        .z = lhs.z + rhs.z,
        .w = lhs.w + rhs.w
    };
}
#else
;
#endif
/// @brief Difference of two i64v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64* SL_i64vsub_(i64* lhs, i64* rhs, i64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] - rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Difference of two i64v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64v SL_i64vsub(i64v lhs, i64v rhs, i64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i64vsub_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two i64v2
SL_header i64v2 SL_i64v2sub(i64v2 lhs, i64v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v2) {
        .x = lhs.x - rhs.x,
        .y = lhs.y - rhs.y
    };
}
#else
;
#endif
/// @brief Difference of two i64v3
SL_header i64v3 SL_i64v3sub(i64v3 lhs, i64v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v3) {
        .x = lhs.x - rhs.x,
        .y = lhs.y - rhs.y,
        .z = lhs.z - rhs.z
    };
}
#else
;
#endif
/// @brief Difference of two i64v4
SL_header i64v4 SL_i64v4sub(i64v4 lhs, i64v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v4) {
        .x = lhs.x - rhs.x,
        .y = lhs.y - rhs.y,
        .z = lhs.z - rhs.z,
        .w = lhs.w - rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of two i64v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64* SL_i64vmul_(i64* lhs, i64* rhs, i64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise multiplication of two i64v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64v SL_i64vmul(i64v lhs, i64v rhs, i64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i64vmul_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise multiplication of two i64v2
SL_header i64v2 SL_i64v2mul(i64v2 lhs, i64v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v2) {
        .x = lhs.x * rhs.x,
        .y = lhs.y * rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of two i64v3
SL_header i64v3 SL_i64v3mul(i64v3 lhs, i64v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v3) {
        .x = lhs.x * rhs.x,
        .y = lhs.y * rhs.y,
        .z = lhs.z * rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of two i64v4
SL_header i64v4 SL_i64v4mul(i64v4 lhs, i64v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v4) {
        .x = lhs.x * rhs.x,
        .y = lhs.y * rhs.y,
        .z = lhs.z * rhs.z,
        .w = lhs.w * rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of a i64v with a scalar
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64* SL_i64vmuls_(i64* lhs, i64 rhs, i64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * rhs;
    return dest;
}
#else
;
#endif
/// @brief Component-wise multiplication of a i64v with a scalar
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64v SL_i64vmuls(i64v lhs, i64 rhs, i64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i64vmuls_(lhs.data, rhs, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise multiplication of a i64v2 with a scalar
SL_header i64v2 SL_i64v2muls(i64v2 lhs, i64 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v2) {
        .x = lhs.x * rhs,
        .y = lhs.y * rhs
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of a i64v3 with a scalar
SL_header i64v3 SL_i64v3muls(i64v3 lhs, i64 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v3) {
        .x = lhs.x * rhs,
        .y = lhs.y * rhs,
        .z = lhs.z * rhs
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of a i64v4 with a scalar
SL_header i64v4 SL_i64v4muls(i64v4 lhs, i64 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v4) {
        .x = lhs.x * rhs,
        .y = lhs.y * rhs,
        .z = lhs.z * rhs,
        .w = lhs.w * rhs
    };
}
#else
;
#endif
/// @brief Component-wise division of two i64v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64* SL_i64vdiv_(i64* lhs, i64* rhs, i64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] / rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise division of two i64v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64v SL_i64vdiv(i64v lhs, i64v rhs, i64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i64vdiv_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise division of two i64v2
SL_header i64v2 SL_i64v2div(i64v2 lhs, i64v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v2) {
        .x = lhs.x / rhs.x,
        .y = lhs.y / rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise division of two i64v3
SL_header i64v3 SL_i64v3div(i64v3 lhs, i64v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v3) {
        .x = lhs.x / rhs.x,
        .y = lhs.y / rhs.y,
        .z = lhs.z / rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise division of two i64v4
SL_header i64v4 SL_i64v4div(i64v4 lhs, i64v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v4) {
        .x = lhs.x / rhs.x,
        .y = lhs.y / rhs.y,
        .z = lhs.z / rhs.z,
        .w = lhs.w / rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise division of a i64v with a scalar
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64* SL_i64vdivs_(i64* lhs, i64 rhs, i64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] / rhs;
    return dest;
}
#else
;
#endif
/// @brief Component-wise division of a i64v with a scalar
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64v SL_i64vdivs(i64v lhs, i64 rhs, i64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i64vdivs_(lhs.data, rhs, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise division of a i64v2 with a scalar
SL_header i64v2 SL_i64v2divs(i64v2 lhs, i64 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v2) {
        .x = lhs.x / rhs,
        .y = lhs.y / rhs
    };
}
#else
;
#endif
/// @brief Component-wise division of a i64v3 with a scalar
SL_header i64v3 SL_i64v3divs(i64v3 lhs, i64 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v3) {
        .x = lhs.x / rhs,
        .y = lhs.y / rhs,
        .z = lhs.z / rhs
    };
}
#else
;
#endif
/// @brief Component-wise division of a i64v4 with a scalar
SL_header i64v4 SL_i64v4divs(i64v4 lhs, i64 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v4) {
        .x = lhs.x / rhs,
        .y = lhs.y / rhs,
        .z = lhs.z / rhs,
        .w = lhs.w / rhs
    };
}
#else
;
#endif
/// @brief Addition of two i64v with lhs scaled by a i64
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64* SL_i64vaddS_(i64* lhs, i64* rhs, i64 s, i64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] + rhs[i] * s;
    return dest;
}
#else
;
#endif
/// @brief Addition of two i64v with lhs scaled by a i64
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64v SL_i64vaddS(i64v lhs, i64v rhs, i64 s, i64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i64vaddS_(lhs.data, rhs.data, s, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two i64v2 with lhs scaled by a i64
SL_header i64v2 SL_i64v2addS(i64v2 lhs, i64v2 rhs, i64 s)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v2) {
        .x = lhs.x + rhs.x * s,
        .y = lhs.y + rhs.y * s
    };
}
#else
;
#endif
/// @brief Addition of two i64v3 with lhs scaled by a i64
SL_header i64v3 SL_i64v3addS(i64v3 lhs, i64v3 rhs, i64 s)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v3) {
        .x = lhs.x + rhs.x * s,
        .y = lhs.y + rhs.y * s,
        .z = lhs.z + rhs.z * s
    };
}
#else
;
#endif
/// @brief Addition of two i64v4 with lhs scaled by a i64
SL_header i64v4 SL_i64v4addS(i64v4 lhs, i64v4 rhs, i64 s)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v4) {
        .x = lhs.x + rhs.x * s,
        .y = lhs.y + rhs.y * s,
        .z = lhs.z + rhs.z * s,
        .w = lhs.w + rhs.w * s
    };
}
#else
;
#endif
/// @brief Difference of two i64v with lhs scaled by a i64
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64* SL_i64vsubS_(i64* lhs, i64* rhs, i64 s, i64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] - rhs[i] * s;
    return dest;
}
#else
;
#endif
/// @brief Difference of two i64v with lhs scaled by a i64
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64v SL_i64vsubS(i64v lhs, i64v rhs, i64 s, i64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i64vsubS_(lhs.data, rhs.data, s, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two i64v2 with lhs scaled by a i64
SL_header i64v2 SL_i64v2subS(i64v2 lhs, i64v2 rhs, i64 s)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v2) {
        .x = lhs.x - rhs.x * s,
        .y = lhs.y - rhs.y * s
    };
}
#else
;
#endif
/// @brief Difference of two i64v3 with lhs scaled by a i64
SL_header i64v3 SL_i64v3subS(i64v3 lhs, i64v3 rhs, i64 s)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v3) {
        .x = lhs.x - rhs.x * s,
        .y = lhs.y - rhs.y * s,
        .z = lhs.z - rhs.z * s
    };
}
#else
;
#endif
/// @brief Difference of two i64v4 with lhs scaled by a i64
SL_header i64v4 SL_i64v4subS(i64v4 lhs, i64v4 rhs, i64 s)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v4) {
        .x = lhs.x - rhs.x * s,
        .y = lhs.y - rhs.y * s,
        .z = lhs.z - rhs.z * s,
        .w = lhs.w - rhs.w * s
    };
}
#else
;
#endif
/// @brief Addition of two i64v with lhs multiplied with a i64
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64* SL_i64vaddM_(i64* lhs, i64* rhs, i64* m, i64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] + rhs[i] * m[i];
    return dest;
}
#else
;
#endif
/// @brief Addition of two i64v with lhs multiplied with a i64
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64v SL_i64vaddM(i64v lhs, i64v rhs, i64v m, i64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i64vaddM_(lhs.data, rhs.data, m.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two i64v2 with lhs multiplied with a i64
SL_header i64v2 SL_i64v2addM(i64v2 lhs, i64v2 rhs, i64v2 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v2) {
        .x = lhs.x + rhs.x * m.x,
        .y = lhs.y + rhs.y * m.y
    };
}
#else
;
#endif
/// @brief Addition of two i64v3 with lhs multiplied with a i64
SL_header i64v3 SL_i64v3addM(i64v3 lhs, i64v3 rhs, i64v3 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v3) {
        .x = lhs.x + rhs.x * m.x,
        .y = lhs.y + rhs.y * m.y,
        .z = lhs.z + rhs.z * m.z
    };
}
#else
;
#endif
/// @brief Addition of two i64v4 with lhs multiplied with a i64
SL_header i64v4 SL_i64v4addM(i64v4 lhs, i64v4 rhs, i64v4 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v4) {
        .x = lhs.x + rhs.x * m.x,
        .y = lhs.y + rhs.y * m.y,
        .z = lhs.z + rhs.z * m.z,
        .w = lhs.w + rhs.w * m.w
    };
}
#else
;
#endif
/// @brief Difference of two i64v with lhs multiplied with a i64
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64* SL_i64vsubM_(i64* lhs, i64* rhs, i64* m, i64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] - rhs[i] * m[i];
    return dest;
}
#else
;
#endif
/// @brief Difference of two i64v with lhs multiplied with a i64
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64v SL_i64vsubM(i64v lhs, i64v rhs, i64v m, i64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i64vsubM_(lhs.data, rhs.data, m.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two i64v2 with lhs multiplied with a i64
SL_header i64v2 SL_i64v2subM(i64v2 lhs, i64v2 rhs, i64v2 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v2) {
        .x = lhs.x - rhs.x * m.x,
        .y = lhs.y - rhs.y * m.y
    };
}
#else
;
#endif
/// @brief Difference of two i64v3 with lhs multiplied with a i64
SL_header i64v3 SL_i64v3subM(i64v3 lhs, i64v3 rhs, i64v3 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v3) {
        .x = lhs.x - rhs.x * m.x,
        .y = lhs.y - rhs.y * m.y,
        .z = lhs.z - rhs.z * m.z
    };
}
#else
;
#endif
/// @brief Difference of two i64v4 with lhs multiplied with a i64
SL_header i64v4 SL_i64v4subM(i64v4 lhs, i64v4 rhs, i64v4 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v4) {
        .x = lhs.x - rhs.x * m.x,
        .y = lhs.y - rhs.y * m.y,
        .z = lhs.z - rhs.z * m.z,
        .w = lhs.w - rhs.w * m.w
    };
}
#else
;
#endif
/// @brief Addition of two i64v with lhs scaled by i64 and multiplied with a i64
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64* SL_i64vaddSM_(i64* lhs, i64* rhs, i64 s, i64* m, i64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] + rhs[i] * s * m[i];
    return dest;
}
#else
;
#endif
/// @brief Addition of two i64v with lhs scaled by i64 and multiplied with a i64
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64v SL_i64vaddSM(i64v lhs, i64v rhs, i64 s, i64v m, i64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i64vaddSM_(lhs.data, rhs.data, s, m.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two i64v2 with lhs scaled by i64 and multiplied with a i64
SL_header i64v2 SL_i64v2addSM(i64v2 lhs, i64v2 rhs, i64 s, i64v2 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v2) {
        .x = lhs.x + rhs.x * s * m.x,
        .y = lhs.y + rhs.y * s * m.y
    };
}
#else
;
#endif
/// @brief Addition of two i64v3 with lhs scaled by i64 and multiplied with a i64
SL_header i64v3 SL_i64v3addSM(i64v3 lhs, i64v3 rhs, i64 s, i64v3 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v3) {
        .x = lhs.x + rhs.x * s * m.x,
        .y = lhs.y + rhs.y * s * m.y,
        .z = lhs.z + rhs.z * s * m.z
    };
}
#else
;
#endif
/// @brief Addition of two i64v4 with lhs scaled by i64 and multiplied with a i64
SL_header i64v4 SL_i64v4addSM(i64v4 lhs, i64v4 rhs, i64 s, i64v4 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v4) {
        .x = lhs.x + rhs.x * s * m.x,
        .y = lhs.y + rhs.y * s * m.y,
        .z = lhs.z + rhs.z * s * m.z,
        .w = lhs.w + rhs.w * s * m.w
    };
}
#else
;
#endif
/// @brief Difference of two i64v with lhs scaled by i64 and multiplied with a i64
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64* SL_i64vsubSM_(i64* lhs, i64* rhs, i64 s, i64* m, i64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] - rhs[i] * s * m[i];
    return dest;
}
#else
;
#endif
/// @brief Difference of two i64v with lhs scaled by i64 and multiplied with a i64
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64v SL_i64vsubSM(i64v lhs, i64v rhs, i64 s, i64v m, i64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i64vsubSM_(lhs.data, rhs.data, s, m.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two i64v2 with lhs scaled by i64 and multiplied with a i64
SL_header i64v2 SL_i64v2subSM(i64v2 lhs, i64v2 rhs, i64 s, i64v2 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v2) {
        .x = lhs.x - rhs.x * s * m.x,
        .y = lhs.y - rhs.y * s * m.y
    };
}
#else
;
#endif
/// @brief Difference of two i64v3 with lhs scaled by i64 and multiplied with a i64
SL_header i64v3 SL_i64v3subSM(i64v3 lhs, i64v3 rhs, i64 s, i64v3 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v3) {
        .x = lhs.x - rhs.x * s * m.x,
        .y = lhs.y - rhs.y * s * m.y,
        .z = lhs.z - rhs.z * s * m.z
    };
}
#else
;
#endif
/// @brief Difference of two i64v4 with lhs scaled by i64 and multiplied with a i64
SL_header i64v4 SL_i64v4subSM(i64v4 lhs, i64v4 rhs, i64 s, i64v4 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v4) {
        .x = lhs.x - rhs.x * s * m.x,
        .y = lhs.y - rhs.y * s * m.y,
        .z = lhs.z - rhs.z * s * m.z,
        .w = lhs.w - rhs.w * s * m.w
    };
}
#else
;
#endif
/// @brief Addition of two i64v with rhs scaled by a i64
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64* SL_i64vSadd_(i64* lhs, i64 s, i64* rhs, i64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * s + rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Addition of two i64v with rhs scaled by a i64
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64v SL_i64vSadd(i64v lhs, i64 s, i64v rhs, i64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i64vSadd_(lhs.data, s, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two i64v2 with rhs scaled by a i64
SL_header i64v2 SL_i64v2Sadd(i64v2 lhs, i64 s, i64v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v2) {
        .x = lhs.x * s + rhs.x,
        .y = lhs.y * s + rhs.y
    };
}
#else
;
#endif
/// @brief Addition of two i64v3 with rhs scaled by a i64
SL_header i64v3 SL_i64v3Sadd(i64v3 lhs, i64 s, i64v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v3) {
        .x = lhs.x * s + rhs.x,
        .y = lhs.y * s + rhs.y,
        .z = lhs.z * s + rhs.z
    };
}
#else
;
#endif
/// @brief Addition of two i64v4 with rhs scaled by a i64
SL_header i64v4 SL_i64v4Sadd(i64v4 lhs, i64 s, i64v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v4) {
        .x = lhs.x * s + rhs.x,
        .y = lhs.y * s + rhs.y,
        .z = lhs.z * s + rhs.z,
        .w = lhs.w * s + rhs.w
    };
}
#else
;
#endif
/// @brief Difference of two i64v with rhs scaled by a i64
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64* SL_i64vSsub_(i64* lhs, i64 s, i64* rhs, i64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * s - rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Difference of two i64v with rhs scaled by a i64
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64v SL_i64vSsub(i64v lhs, i64 s, i64v rhs, i64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i64vSsub_(lhs.data, s, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two i64v2 with rhs scaled by a i64
SL_header i64v2 SL_i64v2Ssub(i64v2 lhs, i64 s, i64v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v2) {
        .x = lhs.x * s - rhs.x,
        .y = lhs.y * s - rhs.y
    };
}
#else
;
#endif
/// @brief Difference of two i64v3 with rhs scaled by a i64
SL_header i64v3 SL_i64v3Ssub(i64v3 lhs, i64 s, i64v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v3) {
        .x = lhs.x * s - rhs.x,
        .y = lhs.y * s - rhs.y,
        .z = lhs.z * s - rhs.z
    };
}
#else
;
#endif
/// @brief Difference of two i64v4 with rhs scaled by a i64
SL_header i64v4 SL_i64v4Ssub(i64v4 lhs, i64 s, i64v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v4) {
        .x = lhs.x * s - rhs.x,
        .y = lhs.y * s - rhs.y,
        .z = lhs.z * s - rhs.z,
        .w = lhs.w * s - rhs.w
    };
}
#else
;
#endif
/// @brief Weighted sum of two i64v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64* SL_i64vmix_(i64* lhs, i64 lhs_w, i64* rhs, i64 rhs_w, i64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * lhs_w + rhs[i] * rhs_w;
    return dest;
}
#else
;
#endif
/// @brief Weighted sum of two i64v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64v SL_i64vmix(i64v lhs, i64 lhs_w, i64v rhs, i64 rhs_w, i64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i64vmix_(lhs.data, lhs_w, rhs.data, rhs_w, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Weighted sum of two i64v2
SL_header i64v2 SL_i64v2mix(i64v2 lhs, i64 lhs_w, i64v2 rhs, i64 rhs_w)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v2) {
        .x = lhs.x * lhs_w + rhs.x * rhs_w,
        .y = lhs.y * lhs_w + rhs.y * rhs_w
    };
}
#else
;
#endif
/// @brief Weighted sum of two i64v3
SL_header i64v3 SL_i64v3mix(i64v3 lhs, i64 lhs_w, i64v3 rhs, i64 rhs_w)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v3) {
        .x = lhs.x * lhs_w + rhs.x * rhs_w,
        .y = lhs.y * lhs_w + rhs.y * rhs_w,
        .z = lhs.z * lhs_w + rhs.z * rhs_w
    };
}
#else
;
#endif
/// @brief Weighted sum of two i64v4
SL_header i64v4 SL_i64v4mix(i64v4 lhs, i64 lhs_w, i64v4 rhs, i64 rhs_w)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v4) {
        .x = lhs.x * lhs_w + rhs.x * rhs_w,
        .y = lhs.y * lhs_w + rhs.y * rhs_w,
        .z = lhs.z * lhs_w + rhs.z * rhs_w,
        .w = lhs.w * lhs_w + rhs.w * rhs_w
    };
}
#else
;
#endif
/// @brief Negation of a i64v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64* SL_i64vneg_(i64* v, i64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = -v[i];
    return dest;
}
#else
;
#endif
/// @brief Negation of a i64v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64v SL_i64vneg(i64v v, i64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i64vneg_(v.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Negation of a i64v2
SL_header i64v2 SL_i64v2neg(i64v2 v)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v2) {
        .x = -v.x,
        .y = -v.y
    };
}
#else
;
#endif
/// @brief Negation of a i64v3
SL_header i64v3 SL_i64v3neg(i64v3 v)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v3) {
        .x = -v.x,
        .y = -v.y,
        .z = -v.z
    };
}
#else
;
#endif
/// @brief Negation of a i64v4
SL_header i64v4 SL_i64v4neg(i64v4 v)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v4) {
        .x = -v.x,
        .y = -v.y,
        .z = -v.z,
        .w = -v.w
    };
}
#else
;
#endif
/// @brief Component-wise absolute value of a i64v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64* SL_i64vabs_(i64* v, i64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = v[i] < 0 ? -v[i] : v[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise absolute value of a i64v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64v SL_i64vabs(i64v v, i64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i64vabs_(v.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise absolute value of a i64v2
SL_header i64v2 SL_i64v2abs(i64v2 v)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v2) {
        .x = v.x < 0 ? -v.x : v.x,
        .y = v.y < 0 ? -v.y : v.y
    };
}
#else
;
#endif
/// @brief Component-wise absolute value of a i64v3
SL_header i64v3 SL_i64v3abs(i64v3 v)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v3) {
        .x = v.x < 0 ? -v.x : v.x,
        .y = v.y < 0 ? -v.y : v.y,
        .z = v.z < 0 ? -v.z : v.z
    };
}
#else
;
#endif
/// @brief Component-wise absolute value of a i64v4
SL_header i64v4 SL_i64v4abs(i64v4 v)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v4) {
        .x = v.x < 0 ? -v.x : v.x,
        .y = v.y < 0 ? -v.y : v.y,
        .z = v.z < 0 ? -v.z : v.z,
        .w = v.w < 0 ? -v.w : v.w
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two i64v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64* SL_i64vmin_(i64* lhs, i64* rhs, i64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] < rhs[i] ? lhs[i] : rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise minimum of two i64v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64v SL_i64vmin(i64v lhs, i64v rhs, i64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i64vmin_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise minimum of two i64v2
SL_header i64v2 SL_i64v2min(i64v2 lhs, i64v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v2) {
        .x = lhs.x < rhs.x ? lhs.x : rhs.x,
        .y = lhs.y < rhs.y ? lhs.y : rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two i64v3
SL_header i64v3 SL_i64v3min(i64v3 lhs, i64v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v3) {
        .x = lhs.x < rhs.x ? lhs.x : rhs.x,
        .y = lhs.y < rhs.y ? lhs.y : rhs.y,
        .z = lhs.z < rhs.z ? lhs.z : rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two i64v4
SL_header i64v4 SL_i64v4min(i64v4 lhs, i64v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v4) {
        .x = lhs.x < rhs.x ? lhs.x : rhs.x,
        .y = lhs.y < rhs.y ? lhs.y : rhs.y,
        .z = lhs.z < rhs.z ? lhs.z : rhs.z,
        .w = lhs.w < rhs.w ? lhs.w : rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two i64v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64* SL_i64vmax_(i64* lhs, i64* rhs, i64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] > rhs[i] ? lhs[i] : rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise maximum of two i64v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64v SL_i64vmax(i64v lhs, i64v rhs, i64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i64vmax_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise maximum of two i64v2
SL_header i64v2 SL_i64v2max(i64v2 lhs, i64v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v2) {
        .x = lhs.x > rhs.x ? lhs.x : rhs.x,
        .y = lhs.y > rhs.y ? lhs.y : rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two i64v3
SL_header i64v3 SL_i64v3max(i64v3 lhs, i64v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v3) {
        .x = lhs.x > rhs.x ? lhs.x : rhs.x,
        .y = lhs.y > rhs.y ? lhs.y : rhs.y,
        .z = lhs.z > rhs.z ? lhs.z : rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two i64v4
SL_header i64v4 SL_i64v4max(i64v4 lhs, i64v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v4) {
        .x = lhs.x > rhs.x ? lhs.x : rhs.x,
        .y = lhs.y > rhs.y ? lhs.y : rhs.y,
        .z = lhs.z > rhs.z ? lhs.z : rhs.z,
        .w = lhs.w > rhs.w ? lhs.w : rhs.w
    };
}
#else
;
#endif
/// @brief Dot product of two i64v
/// @note All vectors are assumed to be of size 'count'
SL_header i64 SL_i64vdot_(i64* lhs, i64* rhs, usize count)
#if defined(SL_IMPLEMENTATION)
{
    i64 dest = 0;
    for (usize i = 0; i < count; ++i) dest += lhs[i] * rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Dot product of two i64v
/// @note All vectors are assumed to be of size 'count'
SL_header i64 SL_i64vdot(i64v lhs, i64v rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i64vdot_(lhs.data, rhs.data, lhs.count);
}
#else
;
#endif
/// @brief Dot product of two i64v2
SL_header i64 SL_i64v2dot(i64v2 lhs, i64v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}
#else
;
#endif
/// @brief Dot product of two i64v3
SL_header i64 SL_i64v3dot(i64v3 lhs, i64v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}
#else
;
#endif
/// @brief Dot product of two i64v4
SL_header i64 SL_i64v4dot(i64v4 lhs, i64v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}
#else
;
#endif
/// @brief Maximum component of a i64v
/// @note All vectors are assumed to be of size 'count'
SL_header i64 SL_i64vlen_max_(i64* v, usize count)
#if defined(SL_IMPLEMENTATION)
{
    i64 dest = 0;
    for (usize i = 0; i < count; ++i) dest = llabs(v[i]) > dest ? llabs(v[i]) : dest;
    return dest;
}
#else
;
#endif
/// @brief Maximum component of a i64v
/// @note All vectors are assumed to be of size 'count'
SL_header i64 SL_i64vlen_max(i64v v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i64vlen_max_(v.data, v.count);
}
#else
;
#endif
/// @brief Maximum component of a i64v2
SL_header i64 SL_i64v2len_max(i64v2 v)
#if defined(SL_IMPLEMENTATION)
{
    v = SL_i64v2abs(v);
    return v.x > v.y ? v.x : v.y;
}
#else
;
#endif
/// @brief Maximum component of a i64v3
SL_header i64 SL_i64v3len_max(i64v3 v)
#if defined(SL_IMPLEMENTATION)
{
    v = SL_i64v3abs(v);
    return v.x > v.y ? (v.x > v.z ? v.x : v.z) : (v.y > v.z ? v.y : v.z);
}
#else
;
#endif
/// @brief Maximum component of a i64v4
SL_header i64 SL_i64v4len_max(i64v4 v)
#if defined(SL_IMPLEMENTATION)
{
    v = SL_i64v4abs(v);
    return v.x > v.y ? (v.x > v.z ? (v.x > v.w ? v.x : v.w) : (v.z > v.w ? v.z : v.w)) : (v.y > v.z ? (v.y > v.w ? v.y : v.w) : (v.z > v.w ? v.z : v.w));
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a i64v
/// @note All vectors are assumed to be of size 'count'
SL_header i64 SL_i64vlen_manh_(i64* v, usize count)
#if defined(SL_IMPLEMENTATION)
{
    i64 dest = 0;
    for (usize i = 0; i < count; ++i) dest += llabs(v[i]);
    return dest;
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a i64v
/// @note All vectors are assumed to be of size 'count'
SL_header i64 SL_i64vlen_manh(i64v v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i64vlen_manh_(v.data, v.count);
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a i64v2
SL_header i64 SL_i64v2len_manh(i64v2 v)
#if defined(SL_IMPLEMENTATION)
{
    v = SL_i64v2abs(v);
    return v.x + v.y;
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a i64v3
SL_header i64 SL_i64v3len_manh(i64v3 v)
#if defined(SL_IMPLEMENTATION)
{
    v = SL_i64v3abs(v);
    return v.x + v.y + v.z;
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a i64v4
SL_header i64 SL_i64v4len_manh(i64v4 v)
#if defined(SL_IMPLEMENTATION)
{
    v = SL_i64v4abs(v);
    return v.x + v.y + v.z + v.w;
}
#else
;
#endif
/// @brief Squared euclidean length of a i64v
/// @note All vectors are assumed to be of size 'count'
SL_header i64 SL_i64vlen_srq_(i64* v, usize count)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i64vdot_(v, v, count);
}
#else
;
#endif
/// @brief Squared euclidean length of a i64v
/// @note All vectors are assumed to be of size 'count'
SL_header i64 SL_i64vlen_srq(i64v v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i64vlen_srq_(v.data, v.count);
}
#else
;
#endif
/// @brief Square length of a i64v2
SL_header i64 SL_i64v2len_sqr(i64v2 v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i64v2dot(v, v);
}
#else
;
#endif
/// @brief Square length of a i64v3
SL_header i64 SL_i64v3len_sqr(i64v3 v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i64v3dot(v, v);
}
#else
;
#endif
/// @brief Square length of a i64v4
SL_header i64 SL_i64v4len_sqr(i64v4 v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i64v4dot(v, v);
}
#else
;
#endif
/// @brief Euclidean length of a i64v
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_i64vlen_(i64* v, usize count)
#if defined(SL_IMPLEMENTATION)
{
    return sqrt(SL_i64vdot_(v, v, count));
}
#else
;
#endif
/// @brief Euclidean length of a i64v
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_i64vlen(i64v v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i64vlen_(v.data, v.count);
}
#else
;
#endif
/// @brief Euclidean length of a i64v2
SL_header double SL_i64v2len(i64v2 v)
#if defined(SL_IMPLEMENTATION)
{
    return sqrt(SL_i64v2dot(v, v));
}
#else
;
#endif
/// @brief Euclidean length of a i64v3
SL_header double SL_i64v3len(i64v3 v)
#if defined(SL_IMPLEMENTATION)
{
    return sqrt(SL_i64v3dot(v, v));
}
#else
;
#endif
/// @brief Euclidean length of a i64v4
SL_header double SL_i64v4len(i64v4 v)
#if defined(SL_IMPLEMENTATION)
{
    return sqrt(SL_i64v4dot(v, v));
}
#else
;
#endif
/// @brief Euclidean distance bewteen two i64v
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_i64vdist_(i64* lhs, i64* rhs, usize count)
#if defined(SL_IMPLEMENTATION)
{
    double accum = 0;
    for (int i = 0; i < count; ++i) accum += (lhs[i] - rhs[i]) * (lhs[i] - rhs[i]);
    return sqrt(accum);
}
#else
;
#endif
/// @brief Euclidean distance bewteen two i64v
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_i64vdist(i64v lhs, i64v rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i64vdist_(lhs.data, rhs.data, lhs.count);
}
#else
;
#endif
/// @brief Euclidean distance between two i64v2
SL_header double SL_i64v2dist(i64v2 lhs, i64v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i64v2len(SL_i64v2sub(lhs, rhs));
}
#else
;
#endif
/// @brief Euclidean distance between two i64v3
SL_header double SL_i64v3dist(i64v3 lhs, i64v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i64v3len(SL_i64v3sub(lhs, rhs));
}
#else
;
#endif
/// @brief Euclidean distance between two i64v4
SL_header double SL_i64v4dist(i64v4 lhs, i64v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i64v4len(SL_i64v4sub(lhs, rhs));
}
#else
;
#endif
/// @brief Reflection of i64v2 v around vector i64v2 n
SL_header i64v2 SL_i64v2refl(i64v2 v, i64v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i64v2subS(v, n, 2.0 * SL_i64v2dot(v, n) / SL_i64v2dot(n, n));
}
#else
;
#endif
/// @brief Reflection of i64v3 v around vector i64v3 n
SL_header i64v3 SL_i64v3refl(i64v3 v, i64v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i64v3subS(v, n, 2.0 * SL_i64v3dot(v, n) / SL_i64v3dot(n, n));
}
#else
;
#endif
/// @brief Reflection of i64v4 v around vector i64v4 n
SL_header i64v4 SL_i64v4refl(i64v4 v, i64v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i64v4subS(v, n, 2.0 * SL_i64v4dot(v, n) / SL_i64v4dot(n, n));
}
#else
;
#endif
/// @brief Reflection of i64v2 v around vector i64v2 n assumed to be of unit length
SL_header i64v2 SL_i64v2refl_u(i64v2 v, i64v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i64v2subS(v, n, 2.0 * SL_i64v2dot(v, n));
}
#else
;
#endif
/// @brief Reflection of i64v3 v around vector i64v3 n assumed to be of unit length
SL_header i64v3 SL_i64v3refl_u(i64v3 v, i64v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i64v3subS(v, n, 2.0 * SL_i64v3dot(v, n));
}
#else
;
#endif
/// @brief Reflection of i64v4 v around vector i64v4 n assumed to be of unit length
SL_header i64v4 SL_i64v4refl_u(i64v4 v, i64v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i64v4subS(v, n, 2.0 * SL_i64v4dot(v, n));
}
#else
;
#endif
/// @brief Get component of i64v2 v in direction i64v2 n
SL_header i64v2 SL_i64v2align(i64v2 v, i64v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i64v2muls(n, SL_i64v2dot(v, n) / SL_i64v2dot(n, n));
}
#else
;
#endif
/// @brief Get component of i64v3 v in direction i64v3 n
SL_header i64v3 SL_i64v3align(i64v3 v, i64v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i64v3muls(n, SL_i64v3dot(v, n) / SL_i64v3dot(n, n));
}
#else
;
#endif
/// @brief Get component of i64v4 v in direction i64v4 n
SL_header i64v4 SL_i64v4align(i64v4 v, i64v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i64v4muls(n, SL_i64v4dot(v, n) / SL_i64v4dot(n, n));
}
#else
;
#endif
/// @brief Get component of i64v2 v in direction i64v2 n assumed to be of unit length
SL_header i64v2 SL_i64v2align_u(i64v2 v, i64v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i64v2muls(n, SL_i64v2dot(v, n));
}
#else
;
#endif
/// @brief Get component of i64v3 v in direction i64v3 n assumed to be of unit length
SL_header i64v3 SL_i64v3align_u(i64v3 v, i64v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i64v3muls(n, SL_i64v3dot(v, n));
}
#else
;
#endif
/// @brief Get component of i64v4 v in direction i64v4 n assumed to be of unit length
SL_header i64v4 SL_i64v4align_u(i64v4 v, i64v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i64v4muls(n, SL_i64v4dot(v, n));
}
#else
;
#endif
/// @brief Project i64v2 v on plane with normal i64v2 n
SL_header i64v2 SL_i64v2proj(i64v2 v, i64v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i64v2sub(v, SL_i64v2align(v, n));
}
#else
;
#endif
/// @brief Project i64v3 v on plane with normal i64v3 n
SL_header i64v3 SL_i64v3proj(i64v3 v, i64v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i64v3sub(v, SL_i64v3align(v, n));
}
#else
;
#endif
/// @brief Project i64v4 v on plane with normal i64v4 n
SL_header i64v4 SL_i64v4proj(i64v4 v, i64v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i64v4sub(v, SL_i64v4align(v, n));
}
#else
;
#endif
/// @brief Project i64v2 v on plane with normal i64v2 n
SL_header i64v2 SL_i64v2proj_u(i64v2 v, i64v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i64v2sub(v, SL_i64v2align_u(v, n));
}
#else
;
#endif
/// @brief Project i64v3 v on plane with normal i64v3 n
SL_header i64v3 SL_i64v3proj_u(i64v3 v, i64v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i64v3sub(v, SL_i64v3align_u(v, n));
}
#else
;
#endif
/// @brief Project i64v4 v on plane with normal i64v4 n
SL_header i64v4 SL_i64v4proj_u(i64v4 v, i64v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i64v4sub(v, SL_i64v4align_u(v, n));
}
#else
;
#endif
/// @brief Component-wise modulo of a i64v by scalar n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64* SL_i64vmods_(i64* v, i64 n, i64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = v[i] % n;
    return dest;
}
#else
;
#endif
/// @brief Component-wise modulo of a i64v by scalar n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64v SL_i64vmods(i64v v, i64 n, i64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i64vmods_(v.data, n, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise modulo of a i64v2 by scalar n
SL_header i64v2 SL_i64v2mods(i64v2 v, i64 n)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v2) {
        .x = v.x % n,
        .y = v.y % n
    };
}
#else
;
#endif
/// @brief Component-wise modulo of a i64v3 by scalar n
SL_header i64v3 SL_i64v3mods(i64v3 v, i64 n)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v3) {
        .x = v.x % n,
        .y = v.y % n,
        .z = v.z % n
    };
}
#else
;
#endif
/// @brief Component-wise modulo of a i64v4 by scalar n
SL_header i64v4 SL_i64v4mods(i64v4 v, i64 n)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v4) {
        .x = v.x % n,
        .y = v.y % n,
        .z = v.z % n,
        .w = v.w % n
    };
}
#else
;
#endif
/// @brief Component-wise modulo of a i64v by i64v n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64* SL_i64vmod_(i64* v, i64* n, i64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = v[i] % n[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise modulo of a i64v by i64v n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64v SL_i64vmod(i64v v, i64v n, i64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i64vmod_(v.data, n.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise modulo of a i64v2 by i64v2 n
SL_header i64v2 SL_i64v2mod(i64v2 v, i64v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v2) {
        .x = v.x % n.x,
        .y = v.y % n.y
    };
}
#else
;
#endif
/// @brief Component-wise modulo of a i64v3 by i64v3 n
SL_header i64v3 SL_i64v3mod(i64v3 v, i64v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v3) {
        .x = v.x % n.x,
        .y = v.y % n.y,
        .z = v.z % n.z
    };
}
#else
;
#endif
/// @brief Component-wise modulo of a i64v4 by i64v4 n
SL_header i64v4 SL_i64v4mod(i64v4 v, i64v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v4) {
        .x = v.x % n.x,
        .y = v.y % n.y,
        .z = v.z % n.z,
        .w = v.w % n.w
    };
}
#else
;
#endif
/// @brief Cross-product of two i64v2
SL_header i64 SL_i64v2cross(i64v2 lhs, i64v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x * rhs.y - lhs.y * rhs.x;
}
#else
;
#endif
/// @brief Cross-product of two i64v3
SL_header i64v3 SL_i64v3cross(i64v3 lhs, i64v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v3) {
        .x = lhs.y * rhs.z - lhs.z * rhs.y,
        .y = lhs.z * rhs.x - lhs.x * rhs.z,
        .z = lhs.x * rhs.y - lhs.y * rhs.x
    };
}
#else
;
#endif
/// @brief Component-wise binary AND of two i64v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64* SL_i64vand_(i64* lhs, i64* rhs, i64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] & rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary AND of two i64v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64v SL_i64vand(i64v lhs, i64v rhs, i64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i64vand_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary AND of two i64v2
SL_header i64v2 SL_i64v2and(i64v2 lhs, i64v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v2) {
        .x = lhs.x & rhs.x,
        .y = lhs.y & rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise binary AND of two i64v3
SL_header i64v3 SL_i64v3and(i64v3 lhs, i64v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v3) {
        .x = lhs.x & rhs.x,
        .y = lhs.y & rhs.y,
        .z = lhs.z & rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise binary AND of two i64v4
SL_header i64v4 SL_i64v4and(i64v4 lhs, i64v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v4) {
        .x = lhs.x & rhs.x,
        .y = lhs.y & rhs.y,
        .z = lhs.z & rhs.z,
        .w = lhs.w & rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise binary OR of two i64v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64* SL_i64vor_(i64* lhs, i64* rhs, i64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] | rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary OR of two i64v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64v SL_i64vor(i64v lhs, i64v rhs, i64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i64vor_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary OR of two i64v2
SL_header i64v2 SL_i64v2or(i64v2 lhs, i64v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v2) {
        .x = lhs.x | rhs.x,
        .y = lhs.y | rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise binary OR of two i64v3
SL_header i64v3 SL_i64v3or(i64v3 lhs, i64v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v3) {
        .x = lhs.x | rhs.x,
        .y = lhs.y | rhs.y,
        .z = lhs.z | rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise binary OR of two i64v4
SL_header i64v4 SL_i64v4or(i64v4 lhs, i64v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v4) {
        .x = lhs.x | rhs.x,
        .y = lhs.y | rhs.y,
        .z = lhs.z | rhs.z,
        .w = lhs.w | rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise binary XOR of two i64v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64* SL_i64vxor_(i64* lhs, i64* rhs, i64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] ^ rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary XOR of two i64v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64v SL_i64vxor(i64v lhs, i64v rhs, i64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i64vxor_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary XOR of two i64v2
SL_header i64v2 SL_i64v2xor(i64v2 lhs, i64v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v2) {
        .x = lhs.x ^ rhs.x,
        .y = lhs.y ^ rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise binary XOR of two i64v3
SL_header i64v3 SL_i64v3xor(i64v3 lhs, i64v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v3) {
        .x = lhs.x ^ rhs.x,
        .y = lhs.y ^ rhs.y,
        .z = lhs.z ^ rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise binary XOR of two i64v4
SL_header i64v4 SL_i64v4xor(i64v4 lhs, i64v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v4) {
        .x = lhs.x ^ rhs.x,
        .y = lhs.y ^ rhs.y,
        .z = lhs.z ^ rhs.z,
        .w = lhs.w ^ rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise binary NOT of a i64v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64* SL_i64vnot_(i64* v, i64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = ~v[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary NOT of a i64v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64v SL_i64vnot(i64v v, i64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i64vnot_(v.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary NOT of a i64v2
SL_header i64v2 SL_i64v2not(i64v2 v)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v2) {
        .x = ~v.x,
        .y = ~v.y
    };
}
#else
;
#endif
/// @brief Component-wise binary NOT of a i64v3
SL_header i64v3 SL_i64v3not(i64v3 v)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v3) {
        .x = ~v.x,
        .y = ~v.y,
        .z = ~v.z
    };
}
#else
;
#endif
/// @brief Component-wise binary NOT of a i64v4
SL_header i64v4 SL_i64v4not(i64v4 v)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v4) {
        .x = ~v.x,
        .y = ~v.y,
        .z = ~v.z,
        .w = ~v.w
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a i64v by integer n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64* SL_i64vlshfts_(i64* lhs, i64 rhs, i64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] << rhs;
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a i64v by integer n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64v SL_i64vlshfts(i64v lhs, i64 rhs, i64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i64vlshfts_(lhs.data, rhs, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a i64v2 by integer n
SL_header i64v2 SL_i64v2lshfts(i64v2 lhs, i64 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v2) {
        .x = lhs.x << rhs,
        .y = lhs.y << rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a i64v3 by integer n
SL_header i64v3 SL_i64v3lshfts(i64v3 lhs, i64 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v3) {
        .x = lhs.x << rhs,
        .y = lhs.y << rhs,
        .z = lhs.z << rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a i64v4 by integer n
SL_header i64v4 SL_i64v4lshfts(i64v4 lhs, i64 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v4) {
        .x = lhs.x << rhs,
        .y = lhs.y << rhs,
        .z = lhs.z << rhs,
        .w = lhs.w << rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a i64v by i64v n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64* SL_i64vlshft_(i64* lhs, i64* rhs, i64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] << rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a i64v by i64v n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64v SL_i64vlshft(i64v lhs, i64v rhs, i64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i64vlshft_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a i64v2 by i64v2 n
SL_header i64v2 SL_i64v2lshft(i64v2 lhs, i64v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v2) {
        .x = lhs.x << rhs.x,
        .y = lhs.y << rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a i64v3 by i64v3 n
SL_header i64v3 SL_i64v3lshft(i64v3 lhs, i64v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v3) {
        .x = lhs.x << rhs.x,
        .y = lhs.y << rhs.y,
        .z = lhs.z << rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a i64v4 by i64v4 n
SL_header i64v4 SL_i64v4lshft(i64v4 lhs, i64v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v4) {
        .x = lhs.x << rhs.x,
        .y = lhs.y << rhs.y,
        .z = lhs.z << rhs.z,
        .w = lhs.w << rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a i64v by interger n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64* SL_i64vrshfts_(i64* lhs, i64 rhs, i64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] >> rhs;
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a i64v by interger n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64v SL_i64vrshfts(i64v lhs, i64 rhs, i64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i64vrshfts_(lhs.data, rhs, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a i64v2 by interger n
SL_header i64v2 SL_i64v2rshfts(i64v2 lhs, i64 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v2) {
        .x = lhs.x >> rhs,
        .y = lhs.y >> rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a i64v3 by interger n
SL_header i64v3 SL_i64v3rshfts(i64v3 lhs, i64 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v3) {
        .x = lhs.x >> rhs,
        .y = lhs.y >> rhs,
        .z = lhs.z >> rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a i64v4 by interger n
SL_header i64v4 SL_i64v4rshfts(i64v4 lhs, i64 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v4) {
        .x = lhs.x >> rhs,
        .y = lhs.y >> rhs,
        .z = lhs.z >> rhs,
        .w = lhs.w >> rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a i64v by i64v n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64* SL_i64vrshft_(i64* lhs, i64* rhs, i64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] >> rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a i64v by i64v n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header i64v SL_i64vrshft(i64v lhs, i64v rhs, i64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_i64vrshft_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a i64v2 by i64v2 n
SL_header i64v2 SL_i64v2rshft(i64v2 lhs, i64v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v2) {
        .x = lhs.x >> rhs.x,
        .y = lhs.y >> rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a i64v3 by i64v3 n
SL_header i64v3 SL_i64v3rshft(i64v3 lhs, i64v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v3) {
        .x = lhs.x >> rhs.x,
        .y = lhs.y >> rhs.y,
        .z = lhs.z >> rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a i64v4 by i64v4 n
SL_header i64v4 SL_i64v4rshft(i64v4 lhs, i64v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64v4) {
        .x = lhs.x >> rhs.x,
        .y = lhs.y >> rhs.y,
        .z = lhs.z >> rhs.z,
        .w = lhs.w >> rhs.w
    };
}
#else
;
#endif
#pragma endregion I64
#pragma region U8

/// @brief Vector of u8 with arbitrary dimension
typedef struct {
    const usize count;
    u8 *data;
} u8v;

/// @brief Vector of u8 with dimension 2
typedef union {
    u8 data[2];
    struct {
        union { u8 x, r, u; };
        union { u8 y, g, v; };
    };
} u8v2;

#define SL_u8v2_zero  ((u8v2){.x =  0, .y =  0})
#define SL_u8v2_one   ((u8v2){.x =  1, .y =  1})
#define SL_u8v2_right ((u8v2){.x =  1, .y =  0})
#define SL_u8v2_up    ((u8v2){.x =  0, .y =  1})

/// @brief Vector of u8 with dimension 3
typedef union {
    u8 data[3];
    struct {
        union { u8 x, r, u; };
        union { u8 y, g, v; };
        union { u8 z, b, s; };
    };
    struct {
        union { u8 __x, __r, __u; };
        union { u8v2 yz, gb, vs; };
    };
    struct {
        union { u8v2 xy, rg, uv; };
        union { u8 __z, __b, __s; };
    };
} u8v3;

#define SL_u8v3_zero  ((u8v3){.x =  0, .y =  0, .z =  0})
#define SL_u8v3_one   ((u8v3){.x =  1, .y =  1, .z =  1})
#define SL_u8v3_right ((u8v3){.x =  1, .y =  0, .z =  0})
#define SL_u8v3_up    ((u8v3){.x =  0, .y =  1, .z =  0})
#define SL_u8v3_forw  ((u8v3){.x =  0, .y =  0, .z =  1})

/// @brief Vector of u8 with dimension 4
typedef union {
    u8 data[4];
    struct {
        union { u8 x, r, u; };
        union { u8 y, g, v; };
        union { u8 z, b, s; };
        union { u8 w, a, t; };
    };
    struct {
        union { u8 __x0, __r0, __u0; };
        union { u8v2 yz, gb, vs; };
        union { u8 __w0, __a0, __t0; };
    };
    struct {
        union { u8v2 xy, rb, uv; };
        union { u8v2 zw, ba, st; };
    };
    struct {
        union { u8v3 xyz, rgb, uvs; };
        union { u8 __w1, __a1, __t1; };
    };
    struct {
        union { u8 __x1, __r1, __u1; };
        union { u8v3 yzw, gba, vst; };
    };
} u8v4;

#define SL_u8v4_zero  ((u8v4){.x = 0, .y = 0, .z = 0, .w = 0})
#define SL_u8v4_one   ((u8v4){.x = 1, .y = 1, .z = 1, .w = 1})

#define SL_u8v4_white  ((u8v4){.x = 1, .y = 1, .z = 1, .w = 1})
#define SL_u8v4_black  ((u8v4){.x = 0, .y = 0, .z = 0, .w = 1})
#define SL_u8v4_red    ((u8v4){.x = 1, .y = 0, .z = 0, .w = 1})
#define SL_u8v4_green  ((u8v4){.x = 0, .y = 1, .z = 0, .w = 1})
#define SL_u8v4_blue   ((u8v4){.x = 0, .y = 0, .z = 1, .w = 1})
#define SL_u8v4_yellow ((u8v4){.x = 1, .y = 1, .z = 0, .w = 1})
#define SL_u8v4_cyan   ((u8v4){.x = 0, .y = 1, .z = 1, .w = 1})
#define SL_u8v4_purple ((u8v4){.x = 1, .y = 0, .z = 1, .w = 1})



#define SL_u8v2_(X, Y)       ((u8v2){.x = X, .y = Y})
#define SL_u8v3_(X, Y, Z)    ((u8v3){.x = X, .y = Y, .z = Z})
#define SL_u8v4_(X, Y, Z, W) ((u8v4){.x = X, .y = Y, .z = Z, .w = W})

#define SL_u8v2s(S)          ((u8v2){.x = S, .y = S})
#define SL_u8v3s(S)          ((u8v3){.x = S, .y = S, .z = S})
#define SL_u8v4s(S)          ((u8v4){.x = S, .y = S, .z = S, .w = S})

#define SL_u8vv(V)           ((u8v){.count = vsize(V), .data = (V).data})
#define SL_u8v2v(V, ...)     ((u8v2){.x = (V).x, .y = (V).y})
#define SL_u8v3v(V, ...)     ((u8v3){.x = (V).x, .y = (V).y, .z = (SL_vsize(V) >= 3 ? (V).data[2] : (0, ##__VA_ARGS__))})
#define SL_u8v4v(V, ...)     ((u8v4){.x = (V).x, .y = (V).y, .z = (SL_vsize(V) >= 3 ? (V).data[2] : ((const float[]){0, ##__VA_ARGS__, 0})[1]), .w = (SL_vsize(V) >= 4 ? (V).data[3] : ((const float[]){0, ##__VA_ARGS__, 0, 0})[2])})



/// @brief Equality of two u8v
/// @note All vectors are assumed to be of size 'count'
SL_header bool SL_u8vequ_(u8* lhs, u8* rhs, usize count)
#if defined(SL_IMPLEMENTATION)
{
    bool dest = true;
    for (usize i = 0; i < count; ++i) dest &= lhs[i] == rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Equality of two u8v
/// @note All vectors are assumed to be of size 'count'
SL_header bool SL_u8vequ(u8v lhs, u8v rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u8vequ_(lhs.data, rhs.data, lhs.count);
}
#else
;
#endif
/// @brief Equality of two u8v2
SL_header bool SL_u8v2equ(u8v2 lhs, u8v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}
#else
;
#endif
/// @brief Equality of two u8v3
SL_header bool SL_u8v3equ(u8v3 lhs, u8v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}
#else
;
#endif
/// @brief Equality of two u8v4
SL_header bool SL_u8v4equ(u8v4 lhs, u8v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
}
#else
;
#endif
/// @brief Addition of two u8v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8* SL_u8vadd_(u8* lhs, u8* rhs, u8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] + rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Addition of two u8v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8v SL_u8vadd(u8v lhs, u8v rhs, u8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u8vadd_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two u8v2
SL_header u8v2 SL_u8v2add(u8v2 lhs, u8v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v2) {
        .x = lhs.x + rhs.x,
        .y = lhs.y + rhs.y
    };
}
#else
;
#endif
/// @brief Addition of two u8v3
SL_header u8v3 SL_u8v3add(u8v3 lhs, u8v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v3) {
        .x = lhs.x + rhs.x,
        .y = lhs.y + rhs.y,
        .z = lhs.z + rhs.z
    };
}
#else
;
#endif
/// @brief Addition of two u8v4
SL_header u8v4 SL_u8v4add(u8v4 lhs, u8v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v4) {
        .x = lhs.x + rhs.x,
        .y = lhs.y + rhs.y,
        .z = lhs.z + rhs.z,
        .w = lhs.w + rhs.w
    };
}
#else
;
#endif
/// @brief Difference of two u8v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8* SL_u8vsub_(u8* lhs, u8* rhs, u8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] - rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Difference of two u8v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8v SL_u8vsub(u8v lhs, u8v rhs, u8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u8vsub_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two u8v2
SL_header u8v2 SL_u8v2sub(u8v2 lhs, u8v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v2) {
        .x = lhs.x - rhs.x,
        .y = lhs.y - rhs.y
    };
}
#else
;
#endif
/// @brief Difference of two u8v3
SL_header u8v3 SL_u8v3sub(u8v3 lhs, u8v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v3) {
        .x = lhs.x - rhs.x,
        .y = lhs.y - rhs.y,
        .z = lhs.z - rhs.z
    };
}
#else
;
#endif
/// @brief Difference of two u8v4
SL_header u8v4 SL_u8v4sub(u8v4 lhs, u8v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v4) {
        .x = lhs.x - rhs.x,
        .y = lhs.y - rhs.y,
        .z = lhs.z - rhs.z,
        .w = lhs.w - rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of two u8v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8* SL_u8vmul_(u8* lhs, u8* rhs, u8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise multiplication of two u8v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8v SL_u8vmul(u8v lhs, u8v rhs, u8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u8vmul_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise multiplication of two u8v2
SL_header u8v2 SL_u8v2mul(u8v2 lhs, u8v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v2) {
        .x = lhs.x * rhs.x,
        .y = lhs.y * rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of two u8v3
SL_header u8v3 SL_u8v3mul(u8v3 lhs, u8v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v3) {
        .x = lhs.x * rhs.x,
        .y = lhs.y * rhs.y,
        .z = lhs.z * rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of two u8v4
SL_header u8v4 SL_u8v4mul(u8v4 lhs, u8v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v4) {
        .x = lhs.x * rhs.x,
        .y = lhs.y * rhs.y,
        .z = lhs.z * rhs.z,
        .w = lhs.w * rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of a u8v with a scalar
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8* SL_u8vmuls_(u8* lhs, u8 rhs, u8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * rhs;
    return dest;
}
#else
;
#endif
/// @brief Component-wise multiplication of a u8v with a scalar
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8v SL_u8vmuls(u8v lhs, u8 rhs, u8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u8vmuls_(lhs.data, rhs, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise multiplication of a u8v2 with a scalar
SL_header u8v2 SL_u8v2muls(u8v2 lhs, u8 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v2) {
        .x = lhs.x * rhs,
        .y = lhs.y * rhs
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of a u8v3 with a scalar
SL_header u8v3 SL_u8v3muls(u8v3 lhs, u8 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v3) {
        .x = lhs.x * rhs,
        .y = lhs.y * rhs,
        .z = lhs.z * rhs
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of a u8v4 with a scalar
SL_header u8v4 SL_u8v4muls(u8v4 lhs, u8 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v4) {
        .x = lhs.x * rhs,
        .y = lhs.y * rhs,
        .z = lhs.z * rhs,
        .w = lhs.w * rhs
    };
}
#else
;
#endif
/// @brief Component-wise division of two u8v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8* SL_u8vdiv_(u8* lhs, u8* rhs, u8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] / rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise division of two u8v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8v SL_u8vdiv(u8v lhs, u8v rhs, u8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u8vdiv_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise division of two u8v2
SL_header u8v2 SL_u8v2div(u8v2 lhs, u8v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v2) {
        .x = lhs.x / rhs.x,
        .y = lhs.y / rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise division of two u8v3
SL_header u8v3 SL_u8v3div(u8v3 lhs, u8v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v3) {
        .x = lhs.x / rhs.x,
        .y = lhs.y / rhs.y,
        .z = lhs.z / rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise division of two u8v4
SL_header u8v4 SL_u8v4div(u8v4 lhs, u8v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v4) {
        .x = lhs.x / rhs.x,
        .y = lhs.y / rhs.y,
        .z = lhs.z / rhs.z,
        .w = lhs.w / rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise division of a u8v with a scalar
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8* SL_u8vdivs_(u8* lhs, u8 rhs, u8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] / rhs;
    return dest;
}
#else
;
#endif
/// @brief Component-wise division of a u8v with a scalar
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8v SL_u8vdivs(u8v lhs, u8 rhs, u8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u8vdivs_(lhs.data, rhs, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise division of a u8v2 with a scalar
SL_header u8v2 SL_u8v2divs(u8v2 lhs, u8 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v2) {
        .x = lhs.x / rhs,
        .y = lhs.y / rhs
    };
}
#else
;
#endif
/// @brief Component-wise division of a u8v3 with a scalar
SL_header u8v3 SL_u8v3divs(u8v3 lhs, u8 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v3) {
        .x = lhs.x / rhs,
        .y = lhs.y / rhs,
        .z = lhs.z / rhs
    };
}
#else
;
#endif
/// @brief Component-wise division of a u8v4 with a scalar
SL_header u8v4 SL_u8v4divs(u8v4 lhs, u8 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v4) {
        .x = lhs.x / rhs,
        .y = lhs.y / rhs,
        .z = lhs.z / rhs,
        .w = lhs.w / rhs
    };
}
#else
;
#endif
/// @brief Addition of two u8v with lhs scaled by a u8
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8* SL_u8vaddS_(u8* lhs, u8* rhs, u8 s, u8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] + rhs[i] * s;
    return dest;
}
#else
;
#endif
/// @brief Addition of two u8v with lhs scaled by a u8
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8v SL_u8vaddS(u8v lhs, u8v rhs, u8 s, u8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u8vaddS_(lhs.data, rhs.data, s, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two u8v2 with lhs scaled by a u8
SL_header u8v2 SL_u8v2addS(u8v2 lhs, u8v2 rhs, u8 s)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v2) {
        .x = lhs.x + rhs.x * s,
        .y = lhs.y + rhs.y * s
    };
}
#else
;
#endif
/// @brief Addition of two u8v3 with lhs scaled by a u8
SL_header u8v3 SL_u8v3addS(u8v3 lhs, u8v3 rhs, u8 s)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v3) {
        .x = lhs.x + rhs.x * s,
        .y = lhs.y + rhs.y * s,
        .z = lhs.z + rhs.z * s
    };
}
#else
;
#endif
/// @brief Addition of two u8v4 with lhs scaled by a u8
SL_header u8v4 SL_u8v4addS(u8v4 lhs, u8v4 rhs, u8 s)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v4) {
        .x = lhs.x + rhs.x * s,
        .y = lhs.y + rhs.y * s,
        .z = lhs.z + rhs.z * s,
        .w = lhs.w + rhs.w * s
    };
}
#else
;
#endif
/// @brief Difference of two u8v with lhs scaled by a u8
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8* SL_u8vsubS_(u8* lhs, u8* rhs, u8 s, u8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] - rhs[i] * s;
    return dest;
}
#else
;
#endif
/// @brief Difference of two u8v with lhs scaled by a u8
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8v SL_u8vsubS(u8v lhs, u8v rhs, u8 s, u8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u8vsubS_(lhs.data, rhs.data, s, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two u8v2 with lhs scaled by a u8
SL_header u8v2 SL_u8v2subS(u8v2 lhs, u8v2 rhs, u8 s)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v2) {
        .x = lhs.x - rhs.x * s,
        .y = lhs.y - rhs.y * s
    };
}
#else
;
#endif
/// @brief Difference of two u8v3 with lhs scaled by a u8
SL_header u8v3 SL_u8v3subS(u8v3 lhs, u8v3 rhs, u8 s)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v3) {
        .x = lhs.x - rhs.x * s,
        .y = lhs.y - rhs.y * s,
        .z = lhs.z - rhs.z * s
    };
}
#else
;
#endif
/// @brief Difference of two u8v4 with lhs scaled by a u8
SL_header u8v4 SL_u8v4subS(u8v4 lhs, u8v4 rhs, u8 s)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v4) {
        .x = lhs.x - rhs.x * s,
        .y = lhs.y - rhs.y * s,
        .z = lhs.z - rhs.z * s,
        .w = lhs.w - rhs.w * s
    };
}
#else
;
#endif
/// @brief Addition of two u8v with lhs multiplied with a u8
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8* SL_u8vaddM_(u8* lhs, u8* rhs, u8* m, u8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] + rhs[i] * m[i];
    return dest;
}
#else
;
#endif
/// @brief Addition of two u8v with lhs multiplied with a u8
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8v SL_u8vaddM(u8v lhs, u8v rhs, u8v m, u8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u8vaddM_(lhs.data, rhs.data, m.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two u8v2 with lhs multiplied with a u8
SL_header u8v2 SL_u8v2addM(u8v2 lhs, u8v2 rhs, u8v2 m)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v2) {
        .x = lhs.x + rhs.x * m.x,
        .y = lhs.y + rhs.y * m.y
    };
}
#else
;
#endif
/// @brief Addition of two u8v3 with lhs multiplied with a u8
SL_header u8v3 SL_u8v3addM(u8v3 lhs, u8v3 rhs, u8v3 m)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v3) {
        .x = lhs.x + rhs.x * m.x,
        .y = lhs.y + rhs.y * m.y,
        .z = lhs.z + rhs.z * m.z
    };
}
#else
;
#endif
/// @brief Addition of two u8v4 with lhs multiplied with a u8
SL_header u8v4 SL_u8v4addM(u8v4 lhs, u8v4 rhs, u8v4 m)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v4) {
        .x = lhs.x + rhs.x * m.x,
        .y = lhs.y + rhs.y * m.y,
        .z = lhs.z + rhs.z * m.z,
        .w = lhs.w + rhs.w * m.w
    };
}
#else
;
#endif
/// @brief Difference of two u8v with lhs multiplied with a u8
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8* SL_u8vsubM_(u8* lhs, u8* rhs, u8* m, u8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] - rhs[i] * m[i];
    return dest;
}
#else
;
#endif
/// @brief Difference of two u8v with lhs multiplied with a u8
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8v SL_u8vsubM(u8v lhs, u8v rhs, u8v m, u8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u8vsubM_(lhs.data, rhs.data, m.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two u8v2 with lhs multiplied with a u8
SL_header u8v2 SL_u8v2subM(u8v2 lhs, u8v2 rhs, u8v2 m)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v2) {
        .x = lhs.x - rhs.x * m.x,
        .y = lhs.y - rhs.y * m.y
    };
}
#else
;
#endif
/// @brief Difference of two u8v3 with lhs multiplied with a u8
SL_header u8v3 SL_u8v3subM(u8v3 lhs, u8v3 rhs, u8v3 m)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v3) {
        .x = lhs.x - rhs.x * m.x,
        .y = lhs.y - rhs.y * m.y,
        .z = lhs.z - rhs.z * m.z
    };
}
#else
;
#endif
/// @brief Difference of two u8v4 with lhs multiplied with a u8
SL_header u8v4 SL_u8v4subM(u8v4 lhs, u8v4 rhs, u8v4 m)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v4) {
        .x = lhs.x - rhs.x * m.x,
        .y = lhs.y - rhs.y * m.y,
        .z = lhs.z - rhs.z * m.z,
        .w = lhs.w - rhs.w * m.w
    };
}
#else
;
#endif
/// @brief Addition of two u8v with lhs scaled by u8 and multiplied with a u8
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8* SL_u8vaddSM_(u8* lhs, u8* rhs, u8 s, u8* m, u8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] + rhs[i] * s * m[i];
    return dest;
}
#else
;
#endif
/// @brief Addition of two u8v with lhs scaled by u8 and multiplied with a u8
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8v SL_u8vaddSM(u8v lhs, u8v rhs, u8 s, u8v m, u8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u8vaddSM_(lhs.data, rhs.data, s, m.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two u8v2 with lhs scaled by u8 and multiplied with a u8
SL_header u8v2 SL_u8v2addSM(u8v2 lhs, u8v2 rhs, u8 s, u8v2 m)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v2) {
        .x = lhs.x + rhs.x * s * m.x,
        .y = lhs.y + rhs.y * s * m.y
    };
}
#else
;
#endif
/// @brief Addition of two u8v3 with lhs scaled by u8 and multiplied with a u8
SL_header u8v3 SL_u8v3addSM(u8v3 lhs, u8v3 rhs, u8 s, u8v3 m)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v3) {
        .x = lhs.x + rhs.x * s * m.x,
        .y = lhs.y + rhs.y * s * m.y,
        .z = lhs.z + rhs.z * s * m.z
    };
}
#else
;
#endif
/// @brief Addition of two u8v4 with lhs scaled by u8 and multiplied with a u8
SL_header u8v4 SL_u8v4addSM(u8v4 lhs, u8v4 rhs, u8 s, u8v4 m)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v4) {
        .x = lhs.x + rhs.x * s * m.x,
        .y = lhs.y + rhs.y * s * m.y,
        .z = lhs.z + rhs.z * s * m.z,
        .w = lhs.w + rhs.w * s * m.w
    };
}
#else
;
#endif
/// @brief Difference of two u8v with lhs scaled by u8 and multiplied with a u8
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8* SL_u8vsubSM_(u8* lhs, u8* rhs, u8 s, u8* m, u8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] - rhs[i] * s * m[i];
    return dest;
}
#else
;
#endif
/// @brief Difference of two u8v with lhs scaled by u8 and multiplied with a u8
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8v SL_u8vsubSM(u8v lhs, u8v rhs, u8 s, u8v m, u8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u8vsubSM_(lhs.data, rhs.data, s, m.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two u8v2 with lhs scaled by u8 and multiplied with a u8
SL_header u8v2 SL_u8v2subSM(u8v2 lhs, u8v2 rhs, u8 s, u8v2 m)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v2) {
        .x = lhs.x - rhs.x * s * m.x,
        .y = lhs.y - rhs.y * s * m.y
    };
}
#else
;
#endif
/// @brief Difference of two u8v3 with lhs scaled by u8 and multiplied with a u8
SL_header u8v3 SL_u8v3subSM(u8v3 lhs, u8v3 rhs, u8 s, u8v3 m)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v3) {
        .x = lhs.x - rhs.x * s * m.x,
        .y = lhs.y - rhs.y * s * m.y,
        .z = lhs.z - rhs.z * s * m.z
    };
}
#else
;
#endif
/// @brief Difference of two u8v4 with lhs scaled by u8 and multiplied with a u8
SL_header u8v4 SL_u8v4subSM(u8v4 lhs, u8v4 rhs, u8 s, u8v4 m)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v4) {
        .x = lhs.x - rhs.x * s * m.x,
        .y = lhs.y - rhs.y * s * m.y,
        .z = lhs.z - rhs.z * s * m.z,
        .w = lhs.w - rhs.w * s * m.w
    };
}
#else
;
#endif
/// @brief Addition of two u8v with rhs scaled by a u8
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8* SL_u8vSadd_(u8* lhs, u8 s, u8* rhs, u8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * s + rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Addition of two u8v with rhs scaled by a u8
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8v SL_u8vSadd(u8v lhs, u8 s, u8v rhs, u8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u8vSadd_(lhs.data, s, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two u8v2 with rhs scaled by a u8
SL_header u8v2 SL_u8v2Sadd(u8v2 lhs, u8 s, u8v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v2) {
        .x = lhs.x * s + rhs.x,
        .y = lhs.y * s + rhs.y
    };
}
#else
;
#endif
/// @brief Addition of two u8v3 with rhs scaled by a u8
SL_header u8v3 SL_u8v3Sadd(u8v3 lhs, u8 s, u8v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v3) {
        .x = lhs.x * s + rhs.x,
        .y = lhs.y * s + rhs.y,
        .z = lhs.z * s + rhs.z
    };
}
#else
;
#endif
/// @brief Addition of two u8v4 with rhs scaled by a u8
SL_header u8v4 SL_u8v4Sadd(u8v4 lhs, u8 s, u8v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v4) {
        .x = lhs.x * s + rhs.x,
        .y = lhs.y * s + rhs.y,
        .z = lhs.z * s + rhs.z,
        .w = lhs.w * s + rhs.w
    };
}
#else
;
#endif
/// @brief Difference of two u8v with rhs scaled by a u8
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8* SL_u8vSsub_(u8* lhs, u8 s, u8* rhs, u8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * s - rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Difference of two u8v with rhs scaled by a u8
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8v SL_u8vSsub(u8v lhs, u8 s, u8v rhs, u8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u8vSsub_(lhs.data, s, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two u8v2 with rhs scaled by a u8
SL_header u8v2 SL_u8v2Ssub(u8v2 lhs, u8 s, u8v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v2) {
        .x = lhs.x * s - rhs.x,
        .y = lhs.y * s - rhs.y
    };
}
#else
;
#endif
/// @brief Difference of two u8v3 with rhs scaled by a u8
SL_header u8v3 SL_u8v3Ssub(u8v3 lhs, u8 s, u8v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v3) {
        .x = lhs.x * s - rhs.x,
        .y = lhs.y * s - rhs.y,
        .z = lhs.z * s - rhs.z
    };
}
#else
;
#endif
/// @brief Difference of two u8v4 with rhs scaled by a u8
SL_header u8v4 SL_u8v4Ssub(u8v4 lhs, u8 s, u8v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v4) {
        .x = lhs.x * s - rhs.x,
        .y = lhs.y * s - rhs.y,
        .z = lhs.z * s - rhs.z,
        .w = lhs.w * s - rhs.w
    };
}
#else
;
#endif
/// @brief Weighted sum of two u8v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8* SL_u8vmix_(u8* lhs, u8 lhs_w, u8* rhs, u8 rhs_w, u8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * lhs_w + rhs[i] * rhs_w;
    return dest;
}
#else
;
#endif
/// @brief Weighted sum of two u8v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8v SL_u8vmix(u8v lhs, u8 lhs_w, u8v rhs, u8 rhs_w, u8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u8vmix_(lhs.data, lhs_w, rhs.data, rhs_w, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Weighted sum of two u8v2
SL_header u8v2 SL_u8v2mix(u8v2 lhs, u8 lhs_w, u8v2 rhs, u8 rhs_w)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v2) {
        .x = lhs.x * lhs_w + rhs.x * rhs_w,
        .y = lhs.y * lhs_w + rhs.y * rhs_w
    };
}
#else
;
#endif
/// @brief Weighted sum of two u8v3
SL_header u8v3 SL_u8v3mix(u8v3 lhs, u8 lhs_w, u8v3 rhs, u8 rhs_w)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v3) {
        .x = lhs.x * lhs_w + rhs.x * rhs_w,
        .y = lhs.y * lhs_w + rhs.y * rhs_w,
        .z = lhs.z * lhs_w + rhs.z * rhs_w
    };
}
#else
;
#endif
/// @brief Weighted sum of two u8v4
SL_header u8v4 SL_u8v4mix(u8v4 lhs, u8 lhs_w, u8v4 rhs, u8 rhs_w)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v4) {
        .x = lhs.x * lhs_w + rhs.x * rhs_w,
        .y = lhs.y * lhs_w + rhs.y * rhs_w,
        .z = lhs.z * lhs_w + rhs.z * rhs_w,
        .w = lhs.w * lhs_w + rhs.w * rhs_w
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two u8v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8* SL_u8vmin_(u8* lhs, u8* rhs, u8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] < rhs[i] ? lhs[i] : rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise minimum of two u8v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8v SL_u8vmin(u8v lhs, u8v rhs, u8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u8vmin_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise minimum of two u8v2
SL_header u8v2 SL_u8v2min(u8v2 lhs, u8v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v2) {
        .x = lhs.x < rhs.x ? lhs.x : rhs.x,
        .y = lhs.y < rhs.y ? lhs.y : rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two u8v3
SL_header u8v3 SL_u8v3min(u8v3 lhs, u8v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v3) {
        .x = lhs.x < rhs.x ? lhs.x : rhs.x,
        .y = lhs.y < rhs.y ? lhs.y : rhs.y,
        .z = lhs.z < rhs.z ? lhs.z : rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two u8v4
SL_header u8v4 SL_u8v4min(u8v4 lhs, u8v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v4) {
        .x = lhs.x < rhs.x ? lhs.x : rhs.x,
        .y = lhs.y < rhs.y ? lhs.y : rhs.y,
        .z = lhs.z < rhs.z ? lhs.z : rhs.z,
        .w = lhs.w < rhs.w ? lhs.w : rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two u8v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8* SL_u8vmax_(u8* lhs, u8* rhs, u8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] > rhs[i] ? lhs[i] : rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise maximum of two u8v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8v SL_u8vmax(u8v lhs, u8v rhs, u8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u8vmax_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise maximum of two u8v2
SL_header u8v2 SL_u8v2max(u8v2 lhs, u8v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v2) {
        .x = lhs.x > rhs.x ? lhs.x : rhs.x,
        .y = lhs.y > rhs.y ? lhs.y : rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two u8v3
SL_header u8v3 SL_u8v3max(u8v3 lhs, u8v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v3) {
        .x = lhs.x > rhs.x ? lhs.x : rhs.x,
        .y = lhs.y > rhs.y ? lhs.y : rhs.y,
        .z = lhs.z > rhs.z ? lhs.z : rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two u8v4
SL_header u8v4 SL_u8v4max(u8v4 lhs, u8v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v4) {
        .x = lhs.x > rhs.x ? lhs.x : rhs.x,
        .y = lhs.y > rhs.y ? lhs.y : rhs.y,
        .z = lhs.z > rhs.z ? lhs.z : rhs.z,
        .w = lhs.w > rhs.w ? lhs.w : rhs.w
    };
}
#else
;
#endif
/// @brief Dot product of two u8v
/// @note All vectors are assumed to be of size 'count'
SL_header u64 SL_u8vdot_(u8* lhs, u8* rhs, usize count)
#if defined(SL_IMPLEMENTATION)
{
    u64 dest = 0;
    for (usize i = 0; i < count; ++i) dest += lhs[i] * rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Dot product of two u8v
/// @note All vectors are assumed to be of size 'count'
SL_header u64 SL_u8vdot(u8v lhs, u8v rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u8vdot_(lhs.data, rhs.data, lhs.count);
}
#else
;
#endif
/// @brief Dot product of two u8v2
SL_header u64 SL_u8v2dot(u8v2 lhs, u8v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}
#else
;
#endif
/// @brief Dot product of two u8v3
SL_header u64 SL_u8v3dot(u8v3 lhs, u8v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}
#else
;
#endif
/// @brief Dot product of two u8v4
SL_header u64 SL_u8v4dot(u8v4 lhs, u8v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}
#else
;
#endif
/// @brief Maximum component of a u8v
/// @note All vectors are assumed to be of size 'count'
SL_header u64 SL_u8vlen_max_(u8* v, usize count)
#if defined(SL_IMPLEMENTATION)
{
    u64 dest = 0;
    for (usize i = 0; i < count; ++i) dest = v[i] > dest ? v[i] : dest;
    return dest;
}
#else
;
#endif
/// @brief Maximum component of a u8v
/// @note All vectors are assumed to be of size 'count'
SL_header u64 SL_u8vlen_max(u8v v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u8vlen_max_(v.data, v.count);
}
#else
;
#endif
/// @brief Maximum component of a u8v2
SL_header u64 SL_u8v2len_max(u8v2 v)
#if defined(SL_IMPLEMENTATION)
{
    return v.x > v.y ? v.x : v.y;
}
#else
;
#endif
/// @brief Maximum component of a u8v3
SL_header u64 SL_u8v3len_max(u8v3 v)
#if defined(SL_IMPLEMENTATION)
{
    return v.x > v.y ? (v.x > v.z ? v.x : v.z) : (v.y > v.z ? v.y : v.z);
}
#else
;
#endif
/// @brief Maximum component of a u8v4
SL_header u64 SL_u8v4len_max(u8v4 v)
#if defined(SL_IMPLEMENTATION)
{
    return v.x > v.y ? (v.x > v.z ? (v.x > v.w ? v.x : v.w) : (v.z > v.w ? v.z : v.w)) : (v.y > v.z ? (v.y > v.w ? v.y : v.w) : (v.z > v.w ? v.z : v.w));
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a u8v
/// @note All vectors are assumed to be of size 'count'
SL_header u64 SL_u8vlen_manh_(u8* v, usize count)
#if defined(SL_IMPLEMENTATION)
{
    u64 dest = 0;
    for (usize i = 0; i < count; ++i) dest += v[i];
    return dest;
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a u8v
/// @note All vectors are assumed to be of size 'count'
SL_header u64 SL_u8vlen_manh(u8v v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u8vlen_manh_(v.data, v.count);
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a u8v2
SL_header u64 SL_u8v2len_manh(u8v2 v)
#if defined(SL_IMPLEMENTATION)
{
    return v.x + v.y;
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a u8v3
SL_header u64 SL_u8v3len_manh(u8v3 v)
#if defined(SL_IMPLEMENTATION)
{
    return v.x + v.y + v.z;
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a u8v4
SL_header u64 SL_u8v4len_manh(u8v4 v)
#if defined(SL_IMPLEMENTATION)
{
    return v.x + v.y + v.z + v.w;
}
#else
;
#endif
/// @brief Squared euclidean length of a u8v
/// @note All vectors are assumed to be of size 'count'
SL_header u64 SL_u8vlen_srq_(u8* v, usize count)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u8vdot_(v, v, count);
}
#else
;
#endif
/// @brief Squared euclidean length of a u8v
/// @note All vectors are assumed to be of size 'count'
SL_header u64 SL_u8vlen_srq(u8v v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u8vlen_srq_(v.data, v.count);
}
#else
;
#endif
/// @brief Square length of a u8v2
SL_header u64 SL_u8v2len_sqr(u8v2 v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u8v2dot(v, v);
}
#else
;
#endif
/// @brief Square length of a u8v3
SL_header u64 SL_u8v3len_sqr(u8v3 v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u8v3dot(v, v);
}
#else
;
#endif
/// @brief Square length of a u8v4
SL_header u64 SL_u8v4len_sqr(u8v4 v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u8v4dot(v, v);
}
#else
;
#endif
/// @brief Euclidean length of a u8v
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_u8vlen_(u8* v, usize count)
#if defined(SL_IMPLEMENTATION)
{
    return sqrt(SL_u8vdot_(v, v, count));
}
#else
;
#endif
/// @brief Euclidean length of a u8v
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_u8vlen(u8v v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u8vlen_(v.data, v.count);
}
#else
;
#endif
/// @brief Euclidean length of a u8v2
SL_header double SL_u8v2len(u8v2 v)
#if defined(SL_IMPLEMENTATION)
{
    return sqrt(SL_u8v2dot(v, v));
}
#else
;
#endif
/// @brief Euclidean length of a u8v3
SL_header double SL_u8v3len(u8v3 v)
#if defined(SL_IMPLEMENTATION)
{
    return sqrt(SL_u8v3dot(v, v));
}
#else
;
#endif
/// @brief Euclidean length of a u8v4
SL_header double SL_u8v4len(u8v4 v)
#if defined(SL_IMPLEMENTATION)
{
    return sqrt(SL_u8v4dot(v, v));
}
#else
;
#endif
/// @brief Euclidean distance bewteen two u8v
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_u8vdist_(u8* lhs, u8* rhs, usize count)
#if defined(SL_IMPLEMENTATION)
{
    double accum = 0;
    for (int i = 0; i < count; ++i) accum += (lhs[i] - rhs[i]) * (lhs[i] - rhs[i]);
    return sqrt(accum);
}
#else
;
#endif
/// @brief Euclidean distance bewteen two u8v
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_u8vdist(u8v lhs, u8v rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u8vdist_(lhs.data, rhs.data, lhs.count);
}
#else
;
#endif
/// @brief Euclidean distance between two u8v2
SL_header double SL_u8v2dist(u8v2 lhs, u8v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u8v2len(SL_u8v2sub(lhs, rhs));
}
#else
;
#endif
/// @brief Euclidean distance between two u8v3
SL_header double SL_u8v3dist(u8v3 lhs, u8v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u8v3len(SL_u8v3sub(lhs, rhs));
}
#else
;
#endif
/// @brief Euclidean distance between two u8v4
SL_header double SL_u8v4dist(u8v4 lhs, u8v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u8v4len(SL_u8v4sub(lhs, rhs));
}
#else
;
#endif
/// @brief Reflection of u8v2 v around vector u8v2 n
SL_header u8v2 SL_u8v2refl(u8v2 v, u8v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u8v2subS(v, n, 2.0 * SL_u8v2dot(v, n) / SL_u8v2dot(n, n));
}
#else
;
#endif
/// @brief Reflection of u8v3 v around vector u8v3 n
SL_header u8v3 SL_u8v3refl(u8v3 v, u8v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u8v3subS(v, n, 2.0 * SL_u8v3dot(v, n) / SL_u8v3dot(n, n));
}
#else
;
#endif
/// @brief Reflection of u8v4 v around vector u8v4 n
SL_header u8v4 SL_u8v4refl(u8v4 v, u8v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u8v4subS(v, n, 2.0 * SL_u8v4dot(v, n) / SL_u8v4dot(n, n));
}
#else
;
#endif
/// @brief Reflection of u8v2 v around vector u8v2 n assumed to be of unit length
SL_header u8v2 SL_u8v2refl_u(u8v2 v, u8v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u8v2subS(v, n, 2.0 * SL_u8v2dot(v, n));
}
#else
;
#endif
/// @brief Reflection of u8v3 v around vector u8v3 n assumed to be of unit length
SL_header u8v3 SL_u8v3refl_u(u8v3 v, u8v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u8v3subS(v, n, 2.0 * SL_u8v3dot(v, n));
}
#else
;
#endif
/// @brief Reflection of u8v4 v around vector u8v4 n assumed to be of unit length
SL_header u8v4 SL_u8v4refl_u(u8v4 v, u8v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u8v4subS(v, n, 2.0 * SL_u8v4dot(v, n));
}
#else
;
#endif
/// @brief Get component of u8v2 v in direction u8v2 n
SL_header u8v2 SL_u8v2align(u8v2 v, u8v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u8v2muls(n, SL_u8v2dot(v, n) / SL_u8v2dot(n, n));
}
#else
;
#endif
/// @brief Get component of u8v3 v in direction u8v3 n
SL_header u8v3 SL_u8v3align(u8v3 v, u8v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u8v3muls(n, SL_u8v3dot(v, n) / SL_u8v3dot(n, n));
}
#else
;
#endif
/// @brief Get component of u8v4 v in direction u8v4 n
SL_header u8v4 SL_u8v4align(u8v4 v, u8v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u8v4muls(n, SL_u8v4dot(v, n) / SL_u8v4dot(n, n));
}
#else
;
#endif
/// @brief Get component of u8v2 v in direction u8v2 n assumed to be of unit length
SL_header u8v2 SL_u8v2align_u(u8v2 v, u8v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u8v2muls(n, SL_u8v2dot(v, n));
}
#else
;
#endif
/// @brief Get component of u8v3 v in direction u8v3 n assumed to be of unit length
SL_header u8v3 SL_u8v3align_u(u8v3 v, u8v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u8v3muls(n, SL_u8v3dot(v, n));
}
#else
;
#endif
/// @brief Get component of u8v4 v in direction u8v4 n assumed to be of unit length
SL_header u8v4 SL_u8v4align_u(u8v4 v, u8v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u8v4muls(n, SL_u8v4dot(v, n));
}
#else
;
#endif
/// @brief Project u8v2 v on plane with normal u8v2 n
SL_header u8v2 SL_u8v2proj(u8v2 v, u8v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u8v2sub(v, SL_u8v2align(v, n));
}
#else
;
#endif
/// @brief Project u8v3 v on plane with normal u8v3 n
SL_header u8v3 SL_u8v3proj(u8v3 v, u8v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u8v3sub(v, SL_u8v3align(v, n));
}
#else
;
#endif
/// @brief Project u8v4 v on plane with normal u8v4 n
SL_header u8v4 SL_u8v4proj(u8v4 v, u8v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u8v4sub(v, SL_u8v4align(v, n));
}
#else
;
#endif
/// @brief Project u8v2 v on plane with normal u8v2 n
SL_header u8v2 SL_u8v2proj_u(u8v2 v, u8v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u8v2sub(v, SL_u8v2align_u(v, n));
}
#else
;
#endif
/// @brief Project u8v3 v on plane with normal u8v3 n
SL_header u8v3 SL_u8v3proj_u(u8v3 v, u8v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u8v3sub(v, SL_u8v3align_u(v, n));
}
#else
;
#endif
/// @brief Project u8v4 v on plane with normal u8v4 n
SL_header u8v4 SL_u8v4proj_u(u8v4 v, u8v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u8v4sub(v, SL_u8v4align_u(v, n));
}
#else
;
#endif
/// @brief Component-wise modulo of a u8v by scalar n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8* SL_u8vmods_(u8* v, u8 n, u8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = v[i] % n;
    return dest;
}
#else
;
#endif
/// @brief Component-wise modulo of a u8v by scalar n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8v SL_u8vmods(u8v v, u8 n, u8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u8vmods_(v.data, n, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise modulo of a u8v2 by scalar n
SL_header u8v2 SL_u8v2mods(u8v2 v, u8 n)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v2) {
        .x = v.x % n,
        .y = v.y % n
    };
}
#else
;
#endif
/// @brief Component-wise modulo of a u8v3 by scalar n
SL_header u8v3 SL_u8v3mods(u8v3 v, u8 n)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v3) {
        .x = v.x % n,
        .y = v.y % n,
        .z = v.z % n
    };
}
#else
;
#endif
/// @brief Component-wise modulo of a u8v4 by scalar n
SL_header u8v4 SL_u8v4mods(u8v4 v, u8 n)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v4) {
        .x = v.x % n,
        .y = v.y % n,
        .z = v.z % n,
        .w = v.w % n
    };
}
#else
;
#endif
/// @brief Component-wise modulo of a u8v by u8v n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8* SL_u8vmod_(u8* v, u8* n, u8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = v[i] % n[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise modulo of a u8v by u8v n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8v SL_u8vmod(u8v v, u8v n, u8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u8vmod_(v.data, n.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise modulo of a u8v2 by u8v2 n
SL_header u8v2 SL_u8v2mod(u8v2 v, u8v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v2) {
        .x = v.x % n.x,
        .y = v.y % n.y
    };
}
#else
;
#endif
/// @brief Component-wise modulo of a u8v3 by u8v3 n
SL_header u8v3 SL_u8v3mod(u8v3 v, u8v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v3) {
        .x = v.x % n.x,
        .y = v.y % n.y,
        .z = v.z % n.z
    };
}
#else
;
#endif
/// @brief Component-wise modulo of a u8v4 by u8v4 n
SL_header u8v4 SL_u8v4mod(u8v4 v, u8v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v4) {
        .x = v.x % n.x,
        .y = v.y % n.y,
        .z = v.z % n.z,
        .w = v.w % n.w
    };
}
#else
;
#endif
/// @brief Component-wise binary AND of two u8v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8* SL_u8vand_(u8* lhs, u8* rhs, u8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] & rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary AND of two u8v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8v SL_u8vand(u8v lhs, u8v rhs, u8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u8vand_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary AND of two u8v2
SL_header u8v2 SL_u8v2and(u8v2 lhs, u8v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v2) {
        .x = lhs.x & rhs.x,
        .y = lhs.y & rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise binary AND of two u8v3
SL_header u8v3 SL_u8v3and(u8v3 lhs, u8v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v3) {
        .x = lhs.x & rhs.x,
        .y = lhs.y & rhs.y,
        .z = lhs.z & rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise binary AND of two u8v4
SL_header u8v4 SL_u8v4and(u8v4 lhs, u8v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v4) {
        .x = lhs.x & rhs.x,
        .y = lhs.y & rhs.y,
        .z = lhs.z & rhs.z,
        .w = lhs.w & rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise binary OR of two u8v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8* SL_u8vor_(u8* lhs, u8* rhs, u8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] | rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary OR of two u8v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8v SL_u8vor(u8v lhs, u8v rhs, u8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u8vor_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary OR of two u8v2
SL_header u8v2 SL_u8v2or(u8v2 lhs, u8v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v2) {
        .x = lhs.x | rhs.x,
        .y = lhs.y | rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise binary OR of two u8v3
SL_header u8v3 SL_u8v3or(u8v3 lhs, u8v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v3) {
        .x = lhs.x | rhs.x,
        .y = lhs.y | rhs.y,
        .z = lhs.z | rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise binary OR of two u8v4
SL_header u8v4 SL_u8v4or(u8v4 lhs, u8v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v4) {
        .x = lhs.x | rhs.x,
        .y = lhs.y | rhs.y,
        .z = lhs.z | rhs.z,
        .w = lhs.w | rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise binary XOR of two u8v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8* SL_u8vxor_(u8* lhs, u8* rhs, u8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] ^ rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary XOR of two u8v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8v SL_u8vxor(u8v lhs, u8v rhs, u8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u8vxor_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary XOR of two u8v2
SL_header u8v2 SL_u8v2xor(u8v2 lhs, u8v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v2) {
        .x = lhs.x ^ rhs.x,
        .y = lhs.y ^ rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise binary XOR of two u8v3
SL_header u8v3 SL_u8v3xor(u8v3 lhs, u8v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v3) {
        .x = lhs.x ^ rhs.x,
        .y = lhs.y ^ rhs.y,
        .z = lhs.z ^ rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise binary XOR of two u8v4
SL_header u8v4 SL_u8v4xor(u8v4 lhs, u8v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v4) {
        .x = lhs.x ^ rhs.x,
        .y = lhs.y ^ rhs.y,
        .z = lhs.z ^ rhs.z,
        .w = lhs.w ^ rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise binary NOT of a u8v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8* SL_u8vnot_(u8* v, u8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = ~v[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary NOT of a u8v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8v SL_u8vnot(u8v v, u8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u8vnot_(v.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary NOT of a u8v2
SL_header u8v2 SL_u8v2not(u8v2 v)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v2) {
        .x = ~v.x,
        .y = ~v.y
    };
}
#else
;
#endif
/// @brief Component-wise binary NOT of a u8v3
SL_header u8v3 SL_u8v3not(u8v3 v)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v3) {
        .x = ~v.x,
        .y = ~v.y,
        .z = ~v.z
    };
}
#else
;
#endif
/// @brief Component-wise binary NOT of a u8v4
SL_header u8v4 SL_u8v4not(u8v4 v)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v4) {
        .x = ~v.x,
        .y = ~v.y,
        .z = ~v.z,
        .w = ~v.w
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a u8v by integer n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8* SL_u8vlshfts_(u8* lhs, u8 rhs, u8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] << rhs;
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a u8v by integer n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8v SL_u8vlshfts(u8v lhs, u8 rhs, u8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u8vlshfts_(lhs.data, rhs, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a u8v2 by integer n
SL_header u8v2 SL_u8v2lshfts(u8v2 lhs, u8 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v2) {
        .x = lhs.x << rhs,
        .y = lhs.y << rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a u8v3 by integer n
SL_header u8v3 SL_u8v3lshfts(u8v3 lhs, u8 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v3) {
        .x = lhs.x << rhs,
        .y = lhs.y << rhs,
        .z = lhs.z << rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a u8v4 by integer n
SL_header u8v4 SL_u8v4lshfts(u8v4 lhs, u8 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v4) {
        .x = lhs.x << rhs,
        .y = lhs.y << rhs,
        .z = lhs.z << rhs,
        .w = lhs.w << rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a u8v by u8v n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8* SL_u8vlshft_(u8* lhs, u8* rhs, u8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] << rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a u8v by u8v n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8v SL_u8vlshft(u8v lhs, u8v rhs, u8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u8vlshft_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a u8v2 by u8v2 n
SL_header u8v2 SL_u8v2lshft(u8v2 lhs, u8v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v2) {
        .x = lhs.x << rhs.x,
        .y = lhs.y << rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a u8v3 by u8v3 n
SL_header u8v3 SL_u8v3lshft(u8v3 lhs, u8v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v3) {
        .x = lhs.x << rhs.x,
        .y = lhs.y << rhs.y,
        .z = lhs.z << rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a u8v4 by u8v4 n
SL_header u8v4 SL_u8v4lshft(u8v4 lhs, u8v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v4) {
        .x = lhs.x << rhs.x,
        .y = lhs.y << rhs.y,
        .z = lhs.z << rhs.z,
        .w = lhs.w << rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a u8v by interger n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8* SL_u8vrshfts_(u8* lhs, u8 rhs, u8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] >> rhs;
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a u8v by interger n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8v SL_u8vrshfts(u8v lhs, u8 rhs, u8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u8vrshfts_(lhs.data, rhs, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a u8v2 by interger n
SL_header u8v2 SL_u8v2rshfts(u8v2 lhs, u8 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v2) {
        .x = lhs.x >> rhs,
        .y = lhs.y >> rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a u8v3 by interger n
SL_header u8v3 SL_u8v3rshfts(u8v3 lhs, u8 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v3) {
        .x = lhs.x >> rhs,
        .y = lhs.y >> rhs,
        .z = lhs.z >> rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a u8v4 by interger n
SL_header u8v4 SL_u8v4rshfts(u8v4 lhs, u8 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v4) {
        .x = lhs.x >> rhs,
        .y = lhs.y >> rhs,
        .z = lhs.z >> rhs,
        .w = lhs.w >> rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a u8v by u8v n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8* SL_u8vrshft_(u8* lhs, u8* rhs, u8* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] >> rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a u8v by u8v n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u8v SL_u8vrshft(u8v lhs, u8v rhs, u8v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u8vrshft_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a u8v2 by u8v2 n
SL_header u8v2 SL_u8v2rshft(u8v2 lhs, u8v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v2) {
        .x = lhs.x >> rhs.x,
        .y = lhs.y >> rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a u8v3 by u8v3 n
SL_header u8v3 SL_u8v3rshft(u8v3 lhs, u8v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v3) {
        .x = lhs.x >> rhs.x,
        .y = lhs.y >> rhs.y,
        .z = lhs.z >> rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a u8v4 by u8v4 n
SL_header u8v4 SL_u8v4rshft(u8v4 lhs, u8v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u8v4) {
        .x = lhs.x >> rhs.x,
        .y = lhs.y >> rhs.y,
        .z = lhs.z >> rhs.z,
        .w = lhs.w >> rhs.w
    };
}
#else
;
#endif
#pragma endregion U8
#pragma region U16

/// @brief Vector of u16 with arbitrary dimension
typedef struct {
    const usize count;
    u16 *data;
} u16v;

/// @brief Vector of u16 with dimension 2
typedef union {
    u16 data[2];
    struct {
        union { u16 x, r, u; };
        union { u16 y, g, v; };
    };
} u16v2;

#define SL_u16v2_zero  ((u16v2){.x =  0, .y =  0})
#define SL_u16v2_one   ((u16v2){.x =  1, .y =  1})
#define SL_u16v2_right ((u16v2){.x =  1, .y =  0})
#define SL_u16v2_up    ((u16v2){.x =  0, .y =  1})

/// @brief Vector of u16 with dimension 3
typedef union {
    u16 data[3];
    struct {
        union { u16 x, r, u; };
        union { u16 y, g, v; };
        union { u16 z, b, s; };
    };
    struct {
        union { u16 __x, __r, __u; };
        union { u16v2 yz, gb, vs; };
    };
    struct {
        union { u16v2 xy, rg, uv; };
        union { u16 __z, __b, __s; };
    };
} u16v3;

#define SL_u16v3_zero  ((u16v3){.x =  0, .y =  0, .z =  0})
#define SL_u16v3_one   ((u16v3){.x =  1, .y =  1, .z =  1})
#define SL_u16v3_right ((u16v3){.x =  1, .y =  0, .z =  0})
#define SL_u16v3_up    ((u16v3){.x =  0, .y =  1, .z =  0})
#define SL_u16v3_forw  ((u16v3){.x =  0, .y =  0, .z =  1})

/// @brief Vector of u16 with dimension 4
typedef union {
    u16 data[4];
    struct {
        union { u16 x, r, u; };
        union { u16 y, g, v; };
        union { u16 z, b, s; };
        union { u16 w, a, t; };
    };
    struct {
        union { u16 __x0, __r0, __u0; };
        union { u16v2 yz, gb, vs; };
        union { u16 __w0, __a0, __t0; };
    };
    struct {
        union { u16v2 xy, rb, uv; };
        union { u16v2 zw, ba, st; };
    };
    struct {
        union { u16v3 xyz, rgb, uvs; };
        union { u16 __w1, __a1, __t1; };
    };
    struct {
        union { u16 __x1, __r1, __u1; };
        union { u16v3 yzw, gba, vst; };
    };
} u16v4;

#define SL_u16v4_zero  ((u16v4){.x = 0, .y = 0, .z = 0, .w = 0})
#define SL_u16v4_one   ((u16v4){.x = 1, .y = 1, .z = 1, .w = 1})

#define SL_u16v4_white  ((u16v4){.x = 1, .y = 1, .z = 1, .w = 1})
#define SL_u16v4_black  ((u16v4){.x = 0, .y = 0, .z = 0, .w = 1})
#define SL_u16v4_red    ((u16v4){.x = 1, .y = 0, .z = 0, .w = 1})
#define SL_u16v4_green  ((u16v4){.x = 0, .y = 1, .z = 0, .w = 1})
#define SL_u16v4_blue   ((u16v4){.x = 0, .y = 0, .z = 1, .w = 1})
#define SL_u16v4_yellow ((u16v4){.x = 1, .y = 1, .z = 0, .w = 1})
#define SL_u16v4_cyan   ((u16v4){.x = 0, .y = 1, .z = 1, .w = 1})
#define SL_u16v4_purple ((u16v4){.x = 1, .y = 0, .z = 1, .w = 1})



#define SL_u16v2_(X, Y)       ((u16v2){.x = X, .y = Y})
#define SL_u16v3_(X, Y, Z)    ((u16v3){.x = X, .y = Y, .z = Z})
#define SL_u16v4_(X, Y, Z, W) ((u16v4){.x = X, .y = Y, .z = Z, .w = W})

#define SL_u16v2s(S)          ((u16v2){.x = S, .y = S})
#define SL_u16v3s(S)          ((u16v3){.x = S, .y = S, .z = S})
#define SL_u16v4s(S)          ((u16v4){.x = S, .y = S, .z = S, .w = S})

#define SL_u16vv(V)           ((u16v){.count = vsize(V), .data = (V).data})
#define SL_u16v2v(V, ...)     ((u16v2){.x = (V).x, .y = (V).y})
#define SL_u16v3v(V, ...)     ((u16v3){.x = (V).x, .y = (V).y, .z = (SL_vsize(V) >= 3 ? (V).data[2] : (0, ##__VA_ARGS__))})
#define SL_u16v4v(V, ...)     ((u16v4){.x = (V).x, .y = (V).y, .z = (SL_vsize(V) >= 3 ? (V).data[2] : ((const float[]){0, ##__VA_ARGS__, 0})[1]), .w = (SL_vsize(V) >= 4 ? (V).data[3] : ((const float[]){0, ##__VA_ARGS__, 0, 0})[2])})



/// @brief Equality of two u16v
/// @note All vectors are assumed to be of size 'count'
SL_header bool SL_u16vequ_(u16* lhs, u16* rhs, usize count)
#if defined(SL_IMPLEMENTATION)
{
    bool dest = true;
    for (usize i = 0; i < count; ++i) dest &= lhs[i] == rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Equality of two u16v
/// @note All vectors are assumed to be of size 'count'
SL_header bool SL_u16vequ(u16v lhs, u16v rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u16vequ_(lhs.data, rhs.data, lhs.count);
}
#else
;
#endif
/// @brief Equality of two u16v2
SL_header bool SL_u16v2equ(u16v2 lhs, u16v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}
#else
;
#endif
/// @brief Equality of two u16v3
SL_header bool SL_u16v3equ(u16v3 lhs, u16v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}
#else
;
#endif
/// @brief Equality of two u16v4
SL_header bool SL_u16v4equ(u16v4 lhs, u16v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
}
#else
;
#endif
/// @brief Addition of two u16v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16* SL_u16vadd_(u16* lhs, u16* rhs, u16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] + rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Addition of two u16v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16v SL_u16vadd(u16v lhs, u16v rhs, u16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u16vadd_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two u16v2
SL_header u16v2 SL_u16v2add(u16v2 lhs, u16v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v2) {
        .x = lhs.x + rhs.x,
        .y = lhs.y + rhs.y
    };
}
#else
;
#endif
/// @brief Addition of two u16v3
SL_header u16v3 SL_u16v3add(u16v3 lhs, u16v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v3) {
        .x = lhs.x + rhs.x,
        .y = lhs.y + rhs.y,
        .z = lhs.z + rhs.z
    };
}
#else
;
#endif
/// @brief Addition of two u16v4
SL_header u16v4 SL_u16v4add(u16v4 lhs, u16v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v4) {
        .x = lhs.x + rhs.x,
        .y = lhs.y + rhs.y,
        .z = lhs.z + rhs.z,
        .w = lhs.w + rhs.w
    };
}
#else
;
#endif
/// @brief Difference of two u16v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16* SL_u16vsub_(u16* lhs, u16* rhs, u16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] - rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Difference of two u16v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16v SL_u16vsub(u16v lhs, u16v rhs, u16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u16vsub_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two u16v2
SL_header u16v2 SL_u16v2sub(u16v2 lhs, u16v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v2) {
        .x = lhs.x - rhs.x,
        .y = lhs.y - rhs.y
    };
}
#else
;
#endif
/// @brief Difference of two u16v3
SL_header u16v3 SL_u16v3sub(u16v3 lhs, u16v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v3) {
        .x = lhs.x - rhs.x,
        .y = lhs.y - rhs.y,
        .z = lhs.z - rhs.z
    };
}
#else
;
#endif
/// @brief Difference of two u16v4
SL_header u16v4 SL_u16v4sub(u16v4 lhs, u16v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v4) {
        .x = lhs.x - rhs.x,
        .y = lhs.y - rhs.y,
        .z = lhs.z - rhs.z,
        .w = lhs.w - rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of two u16v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16* SL_u16vmul_(u16* lhs, u16* rhs, u16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise multiplication of two u16v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16v SL_u16vmul(u16v lhs, u16v rhs, u16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u16vmul_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise multiplication of two u16v2
SL_header u16v2 SL_u16v2mul(u16v2 lhs, u16v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v2) {
        .x = lhs.x * rhs.x,
        .y = lhs.y * rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of two u16v3
SL_header u16v3 SL_u16v3mul(u16v3 lhs, u16v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v3) {
        .x = lhs.x * rhs.x,
        .y = lhs.y * rhs.y,
        .z = lhs.z * rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of two u16v4
SL_header u16v4 SL_u16v4mul(u16v4 lhs, u16v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v4) {
        .x = lhs.x * rhs.x,
        .y = lhs.y * rhs.y,
        .z = lhs.z * rhs.z,
        .w = lhs.w * rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of a u16v with a scalar
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16* SL_u16vmuls_(u16* lhs, u16 rhs, u16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * rhs;
    return dest;
}
#else
;
#endif
/// @brief Component-wise multiplication of a u16v with a scalar
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16v SL_u16vmuls(u16v lhs, u16 rhs, u16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u16vmuls_(lhs.data, rhs, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise multiplication of a u16v2 with a scalar
SL_header u16v2 SL_u16v2muls(u16v2 lhs, u16 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v2) {
        .x = lhs.x * rhs,
        .y = lhs.y * rhs
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of a u16v3 with a scalar
SL_header u16v3 SL_u16v3muls(u16v3 lhs, u16 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v3) {
        .x = lhs.x * rhs,
        .y = lhs.y * rhs,
        .z = lhs.z * rhs
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of a u16v4 with a scalar
SL_header u16v4 SL_u16v4muls(u16v4 lhs, u16 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v4) {
        .x = lhs.x * rhs,
        .y = lhs.y * rhs,
        .z = lhs.z * rhs,
        .w = lhs.w * rhs
    };
}
#else
;
#endif
/// @brief Component-wise division of two u16v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16* SL_u16vdiv_(u16* lhs, u16* rhs, u16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] / rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise division of two u16v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16v SL_u16vdiv(u16v lhs, u16v rhs, u16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u16vdiv_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise division of two u16v2
SL_header u16v2 SL_u16v2div(u16v2 lhs, u16v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v2) {
        .x = lhs.x / rhs.x,
        .y = lhs.y / rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise division of two u16v3
SL_header u16v3 SL_u16v3div(u16v3 lhs, u16v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v3) {
        .x = lhs.x / rhs.x,
        .y = lhs.y / rhs.y,
        .z = lhs.z / rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise division of two u16v4
SL_header u16v4 SL_u16v4div(u16v4 lhs, u16v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v4) {
        .x = lhs.x / rhs.x,
        .y = lhs.y / rhs.y,
        .z = lhs.z / rhs.z,
        .w = lhs.w / rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise division of a u16v with a scalar
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16* SL_u16vdivs_(u16* lhs, u16 rhs, u16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] / rhs;
    return dest;
}
#else
;
#endif
/// @brief Component-wise division of a u16v with a scalar
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16v SL_u16vdivs(u16v lhs, u16 rhs, u16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u16vdivs_(lhs.data, rhs, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise division of a u16v2 with a scalar
SL_header u16v2 SL_u16v2divs(u16v2 lhs, u16 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v2) {
        .x = lhs.x / rhs,
        .y = lhs.y / rhs
    };
}
#else
;
#endif
/// @brief Component-wise division of a u16v3 with a scalar
SL_header u16v3 SL_u16v3divs(u16v3 lhs, u16 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v3) {
        .x = lhs.x / rhs,
        .y = lhs.y / rhs,
        .z = lhs.z / rhs
    };
}
#else
;
#endif
/// @brief Component-wise division of a u16v4 with a scalar
SL_header u16v4 SL_u16v4divs(u16v4 lhs, u16 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v4) {
        .x = lhs.x / rhs,
        .y = lhs.y / rhs,
        .z = lhs.z / rhs,
        .w = lhs.w / rhs
    };
}
#else
;
#endif
/// @brief Addition of two u16v with lhs scaled by a u16
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16* SL_u16vaddS_(u16* lhs, u16* rhs, u16 s, u16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] + rhs[i] * s;
    return dest;
}
#else
;
#endif
/// @brief Addition of two u16v with lhs scaled by a u16
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16v SL_u16vaddS(u16v lhs, u16v rhs, u16 s, u16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u16vaddS_(lhs.data, rhs.data, s, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two u16v2 with lhs scaled by a u16
SL_header u16v2 SL_u16v2addS(u16v2 lhs, u16v2 rhs, u16 s)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v2) {
        .x = lhs.x + rhs.x * s,
        .y = lhs.y + rhs.y * s
    };
}
#else
;
#endif
/// @brief Addition of two u16v3 with lhs scaled by a u16
SL_header u16v3 SL_u16v3addS(u16v3 lhs, u16v3 rhs, u16 s)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v3) {
        .x = lhs.x + rhs.x * s,
        .y = lhs.y + rhs.y * s,
        .z = lhs.z + rhs.z * s
    };
}
#else
;
#endif
/// @brief Addition of two u16v4 with lhs scaled by a u16
SL_header u16v4 SL_u16v4addS(u16v4 lhs, u16v4 rhs, u16 s)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v4) {
        .x = lhs.x + rhs.x * s,
        .y = lhs.y + rhs.y * s,
        .z = lhs.z + rhs.z * s,
        .w = lhs.w + rhs.w * s
    };
}
#else
;
#endif
/// @brief Difference of two u16v with lhs scaled by a u16
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16* SL_u16vsubS_(u16* lhs, u16* rhs, u16 s, u16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] - rhs[i] * s;
    return dest;
}
#else
;
#endif
/// @brief Difference of two u16v with lhs scaled by a u16
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16v SL_u16vsubS(u16v lhs, u16v rhs, u16 s, u16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u16vsubS_(lhs.data, rhs.data, s, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two u16v2 with lhs scaled by a u16
SL_header u16v2 SL_u16v2subS(u16v2 lhs, u16v2 rhs, u16 s)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v2) {
        .x = lhs.x - rhs.x * s,
        .y = lhs.y - rhs.y * s
    };
}
#else
;
#endif
/// @brief Difference of two u16v3 with lhs scaled by a u16
SL_header u16v3 SL_u16v3subS(u16v3 lhs, u16v3 rhs, u16 s)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v3) {
        .x = lhs.x - rhs.x * s,
        .y = lhs.y - rhs.y * s,
        .z = lhs.z - rhs.z * s
    };
}
#else
;
#endif
/// @brief Difference of two u16v4 with lhs scaled by a u16
SL_header u16v4 SL_u16v4subS(u16v4 lhs, u16v4 rhs, u16 s)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v4) {
        .x = lhs.x - rhs.x * s,
        .y = lhs.y - rhs.y * s,
        .z = lhs.z - rhs.z * s,
        .w = lhs.w - rhs.w * s
    };
}
#else
;
#endif
/// @brief Addition of two u16v with lhs multiplied with a u16
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16* SL_u16vaddM_(u16* lhs, u16* rhs, u16* m, u16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] + rhs[i] * m[i];
    return dest;
}
#else
;
#endif
/// @brief Addition of two u16v with lhs multiplied with a u16
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16v SL_u16vaddM(u16v lhs, u16v rhs, u16v m, u16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u16vaddM_(lhs.data, rhs.data, m.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two u16v2 with lhs multiplied with a u16
SL_header u16v2 SL_u16v2addM(u16v2 lhs, u16v2 rhs, u16v2 m)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v2) {
        .x = lhs.x + rhs.x * m.x,
        .y = lhs.y + rhs.y * m.y
    };
}
#else
;
#endif
/// @brief Addition of two u16v3 with lhs multiplied with a u16
SL_header u16v3 SL_u16v3addM(u16v3 lhs, u16v3 rhs, u16v3 m)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v3) {
        .x = lhs.x + rhs.x * m.x,
        .y = lhs.y + rhs.y * m.y,
        .z = lhs.z + rhs.z * m.z
    };
}
#else
;
#endif
/// @brief Addition of two u16v4 with lhs multiplied with a u16
SL_header u16v4 SL_u16v4addM(u16v4 lhs, u16v4 rhs, u16v4 m)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v4) {
        .x = lhs.x + rhs.x * m.x,
        .y = lhs.y + rhs.y * m.y,
        .z = lhs.z + rhs.z * m.z,
        .w = lhs.w + rhs.w * m.w
    };
}
#else
;
#endif
/// @brief Difference of two u16v with lhs multiplied with a u16
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16* SL_u16vsubM_(u16* lhs, u16* rhs, u16* m, u16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] - rhs[i] * m[i];
    return dest;
}
#else
;
#endif
/// @brief Difference of two u16v with lhs multiplied with a u16
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16v SL_u16vsubM(u16v lhs, u16v rhs, u16v m, u16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u16vsubM_(lhs.data, rhs.data, m.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two u16v2 with lhs multiplied with a u16
SL_header u16v2 SL_u16v2subM(u16v2 lhs, u16v2 rhs, u16v2 m)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v2) {
        .x = lhs.x - rhs.x * m.x,
        .y = lhs.y - rhs.y * m.y
    };
}
#else
;
#endif
/// @brief Difference of two u16v3 with lhs multiplied with a u16
SL_header u16v3 SL_u16v3subM(u16v3 lhs, u16v3 rhs, u16v3 m)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v3) {
        .x = lhs.x - rhs.x * m.x,
        .y = lhs.y - rhs.y * m.y,
        .z = lhs.z - rhs.z * m.z
    };
}
#else
;
#endif
/// @brief Difference of two u16v4 with lhs multiplied with a u16
SL_header u16v4 SL_u16v4subM(u16v4 lhs, u16v4 rhs, u16v4 m)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v4) {
        .x = lhs.x - rhs.x * m.x,
        .y = lhs.y - rhs.y * m.y,
        .z = lhs.z - rhs.z * m.z,
        .w = lhs.w - rhs.w * m.w
    };
}
#else
;
#endif
/// @brief Addition of two u16v with lhs scaled by u16 and multiplied with a u16
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16* SL_u16vaddSM_(u16* lhs, u16* rhs, u16 s, u16* m, u16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] + rhs[i] * s * m[i];
    return dest;
}
#else
;
#endif
/// @brief Addition of two u16v with lhs scaled by u16 and multiplied with a u16
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16v SL_u16vaddSM(u16v lhs, u16v rhs, u16 s, u16v m, u16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u16vaddSM_(lhs.data, rhs.data, s, m.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two u16v2 with lhs scaled by u16 and multiplied with a u16
SL_header u16v2 SL_u16v2addSM(u16v2 lhs, u16v2 rhs, u16 s, u16v2 m)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v2) {
        .x = lhs.x + rhs.x * s * m.x,
        .y = lhs.y + rhs.y * s * m.y
    };
}
#else
;
#endif
/// @brief Addition of two u16v3 with lhs scaled by u16 and multiplied with a u16
SL_header u16v3 SL_u16v3addSM(u16v3 lhs, u16v3 rhs, u16 s, u16v3 m)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v3) {
        .x = lhs.x + rhs.x * s * m.x,
        .y = lhs.y + rhs.y * s * m.y,
        .z = lhs.z + rhs.z * s * m.z
    };
}
#else
;
#endif
/// @brief Addition of two u16v4 with lhs scaled by u16 and multiplied with a u16
SL_header u16v4 SL_u16v4addSM(u16v4 lhs, u16v4 rhs, u16 s, u16v4 m)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v4) {
        .x = lhs.x + rhs.x * s * m.x,
        .y = lhs.y + rhs.y * s * m.y,
        .z = lhs.z + rhs.z * s * m.z,
        .w = lhs.w + rhs.w * s * m.w
    };
}
#else
;
#endif
/// @brief Difference of two u16v with lhs scaled by u16 and multiplied with a u16
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16* SL_u16vsubSM_(u16* lhs, u16* rhs, u16 s, u16* m, u16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] - rhs[i] * s * m[i];
    return dest;
}
#else
;
#endif
/// @brief Difference of two u16v with lhs scaled by u16 and multiplied with a u16
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16v SL_u16vsubSM(u16v lhs, u16v rhs, u16 s, u16v m, u16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u16vsubSM_(lhs.data, rhs.data, s, m.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two u16v2 with lhs scaled by u16 and multiplied with a u16
SL_header u16v2 SL_u16v2subSM(u16v2 lhs, u16v2 rhs, u16 s, u16v2 m)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v2) {
        .x = lhs.x - rhs.x * s * m.x,
        .y = lhs.y - rhs.y * s * m.y
    };
}
#else
;
#endif
/// @brief Difference of two u16v3 with lhs scaled by u16 and multiplied with a u16
SL_header u16v3 SL_u16v3subSM(u16v3 lhs, u16v3 rhs, u16 s, u16v3 m)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v3) {
        .x = lhs.x - rhs.x * s * m.x,
        .y = lhs.y - rhs.y * s * m.y,
        .z = lhs.z - rhs.z * s * m.z
    };
}
#else
;
#endif
/// @brief Difference of two u16v4 with lhs scaled by u16 and multiplied with a u16
SL_header u16v4 SL_u16v4subSM(u16v4 lhs, u16v4 rhs, u16 s, u16v4 m)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v4) {
        .x = lhs.x - rhs.x * s * m.x,
        .y = lhs.y - rhs.y * s * m.y,
        .z = lhs.z - rhs.z * s * m.z,
        .w = lhs.w - rhs.w * s * m.w
    };
}
#else
;
#endif
/// @brief Addition of two u16v with rhs scaled by a u16
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16* SL_u16vSadd_(u16* lhs, u16 s, u16* rhs, u16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * s + rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Addition of two u16v with rhs scaled by a u16
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16v SL_u16vSadd(u16v lhs, u16 s, u16v rhs, u16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u16vSadd_(lhs.data, s, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two u16v2 with rhs scaled by a u16
SL_header u16v2 SL_u16v2Sadd(u16v2 lhs, u16 s, u16v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v2) {
        .x = lhs.x * s + rhs.x,
        .y = lhs.y * s + rhs.y
    };
}
#else
;
#endif
/// @brief Addition of two u16v3 with rhs scaled by a u16
SL_header u16v3 SL_u16v3Sadd(u16v3 lhs, u16 s, u16v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v3) {
        .x = lhs.x * s + rhs.x,
        .y = lhs.y * s + rhs.y,
        .z = lhs.z * s + rhs.z
    };
}
#else
;
#endif
/// @brief Addition of two u16v4 with rhs scaled by a u16
SL_header u16v4 SL_u16v4Sadd(u16v4 lhs, u16 s, u16v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v4) {
        .x = lhs.x * s + rhs.x,
        .y = lhs.y * s + rhs.y,
        .z = lhs.z * s + rhs.z,
        .w = lhs.w * s + rhs.w
    };
}
#else
;
#endif
/// @brief Difference of two u16v with rhs scaled by a u16
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16* SL_u16vSsub_(u16* lhs, u16 s, u16* rhs, u16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * s - rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Difference of two u16v with rhs scaled by a u16
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16v SL_u16vSsub(u16v lhs, u16 s, u16v rhs, u16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u16vSsub_(lhs.data, s, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two u16v2 with rhs scaled by a u16
SL_header u16v2 SL_u16v2Ssub(u16v2 lhs, u16 s, u16v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v2) {
        .x = lhs.x * s - rhs.x,
        .y = lhs.y * s - rhs.y
    };
}
#else
;
#endif
/// @brief Difference of two u16v3 with rhs scaled by a u16
SL_header u16v3 SL_u16v3Ssub(u16v3 lhs, u16 s, u16v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v3) {
        .x = lhs.x * s - rhs.x,
        .y = lhs.y * s - rhs.y,
        .z = lhs.z * s - rhs.z
    };
}
#else
;
#endif
/// @brief Difference of two u16v4 with rhs scaled by a u16
SL_header u16v4 SL_u16v4Ssub(u16v4 lhs, u16 s, u16v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v4) {
        .x = lhs.x * s - rhs.x,
        .y = lhs.y * s - rhs.y,
        .z = lhs.z * s - rhs.z,
        .w = lhs.w * s - rhs.w
    };
}
#else
;
#endif
/// @brief Weighted sum of two u16v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16* SL_u16vmix_(u16* lhs, u16 lhs_w, u16* rhs, u16 rhs_w, u16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * lhs_w + rhs[i] * rhs_w;
    return dest;
}
#else
;
#endif
/// @brief Weighted sum of two u16v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16v SL_u16vmix(u16v lhs, u16 lhs_w, u16v rhs, u16 rhs_w, u16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u16vmix_(lhs.data, lhs_w, rhs.data, rhs_w, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Weighted sum of two u16v2
SL_header u16v2 SL_u16v2mix(u16v2 lhs, u16 lhs_w, u16v2 rhs, u16 rhs_w)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v2) {
        .x = lhs.x * lhs_w + rhs.x * rhs_w,
        .y = lhs.y * lhs_w + rhs.y * rhs_w
    };
}
#else
;
#endif
/// @brief Weighted sum of two u16v3
SL_header u16v3 SL_u16v3mix(u16v3 lhs, u16 lhs_w, u16v3 rhs, u16 rhs_w)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v3) {
        .x = lhs.x * lhs_w + rhs.x * rhs_w,
        .y = lhs.y * lhs_w + rhs.y * rhs_w,
        .z = lhs.z * lhs_w + rhs.z * rhs_w
    };
}
#else
;
#endif
/// @brief Weighted sum of two u16v4
SL_header u16v4 SL_u16v4mix(u16v4 lhs, u16 lhs_w, u16v4 rhs, u16 rhs_w)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v4) {
        .x = lhs.x * lhs_w + rhs.x * rhs_w,
        .y = lhs.y * lhs_w + rhs.y * rhs_w,
        .z = lhs.z * lhs_w + rhs.z * rhs_w,
        .w = lhs.w * lhs_w + rhs.w * rhs_w
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two u16v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16* SL_u16vmin_(u16* lhs, u16* rhs, u16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] < rhs[i] ? lhs[i] : rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise minimum of two u16v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16v SL_u16vmin(u16v lhs, u16v rhs, u16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u16vmin_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise minimum of two u16v2
SL_header u16v2 SL_u16v2min(u16v2 lhs, u16v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v2) {
        .x = lhs.x < rhs.x ? lhs.x : rhs.x,
        .y = lhs.y < rhs.y ? lhs.y : rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two u16v3
SL_header u16v3 SL_u16v3min(u16v3 lhs, u16v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v3) {
        .x = lhs.x < rhs.x ? lhs.x : rhs.x,
        .y = lhs.y < rhs.y ? lhs.y : rhs.y,
        .z = lhs.z < rhs.z ? lhs.z : rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two u16v4
SL_header u16v4 SL_u16v4min(u16v4 lhs, u16v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v4) {
        .x = lhs.x < rhs.x ? lhs.x : rhs.x,
        .y = lhs.y < rhs.y ? lhs.y : rhs.y,
        .z = lhs.z < rhs.z ? lhs.z : rhs.z,
        .w = lhs.w < rhs.w ? lhs.w : rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two u16v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16* SL_u16vmax_(u16* lhs, u16* rhs, u16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] > rhs[i] ? lhs[i] : rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise maximum of two u16v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16v SL_u16vmax(u16v lhs, u16v rhs, u16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u16vmax_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise maximum of two u16v2
SL_header u16v2 SL_u16v2max(u16v2 lhs, u16v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v2) {
        .x = lhs.x > rhs.x ? lhs.x : rhs.x,
        .y = lhs.y > rhs.y ? lhs.y : rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two u16v3
SL_header u16v3 SL_u16v3max(u16v3 lhs, u16v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v3) {
        .x = lhs.x > rhs.x ? lhs.x : rhs.x,
        .y = lhs.y > rhs.y ? lhs.y : rhs.y,
        .z = lhs.z > rhs.z ? lhs.z : rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two u16v4
SL_header u16v4 SL_u16v4max(u16v4 lhs, u16v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v4) {
        .x = lhs.x > rhs.x ? lhs.x : rhs.x,
        .y = lhs.y > rhs.y ? lhs.y : rhs.y,
        .z = lhs.z > rhs.z ? lhs.z : rhs.z,
        .w = lhs.w > rhs.w ? lhs.w : rhs.w
    };
}
#else
;
#endif
/// @brief Dot product of two u16v
/// @note All vectors are assumed to be of size 'count'
SL_header u64 SL_u16vdot_(u16* lhs, u16* rhs, usize count)
#if defined(SL_IMPLEMENTATION)
{
    u64 dest = 0;
    for (usize i = 0; i < count; ++i) dest += lhs[i] * rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Dot product of two u16v
/// @note All vectors are assumed to be of size 'count'
SL_header u64 SL_u16vdot(u16v lhs, u16v rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u16vdot_(lhs.data, rhs.data, lhs.count);
}
#else
;
#endif
/// @brief Dot product of two u16v2
SL_header u64 SL_u16v2dot(u16v2 lhs, u16v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}
#else
;
#endif
/// @brief Dot product of two u16v3
SL_header u64 SL_u16v3dot(u16v3 lhs, u16v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}
#else
;
#endif
/// @brief Dot product of two u16v4
SL_header u64 SL_u16v4dot(u16v4 lhs, u16v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}
#else
;
#endif
/// @brief Maximum component of a u16v
/// @note All vectors are assumed to be of size 'count'
SL_header u64 SL_u16vlen_max_(u16* v, usize count)
#if defined(SL_IMPLEMENTATION)
{
    u64 dest = 0;
    for (usize i = 0; i < count; ++i) dest = v[i] > dest ? v[i] : dest;
    return dest;
}
#else
;
#endif
/// @brief Maximum component of a u16v
/// @note All vectors are assumed to be of size 'count'
SL_header u64 SL_u16vlen_max(u16v v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u16vlen_max_(v.data, v.count);
}
#else
;
#endif
/// @brief Maximum component of a u16v2
SL_header u64 SL_u16v2len_max(u16v2 v)
#if defined(SL_IMPLEMENTATION)
{
    return v.x > v.y ? v.x : v.y;
}
#else
;
#endif
/// @brief Maximum component of a u16v3
SL_header u64 SL_u16v3len_max(u16v3 v)
#if defined(SL_IMPLEMENTATION)
{
    return v.x > v.y ? (v.x > v.z ? v.x : v.z) : (v.y > v.z ? v.y : v.z);
}
#else
;
#endif
/// @brief Maximum component of a u16v4
SL_header u64 SL_u16v4len_max(u16v4 v)
#if defined(SL_IMPLEMENTATION)
{
    return v.x > v.y ? (v.x > v.z ? (v.x > v.w ? v.x : v.w) : (v.z > v.w ? v.z : v.w)) : (v.y > v.z ? (v.y > v.w ? v.y : v.w) : (v.z > v.w ? v.z : v.w));
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a u16v
/// @note All vectors are assumed to be of size 'count'
SL_header u64 SL_u16vlen_manh_(u16* v, usize count)
#if defined(SL_IMPLEMENTATION)
{
    u64 dest = 0;
    for (usize i = 0; i < count; ++i) dest += v[i];
    return dest;
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a u16v
/// @note All vectors are assumed to be of size 'count'
SL_header u64 SL_u16vlen_manh(u16v v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u16vlen_manh_(v.data, v.count);
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a u16v2
SL_header u64 SL_u16v2len_manh(u16v2 v)
#if defined(SL_IMPLEMENTATION)
{
    return v.x + v.y;
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a u16v3
SL_header u64 SL_u16v3len_manh(u16v3 v)
#if defined(SL_IMPLEMENTATION)
{
    return v.x + v.y + v.z;
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a u16v4
SL_header u64 SL_u16v4len_manh(u16v4 v)
#if defined(SL_IMPLEMENTATION)
{
    return v.x + v.y + v.z + v.w;
}
#else
;
#endif
/// @brief Squared euclidean length of a u16v
/// @note All vectors are assumed to be of size 'count'
SL_header u64 SL_u16vlen_srq_(u16* v, usize count)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u16vdot_(v, v, count);
}
#else
;
#endif
/// @brief Squared euclidean length of a u16v
/// @note All vectors are assumed to be of size 'count'
SL_header u64 SL_u16vlen_srq(u16v v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u16vlen_srq_(v.data, v.count);
}
#else
;
#endif
/// @brief Square length of a u16v2
SL_header u64 SL_u16v2len_sqr(u16v2 v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u16v2dot(v, v);
}
#else
;
#endif
/// @brief Square length of a u16v3
SL_header u64 SL_u16v3len_sqr(u16v3 v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u16v3dot(v, v);
}
#else
;
#endif
/// @brief Square length of a u16v4
SL_header u64 SL_u16v4len_sqr(u16v4 v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u16v4dot(v, v);
}
#else
;
#endif
/// @brief Euclidean length of a u16v
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_u16vlen_(u16* v, usize count)
#if defined(SL_IMPLEMENTATION)
{
    return sqrt(SL_u16vdot_(v, v, count));
}
#else
;
#endif
/// @brief Euclidean length of a u16v
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_u16vlen(u16v v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u16vlen_(v.data, v.count);
}
#else
;
#endif
/// @brief Euclidean length of a u16v2
SL_header double SL_u16v2len(u16v2 v)
#if defined(SL_IMPLEMENTATION)
{
    return sqrt(SL_u16v2dot(v, v));
}
#else
;
#endif
/// @brief Euclidean length of a u16v3
SL_header double SL_u16v3len(u16v3 v)
#if defined(SL_IMPLEMENTATION)
{
    return sqrt(SL_u16v3dot(v, v));
}
#else
;
#endif
/// @brief Euclidean length of a u16v4
SL_header double SL_u16v4len(u16v4 v)
#if defined(SL_IMPLEMENTATION)
{
    return sqrt(SL_u16v4dot(v, v));
}
#else
;
#endif
/// @brief Euclidean distance bewteen two u16v
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_u16vdist_(u16* lhs, u16* rhs, usize count)
#if defined(SL_IMPLEMENTATION)
{
    double accum = 0;
    for (int i = 0; i < count; ++i) accum += (lhs[i] - rhs[i]) * (lhs[i] - rhs[i]);
    return sqrt(accum);
}
#else
;
#endif
/// @brief Euclidean distance bewteen two u16v
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_u16vdist(u16v lhs, u16v rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u16vdist_(lhs.data, rhs.data, lhs.count);
}
#else
;
#endif
/// @brief Euclidean distance between two u16v2
SL_header double SL_u16v2dist(u16v2 lhs, u16v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u16v2len(SL_u16v2sub(lhs, rhs));
}
#else
;
#endif
/// @brief Euclidean distance between two u16v3
SL_header double SL_u16v3dist(u16v3 lhs, u16v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u16v3len(SL_u16v3sub(lhs, rhs));
}
#else
;
#endif
/// @brief Euclidean distance between two u16v4
SL_header double SL_u16v4dist(u16v4 lhs, u16v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u16v4len(SL_u16v4sub(lhs, rhs));
}
#else
;
#endif
/// @brief Reflection of u16v2 v around vector u16v2 n
SL_header u16v2 SL_u16v2refl(u16v2 v, u16v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u16v2subS(v, n, 2.0 * SL_u16v2dot(v, n) / SL_u16v2dot(n, n));
}
#else
;
#endif
/// @brief Reflection of u16v3 v around vector u16v3 n
SL_header u16v3 SL_u16v3refl(u16v3 v, u16v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u16v3subS(v, n, 2.0 * SL_u16v3dot(v, n) / SL_u16v3dot(n, n));
}
#else
;
#endif
/// @brief Reflection of u16v4 v around vector u16v4 n
SL_header u16v4 SL_u16v4refl(u16v4 v, u16v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u16v4subS(v, n, 2.0 * SL_u16v4dot(v, n) / SL_u16v4dot(n, n));
}
#else
;
#endif
/// @brief Reflection of u16v2 v around vector u16v2 n assumed to be of unit length
SL_header u16v2 SL_u16v2refl_u(u16v2 v, u16v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u16v2subS(v, n, 2.0 * SL_u16v2dot(v, n));
}
#else
;
#endif
/// @brief Reflection of u16v3 v around vector u16v3 n assumed to be of unit length
SL_header u16v3 SL_u16v3refl_u(u16v3 v, u16v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u16v3subS(v, n, 2.0 * SL_u16v3dot(v, n));
}
#else
;
#endif
/// @brief Reflection of u16v4 v around vector u16v4 n assumed to be of unit length
SL_header u16v4 SL_u16v4refl_u(u16v4 v, u16v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u16v4subS(v, n, 2.0 * SL_u16v4dot(v, n));
}
#else
;
#endif
/// @brief Get component of u16v2 v in direction u16v2 n
SL_header u16v2 SL_u16v2align(u16v2 v, u16v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u16v2muls(n, SL_u16v2dot(v, n) / SL_u16v2dot(n, n));
}
#else
;
#endif
/// @brief Get component of u16v3 v in direction u16v3 n
SL_header u16v3 SL_u16v3align(u16v3 v, u16v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u16v3muls(n, SL_u16v3dot(v, n) / SL_u16v3dot(n, n));
}
#else
;
#endif
/// @brief Get component of u16v4 v in direction u16v4 n
SL_header u16v4 SL_u16v4align(u16v4 v, u16v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u16v4muls(n, SL_u16v4dot(v, n) / SL_u16v4dot(n, n));
}
#else
;
#endif
/// @brief Get component of u16v2 v in direction u16v2 n assumed to be of unit length
SL_header u16v2 SL_u16v2align_u(u16v2 v, u16v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u16v2muls(n, SL_u16v2dot(v, n));
}
#else
;
#endif
/// @brief Get component of u16v3 v in direction u16v3 n assumed to be of unit length
SL_header u16v3 SL_u16v3align_u(u16v3 v, u16v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u16v3muls(n, SL_u16v3dot(v, n));
}
#else
;
#endif
/// @brief Get component of u16v4 v in direction u16v4 n assumed to be of unit length
SL_header u16v4 SL_u16v4align_u(u16v4 v, u16v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u16v4muls(n, SL_u16v4dot(v, n));
}
#else
;
#endif
/// @brief Project u16v2 v on plane with normal u16v2 n
SL_header u16v2 SL_u16v2proj(u16v2 v, u16v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u16v2sub(v, SL_u16v2align(v, n));
}
#else
;
#endif
/// @brief Project u16v3 v on plane with normal u16v3 n
SL_header u16v3 SL_u16v3proj(u16v3 v, u16v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u16v3sub(v, SL_u16v3align(v, n));
}
#else
;
#endif
/// @brief Project u16v4 v on plane with normal u16v4 n
SL_header u16v4 SL_u16v4proj(u16v4 v, u16v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u16v4sub(v, SL_u16v4align(v, n));
}
#else
;
#endif
/// @brief Project u16v2 v on plane with normal u16v2 n
SL_header u16v2 SL_u16v2proj_u(u16v2 v, u16v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u16v2sub(v, SL_u16v2align_u(v, n));
}
#else
;
#endif
/// @brief Project u16v3 v on plane with normal u16v3 n
SL_header u16v3 SL_u16v3proj_u(u16v3 v, u16v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u16v3sub(v, SL_u16v3align_u(v, n));
}
#else
;
#endif
/// @brief Project u16v4 v on plane with normal u16v4 n
SL_header u16v4 SL_u16v4proj_u(u16v4 v, u16v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u16v4sub(v, SL_u16v4align_u(v, n));
}
#else
;
#endif
/// @brief Component-wise modulo of a u16v by scalar n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16* SL_u16vmods_(u16* v, u16 n, u16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = v[i] % n;
    return dest;
}
#else
;
#endif
/// @brief Component-wise modulo of a u16v by scalar n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16v SL_u16vmods(u16v v, u16 n, u16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u16vmods_(v.data, n, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise modulo of a u16v2 by scalar n
SL_header u16v2 SL_u16v2mods(u16v2 v, u16 n)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v2) {
        .x = v.x % n,
        .y = v.y % n
    };
}
#else
;
#endif
/// @brief Component-wise modulo of a u16v3 by scalar n
SL_header u16v3 SL_u16v3mods(u16v3 v, u16 n)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v3) {
        .x = v.x % n,
        .y = v.y % n,
        .z = v.z % n
    };
}
#else
;
#endif
/// @brief Component-wise modulo of a u16v4 by scalar n
SL_header u16v4 SL_u16v4mods(u16v4 v, u16 n)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v4) {
        .x = v.x % n,
        .y = v.y % n,
        .z = v.z % n,
        .w = v.w % n
    };
}
#else
;
#endif
/// @brief Component-wise modulo of a u16v by u16v n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16* SL_u16vmod_(u16* v, u16* n, u16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = v[i] % n[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise modulo of a u16v by u16v n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16v SL_u16vmod(u16v v, u16v n, u16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u16vmod_(v.data, n.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise modulo of a u16v2 by u16v2 n
SL_header u16v2 SL_u16v2mod(u16v2 v, u16v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v2) {
        .x = v.x % n.x,
        .y = v.y % n.y
    };
}
#else
;
#endif
/// @brief Component-wise modulo of a u16v3 by u16v3 n
SL_header u16v3 SL_u16v3mod(u16v3 v, u16v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v3) {
        .x = v.x % n.x,
        .y = v.y % n.y,
        .z = v.z % n.z
    };
}
#else
;
#endif
/// @brief Component-wise modulo of a u16v4 by u16v4 n
SL_header u16v4 SL_u16v4mod(u16v4 v, u16v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v4) {
        .x = v.x % n.x,
        .y = v.y % n.y,
        .z = v.z % n.z,
        .w = v.w % n.w
    };
}
#else
;
#endif
/// @brief Component-wise binary AND of two u16v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16* SL_u16vand_(u16* lhs, u16* rhs, u16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] & rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary AND of two u16v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16v SL_u16vand(u16v lhs, u16v rhs, u16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u16vand_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary AND of two u16v2
SL_header u16v2 SL_u16v2and(u16v2 lhs, u16v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v2) {
        .x = lhs.x & rhs.x,
        .y = lhs.y & rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise binary AND of two u16v3
SL_header u16v3 SL_u16v3and(u16v3 lhs, u16v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v3) {
        .x = lhs.x & rhs.x,
        .y = lhs.y & rhs.y,
        .z = lhs.z & rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise binary AND of two u16v4
SL_header u16v4 SL_u16v4and(u16v4 lhs, u16v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v4) {
        .x = lhs.x & rhs.x,
        .y = lhs.y & rhs.y,
        .z = lhs.z & rhs.z,
        .w = lhs.w & rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise binary OR of two u16v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16* SL_u16vor_(u16* lhs, u16* rhs, u16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] | rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary OR of two u16v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16v SL_u16vor(u16v lhs, u16v rhs, u16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u16vor_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary OR of two u16v2
SL_header u16v2 SL_u16v2or(u16v2 lhs, u16v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v2) {
        .x = lhs.x | rhs.x,
        .y = lhs.y | rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise binary OR of two u16v3
SL_header u16v3 SL_u16v3or(u16v3 lhs, u16v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v3) {
        .x = lhs.x | rhs.x,
        .y = lhs.y | rhs.y,
        .z = lhs.z | rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise binary OR of two u16v4
SL_header u16v4 SL_u16v4or(u16v4 lhs, u16v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v4) {
        .x = lhs.x | rhs.x,
        .y = lhs.y | rhs.y,
        .z = lhs.z | rhs.z,
        .w = lhs.w | rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise binary XOR of two u16v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16* SL_u16vxor_(u16* lhs, u16* rhs, u16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] ^ rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary XOR of two u16v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16v SL_u16vxor(u16v lhs, u16v rhs, u16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u16vxor_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary XOR of two u16v2
SL_header u16v2 SL_u16v2xor(u16v2 lhs, u16v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v2) {
        .x = lhs.x ^ rhs.x,
        .y = lhs.y ^ rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise binary XOR of two u16v3
SL_header u16v3 SL_u16v3xor(u16v3 lhs, u16v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v3) {
        .x = lhs.x ^ rhs.x,
        .y = lhs.y ^ rhs.y,
        .z = lhs.z ^ rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise binary XOR of two u16v4
SL_header u16v4 SL_u16v4xor(u16v4 lhs, u16v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v4) {
        .x = lhs.x ^ rhs.x,
        .y = lhs.y ^ rhs.y,
        .z = lhs.z ^ rhs.z,
        .w = lhs.w ^ rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise binary NOT of a u16v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16* SL_u16vnot_(u16* v, u16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = ~v[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary NOT of a u16v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16v SL_u16vnot(u16v v, u16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u16vnot_(v.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary NOT of a u16v2
SL_header u16v2 SL_u16v2not(u16v2 v)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v2) {
        .x = ~v.x,
        .y = ~v.y
    };
}
#else
;
#endif
/// @brief Component-wise binary NOT of a u16v3
SL_header u16v3 SL_u16v3not(u16v3 v)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v3) {
        .x = ~v.x,
        .y = ~v.y,
        .z = ~v.z
    };
}
#else
;
#endif
/// @brief Component-wise binary NOT of a u16v4
SL_header u16v4 SL_u16v4not(u16v4 v)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v4) {
        .x = ~v.x,
        .y = ~v.y,
        .z = ~v.z,
        .w = ~v.w
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a u16v by integer n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16* SL_u16vlshfts_(u16* lhs, u16 rhs, u16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] << rhs;
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a u16v by integer n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16v SL_u16vlshfts(u16v lhs, u16 rhs, u16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u16vlshfts_(lhs.data, rhs, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a u16v2 by integer n
SL_header u16v2 SL_u16v2lshfts(u16v2 lhs, u16 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v2) {
        .x = lhs.x << rhs,
        .y = lhs.y << rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a u16v3 by integer n
SL_header u16v3 SL_u16v3lshfts(u16v3 lhs, u16 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v3) {
        .x = lhs.x << rhs,
        .y = lhs.y << rhs,
        .z = lhs.z << rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a u16v4 by integer n
SL_header u16v4 SL_u16v4lshfts(u16v4 lhs, u16 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v4) {
        .x = lhs.x << rhs,
        .y = lhs.y << rhs,
        .z = lhs.z << rhs,
        .w = lhs.w << rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a u16v by u16v n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16* SL_u16vlshft_(u16* lhs, u16* rhs, u16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] << rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a u16v by u16v n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16v SL_u16vlshft(u16v lhs, u16v rhs, u16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u16vlshft_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a u16v2 by u16v2 n
SL_header u16v2 SL_u16v2lshft(u16v2 lhs, u16v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v2) {
        .x = lhs.x << rhs.x,
        .y = lhs.y << rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a u16v3 by u16v3 n
SL_header u16v3 SL_u16v3lshft(u16v3 lhs, u16v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v3) {
        .x = lhs.x << rhs.x,
        .y = lhs.y << rhs.y,
        .z = lhs.z << rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a u16v4 by u16v4 n
SL_header u16v4 SL_u16v4lshft(u16v4 lhs, u16v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v4) {
        .x = lhs.x << rhs.x,
        .y = lhs.y << rhs.y,
        .z = lhs.z << rhs.z,
        .w = lhs.w << rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a u16v by interger n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16* SL_u16vrshfts_(u16* lhs, u16 rhs, u16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] >> rhs;
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a u16v by interger n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16v SL_u16vrshfts(u16v lhs, u16 rhs, u16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u16vrshfts_(lhs.data, rhs, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a u16v2 by interger n
SL_header u16v2 SL_u16v2rshfts(u16v2 lhs, u16 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v2) {
        .x = lhs.x >> rhs,
        .y = lhs.y >> rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a u16v3 by interger n
SL_header u16v3 SL_u16v3rshfts(u16v3 lhs, u16 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v3) {
        .x = lhs.x >> rhs,
        .y = lhs.y >> rhs,
        .z = lhs.z >> rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a u16v4 by interger n
SL_header u16v4 SL_u16v4rshfts(u16v4 lhs, u16 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v4) {
        .x = lhs.x >> rhs,
        .y = lhs.y >> rhs,
        .z = lhs.z >> rhs,
        .w = lhs.w >> rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a u16v by u16v n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16* SL_u16vrshft_(u16* lhs, u16* rhs, u16* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] >> rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a u16v by u16v n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u16v SL_u16vrshft(u16v lhs, u16v rhs, u16v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u16vrshft_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a u16v2 by u16v2 n
SL_header u16v2 SL_u16v2rshft(u16v2 lhs, u16v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v2) {
        .x = lhs.x >> rhs.x,
        .y = lhs.y >> rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a u16v3 by u16v3 n
SL_header u16v3 SL_u16v3rshft(u16v3 lhs, u16v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v3) {
        .x = lhs.x >> rhs.x,
        .y = lhs.y >> rhs.y,
        .z = lhs.z >> rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a u16v4 by u16v4 n
SL_header u16v4 SL_u16v4rshft(u16v4 lhs, u16v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u16v4) {
        .x = lhs.x >> rhs.x,
        .y = lhs.y >> rhs.y,
        .z = lhs.z >> rhs.z,
        .w = lhs.w >> rhs.w
    };
}
#else
;
#endif
#pragma endregion U16
#pragma region U32

/// @brief Vector of u32 with arbitrary dimension
typedef struct {
    const usize count;
    u32 *data;
} u32v;

/// @brief Vector of u32 with dimension 2
typedef union {
    u32 data[2];
    struct {
        union { u32 x, r, u; };
        union { u32 y, g, v; };
    };
} u32v2;

#define SL_u32v2_zero  ((u32v2){.x =  0, .y =  0})
#define SL_u32v2_one   ((u32v2){.x =  1, .y =  1})
#define SL_u32v2_right ((u32v2){.x =  1, .y =  0})
#define SL_u32v2_up    ((u32v2){.x =  0, .y =  1})

/// @brief Vector of u32 with dimension 3
typedef union {
    u32 data[3];
    struct {
        union { u32 x, r, u; };
        union { u32 y, g, v; };
        union { u32 z, b, s; };
    };
    struct {
        union { u32 __x, __r, __u; };
        union { u32v2 yz, gb, vs; };
    };
    struct {
        union { u32v2 xy, rg, uv; };
        union { u32 __z, __b, __s; };
    };
} u32v3;

#define SL_u32v3_zero  ((u32v3){.x =  0, .y =  0, .z =  0})
#define SL_u32v3_one   ((u32v3){.x =  1, .y =  1, .z =  1})
#define SL_u32v3_right ((u32v3){.x =  1, .y =  0, .z =  0})
#define SL_u32v3_up    ((u32v3){.x =  0, .y =  1, .z =  0})
#define SL_u32v3_forw  ((u32v3){.x =  0, .y =  0, .z =  1})

/// @brief Vector of u32 with dimension 4
typedef union {
    u32 data[4];
    struct {
        union { u32 x, r, u; };
        union { u32 y, g, v; };
        union { u32 z, b, s; };
        union { u32 w, a, t; };
    };
    struct {
        union { u32 __x0, __r0, __u0; };
        union { u32v2 yz, gb, vs; };
        union { u32 __w0, __a0, __t0; };
    };
    struct {
        union { u32v2 xy, rb, uv; };
        union { u32v2 zw, ba, st; };
    };
    struct {
        union { u32v3 xyz, rgb, uvs; };
        union { u32 __w1, __a1, __t1; };
    };
    struct {
        union { u32 __x1, __r1, __u1; };
        union { u32v3 yzw, gba, vst; };
    };
} u32v4;

#define SL_u32v4_zero  ((u32v4){.x = 0, .y = 0, .z = 0, .w = 0})
#define SL_u32v4_one   ((u32v4){.x = 1, .y = 1, .z = 1, .w = 1})

#define SL_u32v4_white  ((u32v4){.x = 1, .y = 1, .z = 1, .w = 1})
#define SL_u32v4_black  ((u32v4){.x = 0, .y = 0, .z = 0, .w = 1})
#define SL_u32v4_red    ((u32v4){.x = 1, .y = 0, .z = 0, .w = 1})
#define SL_u32v4_green  ((u32v4){.x = 0, .y = 1, .z = 0, .w = 1})
#define SL_u32v4_blue   ((u32v4){.x = 0, .y = 0, .z = 1, .w = 1})
#define SL_u32v4_yellow ((u32v4){.x = 1, .y = 1, .z = 0, .w = 1})
#define SL_u32v4_cyan   ((u32v4){.x = 0, .y = 1, .z = 1, .w = 1})
#define SL_u32v4_purple ((u32v4){.x = 1, .y = 0, .z = 1, .w = 1})



#define SL_u32v2_(X, Y)       ((u32v2){.x = X, .y = Y})
#define SL_u32v3_(X, Y, Z)    ((u32v3){.x = X, .y = Y, .z = Z})
#define SL_u32v4_(X, Y, Z, W) ((u32v4){.x = X, .y = Y, .z = Z, .w = W})

#define SL_u32v2s(S)          ((u32v2){.x = S, .y = S})
#define SL_u32v3s(S)          ((u32v3){.x = S, .y = S, .z = S})
#define SL_u32v4s(S)          ((u32v4){.x = S, .y = S, .z = S, .w = S})

#define SL_u32vv(V)           ((u32v){.count = vsize(V), .data = (V).data})
#define SL_u32v2v(V, ...)     ((u32v2){.x = (V).x, .y = (V).y})
#define SL_u32v3v(V, ...)     ((u32v3){.x = (V).x, .y = (V).y, .z = (SL_vsize(V) >= 3 ? (V).data[2] : (0, ##__VA_ARGS__))})
#define SL_u32v4v(V, ...)     ((u32v4){.x = (V).x, .y = (V).y, .z = (SL_vsize(V) >= 3 ? (V).data[2] : ((const float[]){0, ##__VA_ARGS__, 0})[1]), .w = (SL_vsize(V) >= 4 ? (V).data[3] : ((const float[]){0, ##__VA_ARGS__, 0, 0})[2])})



/// @brief Equality of two u32v
/// @note All vectors are assumed to be of size 'count'
SL_header bool SL_u32vequ_(u32* lhs, u32* rhs, usize count)
#if defined(SL_IMPLEMENTATION)
{
    bool dest = true;
    for (usize i = 0; i < count; ++i) dest &= lhs[i] == rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Equality of two u32v
/// @note All vectors are assumed to be of size 'count'
SL_header bool SL_u32vequ(u32v lhs, u32v rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u32vequ_(lhs.data, rhs.data, lhs.count);
}
#else
;
#endif
/// @brief Equality of two u32v2
SL_header bool SL_u32v2equ(u32v2 lhs, u32v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}
#else
;
#endif
/// @brief Equality of two u32v3
SL_header bool SL_u32v3equ(u32v3 lhs, u32v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}
#else
;
#endif
/// @brief Equality of two u32v4
SL_header bool SL_u32v4equ(u32v4 lhs, u32v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
}
#else
;
#endif
/// @brief Addition of two u32v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32* SL_u32vadd_(u32* lhs, u32* rhs, u32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] + rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Addition of two u32v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32v SL_u32vadd(u32v lhs, u32v rhs, u32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u32vadd_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two u32v2
SL_header u32v2 SL_u32v2add(u32v2 lhs, u32v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v2) {
        .x = lhs.x + rhs.x,
        .y = lhs.y + rhs.y
    };
}
#else
;
#endif
/// @brief Addition of two u32v3
SL_header u32v3 SL_u32v3add(u32v3 lhs, u32v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v3) {
        .x = lhs.x + rhs.x,
        .y = lhs.y + rhs.y,
        .z = lhs.z + rhs.z
    };
}
#else
;
#endif
/// @brief Addition of two u32v4
SL_header u32v4 SL_u32v4add(u32v4 lhs, u32v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v4) {
        .x = lhs.x + rhs.x,
        .y = lhs.y + rhs.y,
        .z = lhs.z + rhs.z,
        .w = lhs.w + rhs.w
    };
}
#else
;
#endif
/// @brief Difference of two u32v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32* SL_u32vsub_(u32* lhs, u32* rhs, u32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] - rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Difference of two u32v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32v SL_u32vsub(u32v lhs, u32v rhs, u32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u32vsub_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two u32v2
SL_header u32v2 SL_u32v2sub(u32v2 lhs, u32v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v2) {
        .x = lhs.x - rhs.x,
        .y = lhs.y - rhs.y
    };
}
#else
;
#endif
/// @brief Difference of two u32v3
SL_header u32v3 SL_u32v3sub(u32v3 lhs, u32v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v3) {
        .x = lhs.x - rhs.x,
        .y = lhs.y - rhs.y,
        .z = lhs.z - rhs.z
    };
}
#else
;
#endif
/// @brief Difference of two u32v4
SL_header u32v4 SL_u32v4sub(u32v4 lhs, u32v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v4) {
        .x = lhs.x - rhs.x,
        .y = lhs.y - rhs.y,
        .z = lhs.z - rhs.z,
        .w = lhs.w - rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of two u32v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32* SL_u32vmul_(u32* lhs, u32* rhs, u32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise multiplication of two u32v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32v SL_u32vmul(u32v lhs, u32v rhs, u32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u32vmul_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise multiplication of two u32v2
SL_header u32v2 SL_u32v2mul(u32v2 lhs, u32v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v2) {
        .x = lhs.x * rhs.x,
        .y = lhs.y * rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of two u32v3
SL_header u32v3 SL_u32v3mul(u32v3 lhs, u32v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v3) {
        .x = lhs.x * rhs.x,
        .y = lhs.y * rhs.y,
        .z = lhs.z * rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of two u32v4
SL_header u32v4 SL_u32v4mul(u32v4 lhs, u32v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v4) {
        .x = lhs.x * rhs.x,
        .y = lhs.y * rhs.y,
        .z = lhs.z * rhs.z,
        .w = lhs.w * rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of a u32v with a scalar
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32* SL_u32vmuls_(u32* lhs, u32 rhs, u32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * rhs;
    return dest;
}
#else
;
#endif
/// @brief Component-wise multiplication of a u32v with a scalar
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32v SL_u32vmuls(u32v lhs, u32 rhs, u32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u32vmuls_(lhs.data, rhs, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise multiplication of a u32v2 with a scalar
SL_header u32v2 SL_u32v2muls(u32v2 lhs, u32 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v2) {
        .x = lhs.x * rhs,
        .y = lhs.y * rhs
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of a u32v3 with a scalar
SL_header u32v3 SL_u32v3muls(u32v3 lhs, u32 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v3) {
        .x = lhs.x * rhs,
        .y = lhs.y * rhs,
        .z = lhs.z * rhs
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of a u32v4 with a scalar
SL_header u32v4 SL_u32v4muls(u32v4 lhs, u32 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v4) {
        .x = lhs.x * rhs,
        .y = lhs.y * rhs,
        .z = lhs.z * rhs,
        .w = lhs.w * rhs
    };
}
#else
;
#endif
/// @brief Component-wise division of two u32v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32* SL_u32vdiv_(u32* lhs, u32* rhs, u32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] / rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise division of two u32v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32v SL_u32vdiv(u32v lhs, u32v rhs, u32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u32vdiv_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise division of two u32v2
SL_header u32v2 SL_u32v2div(u32v2 lhs, u32v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v2) {
        .x = lhs.x / rhs.x,
        .y = lhs.y / rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise division of two u32v3
SL_header u32v3 SL_u32v3div(u32v3 lhs, u32v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v3) {
        .x = lhs.x / rhs.x,
        .y = lhs.y / rhs.y,
        .z = lhs.z / rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise division of two u32v4
SL_header u32v4 SL_u32v4div(u32v4 lhs, u32v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v4) {
        .x = lhs.x / rhs.x,
        .y = lhs.y / rhs.y,
        .z = lhs.z / rhs.z,
        .w = lhs.w / rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise division of a u32v with a scalar
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32* SL_u32vdivs_(u32* lhs, u32 rhs, u32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] / rhs;
    return dest;
}
#else
;
#endif
/// @brief Component-wise division of a u32v with a scalar
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32v SL_u32vdivs(u32v lhs, u32 rhs, u32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u32vdivs_(lhs.data, rhs, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise division of a u32v2 with a scalar
SL_header u32v2 SL_u32v2divs(u32v2 lhs, u32 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v2) {
        .x = lhs.x / rhs,
        .y = lhs.y / rhs
    };
}
#else
;
#endif
/// @brief Component-wise division of a u32v3 with a scalar
SL_header u32v3 SL_u32v3divs(u32v3 lhs, u32 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v3) {
        .x = lhs.x / rhs,
        .y = lhs.y / rhs,
        .z = lhs.z / rhs
    };
}
#else
;
#endif
/// @brief Component-wise division of a u32v4 with a scalar
SL_header u32v4 SL_u32v4divs(u32v4 lhs, u32 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v4) {
        .x = lhs.x / rhs,
        .y = lhs.y / rhs,
        .z = lhs.z / rhs,
        .w = lhs.w / rhs
    };
}
#else
;
#endif
/// @brief Addition of two u32v with lhs scaled by a u32
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32* SL_u32vaddS_(u32* lhs, u32* rhs, u32 s, u32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] + rhs[i] * s;
    return dest;
}
#else
;
#endif
/// @brief Addition of two u32v with lhs scaled by a u32
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32v SL_u32vaddS(u32v lhs, u32v rhs, u32 s, u32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u32vaddS_(lhs.data, rhs.data, s, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two u32v2 with lhs scaled by a u32
SL_header u32v2 SL_u32v2addS(u32v2 lhs, u32v2 rhs, u32 s)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v2) {
        .x = lhs.x + rhs.x * s,
        .y = lhs.y + rhs.y * s
    };
}
#else
;
#endif
/// @brief Addition of two u32v3 with lhs scaled by a u32
SL_header u32v3 SL_u32v3addS(u32v3 lhs, u32v3 rhs, u32 s)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v3) {
        .x = lhs.x + rhs.x * s,
        .y = lhs.y + rhs.y * s,
        .z = lhs.z + rhs.z * s
    };
}
#else
;
#endif
/// @brief Addition of two u32v4 with lhs scaled by a u32
SL_header u32v4 SL_u32v4addS(u32v4 lhs, u32v4 rhs, u32 s)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v4) {
        .x = lhs.x + rhs.x * s,
        .y = lhs.y + rhs.y * s,
        .z = lhs.z + rhs.z * s,
        .w = lhs.w + rhs.w * s
    };
}
#else
;
#endif
/// @brief Difference of two u32v with lhs scaled by a u32
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32* SL_u32vsubS_(u32* lhs, u32* rhs, u32 s, u32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] - rhs[i] * s;
    return dest;
}
#else
;
#endif
/// @brief Difference of two u32v with lhs scaled by a u32
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32v SL_u32vsubS(u32v lhs, u32v rhs, u32 s, u32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u32vsubS_(lhs.data, rhs.data, s, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two u32v2 with lhs scaled by a u32
SL_header u32v2 SL_u32v2subS(u32v2 lhs, u32v2 rhs, u32 s)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v2) {
        .x = lhs.x - rhs.x * s,
        .y = lhs.y - rhs.y * s
    };
}
#else
;
#endif
/// @brief Difference of two u32v3 with lhs scaled by a u32
SL_header u32v3 SL_u32v3subS(u32v3 lhs, u32v3 rhs, u32 s)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v3) {
        .x = lhs.x - rhs.x * s,
        .y = lhs.y - rhs.y * s,
        .z = lhs.z - rhs.z * s
    };
}
#else
;
#endif
/// @brief Difference of two u32v4 with lhs scaled by a u32
SL_header u32v4 SL_u32v4subS(u32v4 lhs, u32v4 rhs, u32 s)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v4) {
        .x = lhs.x - rhs.x * s,
        .y = lhs.y - rhs.y * s,
        .z = lhs.z - rhs.z * s,
        .w = lhs.w - rhs.w * s
    };
}
#else
;
#endif
/// @brief Addition of two u32v with lhs multiplied with a u32
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32* SL_u32vaddM_(u32* lhs, u32* rhs, u32* m, u32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] + rhs[i] * m[i];
    return dest;
}
#else
;
#endif
/// @brief Addition of two u32v with lhs multiplied with a u32
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32v SL_u32vaddM(u32v lhs, u32v rhs, u32v m, u32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u32vaddM_(lhs.data, rhs.data, m.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two u32v2 with lhs multiplied with a u32
SL_header u32v2 SL_u32v2addM(u32v2 lhs, u32v2 rhs, u32v2 m)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v2) {
        .x = lhs.x + rhs.x * m.x,
        .y = lhs.y + rhs.y * m.y
    };
}
#else
;
#endif
/// @brief Addition of two u32v3 with lhs multiplied with a u32
SL_header u32v3 SL_u32v3addM(u32v3 lhs, u32v3 rhs, u32v3 m)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v3) {
        .x = lhs.x + rhs.x * m.x,
        .y = lhs.y + rhs.y * m.y,
        .z = lhs.z + rhs.z * m.z
    };
}
#else
;
#endif
/// @brief Addition of two u32v4 with lhs multiplied with a u32
SL_header u32v4 SL_u32v4addM(u32v4 lhs, u32v4 rhs, u32v4 m)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v4) {
        .x = lhs.x + rhs.x * m.x,
        .y = lhs.y + rhs.y * m.y,
        .z = lhs.z + rhs.z * m.z,
        .w = lhs.w + rhs.w * m.w
    };
}
#else
;
#endif
/// @brief Difference of two u32v with lhs multiplied with a u32
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32* SL_u32vsubM_(u32* lhs, u32* rhs, u32* m, u32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] - rhs[i] * m[i];
    return dest;
}
#else
;
#endif
/// @brief Difference of two u32v with lhs multiplied with a u32
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32v SL_u32vsubM(u32v lhs, u32v rhs, u32v m, u32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u32vsubM_(lhs.data, rhs.data, m.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two u32v2 with lhs multiplied with a u32
SL_header u32v2 SL_u32v2subM(u32v2 lhs, u32v2 rhs, u32v2 m)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v2) {
        .x = lhs.x - rhs.x * m.x,
        .y = lhs.y - rhs.y * m.y
    };
}
#else
;
#endif
/// @brief Difference of two u32v3 with lhs multiplied with a u32
SL_header u32v3 SL_u32v3subM(u32v3 lhs, u32v3 rhs, u32v3 m)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v3) {
        .x = lhs.x - rhs.x * m.x,
        .y = lhs.y - rhs.y * m.y,
        .z = lhs.z - rhs.z * m.z
    };
}
#else
;
#endif
/// @brief Difference of two u32v4 with lhs multiplied with a u32
SL_header u32v4 SL_u32v4subM(u32v4 lhs, u32v4 rhs, u32v4 m)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v4) {
        .x = lhs.x - rhs.x * m.x,
        .y = lhs.y - rhs.y * m.y,
        .z = lhs.z - rhs.z * m.z,
        .w = lhs.w - rhs.w * m.w
    };
}
#else
;
#endif
/// @brief Addition of two u32v with lhs scaled by u32 and multiplied with a u32
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32* SL_u32vaddSM_(u32* lhs, u32* rhs, u32 s, u32* m, u32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] + rhs[i] * s * m[i];
    return dest;
}
#else
;
#endif
/// @brief Addition of two u32v with lhs scaled by u32 and multiplied with a u32
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32v SL_u32vaddSM(u32v lhs, u32v rhs, u32 s, u32v m, u32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u32vaddSM_(lhs.data, rhs.data, s, m.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two u32v2 with lhs scaled by u32 and multiplied with a u32
SL_header u32v2 SL_u32v2addSM(u32v2 lhs, u32v2 rhs, u32 s, u32v2 m)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v2) {
        .x = lhs.x + rhs.x * s * m.x,
        .y = lhs.y + rhs.y * s * m.y
    };
}
#else
;
#endif
/// @brief Addition of two u32v3 with lhs scaled by u32 and multiplied with a u32
SL_header u32v3 SL_u32v3addSM(u32v3 lhs, u32v3 rhs, u32 s, u32v3 m)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v3) {
        .x = lhs.x + rhs.x * s * m.x,
        .y = lhs.y + rhs.y * s * m.y,
        .z = lhs.z + rhs.z * s * m.z
    };
}
#else
;
#endif
/// @brief Addition of two u32v4 with lhs scaled by u32 and multiplied with a u32
SL_header u32v4 SL_u32v4addSM(u32v4 lhs, u32v4 rhs, u32 s, u32v4 m)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v4) {
        .x = lhs.x + rhs.x * s * m.x,
        .y = lhs.y + rhs.y * s * m.y,
        .z = lhs.z + rhs.z * s * m.z,
        .w = lhs.w + rhs.w * s * m.w
    };
}
#else
;
#endif
/// @brief Difference of two u32v with lhs scaled by u32 and multiplied with a u32
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32* SL_u32vsubSM_(u32* lhs, u32* rhs, u32 s, u32* m, u32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] - rhs[i] * s * m[i];
    return dest;
}
#else
;
#endif
/// @brief Difference of two u32v with lhs scaled by u32 and multiplied with a u32
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32v SL_u32vsubSM(u32v lhs, u32v rhs, u32 s, u32v m, u32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u32vsubSM_(lhs.data, rhs.data, s, m.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two u32v2 with lhs scaled by u32 and multiplied with a u32
SL_header u32v2 SL_u32v2subSM(u32v2 lhs, u32v2 rhs, u32 s, u32v2 m)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v2) {
        .x = lhs.x - rhs.x * s * m.x,
        .y = lhs.y - rhs.y * s * m.y
    };
}
#else
;
#endif
/// @brief Difference of two u32v3 with lhs scaled by u32 and multiplied with a u32
SL_header u32v3 SL_u32v3subSM(u32v3 lhs, u32v3 rhs, u32 s, u32v3 m)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v3) {
        .x = lhs.x - rhs.x * s * m.x,
        .y = lhs.y - rhs.y * s * m.y,
        .z = lhs.z - rhs.z * s * m.z
    };
}
#else
;
#endif
/// @brief Difference of two u32v4 with lhs scaled by u32 and multiplied with a u32
SL_header u32v4 SL_u32v4subSM(u32v4 lhs, u32v4 rhs, u32 s, u32v4 m)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v4) {
        .x = lhs.x - rhs.x * s * m.x,
        .y = lhs.y - rhs.y * s * m.y,
        .z = lhs.z - rhs.z * s * m.z,
        .w = lhs.w - rhs.w * s * m.w
    };
}
#else
;
#endif
/// @brief Addition of two u32v with rhs scaled by a u32
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32* SL_u32vSadd_(u32* lhs, u32 s, u32* rhs, u32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * s + rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Addition of two u32v with rhs scaled by a u32
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32v SL_u32vSadd(u32v lhs, u32 s, u32v rhs, u32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u32vSadd_(lhs.data, s, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two u32v2 with rhs scaled by a u32
SL_header u32v2 SL_u32v2Sadd(u32v2 lhs, u32 s, u32v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v2) {
        .x = lhs.x * s + rhs.x,
        .y = lhs.y * s + rhs.y
    };
}
#else
;
#endif
/// @brief Addition of two u32v3 with rhs scaled by a u32
SL_header u32v3 SL_u32v3Sadd(u32v3 lhs, u32 s, u32v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v3) {
        .x = lhs.x * s + rhs.x,
        .y = lhs.y * s + rhs.y,
        .z = lhs.z * s + rhs.z
    };
}
#else
;
#endif
/// @brief Addition of two u32v4 with rhs scaled by a u32
SL_header u32v4 SL_u32v4Sadd(u32v4 lhs, u32 s, u32v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v4) {
        .x = lhs.x * s + rhs.x,
        .y = lhs.y * s + rhs.y,
        .z = lhs.z * s + rhs.z,
        .w = lhs.w * s + rhs.w
    };
}
#else
;
#endif
/// @brief Difference of two u32v with rhs scaled by a u32
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32* SL_u32vSsub_(u32* lhs, u32 s, u32* rhs, u32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * s - rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Difference of two u32v with rhs scaled by a u32
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32v SL_u32vSsub(u32v lhs, u32 s, u32v rhs, u32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u32vSsub_(lhs.data, s, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two u32v2 with rhs scaled by a u32
SL_header u32v2 SL_u32v2Ssub(u32v2 lhs, u32 s, u32v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v2) {
        .x = lhs.x * s - rhs.x,
        .y = lhs.y * s - rhs.y
    };
}
#else
;
#endif
/// @brief Difference of two u32v3 with rhs scaled by a u32
SL_header u32v3 SL_u32v3Ssub(u32v3 lhs, u32 s, u32v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v3) {
        .x = lhs.x * s - rhs.x,
        .y = lhs.y * s - rhs.y,
        .z = lhs.z * s - rhs.z
    };
}
#else
;
#endif
/// @brief Difference of two u32v4 with rhs scaled by a u32
SL_header u32v4 SL_u32v4Ssub(u32v4 lhs, u32 s, u32v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v4) {
        .x = lhs.x * s - rhs.x,
        .y = lhs.y * s - rhs.y,
        .z = lhs.z * s - rhs.z,
        .w = lhs.w * s - rhs.w
    };
}
#else
;
#endif
/// @brief Weighted sum of two u32v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32* SL_u32vmix_(u32* lhs, u32 lhs_w, u32* rhs, u32 rhs_w, u32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * lhs_w + rhs[i] * rhs_w;
    return dest;
}
#else
;
#endif
/// @brief Weighted sum of two u32v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32v SL_u32vmix(u32v lhs, u32 lhs_w, u32v rhs, u32 rhs_w, u32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u32vmix_(lhs.data, lhs_w, rhs.data, rhs_w, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Weighted sum of two u32v2
SL_header u32v2 SL_u32v2mix(u32v2 lhs, u32 lhs_w, u32v2 rhs, u32 rhs_w)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v2) {
        .x = lhs.x * lhs_w + rhs.x * rhs_w,
        .y = lhs.y * lhs_w + rhs.y * rhs_w
    };
}
#else
;
#endif
/// @brief Weighted sum of two u32v3
SL_header u32v3 SL_u32v3mix(u32v3 lhs, u32 lhs_w, u32v3 rhs, u32 rhs_w)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v3) {
        .x = lhs.x * lhs_w + rhs.x * rhs_w,
        .y = lhs.y * lhs_w + rhs.y * rhs_w,
        .z = lhs.z * lhs_w + rhs.z * rhs_w
    };
}
#else
;
#endif
/// @brief Weighted sum of two u32v4
SL_header u32v4 SL_u32v4mix(u32v4 lhs, u32 lhs_w, u32v4 rhs, u32 rhs_w)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v4) {
        .x = lhs.x * lhs_w + rhs.x * rhs_w,
        .y = lhs.y * lhs_w + rhs.y * rhs_w,
        .z = lhs.z * lhs_w + rhs.z * rhs_w,
        .w = lhs.w * lhs_w + rhs.w * rhs_w
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two u32v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32* SL_u32vmin_(u32* lhs, u32* rhs, u32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] < rhs[i] ? lhs[i] : rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise minimum of two u32v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32v SL_u32vmin(u32v lhs, u32v rhs, u32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u32vmin_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise minimum of two u32v2
SL_header u32v2 SL_u32v2min(u32v2 lhs, u32v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v2) {
        .x = lhs.x < rhs.x ? lhs.x : rhs.x,
        .y = lhs.y < rhs.y ? lhs.y : rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two u32v3
SL_header u32v3 SL_u32v3min(u32v3 lhs, u32v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v3) {
        .x = lhs.x < rhs.x ? lhs.x : rhs.x,
        .y = lhs.y < rhs.y ? lhs.y : rhs.y,
        .z = lhs.z < rhs.z ? lhs.z : rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two u32v4
SL_header u32v4 SL_u32v4min(u32v4 lhs, u32v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v4) {
        .x = lhs.x < rhs.x ? lhs.x : rhs.x,
        .y = lhs.y < rhs.y ? lhs.y : rhs.y,
        .z = lhs.z < rhs.z ? lhs.z : rhs.z,
        .w = lhs.w < rhs.w ? lhs.w : rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two u32v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32* SL_u32vmax_(u32* lhs, u32* rhs, u32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] > rhs[i] ? lhs[i] : rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise maximum of two u32v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32v SL_u32vmax(u32v lhs, u32v rhs, u32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u32vmax_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise maximum of two u32v2
SL_header u32v2 SL_u32v2max(u32v2 lhs, u32v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v2) {
        .x = lhs.x > rhs.x ? lhs.x : rhs.x,
        .y = lhs.y > rhs.y ? lhs.y : rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two u32v3
SL_header u32v3 SL_u32v3max(u32v3 lhs, u32v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v3) {
        .x = lhs.x > rhs.x ? lhs.x : rhs.x,
        .y = lhs.y > rhs.y ? lhs.y : rhs.y,
        .z = lhs.z > rhs.z ? lhs.z : rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two u32v4
SL_header u32v4 SL_u32v4max(u32v4 lhs, u32v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v4) {
        .x = lhs.x > rhs.x ? lhs.x : rhs.x,
        .y = lhs.y > rhs.y ? lhs.y : rhs.y,
        .z = lhs.z > rhs.z ? lhs.z : rhs.z,
        .w = lhs.w > rhs.w ? lhs.w : rhs.w
    };
}
#else
;
#endif
/// @brief Dot product of two u32v
/// @note All vectors are assumed to be of size 'count'
SL_header u64 SL_u32vdot_(u32* lhs, u32* rhs, usize count)
#if defined(SL_IMPLEMENTATION)
{
    u64 dest = 0;
    for (usize i = 0; i < count; ++i) dest += lhs[i] * rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Dot product of two u32v
/// @note All vectors are assumed to be of size 'count'
SL_header u64 SL_u32vdot(u32v lhs, u32v rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u32vdot_(lhs.data, rhs.data, lhs.count);
}
#else
;
#endif
/// @brief Dot product of two u32v2
SL_header u64 SL_u32v2dot(u32v2 lhs, u32v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}
#else
;
#endif
/// @brief Dot product of two u32v3
SL_header u64 SL_u32v3dot(u32v3 lhs, u32v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}
#else
;
#endif
/// @brief Dot product of two u32v4
SL_header u64 SL_u32v4dot(u32v4 lhs, u32v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}
#else
;
#endif
/// @brief Maximum component of a u32v
/// @note All vectors are assumed to be of size 'count'
SL_header u64 SL_u32vlen_max_(u32* v, usize count)
#if defined(SL_IMPLEMENTATION)
{
    u64 dest = 0;
    for (usize i = 0; i < count; ++i) dest = v[i] > dest ? v[i] : dest;
    return dest;
}
#else
;
#endif
/// @brief Maximum component of a u32v
/// @note All vectors are assumed to be of size 'count'
SL_header u64 SL_u32vlen_max(u32v v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u32vlen_max_(v.data, v.count);
}
#else
;
#endif
/// @brief Maximum component of a u32v2
SL_header u64 SL_u32v2len_max(u32v2 v)
#if defined(SL_IMPLEMENTATION)
{
    return v.x > v.y ? v.x : v.y;
}
#else
;
#endif
/// @brief Maximum component of a u32v3
SL_header u64 SL_u32v3len_max(u32v3 v)
#if defined(SL_IMPLEMENTATION)
{
    return v.x > v.y ? (v.x > v.z ? v.x : v.z) : (v.y > v.z ? v.y : v.z);
}
#else
;
#endif
/// @brief Maximum component of a u32v4
SL_header u64 SL_u32v4len_max(u32v4 v)
#if defined(SL_IMPLEMENTATION)
{
    return v.x > v.y ? (v.x > v.z ? (v.x > v.w ? v.x : v.w) : (v.z > v.w ? v.z : v.w)) : (v.y > v.z ? (v.y > v.w ? v.y : v.w) : (v.z > v.w ? v.z : v.w));
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a u32v
/// @note All vectors are assumed to be of size 'count'
SL_header u64 SL_u32vlen_manh_(u32* v, usize count)
#if defined(SL_IMPLEMENTATION)
{
    u64 dest = 0;
    for (usize i = 0; i < count; ++i) dest += v[i];
    return dest;
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a u32v
/// @note All vectors are assumed to be of size 'count'
SL_header u64 SL_u32vlen_manh(u32v v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u32vlen_manh_(v.data, v.count);
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a u32v2
SL_header u64 SL_u32v2len_manh(u32v2 v)
#if defined(SL_IMPLEMENTATION)
{
    return v.x + v.y;
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a u32v3
SL_header u64 SL_u32v3len_manh(u32v3 v)
#if defined(SL_IMPLEMENTATION)
{
    return v.x + v.y + v.z;
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a u32v4
SL_header u64 SL_u32v4len_manh(u32v4 v)
#if defined(SL_IMPLEMENTATION)
{
    return v.x + v.y + v.z + v.w;
}
#else
;
#endif
/// @brief Squared euclidean length of a u32v
/// @note All vectors are assumed to be of size 'count'
SL_header u64 SL_u32vlen_srq_(u32* v, usize count)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u32vdot_(v, v, count);
}
#else
;
#endif
/// @brief Squared euclidean length of a u32v
/// @note All vectors are assumed to be of size 'count'
SL_header u64 SL_u32vlen_srq(u32v v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u32vlen_srq_(v.data, v.count);
}
#else
;
#endif
/// @brief Square length of a u32v2
SL_header u64 SL_u32v2len_sqr(u32v2 v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u32v2dot(v, v);
}
#else
;
#endif
/// @brief Square length of a u32v3
SL_header u64 SL_u32v3len_sqr(u32v3 v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u32v3dot(v, v);
}
#else
;
#endif
/// @brief Square length of a u32v4
SL_header u64 SL_u32v4len_sqr(u32v4 v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u32v4dot(v, v);
}
#else
;
#endif
/// @brief Euclidean length of a u32v
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_u32vlen_(u32* v, usize count)
#if defined(SL_IMPLEMENTATION)
{
    return sqrt(SL_u32vdot_(v, v, count));
}
#else
;
#endif
/// @brief Euclidean length of a u32v
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_u32vlen(u32v v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u32vlen_(v.data, v.count);
}
#else
;
#endif
/// @brief Euclidean length of a u32v2
SL_header double SL_u32v2len(u32v2 v)
#if defined(SL_IMPLEMENTATION)
{
    return sqrt(SL_u32v2dot(v, v));
}
#else
;
#endif
/// @brief Euclidean length of a u32v3
SL_header double SL_u32v3len(u32v3 v)
#if defined(SL_IMPLEMENTATION)
{
    return sqrt(SL_u32v3dot(v, v));
}
#else
;
#endif
/// @brief Euclidean length of a u32v4
SL_header double SL_u32v4len(u32v4 v)
#if defined(SL_IMPLEMENTATION)
{
    return sqrt(SL_u32v4dot(v, v));
}
#else
;
#endif
/// @brief Euclidean distance bewteen two u32v
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_u32vdist_(u32* lhs, u32* rhs, usize count)
#if defined(SL_IMPLEMENTATION)
{
    double accum = 0;
    for (int i = 0; i < count; ++i) accum += (lhs[i] - rhs[i]) * (lhs[i] - rhs[i]);
    return sqrt(accum);
}
#else
;
#endif
/// @brief Euclidean distance bewteen two u32v
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_u32vdist(u32v lhs, u32v rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u32vdist_(lhs.data, rhs.data, lhs.count);
}
#else
;
#endif
/// @brief Euclidean distance between two u32v2
SL_header double SL_u32v2dist(u32v2 lhs, u32v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u32v2len(SL_u32v2sub(lhs, rhs));
}
#else
;
#endif
/// @brief Euclidean distance between two u32v3
SL_header double SL_u32v3dist(u32v3 lhs, u32v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u32v3len(SL_u32v3sub(lhs, rhs));
}
#else
;
#endif
/// @brief Euclidean distance between two u32v4
SL_header double SL_u32v4dist(u32v4 lhs, u32v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u32v4len(SL_u32v4sub(lhs, rhs));
}
#else
;
#endif
/// @brief Reflection of u32v2 v around vector u32v2 n
SL_header u32v2 SL_u32v2refl(u32v2 v, u32v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u32v2subS(v, n, 2.0 * SL_u32v2dot(v, n) / SL_u32v2dot(n, n));
}
#else
;
#endif
/// @brief Reflection of u32v3 v around vector u32v3 n
SL_header u32v3 SL_u32v3refl(u32v3 v, u32v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u32v3subS(v, n, 2.0 * SL_u32v3dot(v, n) / SL_u32v3dot(n, n));
}
#else
;
#endif
/// @brief Reflection of u32v4 v around vector u32v4 n
SL_header u32v4 SL_u32v4refl(u32v4 v, u32v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u32v4subS(v, n, 2.0 * SL_u32v4dot(v, n) / SL_u32v4dot(n, n));
}
#else
;
#endif
/// @brief Reflection of u32v2 v around vector u32v2 n assumed to be of unit length
SL_header u32v2 SL_u32v2refl_u(u32v2 v, u32v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u32v2subS(v, n, 2.0 * SL_u32v2dot(v, n));
}
#else
;
#endif
/// @brief Reflection of u32v3 v around vector u32v3 n assumed to be of unit length
SL_header u32v3 SL_u32v3refl_u(u32v3 v, u32v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u32v3subS(v, n, 2.0 * SL_u32v3dot(v, n));
}
#else
;
#endif
/// @brief Reflection of u32v4 v around vector u32v4 n assumed to be of unit length
SL_header u32v4 SL_u32v4refl_u(u32v4 v, u32v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u32v4subS(v, n, 2.0 * SL_u32v4dot(v, n));
}
#else
;
#endif
/// @brief Get component of u32v2 v in direction u32v2 n
SL_header u32v2 SL_u32v2align(u32v2 v, u32v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u32v2muls(n, SL_u32v2dot(v, n) / SL_u32v2dot(n, n));
}
#else
;
#endif
/// @brief Get component of u32v3 v in direction u32v3 n
SL_header u32v3 SL_u32v3align(u32v3 v, u32v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u32v3muls(n, SL_u32v3dot(v, n) / SL_u32v3dot(n, n));
}
#else
;
#endif
/// @brief Get component of u32v4 v in direction u32v4 n
SL_header u32v4 SL_u32v4align(u32v4 v, u32v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u32v4muls(n, SL_u32v4dot(v, n) / SL_u32v4dot(n, n));
}
#else
;
#endif
/// @brief Get component of u32v2 v in direction u32v2 n assumed to be of unit length
SL_header u32v2 SL_u32v2align_u(u32v2 v, u32v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u32v2muls(n, SL_u32v2dot(v, n));
}
#else
;
#endif
/// @brief Get component of u32v3 v in direction u32v3 n assumed to be of unit length
SL_header u32v3 SL_u32v3align_u(u32v3 v, u32v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u32v3muls(n, SL_u32v3dot(v, n));
}
#else
;
#endif
/// @brief Get component of u32v4 v in direction u32v4 n assumed to be of unit length
SL_header u32v4 SL_u32v4align_u(u32v4 v, u32v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u32v4muls(n, SL_u32v4dot(v, n));
}
#else
;
#endif
/// @brief Project u32v2 v on plane with normal u32v2 n
SL_header u32v2 SL_u32v2proj(u32v2 v, u32v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u32v2sub(v, SL_u32v2align(v, n));
}
#else
;
#endif
/// @brief Project u32v3 v on plane with normal u32v3 n
SL_header u32v3 SL_u32v3proj(u32v3 v, u32v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u32v3sub(v, SL_u32v3align(v, n));
}
#else
;
#endif
/// @brief Project u32v4 v on plane with normal u32v4 n
SL_header u32v4 SL_u32v4proj(u32v4 v, u32v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u32v4sub(v, SL_u32v4align(v, n));
}
#else
;
#endif
/// @brief Project u32v2 v on plane with normal u32v2 n
SL_header u32v2 SL_u32v2proj_u(u32v2 v, u32v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u32v2sub(v, SL_u32v2align_u(v, n));
}
#else
;
#endif
/// @brief Project u32v3 v on plane with normal u32v3 n
SL_header u32v3 SL_u32v3proj_u(u32v3 v, u32v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u32v3sub(v, SL_u32v3align_u(v, n));
}
#else
;
#endif
/// @brief Project u32v4 v on plane with normal u32v4 n
SL_header u32v4 SL_u32v4proj_u(u32v4 v, u32v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u32v4sub(v, SL_u32v4align_u(v, n));
}
#else
;
#endif
/// @brief Component-wise modulo of a u32v by scalar n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32* SL_u32vmods_(u32* v, u32 n, u32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = v[i] % n;
    return dest;
}
#else
;
#endif
/// @brief Component-wise modulo of a u32v by scalar n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32v SL_u32vmods(u32v v, u32 n, u32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u32vmods_(v.data, n, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise modulo of a u32v2 by scalar n
SL_header u32v2 SL_u32v2mods(u32v2 v, u32 n)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v2) {
        .x = v.x % n,
        .y = v.y % n
    };
}
#else
;
#endif
/// @brief Component-wise modulo of a u32v3 by scalar n
SL_header u32v3 SL_u32v3mods(u32v3 v, u32 n)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v3) {
        .x = v.x % n,
        .y = v.y % n,
        .z = v.z % n
    };
}
#else
;
#endif
/// @brief Component-wise modulo of a u32v4 by scalar n
SL_header u32v4 SL_u32v4mods(u32v4 v, u32 n)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v4) {
        .x = v.x % n,
        .y = v.y % n,
        .z = v.z % n,
        .w = v.w % n
    };
}
#else
;
#endif
/// @brief Component-wise modulo of a u32v by u32v n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32* SL_u32vmod_(u32* v, u32* n, u32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = v[i] % n[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise modulo of a u32v by u32v n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32v SL_u32vmod(u32v v, u32v n, u32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u32vmod_(v.data, n.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise modulo of a u32v2 by u32v2 n
SL_header u32v2 SL_u32v2mod(u32v2 v, u32v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v2) {
        .x = v.x % n.x,
        .y = v.y % n.y
    };
}
#else
;
#endif
/// @brief Component-wise modulo of a u32v3 by u32v3 n
SL_header u32v3 SL_u32v3mod(u32v3 v, u32v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v3) {
        .x = v.x % n.x,
        .y = v.y % n.y,
        .z = v.z % n.z
    };
}
#else
;
#endif
/// @brief Component-wise modulo of a u32v4 by u32v4 n
SL_header u32v4 SL_u32v4mod(u32v4 v, u32v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v4) {
        .x = v.x % n.x,
        .y = v.y % n.y,
        .z = v.z % n.z,
        .w = v.w % n.w
    };
}
#else
;
#endif
/// @brief Component-wise binary AND of two u32v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32* SL_u32vand_(u32* lhs, u32* rhs, u32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] & rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary AND of two u32v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32v SL_u32vand(u32v lhs, u32v rhs, u32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u32vand_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary AND of two u32v2
SL_header u32v2 SL_u32v2and(u32v2 lhs, u32v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v2) {
        .x = lhs.x & rhs.x,
        .y = lhs.y & rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise binary AND of two u32v3
SL_header u32v3 SL_u32v3and(u32v3 lhs, u32v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v3) {
        .x = lhs.x & rhs.x,
        .y = lhs.y & rhs.y,
        .z = lhs.z & rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise binary AND of two u32v4
SL_header u32v4 SL_u32v4and(u32v4 lhs, u32v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v4) {
        .x = lhs.x & rhs.x,
        .y = lhs.y & rhs.y,
        .z = lhs.z & rhs.z,
        .w = lhs.w & rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise binary OR of two u32v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32* SL_u32vor_(u32* lhs, u32* rhs, u32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] | rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary OR of two u32v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32v SL_u32vor(u32v lhs, u32v rhs, u32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u32vor_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary OR of two u32v2
SL_header u32v2 SL_u32v2or(u32v2 lhs, u32v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v2) {
        .x = lhs.x | rhs.x,
        .y = lhs.y | rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise binary OR of two u32v3
SL_header u32v3 SL_u32v3or(u32v3 lhs, u32v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v3) {
        .x = lhs.x | rhs.x,
        .y = lhs.y | rhs.y,
        .z = lhs.z | rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise binary OR of two u32v4
SL_header u32v4 SL_u32v4or(u32v4 lhs, u32v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v4) {
        .x = lhs.x | rhs.x,
        .y = lhs.y | rhs.y,
        .z = lhs.z | rhs.z,
        .w = lhs.w | rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise binary XOR of two u32v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32* SL_u32vxor_(u32* lhs, u32* rhs, u32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] ^ rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary XOR of two u32v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32v SL_u32vxor(u32v lhs, u32v rhs, u32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u32vxor_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary XOR of two u32v2
SL_header u32v2 SL_u32v2xor(u32v2 lhs, u32v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v2) {
        .x = lhs.x ^ rhs.x,
        .y = lhs.y ^ rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise binary XOR of two u32v3
SL_header u32v3 SL_u32v3xor(u32v3 lhs, u32v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v3) {
        .x = lhs.x ^ rhs.x,
        .y = lhs.y ^ rhs.y,
        .z = lhs.z ^ rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise binary XOR of two u32v4
SL_header u32v4 SL_u32v4xor(u32v4 lhs, u32v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v4) {
        .x = lhs.x ^ rhs.x,
        .y = lhs.y ^ rhs.y,
        .z = lhs.z ^ rhs.z,
        .w = lhs.w ^ rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise binary NOT of a u32v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32* SL_u32vnot_(u32* v, u32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = ~v[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary NOT of a u32v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32v SL_u32vnot(u32v v, u32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u32vnot_(v.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary NOT of a u32v2
SL_header u32v2 SL_u32v2not(u32v2 v)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v2) {
        .x = ~v.x,
        .y = ~v.y
    };
}
#else
;
#endif
/// @brief Component-wise binary NOT of a u32v3
SL_header u32v3 SL_u32v3not(u32v3 v)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v3) {
        .x = ~v.x,
        .y = ~v.y,
        .z = ~v.z
    };
}
#else
;
#endif
/// @brief Component-wise binary NOT of a u32v4
SL_header u32v4 SL_u32v4not(u32v4 v)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v4) {
        .x = ~v.x,
        .y = ~v.y,
        .z = ~v.z,
        .w = ~v.w
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a u32v by integer n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32* SL_u32vlshfts_(u32* lhs, u32 rhs, u32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] << rhs;
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a u32v by integer n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32v SL_u32vlshfts(u32v lhs, u32 rhs, u32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u32vlshfts_(lhs.data, rhs, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a u32v2 by integer n
SL_header u32v2 SL_u32v2lshfts(u32v2 lhs, u32 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v2) {
        .x = lhs.x << rhs,
        .y = lhs.y << rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a u32v3 by integer n
SL_header u32v3 SL_u32v3lshfts(u32v3 lhs, u32 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v3) {
        .x = lhs.x << rhs,
        .y = lhs.y << rhs,
        .z = lhs.z << rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a u32v4 by integer n
SL_header u32v4 SL_u32v4lshfts(u32v4 lhs, u32 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v4) {
        .x = lhs.x << rhs,
        .y = lhs.y << rhs,
        .z = lhs.z << rhs,
        .w = lhs.w << rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a u32v by u32v n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32* SL_u32vlshft_(u32* lhs, u32* rhs, u32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] << rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a u32v by u32v n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32v SL_u32vlshft(u32v lhs, u32v rhs, u32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u32vlshft_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a u32v2 by u32v2 n
SL_header u32v2 SL_u32v2lshft(u32v2 lhs, u32v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v2) {
        .x = lhs.x << rhs.x,
        .y = lhs.y << rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a u32v3 by u32v3 n
SL_header u32v3 SL_u32v3lshft(u32v3 lhs, u32v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v3) {
        .x = lhs.x << rhs.x,
        .y = lhs.y << rhs.y,
        .z = lhs.z << rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a u32v4 by u32v4 n
SL_header u32v4 SL_u32v4lshft(u32v4 lhs, u32v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v4) {
        .x = lhs.x << rhs.x,
        .y = lhs.y << rhs.y,
        .z = lhs.z << rhs.z,
        .w = lhs.w << rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a u32v by interger n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32* SL_u32vrshfts_(u32* lhs, u32 rhs, u32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] >> rhs;
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a u32v by interger n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32v SL_u32vrshfts(u32v lhs, u32 rhs, u32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u32vrshfts_(lhs.data, rhs, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a u32v2 by interger n
SL_header u32v2 SL_u32v2rshfts(u32v2 lhs, u32 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v2) {
        .x = lhs.x >> rhs,
        .y = lhs.y >> rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a u32v3 by interger n
SL_header u32v3 SL_u32v3rshfts(u32v3 lhs, u32 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v3) {
        .x = lhs.x >> rhs,
        .y = lhs.y >> rhs,
        .z = lhs.z >> rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a u32v4 by interger n
SL_header u32v4 SL_u32v4rshfts(u32v4 lhs, u32 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v4) {
        .x = lhs.x >> rhs,
        .y = lhs.y >> rhs,
        .z = lhs.z >> rhs,
        .w = lhs.w >> rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a u32v by u32v n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32* SL_u32vrshft_(u32* lhs, u32* rhs, u32* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] >> rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a u32v by u32v n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u32v SL_u32vrshft(u32v lhs, u32v rhs, u32v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u32vrshft_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a u32v2 by u32v2 n
SL_header u32v2 SL_u32v2rshft(u32v2 lhs, u32v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v2) {
        .x = lhs.x >> rhs.x,
        .y = lhs.y >> rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a u32v3 by u32v3 n
SL_header u32v3 SL_u32v3rshft(u32v3 lhs, u32v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v3) {
        .x = lhs.x >> rhs.x,
        .y = lhs.y >> rhs.y,
        .z = lhs.z >> rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a u32v4 by u32v4 n
SL_header u32v4 SL_u32v4rshft(u32v4 lhs, u32v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32v4) {
        .x = lhs.x >> rhs.x,
        .y = lhs.y >> rhs.y,
        .z = lhs.z >> rhs.z,
        .w = lhs.w >> rhs.w
    };
}
#else
;
#endif
#pragma endregion U32
#pragma region U64

/// @brief Vector of u64 with arbitrary dimension
typedef struct {
    const usize count;
    u64 *data;
} u64v;

/// @brief Vector of u64 with dimension 2
typedef union {
    u64 data[2];
    struct {
        union { u64 x, r, u; };
        union { u64 y, g, v; };
    };
} u64v2;

#define SL_u64v2_zero  ((u64v2){.x =  0, .y =  0})
#define SL_u64v2_one   ((u64v2){.x =  1, .y =  1})
#define SL_u64v2_right ((u64v2){.x =  1, .y =  0})
#define SL_u64v2_up    ((u64v2){.x =  0, .y =  1})

/// @brief Vector of u64 with dimension 3
typedef union {
    u64 data[3];
    struct {
        union { u64 x, r, u; };
        union { u64 y, g, v; };
        union { u64 z, b, s; };
    };
    struct {
        union { u64 __x, __r, __u; };
        union { u64v2 yz, gb, vs; };
    };
    struct {
        union { u64v2 xy, rg, uv; };
        union { u64 __z, __b, __s; };
    };
} u64v3;

#define SL_u64v3_zero  ((u64v3){.x =  0, .y =  0, .z =  0})
#define SL_u64v3_one   ((u64v3){.x =  1, .y =  1, .z =  1})
#define SL_u64v3_right ((u64v3){.x =  1, .y =  0, .z =  0})
#define SL_u64v3_up    ((u64v3){.x =  0, .y =  1, .z =  0})
#define SL_u64v3_forw  ((u64v3){.x =  0, .y =  0, .z =  1})

/// @brief Vector of u64 with dimension 4
typedef union {
    u64 data[4];
    struct {
        union { u64 x, r, u; };
        union { u64 y, g, v; };
        union { u64 z, b, s; };
        union { u64 w, a, t; };
    };
    struct {
        union { u64 __x0, __r0, __u0; };
        union { u64v2 yz, gb, vs; };
        union { u64 __w0, __a0, __t0; };
    };
    struct {
        union { u64v2 xy, rb, uv; };
        union { u64v2 zw, ba, st; };
    };
    struct {
        union { u64v3 xyz, rgb, uvs; };
        union { u64 __w1, __a1, __t1; };
    };
    struct {
        union { u64 __x1, __r1, __u1; };
        union { u64v3 yzw, gba, vst; };
    };
} u64v4;

#define SL_u64v4_zero  ((u64v4){.x = 0, .y = 0, .z = 0, .w = 0})
#define SL_u64v4_one   ((u64v4){.x = 1, .y = 1, .z = 1, .w = 1})

#define SL_u64v4_white  ((u64v4){.x = 1, .y = 1, .z = 1, .w = 1})
#define SL_u64v4_black  ((u64v4){.x = 0, .y = 0, .z = 0, .w = 1})
#define SL_u64v4_red    ((u64v4){.x = 1, .y = 0, .z = 0, .w = 1})
#define SL_u64v4_green  ((u64v4){.x = 0, .y = 1, .z = 0, .w = 1})
#define SL_u64v4_blue   ((u64v4){.x = 0, .y = 0, .z = 1, .w = 1})
#define SL_u64v4_yellow ((u64v4){.x = 1, .y = 1, .z = 0, .w = 1})
#define SL_u64v4_cyan   ((u64v4){.x = 0, .y = 1, .z = 1, .w = 1})
#define SL_u64v4_purple ((u64v4){.x = 1, .y = 0, .z = 1, .w = 1})



#define SL_u64v2_(X, Y)       ((u64v2){.x = X, .y = Y})
#define SL_u64v3_(X, Y, Z)    ((u64v3){.x = X, .y = Y, .z = Z})
#define SL_u64v4_(X, Y, Z, W) ((u64v4){.x = X, .y = Y, .z = Z, .w = W})

#define SL_u64v2s(S)          ((u64v2){.x = S, .y = S})
#define SL_u64v3s(S)          ((u64v3){.x = S, .y = S, .z = S})
#define SL_u64v4s(S)          ((u64v4){.x = S, .y = S, .z = S, .w = S})

#define SL_u64vv(V)           ((u64v){.count = vsize(V), .data = (V).data})
#define SL_u64v2v(V, ...)     ((u64v2){.x = (V).x, .y = (V).y})
#define SL_u64v3v(V, ...)     ((u64v3){.x = (V).x, .y = (V).y, .z = (SL_vsize(V) >= 3 ? (V).data[2] : (0, ##__VA_ARGS__))})
#define SL_u64v4v(V, ...)     ((u64v4){.x = (V).x, .y = (V).y, .z = (SL_vsize(V) >= 3 ? (V).data[2] : ((const float[]){0, ##__VA_ARGS__, 0})[1]), .w = (SL_vsize(V) >= 4 ? (V).data[3] : ((const float[]){0, ##__VA_ARGS__, 0, 0})[2])})



/// @brief Equality of two u64v
/// @note All vectors are assumed to be of size 'count'
SL_header bool SL_u64vequ_(u64* lhs, u64* rhs, usize count)
#if defined(SL_IMPLEMENTATION)
{
    bool dest = true;
    for (usize i = 0; i < count; ++i) dest &= lhs[i] == rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Equality of two u64v
/// @note All vectors are assumed to be of size 'count'
SL_header bool SL_u64vequ(u64v lhs, u64v rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u64vequ_(lhs.data, rhs.data, lhs.count);
}
#else
;
#endif
/// @brief Equality of two u64v2
SL_header bool SL_u64v2equ(u64v2 lhs, u64v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}
#else
;
#endif
/// @brief Equality of two u64v3
SL_header bool SL_u64v3equ(u64v3 lhs, u64v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}
#else
;
#endif
/// @brief Equality of two u64v4
SL_header bool SL_u64v4equ(u64v4 lhs, u64v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
}
#else
;
#endif
/// @brief Addition of two u64v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64* SL_u64vadd_(u64* lhs, u64* rhs, u64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] + rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Addition of two u64v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64v SL_u64vadd(u64v lhs, u64v rhs, u64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u64vadd_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two u64v2
SL_header u64v2 SL_u64v2add(u64v2 lhs, u64v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v2) {
        .x = lhs.x + rhs.x,
        .y = lhs.y + rhs.y
    };
}
#else
;
#endif
/// @brief Addition of two u64v3
SL_header u64v3 SL_u64v3add(u64v3 lhs, u64v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v3) {
        .x = lhs.x + rhs.x,
        .y = lhs.y + rhs.y,
        .z = lhs.z + rhs.z
    };
}
#else
;
#endif
/// @brief Addition of two u64v4
SL_header u64v4 SL_u64v4add(u64v4 lhs, u64v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v4) {
        .x = lhs.x + rhs.x,
        .y = lhs.y + rhs.y,
        .z = lhs.z + rhs.z,
        .w = lhs.w + rhs.w
    };
}
#else
;
#endif
/// @brief Difference of two u64v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64* SL_u64vsub_(u64* lhs, u64* rhs, u64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] - rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Difference of two u64v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64v SL_u64vsub(u64v lhs, u64v rhs, u64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u64vsub_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two u64v2
SL_header u64v2 SL_u64v2sub(u64v2 lhs, u64v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v2) {
        .x = lhs.x - rhs.x,
        .y = lhs.y - rhs.y
    };
}
#else
;
#endif
/// @brief Difference of two u64v3
SL_header u64v3 SL_u64v3sub(u64v3 lhs, u64v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v3) {
        .x = lhs.x - rhs.x,
        .y = lhs.y - rhs.y,
        .z = lhs.z - rhs.z
    };
}
#else
;
#endif
/// @brief Difference of two u64v4
SL_header u64v4 SL_u64v4sub(u64v4 lhs, u64v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v4) {
        .x = lhs.x - rhs.x,
        .y = lhs.y - rhs.y,
        .z = lhs.z - rhs.z,
        .w = lhs.w - rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of two u64v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64* SL_u64vmul_(u64* lhs, u64* rhs, u64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise multiplication of two u64v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64v SL_u64vmul(u64v lhs, u64v rhs, u64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u64vmul_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise multiplication of two u64v2
SL_header u64v2 SL_u64v2mul(u64v2 lhs, u64v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v2) {
        .x = lhs.x * rhs.x,
        .y = lhs.y * rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of two u64v3
SL_header u64v3 SL_u64v3mul(u64v3 lhs, u64v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v3) {
        .x = lhs.x * rhs.x,
        .y = lhs.y * rhs.y,
        .z = lhs.z * rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of two u64v4
SL_header u64v4 SL_u64v4mul(u64v4 lhs, u64v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v4) {
        .x = lhs.x * rhs.x,
        .y = lhs.y * rhs.y,
        .z = lhs.z * rhs.z,
        .w = lhs.w * rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of a u64v with a scalar
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64* SL_u64vmuls_(u64* lhs, u64 rhs, u64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * rhs;
    return dest;
}
#else
;
#endif
/// @brief Component-wise multiplication of a u64v with a scalar
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64v SL_u64vmuls(u64v lhs, u64 rhs, u64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u64vmuls_(lhs.data, rhs, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise multiplication of a u64v2 with a scalar
SL_header u64v2 SL_u64v2muls(u64v2 lhs, u64 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v2) {
        .x = lhs.x * rhs,
        .y = lhs.y * rhs
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of a u64v3 with a scalar
SL_header u64v3 SL_u64v3muls(u64v3 lhs, u64 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v3) {
        .x = lhs.x * rhs,
        .y = lhs.y * rhs,
        .z = lhs.z * rhs
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of a u64v4 with a scalar
SL_header u64v4 SL_u64v4muls(u64v4 lhs, u64 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v4) {
        .x = lhs.x * rhs,
        .y = lhs.y * rhs,
        .z = lhs.z * rhs,
        .w = lhs.w * rhs
    };
}
#else
;
#endif
/// @brief Component-wise division of two u64v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64* SL_u64vdiv_(u64* lhs, u64* rhs, u64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] / rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise division of two u64v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64v SL_u64vdiv(u64v lhs, u64v rhs, u64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u64vdiv_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise division of two u64v2
SL_header u64v2 SL_u64v2div(u64v2 lhs, u64v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v2) {
        .x = lhs.x / rhs.x,
        .y = lhs.y / rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise division of two u64v3
SL_header u64v3 SL_u64v3div(u64v3 lhs, u64v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v3) {
        .x = lhs.x / rhs.x,
        .y = lhs.y / rhs.y,
        .z = lhs.z / rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise division of two u64v4
SL_header u64v4 SL_u64v4div(u64v4 lhs, u64v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v4) {
        .x = lhs.x / rhs.x,
        .y = lhs.y / rhs.y,
        .z = lhs.z / rhs.z,
        .w = lhs.w / rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise division of a u64v with a scalar
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64* SL_u64vdivs_(u64* lhs, u64 rhs, u64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] / rhs;
    return dest;
}
#else
;
#endif
/// @brief Component-wise division of a u64v with a scalar
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64v SL_u64vdivs(u64v lhs, u64 rhs, u64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u64vdivs_(lhs.data, rhs, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise division of a u64v2 with a scalar
SL_header u64v2 SL_u64v2divs(u64v2 lhs, u64 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v2) {
        .x = lhs.x / rhs,
        .y = lhs.y / rhs
    };
}
#else
;
#endif
/// @brief Component-wise division of a u64v3 with a scalar
SL_header u64v3 SL_u64v3divs(u64v3 lhs, u64 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v3) {
        .x = lhs.x / rhs,
        .y = lhs.y / rhs,
        .z = lhs.z / rhs
    };
}
#else
;
#endif
/// @brief Component-wise division of a u64v4 with a scalar
SL_header u64v4 SL_u64v4divs(u64v4 lhs, u64 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v4) {
        .x = lhs.x / rhs,
        .y = lhs.y / rhs,
        .z = lhs.z / rhs,
        .w = lhs.w / rhs
    };
}
#else
;
#endif
/// @brief Addition of two u64v with lhs scaled by a u64
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64* SL_u64vaddS_(u64* lhs, u64* rhs, u64 s, u64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] + rhs[i] * s;
    return dest;
}
#else
;
#endif
/// @brief Addition of two u64v with lhs scaled by a u64
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64v SL_u64vaddS(u64v lhs, u64v rhs, u64 s, u64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u64vaddS_(lhs.data, rhs.data, s, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two u64v2 with lhs scaled by a u64
SL_header u64v2 SL_u64v2addS(u64v2 lhs, u64v2 rhs, u64 s)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v2) {
        .x = lhs.x + rhs.x * s,
        .y = lhs.y + rhs.y * s
    };
}
#else
;
#endif
/// @brief Addition of two u64v3 with lhs scaled by a u64
SL_header u64v3 SL_u64v3addS(u64v3 lhs, u64v3 rhs, u64 s)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v3) {
        .x = lhs.x + rhs.x * s,
        .y = lhs.y + rhs.y * s,
        .z = lhs.z + rhs.z * s
    };
}
#else
;
#endif
/// @brief Addition of two u64v4 with lhs scaled by a u64
SL_header u64v4 SL_u64v4addS(u64v4 lhs, u64v4 rhs, u64 s)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v4) {
        .x = lhs.x + rhs.x * s,
        .y = lhs.y + rhs.y * s,
        .z = lhs.z + rhs.z * s,
        .w = lhs.w + rhs.w * s
    };
}
#else
;
#endif
/// @brief Difference of two u64v with lhs scaled by a u64
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64* SL_u64vsubS_(u64* lhs, u64* rhs, u64 s, u64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] - rhs[i] * s;
    return dest;
}
#else
;
#endif
/// @brief Difference of two u64v with lhs scaled by a u64
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64v SL_u64vsubS(u64v lhs, u64v rhs, u64 s, u64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u64vsubS_(lhs.data, rhs.data, s, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two u64v2 with lhs scaled by a u64
SL_header u64v2 SL_u64v2subS(u64v2 lhs, u64v2 rhs, u64 s)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v2) {
        .x = lhs.x - rhs.x * s,
        .y = lhs.y - rhs.y * s
    };
}
#else
;
#endif
/// @brief Difference of two u64v3 with lhs scaled by a u64
SL_header u64v3 SL_u64v3subS(u64v3 lhs, u64v3 rhs, u64 s)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v3) {
        .x = lhs.x - rhs.x * s,
        .y = lhs.y - rhs.y * s,
        .z = lhs.z - rhs.z * s
    };
}
#else
;
#endif
/// @brief Difference of two u64v4 with lhs scaled by a u64
SL_header u64v4 SL_u64v4subS(u64v4 lhs, u64v4 rhs, u64 s)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v4) {
        .x = lhs.x - rhs.x * s,
        .y = lhs.y - rhs.y * s,
        .z = lhs.z - rhs.z * s,
        .w = lhs.w - rhs.w * s
    };
}
#else
;
#endif
/// @brief Addition of two u64v with lhs multiplied with a u64
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64* SL_u64vaddM_(u64* lhs, u64* rhs, u64* m, u64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] + rhs[i] * m[i];
    return dest;
}
#else
;
#endif
/// @brief Addition of two u64v with lhs multiplied with a u64
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64v SL_u64vaddM(u64v lhs, u64v rhs, u64v m, u64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u64vaddM_(lhs.data, rhs.data, m.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two u64v2 with lhs multiplied with a u64
SL_header u64v2 SL_u64v2addM(u64v2 lhs, u64v2 rhs, u64v2 m)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v2) {
        .x = lhs.x + rhs.x * m.x,
        .y = lhs.y + rhs.y * m.y
    };
}
#else
;
#endif
/// @brief Addition of two u64v3 with lhs multiplied with a u64
SL_header u64v3 SL_u64v3addM(u64v3 lhs, u64v3 rhs, u64v3 m)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v3) {
        .x = lhs.x + rhs.x * m.x,
        .y = lhs.y + rhs.y * m.y,
        .z = lhs.z + rhs.z * m.z
    };
}
#else
;
#endif
/// @brief Addition of two u64v4 with lhs multiplied with a u64
SL_header u64v4 SL_u64v4addM(u64v4 lhs, u64v4 rhs, u64v4 m)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v4) {
        .x = lhs.x + rhs.x * m.x,
        .y = lhs.y + rhs.y * m.y,
        .z = lhs.z + rhs.z * m.z,
        .w = lhs.w + rhs.w * m.w
    };
}
#else
;
#endif
/// @brief Difference of two u64v with lhs multiplied with a u64
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64* SL_u64vsubM_(u64* lhs, u64* rhs, u64* m, u64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] - rhs[i] * m[i];
    return dest;
}
#else
;
#endif
/// @brief Difference of two u64v with lhs multiplied with a u64
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64v SL_u64vsubM(u64v lhs, u64v rhs, u64v m, u64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u64vsubM_(lhs.data, rhs.data, m.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two u64v2 with lhs multiplied with a u64
SL_header u64v2 SL_u64v2subM(u64v2 lhs, u64v2 rhs, u64v2 m)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v2) {
        .x = lhs.x - rhs.x * m.x,
        .y = lhs.y - rhs.y * m.y
    };
}
#else
;
#endif
/// @brief Difference of two u64v3 with lhs multiplied with a u64
SL_header u64v3 SL_u64v3subM(u64v3 lhs, u64v3 rhs, u64v3 m)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v3) {
        .x = lhs.x - rhs.x * m.x,
        .y = lhs.y - rhs.y * m.y,
        .z = lhs.z - rhs.z * m.z
    };
}
#else
;
#endif
/// @brief Difference of two u64v4 with lhs multiplied with a u64
SL_header u64v4 SL_u64v4subM(u64v4 lhs, u64v4 rhs, u64v4 m)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v4) {
        .x = lhs.x - rhs.x * m.x,
        .y = lhs.y - rhs.y * m.y,
        .z = lhs.z - rhs.z * m.z,
        .w = lhs.w - rhs.w * m.w
    };
}
#else
;
#endif
/// @brief Addition of two u64v with lhs scaled by u64 and multiplied with a u64
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64* SL_u64vaddSM_(u64* lhs, u64* rhs, u64 s, u64* m, u64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] + rhs[i] * s * m[i];
    return dest;
}
#else
;
#endif
/// @brief Addition of two u64v with lhs scaled by u64 and multiplied with a u64
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64v SL_u64vaddSM(u64v lhs, u64v rhs, u64 s, u64v m, u64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u64vaddSM_(lhs.data, rhs.data, s, m.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two u64v2 with lhs scaled by u64 and multiplied with a u64
SL_header u64v2 SL_u64v2addSM(u64v2 lhs, u64v2 rhs, u64 s, u64v2 m)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v2) {
        .x = lhs.x + rhs.x * s * m.x,
        .y = lhs.y + rhs.y * s * m.y
    };
}
#else
;
#endif
/// @brief Addition of two u64v3 with lhs scaled by u64 and multiplied with a u64
SL_header u64v3 SL_u64v3addSM(u64v3 lhs, u64v3 rhs, u64 s, u64v3 m)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v3) {
        .x = lhs.x + rhs.x * s * m.x,
        .y = lhs.y + rhs.y * s * m.y,
        .z = lhs.z + rhs.z * s * m.z
    };
}
#else
;
#endif
/// @brief Addition of two u64v4 with lhs scaled by u64 and multiplied with a u64
SL_header u64v4 SL_u64v4addSM(u64v4 lhs, u64v4 rhs, u64 s, u64v4 m)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v4) {
        .x = lhs.x + rhs.x * s * m.x,
        .y = lhs.y + rhs.y * s * m.y,
        .z = lhs.z + rhs.z * s * m.z,
        .w = lhs.w + rhs.w * s * m.w
    };
}
#else
;
#endif
/// @brief Difference of two u64v with lhs scaled by u64 and multiplied with a u64
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64* SL_u64vsubSM_(u64* lhs, u64* rhs, u64 s, u64* m, u64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] - rhs[i] * s * m[i];
    return dest;
}
#else
;
#endif
/// @brief Difference of two u64v with lhs scaled by u64 and multiplied with a u64
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64v SL_u64vsubSM(u64v lhs, u64v rhs, u64 s, u64v m, u64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u64vsubSM_(lhs.data, rhs.data, s, m.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two u64v2 with lhs scaled by u64 and multiplied with a u64
SL_header u64v2 SL_u64v2subSM(u64v2 lhs, u64v2 rhs, u64 s, u64v2 m)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v2) {
        .x = lhs.x - rhs.x * s * m.x,
        .y = lhs.y - rhs.y * s * m.y
    };
}
#else
;
#endif
/// @brief Difference of two u64v3 with lhs scaled by u64 and multiplied with a u64
SL_header u64v3 SL_u64v3subSM(u64v3 lhs, u64v3 rhs, u64 s, u64v3 m)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v3) {
        .x = lhs.x - rhs.x * s * m.x,
        .y = lhs.y - rhs.y * s * m.y,
        .z = lhs.z - rhs.z * s * m.z
    };
}
#else
;
#endif
/// @brief Difference of two u64v4 with lhs scaled by u64 and multiplied with a u64
SL_header u64v4 SL_u64v4subSM(u64v4 lhs, u64v4 rhs, u64 s, u64v4 m)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v4) {
        .x = lhs.x - rhs.x * s * m.x,
        .y = lhs.y - rhs.y * s * m.y,
        .z = lhs.z - rhs.z * s * m.z,
        .w = lhs.w - rhs.w * s * m.w
    };
}
#else
;
#endif
/// @brief Addition of two u64v with rhs scaled by a u64
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64* SL_u64vSadd_(u64* lhs, u64 s, u64* rhs, u64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * s + rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Addition of two u64v with rhs scaled by a u64
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64v SL_u64vSadd(u64v lhs, u64 s, u64v rhs, u64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u64vSadd_(lhs.data, s, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two u64v2 with rhs scaled by a u64
SL_header u64v2 SL_u64v2Sadd(u64v2 lhs, u64 s, u64v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v2) {
        .x = lhs.x * s + rhs.x,
        .y = lhs.y * s + rhs.y
    };
}
#else
;
#endif
/// @brief Addition of two u64v3 with rhs scaled by a u64
SL_header u64v3 SL_u64v3Sadd(u64v3 lhs, u64 s, u64v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v3) {
        .x = lhs.x * s + rhs.x,
        .y = lhs.y * s + rhs.y,
        .z = lhs.z * s + rhs.z
    };
}
#else
;
#endif
/// @brief Addition of two u64v4 with rhs scaled by a u64
SL_header u64v4 SL_u64v4Sadd(u64v4 lhs, u64 s, u64v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v4) {
        .x = lhs.x * s + rhs.x,
        .y = lhs.y * s + rhs.y,
        .z = lhs.z * s + rhs.z,
        .w = lhs.w * s + rhs.w
    };
}
#else
;
#endif
/// @brief Difference of two u64v with rhs scaled by a u64
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64* SL_u64vSsub_(u64* lhs, u64 s, u64* rhs, u64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * s - rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Difference of two u64v with rhs scaled by a u64
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64v SL_u64vSsub(u64v lhs, u64 s, u64v rhs, u64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u64vSsub_(lhs.data, s, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two u64v2 with rhs scaled by a u64
SL_header u64v2 SL_u64v2Ssub(u64v2 lhs, u64 s, u64v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v2) {
        .x = lhs.x * s - rhs.x,
        .y = lhs.y * s - rhs.y
    };
}
#else
;
#endif
/// @brief Difference of two u64v3 with rhs scaled by a u64
SL_header u64v3 SL_u64v3Ssub(u64v3 lhs, u64 s, u64v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v3) {
        .x = lhs.x * s - rhs.x,
        .y = lhs.y * s - rhs.y,
        .z = lhs.z * s - rhs.z
    };
}
#else
;
#endif
/// @brief Difference of two u64v4 with rhs scaled by a u64
SL_header u64v4 SL_u64v4Ssub(u64v4 lhs, u64 s, u64v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v4) {
        .x = lhs.x * s - rhs.x,
        .y = lhs.y * s - rhs.y,
        .z = lhs.z * s - rhs.z,
        .w = lhs.w * s - rhs.w
    };
}
#else
;
#endif
/// @brief Weighted sum of two u64v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64* SL_u64vmix_(u64* lhs, u64 lhs_w, u64* rhs, u64 rhs_w, u64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * lhs_w + rhs[i] * rhs_w;
    return dest;
}
#else
;
#endif
/// @brief Weighted sum of two u64v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64v SL_u64vmix(u64v lhs, u64 lhs_w, u64v rhs, u64 rhs_w, u64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u64vmix_(lhs.data, lhs_w, rhs.data, rhs_w, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Weighted sum of two u64v2
SL_header u64v2 SL_u64v2mix(u64v2 lhs, u64 lhs_w, u64v2 rhs, u64 rhs_w)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v2) {
        .x = lhs.x * lhs_w + rhs.x * rhs_w,
        .y = lhs.y * lhs_w + rhs.y * rhs_w
    };
}
#else
;
#endif
/// @brief Weighted sum of two u64v3
SL_header u64v3 SL_u64v3mix(u64v3 lhs, u64 lhs_w, u64v3 rhs, u64 rhs_w)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v3) {
        .x = lhs.x * lhs_w + rhs.x * rhs_w,
        .y = lhs.y * lhs_w + rhs.y * rhs_w,
        .z = lhs.z * lhs_w + rhs.z * rhs_w
    };
}
#else
;
#endif
/// @brief Weighted sum of two u64v4
SL_header u64v4 SL_u64v4mix(u64v4 lhs, u64 lhs_w, u64v4 rhs, u64 rhs_w)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v4) {
        .x = lhs.x * lhs_w + rhs.x * rhs_w,
        .y = lhs.y * lhs_w + rhs.y * rhs_w,
        .z = lhs.z * lhs_w + rhs.z * rhs_w,
        .w = lhs.w * lhs_w + rhs.w * rhs_w
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two u64v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64* SL_u64vmin_(u64* lhs, u64* rhs, u64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] < rhs[i] ? lhs[i] : rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise minimum of two u64v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64v SL_u64vmin(u64v lhs, u64v rhs, u64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u64vmin_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise minimum of two u64v2
SL_header u64v2 SL_u64v2min(u64v2 lhs, u64v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v2) {
        .x = lhs.x < rhs.x ? lhs.x : rhs.x,
        .y = lhs.y < rhs.y ? lhs.y : rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two u64v3
SL_header u64v3 SL_u64v3min(u64v3 lhs, u64v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v3) {
        .x = lhs.x < rhs.x ? lhs.x : rhs.x,
        .y = lhs.y < rhs.y ? lhs.y : rhs.y,
        .z = lhs.z < rhs.z ? lhs.z : rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two u64v4
SL_header u64v4 SL_u64v4min(u64v4 lhs, u64v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v4) {
        .x = lhs.x < rhs.x ? lhs.x : rhs.x,
        .y = lhs.y < rhs.y ? lhs.y : rhs.y,
        .z = lhs.z < rhs.z ? lhs.z : rhs.z,
        .w = lhs.w < rhs.w ? lhs.w : rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two u64v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64* SL_u64vmax_(u64* lhs, u64* rhs, u64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] > rhs[i] ? lhs[i] : rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise maximum of two u64v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64v SL_u64vmax(u64v lhs, u64v rhs, u64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u64vmax_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise maximum of two u64v2
SL_header u64v2 SL_u64v2max(u64v2 lhs, u64v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v2) {
        .x = lhs.x > rhs.x ? lhs.x : rhs.x,
        .y = lhs.y > rhs.y ? lhs.y : rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two u64v3
SL_header u64v3 SL_u64v3max(u64v3 lhs, u64v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v3) {
        .x = lhs.x > rhs.x ? lhs.x : rhs.x,
        .y = lhs.y > rhs.y ? lhs.y : rhs.y,
        .z = lhs.z > rhs.z ? lhs.z : rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two u64v4
SL_header u64v4 SL_u64v4max(u64v4 lhs, u64v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v4) {
        .x = lhs.x > rhs.x ? lhs.x : rhs.x,
        .y = lhs.y > rhs.y ? lhs.y : rhs.y,
        .z = lhs.z > rhs.z ? lhs.z : rhs.z,
        .w = lhs.w > rhs.w ? lhs.w : rhs.w
    };
}
#else
;
#endif
/// @brief Dot product of two u64v
/// @note All vectors are assumed to be of size 'count'
SL_header u64 SL_u64vdot_(u64* lhs, u64* rhs, usize count)
#if defined(SL_IMPLEMENTATION)
{
    u64 dest = 0;
    for (usize i = 0; i < count; ++i) dest += lhs[i] * rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Dot product of two u64v
/// @note All vectors are assumed to be of size 'count'
SL_header u64 SL_u64vdot(u64v lhs, u64v rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u64vdot_(lhs.data, rhs.data, lhs.count);
}
#else
;
#endif
/// @brief Dot product of two u64v2
SL_header u64 SL_u64v2dot(u64v2 lhs, u64v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}
#else
;
#endif
/// @brief Dot product of two u64v3
SL_header u64 SL_u64v3dot(u64v3 lhs, u64v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}
#else
;
#endif
/// @brief Dot product of two u64v4
SL_header u64 SL_u64v4dot(u64v4 lhs, u64v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}
#else
;
#endif
/// @brief Maximum component of a u64v
/// @note All vectors are assumed to be of size 'count'
SL_header u64 SL_u64vlen_max_(u64* v, usize count)
#if defined(SL_IMPLEMENTATION)
{
    u64 dest = 0;
    for (usize i = 0; i < count; ++i) dest = v[i] > dest ? v[i] : dest;
    return dest;
}
#else
;
#endif
/// @brief Maximum component of a u64v
/// @note All vectors are assumed to be of size 'count'
SL_header u64 SL_u64vlen_max(u64v v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u64vlen_max_(v.data, v.count);
}
#else
;
#endif
/// @brief Maximum component of a u64v2
SL_header u64 SL_u64v2len_max(u64v2 v)
#if defined(SL_IMPLEMENTATION)
{
    return v.x > v.y ? v.x : v.y;
}
#else
;
#endif
/// @brief Maximum component of a u64v3
SL_header u64 SL_u64v3len_max(u64v3 v)
#if defined(SL_IMPLEMENTATION)
{
    return v.x > v.y ? (v.x > v.z ? v.x : v.z) : (v.y > v.z ? v.y : v.z);
}
#else
;
#endif
/// @brief Maximum component of a u64v4
SL_header u64 SL_u64v4len_max(u64v4 v)
#if defined(SL_IMPLEMENTATION)
{
    return v.x > v.y ? (v.x > v.z ? (v.x > v.w ? v.x : v.w) : (v.z > v.w ? v.z : v.w)) : (v.y > v.z ? (v.y > v.w ? v.y : v.w) : (v.z > v.w ? v.z : v.w));
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a u64v
/// @note All vectors are assumed to be of size 'count'
SL_header u64 SL_u64vlen_manh_(u64* v, usize count)
#if defined(SL_IMPLEMENTATION)
{
    u64 dest = 0;
    for (usize i = 0; i < count; ++i) dest += v[i];
    return dest;
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a u64v
/// @note All vectors are assumed to be of size 'count'
SL_header u64 SL_u64vlen_manh(u64v v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u64vlen_manh_(v.data, v.count);
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a u64v2
SL_header u64 SL_u64v2len_manh(u64v2 v)
#if defined(SL_IMPLEMENTATION)
{
    return v.x + v.y;
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a u64v3
SL_header u64 SL_u64v3len_manh(u64v3 v)
#if defined(SL_IMPLEMENTATION)
{
    return v.x + v.y + v.z;
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a u64v4
SL_header u64 SL_u64v4len_manh(u64v4 v)
#if defined(SL_IMPLEMENTATION)
{
    return v.x + v.y + v.z + v.w;
}
#else
;
#endif
/// @brief Squared euclidean length of a u64v
/// @note All vectors are assumed to be of size 'count'
SL_header u64 SL_u64vlen_srq_(u64* v, usize count)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u64vdot_(v, v, count);
}
#else
;
#endif
/// @brief Squared euclidean length of a u64v
/// @note All vectors are assumed to be of size 'count'
SL_header u64 SL_u64vlen_srq(u64v v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u64vlen_srq_(v.data, v.count);
}
#else
;
#endif
/// @brief Square length of a u64v2
SL_header u64 SL_u64v2len_sqr(u64v2 v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u64v2dot(v, v);
}
#else
;
#endif
/// @brief Square length of a u64v3
SL_header u64 SL_u64v3len_sqr(u64v3 v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u64v3dot(v, v);
}
#else
;
#endif
/// @brief Square length of a u64v4
SL_header u64 SL_u64v4len_sqr(u64v4 v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u64v4dot(v, v);
}
#else
;
#endif
/// @brief Euclidean length of a u64v
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_u64vlen_(u64* v, usize count)
#if defined(SL_IMPLEMENTATION)
{
    return sqrt(SL_u64vdot_(v, v, count));
}
#else
;
#endif
/// @brief Euclidean length of a u64v
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_u64vlen(u64v v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u64vlen_(v.data, v.count);
}
#else
;
#endif
/// @brief Euclidean length of a u64v2
SL_header double SL_u64v2len(u64v2 v)
#if defined(SL_IMPLEMENTATION)
{
    return sqrt(SL_u64v2dot(v, v));
}
#else
;
#endif
/// @brief Euclidean length of a u64v3
SL_header double SL_u64v3len(u64v3 v)
#if defined(SL_IMPLEMENTATION)
{
    return sqrt(SL_u64v3dot(v, v));
}
#else
;
#endif
/// @brief Euclidean length of a u64v4
SL_header double SL_u64v4len(u64v4 v)
#if defined(SL_IMPLEMENTATION)
{
    return sqrt(SL_u64v4dot(v, v));
}
#else
;
#endif
/// @brief Euclidean distance bewteen two u64v
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_u64vdist_(u64* lhs, u64* rhs, usize count)
#if defined(SL_IMPLEMENTATION)
{
    double accum = 0;
    for (int i = 0; i < count; ++i) accum += (lhs[i] - rhs[i]) * (lhs[i] - rhs[i]);
    return sqrt(accum);
}
#else
;
#endif
/// @brief Euclidean distance bewteen two u64v
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_u64vdist(u64v lhs, u64v rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u64vdist_(lhs.data, rhs.data, lhs.count);
}
#else
;
#endif
/// @brief Euclidean distance between two u64v2
SL_header double SL_u64v2dist(u64v2 lhs, u64v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u64v2len(SL_u64v2sub(lhs, rhs));
}
#else
;
#endif
/// @brief Euclidean distance between two u64v3
SL_header double SL_u64v3dist(u64v3 lhs, u64v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u64v3len(SL_u64v3sub(lhs, rhs));
}
#else
;
#endif
/// @brief Euclidean distance between two u64v4
SL_header double SL_u64v4dist(u64v4 lhs, u64v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u64v4len(SL_u64v4sub(lhs, rhs));
}
#else
;
#endif
/// @brief Reflection of u64v2 v around vector u64v2 n
SL_header u64v2 SL_u64v2refl(u64v2 v, u64v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u64v2subS(v, n, 2.0 * SL_u64v2dot(v, n) / SL_u64v2dot(n, n));
}
#else
;
#endif
/// @brief Reflection of u64v3 v around vector u64v3 n
SL_header u64v3 SL_u64v3refl(u64v3 v, u64v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u64v3subS(v, n, 2.0 * SL_u64v3dot(v, n) / SL_u64v3dot(n, n));
}
#else
;
#endif
/// @brief Reflection of u64v4 v around vector u64v4 n
SL_header u64v4 SL_u64v4refl(u64v4 v, u64v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u64v4subS(v, n, 2.0 * SL_u64v4dot(v, n) / SL_u64v4dot(n, n));
}
#else
;
#endif
/// @brief Reflection of u64v2 v around vector u64v2 n assumed to be of unit length
SL_header u64v2 SL_u64v2refl_u(u64v2 v, u64v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u64v2subS(v, n, 2.0 * SL_u64v2dot(v, n));
}
#else
;
#endif
/// @brief Reflection of u64v3 v around vector u64v3 n assumed to be of unit length
SL_header u64v3 SL_u64v3refl_u(u64v3 v, u64v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u64v3subS(v, n, 2.0 * SL_u64v3dot(v, n));
}
#else
;
#endif
/// @brief Reflection of u64v4 v around vector u64v4 n assumed to be of unit length
SL_header u64v4 SL_u64v4refl_u(u64v4 v, u64v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u64v4subS(v, n, 2.0 * SL_u64v4dot(v, n));
}
#else
;
#endif
/// @brief Get component of u64v2 v in direction u64v2 n
SL_header u64v2 SL_u64v2align(u64v2 v, u64v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u64v2muls(n, SL_u64v2dot(v, n) / SL_u64v2dot(n, n));
}
#else
;
#endif
/// @brief Get component of u64v3 v in direction u64v3 n
SL_header u64v3 SL_u64v3align(u64v3 v, u64v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u64v3muls(n, SL_u64v3dot(v, n) / SL_u64v3dot(n, n));
}
#else
;
#endif
/// @brief Get component of u64v4 v in direction u64v4 n
SL_header u64v4 SL_u64v4align(u64v4 v, u64v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u64v4muls(n, SL_u64v4dot(v, n) / SL_u64v4dot(n, n));
}
#else
;
#endif
/// @brief Get component of u64v2 v in direction u64v2 n assumed to be of unit length
SL_header u64v2 SL_u64v2align_u(u64v2 v, u64v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u64v2muls(n, SL_u64v2dot(v, n));
}
#else
;
#endif
/// @brief Get component of u64v3 v in direction u64v3 n assumed to be of unit length
SL_header u64v3 SL_u64v3align_u(u64v3 v, u64v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u64v3muls(n, SL_u64v3dot(v, n));
}
#else
;
#endif
/// @brief Get component of u64v4 v in direction u64v4 n assumed to be of unit length
SL_header u64v4 SL_u64v4align_u(u64v4 v, u64v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u64v4muls(n, SL_u64v4dot(v, n));
}
#else
;
#endif
/// @brief Project u64v2 v on plane with normal u64v2 n
SL_header u64v2 SL_u64v2proj(u64v2 v, u64v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u64v2sub(v, SL_u64v2align(v, n));
}
#else
;
#endif
/// @brief Project u64v3 v on plane with normal u64v3 n
SL_header u64v3 SL_u64v3proj(u64v3 v, u64v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u64v3sub(v, SL_u64v3align(v, n));
}
#else
;
#endif
/// @brief Project u64v4 v on plane with normal u64v4 n
SL_header u64v4 SL_u64v4proj(u64v4 v, u64v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u64v4sub(v, SL_u64v4align(v, n));
}
#else
;
#endif
/// @brief Project u64v2 v on plane with normal u64v2 n
SL_header u64v2 SL_u64v2proj_u(u64v2 v, u64v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u64v2sub(v, SL_u64v2align_u(v, n));
}
#else
;
#endif
/// @brief Project u64v3 v on plane with normal u64v3 n
SL_header u64v3 SL_u64v3proj_u(u64v3 v, u64v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u64v3sub(v, SL_u64v3align_u(v, n));
}
#else
;
#endif
/// @brief Project u64v4 v on plane with normal u64v4 n
SL_header u64v4 SL_u64v4proj_u(u64v4 v, u64v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u64v4sub(v, SL_u64v4align_u(v, n));
}
#else
;
#endif
/// @brief Component-wise modulo of a u64v by scalar n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64* SL_u64vmods_(u64* v, u64 n, u64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = v[i] % n;
    return dest;
}
#else
;
#endif
/// @brief Component-wise modulo of a u64v by scalar n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64v SL_u64vmods(u64v v, u64 n, u64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u64vmods_(v.data, n, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise modulo of a u64v2 by scalar n
SL_header u64v2 SL_u64v2mods(u64v2 v, u64 n)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v2) {
        .x = v.x % n,
        .y = v.y % n
    };
}
#else
;
#endif
/// @brief Component-wise modulo of a u64v3 by scalar n
SL_header u64v3 SL_u64v3mods(u64v3 v, u64 n)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v3) {
        .x = v.x % n,
        .y = v.y % n,
        .z = v.z % n
    };
}
#else
;
#endif
/// @brief Component-wise modulo of a u64v4 by scalar n
SL_header u64v4 SL_u64v4mods(u64v4 v, u64 n)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v4) {
        .x = v.x % n,
        .y = v.y % n,
        .z = v.z % n,
        .w = v.w % n
    };
}
#else
;
#endif
/// @brief Component-wise modulo of a u64v by u64v n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64* SL_u64vmod_(u64* v, u64* n, u64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = v[i] % n[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise modulo of a u64v by u64v n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64v SL_u64vmod(u64v v, u64v n, u64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u64vmod_(v.data, n.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise modulo of a u64v2 by u64v2 n
SL_header u64v2 SL_u64v2mod(u64v2 v, u64v2 n)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v2) {
        .x = v.x % n.x,
        .y = v.y % n.y
    };
}
#else
;
#endif
/// @brief Component-wise modulo of a u64v3 by u64v3 n
SL_header u64v3 SL_u64v3mod(u64v3 v, u64v3 n)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v3) {
        .x = v.x % n.x,
        .y = v.y % n.y,
        .z = v.z % n.z
    };
}
#else
;
#endif
/// @brief Component-wise modulo of a u64v4 by u64v4 n
SL_header u64v4 SL_u64v4mod(u64v4 v, u64v4 n)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v4) {
        .x = v.x % n.x,
        .y = v.y % n.y,
        .z = v.z % n.z,
        .w = v.w % n.w
    };
}
#else
;
#endif
/// @brief Component-wise binary AND of two u64v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64* SL_u64vand_(u64* lhs, u64* rhs, u64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] & rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary AND of two u64v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64v SL_u64vand(u64v lhs, u64v rhs, u64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u64vand_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary AND of two u64v2
SL_header u64v2 SL_u64v2and(u64v2 lhs, u64v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v2) {
        .x = lhs.x & rhs.x,
        .y = lhs.y & rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise binary AND of two u64v3
SL_header u64v3 SL_u64v3and(u64v3 lhs, u64v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v3) {
        .x = lhs.x & rhs.x,
        .y = lhs.y & rhs.y,
        .z = lhs.z & rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise binary AND of two u64v4
SL_header u64v4 SL_u64v4and(u64v4 lhs, u64v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v4) {
        .x = lhs.x & rhs.x,
        .y = lhs.y & rhs.y,
        .z = lhs.z & rhs.z,
        .w = lhs.w & rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise binary OR of two u64v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64* SL_u64vor_(u64* lhs, u64* rhs, u64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] | rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary OR of two u64v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64v SL_u64vor(u64v lhs, u64v rhs, u64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u64vor_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary OR of two u64v2
SL_header u64v2 SL_u64v2or(u64v2 lhs, u64v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v2) {
        .x = lhs.x | rhs.x,
        .y = lhs.y | rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise binary OR of two u64v3
SL_header u64v3 SL_u64v3or(u64v3 lhs, u64v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v3) {
        .x = lhs.x | rhs.x,
        .y = lhs.y | rhs.y,
        .z = lhs.z | rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise binary OR of two u64v4
SL_header u64v4 SL_u64v4or(u64v4 lhs, u64v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v4) {
        .x = lhs.x | rhs.x,
        .y = lhs.y | rhs.y,
        .z = lhs.z | rhs.z,
        .w = lhs.w | rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise binary XOR of two u64v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64* SL_u64vxor_(u64* lhs, u64* rhs, u64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] ^ rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary XOR of two u64v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64v SL_u64vxor(u64v lhs, u64v rhs, u64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u64vxor_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary XOR of two u64v2
SL_header u64v2 SL_u64v2xor(u64v2 lhs, u64v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v2) {
        .x = lhs.x ^ rhs.x,
        .y = lhs.y ^ rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise binary XOR of two u64v3
SL_header u64v3 SL_u64v3xor(u64v3 lhs, u64v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v3) {
        .x = lhs.x ^ rhs.x,
        .y = lhs.y ^ rhs.y,
        .z = lhs.z ^ rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise binary XOR of two u64v4
SL_header u64v4 SL_u64v4xor(u64v4 lhs, u64v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v4) {
        .x = lhs.x ^ rhs.x,
        .y = lhs.y ^ rhs.y,
        .z = lhs.z ^ rhs.z,
        .w = lhs.w ^ rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise binary NOT of a u64v
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64* SL_u64vnot_(u64* v, u64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = ~v[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary NOT of a u64v
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64v SL_u64vnot(u64v v, u64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u64vnot_(v.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary NOT of a u64v2
SL_header u64v2 SL_u64v2not(u64v2 v)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v2) {
        .x = ~v.x,
        .y = ~v.y
    };
}
#else
;
#endif
/// @brief Component-wise binary NOT of a u64v3
SL_header u64v3 SL_u64v3not(u64v3 v)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v3) {
        .x = ~v.x,
        .y = ~v.y,
        .z = ~v.z
    };
}
#else
;
#endif
/// @brief Component-wise binary NOT of a u64v4
SL_header u64v4 SL_u64v4not(u64v4 v)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v4) {
        .x = ~v.x,
        .y = ~v.y,
        .z = ~v.z,
        .w = ~v.w
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a u64v by integer n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64* SL_u64vlshfts_(u64* lhs, u64 rhs, u64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] << rhs;
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a u64v by integer n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64v SL_u64vlshfts(u64v lhs, u64 rhs, u64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u64vlshfts_(lhs.data, rhs, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a u64v2 by integer n
SL_header u64v2 SL_u64v2lshfts(u64v2 lhs, u64 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v2) {
        .x = lhs.x << rhs,
        .y = lhs.y << rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a u64v3 by integer n
SL_header u64v3 SL_u64v3lshfts(u64v3 lhs, u64 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v3) {
        .x = lhs.x << rhs,
        .y = lhs.y << rhs,
        .z = lhs.z << rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a u64v4 by integer n
SL_header u64v4 SL_u64v4lshfts(u64v4 lhs, u64 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v4) {
        .x = lhs.x << rhs,
        .y = lhs.y << rhs,
        .z = lhs.z << rhs,
        .w = lhs.w << rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a u64v by u64v n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64* SL_u64vlshft_(u64* lhs, u64* rhs, u64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] << rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a u64v by u64v n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64v SL_u64vlshft(u64v lhs, u64v rhs, u64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u64vlshft_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a u64v2 by u64v2 n
SL_header u64v2 SL_u64v2lshft(u64v2 lhs, u64v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v2) {
        .x = lhs.x << rhs.x,
        .y = lhs.y << rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a u64v3 by u64v3 n
SL_header u64v3 SL_u64v3lshft(u64v3 lhs, u64v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v3) {
        .x = lhs.x << rhs.x,
        .y = lhs.y << rhs.y,
        .z = lhs.z << rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a u64v4 by u64v4 n
SL_header u64v4 SL_u64v4lshft(u64v4 lhs, u64v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v4) {
        .x = lhs.x << rhs.x,
        .y = lhs.y << rhs.y,
        .z = lhs.z << rhs.z,
        .w = lhs.w << rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a u64v by interger n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64* SL_u64vrshfts_(u64* lhs, u64 rhs, u64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] >> rhs;
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a u64v by interger n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64v SL_u64vrshfts(u64v lhs, u64 rhs, u64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u64vrshfts_(lhs.data, rhs, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a u64v2 by interger n
SL_header u64v2 SL_u64v2rshfts(u64v2 lhs, u64 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v2) {
        .x = lhs.x >> rhs,
        .y = lhs.y >> rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a u64v3 by interger n
SL_header u64v3 SL_u64v3rshfts(u64v3 lhs, u64 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v3) {
        .x = lhs.x >> rhs,
        .y = lhs.y >> rhs,
        .z = lhs.z >> rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a u64v4 by interger n
SL_header u64v4 SL_u64v4rshfts(u64v4 lhs, u64 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v4) {
        .x = lhs.x >> rhs,
        .y = lhs.y >> rhs,
        .z = lhs.z >> rhs,
        .w = lhs.w >> rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a u64v by u64v n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64* SL_u64vrshft_(u64* lhs, u64* rhs, u64* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] >> rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a u64v by u64v n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header u64v SL_u64vrshft(u64v lhs, u64v rhs, u64v dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_u64vrshft_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a u64v2 by u64v2 n
SL_header u64v2 SL_u64v2rshft(u64v2 lhs, u64v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v2) {
        .x = lhs.x >> rhs.x,
        .y = lhs.y >> rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a u64v3 by u64v3 n
SL_header u64v3 SL_u64v3rshft(u64v3 lhs, u64v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v3) {
        .x = lhs.x >> rhs.x,
        .y = lhs.y >> rhs.y,
        .z = lhs.z >> rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a u64v4 by u64v4 n
SL_header u64v4 SL_u64v4rshft(u64v4 lhs, u64v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64v4) {
        .x = lhs.x >> rhs.x,
        .y = lhs.y >> rhs.y,
        .z = lhs.z >> rhs.z,
        .w = lhs.w >> rhs.w
    };
}
#else
;
#endif
#pragma endregion U64
#pragma region FLOAT

/// @brief Vector of float with arbitrary dimension
typedef struct {
    const usize count;
    float *data;
} fv;

/// @brief Vector of float with dimension 2
typedef union {
    float data[2];
    struct {
        union { float x, r, u; };
        union { float y, g, v; };
    };
} fv2;

#define SL_fv2_zero  ((fv2){.x =  0, .y =  0})
#define SL_fv2_one   ((fv2){.x =  1, .y =  1})
#define SL_fv2_right ((fv2){.x =  1, .y =  0})
#define SL_fv2_up    ((fv2){.x =  0, .y =  1})
#define SL_fv2_left  ((fv2){.x = -1, .y =  0})
#define SL_fv2_down  ((fv2){.x =  0, .y = -1})

/// @brief Vector of float with dimension 3
typedef union {
    float data[3];
    struct {
        union { float x, r, u; };
        union { float y, g, v; };
        union { float z, b, s; };
    };
    struct {
        union { float __x, __r, __u; };
        union { fv2 yz, gb, vs; };
    };
    struct {
        union { fv2 xy, rg, uv; };
        union { float __z, __b, __s; };
    };
} fv3;

#define SL_fv3_zero  ((fv3){.x =  0, .y =  0, .z =  0})
#define SL_fv3_one   ((fv3){.x =  1, .y =  1, .z =  1})
#define SL_fv3_right ((fv3){.x =  1, .y =  0, .z =  0})
#define SL_fv3_up    ((fv3){.x =  0, .y =  1, .z =  0})
#define SL_fv3_forw  ((fv3){.x =  0, .y =  0, .z =  1})
#define SL_fv3_left  ((fv3){.x = -1, .y =  0, .z =  0})
#define SL_fv3_down  ((fv3){.x =  0, .y = -1, .z =  0})
#define SL_fv3_back  ((fv3){.x =  0, .y =  0, .z = -1})

/// @brief Vector of float with dimension 4
typedef union {
    float data[4];
    struct {
        union { float x, r, u; };
        union { float y, g, v; };
        union { float z, b, s; };
        union { float w, a, t; };
    };
    struct {
        union { float __x0, __r0, __u0; };
        union { fv2 yz, gb, vs; };
        union { float __w0, __a0, __t0; };
    };
    struct {
        union { fv2 xy, rb, uv; };
        union { fv2 zw, ba, st; };
    };
    struct {
        union { fv3 xyz, rgb, uvs; };
        union { float __w1, __a1, __t1; };
    };
    struct {
        union { float __x1, __r1, __u1; };
        union { fv3 yzw, gba, vst; };
    };
} fv4;

#define SL_fv4_zero  ((fv4){.x = 0, .y = 0, .z = 0, .w = 0})
#define SL_fv4_one   ((fv4){.x = 1, .y = 1, .z = 1, .w = 1})

#define SL_fv4_white  ((fv4){.x = 1, .y = 1, .z = 1, .w = 1})
#define SL_fv4_black  ((fv4){.x = 0, .y = 0, .z = 0, .w = 1})
#define SL_fv4_red    ((fv4){.x = 1, .y = 0, .z = 0, .w = 1})
#define SL_fv4_green  ((fv4){.x = 0, .y = 1, .z = 0, .w = 1})
#define SL_fv4_blue   ((fv4){.x = 0, .y = 0, .z = 1, .w = 1})
#define SL_fv4_yellow ((fv4){.x = 1, .y = 1, .z = 0, .w = 1})
#define SL_fv4_cyan   ((fv4){.x = 0, .y = 1, .z = 1, .w = 1})
#define SL_fv4_purple ((fv4){.x = 1, .y = 0, .z = 1, .w = 1})



#define SL_fv2_(X, Y)       ((fv2){.x = X, .y = Y})
#define SL_fv3_(X, Y, Z)    ((fv3){.x = X, .y = Y, .z = Z})
#define SL_fv4_(X, Y, Z, W) ((fv4){.x = X, .y = Y, .z = Z, .w = W})

#define SL_fv2s(S)          ((fv2){.x = S, .y = S})
#define SL_fv3s(S)          ((fv3){.x = S, .y = S, .z = S})
#define SL_fv4s(S)          ((fv4){.x = S, .y = S, .z = S, .w = S})

#define SL_fvv(V)           ((fv){.count = vsize(V), .data = (V).data})
#define SL_fv2v(V, ...)     ((fv2){.x = (V).x, .y = (V).y})
#define SL_fv3v(V, ...)     ((fv3){.x = (V).x, .y = (V).y, .z = (SL_vsize(V) >= 3 ? (V).data[2] : (0, ##__VA_ARGS__))})
#define SL_fv4v(V, ...)     ((fv4){.x = (V).x, .y = (V).y, .z = (SL_vsize(V) >= 3 ? (V).data[2] : ((const float[]){0, ##__VA_ARGS__, 0})[1]), .w = (SL_vsize(V) >= 4 ? (V).data[3] : ((const float[]){0, ##__VA_ARGS__, 0, 0})[2])})



/// @brief Equality of two fv
/// @note All vectors are assumed to be of size 'count'
SL_header bool SL_fvequ_(float* lhs, float* rhs, usize count)
#if defined(SL_IMPLEMENTATION)
{
    bool dest = true;
    for (usize i = 0; i < count; ++i) dest &= lhs[i] == rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Equality of two fv
/// @note All vectors are assumed to be of size 'count'
SL_header bool SL_fvequ(fv lhs, fv rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_fvequ_(lhs.data, rhs.data, lhs.count);
}
#else
;
#endif
/// @brief Equality of two fv2
SL_header bool SL_fv2equ(fv2 lhs, fv2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}
#else
;
#endif
/// @brief Equality of two fv3
SL_header bool SL_fv3equ(fv3 lhs, fv3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}
#else
;
#endif
/// @brief Equality of two fv4
SL_header bool SL_fv4equ(fv4 lhs, fv4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
}
#else
;
#endif
/// @brief Addition of two fv
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header float* SL_fvadd_(float* lhs, float* rhs, float* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] + rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Addition of two fv
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header fv SL_fvadd(fv lhs, fv rhs, fv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_fvadd_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two fv2
SL_header fv2 SL_fv2add(fv2 lhs, fv2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (fv2) {
        .x = lhs.x + rhs.x,
        .y = lhs.y + rhs.y
    };
}
#else
;
#endif
/// @brief Addition of two fv3
SL_header fv3 SL_fv3add(fv3 lhs, fv3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (fv3) {
        .x = lhs.x + rhs.x,
        .y = lhs.y + rhs.y,
        .z = lhs.z + rhs.z
    };
}
#else
;
#endif
/// @brief Addition of two fv4
SL_header fv4 SL_fv4add(fv4 lhs, fv4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (fv4) {
        .x = lhs.x + rhs.x,
        .y = lhs.y + rhs.y,
        .z = lhs.z + rhs.z,
        .w = lhs.w + rhs.w
    };
}
#else
;
#endif
/// @brief Difference of two fv
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header float* SL_fvsub_(float* lhs, float* rhs, float* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] - rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Difference of two fv
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header fv SL_fvsub(fv lhs, fv rhs, fv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_fvsub_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two fv2
SL_header fv2 SL_fv2sub(fv2 lhs, fv2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (fv2) {
        .x = lhs.x - rhs.x,
        .y = lhs.y - rhs.y
    };
}
#else
;
#endif
/// @brief Difference of two fv3
SL_header fv3 SL_fv3sub(fv3 lhs, fv3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (fv3) {
        .x = lhs.x - rhs.x,
        .y = lhs.y - rhs.y,
        .z = lhs.z - rhs.z
    };
}
#else
;
#endif
/// @brief Difference of two fv4
SL_header fv4 SL_fv4sub(fv4 lhs, fv4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (fv4) {
        .x = lhs.x - rhs.x,
        .y = lhs.y - rhs.y,
        .z = lhs.z - rhs.z,
        .w = lhs.w - rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of two fv
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header float* SL_fvmul_(float* lhs, float* rhs, float* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise multiplication of two fv
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header fv SL_fvmul(fv lhs, fv rhs, fv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_fvmul_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise multiplication of two fv2
SL_header fv2 SL_fv2mul(fv2 lhs, fv2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (fv2) {
        .x = lhs.x * rhs.x,
        .y = lhs.y * rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of two fv3
SL_header fv3 SL_fv3mul(fv3 lhs, fv3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (fv3) {
        .x = lhs.x * rhs.x,
        .y = lhs.y * rhs.y,
        .z = lhs.z * rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of two fv4
SL_header fv4 SL_fv4mul(fv4 lhs, fv4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (fv4) {
        .x = lhs.x * rhs.x,
        .y = lhs.y * rhs.y,
        .z = lhs.z * rhs.z,
        .w = lhs.w * rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of a fv with a scalar
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header float* SL_fvmuls_(float* lhs, float rhs, float* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * rhs;
    return dest;
}
#else
;
#endif
/// @brief Component-wise multiplication of a fv with a scalar
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header fv SL_fvmuls(fv lhs, float rhs, fv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_fvmuls_(lhs.data, rhs, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise multiplication of a fv2 with a scalar
SL_header fv2 SL_fv2muls(fv2 lhs, float rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (fv2) {
        .x = lhs.x * rhs,
        .y = lhs.y * rhs
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of a fv3 with a scalar
SL_header fv3 SL_fv3muls(fv3 lhs, float rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (fv3) {
        .x = lhs.x * rhs,
        .y = lhs.y * rhs,
        .z = lhs.z * rhs
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of a fv4 with a scalar
SL_header fv4 SL_fv4muls(fv4 lhs, float rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (fv4) {
        .x = lhs.x * rhs,
        .y = lhs.y * rhs,
        .z = lhs.z * rhs,
        .w = lhs.w * rhs
    };
}
#else
;
#endif
/// @brief Component-wise division of two fv
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header float* SL_fvdiv_(float* lhs, float* rhs, float* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] / rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise division of two fv
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header fv SL_fvdiv(fv lhs, fv rhs, fv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_fvdiv_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise division of two fv2
SL_header fv2 SL_fv2div(fv2 lhs, fv2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (fv2) {
        .x = lhs.x / rhs.x,
        .y = lhs.y / rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise division of two fv3
SL_header fv3 SL_fv3div(fv3 lhs, fv3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (fv3) {
        .x = lhs.x / rhs.x,
        .y = lhs.y / rhs.y,
        .z = lhs.z / rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise division of two fv4
SL_header fv4 SL_fv4div(fv4 lhs, fv4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (fv4) {
        .x = lhs.x / rhs.x,
        .y = lhs.y / rhs.y,
        .z = lhs.z / rhs.z,
        .w = lhs.w / rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise division of a fv with a scalar
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header float* SL_fvdivs_(float* lhs, float rhs, float* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] / rhs;
    return dest;
}
#else
;
#endif
/// @brief Component-wise division of a fv with a scalar
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header fv SL_fvdivs(fv lhs, float rhs, fv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_fvdivs_(lhs.data, rhs, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise division of a fv2 with a scalar
SL_header fv2 SL_fv2divs(fv2 lhs, float rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (fv2) {
        .x = lhs.x / rhs,
        .y = lhs.y / rhs
    };
}
#else
;
#endif
/// @brief Component-wise division of a fv3 with a scalar
SL_header fv3 SL_fv3divs(fv3 lhs, float rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (fv3) {
        .x = lhs.x / rhs,
        .y = lhs.y / rhs,
        .z = lhs.z / rhs
    };
}
#else
;
#endif
/// @brief Component-wise division of a fv4 with a scalar
SL_header fv4 SL_fv4divs(fv4 lhs, float rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (fv4) {
        .x = lhs.x / rhs,
        .y = lhs.y / rhs,
        .z = lhs.z / rhs,
        .w = lhs.w / rhs
    };
}
#else
;
#endif
/// @brief Addition of two fv with lhs scaled by a float
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header float* SL_fvaddS_(float* lhs, float* rhs, float s, float* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] + rhs[i] * s;
    return dest;
}
#else
;
#endif
/// @brief Addition of two fv with lhs scaled by a float
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header fv SL_fvaddS(fv lhs, fv rhs, float s, fv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_fvaddS_(lhs.data, rhs.data, s, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two fv2 with lhs scaled by a float
SL_header fv2 SL_fv2addS(fv2 lhs, fv2 rhs, float s)
#if defined(SL_IMPLEMENTATION)
{
    return (fv2) {
        .x = lhs.x + rhs.x * s,
        .y = lhs.y + rhs.y * s
    };
}
#else
;
#endif
/// @brief Addition of two fv3 with lhs scaled by a float
SL_header fv3 SL_fv3addS(fv3 lhs, fv3 rhs, float s)
#if defined(SL_IMPLEMENTATION)
{
    return (fv3) {
        .x = lhs.x + rhs.x * s,
        .y = lhs.y + rhs.y * s,
        .z = lhs.z + rhs.z * s
    };
}
#else
;
#endif
/// @brief Addition of two fv4 with lhs scaled by a float
SL_header fv4 SL_fv4addS(fv4 lhs, fv4 rhs, float s)
#if defined(SL_IMPLEMENTATION)
{
    return (fv4) {
        .x = lhs.x + rhs.x * s,
        .y = lhs.y + rhs.y * s,
        .z = lhs.z + rhs.z * s,
        .w = lhs.w + rhs.w * s
    };
}
#else
;
#endif
/// @brief Difference of two fv with lhs scaled by a float
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header float* SL_fvsubS_(float* lhs, float* rhs, float s, float* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] - rhs[i] * s;
    return dest;
}
#else
;
#endif
/// @brief Difference of two fv with lhs scaled by a float
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header fv SL_fvsubS(fv lhs, fv rhs, float s, fv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_fvsubS_(lhs.data, rhs.data, s, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two fv2 with lhs scaled by a float
SL_header fv2 SL_fv2subS(fv2 lhs, fv2 rhs, float s)
#if defined(SL_IMPLEMENTATION)
{
    return (fv2) {
        .x = lhs.x - rhs.x * s,
        .y = lhs.y - rhs.y * s
    };
}
#else
;
#endif
/// @brief Difference of two fv3 with lhs scaled by a float
SL_header fv3 SL_fv3subS(fv3 lhs, fv3 rhs, float s)
#if defined(SL_IMPLEMENTATION)
{
    return (fv3) {
        .x = lhs.x - rhs.x * s,
        .y = lhs.y - rhs.y * s,
        .z = lhs.z - rhs.z * s
    };
}
#else
;
#endif
/// @brief Difference of two fv4 with lhs scaled by a float
SL_header fv4 SL_fv4subS(fv4 lhs, fv4 rhs, float s)
#if defined(SL_IMPLEMENTATION)
{
    return (fv4) {
        .x = lhs.x - rhs.x * s,
        .y = lhs.y - rhs.y * s,
        .z = lhs.z - rhs.z * s,
        .w = lhs.w - rhs.w * s
    };
}
#else
;
#endif
/// @brief Addition of two fv with lhs multiplied with a float
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header float* SL_fvaddM_(float* lhs, float* rhs, float* m, float* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] + rhs[i] * m[i];
    return dest;
}
#else
;
#endif
/// @brief Addition of two fv with lhs multiplied with a float
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header fv SL_fvaddM(fv lhs, fv rhs, fv m, fv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_fvaddM_(lhs.data, rhs.data, m.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two fv2 with lhs multiplied with a float
SL_header fv2 SL_fv2addM(fv2 lhs, fv2 rhs, fv2 m)
#if defined(SL_IMPLEMENTATION)
{
    return (fv2) {
        .x = lhs.x + rhs.x * m.x,
        .y = lhs.y + rhs.y * m.y
    };
}
#else
;
#endif
/// @brief Addition of two fv3 with lhs multiplied with a float
SL_header fv3 SL_fv3addM(fv3 lhs, fv3 rhs, fv3 m)
#if defined(SL_IMPLEMENTATION)
{
    return (fv3) {
        .x = lhs.x + rhs.x * m.x,
        .y = lhs.y + rhs.y * m.y,
        .z = lhs.z + rhs.z * m.z
    };
}
#else
;
#endif
/// @brief Addition of two fv4 with lhs multiplied with a float
SL_header fv4 SL_fv4addM(fv4 lhs, fv4 rhs, fv4 m)
#if defined(SL_IMPLEMENTATION)
{
    return (fv4) {
        .x = lhs.x + rhs.x * m.x,
        .y = lhs.y + rhs.y * m.y,
        .z = lhs.z + rhs.z * m.z,
        .w = lhs.w + rhs.w * m.w
    };
}
#else
;
#endif
/// @brief Difference of two fv with lhs multiplied with a float
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header float* SL_fvsubM_(float* lhs, float* rhs, float* m, float* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] - rhs[i] * m[i];
    return dest;
}
#else
;
#endif
/// @brief Difference of two fv with lhs multiplied with a float
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header fv SL_fvsubM(fv lhs, fv rhs, fv m, fv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_fvsubM_(lhs.data, rhs.data, m.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two fv2 with lhs multiplied with a float
SL_header fv2 SL_fv2subM(fv2 lhs, fv2 rhs, fv2 m)
#if defined(SL_IMPLEMENTATION)
{
    return (fv2) {
        .x = lhs.x - rhs.x * m.x,
        .y = lhs.y - rhs.y * m.y
    };
}
#else
;
#endif
/// @brief Difference of two fv3 with lhs multiplied with a float
SL_header fv3 SL_fv3subM(fv3 lhs, fv3 rhs, fv3 m)
#if defined(SL_IMPLEMENTATION)
{
    return (fv3) {
        .x = lhs.x - rhs.x * m.x,
        .y = lhs.y - rhs.y * m.y,
        .z = lhs.z - rhs.z * m.z
    };
}
#else
;
#endif
/// @brief Difference of two fv4 with lhs multiplied with a float
SL_header fv4 SL_fv4subM(fv4 lhs, fv4 rhs, fv4 m)
#if defined(SL_IMPLEMENTATION)
{
    return (fv4) {
        .x = lhs.x - rhs.x * m.x,
        .y = lhs.y - rhs.y * m.y,
        .z = lhs.z - rhs.z * m.z,
        .w = lhs.w - rhs.w * m.w
    };
}
#else
;
#endif
/// @brief Addition of two fv with lhs scaled by float and multiplied with a float
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header float* SL_fvaddSM_(float* lhs, float* rhs, float s, float* m, float* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] + rhs[i] * s * m[i];
    return dest;
}
#else
;
#endif
/// @brief Addition of two fv with lhs scaled by float and multiplied with a float
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header fv SL_fvaddSM(fv lhs, fv rhs, float s, fv m, fv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_fvaddSM_(lhs.data, rhs.data, s, m.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two fv2 with lhs scaled by float and multiplied with a float
SL_header fv2 SL_fv2addSM(fv2 lhs, fv2 rhs, float s, fv2 m)
#if defined(SL_IMPLEMENTATION)
{
    return (fv2) {
        .x = lhs.x + rhs.x * s * m.x,
        .y = lhs.y + rhs.y * s * m.y
    };
}
#else
;
#endif
/// @brief Addition of two fv3 with lhs scaled by float and multiplied with a float
SL_header fv3 SL_fv3addSM(fv3 lhs, fv3 rhs, float s, fv3 m)
#if defined(SL_IMPLEMENTATION)
{
    return (fv3) {
        .x = lhs.x + rhs.x * s * m.x,
        .y = lhs.y + rhs.y * s * m.y,
        .z = lhs.z + rhs.z * s * m.z
    };
}
#else
;
#endif
/// @brief Addition of two fv4 with lhs scaled by float and multiplied with a float
SL_header fv4 SL_fv4addSM(fv4 lhs, fv4 rhs, float s, fv4 m)
#if defined(SL_IMPLEMENTATION)
{
    return (fv4) {
        .x = lhs.x + rhs.x * s * m.x,
        .y = lhs.y + rhs.y * s * m.y,
        .z = lhs.z + rhs.z * s * m.z,
        .w = lhs.w + rhs.w * s * m.w
    };
}
#else
;
#endif
/// @brief Difference of two fv with lhs scaled by float and multiplied with a float
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header float* SL_fvsubSM_(float* lhs, float* rhs, float s, float* m, float* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] - rhs[i] * s * m[i];
    return dest;
}
#else
;
#endif
/// @brief Difference of two fv with lhs scaled by float and multiplied with a float
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header fv SL_fvsubSM(fv lhs, fv rhs, float s, fv m, fv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_fvsubSM_(lhs.data, rhs.data, s, m.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two fv2 with lhs scaled by float and multiplied with a float
SL_header fv2 SL_fv2subSM(fv2 lhs, fv2 rhs, float s, fv2 m)
#if defined(SL_IMPLEMENTATION)
{
    return (fv2) {
        .x = lhs.x - rhs.x * s * m.x,
        .y = lhs.y - rhs.y * s * m.y
    };
}
#else
;
#endif
/// @brief Difference of two fv3 with lhs scaled by float and multiplied with a float
SL_header fv3 SL_fv3subSM(fv3 lhs, fv3 rhs, float s, fv3 m)
#if defined(SL_IMPLEMENTATION)
{
    return (fv3) {
        .x = lhs.x - rhs.x * s * m.x,
        .y = lhs.y - rhs.y * s * m.y,
        .z = lhs.z - rhs.z * s * m.z
    };
}
#else
;
#endif
/// @brief Difference of two fv4 with lhs scaled by float and multiplied with a float
SL_header fv4 SL_fv4subSM(fv4 lhs, fv4 rhs, float s, fv4 m)
#if defined(SL_IMPLEMENTATION)
{
    return (fv4) {
        .x = lhs.x - rhs.x * s * m.x,
        .y = lhs.y - rhs.y * s * m.y,
        .z = lhs.z - rhs.z * s * m.z,
        .w = lhs.w - rhs.w * s * m.w
    };
}
#else
;
#endif
/// @brief Addition of two fv with rhs scaled by a float
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header float* SL_fvSadd_(float* lhs, float s, float* rhs, float* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * s + rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Addition of two fv with rhs scaled by a float
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header fv SL_fvSadd(fv lhs, float s, fv rhs, fv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_fvSadd_(lhs.data, s, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two fv2 with rhs scaled by a float
SL_header fv2 SL_fv2Sadd(fv2 lhs, float s, fv2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (fv2) {
        .x = lhs.x * s + rhs.x,
        .y = lhs.y * s + rhs.y
    };
}
#else
;
#endif
/// @brief Addition of two fv3 with rhs scaled by a float
SL_header fv3 SL_fv3Sadd(fv3 lhs, float s, fv3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (fv3) {
        .x = lhs.x * s + rhs.x,
        .y = lhs.y * s + rhs.y,
        .z = lhs.z * s + rhs.z
    };
}
#else
;
#endif
/// @brief Addition of two fv4 with rhs scaled by a float
SL_header fv4 SL_fv4Sadd(fv4 lhs, float s, fv4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (fv4) {
        .x = lhs.x * s + rhs.x,
        .y = lhs.y * s + rhs.y,
        .z = lhs.z * s + rhs.z,
        .w = lhs.w * s + rhs.w
    };
}
#else
;
#endif
/// @brief Difference of two fv with rhs scaled by a float
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header float* SL_fvSsub_(float* lhs, float s, float* rhs, float* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * s - rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Difference of two fv with rhs scaled by a float
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header fv SL_fvSsub(fv lhs, float s, fv rhs, fv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_fvSsub_(lhs.data, s, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two fv2 with rhs scaled by a float
SL_header fv2 SL_fv2Ssub(fv2 lhs, float s, fv2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (fv2) {
        .x = lhs.x * s - rhs.x,
        .y = lhs.y * s - rhs.y
    };
}
#else
;
#endif
/// @brief Difference of two fv3 with rhs scaled by a float
SL_header fv3 SL_fv3Ssub(fv3 lhs, float s, fv3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (fv3) {
        .x = lhs.x * s - rhs.x,
        .y = lhs.y * s - rhs.y,
        .z = lhs.z * s - rhs.z
    };
}
#else
;
#endif
/// @brief Difference of two fv4 with rhs scaled by a float
SL_header fv4 SL_fv4Ssub(fv4 lhs, float s, fv4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (fv4) {
        .x = lhs.x * s - rhs.x,
        .y = lhs.y * s - rhs.y,
        .z = lhs.z * s - rhs.z,
        .w = lhs.w * s - rhs.w
    };
}
#else
;
#endif
/// @brief Weighted sum of two fv
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header float* SL_fvmix_(float* lhs, float lhs_w, float* rhs, float rhs_w, float* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * lhs_w + rhs[i] * rhs_w;
    return dest;
}
#else
;
#endif
/// @brief Weighted sum of two fv
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header fv SL_fvmix(fv lhs, float lhs_w, fv rhs, float rhs_w, fv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_fvmix_(lhs.data, lhs_w, rhs.data, rhs_w, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Weighted sum of two fv2
SL_header fv2 SL_fv2mix(fv2 lhs, float lhs_w, fv2 rhs, float rhs_w)
#if defined(SL_IMPLEMENTATION)
{
    return (fv2) {
        .x = lhs.x * lhs_w + rhs.x * rhs_w,
        .y = lhs.y * lhs_w + rhs.y * rhs_w
    };
}
#else
;
#endif
/// @brief Weighted sum of two fv3
SL_header fv3 SL_fv3mix(fv3 lhs, float lhs_w, fv3 rhs, float rhs_w)
#if defined(SL_IMPLEMENTATION)
{
    return (fv3) {
        .x = lhs.x * lhs_w + rhs.x * rhs_w,
        .y = lhs.y * lhs_w + rhs.y * rhs_w,
        .z = lhs.z * lhs_w + rhs.z * rhs_w
    };
}
#else
;
#endif
/// @brief Weighted sum of two fv4
SL_header fv4 SL_fv4mix(fv4 lhs, float lhs_w, fv4 rhs, float rhs_w)
#if defined(SL_IMPLEMENTATION)
{
    return (fv4) {
        .x = lhs.x * lhs_w + rhs.x * rhs_w,
        .y = lhs.y * lhs_w + rhs.y * rhs_w,
        .z = lhs.z * lhs_w + rhs.z * rhs_w,
        .w = lhs.w * lhs_w + rhs.w * rhs_w
    };
}
#else
;
#endif
/// @brief Negation of a fv
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header float* SL_fvneg_(float* v, float* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = -v[i];
    return dest;
}
#else
;
#endif
/// @brief Negation of a fv
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header fv SL_fvneg(fv v, fv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_fvneg_(v.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Negation of a fv2
SL_header fv2 SL_fv2neg(fv2 v)
#if defined(SL_IMPLEMENTATION)
{
    return (fv2) {
        .x = -v.x,
        .y = -v.y
    };
}
#else
;
#endif
/// @brief Negation of a fv3
SL_header fv3 SL_fv3neg(fv3 v)
#if defined(SL_IMPLEMENTATION)
{
    return (fv3) {
        .x = -v.x,
        .y = -v.y,
        .z = -v.z
    };
}
#else
;
#endif
/// @brief Negation of a fv4
SL_header fv4 SL_fv4neg(fv4 v)
#if defined(SL_IMPLEMENTATION)
{
    return (fv4) {
        .x = -v.x,
        .y = -v.y,
        .z = -v.z,
        .w = -v.w
    };
}
#else
;
#endif
/// @brief Component-wise absolute value of a fv
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header float* SL_fvabs_(float* v, float* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = fabs(v[i]);
    return dest;
}
#else
;
#endif
/// @brief Component-wise absolute value of a fv
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header fv SL_fvabs(fv v, fv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_fvabs_(v.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise absolute value of a fv2
SL_header fv2 SL_fv2abs(fv2 v)
#if defined(SL_IMPLEMENTATION)
{
    return (fv2) {
        .x = fabs(v.x),
        .y = fabs(v.y)
    };
}
#else
;
#endif
/// @brief Component-wise absolute value of a fv3
SL_header fv3 SL_fv3abs(fv3 v)
#if defined(SL_IMPLEMENTATION)
{
    return (fv3) {
        .x = fabs(v.x),
        .y = fabs(v.y),
        .z = fabs(v.z)
    };
}
#else
;
#endif
/// @brief Component-wise absolute value of a fv4
SL_header fv4 SL_fv4abs(fv4 v)
#if defined(SL_IMPLEMENTATION)
{
    return (fv4) {
        .x = fabs(v.x),
        .y = fabs(v.y),
        .z = fabs(v.z),
        .w = fabs(v.w)
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two fv
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header float* SL_fvmin_(float* lhs, float* rhs, float* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] < rhs[i] ? lhs[i] : rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise minimum of two fv
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header fv SL_fvmin(fv lhs, fv rhs, fv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_fvmin_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise minimum of two fv2
SL_header fv2 SL_fv2min(fv2 lhs, fv2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (fv2) {
        .x = lhs.x < rhs.x ? lhs.x : rhs.x,
        .y = lhs.y < rhs.y ? lhs.y : rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two fv3
SL_header fv3 SL_fv3min(fv3 lhs, fv3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (fv3) {
        .x = lhs.x < rhs.x ? lhs.x : rhs.x,
        .y = lhs.y < rhs.y ? lhs.y : rhs.y,
        .z = lhs.z < rhs.z ? lhs.z : rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two fv4
SL_header fv4 SL_fv4min(fv4 lhs, fv4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (fv4) {
        .x = lhs.x < rhs.x ? lhs.x : rhs.x,
        .y = lhs.y < rhs.y ? lhs.y : rhs.y,
        .z = lhs.z < rhs.z ? lhs.z : rhs.z,
        .w = lhs.w < rhs.w ? lhs.w : rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two fv
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header float* SL_fvmax_(float* lhs, float* rhs, float* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] > rhs[i] ? lhs[i] : rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise maximum of two fv
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header fv SL_fvmax(fv lhs, fv rhs, fv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_fvmax_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise maximum of two fv2
SL_header fv2 SL_fv2max(fv2 lhs, fv2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (fv2) {
        .x = lhs.x > rhs.x ? lhs.x : rhs.x,
        .y = lhs.y > rhs.y ? lhs.y : rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two fv3
SL_header fv3 SL_fv3max(fv3 lhs, fv3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (fv3) {
        .x = lhs.x > rhs.x ? lhs.x : rhs.x,
        .y = lhs.y > rhs.y ? lhs.y : rhs.y,
        .z = lhs.z > rhs.z ? lhs.z : rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two fv4
SL_header fv4 SL_fv4max(fv4 lhs, fv4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (fv4) {
        .x = lhs.x > rhs.x ? lhs.x : rhs.x,
        .y = lhs.y > rhs.y ? lhs.y : rhs.y,
        .z = lhs.z > rhs.z ? lhs.z : rhs.z,
        .w = lhs.w > rhs.w ? lhs.w : rhs.w
    };
}
#else
;
#endif
/// @brief Dot product of two fv
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_fvdot_(float* lhs, float* rhs, usize count)
#if defined(SL_IMPLEMENTATION)
{
    double dest = 0;
    for (usize i = 0; i < count; ++i) dest += lhs[i] * rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Dot product of two fv
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_fvdot(fv lhs, fv rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_fvdot_(lhs.data, rhs.data, lhs.count);
}
#else
;
#endif
/// @brief Dot product of two fv2
SL_header double SL_fv2dot(fv2 lhs, fv2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}
#else
;
#endif
/// @brief Dot product of two fv3
SL_header double SL_fv3dot(fv3 lhs, fv3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}
#else
;
#endif
/// @brief Dot product of two fv4
SL_header double SL_fv4dot(fv4 lhs, fv4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}
#else
;
#endif
/// @brief Maximum component of a fv
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_fvlen_max_(float* v, usize count)
#if defined(SL_IMPLEMENTATION)
{
    double dest = 0;
    for (usize i = 0; i < count; ++i) dest = fabs(v[i]) > dest ? fabs(v[i]) : dest;
    return dest;
}
#else
;
#endif
/// @brief Maximum component of a fv
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_fvlen_max(fv v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_fvlen_max_(v.data, v.count);
}
#else
;
#endif
/// @brief Maximum component of a fv2
SL_header double SL_fv2len_max(fv2 v)
#if defined(SL_IMPLEMENTATION)
{
    v = SL_fv2abs(v);
    return v.x > v.y ? v.x : v.y;
}
#else
;
#endif
/// @brief Maximum component of a fv3
SL_header double SL_fv3len_max(fv3 v)
#if defined(SL_IMPLEMENTATION)
{
    v = SL_fv3abs(v);
    return v.x > v.y ? (v.x > v.z ? v.x : v.z) : (v.y > v.z ? v.y : v.z);
}
#else
;
#endif
/// @brief Maximum component of a fv4
SL_header double SL_fv4len_max(fv4 v)
#if defined(SL_IMPLEMENTATION)
{
    v = SL_fv4abs(v);
    return v.x > v.y ? (v.x > v.z ? (v.x > v.w ? v.x : v.w) : (v.z > v.w ? v.z : v.w)) : (v.y > v.z ? (v.y > v.w ? v.y : v.w) : (v.z > v.w ? v.z : v.w));
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a fv
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_fvlen_manh_(float* v, usize count)
#if defined(SL_IMPLEMENTATION)
{
    double dest = 0;
    for (usize i = 0; i < count; ++i) dest += fabs(v[i]);
    return dest;
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a fv
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_fvlen_manh(fv v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_fvlen_manh_(v.data, v.count);
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a fv2
SL_header double SL_fv2len_manh(fv2 v)
#if defined(SL_IMPLEMENTATION)
{
    v = SL_fv2abs(v);
    return v.x + v.y;
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a fv3
SL_header double SL_fv3len_manh(fv3 v)
#if defined(SL_IMPLEMENTATION)
{
    v = SL_fv3abs(v);
    return v.x + v.y + v.z;
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a fv4
SL_header double SL_fv4len_manh(fv4 v)
#if defined(SL_IMPLEMENTATION)
{
    v = SL_fv4abs(v);
    return v.x + v.y + v.z + v.w;
}
#else
;
#endif
/// @brief Squared euclidean length of a fv
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_fvlen_srq_(float* v, usize count)
#if defined(SL_IMPLEMENTATION)
{
    return SL_fvdot_(v, v, count);
}
#else
;
#endif
/// @brief Squared euclidean length of a fv
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_fvlen_srq(fv v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_fvlen_srq_(v.data, v.count);
}
#else
;
#endif
/// @brief Square length of a fv2
SL_header double SL_fv2len_sqr(fv2 v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_fv2dot(v, v);
}
#else
;
#endif
/// @brief Square length of a fv3
SL_header double SL_fv3len_sqr(fv3 v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_fv3dot(v, v);
}
#else
;
#endif
/// @brief Square length of a fv4
SL_header double SL_fv4len_sqr(fv4 v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_fv4dot(v, v);
}
#else
;
#endif
/// @brief Euclidean length of a fv
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_fvlen_(float* v, usize count)
#if defined(SL_IMPLEMENTATION)
{
    return sqrt(SL_fvdot_(v, v, count));
}
#else
;
#endif
/// @brief Euclidean length of a fv
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_fvlen(fv v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_fvlen_(v.data, v.count);
}
#else
;
#endif
/// @brief Euclidean length of a fv2
SL_header double SL_fv2len(fv2 v)
#if defined(SL_IMPLEMENTATION)
{
    return sqrt(SL_fv2dot(v, v));
}
#else
;
#endif
/// @brief Euclidean length of a fv3
SL_header double SL_fv3len(fv3 v)
#if defined(SL_IMPLEMENTATION)
{
    return sqrt(SL_fv3dot(v, v));
}
#else
;
#endif
/// @brief Euclidean length of a fv4
SL_header double SL_fv4len(fv4 v)
#if defined(SL_IMPLEMENTATION)
{
    return sqrt(SL_fv4dot(v, v));
}
#else
;
#endif
/// @brief Euclidean distance bewteen two fv
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_fvdist_(float* lhs, float* rhs, usize count)
#if defined(SL_IMPLEMENTATION)
{
    double accum = 0;
    for (int i = 0; i < count; ++i) accum += (lhs[i] - rhs[i]) * (lhs[i] - rhs[i]);
    return sqrt(accum);
}
#else
;
#endif
/// @brief Euclidean distance bewteen two fv
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_fvdist(fv lhs, fv rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_fvdist_(lhs.data, rhs.data, lhs.count);
}
#else
;
#endif
/// @brief Euclidean distance between two fv2
SL_header double SL_fv2dist(fv2 lhs, fv2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_fv2len(SL_fv2sub(lhs, rhs));
}
#else
;
#endif
/// @brief Euclidean distance between two fv3
SL_header double SL_fv3dist(fv3 lhs, fv3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_fv3len(SL_fv3sub(lhs, rhs));
}
#else
;
#endif
/// @brief Euclidean distance between two fv4
SL_header double SL_fv4dist(fv4 lhs, fv4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_fv4len(SL_fv4sub(lhs, rhs));
}
#else
;
#endif
/// @brief Reflection of fv2 v around vector fv2 n
SL_header fv2 SL_fv2refl(fv2 v, fv2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_fv2subS(v, n, 2.0 * SL_fv2dot(v, n) / SL_fv2dot(n, n));
}
#else
;
#endif
/// @brief Reflection of fv3 v around vector fv3 n
SL_header fv3 SL_fv3refl(fv3 v, fv3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_fv3subS(v, n, 2.0 * SL_fv3dot(v, n) / SL_fv3dot(n, n));
}
#else
;
#endif
/// @brief Reflection of fv4 v around vector fv4 n
SL_header fv4 SL_fv4refl(fv4 v, fv4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_fv4subS(v, n, 2.0 * SL_fv4dot(v, n) / SL_fv4dot(n, n));
}
#else
;
#endif
/// @brief Reflection of fv2 v around vector fv2 n assumed to be of unit length
SL_header fv2 SL_fv2refl_u(fv2 v, fv2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_fv2subS(v, n, 2.0 * SL_fv2dot(v, n));
}
#else
;
#endif
/// @brief Reflection of fv3 v around vector fv3 n assumed to be of unit length
SL_header fv3 SL_fv3refl_u(fv3 v, fv3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_fv3subS(v, n, 2.0 * SL_fv3dot(v, n));
}
#else
;
#endif
/// @brief Reflection of fv4 v around vector fv4 n assumed to be of unit length
SL_header fv4 SL_fv4refl_u(fv4 v, fv4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_fv4subS(v, n, 2.0 * SL_fv4dot(v, n));
}
#else
;
#endif
/// @brief Get component of fv2 v in direction fv2 n
SL_header fv2 SL_fv2align(fv2 v, fv2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_fv2muls(n, SL_fv2dot(v, n) / SL_fv2dot(n, n));
}
#else
;
#endif
/// @brief Get component of fv3 v in direction fv3 n
SL_header fv3 SL_fv3align(fv3 v, fv3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_fv3muls(n, SL_fv3dot(v, n) / SL_fv3dot(n, n));
}
#else
;
#endif
/// @brief Get component of fv4 v in direction fv4 n
SL_header fv4 SL_fv4align(fv4 v, fv4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_fv4muls(n, SL_fv4dot(v, n) / SL_fv4dot(n, n));
}
#else
;
#endif
/// @brief Get component of fv2 v in direction fv2 n assumed to be of unit length
SL_header fv2 SL_fv2align_u(fv2 v, fv2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_fv2muls(n, SL_fv2dot(v, n));
}
#else
;
#endif
/// @brief Get component of fv3 v in direction fv3 n assumed to be of unit length
SL_header fv3 SL_fv3align_u(fv3 v, fv3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_fv3muls(n, SL_fv3dot(v, n));
}
#else
;
#endif
/// @brief Get component of fv4 v in direction fv4 n assumed to be of unit length
SL_header fv4 SL_fv4align_u(fv4 v, fv4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_fv4muls(n, SL_fv4dot(v, n));
}
#else
;
#endif
/// @brief Project fv2 v on plane with normal fv2 n
SL_header fv2 SL_fv2proj(fv2 v, fv2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_fv2sub(v, SL_fv2align(v, n));
}
#else
;
#endif
/// @brief Project fv3 v on plane with normal fv3 n
SL_header fv3 SL_fv3proj(fv3 v, fv3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_fv3sub(v, SL_fv3align(v, n));
}
#else
;
#endif
/// @brief Project fv4 v on plane with normal fv4 n
SL_header fv4 SL_fv4proj(fv4 v, fv4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_fv4sub(v, SL_fv4align(v, n));
}
#else
;
#endif
/// @brief Project fv2 v on plane with normal fv2 n
SL_header fv2 SL_fv2proj_u(fv2 v, fv2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_fv2sub(v, SL_fv2align_u(v, n));
}
#else
;
#endif
/// @brief Project fv3 v on plane with normal fv3 n
SL_header fv3 SL_fv3proj_u(fv3 v, fv3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_fv3sub(v, SL_fv3align_u(v, n));
}
#else
;
#endif
/// @brief Project fv4 v on plane with normal fv4 n
SL_header fv4 SL_fv4proj_u(fv4 v, fv4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_fv4sub(v, SL_fv4align_u(v, n));
}
#else
;
#endif
/// @brief Component-wise modulo of a fv by scalar n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header float* SL_fvmods_(float* v, float n, float* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = fmod(v[i], n);
    return dest;
}
#else
;
#endif
/// @brief Component-wise modulo of a fv by scalar n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header fv SL_fvmods(fv v, float n, fv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_fvmods_(v.data, n, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise modulo of a fv2 by scalar n
SL_header fv2 SL_fv2mods(fv2 v, float n)
#if defined(SL_IMPLEMENTATION)
{
    return (fv2) {
        .x = fmod(v.x, n),
        .y = fmod(v.y, n)
    };
}
#else
;
#endif
/// @brief Component-wise modulo of a fv3 by scalar n
SL_header fv3 SL_fv3mods(fv3 v, float n)
#if defined(SL_IMPLEMENTATION)
{
    return (fv3) {
        .x = fmod(v.x, n),
        .y = fmod(v.y, n),
        .z = fmod(v.z, n)
    };
}
#else
;
#endif
/// @brief Component-wise modulo of a fv4 by scalar n
SL_header fv4 SL_fv4mods(fv4 v, float n)
#if defined(SL_IMPLEMENTATION)
{
    return (fv4) {
        .x = fmod(v.x, n),
        .y = fmod(v.y, n),
        .z = fmod(v.z, n),
        .w = fmod(v.w, n)
    };
}
#else
;
#endif
/// @brief Component-wise modulo of a fv by fv n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header float* SL_fvmod_(float* v, float* n, float* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = fmod(v[i], n[i]);
    return dest;
}
#else
;
#endif
/// @brief Component-wise modulo of a fv by fv n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header fv SL_fvmod(fv v, fv n, fv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_fvmod_(v.data, n.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise modulo of a fv2 by fv2 n
SL_header fv2 SL_fv2mod(fv2 v, fv2 n)
#if defined(SL_IMPLEMENTATION)
{
    return (fv2) {
        .x = fmod(v.x, n.x),
        .y = fmod(v.y, n.y)
    };
}
#else
;
#endif
/// @brief Component-wise modulo of a fv3 by fv3 n
SL_header fv3 SL_fv3mod(fv3 v, fv3 n)
#if defined(SL_IMPLEMENTATION)
{
    return (fv3) {
        .x = fmod(v.x, n.x),
        .y = fmod(v.y, n.y),
        .z = fmod(v.z, n.z)
    };
}
#else
;
#endif
/// @brief Component-wise modulo of a fv4 by fv4 n
SL_header fv4 SL_fv4mod(fv4 v, fv4 n)
#if defined(SL_IMPLEMENTATION)
{
    return (fv4) {
        .x = fmod(v.x, n.x),
        .y = fmod(v.y, n.y),
        .z = fmod(v.z, n.z),
        .w = fmod(v.w, n.w)
    };
}
#else
;
#endif
/// @brief Normalization of a fv
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header float* SL_fvnorm_(float* v, float* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    double inv_len = 1.0 / SL_fvlen_(v, count);
    for (usize i = 0; i < count; ++i) dest[i] = v[i] * inv_len;
    return dest;
}
#else
;
#endif
/// @brief Normalization of a fv
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header fv SL_fvnorm(fv v, fv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_fvnorm_(v.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Normalization of a fv2
SL_header fv2 SL_fv2norm(fv2 v)
#if defined(SL_IMPLEMENTATION)
{
    double inv_len = 1.0 / SL_fv2len(v);
    return (fv2) {
        .x = v.x * inv_len,
        .y = v.y * inv_len
    };
}
#else
;
#endif
/// @brief Normalization of a fv3
SL_header fv3 SL_fv3norm(fv3 v)
#if defined(SL_IMPLEMENTATION)
{
    double inv_len = 1.0 / SL_fv3len(v);
    return (fv3) {
        .x = v.x * inv_len,
        .y = v.y * inv_len,
        .z = v.z * inv_len
    };
}
#else
;
#endif
/// @brief Normalization of a fv4
SL_header fv4 SL_fv4norm(fv4 v)
#if defined(SL_IMPLEMENTATION)
{
    double inv_len = 1.0 / SL_fv4len(v);
    return (fv4) {
        .x = v.x * inv_len,
        .y = v.y * inv_len,
        .z = v.z * inv_len,
        .w = v.w * inv_len
    };
}
#else
;
#endif
/// @brief Component-wise flooring of a fv
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header float* SL_fvfloor_(float* v, float* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = floor(v[i]);
    return dest;
}
#else
;
#endif
/// @brief Component-wise flooring of a fv
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header fv SL_fvfloor(fv v, fv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_fvfloor_(v.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise flooring of a fv2
SL_header fv2 SL_fv2floor(fv2 v)
#if defined(SL_IMPLEMENTATION)
{
    return (fv2) {
        .x = floor(v.x),
        .y = floor(v.y)
    };
}
#else
;
#endif
/// @brief Component-wise flooring of a fv3
SL_header fv3 SL_fv3floor(fv3 v)
#if defined(SL_IMPLEMENTATION)
{
    return (fv3) {
        .x = floor(v.x),
        .y = floor(v.y),
        .z = floor(v.z)
    };
}
#else
;
#endif
/// @brief Component-wise flooring of a fv4
SL_header fv4 SL_fv4floor(fv4 v)
#if defined(SL_IMPLEMENTATION)
{
    return (fv4) {
        .x = floor(v.x),
        .y = floor(v.y),
        .z = floor(v.z),
        .w = floor(v.w)
    };
}
#else
;
#endif
/// @brief Component-wise ceiling of a fv
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header float* SL_fvceil_(float* v, float* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = ceil(v[i]);
    return dest;
}
#else
;
#endif
/// @brief Component-wise ceiling of a fv
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header fv SL_fvceil(fv v, fv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_fvceil_(v.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise ceiling of a fv2
SL_header fv2 SL_fv2ceil(fv2 v)
#if defined(SL_IMPLEMENTATION)
{
    return (fv2) {
        .x = ceil(v.x),
        .y = ceil(v.y)
    };
}
#else
;
#endif
/// @brief Component-wise ceiling of a fv3
SL_header fv3 SL_fv3ceil(fv3 v)
#if defined(SL_IMPLEMENTATION)
{
    return (fv3) {
        .x = ceil(v.x),
        .y = ceil(v.y),
        .z = ceil(v.z)
    };
}
#else
;
#endif
/// @brief Component-wise ceiling of a fv4
SL_header fv4 SL_fv4ceil(fv4 v)
#if defined(SL_IMPLEMENTATION)
{
    return (fv4) {
        .x = ceil(v.x),
        .y = ceil(v.y),
        .z = ceil(v.z),
        .w = ceil(v.w)
    };
}
#else
;
#endif
/// @brief Component-wise fractional part of a fv
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header float* SL_fvfrac_(float* v, float* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = v[i] - floor(v[i]);
    return dest;
}
#else
;
#endif
/// @brief Component-wise fractional part of a fv
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header fv SL_fvfrac(fv v, fv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_fvfrac_(v.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise fractional part of a fv2
SL_header fv2 SL_fv2frac(fv2 v)
#if defined(SL_IMPLEMENTATION)
{
    return (fv2) {
        .x = v.x - floor(v.x),
        .y = v.y - floor(v.y)
    };
}
#else
;
#endif
/// @brief Component-wise fractional part of a fv3
SL_header fv3 SL_fv3frac(fv3 v)
#if defined(SL_IMPLEMENTATION)
{
    return (fv3) {
        .x = v.x - floor(v.x),
        .y = v.y - floor(v.y),
        .z = v.z - floor(v.z)
    };
}
#else
;
#endif
/// @brief Component-wise fractional part of a fv4
SL_header fv4 SL_fv4frac(fv4 v)
#if defined(SL_IMPLEMENTATION)
{
    return (fv4) {
        .x = v.x - floor(v.x),
        .y = v.y - floor(v.y),
        .z = v.z - floor(v.z),
        .w = v.w - floor(v.w)
    };
}
#else
;
#endif
/// @brief Linear interpolation of two fv
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header float* SL_fvlerp_(float* lhs, float* rhs, float t, float* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] + (rhs[i] - lhs[i]) * t;
    return dest;
}
#else
;
#endif
/// @brief Linear interpolation of two fv
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header fv SL_fvlerp(fv lhs, fv rhs, float t, fv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_fvlerp_(lhs.data, rhs.data, t, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Linear interpolation of two fv2
SL_header fv2 SL_fv2lerp(fv2 lhs, fv2 rhs, float t)
#if defined(SL_IMPLEMENTATION)
{
    return (fv2) {
        .x = lhs.x + (rhs.x - lhs.x) * t,
        .y = lhs.y + (rhs.y - lhs.y) * t
    };
}
#else
;
#endif
/// @brief Linear interpolation of two fv3
SL_header fv3 SL_fv3lerp(fv3 lhs, fv3 rhs, float t)
#if defined(SL_IMPLEMENTATION)
{
    return (fv3) {
        .x = lhs.x + (rhs.x - lhs.x) * t,
        .y = lhs.y + (rhs.y - lhs.y) * t,
        .z = lhs.z + (rhs.z - lhs.z) * t
    };
}
#else
;
#endif
/// @brief Linear interpolation of two fv4
SL_header fv4 SL_fv4lerp(fv4 lhs, fv4 rhs, float t)
#if defined(SL_IMPLEMENTATION)
{
    return (fv4) {
        .x = lhs.x + (rhs.x - lhs.x) * t,
        .y = lhs.y + (rhs.y - lhs.y) * t,
        .z = lhs.z + (rhs.z - lhs.z) * t,
        .w = lhs.w + (rhs.w - lhs.w) * t
    };
}
#else
;
#endif
/// @brief Spherical interpolation of two fv2
SL_header fv2 SL_fv2serp(fv2 lhs, fv2 rhs, float t)
#if defined(SL_IMPLEMENTATION)
{
    float angle = acos(SL_fv2dot(SL_fv2norm(lhs), SL_fv2norm(rhs)));
    float inv_sin = 1.0 / sin(angle);
    float a = sin(angle * t) * inv_sin;
    float b = sin(angle * (1 - t)) * inv_sin;
    return (fv2) {
        .x = lhs.x * a + rhs.x * b,
        .y = lhs.y * a + rhs.y * b
    };
}
#else
;
#endif
/// @brief Spherical interpolation of two fv3
SL_header fv3 SL_fv3serp(fv3 lhs, fv3 rhs, float t)
#if defined(SL_IMPLEMENTATION)
{
    float angle = acos(SL_fv3dot(SL_fv3norm(lhs), SL_fv3norm(rhs)));
    float inv_sin = 1.0 / sin(angle);
    float a = sin(angle * t) * inv_sin;
    float b = sin(angle * (1 - t)) * inv_sin;
    return (fv3) {
        .x = lhs.x * a + rhs.x * b,
        .y = lhs.y * a + rhs.y * b,
        .z = lhs.z * a + rhs.z * b
    };
}
#else
;
#endif
/// @brief Spherical interpolation of two fv4
SL_header fv4 SL_fv4serp(fv4 lhs, fv4 rhs, float t)
#if defined(SL_IMPLEMENTATION)
{
    float angle = acos(SL_fv4dot(SL_fv4norm(lhs), SL_fv4norm(rhs)));
    float inv_sin = 1.0 / sin(angle);
    float a = sin(angle * t) * inv_sin;
    float b = sin(angle * (1 - t)) * inv_sin;
    return (fv4) {
        .x = lhs.x * a + rhs.x * b,
        .y = lhs.y * a + rhs.y * b,
        .z = lhs.z * a + rhs.z * b,
        .w = lhs.w * a + rhs.w * b
    };
}
#else
;
#endif
/// @brief Angle on the 2D plane formed by a fv2
SL_header double SL_fv2angle(fv2 v)
#if defined(SL_IMPLEMENTATION)
{
    return atan2(v.y, v.x);
}
#else
;
#endif
/// @brief Unit fv2 oriented based on given angle
SL_header fv2 SL_fv2from_angle(float angle)
#if defined(SL_IMPLEMENTATION)
{
    double c, s; sincos(angle, &s, &c);
    return SL_fv2_(c, s);
}
#else
;
#endif
/// @brief Unit fv3 oriented based on given angles
SL_header fv3 SL_fv3from_yawPitch(float yaw, float pitch)
#if defined(SL_IMPLEMENTATION)
{
    double cy, sy; sincos(yaw, &sy, &cy);
    double cp, sp; sincos(pitch, &sp, &cp);
    return SL_fv3_(sy * cp, sp, cy * cp);
}
#else
;
#endif
/// @brief Rotate fv2 by angle encoded by `cosa` and `sina`
SL_header fv2 SL_fv2rot_sc(fv2 v, float sina, float cosa)
#if defined(SL_IMPLEMENTATION)
{
    return SL_fv2_(v.x * cosa - v.y * sina, v.y * cosa + v.x * sina);
}
#else
;
#endif
/// @brief Rotate fv2 by angle encoded in vector `cs`
SL_header fv2 SL_fv2rot_cs(fv2 v, fv2 cs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_fv2_(v.x * cs.x - v.y * cs.y, v.x * cs.y + v.y * cs.x);
}
#else
;
#endif
/// @brief Rotate fv2 by angle
SL_header fv2 SL_fv2rot(fv2 v, float a)
#if defined(SL_IMPLEMENTATION)
{
    double sina, cosa; sincos(a, &sina, &cosa);
    return SL_fv2rot_sc(v, sina, cosa);
}
#else
;
#endif
/// @brief Cross-product of two fv2
SL_header double SL_fv2cross(fv2 lhs, fv2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x * rhs.y - lhs.y * rhs.x;
}
#else
;
#endif
/// @brief Cross-product of two fv3
SL_header fv3 SL_fv3cross(fv3 lhs, fv3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (fv3) {
        .x = lhs.y * rhs.z - lhs.z * rhs.y,
        .y = lhs.z * rhs.x - lhs.x * rhs.z,
        .z = lhs.x * rhs.y - lhs.y * rhs.x
    };
}
#else
;
#endif
#pragma endregion FLOAT
#pragma region DOUBLE

/// @brief Vector of double with arbitrary dimension
typedef struct {
    const usize count;
    double *data;
} dv;

/// @brief Vector of double with dimension 2
typedef union {
    double data[2];
    struct {
        union { double x, r, u; };
        union { double y, g, v; };
    };
} dv2;

#define SL_dv2_zero  ((dv2){.x =  0, .y =  0})
#define SL_dv2_one   ((dv2){.x =  1, .y =  1})
#define SL_dv2_right ((dv2){.x =  1, .y =  0})
#define SL_dv2_up    ((dv2){.x =  0, .y =  1})
#define SL_dv2_left  ((dv2){.x = -1, .y =  0})
#define SL_dv2_down  ((dv2){.x =  0, .y = -1})

/// @brief Vector of double with dimension 3
typedef union {
    double data[3];
    struct {
        union { double x, r, u; };
        union { double y, g, v; };
        union { double z, b, s; };
    };
    struct {
        union { double __x, __r, __u; };
        union { dv2 yz, gb, vs; };
    };
    struct {
        union { dv2 xy, rg, uv; };
        union { double __z, __b, __s; };
    };
} dv3;

#define SL_dv3_zero  ((dv3){.x =  0, .y =  0, .z =  0})
#define SL_dv3_one   ((dv3){.x =  1, .y =  1, .z =  1})
#define SL_dv3_right ((dv3){.x =  1, .y =  0, .z =  0})
#define SL_dv3_up    ((dv3){.x =  0, .y =  1, .z =  0})
#define SL_dv3_forw  ((dv3){.x =  0, .y =  0, .z =  1})
#define SL_dv3_left  ((dv3){.x = -1, .y =  0, .z =  0})
#define SL_dv3_down  ((dv3){.x =  0, .y = -1, .z =  0})
#define SL_dv3_back  ((dv3){.x =  0, .y =  0, .z = -1})

/// @brief Vector of double with dimension 4
typedef union {
    double data[4];
    struct {
        union { double x, r, u; };
        union { double y, g, v; };
        union { double z, b, s; };
        union { double w, a, t; };
    };
    struct {
        union { double __x0, __r0, __u0; };
        union { dv2 yz, gb, vs; };
        union { double __w0, __a0, __t0; };
    };
    struct {
        union { dv2 xy, rb, uv; };
        union { dv2 zw, ba, st; };
    };
    struct {
        union { dv3 xyz, rgb, uvs; };
        union { double __w1, __a1, __t1; };
    };
    struct {
        union { double __x1, __r1, __u1; };
        union { dv3 yzw, gba, vst; };
    };
} dv4;

#define SL_dv4_zero  ((dv4){.x = 0, .y = 0, .z = 0, .w = 0})
#define SL_dv4_one   ((dv4){.x = 1, .y = 1, .z = 1, .w = 1})

#define SL_dv4_white  ((dv4){.x = 1, .y = 1, .z = 1, .w = 1})
#define SL_dv4_black  ((dv4){.x = 0, .y = 0, .z = 0, .w = 1})
#define SL_dv4_red    ((dv4){.x = 1, .y = 0, .z = 0, .w = 1})
#define SL_dv4_green  ((dv4){.x = 0, .y = 1, .z = 0, .w = 1})
#define SL_dv4_blue   ((dv4){.x = 0, .y = 0, .z = 1, .w = 1})
#define SL_dv4_yellow ((dv4){.x = 1, .y = 1, .z = 0, .w = 1})
#define SL_dv4_cyan   ((dv4){.x = 0, .y = 1, .z = 1, .w = 1})
#define SL_dv4_purple ((dv4){.x = 1, .y = 0, .z = 1, .w = 1})



#define SL_dv2_(X, Y)       ((dv2){.x = X, .y = Y})
#define SL_dv3_(X, Y, Z)    ((dv3){.x = X, .y = Y, .z = Z})
#define SL_dv4_(X, Y, Z, W) ((dv4){.x = X, .y = Y, .z = Z, .w = W})

#define SL_dv2s(S)          ((dv2){.x = S, .y = S})
#define SL_dv3s(S)          ((dv3){.x = S, .y = S, .z = S})
#define SL_dv4s(S)          ((dv4){.x = S, .y = S, .z = S, .w = S})

#define SL_dvv(V)           ((dv){.count = vsize(V), .data = (V).data})
#define SL_dv2v(V, ...)     ((dv2){.x = (V).x, .y = (V).y})
#define SL_dv3v(V, ...)     ((dv3){.x = (V).x, .y = (V).y, .z = (SL_vsize(V) >= 3 ? (V).data[2] : (0, ##__VA_ARGS__))})
#define SL_dv4v(V, ...)     ((dv4){.x = (V).x, .y = (V).y, .z = (SL_vsize(V) >= 3 ? (V).data[2] : ((const float[]){0, ##__VA_ARGS__, 0})[1]), .w = (SL_vsize(V) >= 4 ? (V).data[3] : ((const float[]){0, ##__VA_ARGS__, 0, 0})[2])})



/// @brief Equality of two dv
/// @note All vectors are assumed to be of size 'count'
SL_header bool SL_dvequ_(double* lhs, double* rhs, usize count)
#if defined(SL_IMPLEMENTATION)
{
    bool dest = true;
    for (usize i = 0; i < count; ++i) dest &= lhs[i] == rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Equality of two dv
/// @note All vectors are assumed to be of size 'count'
SL_header bool SL_dvequ(dv lhs, dv rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_dvequ_(lhs.data, rhs.data, lhs.count);
}
#else
;
#endif
/// @brief Equality of two dv2
SL_header bool SL_dv2equ(dv2 lhs, dv2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}
#else
;
#endif
/// @brief Equality of two dv3
SL_header bool SL_dv3equ(dv3 lhs, dv3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}
#else
;
#endif
/// @brief Equality of two dv4
SL_header bool SL_dv4equ(dv4 lhs, dv4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
}
#else
;
#endif
/// @brief Addition of two dv
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header double* SL_dvadd_(double* lhs, double* rhs, double* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] + rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Addition of two dv
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header dv SL_dvadd(dv lhs, dv rhs, dv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_dvadd_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two dv2
SL_header dv2 SL_dv2add(dv2 lhs, dv2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (dv2) {
        .x = lhs.x + rhs.x,
        .y = lhs.y + rhs.y
    };
}
#else
;
#endif
/// @brief Addition of two dv3
SL_header dv3 SL_dv3add(dv3 lhs, dv3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (dv3) {
        .x = lhs.x + rhs.x,
        .y = lhs.y + rhs.y,
        .z = lhs.z + rhs.z
    };
}
#else
;
#endif
/// @brief Addition of two dv4
SL_header dv4 SL_dv4add(dv4 lhs, dv4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (dv4) {
        .x = lhs.x + rhs.x,
        .y = lhs.y + rhs.y,
        .z = lhs.z + rhs.z,
        .w = lhs.w + rhs.w
    };
}
#else
;
#endif
/// @brief Difference of two dv
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header double* SL_dvsub_(double* lhs, double* rhs, double* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] - rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Difference of two dv
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header dv SL_dvsub(dv lhs, dv rhs, dv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_dvsub_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two dv2
SL_header dv2 SL_dv2sub(dv2 lhs, dv2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (dv2) {
        .x = lhs.x - rhs.x,
        .y = lhs.y - rhs.y
    };
}
#else
;
#endif
/// @brief Difference of two dv3
SL_header dv3 SL_dv3sub(dv3 lhs, dv3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (dv3) {
        .x = lhs.x - rhs.x,
        .y = lhs.y - rhs.y,
        .z = lhs.z - rhs.z
    };
}
#else
;
#endif
/// @brief Difference of two dv4
SL_header dv4 SL_dv4sub(dv4 lhs, dv4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (dv4) {
        .x = lhs.x - rhs.x,
        .y = lhs.y - rhs.y,
        .z = lhs.z - rhs.z,
        .w = lhs.w - rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of two dv
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header double* SL_dvmul_(double* lhs, double* rhs, double* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise multiplication of two dv
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header dv SL_dvmul(dv lhs, dv rhs, dv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_dvmul_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise multiplication of two dv2
SL_header dv2 SL_dv2mul(dv2 lhs, dv2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (dv2) {
        .x = lhs.x * rhs.x,
        .y = lhs.y * rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of two dv3
SL_header dv3 SL_dv3mul(dv3 lhs, dv3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (dv3) {
        .x = lhs.x * rhs.x,
        .y = lhs.y * rhs.y,
        .z = lhs.z * rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of two dv4
SL_header dv4 SL_dv4mul(dv4 lhs, dv4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (dv4) {
        .x = lhs.x * rhs.x,
        .y = lhs.y * rhs.y,
        .z = lhs.z * rhs.z,
        .w = lhs.w * rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of a dv with a scalar
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header double* SL_dvmuls_(double* lhs, double rhs, double* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * rhs;
    return dest;
}
#else
;
#endif
/// @brief Component-wise multiplication of a dv with a scalar
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header dv SL_dvmuls(dv lhs, double rhs, dv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_dvmuls_(lhs.data, rhs, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise multiplication of a dv2 with a scalar
SL_header dv2 SL_dv2muls(dv2 lhs, double rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (dv2) {
        .x = lhs.x * rhs,
        .y = lhs.y * rhs
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of a dv3 with a scalar
SL_header dv3 SL_dv3muls(dv3 lhs, double rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (dv3) {
        .x = lhs.x * rhs,
        .y = lhs.y * rhs,
        .z = lhs.z * rhs
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of a dv4 with a scalar
SL_header dv4 SL_dv4muls(dv4 lhs, double rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (dv4) {
        .x = lhs.x * rhs,
        .y = lhs.y * rhs,
        .z = lhs.z * rhs,
        .w = lhs.w * rhs
    };
}
#else
;
#endif
/// @brief Component-wise division of two dv
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header double* SL_dvdiv_(double* lhs, double* rhs, double* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] / rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise division of two dv
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header dv SL_dvdiv(dv lhs, dv rhs, dv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_dvdiv_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise division of two dv2
SL_header dv2 SL_dv2div(dv2 lhs, dv2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (dv2) {
        .x = lhs.x / rhs.x,
        .y = lhs.y / rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise division of two dv3
SL_header dv3 SL_dv3div(dv3 lhs, dv3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (dv3) {
        .x = lhs.x / rhs.x,
        .y = lhs.y / rhs.y,
        .z = lhs.z / rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise division of two dv4
SL_header dv4 SL_dv4div(dv4 lhs, dv4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (dv4) {
        .x = lhs.x / rhs.x,
        .y = lhs.y / rhs.y,
        .z = lhs.z / rhs.z,
        .w = lhs.w / rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise division of a dv with a scalar
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header double* SL_dvdivs_(double* lhs, double rhs, double* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] / rhs;
    return dest;
}
#else
;
#endif
/// @brief Component-wise division of a dv with a scalar
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header dv SL_dvdivs(dv lhs, double rhs, dv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_dvdivs_(lhs.data, rhs, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise division of a dv2 with a scalar
SL_header dv2 SL_dv2divs(dv2 lhs, double rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (dv2) {
        .x = lhs.x / rhs,
        .y = lhs.y / rhs
    };
}
#else
;
#endif
/// @brief Component-wise division of a dv3 with a scalar
SL_header dv3 SL_dv3divs(dv3 lhs, double rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (dv3) {
        .x = lhs.x / rhs,
        .y = lhs.y / rhs,
        .z = lhs.z / rhs
    };
}
#else
;
#endif
/// @brief Component-wise division of a dv4 with a scalar
SL_header dv4 SL_dv4divs(dv4 lhs, double rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (dv4) {
        .x = lhs.x / rhs,
        .y = lhs.y / rhs,
        .z = lhs.z / rhs,
        .w = lhs.w / rhs
    };
}
#else
;
#endif
/// @brief Addition of two dv with lhs scaled by a double
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header double* SL_dvaddS_(double* lhs, double* rhs, double s, double* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] + rhs[i] * s;
    return dest;
}
#else
;
#endif
/// @brief Addition of two dv with lhs scaled by a double
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header dv SL_dvaddS(dv lhs, dv rhs, double s, dv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_dvaddS_(lhs.data, rhs.data, s, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two dv2 with lhs scaled by a double
SL_header dv2 SL_dv2addS(dv2 lhs, dv2 rhs, double s)
#if defined(SL_IMPLEMENTATION)
{
    return (dv2) {
        .x = lhs.x + rhs.x * s,
        .y = lhs.y + rhs.y * s
    };
}
#else
;
#endif
/// @brief Addition of two dv3 with lhs scaled by a double
SL_header dv3 SL_dv3addS(dv3 lhs, dv3 rhs, double s)
#if defined(SL_IMPLEMENTATION)
{
    return (dv3) {
        .x = lhs.x + rhs.x * s,
        .y = lhs.y + rhs.y * s,
        .z = lhs.z + rhs.z * s
    };
}
#else
;
#endif
/// @brief Addition of two dv4 with lhs scaled by a double
SL_header dv4 SL_dv4addS(dv4 lhs, dv4 rhs, double s)
#if defined(SL_IMPLEMENTATION)
{
    return (dv4) {
        .x = lhs.x + rhs.x * s,
        .y = lhs.y + rhs.y * s,
        .z = lhs.z + rhs.z * s,
        .w = lhs.w + rhs.w * s
    };
}
#else
;
#endif
/// @brief Difference of two dv with lhs scaled by a double
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header double* SL_dvsubS_(double* lhs, double* rhs, double s, double* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] - rhs[i] * s;
    return dest;
}
#else
;
#endif
/// @brief Difference of two dv with lhs scaled by a double
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header dv SL_dvsubS(dv lhs, dv rhs, double s, dv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_dvsubS_(lhs.data, rhs.data, s, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two dv2 with lhs scaled by a double
SL_header dv2 SL_dv2subS(dv2 lhs, dv2 rhs, double s)
#if defined(SL_IMPLEMENTATION)
{
    return (dv2) {
        .x = lhs.x - rhs.x * s,
        .y = lhs.y - rhs.y * s
    };
}
#else
;
#endif
/// @brief Difference of two dv3 with lhs scaled by a double
SL_header dv3 SL_dv3subS(dv3 lhs, dv3 rhs, double s)
#if defined(SL_IMPLEMENTATION)
{
    return (dv3) {
        .x = lhs.x - rhs.x * s,
        .y = lhs.y - rhs.y * s,
        .z = lhs.z - rhs.z * s
    };
}
#else
;
#endif
/// @brief Difference of two dv4 with lhs scaled by a double
SL_header dv4 SL_dv4subS(dv4 lhs, dv4 rhs, double s)
#if defined(SL_IMPLEMENTATION)
{
    return (dv4) {
        .x = lhs.x - rhs.x * s,
        .y = lhs.y - rhs.y * s,
        .z = lhs.z - rhs.z * s,
        .w = lhs.w - rhs.w * s
    };
}
#else
;
#endif
/// @brief Addition of two dv with lhs multiplied with a double
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header double* SL_dvaddM_(double* lhs, double* rhs, double* m, double* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] + rhs[i] * m[i];
    return dest;
}
#else
;
#endif
/// @brief Addition of two dv with lhs multiplied with a double
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header dv SL_dvaddM(dv lhs, dv rhs, dv m, dv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_dvaddM_(lhs.data, rhs.data, m.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two dv2 with lhs multiplied with a double
SL_header dv2 SL_dv2addM(dv2 lhs, dv2 rhs, dv2 m)
#if defined(SL_IMPLEMENTATION)
{
    return (dv2) {
        .x = lhs.x + rhs.x * m.x,
        .y = lhs.y + rhs.y * m.y
    };
}
#else
;
#endif
/// @brief Addition of two dv3 with lhs multiplied with a double
SL_header dv3 SL_dv3addM(dv3 lhs, dv3 rhs, dv3 m)
#if defined(SL_IMPLEMENTATION)
{
    return (dv3) {
        .x = lhs.x + rhs.x * m.x,
        .y = lhs.y + rhs.y * m.y,
        .z = lhs.z + rhs.z * m.z
    };
}
#else
;
#endif
/// @brief Addition of two dv4 with lhs multiplied with a double
SL_header dv4 SL_dv4addM(dv4 lhs, dv4 rhs, dv4 m)
#if defined(SL_IMPLEMENTATION)
{
    return (dv4) {
        .x = lhs.x + rhs.x * m.x,
        .y = lhs.y + rhs.y * m.y,
        .z = lhs.z + rhs.z * m.z,
        .w = lhs.w + rhs.w * m.w
    };
}
#else
;
#endif
/// @brief Difference of two dv with lhs multiplied with a double
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header double* SL_dvsubM_(double* lhs, double* rhs, double* m, double* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] - rhs[i] * m[i];
    return dest;
}
#else
;
#endif
/// @brief Difference of two dv with lhs multiplied with a double
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header dv SL_dvsubM(dv lhs, dv rhs, dv m, dv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_dvsubM_(lhs.data, rhs.data, m.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two dv2 with lhs multiplied with a double
SL_header dv2 SL_dv2subM(dv2 lhs, dv2 rhs, dv2 m)
#if defined(SL_IMPLEMENTATION)
{
    return (dv2) {
        .x = lhs.x - rhs.x * m.x,
        .y = lhs.y - rhs.y * m.y
    };
}
#else
;
#endif
/// @brief Difference of two dv3 with lhs multiplied with a double
SL_header dv3 SL_dv3subM(dv3 lhs, dv3 rhs, dv3 m)
#if defined(SL_IMPLEMENTATION)
{
    return (dv3) {
        .x = lhs.x - rhs.x * m.x,
        .y = lhs.y - rhs.y * m.y,
        .z = lhs.z - rhs.z * m.z
    };
}
#else
;
#endif
/// @brief Difference of two dv4 with lhs multiplied with a double
SL_header dv4 SL_dv4subM(dv4 lhs, dv4 rhs, dv4 m)
#if defined(SL_IMPLEMENTATION)
{
    return (dv4) {
        .x = lhs.x - rhs.x * m.x,
        .y = lhs.y - rhs.y * m.y,
        .z = lhs.z - rhs.z * m.z,
        .w = lhs.w - rhs.w * m.w
    };
}
#else
;
#endif
/// @brief Addition of two dv with lhs scaled by double and multiplied with a double
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header double* SL_dvaddSM_(double* lhs, double* rhs, double s, double* m, double* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] + rhs[i] * s * m[i];
    return dest;
}
#else
;
#endif
/// @brief Addition of two dv with lhs scaled by double and multiplied with a double
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header dv SL_dvaddSM(dv lhs, dv rhs, double s, dv m, dv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_dvaddSM_(lhs.data, rhs.data, s, m.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two dv2 with lhs scaled by double and multiplied with a double
SL_header dv2 SL_dv2addSM(dv2 lhs, dv2 rhs, double s, dv2 m)
#if defined(SL_IMPLEMENTATION)
{
    return (dv2) {
        .x = lhs.x + rhs.x * s * m.x,
        .y = lhs.y + rhs.y * s * m.y
    };
}
#else
;
#endif
/// @brief Addition of two dv3 with lhs scaled by double and multiplied with a double
SL_header dv3 SL_dv3addSM(dv3 lhs, dv3 rhs, double s, dv3 m)
#if defined(SL_IMPLEMENTATION)
{
    return (dv3) {
        .x = lhs.x + rhs.x * s * m.x,
        .y = lhs.y + rhs.y * s * m.y,
        .z = lhs.z + rhs.z * s * m.z
    };
}
#else
;
#endif
/// @brief Addition of two dv4 with lhs scaled by double and multiplied with a double
SL_header dv4 SL_dv4addSM(dv4 lhs, dv4 rhs, double s, dv4 m)
#if defined(SL_IMPLEMENTATION)
{
    return (dv4) {
        .x = lhs.x + rhs.x * s * m.x,
        .y = lhs.y + rhs.y * s * m.y,
        .z = lhs.z + rhs.z * s * m.z,
        .w = lhs.w + rhs.w * s * m.w
    };
}
#else
;
#endif
/// @brief Difference of two dv with lhs scaled by double and multiplied with a double
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header double* SL_dvsubSM_(double* lhs, double* rhs, double s, double* m, double* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] - rhs[i] * s * m[i];
    return dest;
}
#else
;
#endif
/// @brief Difference of two dv with lhs scaled by double and multiplied with a double
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header dv SL_dvsubSM(dv lhs, dv rhs, double s, dv m, dv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_dvsubSM_(lhs.data, rhs.data, s, m.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two dv2 with lhs scaled by double and multiplied with a double
SL_header dv2 SL_dv2subSM(dv2 lhs, dv2 rhs, double s, dv2 m)
#if defined(SL_IMPLEMENTATION)
{
    return (dv2) {
        .x = lhs.x - rhs.x * s * m.x,
        .y = lhs.y - rhs.y * s * m.y
    };
}
#else
;
#endif
/// @brief Difference of two dv3 with lhs scaled by double and multiplied with a double
SL_header dv3 SL_dv3subSM(dv3 lhs, dv3 rhs, double s, dv3 m)
#if defined(SL_IMPLEMENTATION)
{
    return (dv3) {
        .x = lhs.x - rhs.x * s * m.x,
        .y = lhs.y - rhs.y * s * m.y,
        .z = lhs.z - rhs.z * s * m.z
    };
}
#else
;
#endif
/// @brief Difference of two dv4 with lhs scaled by double and multiplied with a double
SL_header dv4 SL_dv4subSM(dv4 lhs, dv4 rhs, double s, dv4 m)
#if defined(SL_IMPLEMENTATION)
{
    return (dv4) {
        .x = lhs.x - rhs.x * s * m.x,
        .y = lhs.y - rhs.y * s * m.y,
        .z = lhs.z - rhs.z * s * m.z,
        .w = lhs.w - rhs.w * s * m.w
    };
}
#else
;
#endif
/// @brief Addition of two dv with rhs scaled by a double
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header double* SL_dvSadd_(double* lhs, double s, double* rhs, double* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * s + rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Addition of two dv with rhs scaled by a double
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header dv SL_dvSadd(dv lhs, double s, dv rhs, dv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_dvSadd_(lhs.data, s, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two dv2 with rhs scaled by a double
SL_header dv2 SL_dv2Sadd(dv2 lhs, double s, dv2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (dv2) {
        .x = lhs.x * s + rhs.x,
        .y = lhs.y * s + rhs.y
    };
}
#else
;
#endif
/// @brief Addition of two dv3 with rhs scaled by a double
SL_header dv3 SL_dv3Sadd(dv3 lhs, double s, dv3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (dv3) {
        .x = lhs.x * s + rhs.x,
        .y = lhs.y * s + rhs.y,
        .z = lhs.z * s + rhs.z
    };
}
#else
;
#endif
/// @brief Addition of two dv4 with rhs scaled by a double
SL_header dv4 SL_dv4Sadd(dv4 lhs, double s, dv4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (dv4) {
        .x = lhs.x * s + rhs.x,
        .y = lhs.y * s + rhs.y,
        .z = lhs.z * s + rhs.z,
        .w = lhs.w * s + rhs.w
    };
}
#else
;
#endif
/// @brief Difference of two dv with rhs scaled by a double
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header double* SL_dvSsub_(double* lhs, double s, double* rhs, double* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * s - rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Difference of two dv with rhs scaled by a double
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header dv SL_dvSsub(dv lhs, double s, dv rhs, dv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_dvSsub_(lhs.data, s, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two dv2 with rhs scaled by a double
SL_header dv2 SL_dv2Ssub(dv2 lhs, double s, dv2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (dv2) {
        .x = lhs.x * s - rhs.x,
        .y = lhs.y * s - rhs.y
    };
}
#else
;
#endif
/// @brief Difference of two dv3 with rhs scaled by a double
SL_header dv3 SL_dv3Ssub(dv3 lhs, double s, dv3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (dv3) {
        .x = lhs.x * s - rhs.x,
        .y = lhs.y * s - rhs.y,
        .z = lhs.z * s - rhs.z
    };
}
#else
;
#endif
/// @brief Difference of two dv4 with rhs scaled by a double
SL_header dv4 SL_dv4Ssub(dv4 lhs, double s, dv4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (dv4) {
        .x = lhs.x * s - rhs.x,
        .y = lhs.y * s - rhs.y,
        .z = lhs.z * s - rhs.z,
        .w = lhs.w * s - rhs.w
    };
}
#else
;
#endif
/// @brief Weighted sum of two dv
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header double* SL_dvmix_(double* lhs, double lhs_w, double* rhs, double rhs_w, double* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * lhs_w + rhs[i] * rhs_w;
    return dest;
}
#else
;
#endif
/// @brief Weighted sum of two dv
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header dv SL_dvmix(dv lhs, double lhs_w, dv rhs, double rhs_w, dv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_dvmix_(lhs.data, lhs_w, rhs.data, rhs_w, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Weighted sum of two dv2
SL_header dv2 SL_dv2mix(dv2 lhs, double lhs_w, dv2 rhs, double rhs_w)
#if defined(SL_IMPLEMENTATION)
{
    return (dv2) {
        .x = lhs.x * lhs_w + rhs.x * rhs_w,
        .y = lhs.y * lhs_w + rhs.y * rhs_w
    };
}
#else
;
#endif
/// @brief Weighted sum of two dv3
SL_header dv3 SL_dv3mix(dv3 lhs, double lhs_w, dv3 rhs, double rhs_w)
#if defined(SL_IMPLEMENTATION)
{
    return (dv3) {
        .x = lhs.x * lhs_w + rhs.x * rhs_w,
        .y = lhs.y * lhs_w + rhs.y * rhs_w,
        .z = lhs.z * lhs_w + rhs.z * rhs_w
    };
}
#else
;
#endif
/// @brief Weighted sum of two dv4
SL_header dv4 SL_dv4mix(dv4 lhs, double lhs_w, dv4 rhs, double rhs_w)
#if defined(SL_IMPLEMENTATION)
{
    return (dv4) {
        .x = lhs.x * lhs_w + rhs.x * rhs_w,
        .y = lhs.y * lhs_w + rhs.y * rhs_w,
        .z = lhs.z * lhs_w + rhs.z * rhs_w,
        .w = lhs.w * lhs_w + rhs.w * rhs_w
    };
}
#else
;
#endif
/// @brief Negation of a dv
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header double* SL_dvneg_(double* v, double* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = -v[i];
    return dest;
}
#else
;
#endif
/// @brief Negation of a dv
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header dv SL_dvneg(dv v, dv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_dvneg_(v.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Negation of a dv2
SL_header dv2 SL_dv2neg(dv2 v)
#if defined(SL_IMPLEMENTATION)
{
    return (dv2) {
        .x = -v.x,
        .y = -v.y
    };
}
#else
;
#endif
/// @brief Negation of a dv3
SL_header dv3 SL_dv3neg(dv3 v)
#if defined(SL_IMPLEMENTATION)
{
    return (dv3) {
        .x = -v.x,
        .y = -v.y,
        .z = -v.z
    };
}
#else
;
#endif
/// @brief Negation of a dv4
SL_header dv4 SL_dv4neg(dv4 v)
#if defined(SL_IMPLEMENTATION)
{
    return (dv4) {
        .x = -v.x,
        .y = -v.y,
        .z = -v.z,
        .w = -v.w
    };
}
#else
;
#endif
/// @brief Component-wise absolute value of a dv
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header double* SL_dvabs_(double* v, double* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = fabs(v[i]);
    return dest;
}
#else
;
#endif
/// @brief Component-wise absolute value of a dv
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header dv SL_dvabs(dv v, dv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_dvabs_(v.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise absolute value of a dv2
SL_header dv2 SL_dv2abs(dv2 v)
#if defined(SL_IMPLEMENTATION)
{
    return (dv2) {
        .x = fabs(v.x),
        .y = fabs(v.y)
    };
}
#else
;
#endif
/// @brief Component-wise absolute value of a dv3
SL_header dv3 SL_dv3abs(dv3 v)
#if defined(SL_IMPLEMENTATION)
{
    return (dv3) {
        .x = fabs(v.x),
        .y = fabs(v.y),
        .z = fabs(v.z)
    };
}
#else
;
#endif
/// @brief Component-wise absolute value of a dv4
SL_header dv4 SL_dv4abs(dv4 v)
#if defined(SL_IMPLEMENTATION)
{
    return (dv4) {
        .x = fabs(v.x),
        .y = fabs(v.y),
        .z = fabs(v.z),
        .w = fabs(v.w)
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two dv
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header double* SL_dvmin_(double* lhs, double* rhs, double* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] < rhs[i] ? lhs[i] : rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise minimum of two dv
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header dv SL_dvmin(dv lhs, dv rhs, dv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_dvmin_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise minimum of two dv2
SL_header dv2 SL_dv2min(dv2 lhs, dv2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (dv2) {
        .x = lhs.x < rhs.x ? lhs.x : rhs.x,
        .y = lhs.y < rhs.y ? lhs.y : rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two dv3
SL_header dv3 SL_dv3min(dv3 lhs, dv3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (dv3) {
        .x = lhs.x < rhs.x ? lhs.x : rhs.x,
        .y = lhs.y < rhs.y ? lhs.y : rhs.y,
        .z = lhs.z < rhs.z ? lhs.z : rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two dv4
SL_header dv4 SL_dv4min(dv4 lhs, dv4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (dv4) {
        .x = lhs.x < rhs.x ? lhs.x : rhs.x,
        .y = lhs.y < rhs.y ? lhs.y : rhs.y,
        .z = lhs.z < rhs.z ? lhs.z : rhs.z,
        .w = lhs.w < rhs.w ? lhs.w : rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two dv
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header double* SL_dvmax_(double* lhs, double* rhs, double* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] > rhs[i] ? lhs[i] : rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise maximum of two dv
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header dv SL_dvmax(dv lhs, dv rhs, dv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_dvmax_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise maximum of two dv2
SL_header dv2 SL_dv2max(dv2 lhs, dv2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (dv2) {
        .x = lhs.x > rhs.x ? lhs.x : rhs.x,
        .y = lhs.y > rhs.y ? lhs.y : rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two dv3
SL_header dv3 SL_dv3max(dv3 lhs, dv3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (dv3) {
        .x = lhs.x > rhs.x ? lhs.x : rhs.x,
        .y = lhs.y > rhs.y ? lhs.y : rhs.y,
        .z = lhs.z > rhs.z ? lhs.z : rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two dv4
SL_header dv4 SL_dv4max(dv4 lhs, dv4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (dv4) {
        .x = lhs.x > rhs.x ? lhs.x : rhs.x,
        .y = lhs.y > rhs.y ? lhs.y : rhs.y,
        .z = lhs.z > rhs.z ? lhs.z : rhs.z,
        .w = lhs.w > rhs.w ? lhs.w : rhs.w
    };
}
#else
;
#endif
/// @brief Dot product of two dv
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_dvdot_(double* lhs, double* rhs, usize count)
#if defined(SL_IMPLEMENTATION)
{
    double dest = 0;
    for (usize i = 0; i < count; ++i) dest += lhs[i] * rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Dot product of two dv
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_dvdot(dv lhs, dv rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_dvdot_(lhs.data, rhs.data, lhs.count);
}
#else
;
#endif
/// @brief Dot product of two dv2
SL_header double SL_dv2dot(dv2 lhs, dv2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}
#else
;
#endif
/// @brief Dot product of two dv3
SL_header double SL_dv3dot(dv3 lhs, dv3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}
#else
;
#endif
/// @brief Dot product of two dv4
SL_header double SL_dv4dot(dv4 lhs, dv4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}
#else
;
#endif
/// @brief Maximum component of a dv
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_dvlen_max_(double* v, usize count)
#if defined(SL_IMPLEMENTATION)
{
    double dest = 0;
    for (usize i = 0; i < count; ++i) dest = fabs(v[i]) > dest ? fabs(v[i]) : dest;
    return dest;
}
#else
;
#endif
/// @brief Maximum component of a dv
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_dvlen_max(dv v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_dvlen_max_(v.data, v.count);
}
#else
;
#endif
/// @brief Maximum component of a dv2
SL_header double SL_dv2len_max(dv2 v)
#if defined(SL_IMPLEMENTATION)
{
    v = SL_dv2abs(v);
    return v.x > v.y ? v.x : v.y;
}
#else
;
#endif
/// @brief Maximum component of a dv3
SL_header double SL_dv3len_max(dv3 v)
#if defined(SL_IMPLEMENTATION)
{
    v = SL_dv3abs(v);
    return v.x > v.y ? (v.x > v.z ? v.x : v.z) : (v.y > v.z ? v.y : v.z);
}
#else
;
#endif
/// @brief Maximum component of a dv4
SL_header double SL_dv4len_max(dv4 v)
#if defined(SL_IMPLEMENTATION)
{
    v = SL_dv4abs(v);
    return v.x > v.y ? (v.x > v.z ? (v.x > v.w ? v.x : v.w) : (v.z > v.w ? v.z : v.w)) : (v.y > v.z ? (v.y > v.w ? v.y : v.w) : (v.z > v.w ? v.z : v.w));
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a dv
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_dvlen_manh_(double* v, usize count)
#if defined(SL_IMPLEMENTATION)
{
    double dest = 0;
    for (usize i = 0; i < count; ++i) dest += fabs(v[i]);
    return dest;
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a dv
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_dvlen_manh(dv v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_dvlen_manh_(v.data, v.count);
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a dv2
SL_header double SL_dv2len_manh(dv2 v)
#if defined(SL_IMPLEMENTATION)
{
    v = SL_dv2abs(v);
    return v.x + v.y;
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a dv3
SL_header double SL_dv3len_manh(dv3 v)
#if defined(SL_IMPLEMENTATION)
{
    v = SL_dv3abs(v);
    return v.x + v.y + v.z;
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a dv4
SL_header double SL_dv4len_manh(dv4 v)
#if defined(SL_IMPLEMENTATION)
{
    v = SL_dv4abs(v);
    return v.x + v.y + v.z + v.w;
}
#else
;
#endif
/// @brief Squared euclidean length of a dv
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_dvlen_srq_(double* v, usize count)
#if defined(SL_IMPLEMENTATION)
{
    return SL_dvdot_(v, v, count);
}
#else
;
#endif
/// @brief Squared euclidean length of a dv
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_dvlen_srq(dv v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_dvlen_srq_(v.data, v.count);
}
#else
;
#endif
/// @brief Square length of a dv2
SL_header double SL_dv2len_sqr(dv2 v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_dv2dot(v, v);
}
#else
;
#endif
/// @brief Square length of a dv3
SL_header double SL_dv3len_sqr(dv3 v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_dv3dot(v, v);
}
#else
;
#endif
/// @brief Square length of a dv4
SL_header double SL_dv4len_sqr(dv4 v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_dv4dot(v, v);
}
#else
;
#endif
/// @brief Euclidean length of a dv
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_dvlen_(double* v, usize count)
#if defined(SL_IMPLEMENTATION)
{
    return sqrt(SL_dvdot_(v, v, count));
}
#else
;
#endif
/// @brief Euclidean length of a dv
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_dvlen(dv v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_dvlen_(v.data, v.count);
}
#else
;
#endif
/// @brief Euclidean length of a dv2
SL_header double SL_dv2len(dv2 v)
#if defined(SL_IMPLEMENTATION)
{
    return sqrt(SL_dv2dot(v, v));
}
#else
;
#endif
/// @brief Euclidean length of a dv3
SL_header double SL_dv3len(dv3 v)
#if defined(SL_IMPLEMENTATION)
{
    return sqrt(SL_dv3dot(v, v));
}
#else
;
#endif
/// @brief Euclidean length of a dv4
SL_header double SL_dv4len(dv4 v)
#if defined(SL_IMPLEMENTATION)
{
    return sqrt(SL_dv4dot(v, v));
}
#else
;
#endif
/// @brief Euclidean distance bewteen two dv
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_dvdist_(double* lhs, double* rhs, usize count)
#if defined(SL_IMPLEMENTATION)
{
    double accum = 0;
    for (int i = 0; i < count; ++i) accum += (lhs[i] - rhs[i]) * (lhs[i] - rhs[i]);
    return sqrt(accum);
}
#else
;
#endif
/// @brief Euclidean distance bewteen two dv
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_dvdist(dv lhs, dv rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_dvdist_(lhs.data, rhs.data, lhs.count);
}
#else
;
#endif
/// @brief Euclidean distance between two dv2
SL_header double SL_dv2dist(dv2 lhs, dv2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_dv2len(SL_dv2sub(lhs, rhs));
}
#else
;
#endif
/// @brief Euclidean distance between two dv3
SL_header double SL_dv3dist(dv3 lhs, dv3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_dv3len(SL_dv3sub(lhs, rhs));
}
#else
;
#endif
/// @brief Euclidean distance between two dv4
SL_header double SL_dv4dist(dv4 lhs, dv4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_dv4len(SL_dv4sub(lhs, rhs));
}
#else
;
#endif
/// @brief Reflection of dv2 v around vector dv2 n
SL_header dv2 SL_dv2refl(dv2 v, dv2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_dv2subS(v, n, 2.0 * SL_dv2dot(v, n) / SL_dv2dot(n, n));
}
#else
;
#endif
/// @brief Reflection of dv3 v around vector dv3 n
SL_header dv3 SL_dv3refl(dv3 v, dv3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_dv3subS(v, n, 2.0 * SL_dv3dot(v, n) / SL_dv3dot(n, n));
}
#else
;
#endif
/// @brief Reflection of dv4 v around vector dv4 n
SL_header dv4 SL_dv4refl(dv4 v, dv4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_dv4subS(v, n, 2.0 * SL_dv4dot(v, n) / SL_dv4dot(n, n));
}
#else
;
#endif
/// @brief Reflection of dv2 v around vector dv2 n assumed to be of unit length
SL_header dv2 SL_dv2refl_u(dv2 v, dv2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_dv2subS(v, n, 2.0 * SL_dv2dot(v, n));
}
#else
;
#endif
/// @brief Reflection of dv3 v around vector dv3 n assumed to be of unit length
SL_header dv3 SL_dv3refl_u(dv3 v, dv3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_dv3subS(v, n, 2.0 * SL_dv3dot(v, n));
}
#else
;
#endif
/// @brief Reflection of dv4 v around vector dv4 n assumed to be of unit length
SL_header dv4 SL_dv4refl_u(dv4 v, dv4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_dv4subS(v, n, 2.0 * SL_dv4dot(v, n));
}
#else
;
#endif
/// @brief Get component of dv2 v in direction dv2 n
SL_header dv2 SL_dv2align(dv2 v, dv2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_dv2muls(n, SL_dv2dot(v, n) / SL_dv2dot(n, n));
}
#else
;
#endif
/// @brief Get component of dv3 v in direction dv3 n
SL_header dv3 SL_dv3align(dv3 v, dv3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_dv3muls(n, SL_dv3dot(v, n) / SL_dv3dot(n, n));
}
#else
;
#endif
/// @brief Get component of dv4 v in direction dv4 n
SL_header dv4 SL_dv4align(dv4 v, dv4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_dv4muls(n, SL_dv4dot(v, n) / SL_dv4dot(n, n));
}
#else
;
#endif
/// @brief Get component of dv2 v in direction dv2 n assumed to be of unit length
SL_header dv2 SL_dv2align_u(dv2 v, dv2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_dv2muls(n, SL_dv2dot(v, n));
}
#else
;
#endif
/// @brief Get component of dv3 v in direction dv3 n assumed to be of unit length
SL_header dv3 SL_dv3align_u(dv3 v, dv3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_dv3muls(n, SL_dv3dot(v, n));
}
#else
;
#endif
/// @brief Get component of dv4 v in direction dv4 n assumed to be of unit length
SL_header dv4 SL_dv4align_u(dv4 v, dv4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_dv4muls(n, SL_dv4dot(v, n));
}
#else
;
#endif
/// @brief Project dv2 v on plane with normal dv2 n
SL_header dv2 SL_dv2proj(dv2 v, dv2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_dv2sub(v, SL_dv2align(v, n));
}
#else
;
#endif
/// @brief Project dv3 v on plane with normal dv3 n
SL_header dv3 SL_dv3proj(dv3 v, dv3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_dv3sub(v, SL_dv3align(v, n));
}
#else
;
#endif
/// @brief Project dv4 v on plane with normal dv4 n
SL_header dv4 SL_dv4proj(dv4 v, dv4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_dv4sub(v, SL_dv4align(v, n));
}
#else
;
#endif
/// @brief Project dv2 v on plane with normal dv2 n
SL_header dv2 SL_dv2proj_u(dv2 v, dv2 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_dv2sub(v, SL_dv2align_u(v, n));
}
#else
;
#endif
/// @brief Project dv3 v on plane with normal dv3 n
SL_header dv3 SL_dv3proj_u(dv3 v, dv3 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_dv3sub(v, SL_dv3align_u(v, n));
}
#else
;
#endif
/// @brief Project dv4 v on plane with normal dv4 n
SL_header dv4 SL_dv4proj_u(dv4 v, dv4 n)
#if defined(SL_IMPLEMENTATION)
{
    return SL_dv4sub(v, SL_dv4align_u(v, n));
}
#else
;
#endif
/// @brief Component-wise modulo of a dv by scalar n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header double* SL_dvmods_(double* v, double n, double* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = fmod(v[i], n);
    return dest;
}
#else
;
#endif
/// @brief Component-wise modulo of a dv by scalar n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header dv SL_dvmods(dv v, double n, dv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_dvmods_(v.data, n, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise modulo of a dv2 by scalar n
SL_header dv2 SL_dv2mods(dv2 v, double n)
#if defined(SL_IMPLEMENTATION)
{
    return (dv2) {
        .x = fmod(v.x, n),
        .y = fmod(v.y, n)
    };
}
#else
;
#endif
/// @brief Component-wise modulo of a dv3 by scalar n
SL_header dv3 SL_dv3mods(dv3 v, double n)
#if defined(SL_IMPLEMENTATION)
{
    return (dv3) {
        .x = fmod(v.x, n),
        .y = fmod(v.y, n),
        .z = fmod(v.z, n)
    };
}
#else
;
#endif
/// @brief Component-wise modulo of a dv4 by scalar n
SL_header dv4 SL_dv4mods(dv4 v, double n)
#if defined(SL_IMPLEMENTATION)
{
    return (dv4) {
        .x = fmod(v.x, n),
        .y = fmod(v.y, n),
        .z = fmod(v.z, n),
        .w = fmod(v.w, n)
    };
}
#else
;
#endif
/// @brief Component-wise modulo of a dv by dv n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header double* SL_dvmod_(double* v, double* n, double* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = fmod(v[i], n[i]);
    return dest;
}
#else
;
#endif
/// @brief Component-wise modulo of a dv by dv n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header dv SL_dvmod(dv v, dv n, dv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_dvmod_(v.data, n.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise modulo of a dv2 by dv2 n
SL_header dv2 SL_dv2mod(dv2 v, dv2 n)
#if defined(SL_IMPLEMENTATION)
{
    return (dv2) {
        .x = fmod(v.x, n.x),
        .y = fmod(v.y, n.y)
    };
}
#else
;
#endif
/// @brief Component-wise modulo of a dv3 by dv3 n
SL_header dv3 SL_dv3mod(dv3 v, dv3 n)
#if defined(SL_IMPLEMENTATION)
{
    return (dv3) {
        .x = fmod(v.x, n.x),
        .y = fmod(v.y, n.y),
        .z = fmod(v.z, n.z)
    };
}
#else
;
#endif
/// @brief Component-wise modulo of a dv4 by dv4 n
SL_header dv4 SL_dv4mod(dv4 v, dv4 n)
#if defined(SL_IMPLEMENTATION)
{
    return (dv4) {
        .x = fmod(v.x, n.x),
        .y = fmod(v.y, n.y),
        .z = fmod(v.z, n.z),
        .w = fmod(v.w, n.w)
    };
}
#else
;
#endif
/// @brief Normalization of a dv
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header double* SL_dvnorm_(double* v, double* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    double inv_len = 1.0 / SL_dvlen_(v, count);
    for (usize i = 0; i < count; ++i) dest[i] = v[i] * inv_len;
    return dest;
}
#else
;
#endif
/// @brief Normalization of a dv
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header dv SL_dvnorm(dv v, dv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_dvnorm_(v.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Normalization of a dv2
SL_header dv2 SL_dv2norm(dv2 v)
#if defined(SL_IMPLEMENTATION)
{
    double inv_len = 1.0 / SL_dv2len(v);
    return (dv2) {
        .x = v.x * inv_len,
        .y = v.y * inv_len
    };
}
#else
;
#endif
/// @brief Normalization of a dv3
SL_header dv3 SL_dv3norm(dv3 v)
#if defined(SL_IMPLEMENTATION)
{
    double inv_len = 1.0 / SL_dv3len(v);
    return (dv3) {
        .x = v.x * inv_len,
        .y = v.y * inv_len,
        .z = v.z * inv_len
    };
}
#else
;
#endif
/// @brief Normalization of a dv4
SL_header dv4 SL_dv4norm(dv4 v)
#if defined(SL_IMPLEMENTATION)
{
    double inv_len = 1.0 / SL_dv4len(v);
    return (dv4) {
        .x = v.x * inv_len,
        .y = v.y * inv_len,
        .z = v.z * inv_len,
        .w = v.w * inv_len
    };
}
#else
;
#endif
/// @brief Component-wise flooring of a dv
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header double* SL_dvfloor_(double* v, double* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = floor(v[i]);
    return dest;
}
#else
;
#endif
/// @brief Component-wise flooring of a dv
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header dv SL_dvfloor(dv v, dv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_dvfloor_(v.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise flooring of a dv2
SL_header dv2 SL_dv2floor(dv2 v)
#if defined(SL_IMPLEMENTATION)
{
    return (dv2) {
        .x = floor(v.x),
        .y = floor(v.y)
    };
}
#else
;
#endif
/// @brief Component-wise flooring of a dv3
SL_header dv3 SL_dv3floor(dv3 v)
#if defined(SL_IMPLEMENTATION)
{
    return (dv3) {
        .x = floor(v.x),
        .y = floor(v.y),
        .z = floor(v.z)
    };
}
#else
;
#endif
/// @brief Component-wise flooring of a dv4
SL_header dv4 SL_dv4floor(dv4 v)
#if defined(SL_IMPLEMENTATION)
{
    return (dv4) {
        .x = floor(v.x),
        .y = floor(v.y),
        .z = floor(v.z),
        .w = floor(v.w)
    };
}
#else
;
#endif
/// @brief Component-wise ceiling of a dv
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header double* SL_dvceil_(double* v, double* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = ceil(v[i]);
    return dest;
}
#else
;
#endif
/// @brief Component-wise ceiling of a dv
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header dv SL_dvceil(dv v, dv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_dvceil_(v.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise ceiling of a dv2
SL_header dv2 SL_dv2ceil(dv2 v)
#if defined(SL_IMPLEMENTATION)
{
    return (dv2) {
        .x = ceil(v.x),
        .y = ceil(v.y)
    };
}
#else
;
#endif
/// @brief Component-wise ceiling of a dv3
SL_header dv3 SL_dv3ceil(dv3 v)
#if defined(SL_IMPLEMENTATION)
{
    return (dv3) {
        .x = ceil(v.x),
        .y = ceil(v.y),
        .z = ceil(v.z)
    };
}
#else
;
#endif
/// @brief Component-wise ceiling of a dv4
SL_header dv4 SL_dv4ceil(dv4 v)
#if defined(SL_IMPLEMENTATION)
{
    return (dv4) {
        .x = ceil(v.x),
        .y = ceil(v.y),
        .z = ceil(v.z),
        .w = ceil(v.w)
    };
}
#else
;
#endif
/// @brief Component-wise fractional part of a dv
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header double* SL_dvfrac_(double* v, double* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = v[i] - floor(v[i]);
    return dest;
}
#else
;
#endif
/// @brief Component-wise fractional part of a dv
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header dv SL_dvfrac(dv v, dv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_dvfrac_(v.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise fractional part of a dv2
SL_header dv2 SL_dv2frac(dv2 v)
#if defined(SL_IMPLEMENTATION)
{
    return (dv2) {
        .x = v.x - floor(v.x),
        .y = v.y - floor(v.y)
    };
}
#else
;
#endif
/// @brief Component-wise fractional part of a dv3
SL_header dv3 SL_dv3frac(dv3 v)
#if defined(SL_IMPLEMENTATION)
{
    return (dv3) {
        .x = v.x - floor(v.x),
        .y = v.y - floor(v.y),
        .z = v.z - floor(v.z)
    };
}
#else
;
#endif
/// @brief Component-wise fractional part of a dv4
SL_header dv4 SL_dv4frac(dv4 v)
#if defined(SL_IMPLEMENTATION)
{
    return (dv4) {
        .x = v.x - floor(v.x),
        .y = v.y - floor(v.y),
        .z = v.z - floor(v.z),
        .w = v.w - floor(v.w)
    };
}
#else
;
#endif
/// @brief Linear interpolation of two dv
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header double* SL_dvlerp_(double* lhs, double* rhs, double t, double* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] + (rhs[i] - lhs[i]) * t;
    return dest;
}
#else
;
#endif
/// @brief Linear interpolation of two dv
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header dv SL_dvlerp(dv lhs, dv rhs, double t, dv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_dvlerp_(lhs.data, rhs.data, t, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Linear interpolation of two dv2
SL_header dv2 SL_dv2lerp(dv2 lhs, dv2 rhs, double t)
#if defined(SL_IMPLEMENTATION)
{
    return (dv2) {
        .x = lhs.x + (rhs.x - lhs.x) * t,
        .y = lhs.y + (rhs.y - lhs.y) * t
    };
}
#else
;
#endif
/// @brief Linear interpolation of two dv3
SL_header dv3 SL_dv3lerp(dv3 lhs, dv3 rhs, double t)
#if defined(SL_IMPLEMENTATION)
{
    return (dv3) {
        .x = lhs.x + (rhs.x - lhs.x) * t,
        .y = lhs.y + (rhs.y - lhs.y) * t,
        .z = lhs.z + (rhs.z - lhs.z) * t
    };
}
#else
;
#endif
/// @brief Linear interpolation of two dv4
SL_header dv4 SL_dv4lerp(dv4 lhs, dv4 rhs, double t)
#if defined(SL_IMPLEMENTATION)
{
    return (dv4) {
        .x = lhs.x + (rhs.x - lhs.x) * t,
        .y = lhs.y + (rhs.y - lhs.y) * t,
        .z = lhs.z + (rhs.z - lhs.z) * t,
        .w = lhs.w + (rhs.w - lhs.w) * t
    };
}
#else
;
#endif
/// @brief Spherical interpolation of two dv2
SL_header dv2 SL_dv2serp(dv2 lhs, dv2 rhs, double t)
#if defined(SL_IMPLEMENTATION)
{
    double angle = acos(SL_dv2dot(SL_dv2norm(lhs), SL_dv2norm(rhs)));
    double inv_sin = 1.0 / sin(angle);
    double a = sin(angle * t) * inv_sin;
    double b = sin(angle * (1 - t)) * inv_sin;
    return (dv2) {
        .x = lhs.x * a + rhs.x * b,
        .y = lhs.y * a + rhs.y * b
    };
}
#else
;
#endif
/// @brief Spherical interpolation of two dv3
SL_header dv3 SL_dv3serp(dv3 lhs, dv3 rhs, double t)
#if defined(SL_IMPLEMENTATION)
{
    double angle = acos(SL_dv3dot(SL_dv3norm(lhs), SL_dv3norm(rhs)));
    double inv_sin = 1.0 / sin(angle);
    double a = sin(angle * t) * inv_sin;
    double b = sin(angle * (1 - t)) * inv_sin;
    return (dv3) {
        .x = lhs.x * a + rhs.x * b,
        .y = lhs.y * a + rhs.y * b,
        .z = lhs.z * a + rhs.z * b
    };
}
#else
;
#endif
/// @brief Spherical interpolation of two dv4
SL_header dv4 SL_dv4serp(dv4 lhs, dv4 rhs, double t)
#if defined(SL_IMPLEMENTATION)
{
    double angle = acos(SL_dv4dot(SL_dv4norm(lhs), SL_dv4norm(rhs)));
    double inv_sin = 1.0 / sin(angle);
    double a = sin(angle * t) * inv_sin;
    double b = sin(angle * (1 - t)) * inv_sin;
    return (dv4) {
        .x = lhs.x * a + rhs.x * b,
        .y = lhs.y * a + rhs.y * b,
        .z = lhs.z * a + rhs.z * b,
        .w = lhs.w * a + rhs.w * b
    };
}
#else
;
#endif
/// @brief Angle on the 2D plane formed by a dv2
SL_header double SL_dv2angle(dv2 v)
#if defined(SL_IMPLEMENTATION)
{
    return atan2(v.y, v.x);
}
#else
;
#endif
/// @brief Unit dv2 oriented based on given angle
SL_header dv2 SL_dv2from_angle(double angle)
#if defined(SL_IMPLEMENTATION)
{
    double c, s; sincos(angle, &s, &c);
    return SL_dv2_(c, s);
}
#else
;
#endif
/// @brief Unit dv3 oriented based on given angles
SL_header dv3 SL_dv3from_yawPitch(double yaw, double pitch)
#if defined(SL_IMPLEMENTATION)
{
    double cy, sy; sincos(yaw, &sy, &cy);
    double cp, sp; sincos(pitch, &sp, &cp);
    return SL_dv3_(sy * cp, sp, cy * cp);
}
#else
;
#endif
/// @brief Rotate dv2 by angle encoded by `cosa` and `sina`
SL_header dv2 SL_dv2rot_sc(dv2 v, double sina, double cosa)
#if defined(SL_IMPLEMENTATION)
{
    return SL_dv2_(v.x * cosa - v.y * sina, v.y * cosa + v.x * sina);
}
#else
;
#endif
/// @brief Rotate dv2 by angle encoded in vector `cs`
SL_header dv2 SL_dv2rot_cs(dv2 v, dv2 cs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_dv2_(v.x * cs.x - v.y * cs.y, v.x * cs.y + v.y * cs.x);
}
#else
;
#endif
/// @brief Rotate dv2 by angle
SL_header dv2 SL_dv2rot(dv2 v, double a)
#if defined(SL_IMPLEMENTATION)
{
    double sina, cosa; sincos(a, &sina, &cosa);
    return SL_dv2rot_sc(v, sina, cosa);
}
#else
;
#endif
/// @brief Cross-product of two dv2
SL_header double SL_dv2cross(dv2 lhs, dv2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x * rhs.y - lhs.y * rhs.x;
}
#else
;
#endif
/// @brief Cross-product of two dv3
SL_header dv3 SL_dv3cross(dv3 lhs, dv3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (dv3) {
        .x = lhs.y * rhs.z - lhs.z * rhs.y,
        .y = lhs.z * rhs.x - lhs.x * rhs.z,
        .z = lhs.x * rhs.y - lhs.y * rhs.x
    };
}
#else
;
#endif
#pragma endregion DOUBLE
#pragma region BOOL

/// @brief Vector of bool with arbitrary dimension
typedef struct {
    const usize count;
    bool *data;
} bv;

/// @brief Vector of bool with dimension 2
typedef union {
    bool data[2];
    struct {
        union { bool x, r, u; };
        union { bool y, g, v; };
    };
} bv2;

#define SL_bv2_zero  ((bv2){.x =  0, .y =  0})
#define SL_bv2_one   ((bv2){.x =  1, .y =  1})
#define SL_bv2_right ((bv2){.x =  1, .y =  0})
#define SL_bv2_up    ((bv2){.x =  0, .y =  1})

/// @brief Vector of bool with dimension 3
typedef union {
    bool data[3];
    struct {
        union { bool x, r, u; };
        union { bool y, g, v; };
        union { bool z, b, s; };
    };
    struct {
        union { bool __x, __r, __u; };
        union { bv2 yz, gb, vs; };
    };
    struct {
        union { bv2 xy, rg, uv; };
        union { bool __z, __b, __s; };
    };
} bv3;

#define SL_bv3_zero  ((bv3){.x =  0, .y =  0, .z =  0})
#define SL_bv3_one   ((bv3){.x =  1, .y =  1, .z =  1})
#define SL_bv3_right ((bv3){.x =  1, .y =  0, .z =  0})
#define SL_bv3_up    ((bv3){.x =  0, .y =  1, .z =  0})
#define SL_bv3_forw  ((bv3){.x =  0, .y =  0, .z =  1})

/// @brief Vector of bool with dimension 4
typedef union {
    bool data[4];
    struct {
        union { bool x, r, u; };
        union { bool y, g, v; };
        union { bool z, b, s; };
        union { bool w, a, t; };
    };
    struct {
        union { bool __x0, __r0, __u0; };
        union { bv2 yz, gb, vs; };
        union { bool __w0, __a0, __t0; };
    };
    struct {
        union { bv2 xy, rb, uv; };
        union { bv2 zw, ba, st; };
    };
    struct {
        union { bv3 xyz, rgb, uvs; };
        union { bool __w1, __a1, __t1; };
    };
    struct {
        union { bool __x1, __r1, __u1; };
        union { bv3 yzw, gba, vst; };
    };
} bv4;

#define SL_bv4_zero  ((bv4){.x = 0, .y = 0, .z = 0, .w = 0})
#define SL_bv4_one   ((bv4){.x = 1, .y = 1, .z = 1, .w = 1})

#define SL_bv4_white  ((bv4){.x = 1, .y = 1, .z = 1, .w = 1})
#define SL_bv4_black  ((bv4){.x = 0, .y = 0, .z = 0, .w = 1})
#define SL_bv4_red    ((bv4){.x = 1, .y = 0, .z = 0, .w = 1})
#define SL_bv4_green  ((bv4){.x = 0, .y = 1, .z = 0, .w = 1})
#define SL_bv4_blue   ((bv4){.x = 0, .y = 0, .z = 1, .w = 1})
#define SL_bv4_yellow ((bv4){.x = 1, .y = 1, .z = 0, .w = 1})
#define SL_bv4_cyan   ((bv4){.x = 0, .y = 1, .z = 1, .w = 1})
#define SL_bv4_purple ((bv4){.x = 1, .y = 0, .z = 1, .w = 1})



#define SL_bv2_(X, Y)       ((bv2){.x = X, .y = Y})
#define SL_bv3_(X, Y, Z)    ((bv3){.x = X, .y = Y, .z = Z})
#define SL_bv4_(X, Y, Z, W) ((bv4){.x = X, .y = Y, .z = Z, .w = W})

#define SL_bv2s(S)          ((bv2){.x = S, .y = S})
#define SL_bv3s(S)          ((bv3){.x = S, .y = S, .z = S})
#define SL_bv4s(S)          ((bv4){.x = S, .y = S, .z = S, .w = S})

#define SL_bvv(V)           ((bv){.count = vsize(V), .data = (V).data})
#define SL_bv2v(V, ...)     ((bv2){.x = (V).x, .y = (V).y})
#define SL_bv3v(V, ...)     ((bv3){.x = (V).x, .y = (V).y, .z = (SL_vsize(V) >= 3 ? (V).data[2] : (0, ##__VA_ARGS__))})
#define SL_bv4v(V, ...)     ((bv4){.x = (V).x, .y = (V).y, .z = (SL_vsize(V) >= 3 ? (V).data[2] : ((const float[]){0, ##__VA_ARGS__, 0})[1]), .w = (SL_vsize(V) >= 4 ? (V).data[3] : ((const float[]){0, ##__VA_ARGS__, 0, 0})[2])})



/// @brief Equality of two bv
/// @note All vectors are assumed to be of size 'count'
SL_header bool SL_bvequ_(bool* lhs, bool* rhs, usize count)
#if defined(SL_IMPLEMENTATION)
{
    bool dest = true;
    for (usize i = 0; i < count; ++i) dest &= lhs[i] == rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Equality of two bv
/// @note All vectors are assumed to be of size 'count'
SL_header bool SL_bvequ(bv lhs, bv rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_bvequ_(lhs.data, rhs.data, lhs.count);
}
#else
;
#endif
/// @brief Equality of two bv2
SL_header bool SL_bv2equ(bv2 lhs, bv2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}
#else
;
#endif
/// @brief Equality of two bv3
SL_header bool SL_bv3equ(bv3 lhs, bv3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}
#else
;
#endif
/// @brief Equality of two bv4
SL_header bool SL_bv4equ(bv4 lhs, bv4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
}
#else
;
#endif
/// @brief Addition of two bv
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header bool* SL_bvadd_(bool* lhs, bool* rhs, bool* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] + rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Addition of two bv
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header bv SL_bvadd(bv lhs, bv rhs, bv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_bvadd_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two bv2
SL_header bv2 SL_bv2add(bv2 lhs, bv2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bv2) {
        .x = lhs.x + rhs.x,
        .y = lhs.y + rhs.y
    };
}
#else
;
#endif
/// @brief Addition of two bv3
SL_header bv3 SL_bv3add(bv3 lhs, bv3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bv3) {
        .x = lhs.x + rhs.x,
        .y = lhs.y + rhs.y,
        .z = lhs.z + rhs.z
    };
}
#else
;
#endif
/// @brief Addition of two bv4
SL_header bv4 SL_bv4add(bv4 lhs, bv4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bv4) {
        .x = lhs.x + rhs.x,
        .y = lhs.y + rhs.y,
        .z = lhs.z + rhs.z,
        .w = lhs.w + rhs.w
    };
}
#else
;
#endif
/// @brief Difference of two bv
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header bool* SL_bvsub_(bool* lhs, bool* rhs, bool* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] - rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Difference of two bv
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header bv SL_bvsub(bv lhs, bv rhs, bv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_bvsub_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two bv2
SL_header bv2 SL_bv2sub(bv2 lhs, bv2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bv2) {
        .x = lhs.x - rhs.x,
        .y = lhs.y - rhs.y
    };
}
#else
;
#endif
/// @brief Difference of two bv3
SL_header bv3 SL_bv3sub(bv3 lhs, bv3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bv3) {
        .x = lhs.x - rhs.x,
        .y = lhs.y - rhs.y,
        .z = lhs.z - rhs.z
    };
}
#else
;
#endif
/// @brief Difference of two bv4
SL_header bv4 SL_bv4sub(bv4 lhs, bv4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bv4) {
        .x = lhs.x - rhs.x,
        .y = lhs.y - rhs.y,
        .z = lhs.z - rhs.z,
        .w = lhs.w - rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of two bv
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header bool* SL_bvmul_(bool* lhs, bool* rhs, bool* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise multiplication of two bv
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header bv SL_bvmul(bv lhs, bv rhs, bv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_bvmul_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise multiplication of two bv2
SL_header bv2 SL_bv2mul(bv2 lhs, bv2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bv2) {
        .x = lhs.x * rhs.x,
        .y = lhs.y * rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of two bv3
SL_header bv3 SL_bv3mul(bv3 lhs, bv3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bv3) {
        .x = lhs.x * rhs.x,
        .y = lhs.y * rhs.y,
        .z = lhs.z * rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of two bv4
SL_header bv4 SL_bv4mul(bv4 lhs, bv4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bv4) {
        .x = lhs.x * rhs.x,
        .y = lhs.y * rhs.y,
        .z = lhs.z * rhs.z,
        .w = lhs.w * rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of a bv with a scalar
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header bool* SL_bvmuls_(bool* lhs, bool rhs, bool* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * rhs;
    return dest;
}
#else
;
#endif
/// @brief Component-wise multiplication of a bv with a scalar
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header bv SL_bvmuls(bv lhs, bool rhs, bv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_bvmuls_(lhs.data, rhs, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise multiplication of a bv2 with a scalar
SL_header bv2 SL_bv2muls(bv2 lhs, bool rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bv2) {
        .x = lhs.x * rhs,
        .y = lhs.y * rhs
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of a bv3 with a scalar
SL_header bv3 SL_bv3muls(bv3 lhs, bool rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bv3) {
        .x = lhs.x * rhs,
        .y = lhs.y * rhs,
        .z = lhs.z * rhs
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of a bv4 with a scalar
SL_header bv4 SL_bv4muls(bv4 lhs, bool rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bv4) {
        .x = lhs.x * rhs,
        .y = lhs.y * rhs,
        .z = lhs.z * rhs,
        .w = lhs.w * rhs
    };
}
#else
;
#endif
/// @brief Component-wise division of two bv
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header bool* SL_bvdiv_(bool* lhs, bool* rhs, bool* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] / rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise division of two bv
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header bv SL_bvdiv(bv lhs, bv rhs, bv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_bvdiv_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise division of two bv2
SL_header bv2 SL_bv2div(bv2 lhs, bv2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bv2) {
        .x = lhs.x / rhs.x,
        .y = lhs.y / rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise division of two bv3
SL_header bv3 SL_bv3div(bv3 lhs, bv3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bv3) {
        .x = lhs.x / rhs.x,
        .y = lhs.y / rhs.y,
        .z = lhs.z / rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise division of two bv4
SL_header bv4 SL_bv4div(bv4 lhs, bv4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bv4) {
        .x = lhs.x / rhs.x,
        .y = lhs.y / rhs.y,
        .z = lhs.z / rhs.z,
        .w = lhs.w / rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise division of a bv with a scalar
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header bool* SL_bvdivs_(bool* lhs, bool rhs, bool* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] / rhs;
    return dest;
}
#else
;
#endif
/// @brief Component-wise division of a bv with a scalar
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header bv SL_bvdivs(bv lhs, bool rhs, bv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_bvdivs_(lhs.data, rhs, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise division of a bv2 with a scalar
SL_header bv2 SL_bv2divs(bv2 lhs, bool rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bv2) {
        .x = lhs.x / rhs,
        .y = lhs.y / rhs
    };
}
#else
;
#endif
/// @brief Component-wise division of a bv3 with a scalar
SL_header bv3 SL_bv3divs(bv3 lhs, bool rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bv3) {
        .x = lhs.x / rhs,
        .y = lhs.y / rhs,
        .z = lhs.z / rhs
    };
}
#else
;
#endif
/// @brief Component-wise division of a bv4 with a scalar
SL_header bv4 SL_bv4divs(bv4 lhs, bool rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bv4) {
        .x = lhs.x / rhs,
        .y = lhs.y / rhs,
        .z = lhs.z / rhs,
        .w = lhs.w / rhs
    };
}
#else
;
#endif
/// @brief Addition of two bv with lhs scaled by a bool
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header bool* SL_bvaddS_(bool* lhs, bool* rhs, bool s, bool* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] + rhs[i] * s;
    return dest;
}
#else
;
#endif
/// @brief Addition of two bv with lhs scaled by a bool
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header bv SL_bvaddS(bv lhs, bv rhs, bool s, bv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_bvaddS_(lhs.data, rhs.data, s, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two bv2 with lhs scaled by a bool
SL_header bv2 SL_bv2addS(bv2 lhs, bv2 rhs, bool s)
#if defined(SL_IMPLEMENTATION)
{
    return (bv2) {
        .x = lhs.x + rhs.x * s,
        .y = lhs.y + rhs.y * s
    };
}
#else
;
#endif
/// @brief Addition of two bv3 with lhs scaled by a bool
SL_header bv3 SL_bv3addS(bv3 lhs, bv3 rhs, bool s)
#if defined(SL_IMPLEMENTATION)
{
    return (bv3) {
        .x = lhs.x + rhs.x * s,
        .y = lhs.y + rhs.y * s,
        .z = lhs.z + rhs.z * s
    };
}
#else
;
#endif
/// @brief Addition of two bv4 with lhs scaled by a bool
SL_header bv4 SL_bv4addS(bv4 lhs, bv4 rhs, bool s)
#if defined(SL_IMPLEMENTATION)
{
    return (bv4) {
        .x = lhs.x + rhs.x * s,
        .y = lhs.y + rhs.y * s,
        .z = lhs.z + rhs.z * s,
        .w = lhs.w + rhs.w * s
    };
}
#else
;
#endif
/// @brief Difference of two bv with lhs scaled by a bool
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header bool* SL_bvsubS_(bool* lhs, bool* rhs, bool s, bool* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] - rhs[i] * s;
    return dest;
}
#else
;
#endif
/// @brief Difference of two bv with lhs scaled by a bool
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header bv SL_bvsubS(bv lhs, bv rhs, bool s, bv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_bvsubS_(lhs.data, rhs.data, s, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two bv2 with lhs scaled by a bool
SL_header bv2 SL_bv2subS(bv2 lhs, bv2 rhs, bool s)
#if defined(SL_IMPLEMENTATION)
{
    return (bv2) {
        .x = lhs.x - rhs.x * s,
        .y = lhs.y - rhs.y * s
    };
}
#else
;
#endif
/// @brief Difference of two bv3 with lhs scaled by a bool
SL_header bv3 SL_bv3subS(bv3 lhs, bv3 rhs, bool s)
#if defined(SL_IMPLEMENTATION)
{
    return (bv3) {
        .x = lhs.x - rhs.x * s,
        .y = lhs.y - rhs.y * s,
        .z = lhs.z - rhs.z * s
    };
}
#else
;
#endif
/// @brief Difference of two bv4 with lhs scaled by a bool
SL_header bv4 SL_bv4subS(bv4 lhs, bv4 rhs, bool s)
#if defined(SL_IMPLEMENTATION)
{
    return (bv4) {
        .x = lhs.x - rhs.x * s,
        .y = lhs.y - rhs.y * s,
        .z = lhs.z - rhs.z * s,
        .w = lhs.w - rhs.w * s
    };
}
#else
;
#endif
/// @brief Addition of two bv with lhs multiplied with a bool
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header bool* SL_bvaddM_(bool* lhs, bool* rhs, bool* m, bool* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] + rhs[i] * m[i];
    return dest;
}
#else
;
#endif
/// @brief Addition of two bv with lhs multiplied with a bool
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header bv SL_bvaddM(bv lhs, bv rhs, bv m, bv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_bvaddM_(lhs.data, rhs.data, m.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two bv2 with lhs multiplied with a bool
SL_header bv2 SL_bv2addM(bv2 lhs, bv2 rhs, bv2 m)
#if defined(SL_IMPLEMENTATION)
{
    return (bv2) {
        .x = lhs.x + rhs.x * m.x,
        .y = lhs.y + rhs.y * m.y
    };
}
#else
;
#endif
/// @brief Addition of two bv3 with lhs multiplied with a bool
SL_header bv3 SL_bv3addM(bv3 lhs, bv3 rhs, bv3 m)
#if defined(SL_IMPLEMENTATION)
{
    return (bv3) {
        .x = lhs.x + rhs.x * m.x,
        .y = lhs.y + rhs.y * m.y,
        .z = lhs.z + rhs.z * m.z
    };
}
#else
;
#endif
/// @brief Addition of two bv4 with lhs multiplied with a bool
SL_header bv4 SL_bv4addM(bv4 lhs, bv4 rhs, bv4 m)
#if defined(SL_IMPLEMENTATION)
{
    return (bv4) {
        .x = lhs.x + rhs.x * m.x,
        .y = lhs.y + rhs.y * m.y,
        .z = lhs.z + rhs.z * m.z,
        .w = lhs.w + rhs.w * m.w
    };
}
#else
;
#endif
/// @brief Difference of two bv with lhs multiplied with a bool
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header bool* SL_bvsubM_(bool* lhs, bool* rhs, bool* m, bool* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] - rhs[i] * m[i];
    return dest;
}
#else
;
#endif
/// @brief Difference of two bv with lhs multiplied with a bool
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header bv SL_bvsubM(bv lhs, bv rhs, bv m, bv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_bvsubM_(lhs.data, rhs.data, m.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two bv2 with lhs multiplied with a bool
SL_header bv2 SL_bv2subM(bv2 lhs, bv2 rhs, bv2 m)
#if defined(SL_IMPLEMENTATION)
{
    return (bv2) {
        .x = lhs.x - rhs.x * m.x,
        .y = lhs.y - rhs.y * m.y
    };
}
#else
;
#endif
/// @brief Difference of two bv3 with lhs multiplied with a bool
SL_header bv3 SL_bv3subM(bv3 lhs, bv3 rhs, bv3 m)
#if defined(SL_IMPLEMENTATION)
{
    return (bv3) {
        .x = lhs.x - rhs.x * m.x,
        .y = lhs.y - rhs.y * m.y,
        .z = lhs.z - rhs.z * m.z
    };
}
#else
;
#endif
/// @brief Difference of two bv4 with lhs multiplied with a bool
SL_header bv4 SL_bv4subM(bv4 lhs, bv4 rhs, bv4 m)
#if defined(SL_IMPLEMENTATION)
{
    return (bv4) {
        .x = lhs.x - rhs.x * m.x,
        .y = lhs.y - rhs.y * m.y,
        .z = lhs.z - rhs.z * m.z,
        .w = lhs.w - rhs.w * m.w
    };
}
#else
;
#endif
/// @brief Addition of two bv with lhs scaled by bool and multiplied with a bool
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header bool* SL_bvaddSM_(bool* lhs, bool* rhs, bool s, bool* m, bool* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] + rhs[i] * s * m[i];
    return dest;
}
#else
;
#endif
/// @brief Addition of two bv with lhs scaled by bool and multiplied with a bool
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header bv SL_bvaddSM(bv lhs, bv rhs, bool s, bv m, bv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_bvaddSM_(lhs.data, rhs.data, s, m.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two bv2 with lhs scaled by bool and multiplied with a bool
SL_header bv2 SL_bv2addSM(bv2 lhs, bv2 rhs, bool s, bv2 m)
#if defined(SL_IMPLEMENTATION)
{
    return (bv2) {
        .x = lhs.x + rhs.x * s * m.x,
        .y = lhs.y + rhs.y * s * m.y
    };
}
#else
;
#endif
/// @brief Addition of two bv3 with lhs scaled by bool and multiplied with a bool
SL_header bv3 SL_bv3addSM(bv3 lhs, bv3 rhs, bool s, bv3 m)
#if defined(SL_IMPLEMENTATION)
{
    return (bv3) {
        .x = lhs.x + rhs.x * s * m.x,
        .y = lhs.y + rhs.y * s * m.y,
        .z = lhs.z + rhs.z * s * m.z
    };
}
#else
;
#endif
/// @brief Addition of two bv4 with lhs scaled by bool and multiplied with a bool
SL_header bv4 SL_bv4addSM(bv4 lhs, bv4 rhs, bool s, bv4 m)
#if defined(SL_IMPLEMENTATION)
{
    return (bv4) {
        .x = lhs.x + rhs.x * s * m.x,
        .y = lhs.y + rhs.y * s * m.y,
        .z = lhs.z + rhs.z * s * m.z,
        .w = lhs.w + rhs.w * s * m.w
    };
}
#else
;
#endif
/// @brief Difference of two bv with lhs scaled by bool and multiplied with a bool
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header bool* SL_bvsubSM_(bool* lhs, bool* rhs, bool s, bool* m, bool* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] - rhs[i] * s * m[i];
    return dest;
}
#else
;
#endif
/// @brief Difference of two bv with lhs scaled by bool and multiplied with a bool
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header bv SL_bvsubSM(bv lhs, bv rhs, bool s, bv m, bv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_bvsubSM_(lhs.data, rhs.data, s, m.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two bv2 with lhs scaled by bool and multiplied with a bool
SL_header bv2 SL_bv2subSM(bv2 lhs, bv2 rhs, bool s, bv2 m)
#if defined(SL_IMPLEMENTATION)
{
    return (bv2) {
        .x = lhs.x - rhs.x * s * m.x,
        .y = lhs.y - rhs.y * s * m.y
    };
}
#else
;
#endif
/// @brief Difference of two bv3 with lhs scaled by bool and multiplied with a bool
SL_header bv3 SL_bv3subSM(bv3 lhs, bv3 rhs, bool s, bv3 m)
#if defined(SL_IMPLEMENTATION)
{
    return (bv3) {
        .x = lhs.x - rhs.x * s * m.x,
        .y = lhs.y - rhs.y * s * m.y,
        .z = lhs.z - rhs.z * s * m.z
    };
}
#else
;
#endif
/// @brief Difference of two bv4 with lhs scaled by bool and multiplied with a bool
SL_header bv4 SL_bv4subSM(bv4 lhs, bv4 rhs, bool s, bv4 m)
#if defined(SL_IMPLEMENTATION)
{
    return (bv4) {
        .x = lhs.x - rhs.x * s * m.x,
        .y = lhs.y - rhs.y * s * m.y,
        .z = lhs.z - rhs.z * s * m.z,
        .w = lhs.w - rhs.w * s * m.w
    };
}
#else
;
#endif
/// @brief Addition of two bv with rhs scaled by a bool
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header bool* SL_bvSadd_(bool* lhs, bool s, bool* rhs, bool* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * s + rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Addition of two bv with rhs scaled by a bool
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header bv SL_bvSadd(bv lhs, bool s, bv rhs, bv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_bvSadd_(lhs.data, s, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Addition of two bv2 with rhs scaled by a bool
SL_header bv2 SL_bv2Sadd(bv2 lhs, bool s, bv2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bv2) {
        .x = lhs.x * s + rhs.x,
        .y = lhs.y * s + rhs.y
    };
}
#else
;
#endif
/// @brief Addition of two bv3 with rhs scaled by a bool
SL_header bv3 SL_bv3Sadd(bv3 lhs, bool s, bv3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bv3) {
        .x = lhs.x * s + rhs.x,
        .y = lhs.y * s + rhs.y,
        .z = lhs.z * s + rhs.z
    };
}
#else
;
#endif
/// @brief Addition of two bv4 with rhs scaled by a bool
SL_header bv4 SL_bv4Sadd(bv4 lhs, bool s, bv4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bv4) {
        .x = lhs.x * s + rhs.x,
        .y = lhs.y * s + rhs.y,
        .z = lhs.z * s + rhs.z,
        .w = lhs.w * s + rhs.w
    };
}
#else
;
#endif
/// @brief Difference of two bv with rhs scaled by a bool
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header bool* SL_bvSsub_(bool* lhs, bool s, bool* rhs, bool* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * s - rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Difference of two bv with rhs scaled by a bool
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header bv SL_bvSsub(bv lhs, bool s, bv rhs, bv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_bvSsub_(lhs.data, s, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Difference of two bv2 with rhs scaled by a bool
SL_header bv2 SL_bv2Ssub(bv2 lhs, bool s, bv2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bv2) {
        .x = lhs.x * s - rhs.x,
        .y = lhs.y * s - rhs.y
    };
}
#else
;
#endif
/// @brief Difference of two bv3 with rhs scaled by a bool
SL_header bv3 SL_bv3Ssub(bv3 lhs, bool s, bv3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bv3) {
        .x = lhs.x * s - rhs.x,
        .y = lhs.y * s - rhs.y,
        .z = lhs.z * s - rhs.z
    };
}
#else
;
#endif
/// @brief Difference of two bv4 with rhs scaled by a bool
SL_header bv4 SL_bv4Ssub(bv4 lhs, bool s, bv4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bv4) {
        .x = lhs.x * s - rhs.x,
        .y = lhs.y * s - rhs.y,
        .z = lhs.z * s - rhs.z,
        .w = lhs.w * s - rhs.w
    };
}
#else
;
#endif
/// @brief Weighted sum of two bv
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header bool* SL_bvmix_(bool* lhs, bool lhs_w, bool* rhs, bool rhs_w, bool* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] * lhs_w + rhs[i] * rhs_w;
    return dest;
}
#else
;
#endif
/// @brief Weighted sum of two bv
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header bv SL_bvmix(bv lhs, bool lhs_w, bv rhs, bool rhs_w, bv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_bvmix_(lhs.data, lhs_w, rhs.data, rhs_w, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Weighted sum of two bv2
SL_header bv2 SL_bv2mix(bv2 lhs, bool lhs_w, bv2 rhs, bool rhs_w)
#if defined(SL_IMPLEMENTATION)
{
    return (bv2) {
        .x = lhs.x * lhs_w + rhs.x * rhs_w,
        .y = lhs.y * lhs_w + rhs.y * rhs_w
    };
}
#else
;
#endif
/// @brief Weighted sum of two bv3
SL_header bv3 SL_bv3mix(bv3 lhs, bool lhs_w, bv3 rhs, bool rhs_w)
#if defined(SL_IMPLEMENTATION)
{
    return (bv3) {
        .x = lhs.x * lhs_w + rhs.x * rhs_w,
        .y = lhs.y * lhs_w + rhs.y * rhs_w,
        .z = lhs.z * lhs_w + rhs.z * rhs_w
    };
}
#else
;
#endif
/// @brief Weighted sum of two bv4
SL_header bv4 SL_bv4mix(bv4 lhs, bool lhs_w, bv4 rhs, bool rhs_w)
#if defined(SL_IMPLEMENTATION)
{
    return (bv4) {
        .x = lhs.x * lhs_w + rhs.x * rhs_w,
        .y = lhs.y * lhs_w + rhs.y * rhs_w,
        .z = lhs.z * lhs_w + rhs.z * rhs_w,
        .w = lhs.w * lhs_w + rhs.w * rhs_w
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two bv
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header bool* SL_bvmin_(bool* lhs, bool* rhs, bool* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] < rhs[i] ? lhs[i] : rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise minimum of two bv
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header bv SL_bvmin(bv lhs, bv rhs, bv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_bvmin_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise minimum of two bv2
SL_header bv2 SL_bv2min(bv2 lhs, bv2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bv2) {
        .x = lhs.x < rhs.x ? lhs.x : rhs.x,
        .y = lhs.y < rhs.y ? lhs.y : rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two bv3
SL_header bv3 SL_bv3min(bv3 lhs, bv3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bv3) {
        .x = lhs.x < rhs.x ? lhs.x : rhs.x,
        .y = lhs.y < rhs.y ? lhs.y : rhs.y,
        .z = lhs.z < rhs.z ? lhs.z : rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two bv4
SL_header bv4 SL_bv4min(bv4 lhs, bv4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bv4) {
        .x = lhs.x < rhs.x ? lhs.x : rhs.x,
        .y = lhs.y < rhs.y ? lhs.y : rhs.y,
        .z = lhs.z < rhs.z ? lhs.z : rhs.z,
        .w = lhs.w < rhs.w ? lhs.w : rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two bv
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header bool* SL_bvmax_(bool* lhs, bool* rhs, bool* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] > rhs[i] ? lhs[i] : rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise maximum of two bv
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header bv SL_bvmax(bv lhs, bv rhs, bv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_bvmax_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise maximum of two bv2
SL_header bv2 SL_bv2max(bv2 lhs, bv2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bv2) {
        .x = lhs.x > rhs.x ? lhs.x : rhs.x,
        .y = lhs.y > rhs.y ? lhs.y : rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two bv3
SL_header bv3 SL_bv3max(bv3 lhs, bv3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bv3) {
        .x = lhs.x > rhs.x ? lhs.x : rhs.x,
        .y = lhs.y > rhs.y ? lhs.y : rhs.y,
        .z = lhs.z > rhs.z ? lhs.z : rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two bv4
SL_header bv4 SL_bv4max(bv4 lhs, bv4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bv4) {
        .x = lhs.x > rhs.x ? lhs.x : rhs.x,
        .y = lhs.y > rhs.y ? lhs.y : rhs.y,
        .z = lhs.z > rhs.z ? lhs.z : rhs.z,
        .w = lhs.w > rhs.w ? lhs.w : rhs.w
    };
}
#else
;
#endif
/// @brief Dot product of two bv
/// @note All vectors are assumed to be of size 'count'
SL_header u64 SL_bvdot_(bool* lhs, bool* rhs, usize count)
#if defined(SL_IMPLEMENTATION)
{
    u64 dest = 0;
    for (usize i = 0; i < count; ++i) dest += lhs[i] * rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Dot product of two bv
/// @note All vectors are assumed to be of size 'count'
SL_header u64 SL_bvdot(bv lhs, bv rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_bvdot_(lhs.data, rhs.data, lhs.count);
}
#else
;
#endif
/// @brief Dot product of two bv2
SL_header u64 SL_bv2dot(bv2 lhs, bv2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}
#else
;
#endif
/// @brief Dot product of two bv3
SL_header u64 SL_bv3dot(bv3 lhs, bv3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}
#else
;
#endif
/// @brief Dot product of two bv4
SL_header u64 SL_bv4dot(bv4 lhs, bv4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}
#else
;
#endif
/// @brief Maximum component of a bv
/// @note All vectors are assumed to be of size 'count'
SL_header u64 SL_bvlen_max_(bool* v, usize count)
#if defined(SL_IMPLEMENTATION)
{
    u64 dest = 0;
    for (usize i = 0; i < count; ++i) dest = v[i] > dest ? v[i] : dest;
    return dest;
}
#else
;
#endif
/// @brief Maximum component of a bv
/// @note All vectors are assumed to be of size 'count'
SL_header u64 SL_bvlen_max(bv v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_bvlen_max_(v.data, v.count);
}
#else
;
#endif
/// @brief Maximum component of a bv2
SL_header u64 SL_bv2len_max(bv2 v)
#if defined(SL_IMPLEMENTATION)
{
    return v.x > v.y ? v.x : v.y;
}
#else
;
#endif
/// @brief Maximum component of a bv3
SL_header u64 SL_bv3len_max(bv3 v)
#if defined(SL_IMPLEMENTATION)
{
    return v.x > v.y ? (v.x > v.z ? v.x : v.z) : (v.y > v.z ? v.y : v.z);
}
#else
;
#endif
/// @brief Maximum component of a bv4
SL_header u64 SL_bv4len_max(bv4 v)
#if defined(SL_IMPLEMENTATION)
{
    return v.x > v.y ? (v.x > v.z ? (v.x > v.w ? v.x : v.w) : (v.z > v.w ? v.z : v.w)) : (v.y > v.z ? (v.y > v.w ? v.y : v.w) : (v.z > v.w ? v.z : v.w));
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a bv
/// @note All vectors are assumed to be of size 'count'
SL_header u64 SL_bvlen_manh_(bool* v, usize count)
#if defined(SL_IMPLEMENTATION)
{
    u64 dest = 0;
    for (usize i = 0; i < count; ++i) dest += v[i];
    return dest;
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a bv
/// @note All vectors are assumed to be of size 'count'
SL_header u64 SL_bvlen_manh(bv v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_bvlen_manh_(v.data, v.count);
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a bv2
SL_header u64 SL_bv2len_manh(bv2 v)
#if defined(SL_IMPLEMENTATION)
{
    return v.x + v.y;
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a bv3
SL_header u64 SL_bv3len_manh(bv3 v)
#if defined(SL_IMPLEMENTATION)
{
    return v.x + v.y + v.z;
}
#else
;
#endif
/// @brief Manhattan (or taxicab) length of a bv4
SL_header u64 SL_bv4len_manh(bv4 v)
#if defined(SL_IMPLEMENTATION)
{
    return v.x + v.y + v.z + v.w;
}
#else
;
#endif
/// @brief Squared euclidean length of a bv
/// @note All vectors are assumed to be of size 'count'
SL_header u64 SL_bvlen_srq_(bool* v, usize count)
#if defined(SL_IMPLEMENTATION)
{
    return SL_bvdot_(v, v, count);
}
#else
;
#endif
/// @brief Squared euclidean length of a bv
/// @note All vectors are assumed to be of size 'count'
SL_header u64 SL_bvlen_srq(bv v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_bvlen_srq_(v.data, v.count);
}
#else
;
#endif
/// @brief Square length of a bv2
SL_header u64 SL_bv2len_sqr(bv2 v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_bv2dot(v, v);
}
#else
;
#endif
/// @brief Square length of a bv3
SL_header u64 SL_bv3len_sqr(bv3 v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_bv3dot(v, v);
}
#else
;
#endif
/// @brief Square length of a bv4
SL_header u64 SL_bv4len_sqr(bv4 v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_bv4dot(v, v);
}
#else
;
#endif
/// @brief Euclidean length of a bv
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_bvlen_(bool* v, usize count)
#if defined(SL_IMPLEMENTATION)
{
    return sqrt(SL_bvdot_(v, v, count));
}
#else
;
#endif
/// @brief Euclidean length of a bv
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_bvlen(bv v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_bvlen_(v.data, v.count);
}
#else
;
#endif
/// @brief Euclidean length of a bv2
SL_header double SL_bv2len(bv2 v)
#if defined(SL_IMPLEMENTATION)
{
    return sqrt(SL_bv2dot(v, v));
}
#else
;
#endif
/// @brief Euclidean length of a bv3
SL_header double SL_bv3len(bv3 v)
#if defined(SL_IMPLEMENTATION)
{
    return sqrt(SL_bv3dot(v, v));
}
#else
;
#endif
/// @brief Euclidean length of a bv4
SL_header double SL_bv4len(bv4 v)
#if defined(SL_IMPLEMENTATION)
{
    return sqrt(SL_bv4dot(v, v));
}
#else
;
#endif
/// @brief Euclidean distance bewteen two bv
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_bvdist_(bool* lhs, bool* rhs, usize count)
#if defined(SL_IMPLEMENTATION)
{
    double accum = 0;
    for (int i = 0; i < count; ++i) accum += (lhs[i] - rhs[i]) * (lhs[i] - rhs[i]);
    return sqrt(accum);
}
#else
;
#endif
/// @brief Euclidean distance bewteen two bv
/// @note All vectors are assumed to be of size 'count'
SL_header double SL_bvdist(bv lhs, bv rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_bvdist_(lhs.data, rhs.data, lhs.count);
}
#else
;
#endif
/// @brief Euclidean distance between two bv2
SL_header double SL_bv2dist(bv2 lhs, bv2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_bv2len(SL_bv2sub(lhs, rhs));
}
#else
;
#endif
/// @brief Euclidean distance between two bv3
SL_header double SL_bv3dist(bv3 lhs, bv3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_bv3len(SL_bv3sub(lhs, rhs));
}
#else
;
#endif
/// @brief Euclidean distance between two bv4
SL_header double SL_bv4dist(bv4 lhs, bv4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_bv4len(SL_bv4sub(lhs, rhs));
}
#else
;
#endif
/// @brief Component-wise binary AND of two bv
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header bool* SL_bvand_(bool* lhs, bool* rhs, bool* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] & rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary AND of two bv
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header bv SL_bvand(bv lhs, bv rhs, bv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_bvand_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary AND of two bv2
SL_header bv2 SL_bv2and(bv2 lhs, bv2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bv2) {
        .x = lhs.x & rhs.x,
        .y = lhs.y & rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise binary AND of two bv3
SL_header bv3 SL_bv3and(bv3 lhs, bv3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bv3) {
        .x = lhs.x & rhs.x,
        .y = lhs.y & rhs.y,
        .z = lhs.z & rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise binary AND of two bv4
SL_header bv4 SL_bv4and(bv4 lhs, bv4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bv4) {
        .x = lhs.x & rhs.x,
        .y = lhs.y & rhs.y,
        .z = lhs.z & rhs.z,
        .w = lhs.w & rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise binary OR of two bv
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header bool* SL_bvor_(bool* lhs, bool* rhs, bool* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] | rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary OR of two bv
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header bv SL_bvor(bv lhs, bv rhs, bv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_bvor_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary OR of two bv2
SL_header bv2 SL_bv2or(bv2 lhs, bv2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bv2) {
        .x = lhs.x | rhs.x,
        .y = lhs.y | rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise binary OR of two bv3
SL_header bv3 SL_bv3or(bv3 lhs, bv3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bv3) {
        .x = lhs.x | rhs.x,
        .y = lhs.y | rhs.y,
        .z = lhs.z | rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise binary OR of two bv4
SL_header bv4 SL_bv4or(bv4 lhs, bv4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bv4) {
        .x = lhs.x | rhs.x,
        .y = lhs.y | rhs.y,
        .z = lhs.z | rhs.z,
        .w = lhs.w | rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise binary XOR of two bv
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header bool* SL_bvxor_(bool* lhs, bool* rhs, bool* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] ^ rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary XOR of two bv
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header bv SL_bvxor(bv lhs, bv rhs, bv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_bvxor_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary XOR of two bv2
SL_header bv2 SL_bv2xor(bv2 lhs, bv2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bv2) {
        .x = lhs.x ^ rhs.x,
        .y = lhs.y ^ rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise binary XOR of two bv3
SL_header bv3 SL_bv3xor(bv3 lhs, bv3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bv3) {
        .x = lhs.x ^ rhs.x,
        .y = lhs.y ^ rhs.y,
        .z = lhs.z ^ rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise binary XOR of two bv4
SL_header bv4 SL_bv4xor(bv4 lhs, bv4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bv4) {
        .x = lhs.x ^ rhs.x,
        .y = lhs.y ^ rhs.y,
        .z = lhs.z ^ rhs.z,
        .w = lhs.w ^ rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise binary NOT of a bv
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header bool* SL_bvnot_(bool* v, bool* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = ~v[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary NOT of a bv
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header bv SL_bvnot(bv v, bv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_bvnot_(v.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary NOT of a bv2
SL_header bv2 SL_bv2not(bv2 v)
#if defined(SL_IMPLEMENTATION)
{
    return (bv2) {
        .x = ~v.x,
        .y = ~v.y
    };
}
#else
;
#endif
/// @brief Component-wise binary NOT of a bv3
SL_header bv3 SL_bv3not(bv3 v)
#if defined(SL_IMPLEMENTATION)
{
    return (bv3) {
        .x = ~v.x,
        .y = ~v.y,
        .z = ~v.z
    };
}
#else
;
#endif
/// @brief Component-wise binary NOT of a bv4
SL_header bv4 SL_bv4not(bv4 v)
#if defined(SL_IMPLEMENTATION)
{
    return (bv4) {
        .x = ~v.x,
        .y = ~v.y,
        .z = ~v.z,
        .w = ~v.w
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a bv by integer n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header bool* SL_bvlshfts_(bool* lhs, bool rhs, bool* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] << rhs;
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a bv by integer n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header bv SL_bvlshfts(bv lhs, bool rhs, bv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_bvlshfts_(lhs.data, rhs, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a bv2 by integer n
SL_header bv2 SL_bv2lshfts(bv2 lhs, bool rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bv2) {
        .x = lhs.x << rhs,
        .y = lhs.y << rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a bv3 by integer n
SL_header bv3 SL_bv3lshfts(bv3 lhs, bool rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bv3) {
        .x = lhs.x << rhs,
        .y = lhs.y << rhs,
        .z = lhs.z << rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a bv4 by integer n
SL_header bv4 SL_bv4lshfts(bv4 lhs, bool rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bv4) {
        .x = lhs.x << rhs,
        .y = lhs.y << rhs,
        .z = lhs.z << rhs,
        .w = lhs.w << rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a bv by bv n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header bool* SL_bvlshft_(bool* lhs, bool* rhs, bool* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] << rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a bv by bv n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header bv SL_bvlshft(bv lhs, bv rhs, bv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_bvlshft_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a bv2 by bv2 n
SL_header bv2 SL_bv2lshft(bv2 lhs, bv2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bv2) {
        .x = lhs.x << rhs.x,
        .y = lhs.y << rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a bv3 by bv3 n
SL_header bv3 SL_bv3lshft(bv3 lhs, bv3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bv3) {
        .x = lhs.x << rhs.x,
        .y = lhs.y << rhs.y,
        .z = lhs.z << rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise binary LEFT-SHIFT of a bv4 by bv4 n
SL_header bv4 SL_bv4lshft(bv4 lhs, bv4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bv4) {
        .x = lhs.x << rhs.x,
        .y = lhs.y << rhs.y,
        .z = lhs.z << rhs.z,
        .w = lhs.w << rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a bv by interger n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header bool* SL_bvrshfts_(bool* lhs, bool rhs, bool* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] >> rhs;
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a bv by interger n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header bv SL_bvrshfts(bv lhs, bool rhs, bv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_bvrshfts_(lhs.data, rhs, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a bv2 by interger n
SL_header bv2 SL_bv2rshfts(bv2 lhs, bool rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bv2) {
        .x = lhs.x >> rhs,
        .y = lhs.y >> rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a bv3 by interger n
SL_header bv3 SL_bv3rshfts(bv3 lhs, bool rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bv3) {
        .x = lhs.x >> rhs,
        .y = lhs.y >> rhs,
        .z = lhs.z >> rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a bv4 by interger n
SL_header bv4 SL_bv4rshfts(bv4 lhs, bool rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bv4) {
        .x = lhs.x >> rhs,
        .y = lhs.y >> rhs,
        .z = lhs.z >> rhs,
        .w = lhs.w >> rhs
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a bv by bv n
/// @note All vectors are assumed to be of size 'count'
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header bool* SL_bvrshft_(bool* lhs, bool* rhs, bool* dest, usize count)
#if defined(SL_IMPLEMENTATION)
{
    for (usize i = 0; i < count; ++i) dest[i] = lhs[i] >> rhs[i];
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a bv by bv n
/// @note Result is stored in 'dest' (which is returned to allow chaining function calls)
SL_header bv SL_bvrshft(bv lhs, bv rhs, bv dest)
#if defined(SL_IMPLEMENTATION)
{
    (void)SL_bvrshft_(lhs.data, rhs.data, dest.data, dest.count);
    return dest;
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a bv2 by bv2 n
SL_header bv2 SL_bv2rshft(bv2 lhs, bv2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bv2) {
        .x = lhs.x >> rhs.x,
        .y = lhs.y >> rhs.y
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a bv3 by bv3 n
SL_header bv3 SL_bv3rshft(bv3 lhs, bv3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bv3) {
        .x = lhs.x >> rhs.x,
        .y = lhs.y >> rhs.y,
        .z = lhs.z >> rhs.z
    };
}
#else
;
#endif
/// @brief Component-wise binary RIGHT-SHIFT of a bv4 by bv4 n
SL_header bv4 SL_bv4rshft(bv4 lhs, bv4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bv4) {
        .x = lhs.x >> rhs.x,
        .y = lhs.y >> rhs.y,
        .z = lhs.z >> rhs.z,
        .w = lhs.w >> rhs.w
    };
}
#else
;
#endif
#pragma endregion BOOL
#pragma region INT

typedef i32v iv;
typedef i32v2 iv2;
#define SL_iv2_zero  SL_i32v2_zero
#define SL_iv2_one   SL_i32v2_one
#define SL_iv2_right SL_i32v2_right
#define SL_iv2_up    SL_i32v2_up
#define SL_iv2_left  SL_i32v2_left
#define SL_iv2_down  SL_i32v2_down
typedef i32v3 iv3;
#define SL_iv3_zero  SL_i32v3_zero
#define SL_iv3_one   SL_i32v3_one
#define SL_iv3_right SL_i32v3_right
#define SL_iv3_up    SL_i32v3_up
#define SL_iv3_forw  SL_i32v3_forw
#define SL_iv3_left  SL_i32v3_left
#define SL_iv3_down  SL_i32v3_down
#define SL_iv3_back  SL_i32v3_back
typedef i32v4 iv4;
#define SL_iv4_zero  SL_i32v4_zero
#define SL_iv4_one   SL_i32v4_one


#define SL_iv2_(X, Y)       ((iv2){.x = X, .y = Y})
#define SL_iv3_(X, Y, Z)    ((iv3){.x = X, .y = Y, .z = Z})
#define SL_iv4_(X, Y, Z, W) ((iv4){.x = X, .y = Y, .z = Z, .w = W})

#define SL_iv2s(S)          ((iv2){.x = S, .y = S})
#define SL_iv3s(S)          ((iv3){.x = S, .y = S, .z = S})
#define SL_iv4s(S)          ((iv4){.x = S, .y = S, .z = S, .w = S})

#define SL_ivv(V)           ((iv){.count = vsize(V), .data = (V).data})
#define SL_iv2v(V, ...)     ((iv2){.x = (V).x, .y = (V).y})
#define SL_iv3v(V, ...)     ((iv3){.x = (V).x, .y = (V).y, .z = (SL_vsize(V) >= 3 ? (V).data[2] : (0, ##__VA_ARGS__))})
#define SL_iv4v(V, ...)     ((iv4){.x = (V).x, .y = (V).y, .z = (SL_vsize(V) >= 3 ? (V).data[2] : ((const float[]){0, ##__VA_ARGS__, 0})[1]), .w = (SL_vsize(V) >= 4 ? (V).data[3] : ((const float[]){0, ##__VA_ARGS__, 0, 0})[2])})



#define SL_ivequ_ SL_i32vequ_
#define SL_ivequ SL_i32vequ
#define SL_iv2equ SL_i32v2equ
#define SL_iv3equ SL_i32v3equ
#define SL_iv4equ SL_i32v4equ
#define SL_ivadd_ SL_i32vadd_
#define SL_ivadd SL_i32vadd
#define SL_iv2add SL_i32v2add
#define SL_iv3add SL_i32v3add
#define SL_iv4add SL_i32v4add
#define SL_ivsub_ SL_i32vsub_
#define SL_ivsub SL_i32vsub
#define SL_iv2sub SL_i32v2sub
#define SL_iv3sub SL_i32v3sub
#define SL_iv4sub SL_i32v4sub
#define SL_ivmul_ SL_i32vmul_
#define SL_ivmul SL_i32vmul
#define SL_iv2mul SL_i32v2mul
#define SL_iv3mul SL_i32v3mul
#define SL_iv4mul SL_i32v4mul
#define SL_ivmuls_ SL_i32vmuls_
#define SL_ivmuls SL_i32vmuls
#define SL_iv2muls SL_i32v2muls
#define SL_iv3muls SL_i32v3muls
#define SL_iv4muls SL_i32v4muls
#define SL_ivdiv_ SL_i32vdiv_
#define SL_ivdiv SL_i32vdiv
#define SL_iv2div SL_i32v2div
#define SL_iv3div SL_i32v3div
#define SL_iv4div SL_i32v4div
#define SL_ivdivs_ SL_i32vdivs_
#define SL_ivdivs SL_i32vdivs
#define SL_iv2divs SL_i32v2divs
#define SL_iv3divs SL_i32v3divs
#define SL_iv4divs SL_i32v4divs
#define SL_ivaddS_ SL_i32vaddS_
#define SL_ivaddS SL_i32vaddS
#define SL_iv2addS SL_i32v2addS
#define SL_iv3addS SL_i32v3addS
#define SL_iv4addS SL_i32v4addS
#define SL_ivsubS_ SL_i32vsubS_
#define SL_ivsubS SL_i32vsubS
#define SL_iv2subS SL_i32v2subS
#define SL_iv3subS SL_i32v3subS
#define SL_iv4subS SL_i32v4subS
#define SL_ivaddM_ SL_i32vaddM_
#define SL_ivaddM SL_i32vaddM
#define SL_iv2addM SL_i32v2addM
#define SL_iv3addM SL_i32v3addM
#define SL_iv4addM SL_i32v4addM
#define SL_ivsubM_ SL_i32vsubM_
#define SL_ivsubM SL_i32vsubM
#define SL_iv2subM SL_i32v2subM
#define SL_iv3subM SL_i32v3subM
#define SL_iv4subM SL_i32v4subM
#define SL_ivaddSM_ SL_i32vaddSM_
#define SL_ivaddSM SL_i32vaddSM
#define SL_iv2addSM SL_i32v2addSM
#define SL_iv3addSM SL_i32v3addSM
#define SL_iv4addSM SL_i32v4addSM
#define SL_ivsubSM_ SL_i32vsubSM_
#define SL_ivsubSM SL_i32vsubSM
#define SL_iv2subSM SL_i32v2subSM
#define SL_iv3subSM SL_i32v3subSM
#define SL_iv4subSM SL_i32v4subSM
#define SL_ivSadd_ SL_i32vSadd_
#define SL_ivSadd SL_i32vSadd
#define SL_iv2Sadd SL_i32v2Sadd
#define SL_iv3Sadd SL_i32v3Sadd
#define SL_iv4Sadd SL_i32v4Sadd
#define SL_ivSsub_ SL_i32vSsub_
#define SL_ivSsub SL_i32vSsub
#define SL_iv2Ssub SL_i32v2Ssub
#define SL_iv3Ssub SL_i32v3Ssub
#define SL_iv4Ssub SL_i32v4Ssub
#define SL_ivmix_ SL_i32vmix_
#define SL_ivmix SL_i32vmix
#define SL_iv2mix SL_i32v2mix
#define SL_iv3mix SL_i32v3mix
#define SL_iv4mix SL_i32v4mix
#define SL_ivneg_ SL_i32vneg_
#define SL_ivneg SL_i32vneg
#define SL_iv2neg SL_i32v2neg
#define SL_iv3neg SL_i32v3neg
#define SL_iv4neg SL_i32v4neg
#define SL_ivabs_ SL_i32vabs_
#define SL_ivabs SL_i32vabs
#define SL_iv2abs SL_i32v2abs
#define SL_iv3abs SL_i32v3abs
#define SL_iv4abs SL_i32v4abs
#define SL_ivmin_ SL_i32vmin_
#define SL_ivmin SL_i32vmin
#define SL_iv2min SL_i32v2min
#define SL_iv3min SL_i32v3min
#define SL_iv4min SL_i32v4min
#define SL_ivmax_ SL_i32vmax_
#define SL_ivmax SL_i32vmax
#define SL_iv2max SL_i32v2max
#define SL_iv3max SL_i32v3max
#define SL_iv4max SL_i32v4max
#define SL_ivdot_ SL_i32vdot_
#define SL_ivdot SL_i32vdot
#define SL_iv2dot SL_i32v2dot
#define SL_iv3dot SL_i32v3dot
#define SL_iv4dot SL_i32v4dot
#define SL_ivlen_max_ SL_i32vlen_max_
#define SL_ivlen_max SL_i32vlen_max
#define SL_iv2len_max SL_i32v2len_max
#define SL_iv3len_max SL_i32v3len_max
#define SL_iv4len_max SL_i32v4len_max
#define SL_ivlen_manh_ SL_i32vlen_manh_
#define SL_ivlen_manh SL_i32vlen_manh
#define SL_iv2len_manh SL_i32v2len_manh
#define SL_iv3len_manh SL_i32v3len_manh
#define SL_iv4len_manh SL_i32v4len_manh
#define SL_ivlen_srq_ SL_i32vlen_srq_
#define SL_ivlen_srq SL_i32vlen_srq
#define SL_iv2len_sqr SL_i32v2len_sqr
#define SL_iv3len_sqr SL_i32v3len_sqr
#define SL_iv4len_sqr SL_i32v4len_sqr
#define SL_ivlen_ SL_i32vlen_
#define SL_ivlen SL_i32vlen
#define SL_iv2len SL_i32v2len
#define SL_iv3len SL_i32v3len
#define SL_iv4len SL_i32v4len
#define SL_ivdist_ SL_i32vdist_
#define SL_ivdist SL_i32vdist
#define SL_iv2dist SL_i32v2dist
#define SL_iv3dist SL_i32v3dist
#define SL_iv4dist SL_i32v4dist
#define SL_iv2refl SL_i32v2refl
#define SL_iv3refl SL_i32v3refl
#define SL_iv4refl SL_i32v4refl
#define SL_iv2refl_u SL_i32v2refl_u
#define SL_iv3refl_u SL_i32v3refl_u
#define SL_iv4refl_u SL_i32v4refl_u
#define SL_iv2align SL_i32v2align
#define SL_iv3align SL_i32v3align
#define SL_iv4align SL_i32v4align
#define SL_iv2align_u SL_i32v2align_u
#define SL_iv3align_u SL_i32v3align_u
#define SL_iv4align_u SL_i32v4align_u
#define SL_iv2proj SL_i32v2proj
#define SL_iv3proj SL_i32v3proj
#define SL_iv4proj SL_i32v4proj
#define SL_iv2proj_u SL_i32v2proj_u
#define SL_iv3proj_u SL_i32v3proj_u
#define SL_iv4proj_u SL_i32v4proj_u
#define SL_ivmods_ SL_i32vmods_
#define SL_ivmods SL_i32vmods
#define SL_iv2mods SL_i32v2mods
#define SL_iv3mods SL_i32v3mods
#define SL_iv4mods SL_i32v4mods
#define SL_ivmod_ SL_i32vmod_
#define SL_ivmod SL_i32vmod
#define SL_iv2mod SL_i32v2mod
#define SL_iv3mod SL_i32v3mod
#define SL_iv4mod SL_i32v4mod
#define SL_iv2cross SL_i32v2cross
#define SL_iv3cross SL_i32v3cross
#define SL_ivand_ SL_i32vand_
#define SL_ivand SL_i32vand
#define SL_iv2and SL_i32v2and
#define SL_iv3and SL_i32v3and
#define SL_iv4and SL_i32v4and
#define SL_ivor_ SL_i32vor_
#define SL_ivor SL_i32vor
#define SL_iv2or SL_i32v2or
#define SL_iv3or SL_i32v3or
#define SL_iv4or SL_i32v4or
#define SL_ivxor_ SL_i32vxor_
#define SL_ivxor SL_i32vxor
#define SL_iv2xor SL_i32v2xor
#define SL_iv3xor SL_i32v3xor
#define SL_iv4xor SL_i32v4xor
#define SL_ivnot_ SL_i32vnot_
#define SL_ivnot SL_i32vnot
#define SL_iv2not SL_i32v2not
#define SL_iv3not SL_i32v3not
#define SL_iv4not SL_i32v4not
#define SL_ivlshfts_ SL_i32vlshfts_
#define SL_ivlshfts SL_i32vlshfts
#define SL_iv2lshfts SL_i32v2lshfts
#define SL_iv3lshfts SL_i32v3lshfts
#define SL_iv4lshfts SL_i32v4lshfts
#define SL_ivlshft_ SL_i32vlshft_
#define SL_ivlshft SL_i32vlshft
#define SL_iv2lshft SL_i32v2lshft
#define SL_iv3lshft SL_i32v3lshft
#define SL_iv4lshft SL_i32v4lshft
#define SL_ivrshfts_ SL_i32vrshfts_
#define SL_ivrshfts SL_i32vrshfts
#define SL_iv2rshfts SL_i32v2rshfts
#define SL_iv3rshfts SL_i32v3rshfts
#define SL_iv4rshfts SL_i32v4rshfts
#define SL_ivrshft_ SL_i32vrshft_
#define SL_ivrshft SL_i32vrshft
#define SL_iv2rshft SL_i32v2rshft
#define SL_iv3rshft SL_i32v3rshft
#define SL_iv4rshft SL_i32v4rshft
#pragma endregion INT
#pragma region UINT

typedef u32v uv;
typedef u32v2 uv2;
#define SL_uv2_zero  SL_u32v2_zero
#define SL_uv2_one   SL_u32v2_one
#define SL_uv2_right SL_u32v2_right
#define SL_uv2_up    SL_u32v2_up
typedef u32v3 uv3;
#define SL_uv3_zero  SL_u32v3_zero
#define SL_uv3_one   SL_u32v3_one
#define SL_uv3_right SL_u32v3_right
#define SL_uv3_up    SL_u32v3_up
#define SL_uv3_forw  SL_u32v3_forw
typedef u32v4 uv4;
#define SL_uv4_zero  SL_u32v4_zero
#define SL_uv4_one   SL_u32v4_one


#define SL_uv2_(X, Y)       ((uv2){.x = X, .y = Y})
#define SL_uv3_(X, Y, Z)    ((uv3){.x = X, .y = Y, .z = Z})
#define SL_uv4_(X, Y, Z, W) ((uv4){.x = X, .y = Y, .z = Z, .w = W})

#define SL_uv2s(S)          ((uv2){.x = S, .y = S})
#define SL_uv3s(S)          ((uv3){.x = S, .y = S, .z = S})
#define SL_uv4s(S)          ((uv4){.x = S, .y = S, .z = S, .w = S})

#define SL_uvv(V)           ((uv){.count = vsize(V), .data = (V).data})
#define SL_uv2v(V, ...)     ((uv2){.x = (V).x, .y = (V).y})
#define SL_uv3v(V, ...)     ((uv3){.x = (V).x, .y = (V).y, .z = (SL_vsize(V) >= 3 ? (V).data[2] : (0, ##__VA_ARGS__))})
#define SL_uv4v(V, ...)     ((uv4){.x = (V).x, .y = (V).y, .z = (SL_vsize(V) >= 3 ? (V).data[2] : ((const float[]){0, ##__VA_ARGS__, 0})[1]), .w = (SL_vsize(V) >= 4 ? (V).data[3] : ((const float[]){0, ##__VA_ARGS__, 0, 0})[2])})



#define SL_uvequ_ SL_u32vequ_
#define SL_uvequ SL_u32vequ
#define SL_uv2equ SL_u32v2equ
#define SL_uv3equ SL_u32v3equ
#define SL_uv4equ SL_u32v4equ
#define SL_uvadd_ SL_u32vadd_
#define SL_uvadd SL_u32vadd
#define SL_uv2add SL_u32v2add
#define SL_uv3add SL_u32v3add
#define SL_uv4add SL_u32v4add
#define SL_uvsub_ SL_u32vsub_
#define SL_uvsub SL_u32vsub
#define SL_uv2sub SL_u32v2sub
#define SL_uv3sub SL_u32v3sub
#define SL_uv4sub SL_u32v4sub
#define SL_uvmul_ SL_u32vmul_
#define SL_uvmul SL_u32vmul
#define SL_uv2mul SL_u32v2mul
#define SL_uv3mul SL_u32v3mul
#define SL_uv4mul SL_u32v4mul
#define SL_uvmuls_ SL_u32vmuls_
#define SL_uvmuls SL_u32vmuls
#define SL_uv2muls SL_u32v2muls
#define SL_uv3muls SL_u32v3muls
#define SL_uv4muls SL_u32v4muls
#define SL_uvdiv_ SL_u32vdiv_
#define SL_uvdiv SL_u32vdiv
#define SL_uv2div SL_u32v2div
#define SL_uv3div SL_u32v3div
#define SL_uv4div SL_u32v4div
#define SL_uvdivs_ SL_u32vdivs_
#define SL_uvdivs SL_u32vdivs
#define SL_uv2divs SL_u32v2divs
#define SL_uv3divs SL_u32v3divs
#define SL_uv4divs SL_u32v4divs
#define SL_uvaddS_ SL_u32vaddS_
#define SL_uvaddS SL_u32vaddS
#define SL_uv2addS SL_u32v2addS
#define SL_uv3addS SL_u32v3addS
#define SL_uv4addS SL_u32v4addS
#define SL_uvsubS_ SL_u32vsubS_
#define SL_uvsubS SL_u32vsubS
#define SL_uv2subS SL_u32v2subS
#define SL_uv3subS SL_u32v3subS
#define SL_uv4subS SL_u32v4subS
#define SL_uvaddM_ SL_u32vaddM_
#define SL_uvaddM SL_u32vaddM
#define SL_uv2addM SL_u32v2addM
#define SL_uv3addM SL_u32v3addM
#define SL_uv4addM SL_u32v4addM
#define SL_uvsubM_ SL_u32vsubM_
#define SL_uvsubM SL_u32vsubM
#define SL_uv2subM SL_u32v2subM
#define SL_uv3subM SL_u32v3subM
#define SL_uv4subM SL_u32v4subM
#define SL_uvaddSM_ SL_u32vaddSM_
#define SL_uvaddSM SL_u32vaddSM
#define SL_uv2addSM SL_u32v2addSM
#define SL_uv3addSM SL_u32v3addSM
#define SL_uv4addSM SL_u32v4addSM
#define SL_uvsubSM_ SL_u32vsubSM_
#define SL_uvsubSM SL_u32vsubSM
#define SL_uv2subSM SL_u32v2subSM
#define SL_uv3subSM SL_u32v3subSM
#define SL_uv4subSM SL_u32v4subSM
#define SL_uvSadd_ SL_u32vSadd_
#define SL_uvSadd SL_u32vSadd
#define SL_uv2Sadd SL_u32v2Sadd
#define SL_uv3Sadd SL_u32v3Sadd
#define SL_uv4Sadd SL_u32v4Sadd
#define SL_uvSsub_ SL_u32vSsub_
#define SL_uvSsub SL_u32vSsub
#define SL_uv2Ssub SL_u32v2Ssub
#define SL_uv3Ssub SL_u32v3Ssub
#define SL_uv4Ssub SL_u32v4Ssub
#define SL_uvmix_ SL_u32vmix_
#define SL_uvmix SL_u32vmix
#define SL_uv2mix SL_u32v2mix
#define SL_uv3mix SL_u32v3mix
#define SL_uv4mix SL_u32v4mix
#define SL_uvmin_ SL_u32vmin_
#define SL_uvmin SL_u32vmin
#define SL_uv2min SL_u32v2min
#define SL_uv3min SL_u32v3min
#define SL_uv4min SL_u32v4min
#define SL_uvmax_ SL_u32vmax_
#define SL_uvmax SL_u32vmax
#define SL_uv2max SL_u32v2max
#define SL_uv3max SL_u32v3max
#define SL_uv4max SL_u32v4max
#define SL_uvdot_ SL_u32vdot_
#define SL_uvdot SL_u32vdot
#define SL_uv2dot SL_u32v2dot
#define SL_uv3dot SL_u32v3dot
#define SL_uv4dot SL_u32v4dot
#define SL_uvlen_max_ SL_u32vlen_max_
#define SL_uvlen_max SL_u32vlen_max
#define SL_uv2len_max SL_u32v2len_max
#define SL_uv3len_max SL_u32v3len_max
#define SL_uv4len_max SL_u32v4len_max
#define SL_uvlen_manh_ SL_u32vlen_manh_
#define SL_uvlen_manh SL_u32vlen_manh
#define SL_uv2len_manh SL_u32v2len_manh
#define SL_uv3len_manh SL_u32v3len_manh
#define SL_uv4len_manh SL_u32v4len_manh
#define SL_uvlen_srq_ SL_u32vlen_srq_
#define SL_uvlen_srq SL_u32vlen_srq
#define SL_uv2len_sqr SL_u32v2len_sqr
#define SL_uv3len_sqr SL_u32v3len_sqr
#define SL_uv4len_sqr SL_u32v4len_sqr
#define SL_uvlen_ SL_u32vlen_
#define SL_uvlen SL_u32vlen
#define SL_uv2len SL_u32v2len
#define SL_uv3len SL_u32v3len
#define SL_uv4len SL_u32v4len
#define SL_uvdist_ SL_u32vdist_
#define SL_uvdist SL_u32vdist
#define SL_uv2dist SL_u32v2dist
#define SL_uv3dist SL_u32v3dist
#define SL_uv4dist SL_u32v4dist
#define SL_uv2refl SL_u32v2refl
#define SL_uv3refl SL_u32v3refl
#define SL_uv4refl SL_u32v4refl
#define SL_uv2refl_u SL_u32v2refl_u
#define SL_uv3refl_u SL_u32v3refl_u
#define SL_uv4refl_u SL_u32v4refl_u
#define SL_uv2align SL_u32v2align
#define SL_uv3align SL_u32v3align
#define SL_uv4align SL_u32v4align
#define SL_uv2align_u SL_u32v2align_u
#define SL_uv3align_u SL_u32v3align_u
#define SL_uv4align_u SL_u32v4align_u
#define SL_uv2proj SL_u32v2proj
#define SL_uv3proj SL_u32v3proj
#define SL_uv4proj SL_u32v4proj
#define SL_uv2proj_u SL_u32v2proj_u
#define SL_uv3proj_u SL_u32v3proj_u
#define SL_uv4proj_u SL_u32v4proj_u
#define SL_uvmods_ SL_u32vmods_
#define SL_uvmods SL_u32vmods
#define SL_uv2mods SL_u32v2mods
#define SL_uv3mods SL_u32v3mods
#define SL_uv4mods SL_u32v4mods
#define SL_uvmod_ SL_u32vmod_
#define SL_uvmod SL_u32vmod
#define SL_uv2mod SL_u32v2mod
#define SL_uv3mod SL_u32v3mod
#define SL_uv4mod SL_u32v4mod
#define SL_uvand_ SL_u32vand_
#define SL_uvand SL_u32vand
#define SL_uv2and SL_u32v2and
#define SL_uv3and SL_u32v3and
#define SL_uv4and SL_u32v4and
#define SL_uvor_ SL_u32vor_
#define SL_uvor SL_u32vor
#define SL_uv2or SL_u32v2or
#define SL_uv3or SL_u32v3or
#define SL_uv4or SL_u32v4or
#define SL_uvxor_ SL_u32vxor_
#define SL_uvxor SL_u32vxor
#define SL_uv2xor SL_u32v2xor
#define SL_uv3xor SL_u32v3xor
#define SL_uv4xor SL_u32v4xor
#define SL_uvnot_ SL_u32vnot_
#define SL_uvnot SL_u32vnot
#define SL_uv2not SL_u32v2not
#define SL_uv3not SL_u32v3not
#define SL_uv4not SL_u32v4not
#define SL_uvlshfts_ SL_u32vlshfts_
#define SL_uvlshfts SL_u32vlshfts
#define SL_uv2lshfts SL_u32v2lshfts
#define SL_uv3lshfts SL_u32v3lshfts
#define SL_uv4lshfts SL_u32v4lshfts
#define SL_uvlshft_ SL_u32vlshft_
#define SL_uvlshft SL_u32vlshft
#define SL_uv2lshft SL_u32v2lshft
#define SL_uv3lshft SL_u32v3lshft
#define SL_uv4lshft SL_u32v4lshft
#define SL_uvrshfts_ SL_u32vrshfts_
#define SL_uvrshfts SL_u32vrshfts
#define SL_uv2rshfts SL_u32v2rshfts
#define SL_uv3rshfts SL_u32v3rshfts
#define SL_uv4rshfts SL_u32v4rshfts
#define SL_uvrshft_ SL_u32vrshft_
#define SL_uvrshft SL_u32vrshft
#define SL_uv2rshft SL_u32v2rshft
#define SL_uv3rshft SL_u32v3rshft
#define SL_uv4rshft SL_u32v4rshft
#pragma endregion UINT
#pragma region I64

typedef i64v liv;
typedef i64v2 liv2;
#define SL_liv2_zero  SL_i64v2_zero
#define SL_liv2_one   SL_i64v2_one
#define SL_liv2_right SL_i64v2_right
#define SL_liv2_up    SL_i64v2_up
#define SL_liv2_left  SL_i64v2_left
#define SL_liv2_down  SL_i64v2_down
typedef i64v3 liv3;
#define SL_liv3_zero  SL_i64v3_zero
#define SL_liv3_one   SL_i64v3_one
#define SL_liv3_right SL_i64v3_right
#define SL_liv3_up    SL_i64v3_up
#define SL_liv3_forw  SL_i64v3_forw
#define SL_liv3_left  SL_i64v3_left
#define SL_liv3_down  SL_i64v3_down
#define SL_liv3_back  SL_i64v3_back
typedef i64v4 liv4;
#define SL_liv4_zero  SL_i64v4_zero
#define SL_liv4_one   SL_i64v4_one


#define SL_liv2_(X, Y)       ((liv2){.x = X, .y = Y})
#define SL_liv3_(X, Y, Z)    ((liv3){.x = X, .y = Y, .z = Z})
#define SL_liv4_(X, Y, Z, W) ((liv4){.x = X, .y = Y, .z = Z, .w = W})

#define SL_liv2s(S)          ((liv2){.x = S, .y = S})
#define SL_liv3s(S)          ((liv3){.x = S, .y = S, .z = S})
#define SL_liv4s(S)          ((liv4){.x = S, .y = S, .z = S, .w = S})

#define SL_livv(V)           ((liv){.count = vsize(V), .data = (V).data})
#define SL_liv2v(V, ...)     ((liv2){.x = (V).x, .y = (V).y})
#define SL_liv3v(V, ...)     ((liv3){.x = (V).x, .y = (V).y, .z = (SL_vsize(V) >= 3 ? (V).data[2] : (0, ##__VA_ARGS__))})
#define SL_liv4v(V, ...)     ((liv4){.x = (V).x, .y = (V).y, .z = (SL_vsize(V) >= 3 ? (V).data[2] : ((const float[]){0, ##__VA_ARGS__, 0})[1]), .w = (SL_vsize(V) >= 4 ? (V).data[3] : ((const float[]){0, ##__VA_ARGS__, 0, 0})[2])})



#define SL_livequ_ SL_i64vequ_
#define SL_livequ SL_i64vequ
#define SL_liv2equ SL_i64v2equ
#define SL_liv3equ SL_i64v3equ
#define SL_liv4equ SL_i64v4equ
#define SL_livadd_ SL_i64vadd_
#define SL_livadd SL_i64vadd
#define SL_liv2add SL_i64v2add
#define SL_liv3add SL_i64v3add
#define SL_liv4add SL_i64v4add
#define SL_livsub_ SL_i64vsub_
#define SL_livsub SL_i64vsub
#define SL_liv2sub SL_i64v2sub
#define SL_liv3sub SL_i64v3sub
#define SL_liv4sub SL_i64v4sub
#define SL_livmul_ SL_i64vmul_
#define SL_livmul SL_i64vmul
#define SL_liv2mul SL_i64v2mul
#define SL_liv3mul SL_i64v3mul
#define SL_liv4mul SL_i64v4mul
#define SL_livmuls_ SL_i64vmuls_
#define SL_livmuls SL_i64vmuls
#define SL_liv2muls SL_i64v2muls
#define SL_liv3muls SL_i64v3muls
#define SL_liv4muls SL_i64v4muls
#define SL_livdiv_ SL_i64vdiv_
#define SL_livdiv SL_i64vdiv
#define SL_liv2div SL_i64v2div
#define SL_liv3div SL_i64v3div
#define SL_liv4div SL_i64v4div
#define SL_livdivs_ SL_i64vdivs_
#define SL_livdivs SL_i64vdivs
#define SL_liv2divs SL_i64v2divs
#define SL_liv3divs SL_i64v3divs
#define SL_liv4divs SL_i64v4divs
#define SL_livaddS_ SL_i64vaddS_
#define SL_livaddS SL_i64vaddS
#define SL_liv2addS SL_i64v2addS
#define SL_liv3addS SL_i64v3addS
#define SL_liv4addS SL_i64v4addS
#define SL_livsubS_ SL_i64vsubS_
#define SL_livsubS SL_i64vsubS
#define SL_liv2subS SL_i64v2subS
#define SL_liv3subS SL_i64v3subS
#define SL_liv4subS SL_i64v4subS
#define SL_livaddM_ SL_i64vaddM_
#define SL_livaddM SL_i64vaddM
#define SL_liv2addM SL_i64v2addM
#define SL_liv3addM SL_i64v3addM
#define SL_liv4addM SL_i64v4addM
#define SL_livsubM_ SL_i64vsubM_
#define SL_livsubM SL_i64vsubM
#define SL_liv2subM SL_i64v2subM
#define SL_liv3subM SL_i64v3subM
#define SL_liv4subM SL_i64v4subM
#define SL_livaddSM_ SL_i64vaddSM_
#define SL_livaddSM SL_i64vaddSM
#define SL_liv2addSM SL_i64v2addSM
#define SL_liv3addSM SL_i64v3addSM
#define SL_liv4addSM SL_i64v4addSM
#define SL_livsubSM_ SL_i64vsubSM_
#define SL_livsubSM SL_i64vsubSM
#define SL_liv2subSM SL_i64v2subSM
#define SL_liv3subSM SL_i64v3subSM
#define SL_liv4subSM SL_i64v4subSM
#define SL_livSadd_ SL_i64vSadd_
#define SL_livSadd SL_i64vSadd
#define SL_liv2Sadd SL_i64v2Sadd
#define SL_liv3Sadd SL_i64v3Sadd
#define SL_liv4Sadd SL_i64v4Sadd
#define SL_livSsub_ SL_i64vSsub_
#define SL_livSsub SL_i64vSsub
#define SL_liv2Ssub SL_i64v2Ssub
#define SL_liv3Ssub SL_i64v3Ssub
#define SL_liv4Ssub SL_i64v4Ssub
#define SL_livmix_ SL_i64vmix_
#define SL_livmix SL_i64vmix
#define SL_liv2mix SL_i64v2mix
#define SL_liv3mix SL_i64v3mix
#define SL_liv4mix SL_i64v4mix
#define SL_livneg_ SL_i64vneg_
#define SL_livneg SL_i64vneg
#define SL_liv2neg SL_i64v2neg
#define SL_liv3neg SL_i64v3neg
#define SL_liv4neg SL_i64v4neg
#define SL_livabs_ SL_i64vabs_
#define SL_livabs SL_i64vabs
#define SL_liv2abs SL_i64v2abs
#define SL_liv3abs SL_i64v3abs
#define SL_liv4abs SL_i64v4abs
#define SL_livmin_ SL_i64vmin_
#define SL_livmin SL_i64vmin
#define SL_liv2min SL_i64v2min
#define SL_liv3min SL_i64v3min
#define SL_liv4min SL_i64v4min
#define SL_livmax_ SL_i64vmax_
#define SL_livmax SL_i64vmax
#define SL_liv2max SL_i64v2max
#define SL_liv3max SL_i64v3max
#define SL_liv4max SL_i64v4max
#define SL_livdot_ SL_i64vdot_
#define SL_livdot SL_i64vdot
#define SL_liv2dot SL_i64v2dot
#define SL_liv3dot SL_i64v3dot
#define SL_liv4dot SL_i64v4dot
#define SL_livlen_max_ SL_i64vlen_max_
#define SL_livlen_max SL_i64vlen_max
#define SL_liv2len_max SL_i64v2len_max
#define SL_liv3len_max SL_i64v3len_max
#define SL_liv4len_max SL_i64v4len_max
#define SL_livlen_manh_ SL_i64vlen_manh_
#define SL_livlen_manh SL_i64vlen_manh
#define SL_liv2len_manh SL_i64v2len_manh
#define SL_liv3len_manh SL_i64v3len_manh
#define SL_liv4len_manh SL_i64v4len_manh
#define SL_livlen_srq_ SL_i64vlen_srq_
#define SL_livlen_srq SL_i64vlen_srq
#define SL_liv2len_sqr SL_i64v2len_sqr
#define SL_liv3len_sqr SL_i64v3len_sqr
#define SL_liv4len_sqr SL_i64v4len_sqr
#define SL_livlen_ SL_i64vlen_
#define SL_livlen SL_i64vlen
#define SL_liv2len SL_i64v2len
#define SL_liv3len SL_i64v3len
#define SL_liv4len SL_i64v4len
#define SL_livdist_ SL_i64vdist_
#define SL_livdist SL_i64vdist
#define SL_liv2dist SL_i64v2dist
#define SL_liv3dist SL_i64v3dist
#define SL_liv4dist SL_i64v4dist
#define SL_liv2refl SL_i64v2refl
#define SL_liv3refl SL_i64v3refl
#define SL_liv4refl SL_i64v4refl
#define SL_liv2refl_u SL_i64v2refl_u
#define SL_liv3refl_u SL_i64v3refl_u
#define SL_liv4refl_u SL_i64v4refl_u
#define SL_liv2align SL_i64v2align
#define SL_liv3align SL_i64v3align
#define SL_liv4align SL_i64v4align
#define SL_liv2align_u SL_i64v2align_u
#define SL_liv3align_u SL_i64v3align_u
#define SL_liv4align_u SL_i64v4align_u
#define SL_liv2proj SL_i64v2proj
#define SL_liv3proj SL_i64v3proj
#define SL_liv4proj SL_i64v4proj
#define SL_liv2proj_u SL_i64v2proj_u
#define SL_liv3proj_u SL_i64v3proj_u
#define SL_liv4proj_u SL_i64v4proj_u
#define SL_livmods_ SL_i64vmods_
#define SL_livmods SL_i64vmods
#define SL_liv2mods SL_i64v2mods
#define SL_liv3mods SL_i64v3mods
#define SL_liv4mods SL_i64v4mods
#define SL_livmod_ SL_i64vmod_
#define SL_livmod SL_i64vmod
#define SL_liv2mod SL_i64v2mod
#define SL_liv3mod SL_i64v3mod
#define SL_liv4mod SL_i64v4mod
#define SL_liv2cross SL_i64v2cross
#define SL_liv3cross SL_i64v3cross
#define SL_livand_ SL_i64vand_
#define SL_livand SL_i64vand
#define SL_liv2and SL_i64v2and
#define SL_liv3and SL_i64v3and
#define SL_liv4and SL_i64v4and
#define SL_livor_ SL_i64vor_
#define SL_livor SL_i64vor
#define SL_liv2or SL_i64v2or
#define SL_liv3or SL_i64v3or
#define SL_liv4or SL_i64v4or
#define SL_livxor_ SL_i64vxor_
#define SL_livxor SL_i64vxor
#define SL_liv2xor SL_i64v2xor
#define SL_liv3xor SL_i64v3xor
#define SL_liv4xor SL_i64v4xor
#define SL_livnot_ SL_i64vnot_
#define SL_livnot SL_i64vnot
#define SL_liv2not SL_i64v2not
#define SL_liv3not SL_i64v3not
#define SL_liv4not SL_i64v4not
#define SL_livlshfts_ SL_i64vlshfts_
#define SL_livlshfts SL_i64vlshfts
#define SL_liv2lshfts SL_i64v2lshfts
#define SL_liv3lshfts SL_i64v3lshfts
#define SL_liv4lshfts SL_i64v4lshfts
#define SL_livlshft_ SL_i64vlshft_
#define SL_livlshft SL_i64vlshft
#define SL_liv2lshft SL_i64v2lshft
#define SL_liv3lshft SL_i64v3lshft
#define SL_liv4lshft SL_i64v4lshft
#define SL_livrshfts_ SL_i64vrshfts_
#define SL_livrshfts SL_i64vrshfts
#define SL_liv2rshfts SL_i64v2rshfts
#define SL_liv3rshfts SL_i64v3rshfts
#define SL_liv4rshfts SL_i64v4rshfts
#define SL_livrshft_ SL_i64vrshft_
#define SL_livrshft SL_i64vrshft
#define SL_liv2rshft SL_i64v2rshft
#define SL_liv3rshft SL_i64v3rshft
#define SL_liv4rshft SL_i64v4rshft
#pragma endregion I64
#pragma region U64

typedef u64v luv;
typedef u64v2 luv2;
#define SL_luv2_zero  SL_u64v2_zero
#define SL_luv2_one   SL_u64v2_one
#define SL_luv2_right SL_u64v2_right
#define SL_luv2_up    SL_u64v2_up
typedef u64v3 luv3;
#define SL_luv3_zero  SL_u64v3_zero
#define SL_luv3_one   SL_u64v3_one
#define SL_luv3_right SL_u64v3_right
#define SL_luv3_up    SL_u64v3_up
#define SL_luv3_forw  SL_u64v3_forw
typedef u64v4 luv4;
#define SL_luv4_zero  SL_u64v4_zero
#define SL_luv4_one   SL_u64v4_one


#define SL_luv2_(X, Y)       ((luv2){.x = X, .y = Y})
#define SL_luv3_(X, Y, Z)    ((luv3){.x = X, .y = Y, .z = Z})
#define SL_luv4_(X, Y, Z, W) ((luv4){.x = X, .y = Y, .z = Z, .w = W})

#define SL_luv2s(S)          ((luv2){.x = S, .y = S})
#define SL_luv3s(S)          ((luv3){.x = S, .y = S, .z = S})
#define SL_luv4s(S)          ((luv4){.x = S, .y = S, .z = S, .w = S})

#define SL_luvv(V)           ((luv){.count = vsize(V), .data = (V).data})
#define SL_luv2v(V, ...)     ((luv2){.x = (V).x, .y = (V).y})
#define SL_luv3v(V, ...)     ((luv3){.x = (V).x, .y = (V).y, .z = (SL_vsize(V) >= 3 ? (V).data[2] : (0, ##__VA_ARGS__))})
#define SL_luv4v(V, ...)     ((luv4){.x = (V).x, .y = (V).y, .z = (SL_vsize(V) >= 3 ? (V).data[2] : ((const float[]){0, ##__VA_ARGS__, 0})[1]), .w = (SL_vsize(V) >= 4 ? (V).data[3] : ((const float[]){0, ##__VA_ARGS__, 0, 0})[2])})



#define SL_luvequ_ SL_u64vequ_
#define SL_luvequ SL_u64vequ
#define SL_luv2equ SL_u64v2equ
#define SL_luv3equ SL_u64v3equ
#define SL_luv4equ SL_u64v4equ
#define SL_luvadd_ SL_u64vadd_
#define SL_luvadd SL_u64vadd
#define SL_luv2add SL_u64v2add
#define SL_luv3add SL_u64v3add
#define SL_luv4add SL_u64v4add
#define SL_luvsub_ SL_u64vsub_
#define SL_luvsub SL_u64vsub
#define SL_luv2sub SL_u64v2sub
#define SL_luv3sub SL_u64v3sub
#define SL_luv4sub SL_u64v4sub
#define SL_luvmul_ SL_u64vmul_
#define SL_luvmul SL_u64vmul
#define SL_luv2mul SL_u64v2mul
#define SL_luv3mul SL_u64v3mul
#define SL_luv4mul SL_u64v4mul
#define SL_luvmuls_ SL_u64vmuls_
#define SL_luvmuls SL_u64vmuls
#define SL_luv2muls SL_u64v2muls
#define SL_luv3muls SL_u64v3muls
#define SL_luv4muls SL_u64v4muls
#define SL_luvdiv_ SL_u64vdiv_
#define SL_luvdiv SL_u64vdiv
#define SL_luv2div SL_u64v2div
#define SL_luv3div SL_u64v3div
#define SL_luv4div SL_u64v4div
#define SL_luvdivs_ SL_u64vdivs_
#define SL_luvdivs SL_u64vdivs
#define SL_luv2divs SL_u64v2divs
#define SL_luv3divs SL_u64v3divs
#define SL_luv4divs SL_u64v4divs
#define SL_luvaddS_ SL_u64vaddS_
#define SL_luvaddS SL_u64vaddS
#define SL_luv2addS SL_u64v2addS
#define SL_luv3addS SL_u64v3addS
#define SL_luv4addS SL_u64v4addS
#define SL_luvsubS_ SL_u64vsubS_
#define SL_luvsubS SL_u64vsubS
#define SL_luv2subS SL_u64v2subS
#define SL_luv3subS SL_u64v3subS
#define SL_luv4subS SL_u64v4subS
#define SL_luvaddM_ SL_u64vaddM_
#define SL_luvaddM SL_u64vaddM
#define SL_luv2addM SL_u64v2addM
#define SL_luv3addM SL_u64v3addM
#define SL_luv4addM SL_u64v4addM
#define SL_luvsubM_ SL_u64vsubM_
#define SL_luvsubM SL_u64vsubM
#define SL_luv2subM SL_u64v2subM
#define SL_luv3subM SL_u64v3subM
#define SL_luv4subM SL_u64v4subM
#define SL_luvaddSM_ SL_u64vaddSM_
#define SL_luvaddSM SL_u64vaddSM
#define SL_luv2addSM SL_u64v2addSM
#define SL_luv3addSM SL_u64v3addSM
#define SL_luv4addSM SL_u64v4addSM
#define SL_luvsubSM_ SL_u64vsubSM_
#define SL_luvsubSM SL_u64vsubSM
#define SL_luv2subSM SL_u64v2subSM
#define SL_luv3subSM SL_u64v3subSM
#define SL_luv4subSM SL_u64v4subSM
#define SL_luvSadd_ SL_u64vSadd_
#define SL_luvSadd SL_u64vSadd
#define SL_luv2Sadd SL_u64v2Sadd
#define SL_luv3Sadd SL_u64v3Sadd
#define SL_luv4Sadd SL_u64v4Sadd
#define SL_luvSsub_ SL_u64vSsub_
#define SL_luvSsub SL_u64vSsub
#define SL_luv2Ssub SL_u64v2Ssub
#define SL_luv3Ssub SL_u64v3Ssub
#define SL_luv4Ssub SL_u64v4Ssub
#define SL_luvmix_ SL_u64vmix_
#define SL_luvmix SL_u64vmix
#define SL_luv2mix SL_u64v2mix
#define SL_luv3mix SL_u64v3mix
#define SL_luv4mix SL_u64v4mix
#define SL_luvmin_ SL_u64vmin_
#define SL_luvmin SL_u64vmin
#define SL_luv2min SL_u64v2min
#define SL_luv3min SL_u64v3min
#define SL_luv4min SL_u64v4min
#define SL_luvmax_ SL_u64vmax_
#define SL_luvmax SL_u64vmax
#define SL_luv2max SL_u64v2max
#define SL_luv3max SL_u64v3max
#define SL_luv4max SL_u64v4max
#define SL_luvdot_ SL_u64vdot_
#define SL_luvdot SL_u64vdot
#define SL_luv2dot SL_u64v2dot
#define SL_luv3dot SL_u64v3dot
#define SL_luv4dot SL_u64v4dot
#define SL_luvlen_max_ SL_u64vlen_max_
#define SL_luvlen_max SL_u64vlen_max
#define SL_luv2len_max SL_u64v2len_max
#define SL_luv3len_max SL_u64v3len_max
#define SL_luv4len_max SL_u64v4len_max
#define SL_luvlen_manh_ SL_u64vlen_manh_
#define SL_luvlen_manh SL_u64vlen_manh
#define SL_luv2len_manh SL_u64v2len_manh
#define SL_luv3len_manh SL_u64v3len_manh
#define SL_luv4len_manh SL_u64v4len_manh
#define SL_luvlen_srq_ SL_u64vlen_srq_
#define SL_luvlen_srq SL_u64vlen_srq
#define SL_luv2len_sqr SL_u64v2len_sqr
#define SL_luv3len_sqr SL_u64v3len_sqr
#define SL_luv4len_sqr SL_u64v4len_sqr
#define SL_luvlen_ SL_u64vlen_
#define SL_luvlen SL_u64vlen
#define SL_luv2len SL_u64v2len
#define SL_luv3len SL_u64v3len
#define SL_luv4len SL_u64v4len
#define SL_luvdist_ SL_u64vdist_
#define SL_luvdist SL_u64vdist
#define SL_luv2dist SL_u64v2dist
#define SL_luv3dist SL_u64v3dist
#define SL_luv4dist SL_u64v4dist
#define SL_luv2refl SL_u64v2refl
#define SL_luv3refl SL_u64v3refl
#define SL_luv4refl SL_u64v4refl
#define SL_luv2refl_u SL_u64v2refl_u
#define SL_luv3refl_u SL_u64v3refl_u
#define SL_luv4refl_u SL_u64v4refl_u
#define SL_luv2align SL_u64v2align
#define SL_luv3align SL_u64v3align
#define SL_luv4align SL_u64v4align
#define SL_luv2align_u SL_u64v2align_u
#define SL_luv3align_u SL_u64v3align_u
#define SL_luv4align_u SL_u64v4align_u
#define SL_luv2proj SL_u64v2proj
#define SL_luv3proj SL_u64v3proj
#define SL_luv4proj SL_u64v4proj
#define SL_luv2proj_u SL_u64v2proj_u
#define SL_luv3proj_u SL_u64v3proj_u
#define SL_luv4proj_u SL_u64v4proj_u
#define SL_luvmods_ SL_u64vmods_
#define SL_luvmods SL_u64vmods
#define SL_luv2mods SL_u64v2mods
#define SL_luv3mods SL_u64v3mods
#define SL_luv4mods SL_u64v4mods
#define SL_luvmod_ SL_u64vmod_
#define SL_luvmod SL_u64vmod
#define SL_luv2mod SL_u64v2mod
#define SL_luv3mod SL_u64v3mod
#define SL_luv4mod SL_u64v4mod
#define SL_luvand_ SL_u64vand_
#define SL_luvand SL_u64vand
#define SL_luv2and SL_u64v2and
#define SL_luv3and SL_u64v3and
#define SL_luv4and SL_u64v4and
#define SL_luvor_ SL_u64vor_
#define SL_luvor SL_u64vor
#define SL_luv2or SL_u64v2or
#define SL_luv3or SL_u64v3or
#define SL_luv4or SL_u64v4or
#define SL_luvxor_ SL_u64vxor_
#define SL_luvxor SL_u64vxor
#define SL_luv2xor SL_u64v2xor
#define SL_luv3xor SL_u64v3xor
#define SL_luv4xor SL_u64v4xor
#define SL_luvnot_ SL_u64vnot_
#define SL_luvnot SL_u64vnot
#define SL_luv2not SL_u64v2not
#define SL_luv3not SL_u64v3not
#define SL_luv4not SL_u64v4not
#define SL_luvlshfts_ SL_u64vlshfts_
#define SL_luvlshfts SL_u64vlshfts
#define SL_luv2lshfts SL_u64v2lshfts
#define SL_luv3lshfts SL_u64v3lshfts
#define SL_luv4lshfts SL_u64v4lshfts
#define SL_luvlshft_ SL_u64vlshft_
#define SL_luvlshft SL_u64vlshft
#define SL_luv2lshft SL_u64v2lshft
#define SL_luv3lshft SL_u64v3lshft
#define SL_luv4lshft SL_u64v4lshft
#define SL_luvrshfts_ SL_u64vrshfts_
#define SL_luvrshfts SL_u64vrshfts
#define SL_luv2rshfts SL_u64v2rshfts
#define SL_luv3rshfts SL_u64v3rshfts
#define SL_luv4rshfts SL_u64v4rshfts
#define SL_luvrshft_ SL_u64vrshft_
#define SL_luvrshft SL_u64vrshft
#define SL_luv2rshft SL_u64v2rshft
#define SL_luv3rshft SL_u64v3rshft
#define SL_luv4rshft SL_u64v4rshft
#pragma endregion U64
#ifdef SL_STRIP_PREFIX
#   define  XPD_V SL_XPD_V
#   define  XPD_V2 SL_XPD_V2
#   define  XPD_V3 SL_XPD_V3
#   define  XPD_V4 SL_XPD_V4
#   define  FMT_V2 SL_FMT_V2
#   define  FMT_V3 SL_FMT_V3
#   define  FMT_V4 SL_FMT_V4
#   define  vsize SL_vsize
#   define  i8v2_zero SL_i8v2_zero
#   define  i8v2_one SL_i8v2_one
#   define  i8v2_right SL_i8v2_right
#   define  i8v2_up SL_i8v2_up
#   define  i8v2_left SL_i8v2_left
#   define  i8v2_down SL_i8v2_down
#   define  i8v3_zero SL_i8v3_zero
#   define  i8v3_one SL_i8v3_one
#   define  i8v3_right SL_i8v3_right
#   define  i8v3_up SL_i8v3_up
#   define  i8v3_forw SL_i8v3_forw
#   define  i8v3_left SL_i8v3_left
#   define  i8v3_down SL_i8v3_down
#   define  i8v3_back SL_i8v3_back
#   define  i8v4_zero SL_i8v4_zero
#   define  i8v4_one SL_i8v4_one
#   define  i8v4_white SL_i8v4_white
#   define  i8v4_black SL_i8v4_black
#   define  i8v4_red SL_i8v4_red
#   define  i8v4_green SL_i8v4_green
#   define  i8v4_blue SL_i8v4_blue
#   define  i8v4_yellow SL_i8v4_yellow
#   define  i8v4_cyan SL_i8v4_cyan
#   define  i8v4_purple SL_i8v4_purple
#   define  i8v2_ SL_i8v2_
#   define  i8v3_ SL_i8v3_
#   define  i8v4_ SL_i8v4_
#   define  i8v2s SL_i8v2s
#   define  i8v3s SL_i8v3s
#   define  i8v4s SL_i8v4s
#   define  i8vv SL_i8vv
#   define  i8v2v SL_i8v2v
#   define  i8v3v SL_i8v3v
#   define  i8v4v SL_i8v4v
#   define  i8vequ_ SL_i8vequ_
#   define  i8vequ SL_i8vequ
#   define  i8v2equ SL_i8v2equ
#   define  i8v3equ SL_i8v3equ
#   define  i8v4equ SL_i8v4equ
#   define  i8vadd_ SL_i8vadd_
#   define  i8vadd SL_i8vadd
#   define  i8v2add SL_i8v2add
#   define  i8v3add SL_i8v3add
#   define  i8v4add SL_i8v4add
#   define  i8vsub_ SL_i8vsub_
#   define  i8vsub SL_i8vsub
#   define  i8v2sub SL_i8v2sub
#   define  i8v3sub SL_i8v3sub
#   define  i8v4sub SL_i8v4sub
#   define  i8vmul_ SL_i8vmul_
#   define  i8vmul SL_i8vmul
#   define  i8v2mul SL_i8v2mul
#   define  i8v3mul SL_i8v3mul
#   define  i8v4mul SL_i8v4mul
#   define  i8vmuls_ SL_i8vmuls_
#   define  i8vmuls SL_i8vmuls
#   define  i8v2muls SL_i8v2muls
#   define  i8v3muls SL_i8v3muls
#   define  i8v4muls SL_i8v4muls
#   define  i8vdiv_ SL_i8vdiv_
#   define  i8vdiv SL_i8vdiv
#   define  i8v2div SL_i8v2div
#   define  i8v3div SL_i8v3div
#   define  i8v4div SL_i8v4div
#   define  i8vdivs_ SL_i8vdivs_
#   define  i8vdivs SL_i8vdivs
#   define  i8v2divs SL_i8v2divs
#   define  i8v3divs SL_i8v3divs
#   define  i8v4divs SL_i8v4divs
#   define  i8vaddS_ SL_i8vaddS_
#   define  i8vaddS SL_i8vaddS
#   define  i8v2addS SL_i8v2addS
#   define  i8v3addS SL_i8v3addS
#   define  i8v4addS SL_i8v4addS
#   define  i8vsubS_ SL_i8vsubS_
#   define  i8vsubS SL_i8vsubS
#   define  i8v2subS SL_i8v2subS
#   define  i8v3subS SL_i8v3subS
#   define  i8v4subS SL_i8v4subS
#   define  i8vaddM_ SL_i8vaddM_
#   define  i8vaddM SL_i8vaddM
#   define  i8v2addM SL_i8v2addM
#   define  i8v3addM SL_i8v3addM
#   define  i8v4addM SL_i8v4addM
#   define  i8vsubM_ SL_i8vsubM_
#   define  i8vsubM SL_i8vsubM
#   define  i8v2subM SL_i8v2subM
#   define  i8v3subM SL_i8v3subM
#   define  i8v4subM SL_i8v4subM
#   define  i8vaddSM_ SL_i8vaddSM_
#   define  i8vaddSM SL_i8vaddSM
#   define  i8v2addSM SL_i8v2addSM
#   define  i8v3addSM SL_i8v3addSM
#   define  i8v4addSM SL_i8v4addSM
#   define  i8vsubSM_ SL_i8vsubSM_
#   define  i8vsubSM SL_i8vsubSM
#   define  i8v2subSM SL_i8v2subSM
#   define  i8v3subSM SL_i8v3subSM
#   define  i8v4subSM SL_i8v4subSM
#   define  i8vSadd_ SL_i8vSadd_
#   define  i8vSadd SL_i8vSadd
#   define  i8v2Sadd SL_i8v2Sadd
#   define  i8v3Sadd SL_i8v3Sadd
#   define  i8v4Sadd SL_i8v4Sadd
#   define  i8vSsub_ SL_i8vSsub_
#   define  i8vSsub SL_i8vSsub
#   define  i8v2Ssub SL_i8v2Ssub
#   define  i8v3Ssub SL_i8v3Ssub
#   define  i8v4Ssub SL_i8v4Ssub
#   define  i8vmix_ SL_i8vmix_
#   define  i8vmix SL_i8vmix
#   define  i8v2mix SL_i8v2mix
#   define  i8v3mix SL_i8v3mix
#   define  i8v4mix SL_i8v4mix
#   define  i8vneg_ SL_i8vneg_
#   define  i8vneg SL_i8vneg
#   define  i8v2neg SL_i8v2neg
#   define  i8v3neg SL_i8v3neg
#   define  i8v4neg SL_i8v4neg
#   define  i8vabs_ SL_i8vabs_
#   define  i8vabs SL_i8vabs
#   define  i8v2abs SL_i8v2abs
#   define  i8v3abs SL_i8v3abs
#   define  i8v4abs SL_i8v4abs
#   define  i8vmin_ SL_i8vmin_
#   define  i8vmin SL_i8vmin
#   define  i8v2min SL_i8v2min
#   define  i8v3min SL_i8v3min
#   define  i8v4min SL_i8v4min
#   define  i8vmax_ SL_i8vmax_
#   define  i8vmax SL_i8vmax
#   define  i8v2max SL_i8v2max
#   define  i8v3max SL_i8v3max
#   define  i8v4max SL_i8v4max
#   define  i8vdot_ SL_i8vdot_
#   define  i8vdot SL_i8vdot
#   define  i8v2dot SL_i8v2dot
#   define  i8v3dot SL_i8v3dot
#   define  i8v4dot SL_i8v4dot
#   define  i8vlen_max_ SL_i8vlen_max_
#   define  i8vlen_max SL_i8vlen_max
#   define  i8v2len_max SL_i8v2len_max
#   define  i8v3len_max SL_i8v3len_max
#   define  i8v4len_max SL_i8v4len_max
#   define  i8vlen_manh_ SL_i8vlen_manh_
#   define  i8vlen_manh SL_i8vlen_manh
#   define  i8v2len_manh SL_i8v2len_manh
#   define  i8v3len_manh SL_i8v3len_manh
#   define  i8v4len_manh SL_i8v4len_manh
#   define  i8vlen_srq_ SL_i8vlen_srq_
#   define  i8vlen_srq SL_i8vlen_srq
#   define  i8v2len_sqr SL_i8v2len_sqr
#   define  i8v3len_sqr SL_i8v3len_sqr
#   define  i8v4len_sqr SL_i8v4len_sqr
#   define  i8vlen_ SL_i8vlen_
#   define  i8vlen SL_i8vlen
#   define  i8v2len SL_i8v2len
#   define  i8v3len SL_i8v3len
#   define  i8v4len SL_i8v4len
#   define  i8vdist_ SL_i8vdist_
#   define  i8vdist SL_i8vdist
#   define  i8v2dist SL_i8v2dist
#   define  i8v3dist SL_i8v3dist
#   define  i8v4dist SL_i8v4dist
#   define  i8v2refl SL_i8v2refl
#   define  i8v3refl SL_i8v3refl
#   define  i8v4refl SL_i8v4refl
#   define  i8v2refl_u SL_i8v2refl_u
#   define  i8v3refl_u SL_i8v3refl_u
#   define  i8v4refl_u SL_i8v4refl_u
#   define  i8v2align SL_i8v2align
#   define  i8v3align SL_i8v3align
#   define  i8v4align SL_i8v4align
#   define  i8v2align_u SL_i8v2align_u
#   define  i8v3align_u SL_i8v3align_u
#   define  i8v4align_u SL_i8v4align_u
#   define  i8v2proj SL_i8v2proj
#   define  i8v3proj SL_i8v3proj
#   define  i8v4proj SL_i8v4proj
#   define  i8v2proj_u SL_i8v2proj_u
#   define  i8v3proj_u SL_i8v3proj_u
#   define  i8v4proj_u SL_i8v4proj_u
#   define  i8vmods_ SL_i8vmods_
#   define  i8vmods SL_i8vmods
#   define  i8v2mods SL_i8v2mods
#   define  i8v3mods SL_i8v3mods
#   define  i8v4mods SL_i8v4mods
#   define  i8vmod_ SL_i8vmod_
#   define  i8vmod SL_i8vmod
#   define  i8v2mod SL_i8v2mod
#   define  i8v3mod SL_i8v3mod
#   define  i8v4mod SL_i8v4mod
#   define  i8v2cross SL_i8v2cross
#   define  i8v3cross SL_i8v3cross
#   define  i8vand_ SL_i8vand_
#   define  i8vand SL_i8vand
#   define  i8v2and SL_i8v2and
#   define  i8v3and SL_i8v3and
#   define  i8v4and SL_i8v4and
#   define  i8vor_ SL_i8vor_
#   define  i8vor SL_i8vor
#   define  i8v2or SL_i8v2or
#   define  i8v3or SL_i8v3or
#   define  i8v4or SL_i8v4or
#   define  i8vxor_ SL_i8vxor_
#   define  i8vxor SL_i8vxor
#   define  i8v2xor SL_i8v2xor
#   define  i8v3xor SL_i8v3xor
#   define  i8v4xor SL_i8v4xor
#   define  i8vnot_ SL_i8vnot_
#   define  i8vnot SL_i8vnot
#   define  i8v2not SL_i8v2not
#   define  i8v3not SL_i8v3not
#   define  i8v4not SL_i8v4not
#   define  i8vlshfts_ SL_i8vlshfts_
#   define  i8vlshfts SL_i8vlshfts
#   define  i8v2lshfts SL_i8v2lshfts
#   define  i8v3lshfts SL_i8v3lshfts
#   define  i8v4lshfts SL_i8v4lshfts
#   define  i8vlshft_ SL_i8vlshft_
#   define  i8vlshft SL_i8vlshft
#   define  i8v2lshft SL_i8v2lshft
#   define  i8v3lshft SL_i8v3lshft
#   define  i8v4lshft SL_i8v4lshft
#   define  i8vrshfts_ SL_i8vrshfts_
#   define  i8vrshfts SL_i8vrshfts
#   define  i8v2rshfts SL_i8v2rshfts
#   define  i8v3rshfts SL_i8v3rshfts
#   define  i8v4rshfts SL_i8v4rshfts
#   define  i8vrshft_ SL_i8vrshft_
#   define  i8vrshft SL_i8vrshft
#   define  i8v2rshft SL_i8v2rshft
#   define  i8v3rshft SL_i8v3rshft
#   define  i8v4rshft SL_i8v4rshft
#   define  i16v2_zero SL_i16v2_zero
#   define  i16v2_one SL_i16v2_one
#   define  i16v2_right SL_i16v2_right
#   define  i16v2_up SL_i16v2_up
#   define  i16v2_left SL_i16v2_left
#   define  i16v2_down SL_i16v2_down
#   define  i16v3_zero SL_i16v3_zero
#   define  i16v3_one SL_i16v3_one
#   define  i16v3_right SL_i16v3_right
#   define  i16v3_up SL_i16v3_up
#   define  i16v3_forw SL_i16v3_forw
#   define  i16v3_left SL_i16v3_left
#   define  i16v3_down SL_i16v3_down
#   define  i16v3_back SL_i16v3_back
#   define  i16v4_zero SL_i16v4_zero
#   define  i16v4_one SL_i16v4_one
#   define  i16v4_white SL_i16v4_white
#   define  i16v4_black SL_i16v4_black
#   define  i16v4_red SL_i16v4_red
#   define  i16v4_green SL_i16v4_green
#   define  i16v4_blue SL_i16v4_blue
#   define  i16v4_yellow SL_i16v4_yellow
#   define  i16v4_cyan SL_i16v4_cyan
#   define  i16v4_purple SL_i16v4_purple
#   define  i16v2_ SL_i16v2_
#   define  i16v3_ SL_i16v3_
#   define  i16v4_ SL_i16v4_
#   define  i16v2s SL_i16v2s
#   define  i16v3s SL_i16v3s
#   define  i16v4s SL_i16v4s
#   define  i16vv SL_i16vv
#   define  i16v2v SL_i16v2v
#   define  i16v3v SL_i16v3v
#   define  i16v4v SL_i16v4v
#   define  i16vequ_ SL_i16vequ_
#   define  i16vequ SL_i16vequ
#   define  i16v2equ SL_i16v2equ
#   define  i16v3equ SL_i16v3equ
#   define  i16v4equ SL_i16v4equ
#   define  i16vadd_ SL_i16vadd_
#   define  i16vadd SL_i16vadd
#   define  i16v2add SL_i16v2add
#   define  i16v3add SL_i16v3add
#   define  i16v4add SL_i16v4add
#   define  i16vsub_ SL_i16vsub_
#   define  i16vsub SL_i16vsub
#   define  i16v2sub SL_i16v2sub
#   define  i16v3sub SL_i16v3sub
#   define  i16v4sub SL_i16v4sub
#   define  i16vmul_ SL_i16vmul_
#   define  i16vmul SL_i16vmul
#   define  i16v2mul SL_i16v2mul
#   define  i16v3mul SL_i16v3mul
#   define  i16v4mul SL_i16v4mul
#   define  i16vmuls_ SL_i16vmuls_
#   define  i16vmuls SL_i16vmuls
#   define  i16v2muls SL_i16v2muls
#   define  i16v3muls SL_i16v3muls
#   define  i16v4muls SL_i16v4muls
#   define  i16vdiv_ SL_i16vdiv_
#   define  i16vdiv SL_i16vdiv
#   define  i16v2div SL_i16v2div
#   define  i16v3div SL_i16v3div
#   define  i16v4div SL_i16v4div
#   define  i16vdivs_ SL_i16vdivs_
#   define  i16vdivs SL_i16vdivs
#   define  i16v2divs SL_i16v2divs
#   define  i16v3divs SL_i16v3divs
#   define  i16v4divs SL_i16v4divs
#   define  i16vaddS_ SL_i16vaddS_
#   define  i16vaddS SL_i16vaddS
#   define  i16v2addS SL_i16v2addS
#   define  i16v3addS SL_i16v3addS
#   define  i16v4addS SL_i16v4addS
#   define  i16vsubS_ SL_i16vsubS_
#   define  i16vsubS SL_i16vsubS
#   define  i16v2subS SL_i16v2subS
#   define  i16v3subS SL_i16v3subS
#   define  i16v4subS SL_i16v4subS
#   define  i16vaddM_ SL_i16vaddM_
#   define  i16vaddM SL_i16vaddM
#   define  i16v2addM SL_i16v2addM
#   define  i16v3addM SL_i16v3addM
#   define  i16v4addM SL_i16v4addM
#   define  i16vsubM_ SL_i16vsubM_
#   define  i16vsubM SL_i16vsubM
#   define  i16v2subM SL_i16v2subM
#   define  i16v3subM SL_i16v3subM
#   define  i16v4subM SL_i16v4subM
#   define  i16vaddSM_ SL_i16vaddSM_
#   define  i16vaddSM SL_i16vaddSM
#   define  i16v2addSM SL_i16v2addSM
#   define  i16v3addSM SL_i16v3addSM
#   define  i16v4addSM SL_i16v4addSM
#   define  i16vsubSM_ SL_i16vsubSM_
#   define  i16vsubSM SL_i16vsubSM
#   define  i16v2subSM SL_i16v2subSM
#   define  i16v3subSM SL_i16v3subSM
#   define  i16v4subSM SL_i16v4subSM
#   define  i16vSadd_ SL_i16vSadd_
#   define  i16vSadd SL_i16vSadd
#   define  i16v2Sadd SL_i16v2Sadd
#   define  i16v3Sadd SL_i16v3Sadd
#   define  i16v4Sadd SL_i16v4Sadd
#   define  i16vSsub_ SL_i16vSsub_
#   define  i16vSsub SL_i16vSsub
#   define  i16v2Ssub SL_i16v2Ssub
#   define  i16v3Ssub SL_i16v3Ssub
#   define  i16v4Ssub SL_i16v4Ssub
#   define  i16vmix_ SL_i16vmix_
#   define  i16vmix SL_i16vmix
#   define  i16v2mix SL_i16v2mix
#   define  i16v3mix SL_i16v3mix
#   define  i16v4mix SL_i16v4mix
#   define  i16vneg_ SL_i16vneg_
#   define  i16vneg SL_i16vneg
#   define  i16v2neg SL_i16v2neg
#   define  i16v3neg SL_i16v3neg
#   define  i16v4neg SL_i16v4neg
#   define  i16vabs_ SL_i16vabs_
#   define  i16vabs SL_i16vabs
#   define  i16v2abs SL_i16v2abs
#   define  i16v3abs SL_i16v3abs
#   define  i16v4abs SL_i16v4abs
#   define  i16vmin_ SL_i16vmin_
#   define  i16vmin SL_i16vmin
#   define  i16v2min SL_i16v2min
#   define  i16v3min SL_i16v3min
#   define  i16v4min SL_i16v4min
#   define  i16vmax_ SL_i16vmax_
#   define  i16vmax SL_i16vmax
#   define  i16v2max SL_i16v2max
#   define  i16v3max SL_i16v3max
#   define  i16v4max SL_i16v4max
#   define  i16vdot_ SL_i16vdot_
#   define  i16vdot SL_i16vdot
#   define  i16v2dot SL_i16v2dot
#   define  i16v3dot SL_i16v3dot
#   define  i16v4dot SL_i16v4dot
#   define  i16vlen_max_ SL_i16vlen_max_
#   define  i16vlen_max SL_i16vlen_max
#   define  i16v2len_max SL_i16v2len_max
#   define  i16v3len_max SL_i16v3len_max
#   define  i16v4len_max SL_i16v4len_max
#   define  i16vlen_manh_ SL_i16vlen_manh_
#   define  i16vlen_manh SL_i16vlen_manh
#   define  i16v2len_manh SL_i16v2len_manh
#   define  i16v3len_manh SL_i16v3len_manh
#   define  i16v4len_manh SL_i16v4len_manh
#   define  i16vlen_srq_ SL_i16vlen_srq_
#   define  i16vlen_srq SL_i16vlen_srq
#   define  i16v2len_sqr SL_i16v2len_sqr
#   define  i16v3len_sqr SL_i16v3len_sqr
#   define  i16v4len_sqr SL_i16v4len_sqr
#   define  i16vlen_ SL_i16vlen_
#   define  i16vlen SL_i16vlen
#   define  i16v2len SL_i16v2len
#   define  i16v3len SL_i16v3len
#   define  i16v4len SL_i16v4len
#   define  i16vdist_ SL_i16vdist_
#   define  i16vdist SL_i16vdist
#   define  i16v2dist SL_i16v2dist
#   define  i16v3dist SL_i16v3dist
#   define  i16v4dist SL_i16v4dist
#   define  i16v2refl SL_i16v2refl
#   define  i16v3refl SL_i16v3refl
#   define  i16v4refl SL_i16v4refl
#   define  i16v2refl_u SL_i16v2refl_u
#   define  i16v3refl_u SL_i16v3refl_u
#   define  i16v4refl_u SL_i16v4refl_u
#   define  i16v2align SL_i16v2align
#   define  i16v3align SL_i16v3align
#   define  i16v4align SL_i16v4align
#   define  i16v2align_u SL_i16v2align_u
#   define  i16v3align_u SL_i16v3align_u
#   define  i16v4align_u SL_i16v4align_u
#   define  i16v2proj SL_i16v2proj
#   define  i16v3proj SL_i16v3proj
#   define  i16v4proj SL_i16v4proj
#   define  i16v2proj_u SL_i16v2proj_u
#   define  i16v3proj_u SL_i16v3proj_u
#   define  i16v4proj_u SL_i16v4proj_u
#   define  i16vmods_ SL_i16vmods_
#   define  i16vmods SL_i16vmods
#   define  i16v2mods SL_i16v2mods
#   define  i16v3mods SL_i16v3mods
#   define  i16v4mods SL_i16v4mods
#   define  i16vmod_ SL_i16vmod_
#   define  i16vmod SL_i16vmod
#   define  i16v2mod SL_i16v2mod
#   define  i16v3mod SL_i16v3mod
#   define  i16v4mod SL_i16v4mod
#   define  i16v2cross SL_i16v2cross
#   define  i16v3cross SL_i16v3cross
#   define  i16vand_ SL_i16vand_
#   define  i16vand SL_i16vand
#   define  i16v2and SL_i16v2and
#   define  i16v3and SL_i16v3and
#   define  i16v4and SL_i16v4and
#   define  i16vor_ SL_i16vor_
#   define  i16vor SL_i16vor
#   define  i16v2or SL_i16v2or
#   define  i16v3or SL_i16v3or
#   define  i16v4or SL_i16v4or
#   define  i16vxor_ SL_i16vxor_
#   define  i16vxor SL_i16vxor
#   define  i16v2xor SL_i16v2xor
#   define  i16v3xor SL_i16v3xor
#   define  i16v4xor SL_i16v4xor
#   define  i16vnot_ SL_i16vnot_
#   define  i16vnot SL_i16vnot
#   define  i16v2not SL_i16v2not
#   define  i16v3not SL_i16v3not
#   define  i16v4not SL_i16v4not
#   define  i16vlshfts_ SL_i16vlshfts_
#   define  i16vlshfts SL_i16vlshfts
#   define  i16v2lshfts SL_i16v2lshfts
#   define  i16v3lshfts SL_i16v3lshfts
#   define  i16v4lshfts SL_i16v4lshfts
#   define  i16vlshft_ SL_i16vlshft_
#   define  i16vlshft SL_i16vlshft
#   define  i16v2lshft SL_i16v2lshft
#   define  i16v3lshft SL_i16v3lshft
#   define  i16v4lshft SL_i16v4lshft
#   define  i16vrshfts_ SL_i16vrshfts_
#   define  i16vrshfts SL_i16vrshfts
#   define  i16v2rshfts SL_i16v2rshfts
#   define  i16v3rshfts SL_i16v3rshfts
#   define  i16v4rshfts SL_i16v4rshfts
#   define  i16vrshft_ SL_i16vrshft_
#   define  i16vrshft SL_i16vrshft
#   define  i16v2rshft SL_i16v2rshft
#   define  i16v3rshft SL_i16v3rshft
#   define  i16v4rshft SL_i16v4rshft
#   define  i32v2_zero SL_i32v2_zero
#   define  i32v2_one SL_i32v2_one
#   define  i32v2_right SL_i32v2_right
#   define  i32v2_up SL_i32v2_up
#   define  i32v2_left SL_i32v2_left
#   define  i32v2_down SL_i32v2_down
#   define  i32v3_zero SL_i32v3_zero
#   define  i32v3_one SL_i32v3_one
#   define  i32v3_right SL_i32v3_right
#   define  i32v3_up SL_i32v3_up
#   define  i32v3_forw SL_i32v3_forw
#   define  i32v3_left SL_i32v3_left
#   define  i32v3_down SL_i32v3_down
#   define  i32v3_back SL_i32v3_back
#   define  i32v4_zero SL_i32v4_zero
#   define  i32v4_one SL_i32v4_one
#   define  i32v4_white SL_i32v4_white
#   define  i32v4_black SL_i32v4_black
#   define  i32v4_red SL_i32v4_red
#   define  i32v4_green SL_i32v4_green
#   define  i32v4_blue SL_i32v4_blue
#   define  i32v4_yellow SL_i32v4_yellow
#   define  i32v4_cyan SL_i32v4_cyan
#   define  i32v4_purple SL_i32v4_purple
#   define  i32v2_ SL_i32v2_
#   define  i32v3_ SL_i32v3_
#   define  i32v4_ SL_i32v4_
#   define  i32v2s SL_i32v2s
#   define  i32v3s SL_i32v3s
#   define  i32v4s SL_i32v4s
#   define  i32vv SL_i32vv
#   define  i32v2v SL_i32v2v
#   define  i32v3v SL_i32v3v
#   define  i32v4v SL_i32v4v
#   define  i32vequ_ SL_i32vequ_
#   define  i32vequ SL_i32vequ
#   define  i32v2equ SL_i32v2equ
#   define  i32v3equ SL_i32v3equ
#   define  i32v4equ SL_i32v4equ
#   define  i32vadd_ SL_i32vadd_
#   define  i32vadd SL_i32vadd
#   define  i32v2add SL_i32v2add
#   define  i32v3add SL_i32v3add
#   define  i32v4add SL_i32v4add
#   define  i32vsub_ SL_i32vsub_
#   define  i32vsub SL_i32vsub
#   define  i32v2sub SL_i32v2sub
#   define  i32v3sub SL_i32v3sub
#   define  i32v4sub SL_i32v4sub
#   define  i32vmul_ SL_i32vmul_
#   define  i32vmul SL_i32vmul
#   define  i32v2mul SL_i32v2mul
#   define  i32v3mul SL_i32v3mul
#   define  i32v4mul SL_i32v4mul
#   define  i32vmuls_ SL_i32vmuls_
#   define  i32vmuls SL_i32vmuls
#   define  i32v2muls SL_i32v2muls
#   define  i32v3muls SL_i32v3muls
#   define  i32v4muls SL_i32v4muls
#   define  i32vdiv_ SL_i32vdiv_
#   define  i32vdiv SL_i32vdiv
#   define  i32v2div SL_i32v2div
#   define  i32v3div SL_i32v3div
#   define  i32v4div SL_i32v4div
#   define  i32vdivs_ SL_i32vdivs_
#   define  i32vdivs SL_i32vdivs
#   define  i32v2divs SL_i32v2divs
#   define  i32v3divs SL_i32v3divs
#   define  i32v4divs SL_i32v4divs
#   define  i32vaddS_ SL_i32vaddS_
#   define  i32vaddS SL_i32vaddS
#   define  i32v2addS SL_i32v2addS
#   define  i32v3addS SL_i32v3addS
#   define  i32v4addS SL_i32v4addS
#   define  i32vsubS_ SL_i32vsubS_
#   define  i32vsubS SL_i32vsubS
#   define  i32v2subS SL_i32v2subS
#   define  i32v3subS SL_i32v3subS
#   define  i32v4subS SL_i32v4subS
#   define  i32vaddM_ SL_i32vaddM_
#   define  i32vaddM SL_i32vaddM
#   define  i32v2addM SL_i32v2addM
#   define  i32v3addM SL_i32v3addM
#   define  i32v4addM SL_i32v4addM
#   define  i32vsubM_ SL_i32vsubM_
#   define  i32vsubM SL_i32vsubM
#   define  i32v2subM SL_i32v2subM
#   define  i32v3subM SL_i32v3subM
#   define  i32v4subM SL_i32v4subM
#   define  i32vaddSM_ SL_i32vaddSM_
#   define  i32vaddSM SL_i32vaddSM
#   define  i32v2addSM SL_i32v2addSM
#   define  i32v3addSM SL_i32v3addSM
#   define  i32v4addSM SL_i32v4addSM
#   define  i32vsubSM_ SL_i32vsubSM_
#   define  i32vsubSM SL_i32vsubSM
#   define  i32v2subSM SL_i32v2subSM
#   define  i32v3subSM SL_i32v3subSM
#   define  i32v4subSM SL_i32v4subSM
#   define  i32vSadd_ SL_i32vSadd_
#   define  i32vSadd SL_i32vSadd
#   define  i32v2Sadd SL_i32v2Sadd
#   define  i32v3Sadd SL_i32v3Sadd
#   define  i32v4Sadd SL_i32v4Sadd
#   define  i32vSsub_ SL_i32vSsub_
#   define  i32vSsub SL_i32vSsub
#   define  i32v2Ssub SL_i32v2Ssub
#   define  i32v3Ssub SL_i32v3Ssub
#   define  i32v4Ssub SL_i32v4Ssub
#   define  i32vmix_ SL_i32vmix_
#   define  i32vmix SL_i32vmix
#   define  i32v2mix SL_i32v2mix
#   define  i32v3mix SL_i32v3mix
#   define  i32v4mix SL_i32v4mix
#   define  i32vneg_ SL_i32vneg_
#   define  i32vneg SL_i32vneg
#   define  i32v2neg SL_i32v2neg
#   define  i32v3neg SL_i32v3neg
#   define  i32v4neg SL_i32v4neg
#   define  i32vabs_ SL_i32vabs_
#   define  i32vabs SL_i32vabs
#   define  i32v2abs SL_i32v2abs
#   define  i32v3abs SL_i32v3abs
#   define  i32v4abs SL_i32v4abs
#   define  i32vmin_ SL_i32vmin_
#   define  i32vmin SL_i32vmin
#   define  i32v2min SL_i32v2min
#   define  i32v3min SL_i32v3min
#   define  i32v4min SL_i32v4min
#   define  i32vmax_ SL_i32vmax_
#   define  i32vmax SL_i32vmax
#   define  i32v2max SL_i32v2max
#   define  i32v3max SL_i32v3max
#   define  i32v4max SL_i32v4max
#   define  i32vdot_ SL_i32vdot_
#   define  i32vdot SL_i32vdot
#   define  i32v2dot SL_i32v2dot
#   define  i32v3dot SL_i32v3dot
#   define  i32v4dot SL_i32v4dot
#   define  i32vlen_max_ SL_i32vlen_max_
#   define  i32vlen_max SL_i32vlen_max
#   define  i32v2len_max SL_i32v2len_max
#   define  i32v3len_max SL_i32v3len_max
#   define  i32v4len_max SL_i32v4len_max
#   define  i32vlen_manh_ SL_i32vlen_manh_
#   define  i32vlen_manh SL_i32vlen_manh
#   define  i32v2len_manh SL_i32v2len_manh
#   define  i32v3len_manh SL_i32v3len_manh
#   define  i32v4len_manh SL_i32v4len_manh
#   define  i32vlen_srq_ SL_i32vlen_srq_
#   define  i32vlen_srq SL_i32vlen_srq
#   define  i32v2len_sqr SL_i32v2len_sqr
#   define  i32v3len_sqr SL_i32v3len_sqr
#   define  i32v4len_sqr SL_i32v4len_sqr
#   define  i32vlen_ SL_i32vlen_
#   define  i32vlen SL_i32vlen
#   define  i32v2len SL_i32v2len
#   define  i32v3len SL_i32v3len
#   define  i32v4len SL_i32v4len
#   define  i32vdist_ SL_i32vdist_
#   define  i32vdist SL_i32vdist
#   define  i32v2dist SL_i32v2dist
#   define  i32v3dist SL_i32v3dist
#   define  i32v4dist SL_i32v4dist
#   define  i32v2refl SL_i32v2refl
#   define  i32v3refl SL_i32v3refl
#   define  i32v4refl SL_i32v4refl
#   define  i32v2refl_u SL_i32v2refl_u
#   define  i32v3refl_u SL_i32v3refl_u
#   define  i32v4refl_u SL_i32v4refl_u
#   define  i32v2align SL_i32v2align
#   define  i32v3align SL_i32v3align
#   define  i32v4align SL_i32v4align
#   define  i32v2align_u SL_i32v2align_u
#   define  i32v3align_u SL_i32v3align_u
#   define  i32v4align_u SL_i32v4align_u
#   define  i32v2proj SL_i32v2proj
#   define  i32v3proj SL_i32v3proj
#   define  i32v4proj SL_i32v4proj
#   define  i32v2proj_u SL_i32v2proj_u
#   define  i32v3proj_u SL_i32v3proj_u
#   define  i32v4proj_u SL_i32v4proj_u
#   define  i32vmods_ SL_i32vmods_
#   define  i32vmods SL_i32vmods
#   define  i32v2mods SL_i32v2mods
#   define  i32v3mods SL_i32v3mods
#   define  i32v4mods SL_i32v4mods
#   define  i32vmod_ SL_i32vmod_
#   define  i32vmod SL_i32vmod
#   define  i32v2mod SL_i32v2mod
#   define  i32v3mod SL_i32v3mod
#   define  i32v4mod SL_i32v4mod
#   define  i32v2cross SL_i32v2cross
#   define  i32v3cross SL_i32v3cross
#   define  i32vand_ SL_i32vand_
#   define  i32vand SL_i32vand
#   define  i32v2and SL_i32v2and
#   define  i32v3and SL_i32v3and
#   define  i32v4and SL_i32v4and
#   define  i32vor_ SL_i32vor_
#   define  i32vor SL_i32vor
#   define  i32v2or SL_i32v2or
#   define  i32v3or SL_i32v3or
#   define  i32v4or SL_i32v4or
#   define  i32vxor_ SL_i32vxor_
#   define  i32vxor SL_i32vxor
#   define  i32v2xor SL_i32v2xor
#   define  i32v3xor SL_i32v3xor
#   define  i32v4xor SL_i32v4xor
#   define  i32vnot_ SL_i32vnot_
#   define  i32vnot SL_i32vnot
#   define  i32v2not SL_i32v2not
#   define  i32v3not SL_i32v3not
#   define  i32v4not SL_i32v4not
#   define  i32vlshfts_ SL_i32vlshfts_
#   define  i32vlshfts SL_i32vlshfts
#   define  i32v2lshfts SL_i32v2lshfts
#   define  i32v3lshfts SL_i32v3lshfts
#   define  i32v4lshfts SL_i32v4lshfts
#   define  i32vlshft_ SL_i32vlshft_
#   define  i32vlshft SL_i32vlshft
#   define  i32v2lshft SL_i32v2lshft
#   define  i32v3lshft SL_i32v3lshft
#   define  i32v4lshft SL_i32v4lshft
#   define  i32vrshfts_ SL_i32vrshfts_
#   define  i32vrshfts SL_i32vrshfts
#   define  i32v2rshfts SL_i32v2rshfts
#   define  i32v3rshfts SL_i32v3rshfts
#   define  i32v4rshfts SL_i32v4rshfts
#   define  i32vrshft_ SL_i32vrshft_
#   define  i32vrshft SL_i32vrshft
#   define  i32v2rshft SL_i32v2rshft
#   define  i32v3rshft SL_i32v3rshft
#   define  i32v4rshft SL_i32v4rshft
#   define  i64v2_zero SL_i64v2_zero
#   define  i64v2_one SL_i64v2_one
#   define  i64v2_right SL_i64v2_right
#   define  i64v2_up SL_i64v2_up
#   define  i64v2_left SL_i64v2_left
#   define  i64v2_down SL_i64v2_down
#   define  i64v3_zero SL_i64v3_zero
#   define  i64v3_one SL_i64v3_one
#   define  i64v3_right SL_i64v3_right
#   define  i64v3_up SL_i64v3_up
#   define  i64v3_forw SL_i64v3_forw
#   define  i64v3_left SL_i64v3_left
#   define  i64v3_down SL_i64v3_down
#   define  i64v3_back SL_i64v3_back
#   define  i64v4_zero SL_i64v4_zero
#   define  i64v4_one SL_i64v4_one
#   define  i64v4_white SL_i64v4_white
#   define  i64v4_black SL_i64v4_black
#   define  i64v4_red SL_i64v4_red
#   define  i64v4_green SL_i64v4_green
#   define  i64v4_blue SL_i64v4_blue
#   define  i64v4_yellow SL_i64v4_yellow
#   define  i64v4_cyan SL_i64v4_cyan
#   define  i64v4_purple SL_i64v4_purple
#   define  i64v2_ SL_i64v2_
#   define  i64v3_ SL_i64v3_
#   define  i64v4_ SL_i64v4_
#   define  i64v2s SL_i64v2s
#   define  i64v3s SL_i64v3s
#   define  i64v4s SL_i64v4s
#   define  i64vv SL_i64vv
#   define  i64v2v SL_i64v2v
#   define  i64v3v SL_i64v3v
#   define  i64v4v SL_i64v4v
#   define  i64vequ_ SL_i64vequ_
#   define  i64vequ SL_i64vequ
#   define  i64v2equ SL_i64v2equ
#   define  i64v3equ SL_i64v3equ
#   define  i64v4equ SL_i64v4equ
#   define  i64vadd_ SL_i64vadd_
#   define  i64vadd SL_i64vadd
#   define  i64v2add SL_i64v2add
#   define  i64v3add SL_i64v3add
#   define  i64v4add SL_i64v4add
#   define  i64vsub_ SL_i64vsub_
#   define  i64vsub SL_i64vsub
#   define  i64v2sub SL_i64v2sub
#   define  i64v3sub SL_i64v3sub
#   define  i64v4sub SL_i64v4sub
#   define  i64vmul_ SL_i64vmul_
#   define  i64vmul SL_i64vmul
#   define  i64v2mul SL_i64v2mul
#   define  i64v3mul SL_i64v3mul
#   define  i64v4mul SL_i64v4mul
#   define  i64vmuls_ SL_i64vmuls_
#   define  i64vmuls SL_i64vmuls
#   define  i64v2muls SL_i64v2muls
#   define  i64v3muls SL_i64v3muls
#   define  i64v4muls SL_i64v4muls
#   define  i64vdiv_ SL_i64vdiv_
#   define  i64vdiv SL_i64vdiv
#   define  i64v2div SL_i64v2div
#   define  i64v3div SL_i64v3div
#   define  i64v4div SL_i64v4div
#   define  i64vdivs_ SL_i64vdivs_
#   define  i64vdivs SL_i64vdivs
#   define  i64v2divs SL_i64v2divs
#   define  i64v3divs SL_i64v3divs
#   define  i64v4divs SL_i64v4divs
#   define  i64vaddS_ SL_i64vaddS_
#   define  i64vaddS SL_i64vaddS
#   define  i64v2addS SL_i64v2addS
#   define  i64v3addS SL_i64v3addS
#   define  i64v4addS SL_i64v4addS
#   define  i64vsubS_ SL_i64vsubS_
#   define  i64vsubS SL_i64vsubS
#   define  i64v2subS SL_i64v2subS
#   define  i64v3subS SL_i64v3subS
#   define  i64v4subS SL_i64v4subS
#   define  i64vaddM_ SL_i64vaddM_
#   define  i64vaddM SL_i64vaddM
#   define  i64v2addM SL_i64v2addM
#   define  i64v3addM SL_i64v3addM
#   define  i64v4addM SL_i64v4addM
#   define  i64vsubM_ SL_i64vsubM_
#   define  i64vsubM SL_i64vsubM
#   define  i64v2subM SL_i64v2subM
#   define  i64v3subM SL_i64v3subM
#   define  i64v4subM SL_i64v4subM
#   define  i64vaddSM_ SL_i64vaddSM_
#   define  i64vaddSM SL_i64vaddSM
#   define  i64v2addSM SL_i64v2addSM
#   define  i64v3addSM SL_i64v3addSM
#   define  i64v4addSM SL_i64v4addSM
#   define  i64vsubSM_ SL_i64vsubSM_
#   define  i64vsubSM SL_i64vsubSM
#   define  i64v2subSM SL_i64v2subSM
#   define  i64v3subSM SL_i64v3subSM
#   define  i64v4subSM SL_i64v4subSM
#   define  i64vSadd_ SL_i64vSadd_
#   define  i64vSadd SL_i64vSadd
#   define  i64v2Sadd SL_i64v2Sadd
#   define  i64v3Sadd SL_i64v3Sadd
#   define  i64v4Sadd SL_i64v4Sadd
#   define  i64vSsub_ SL_i64vSsub_
#   define  i64vSsub SL_i64vSsub
#   define  i64v2Ssub SL_i64v2Ssub
#   define  i64v3Ssub SL_i64v3Ssub
#   define  i64v4Ssub SL_i64v4Ssub
#   define  i64vmix_ SL_i64vmix_
#   define  i64vmix SL_i64vmix
#   define  i64v2mix SL_i64v2mix
#   define  i64v3mix SL_i64v3mix
#   define  i64v4mix SL_i64v4mix
#   define  i64vneg_ SL_i64vneg_
#   define  i64vneg SL_i64vneg
#   define  i64v2neg SL_i64v2neg
#   define  i64v3neg SL_i64v3neg
#   define  i64v4neg SL_i64v4neg
#   define  i64vabs_ SL_i64vabs_
#   define  i64vabs SL_i64vabs
#   define  i64v2abs SL_i64v2abs
#   define  i64v3abs SL_i64v3abs
#   define  i64v4abs SL_i64v4abs
#   define  i64vmin_ SL_i64vmin_
#   define  i64vmin SL_i64vmin
#   define  i64v2min SL_i64v2min
#   define  i64v3min SL_i64v3min
#   define  i64v4min SL_i64v4min
#   define  i64vmax_ SL_i64vmax_
#   define  i64vmax SL_i64vmax
#   define  i64v2max SL_i64v2max
#   define  i64v3max SL_i64v3max
#   define  i64v4max SL_i64v4max
#   define  i64vdot_ SL_i64vdot_
#   define  i64vdot SL_i64vdot
#   define  i64v2dot SL_i64v2dot
#   define  i64v3dot SL_i64v3dot
#   define  i64v4dot SL_i64v4dot
#   define  i64vlen_max_ SL_i64vlen_max_
#   define  i64vlen_max SL_i64vlen_max
#   define  i64v2len_max SL_i64v2len_max
#   define  i64v3len_max SL_i64v3len_max
#   define  i64v4len_max SL_i64v4len_max
#   define  i64vlen_manh_ SL_i64vlen_manh_
#   define  i64vlen_manh SL_i64vlen_manh
#   define  i64v2len_manh SL_i64v2len_manh
#   define  i64v3len_manh SL_i64v3len_manh
#   define  i64v4len_manh SL_i64v4len_manh
#   define  i64vlen_srq_ SL_i64vlen_srq_
#   define  i64vlen_srq SL_i64vlen_srq
#   define  i64v2len_sqr SL_i64v2len_sqr
#   define  i64v3len_sqr SL_i64v3len_sqr
#   define  i64v4len_sqr SL_i64v4len_sqr
#   define  i64vlen_ SL_i64vlen_
#   define  i64vlen SL_i64vlen
#   define  i64v2len SL_i64v2len
#   define  i64v3len SL_i64v3len
#   define  i64v4len SL_i64v4len
#   define  i64vdist_ SL_i64vdist_
#   define  i64vdist SL_i64vdist
#   define  i64v2dist SL_i64v2dist
#   define  i64v3dist SL_i64v3dist
#   define  i64v4dist SL_i64v4dist
#   define  i64v2refl SL_i64v2refl
#   define  i64v3refl SL_i64v3refl
#   define  i64v4refl SL_i64v4refl
#   define  i64v2refl_u SL_i64v2refl_u
#   define  i64v3refl_u SL_i64v3refl_u
#   define  i64v4refl_u SL_i64v4refl_u
#   define  i64v2align SL_i64v2align
#   define  i64v3align SL_i64v3align
#   define  i64v4align SL_i64v4align
#   define  i64v2align_u SL_i64v2align_u
#   define  i64v3align_u SL_i64v3align_u
#   define  i64v4align_u SL_i64v4align_u
#   define  i64v2proj SL_i64v2proj
#   define  i64v3proj SL_i64v3proj
#   define  i64v4proj SL_i64v4proj
#   define  i64v2proj_u SL_i64v2proj_u
#   define  i64v3proj_u SL_i64v3proj_u
#   define  i64v4proj_u SL_i64v4proj_u
#   define  i64vmods_ SL_i64vmods_
#   define  i64vmods SL_i64vmods
#   define  i64v2mods SL_i64v2mods
#   define  i64v3mods SL_i64v3mods
#   define  i64v4mods SL_i64v4mods
#   define  i64vmod_ SL_i64vmod_
#   define  i64vmod SL_i64vmod
#   define  i64v2mod SL_i64v2mod
#   define  i64v3mod SL_i64v3mod
#   define  i64v4mod SL_i64v4mod
#   define  i64v2cross SL_i64v2cross
#   define  i64v3cross SL_i64v3cross
#   define  i64vand_ SL_i64vand_
#   define  i64vand SL_i64vand
#   define  i64v2and SL_i64v2and
#   define  i64v3and SL_i64v3and
#   define  i64v4and SL_i64v4and
#   define  i64vor_ SL_i64vor_
#   define  i64vor SL_i64vor
#   define  i64v2or SL_i64v2or
#   define  i64v3or SL_i64v3or
#   define  i64v4or SL_i64v4or
#   define  i64vxor_ SL_i64vxor_
#   define  i64vxor SL_i64vxor
#   define  i64v2xor SL_i64v2xor
#   define  i64v3xor SL_i64v3xor
#   define  i64v4xor SL_i64v4xor
#   define  i64vnot_ SL_i64vnot_
#   define  i64vnot SL_i64vnot
#   define  i64v2not SL_i64v2not
#   define  i64v3not SL_i64v3not
#   define  i64v4not SL_i64v4not
#   define  i64vlshfts_ SL_i64vlshfts_
#   define  i64vlshfts SL_i64vlshfts
#   define  i64v2lshfts SL_i64v2lshfts
#   define  i64v3lshfts SL_i64v3lshfts
#   define  i64v4lshfts SL_i64v4lshfts
#   define  i64vlshft_ SL_i64vlshft_
#   define  i64vlshft SL_i64vlshft
#   define  i64v2lshft SL_i64v2lshft
#   define  i64v3lshft SL_i64v3lshft
#   define  i64v4lshft SL_i64v4lshft
#   define  i64vrshfts_ SL_i64vrshfts_
#   define  i64vrshfts SL_i64vrshfts
#   define  i64v2rshfts SL_i64v2rshfts
#   define  i64v3rshfts SL_i64v3rshfts
#   define  i64v4rshfts SL_i64v4rshfts
#   define  i64vrshft_ SL_i64vrshft_
#   define  i64vrshft SL_i64vrshft
#   define  i64v2rshft SL_i64v2rshft
#   define  i64v3rshft SL_i64v3rshft
#   define  i64v4rshft SL_i64v4rshft
#   define  u8v2_zero SL_u8v2_zero
#   define  u8v2_one SL_u8v2_one
#   define  u8v2_right SL_u8v2_right
#   define  u8v2_up SL_u8v2_up
#   define  u8v3_zero SL_u8v3_zero
#   define  u8v3_one SL_u8v3_one
#   define  u8v3_right SL_u8v3_right
#   define  u8v3_up SL_u8v3_up
#   define  u8v3_forw SL_u8v3_forw
#   define  u8v4_zero SL_u8v4_zero
#   define  u8v4_one SL_u8v4_one
#   define  u8v4_white SL_u8v4_white
#   define  u8v4_black SL_u8v4_black
#   define  u8v4_red SL_u8v4_red
#   define  u8v4_green SL_u8v4_green
#   define  u8v4_blue SL_u8v4_blue
#   define  u8v4_yellow SL_u8v4_yellow
#   define  u8v4_cyan SL_u8v4_cyan
#   define  u8v4_purple SL_u8v4_purple
#   define  u8v2_ SL_u8v2_
#   define  u8v3_ SL_u8v3_
#   define  u8v4_ SL_u8v4_
#   define  u8v2s SL_u8v2s
#   define  u8v3s SL_u8v3s
#   define  u8v4s SL_u8v4s
#   define  u8vv SL_u8vv
#   define  u8v2v SL_u8v2v
#   define  u8v3v SL_u8v3v
#   define  u8v4v SL_u8v4v
#   define  u8vequ_ SL_u8vequ_
#   define  u8vequ SL_u8vequ
#   define  u8v2equ SL_u8v2equ
#   define  u8v3equ SL_u8v3equ
#   define  u8v4equ SL_u8v4equ
#   define  u8vadd_ SL_u8vadd_
#   define  u8vadd SL_u8vadd
#   define  u8v2add SL_u8v2add
#   define  u8v3add SL_u8v3add
#   define  u8v4add SL_u8v4add
#   define  u8vsub_ SL_u8vsub_
#   define  u8vsub SL_u8vsub
#   define  u8v2sub SL_u8v2sub
#   define  u8v3sub SL_u8v3sub
#   define  u8v4sub SL_u8v4sub
#   define  u8vmul_ SL_u8vmul_
#   define  u8vmul SL_u8vmul
#   define  u8v2mul SL_u8v2mul
#   define  u8v3mul SL_u8v3mul
#   define  u8v4mul SL_u8v4mul
#   define  u8vmuls_ SL_u8vmuls_
#   define  u8vmuls SL_u8vmuls
#   define  u8v2muls SL_u8v2muls
#   define  u8v3muls SL_u8v3muls
#   define  u8v4muls SL_u8v4muls
#   define  u8vdiv_ SL_u8vdiv_
#   define  u8vdiv SL_u8vdiv
#   define  u8v2div SL_u8v2div
#   define  u8v3div SL_u8v3div
#   define  u8v4div SL_u8v4div
#   define  u8vdivs_ SL_u8vdivs_
#   define  u8vdivs SL_u8vdivs
#   define  u8v2divs SL_u8v2divs
#   define  u8v3divs SL_u8v3divs
#   define  u8v4divs SL_u8v4divs
#   define  u8vaddS_ SL_u8vaddS_
#   define  u8vaddS SL_u8vaddS
#   define  u8v2addS SL_u8v2addS
#   define  u8v3addS SL_u8v3addS
#   define  u8v4addS SL_u8v4addS
#   define  u8vsubS_ SL_u8vsubS_
#   define  u8vsubS SL_u8vsubS
#   define  u8v2subS SL_u8v2subS
#   define  u8v3subS SL_u8v3subS
#   define  u8v4subS SL_u8v4subS
#   define  u8vaddM_ SL_u8vaddM_
#   define  u8vaddM SL_u8vaddM
#   define  u8v2addM SL_u8v2addM
#   define  u8v3addM SL_u8v3addM
#   define  u8v4addM SL_u8v4addM
#   define  u8vsubM_ SL_u8vsubM_
#   define  u8vsubM SL_u8vsubM
#   define  u8v2subM SL_u8v2subM
#   define  u8v3subM SL_u8v3subM
#   define  u8v4subM SL_u8v4subM
#   define  u8vaddSM_ SL_u8vaddSM_
#   define  u8vaddSM SL_u8vaddSM
#   define  u8v2addSM SL_u8v2addSM
#   define  u8v3addSM SL_u8v3addSM
#   define  u8v4addSM SL_u8v4addSM
#   define  u8vsubSM_ SL_u8vsubSM_
#   define  u8vsubSM SL_u8vsubSM
#   define  u8v2subSM SL_u8v2subSM
#   define  u8v3subSM SL_u8v3subSM
#   define  u8v4subSM SL_u8v4subSM
#   define  u8vSadd_ SL_u8vSadd_
#   define  u8vSadd SL_u8vSadd
#   define  u8v2Sadd SL_u8v2Sadd
#   define  u8v3Sadd SL_u8v3Sadd
#   define  u8v4Sadd SL_u8v4Sadd
#   define  u8vSsub_ SL_u8vSsub_
#   define  u8vSsub SL_u8vSsub
#   define  u8v2Ssub SL_u8v2Ssub
#   define  u8v3Ssub SL_u8v3Ssub
#   define  u8v4Ssub SL_u8v4Ssub
#   define  u8vmix_ SL_u8vmix_
#   define  u8vmix SL_u8vmix
#   define  u8v2mix SL_u8v2mix
#   define  u8v3mix SL_u8v3mix
#   define  u8v4mix SL_u8v4mix
#   define  u8vmin_ SL_u8vmin_
#   define  u8vmin SL_u8vmin
#   define  u8v2min SL_u8v2min
#   define  u8v3min SL_u8v3min
#   define  u8v4min SL_u8v4min
#   define  u8vmax_ SL_u8vmax_
#   define  u8vmax SL_u8vmax
#   define  u8v2max SL_u8v2max
#   define  u8v3max SL_u8v3max
#   define  u8v4max SL_u8v4max
#   define  u8vdot_ SL_u8vdot_
#   define  u8vdot SL_u8vdot
#   define  u8v2dot SL_u8v2dot
#   define  u8v3dot SL_u8v3dot
#   define  u8v4dot SL_u8v4dot
#   define  u8vlen_max_ SL_u8vlen_max_
#   define  u8vlen_max SL_u8vlen_max
#   define  u8v2len_max SL_u8v2len_max
#   define  u8v3len_max SL_u8v3len_max
#   define  u8v4len_max SL_u8v4len_max
#   define  u8vlen_manh_ SL_u8vlen_manh_
#   define  u8vlen_manh SL_u8vlen_manh
#   define  u8v2len_manh SL_u8v2len_manh
#   define  u8v3len_manh SL_u8v3len_manh
#   define  u8v4len_manh SL_u8v4len_manh
#   define  u8vlen_srq_ SL_u8vlen_srq_
#   define  u8vlen_srq SL_u8vlen_srq
#   define  u8v2len_sqr SL_u8v2len_sqr
#   define  u8v3len_sqr SL_u8v3len_sqr
#   define  u8v4len_sqr SL_u8v4len_sqr
#   define  u8vlen_ SL_u8vlen_
#   define  u8vlen SL_u8vlen
#   define  u8v2len SL_u8v2len
#   define  u8v3len SL_u8v3len
#   define  u8v4len SL_u8v4len
#   define  u8vdist_ SL_u8vdist_
#   define  u8vdist SL_u8vdist
#   define  u8v2dist SL_u8v2dist
#   define  u8v3dist SL_u8v3dist
#   define  u8v4dist SL_u8v4dist
#   define  u8v2refl SL_u8v2refl
#   define  u8v3refl SL_u8v3refl
#   define  u8v4refl SL_u8v4refl
#   define  u8v2refl_u SL_u8v2refl_u
#   define  u8v3refl_u SL_u8v3refl_u
#   define  u8v4refl_u SL_u8v4refl_u
#   define  u8v2align SL_u8v2align
#   define  u8v3align SL_u8v3align
#   define  u8v4align SL_u8v4align
#   define  u8v2align_u SL_u8v2align_u
#   define  u8v3align_u SL_u8v3align_u
#   define  u8v4align_u SL_u8v4align_u
#   define  u8v2proj SL_u8v2proj
#   define  u8v3proj SL_u8v3proj
#   define  u8v4proj SL_u8v4proj
#   define  u8v2proj_u SL_u8v2proj_u
#   define  u8v3proj_u SL_u8v3proj_u
#   define  u8v4proj_u SL_u8v4proj_u
#   define  u8vmods_ SL_u8vmods_
#   define  u8vmods SL_u8vmods
#   define  u8v2mods SL_u8v2mods
#   define  u8v3mods SL_u8v3mods
#   define  u8v4mods SL_u8v4mods
#   define  u8vmod_ SL_u8vmod_
#   define  u8vmod SL_u8vmod
#   define  u8v2mod SL_u8v2mod
#   define  u8v3mod SL_u8v3mod
#   define  u8v4mod SL_u8v4mod
#   define  u8vand_ SL_u8vand_
#   define  u8vand SL_u8vand
#   define  u8v2and SL_u8v2and
#   define  u8v3and SL_u8v3and
#   define  u8v4and SL_u8v4and
#   define  u8vor_ SL_u8vor_
#   define  u8vor SL_u8vor
#   define  u8v2or SL_u8v2or
#   define  u8v3or SL_u8v3or
#   define  u8v4or SL_u8v4or
#   define  u8vxor_ SL_u8vxor_
#   define  u8vxor SL_u8vxor
#   define  u8v2xor SL_u8v2xor
#   define  u8v3xor SL_u8v3xor
#   define  u8v4xor SL_u8v4xor
#   define  u8vnot_ SL_u8vnot_
#   define  u8vnot SL_u8vnot
#   define  u8v2not SL_u8v2not
#   define  u8v3not SL_u8v3not
#   define  u8v4not SL_u8v4not
#   define  u8vlshfts_ SL_u8vlshfts_
#   define  u8vlshfts SL_u8vlshfts
#   define  u8v2lshfts SL_u8v2lshfts
#   define  u8v3lshfts SL_u8v3lshfts
#   define  u8v4lshfts SL_u8v4lshfts
#   define  u8vlshft_ SL_u8vlshft_
#   define  u8vlshft SL_u8vlshft
#   define  u8v2lshft SL_u8v2lshft
#   define  u8v3lshft SL_u8v3lshft
#   define  u8v4lshft SL_u8v4lshft
#   define  u8vrshfts_ SL_u8vrshfts_
#   define  u8vrshfts SL_u8vrshfts
#   define  u8v2rshfts SL_u8v2rshfts
#   define  u8v3rshfts SL_u8v3rshfts
#   define  u8v4rshfts SL_u8v4rshfts
#   define  u8vrshft_ SL_u8vrshft_
#   define  u8vrshft SL_u8vrshft
#   define  u8v2rshft SL_u8v2rshft
#   define  u8v3rshft SL_u8v3rshft
#   define  u8v4rshft SL_u8v4rshft
#   define  u16v2_zero SL_u16v2_zero
#   define  u16v2_one SL_u16v2_one
#   define  u16v2_right SL_u16v2_right
#   define  u16v2_up SL_u16v2_up
#   define  u16v3_zero SL_u16v3_zero
#   define  u16v3_one SL_u16v3_one
#   define  u16v3_right SL_u16v3_right
#   define  u16v3_up SL_u16v3_up
#   define  u16v3_forw SL_u16v3_forw
#   define  u16v4_zero SL_u16v4_zero
#   define  u16v4_one SL_u16v4_one
#   define  u16v4_white SL_u16v4_white
#   define  u16v4_black SL_u16v4_black
#   define  u16v4_red SL_u16v4_red
#   define  u16v4_green SL_u16v4_green
#   define  u16v4_blue SL_u16v4_blue
#   define  u16v4_yellow SL_u16v4_yellow
#   define  u16v4_cyan SL_u16v4_cyan
#   define  u16v4_purple SL_u16v4_purple
#   define  u16v2_ SL_u16v2_
#   define  u16v3_ SL_u16v3_
#   define  u16v4_ SL_u16v4_
#   define  u16v2s SL_u16v2s
#   define  u16v3s SL_u16v3s
#   define  u16v4s SL_u16v4s
#   define  u16vv SL_u16vv
#   define  u16v2v SL_u16v2v
#   define  u16v3v SL_u16v3v
#   define  u16v4v SL_u16v4v
#   define  u16vequ_ SL_u16vequ_
#   define  u16vequ SL_u16vequ
#   define  u16v2equ SL_u16v2equ
#   define  u16v3equ SL_u16v3equ
#   define  u16v4equ SL_u16v4equ
#   define  u16vadd_ SL_u16vadd_
#   define  u16vadd SL_u16vadd
#   define  u16v2add SL_u16v2add
#   define  u16v3add SL_u16v3add
#   define  u16v4add SL_u16v4add
#   define  u16vsub_ SL_u16vsub_
#   define  u16vsub SL_u16vsub
#   define  u16v2sub SL_u16v2sub
#   define  u16v3sub SL_u16v3sub
#   define  u16v4sub SL_u16v4sub
#   define  u16vmul_ SL_u16vmul_
#   define  u16vmul SL_u16vmul
#   define  u16v2mul SL_u16v2mul
#   define  u16v3mul SL_u16v3mul
#   define  u16v4mul SL_u16v4mul
#   define  u16vmuls_ SL_u16vmuls_
#   define  u16vmuls SL_u16vmuls
#   define  u16v2muls SL_u16v2muls
#   define  u16v3muls SL_u16v3muls
#   define  u16v4muls SL_u16v4muls
#   define  u16vdiv_ SL_u16vdiv_
#   define  u16vdiv SL_u16vdiv
#   define  u16v2div SL_u16v2div
#   define  u16v3div SL_u16v3div
#   define  u16v4div SL_u16v4div
#   define  u16vdivs_ SL_u16vdivs_
#   define  u16vdivs SL_u16vdivs
#   define  u16v2divs SL_u16v2divs
#   define  u16v3divs SL_u16v3divs
#   define  u16v4divs SL_u16v4divs
#   define  u16vaddS_ SL_u16vaddS_
#   define  u16vaddS SL_u16vaddS
#   define  u16v2addS SL_u16v2addS
#   define  u16v3addS SL_u16v3addS
#   define  u16v4addS SL_u16v4addS
#   define  u16vsubS_ SL_u16vsubS_
#   define  u16vsubS SL_u16vsubS
#   define  u16v2subS SL_u16v2subS
#   define  u16v3subS SL_u16v3subS
#   define  u16v4subS SL_u16v4subS
#   define  u16vaddM_ SL_u16vaddM_
#   define  u16vaddM SL_u16vaddM
#   define  u16v2addM SL_u16v2addM
#   define  u16v3addM SL_u16v3addM
#   define  u16v4addM SL_u16v4addM
#   define  u16vsubM_ SL_u16vsubM_
#   define  u16vsubM SL_u16vsubM
#   define  u16v2subM SL_u16v2subM
#   define  u16v3subM SL_u16v3subM
#   define  u16v4subM SL_u16v4subM
#   define  u16vaddSM_ SL_u16vaddSM_
#   define  u16vaddSM SL_u16vaddSM
#   define  u16v2addSM SL_u16v2addSM
#   define  u16v3addSM SL_u16v3addSM
#   define  u16v4addSM SL_u16v4addSM
#   define  u16vsubSM_ SL_u16vsubSM_
#   define  u16vsubSM SL_u16vsubSM
#   define  u16v2subSM SL_u16v2subSM
#   define  u16v3subSM SL_u16v3subSM
#   define  u16v4subSM SL_u16v4subSM
#   define  u16vSadd_ SL_u16vSadd_
#   define  u16vSadd SL_u16vSadd
#   define  u16v2Sadd SL_u16v2Sadd
#   define  u16v3Sadd SL_u16v3Sadd
#   define  u16v4Sadd SL_u16v4Sadd
#   define  u16vSsub_ SL_u16vSsub_
#   define  u16vSsub SL_u16vSsub
#   define  u16v2Ssub SL_u16v2Ssub
#   define  u16v3Ssub SL_u16v3Ssub
#   define  u16v4Ssub SL_u16v4Ssub
#   define  u16vmix_ SL_u16vmix_
#   define  u16vmix SL_u16vmix
#   define  u16v2mix SL_u16v2mix
#   define  u16v3mix SL_u16v3mix
#   define  u16v4mix SL_u16v4mix
#   define  u16vmin_ SL_u16vmin_
#   define  u16vmin SL_u16vmin
#   define  u16v2min SL_u16v2min
#   define  u16v3min SL_u16v3min
#   define  u16v4min SL_u16v4min
#   define  u16vmax_ SL_u16vmax_
#   define  u16vmax SL_u16vmax
#   define  u16v2max SL_u16v2max
#   define  u16v3max SL_u16v3max
#   define  u16v4max SL_u16v4max
#   define  u16vdot_ SL_u16vdot_
#   define  u16vdot SL_u16vdot
#   define  u16v2dot SL_u16v2dot
#   define  u16v3dot SL_u16v3dot
#   define  u16v4dot SL_u16v4dot
#   define  u16vlen_max_ SL_u16vlen_max_
#   define  u16vlen_max SL_u16vlen_max
#   define  u16v2len_max SL_u16v2len_max
#   define  u16v3len_max SL_u16v3len_max
#   define  u16v4len_max SL_u16v4len_max
#   define  u16vlen_manh_ SL_u16vlen_manh_
#   define  u16vlen_manh SL_u16vlen_manh
#   define  u16v2len_manh SL_u16v2len_manh
#   define  u16v3len_manh SL_u16v3len_manh
#   define  u16v4len_manh SL_u16v4len_manh
#   define  u16vlen_srq_ SL_u16vlen_srq_
#   define  u16vlen_srq SL_u16vlen_srq
#   define  u16v2len_sqr SL_u16v2len_sqr
#   define  u16v3len_sqr SL_u16v3len_sqr
#   define  u16v4len_sqr SL_u16v4len_sqr
#   define  u16vlen_ SL_u16vlen_
#   define  u16vlen SL_u16vlen
#   define  u16v2len SL_u16v2len
#   define  u16v3len SL_u16v3len
#   define  u16v4len SL_u16v4len
#   define  u16vdist_ SL_u16vdist_
#   define  u16vdist SL_u16vdist
#   define  u16v2dist SL_u16v2dist
#   define  u16v3dist SL_u16v3dist
#   define  u16v4dist SL_u16v4dist
#   define  u16v2refl SL_u16v2refl
#   define  u16v3refl SL_u16v3refl
#   define  u16v4refl SL_u16v4refl
#   define  u16v2refl_u SL_u16v2refl_u
#   define  u16v3refl_u SL_u16v3refl_u
#   define  u16v4refl_u SL_u16v4refl_u
#   define  u16v2align SL_u16v2align
#   define  u16v3align SL_u16v3align
#   define  u16v4align SL_u16v4align
#   define  u16v2align_u SL_u16v2align_u
#   define  u16v3align_u SL_u16v3align_u
#   define  u16v4align_u SL_u16v4align_u
#   define  u16v2proj SL_u16v2proj
#   define  u16v3proj SL_u16v3proj
#   define  u16v4proj SL_u16v4proj
#   define  u16v2proj_u SL_u16v2proj_u
#   define  u16v3proj_u SL_u16v3proj_u
#   define  u16v4proj_u SL_u16v4proj_u
#   define  u16vmods_ SL_u16vmods_
#   define  u16vmods SL_u16vmods
#   define  u16v2mods SL_u16v2mods
#   define  u16v3mods SL_u16v3mods
#   define  u16v4mods SL_u16v4mods
#   define  u16vmod_ SL_u16vmod_
#   define  u16vmod SL_u16vmod
#   define  u16v2mod SL_u16v2mod
#   define  u16v3mod SL_u16v3mod
#   define  u16v4mod SL_u16v4mod
#   define  u16vand_ SL_u16vand_
#   define  u16vand SL_u16vand
#   define  u16v2and SL_u16v2and
#   define  u16v3and SL_u16v3and
#   define  u16v4and SL_u16v4and
#   define  u16vor_ SL_u16vor_
#   define  u16vor SL_u16vor
#   define  u16v2or SL_u16v2or
#   define  u16v3or SL_u16v3or
#   define  u16v4or SL_u16v4or
#   define  u16vxor_ SL_u16vxor_
#   define  u16vxor SL_u16vxor
#   define  u16v2xor SL_u16v2xor
#   define  u16v3xor SL_u16v3xor
#   define  u16v4xor SL_u16v4xor
#   define  u16vnot_ SL_u16vnot_
#   define  u16vnot SL_u16vnot
#   define  u16v2not SL_u16v2not
#   define  u16v3not SL_u16v3not
#   define  u16v4not SL_u16v4not
#   define  u16vlshfts_ SL_u16vlshfts_
#   define  u16vlshfts SL_u16vlshfts
#   define  u16v2lshfts SL_u16v2lshfts
#   define  u16v3lshfts SL_u16v3lshfts
#   define  u16v4lshfts SL_u16v4lshfts
#   define  u16vlshft_ SL_u16vlshft_
#   define  u16vlshft SL_u16vlshft
#   define  u16v2lshft SL_u16v2lshft
#   define  u16v3lshft SL_u16v3lshft
#   define  u16v4lshft SL_u16v4lshft
#   define  u16vrshfts_ SL_u16vrshfts_
#   define  u16vrshfts SL_u16vrshfts
#   define  u16v2rshfts SL_u16v2rshfts
#   define  u16v3rshfts SL_u16v3rshfts
#   define  u16v4rshfts SL_u16v4rshfts
#   define  u16vrshft_ SL_u16vrshft_
#   define  u16vrshft SL_u16vrshft
#   define  u16v2rshft SL_u16v2rshft
#   define  u16v3rshft SL_u16v3rshft
#   define  u16v4rshft SL_u16v4rshft
#   define  u32v2_zero SL_u32v2_zero
#   define  u32v2_one SL_u32v2_one
#   define  u32v2_right SL_u32v2_right
#   define  u32v2_up SL_u32v2_up
#   define  u32v3_zero SL_u32v3_zero
#   define  u32v3_one SL_u32v3_one
#   define  u32v3_right SL_u32v3_right
#   define  u32v3_up SL_u32v3_up
#   define  u32v3_forw SL_u32v3_forw
#   define  u32v4_zero SL_u32v4_zero
#   define  u32v4_one SL_u32v4_one
#   define  u32v4_white SL_u32v4_white
#   define  u32v4_black SL_u32v4_black
#   define  u32v4_red SL_u32v4_red
#   define  u32v4_green SL_u32v4_green
#   define  u32v4_blue SL_u32v4_blue
#   define  u32v4_yellow SL_u32v4_yellow
#   define  u32v4_cyan SL_u32v4_cyan
#   define  u32v4_purple SL_u32v4_purple
#   define  u32v2_ SL_u32v2_
#   define  u32v3_ SL_u32v3_
#   define  u32v4_ SL_u32v4_
#   define  u32v2s SL_u32v2s
#   define  u32v3s SL_u32v3s
#   define  u32v4s SL_u32v4s
#   define  u32vv SL_u32vv
#   define  u32v2v SL_u32v2v
#   define  u32v3v SL_u32v3v
#   define  u32v4v SL_u32v4v
#   define  u32vequ_ SL_u32vequ_
#   define  u32vequ SL_u32vequ
#   define  u32v2equ SL_u32v2equ
#   define  u32v3equ SL_u32v3equ
#   define  u32v4equ SL_u32v4equ
#   define  u32vadd_ SL_u32vadd_
#   define  u32vadd SL_u32vadd
#   define  u32v2add SL_u32v2add
#   define  u32v3add SL_u32v3add
#   define  u32v4add SL_u32v4add
#   define  u32vsub_ SL_u32vsub_
#   define  u32vsub SL_u32vsub
#   define  u32v2sub SL_u32v2sub
#   define  u32v3sub SL_u32v3sub
#   define  u32v4sub SL_u32v4sub
#   define  u32vmul_ SL_u32vmul_
#   define  u32vmul SL_u32vmul
#   define  u32v2mul SL_u32v2mul
#   define  u32v3mul SL_u32v3mul
#   define  u32v4mul SL_u32v4mul
#   define  u32vmuls_ SL_u32vmuls_
#   define  u32vmuls SL_u32vmuls
#   define  u32v2muls SL_u32v2muls
#   define  u32v3muls SL_u32v3muls
#   define  u32v4muls SL_u32v4muls
#   define  u32vdiv_ SL_u32vdiv_
#   define  u32vdiv SL_u32vdiv
#   define  u32v2div SL_u32v2div
#   define  u32v3div SL_u32v3div
#   define  u32v4div SL_u32v4div
#   define  u32vdivs_ SL_u32vdivs_
#   define  u32vdivs SL_u32vdivs
#   define  u32v2divs SL_u32v2divs
#   define  u32v3divs SL_u32v3divs
#   define  u32v4divs SL_u32v4divs
#   define  u32vaddS_ SL_u32vaddS_
#   define  u32vaddS SL_u32vaddS
#   define  u32v2addS SL_u32v2addS
#   define  u32v3addS SL_u32v3addS
#   define  u32v4addS SL_u32v4addS
#   define  u32vsubS_ SL_u32vsubS_
#   define  u32vsubS SL_u32vsubS
#   define  u32v2subS SL_u32v2subS
#   define  u32v3subS SL_u32v3subS
#   define  u32v4subS SL_u32v4subS
#   define  u32vaddM_ SL_u32vaddM_
#   define  u32vaddM SL_u32vaddM
#   define  u32v2addM SL_u32v2addM
#   define  u32v3addM SL_u32v3addM
#   define  u32v4addM SL_u32v4addM
#   define  u32vsubM_ SL_u32vsubM_
#   define  u32vsubM SL_u32vsubM
#   define  u32v2subM SL_u32v2subM
#   define  u32v3subM SL_u32v3subM
#   define  u32v4subM SL_u32v4subM
#   define  u32vaddSM_ SL_u32vaddSM_
#   define  u32vaddSM SL_u32vaddSM
#   define  u32v2addSM SL_u32v2addSM
#   define  u32v3addSM SL_u32v3addSM
#   define  u32v4addSM SL_u32v4addSM
#   define  u32vsubSM_ SL_u32vsubSM_
#   define  u32vsubSM SL_u32vsubSM
#   define  u32v2subSM SL_u32v2subSM
#   define  u32v3subSM SL_u32v3subSM
#   define  u32v4subSM SL_u32v4subSM
#   define  u32vSadd_ SL_u32vSadd_
#   define  u32vSadd SL_u32vSadd
#   define  u32v2Sadd SL_u32v2Sadd
#   define  u32v3Sadd SL_u32v3Sadd
#   define  u32v4Sadd SL_u32v4Sadd
#   define  u32vSsub_ SL_u32vSsub_
#   define  u32vSsub SL_u32vSsub
#   define  u32v2Ssub SL_u32v2Ssub
#   define  u32v3Ssub SL_u32v3Ssub
#   define  u32v4Ssub SL_u32v4Ssub
#   define  u32vmix_ SL_u32vmix_
#   define  u32vmix SL_u32vmix
#   define  u32v2mix SL_u32v2mix
#   define  u32v3mix SL_u32v3mix
#   define  u32v4mix SL_u32v4mix
#   define  u32vmin_ SL_u32vmin_
#   define  u32vmin SL_u32vmin
#   define  u32v2min SL_u32v2min
#   define  u32v3min SL_u32v3min
#   define  u32v4min SL_u32v4min
#   define  u32vmax_ SL_u32vmax_
#   define  u32vmax SL_u32vmax
#   define  u32v2max SL_u32v2max
#   define  u32v3max SL_u32v3max
#   define  u32v4max SL_u32v4max
#   define  u32vdot_ SL_u32vdot_
#   define  u32vdot SL_u32vdot
#   define  u32v2dot SL_u32v2dot
#   define  u32v3dot SL_u32v3dot
#   define  u32v4dot SL_u32v4dot
#   define  u32vlen_max_ SL_u32vlen_max_
#   define  u32vlen_max SL_u32vlen_max
#   define  u32v2len_max SL_u32v2len_max
#   define  u32v3len_max SL_u32v3len_max
#   define  u32v4len_max SL_u32v4len_max
#   define  u32vlen_manh_ SL_u32vlen_manh_
#   define  u32vlen_manh SL_u32vlen_manh
#   define  u32v2len_manh SL_u32v2len_manh
#   define  u32v3len_manh SL_u32v3len_manh
#   define  u32v4len_manh SL_u32v4len_manh
#   define  u32vlen_srq_ SL_u32vlen_srq_
#   define  u32vlen_srq SL_u32vlen_srq
#   define  u32v2len_sqr SL_u32v2len_sqr
#   define  u32v3len_sqr SL_u32v3len_sqr
#   define  u32v4len_sqr SL_u32v4len_sqr
#   define  u32vlen_ SL_u32vlen_
#   define  u32vlen SL_u32vlen
#   define  u32v2len SL_u32v2len
#   define  u32v3len SL_u32v3len
#   define  u32v4len SL_u32v4len
#   define  u32vdist_ SL_u32vdist_
#   define  u32vdist SL_u32vdist
#   define  u32v2dist SL_u32v2dist
#   define  u32v3dist SL_u32v3dist
#   define  u32v4dist SL_u32v4dist
#   define  u32v2refl SL_u32v2refl
#   define  u32v3refl SL_u32v3refl
#   define  u32v4refl SL_u32v4refl
#   define  u32v2refl_u SL_u32v2refl_u
#   define  u32v3refl_u SL_u32v3refl_u
#   define  u32v4refl_u SL_u32v4refl_u
#   define  u32v2align SL_u32v2align
#   define  u32v3align SL_u32v3align
#   define  u32v4align SL_u32v4align
#   define  u32v2align_u SL_u32v2align_u
#   define  u32v3align_u SL_u32v3align_u
#   define  u32v4align_u SL_u32v4align_u
#   define  u32v2proj SL_u32v2proj
#   define  u32v3proj SL_u32v3proj
#   define  u32v4proj SL_u32v4proj
#   define  u32v2proj_u SL_u32v2proj_u
#   define  u32v3proj_u SL_u32v3proj_u
#   define  u32v4proj_u SL_u32v4proj_u
#   define  u32vmods_ SL_u32vmods_
#   define  u32vmods SL_u32vmods
#   define  u32v2mods SL_u32v2mods
#   define  u32v3mods SL_u32v3mods
#   define  u32v4mods SL_u32v4mods
#   define  u32vmod_ SL_u32vmod_
#   define  u32vmod SL_u32vmod
#   define  u32v2mod SL_u32v2mod
#   define  u32v3mod SL_u32v3mod
#   define  u32v4mod SL_u32v4mod
#   define  u32vand_ SL_u32vand_
#   define  u32vand SL_u32vand
#   define  u32v2and SL_u32v2and
#   define  u32v3and SL_u32v3and
#   define  u32v4and SL_u32v4and
#   define  u32vor_ SL_u32vor_
#   define  u32vor SL_u32vor
#   define  u32v2or SL_u32v2or
#   define  u32v3or SL_u32v3or
#   define  u32v4or SL_u32v4or
#   define  u32vxor_ SL_u32vxor_
#   define  u32vxor SL_u32vxor
#   define  u32v2xor SL_u32v2xor
#   define  u32v3xor SL_u32v3xor
#   define  u32v4xor SL_u32v4xor
#   define  u32vnot_ SL_u32vnot_
#   define  u32vnot SL_u32vnot
#   define  u32v2not SL_u32v2not
#   define  u32v3not SL_u32v3not
#   define  u32v4not SL_u32v4not
#   define  u32vlshfts_ SL_u32vlshfts_
#   define  u32vlshfts SL_u32vlshfts
#   define  u32v2lshfts SL_u32v2lshfts
#   define  u32v3lshfts SL_u32v3lshfts
#   define  u32v4lshfts SL_u32v4lshfts
#   define  u32vlshft_ SL_u32vlshft_
#   define  u32vlshft SL_u32vlshft
#   define  u32v2lshft SL_u32v2lshft
#   define  u32v3lshft SL_u32v3lshft
#   define  u32v4lshft SL_u32v4lshft
#   define  u32vrshfts_ SL_u32vrshfts_
#   define  u32vrshfts SL_u32vrshfts
#   define  u32v2rshfts SL_u32v2rshfts
#   define  u32v3rshfts SL_u32v3rshfts
#   define  u32v4rshfts SL_u32v4rshfts
#   define  u32vrshft_ SL_u32vrshft_
#   define  u32vrshft SL_u32vrshft
#   define  u32v2rshft SL_u32v2rshft
#   define  u32v3rshft SL_u32v3rshft
#   define  u32v4rshft SL_u32v4rshft
#   define  u64v2_zero SL_u64v2_zero
#   define  u64v2_one SL_u64v2_one
#   define  u64v2_right SL_u64v2_right
#   define  u64v2_up SL_u64v2_up
#   define  u64v3_zero SL_u64v3_zero
#   define  u64v3_one SL_u64v3_one
#   define  u64v3_right SL_u64v3_right
#   define  u64v3_up SL_u64v3_up
#   define  u64v3_forw SL_u64v3_forw
#   define  u64v4_zero SL_u64v4_zero
#   define  u64v4_one SL_u64v4_one
#   define  u64v4_white SL_u64v4_white
#   define  u64v4_black SL_u64v4_black
#   define  u64v4_red SL_u64v4_red
#   define  u64v4_green SL_u64v4_green
#   define  u64v4_blue SL_u64v4_blue
#   define  u64v4_yellow SL_u64v4_yellow
#   define  u64v4_cyan SL_u64v4_cyan
#   define  u64v4_purple SL_u64v4_purple
#   define  u64v2_ SL_u64v2_
#   define  u64v3_ SL_u64v3_
#   define  u64v4_ SL_u64v4_
#   define  u64v2s SL_u64v2s
#   define  u64v3s SL_u64v3s
#   define  u64v4s SL_u64v4s
#   define  u64vv SL_u64vv
#   define  u64v2v SL_u64v2v
#   define  u64v3v SL_u64v3v
#   define  u64v4v SL_u64v4v
#   define  u64vequ_ SL_u64vequ_
#   define  u64vequ SL_u64vequ
#   define  u64v2equ SL_u64v2equ
#   define  u64v3equ SL_u64v3equ
#   define  u64v4equ SL_u64v4equ
#   define  u64vadd_ SL_u64vadd_
#   define  u64vadd SL_u64vadd
#   define  u64v2add SL_u64v2add
#   define  u64v3add SL_u64v3add
#   define  u64v4add SL_u64v4add
#   define  u64vsub_ SL_u64vsub_
#   define  u64vsub SL_u64vsub
#   define  u64v2sub SL_u64v2sub
#   define  u64v3sub SL_u64v3sub
#   define  u64v4sub SL_u64v4sub
#   define  u64vmul_ SL_u64vmul_
#   define  u64vmul SL_u64vmul
#   define  u64v2mul SL_u64v2mul
#   define  u64v3mul SL_u64v3mul
#   define  u64v4mul SL_u64v4mul
#   define  u64vmuls_ SL_u64vmuls_
#   define  u64vmuls SL_u64vmuls
#   define  u64v2muls SL_u64v2muls
#   define  u64v3muls SL_u64v3muls
#   define  u64v4muls SL_u64v4muls
#   define  u64vdiv_ SL_u64vdiv_
#   define  u64vdiv SL_u64vdiv
#   define  u64v2div SL_u64v2div
#   define  u64v3div SL_u64v3div
#   define  u64v4div SL_u64v4div
#   define  u64vdivs_ SL_u64vdivs_
#   define  u64vdivs SL_u64vdivs
#   define  u64v2divs SL_u64v2divs
#   define  u64v3divs SL_u64v3divs
#   define  u64v4divs SL_u64v4divs
#   define  u64vaddS_ SL_u64vaddS_
#   define  u64vaddS SL_u64vaddS
#   define  u64v2addS SL_u64v2addS
#   define  u64v3addS SL_u64v3addS
#   define  u64v4addS SL_u64v4addS
#   define  u64vsubS_ SL_u64vsubS_
#   define  u64vsubS SL_u64vsubS
#   define  u64v2subS SL_u64v2subS
#   define  u64v3subS SL_u64v3subS
#   define  u64v4subS SL_u64v4subS
#   define  u64vaddM_ SL_u64vaddM_
#   define  u64vaddM SL_u64vaddM
#   define  u64v2addM SL_u64v2addM
#   define  u64v3addM SL_u64v3addM
#   define  u64v4addM SL_u64v4addM
#   define  u64vsubM_ SL_u64vsubM_
#   define  u64vsubM SL_u64vsubM
#   define  u64v2subM SL_u64v2subM
#   define  u64v3subM SL_u64v3subM
#   define  u64v4subM SL_u64v4subM
#   define  u64vaddSM_ SL_u64vaddSM_
#   define  u64vaddSM SL_u64vaddSM
#   define  u64v2addSM SL_u64v2addSM
#   define  u64v3addSM SL_u64v3addSM
#   define  u64v4addSM SL_u64v4addSM
#   define  u64vsubSM_ SL_u64vsubSM_
#   define  u64vsubSM SL_u64vsubSM
#   define  u64v2subSM SL_u64v2subSM
#   define  u64v3subSM SL_u64v3subSM
#   define  u64v4subSM SL_u64v4subSM
#   define  u64vSadd_ SL_u64vSadd_
#   define  u64vSadd SL_u64vSadd
#   define  u64v2Sadd SL_u64v2Sadd
#   define  u64v3Sadd SL_u64v3Sadd
#   define  u64v4Sadd SL_u64v4Sadd
#   define  u64vSsub_ SL_u64vSsub_
#   define  u64vSsub SL_u64vSsub
#   define  u64v2Ssub SL_u64v2Ssub
#   define  u64v3Ssub SL_u64v3Ssub
#   define  u64v4Ssub SL_u64v4Ssub
#   define  u64vmix_ SL_u64vmix_
#   define  u64vmix SL_u64vmix
#   define  u64v2mix SL_u64v2mix
#   define  u64v3mix SL_u64v3mix
#   define  u64v4mix SL_u64v4mix
#   define  u64vmin_ SL_u64vmin_
#   define  u64vmin SL_u64vmin
#   define  u64v2min SL_u64v2min
#   define  u64v3min SL_u64v3min
#   define  u64v4min SL_u64v4min
#   define  u64vmax_ SL_u64vmax_
#   define  u64vmax SL_u64vmax
#   define  u64v2max SL_u64v2max
#   define  u64v3max SL_u64v3max
#   define  u64v4max SL_u64v4max
#   define  u64vdot_ SL_u64vdot_
#   define  u64vdot SL_u64vdot
#   define  u64v2dot SL_u64v2dot
#   define  u64v3dot SL_u64v3dot
#   define  u64v4dot SL_u64v4dot
#   define  u64vlen_max_ SL_u64vlen_max_
#   define  u64vlen_max SL_u64vlen_max
#   define  u64v2len_max SL_u64v2len_max
#   define  u64v3len_max SL_u64v3len_max
#   define  u64v4len_max SL_u64v4len_max
#   define  u64vlen_manh_ SL_u64vlen_manh_
#   define  u64vlen_manh SL_u64vlen_manh
#   define  u64v2len_manh SL_u64v2len_manh
#   define  u64v3len_manh SL_u64v3len_manh
#   define  u64v4len_manh SL_u64v4len_manh
#   define  u64vlen_srq_ SL_u64vlen_srq_
#   define  u64vlen_srq SL_u64vlen_srq
#   define  u64v2len_sqr SL_u64v2len_sqr
#   define  u64v3len_sqr SL_u64v3len_sqr
#   define  u64v4len_sqr SL_u64v4len_sqr
#   define  u64vlen_ SL_u64vlen_
#   define  u64vlen SL_u64vlen
#   define  u64v2len SL_u64v2len
#   define  u64v3len SL_u64v3len
#   define  u64v4len SL_u64v4len
#   define  u64vdist_ SL_u64vdist_
#   define  u64vdist SL_u64vdist
#   define  u64v2dist SL_u64v2dist
#   define  u64v3dist SL_u64v3dist
#   define  u64v4dist SL_u64v4dist
#   define  u64v2refl SL_u64v2refl
#   define  u64v3refl SL_u64v3refl
#   define  u64v4refl SL_u64v4refl
#   define  u64v2refl_u SL_u64v2refl_u
#   define  u64v3refl_u SL_u64v3refl_u
#   define  u64v4refl_u SL_u64v4refl_u
#   define  u64v2align SL_u64v2align
#   define  u64v3align SL_u64v3align
#   define  u64v4align SL_u64v4align
#   define  u64v2align_u SL_u64v2align_u
#   define  u64v3align_u SL_u64v3align_u
#   define  u64v4align_u SL_u64v4align_u
#   define  u64v2proj SL_u64v2proj
#   define  u64v3proj SL_u64v3proj
#   define  u64v4proj SL_u64v4proj
#   define  u64v2proj_u SL_u64v2proj_u
#   define  u64v3proj_u SL_u64v3proj_u
#   define  u64v4proj_u SL_u64v4proj_u
#   define  u64vmods_ SL_u64vmods_
#   define  u64vmods SL_u64vmods
#   define  u64v2mods SL_u64v2mods
#   define  u64v3mods SL_u64v3mods
#   define  u64v4mods SL_u64v4mods
#   define  u64vmod_ SL_u64vmod_
#   define  u64vmod SL_u64vmod
#   define  u64v2mod SL_u64v2mod
#   define  u64v3mod SL_u64v3mod
#   define  u64v4mod SL_u64v4mod
#   define  u64vand_ SL_u64vand_
#   define  u64vand SL_u64vand
#   define  u64v2and SL_u64v2and
#   define  u64v3and SL_u64v3and
#   define  u64v4and SL_u64v4and
#   define  u64vor_ SL_u64vor_
#   define  u64vor SL_u64vor
#   define  u64v2or SL_u64v2or
#   define  u64v3or SL_u64v3or
#   define  u64v4or SL_u64v4or
#   define  u64vxor_ SL_u64vxor_
#   define  u64vxor SL_u64vxor
#   define  u64v2xor SL_u64v2xor
#   define  u64v3xor SL_u64v3xor
#   define  u64v4xor SL_u64v4xor
#   define  u64vnot_ SL_u64vnot_
#   define  u64vnot SL_u64vnot
#   define  u64v2not SL_u64v2not
#   define  u64v3not SL_u64v3not
#   define  u64v4not SL_u64v4not
#   define  u64vlshfts_ SL_u64vlshfts_
#   define  u64vlshfts SL_u64vlshfts
#   define  u64v2lshfts SL_u64v2lshfts
#   define  u64v3lshfts SL_u64v3lshfts
#   define  u64v4lshfts SL_u64v4lshfts
#   define  u64vlshft_ SL_u64vlshft_
#   define  u64vlshft SL_u64vlshft
#   define  u64v2lshft SL_u64v2lshft
#   define  u64v3lshft SL_u64v3lshft
#   define  u64v4lshft SL_u64v4lshft
#   define  u64vrshfts_ SL_u64vrshfts_
#   define  u64vrshfts SL_u64vrshfts
#   define  u64v2rshfts SL_u64v2rshfts
#   define  u64v3rshfts SL_u64v3rshfts
#   define  u64v4rshfts SL_u64v4rshfts
#   define  u64vrshft_ SL_u64vrshft_
#   define  u64vrshft SL_u64vrshft
#   define  u64v2rshft SL_u64v2rshft
#   define  u64v3rshft SL_u64v3rshft
#   define  u64v4rshft SL_u64v4rshft
#   define  fv2_zero SL_fv2_zero
#   define  fv2_one SL_fv2_one
#   define  fv2_right SL_fv2_right
#   define  fv2_up SL_fv2_up
#   define  fv2_left SL_fv2_left
#   define  fv2_down SL_fv2_down
#   define  fv3_zero SL_fv3_zero
#   define  fv3_one SL_fv3_one
#   define  fv3_right SL_fv3_right
#   define  fv3_up SL_fv3_up
#   define  fv3_forw SL_fv3_forw
#   define  fv3_left SL_fv3_left
#   define  fv3_down SL_fv3_down
#   define  fv3_back SL_fv3_back
#   define  fv4_zero SL_fv4_zero
#   define  fv4_one SL_fv4_one
#   define  fv4_white SL_fv4_white
#   define  fv4_black SL_fv4_black
#   define  fv4_red SL_fv4_red
#   define  fv4_green SL_fv4_green
#   define  fv4_blue SL_fv4_blue
#   define  fv4_yellow SL_fv4_yellow
#   define  fv4_cyan SL_fv4_cyan
#   define  fv4_purple SL_fv4_purple
#   define  fv2_ SL_fv2_
#   define  fv3_ SL_fv3_
#   define  fv4_ SL_fv4_
#   define  fv2s SL_fv2s
#   define  fv3s SL_fv3s
#   define  fv4s SL_fv4s
#   define  fvv SL_fvv
#   define  fv2v SL_fv2v
#   define  fv3v SL_fv3v
#   define  fv4v SL_fv4v
#   define  fvequ_ SL_fvequ_
#   define  fvequ SL_fvequ
#   define  fv2equ SL_fv2equ
#   define  fv3equ SL_fv3equ
#   define  fv4equ SL_fv4equ
#   define  fvadd_ SL_fvadd_
#   define  fvadd SL_fvadd
#   define  fv2add SL_fv2add
#   define  fv3add SL_fv3add
#   define  fv4add SL_fv4add
#   define  fvsub_ SL_fvsub_
#   define  fvsub SL_fvsub
#   define  fv2sub SL_fv2sub
#   define  fv3sub SL_fv3sub
#   define  fv4sub SL_fv4sub
#   define  fvmul_ SL_fvmul_
#   define  fvmul SL_fvmul
#   define  fv2mul SL_fv2mul
#   define  fv3mul SL_fv3mul
#   define  fv4mul SL_fv4mul
#   define  fvmuls_ SL_fvmuls_
#   define  fvmuls SL_fvmuls
#   define  fv2muls SL_fv2muls
#   define  fv3muls SL_fv3muls
#   define  fv4muls SL_fv4muls
#   define  fvdiv_ SL_fvdiv_
#   define  fvdiv SL_fvdiv
#   define  fv2div SL_fv2div
#   define  fv3div SL_fv3div
#   define  fv4div SL_fv4div
#   define  fvdivs_ SL_fvdivs_
#   define  fvdivs SL_fvdivs
#   define  fv2divs SL_fv2divs
#   define  fv3divs SL_fv3divs
#   define  fv4divs SL_fv4divs
#   define  fvaddS_ SL_fvaddS_
#   define  fvaddS SL_fvaddS
#   define  fv2addS SL_fv2addS
#   define  fv3addS SL_fv3addS
#   define  fv4addS SL_fv4addS
#   define  fvsubS_ SL_fvsubS_
#   define  fvsubS SL_fvsubS
#   define  fv2subS SL_fv2subS
#   define  fv3subS SL_fv3subS
#   define  fv4subS SL_fv4subS
#   define  fvaddM_ SL_fvaddM_
#   define  fvaddM SL_fvaddM
#   define  fv2addM SL_fv2addM
#   define  fv3addM SL_fv3addM
#   define  fv4addM SL_fv4addM
#   define  fvsubM_ SL_fvsubM_
#   define  fvsubM SL_fvsubM
#   define  fv2subM SL_fv2subM
#   define  fv3subM SL_fv3subM
#   define  fv4subM SL_fv4subM
#   define  fvaddSM_ SL_fvaddSM_
#   define  fvaddSM SL_fvaddSM
#   define  fv2addSM SL_fv2addSM
#   define  fv3addSM SL_fv3addSM
#   define  fv4addSM SL_fv4addSM
#   define  fvsubSM_ SL_fvsubSM_
#   define  fvsubSM SL_fvsubSM
#   define  fv2subSM SL_fv2subSM
#   define  fv3subSM SL_fv3subSM
#   define  fv4subSM SL_fv4subSM
#   define  fvSadd_ SL_fvSadd_
#   define  fvSadd SL_fvSadd
#   define  fv2Sadd SL_fv2Sadd
#   define  fv3Sadd SL_fv3Sadd
#   define  fv4Sadd SL_fv4Sadd
#   define  fvSsub_ SL_fvSsub_
#   define  fvSsub SL_fvSsub
#   define  fv2Ssub SL_fv2Ssub
#   define  fv3Ssub SL_fv3Ssub
#   define  fv4Ssub SL_fv4Ssub
#   define  fvmix_ SL_fvmix_
#   define  fvmix SL_fvmix
#   define  fv2mix SL_fv2mix
#   define  fv3mix SL_fv3mix
#   define  fv4mix SL_fv4mix
#   define  fvneg_ SL_fvneg_
#   define  fvneg SL_fvneg
#   define  fv2neg SL_fv2neg
#   define  fv3neg SL_fv3neg
#   define  fv4neg SL_fv4neg
#   define  fvabs_ SL_fvabs_
#   define  fvabs SL_fvabs
#   define  fv2abs SL_fv2abs
#   define  fv3abs SL_fv3abs
#   define  fv4abs SL_fv4abs
#   define  fvmin_ SL_fvmin_
#   define  fvmin SL_fvmin
#   define  fv2min SL_fv2min
#   define  fv3min SL_fv3min
#   define  fv4min SL_fv4min
#   define  fvmax_ SL_fvmax_
#   define  fvmax SL_fvmax
#   define  fv2max SL_fv2max
#   define  fv3max SL_fv3max
#   define  fv4max SL_fv4max
#   define  fvdot_ SL_fvdot_
#   define  fvdot SL_fvdot
#   define  fv2dot SL_fv2dot
#   define  fv3dot SL_fv3dot
#   define  fv4dot SL_fv4dot
#   define  fvlen_max_ SL_fvlen_max_
#   define  fvlen_max SL_fvlen_max
#   define  fv2len_max SL_fv2len_max
#   define  fv3len_max SL_fv3len_max
#   define  fv4len_max SL_fv4len_max
#   define  fvlen_manh_ SL_fvlen_manh_
#   define  fvlen_manh SL_fvlen_manh
#   define  fv2len_manh SL_fv2len_manh
#   define  fv3len_manh SL_fv3len_manh
#   define  fv4len_manh SL_fv4len_manh
#   define  fvlen_srq_ SL_fvlen_srq_
#   define  fvlen_srq SL_fvlen_srq
#   define  fv2len_sqr SL_fv2len_sqr
#   define  fv3len_sqr SL_fv3len_sqr
#   define  fv4len_sqr SL_fv4len_sqr
#   define  fvlen_ SL_fvlen_
#   define  fvlen SL_fvlen
#   define  fv2len SL_fv2len
#   define  fv3len SL_fv3len
#   define  fv4len SL_fv4len
#   define  fvdist_ SL_fvdist_
#   define  fvdist SL_fvdist
#   define  fv2dist SL_fv2dist
#   define  fv3dist SL_fv3dist
#   define  fv4dist SL_fv4dist
#   define  fv2refl SL_fv2refl
#   define  fv3refl SL_fv3refl
#   define  fv4refl SL_fv4refl
#   define  fv2refl_u SL_fv2refl_u
#   define  fv3refl_u SL_fv3refl_u
#   define  fv4refl_u SL_fv4refl_u
#   define  fv2align SL_fv2align
#   define  fv3align SL_fv3align
#   define  fv4align SL_fv4align
#   define  fv2align_u SL_fv2align_u
#   define  fv3align_u SL_fv3align_u
#   define  fv4align_u SL_fv4align_u
#   define  fv2proj SL_fv2proj
#   define  fv3proj SL_fv3proj
#   define  fv4proj SL_fv4proj
#   define  fv2proj_u SL_fv2proj_u
#   define  fv3proj_u SL_fv3proj_u
#   define  fv4proj_u SL_fv4proj_u
#   define  fvmods_ SL_fvmods_
#   define  fvmods SL_fvmods
#   define  fv2mods SL_fv2mods
#   define  fv3mods SL_fv3mods
#   define  fv4mods SL_fv4mods
#   define  fvmod_ SL_fvmod_
#   define  fvmod SL_fvmod
#   define  fv2mod SL_fv2mod
#   define  fv3mod SL_fv3mod
#   define  fv4mod SL_fv4mod
#   define  fvnorm_ SL_fvnorm_
#   define  fvnorm SL_fvnorm
#   define  fv2norm SL_fv2norm
#   define  fv3norm SL_fv3norm
#   define  fv4norm SL_fv4norm
#   define  fvfloor_ SL_fvfloor_
#   define  fvfloor SL_fvfloor
#   define  fv2floor SL_fv2floor
#   define  fv3floor SL_fv3floor
#   define  fv4floor SL_fv4floor
#   define  fvceil_ SL_fvceil_
#   define  fvceil SL_fvceil
#   define  fv2ceil SL_fv2ceil
#   define  fv3ceil SL_fv3ceil
#   define  fv4ceil SL_fv4ceil
#   define  fvfrac_ SL_fvfrac_
#   define  fvfrac SL_fvfrac
#   define  fv2frac SL_fv2frac
#   define  fv3frac SL_fv3frac
#   define  fv4frac SL_fv4frac
#   define  fvlerp_ SL_fvlerp_
#   define  fvlerp SL_fvlerp
#   define  fv2lerp SL_fv2lerp
#   define  fv3lerp SL_fv3lerp
#   define  fv4lerp SL_fv4lerp
#   define  fv2serp SL_fv2serp
#   define  fv3serp SL_fv3serp
#   define  fv4serp SL_fv4serp
#   define  fv2angle SL_fv2angle
#   define  fv2from_angle SL_fv2from_angle
#   define  fv3from_yawPitch SL_fv3from_yawPitch
#   define  fv2rot_sc SL_fv2rot_sc
#   define  fv2rot_cs SL_fv2rot_cs
#   define  fv2rot SL_fv2rot
#   define  fv2cross SL_fv2cross
#   define  fv3cross SL_fv3cross
#   define  dv2_zero SL_dv2_zero
#   define  dv2_one SL_dv2_one
#   define  dv2_right SL_dv2_right
#   define  dv2_up SL_dv2_up
#   define  dv2_left SL_dv2_left
#   define  dv2_down SL_dv2_down
#   define  dv3_zero SL_dv3_zero
#   define  dv3_one SL_dv3_one
#   define  dv3_right SL_dv3_right
#   define  dv3_up SL_dv3_up
#   define  dv3_forw SL_dv3_forw
#   define  dv3_left SL_dv3_left
#   define  dv3_down SL_dv3_down
#   define  dv3_back SL_dv3_back
#   define  dv4_zero SL_dv4_zero
#   define  dv4_one SL_dv4_one
#   define  dv4_white SL_dv4_white
#   define  dv4_black SL_dv4_black
#   define  dv4_red SL_dv4_red
#   define  dv4_green SL_dv4_green
#   define  dv4_blue SL_dv4_blue
#   define  dv4_yellow SL_dv4_yellow
#   define  dv4_cyan SL_dv4_cyan
#   define  dv4_purple SL_dv4_purple
#   define  dv2_ SL_dv2_
#   define  dv3_ SL_dv3_
#   define  dv4_ SL_dv4_
#   define  dv2s SL_dv2s
#   define  dv3s SL_dv3s
#   define  dv4s SL_dv4s
#   define  dvv SL_dvv
#   define  dv2v SL_dv2v
#   define  dv3v SL_dv3v
#   define  dv4v SL_dv4v
#   define  dvequ_ SL_dvequ_
#   define  dvequ SL_dvequ
#   define  dv2equ SL_dv2equ
#   define  dv3equ SL_dv3equ
#   define  dv4equ SL_dv4equ
#   define  dvadd_ SL_dvadd_
#   define  dvadd SL_dvadd
#   define  dv2add SL_dv2add
#   define  dv3add SL_dv3add
#   define  dv4add SL_dv4add
#   define  dvsub_ SL_dvsub_
#   define  dvsub SL_dvsub
#   define  dv2sub SL_dv2sub
#   define  dv3sub SL_dv3sub
#   define  dv4sub SL_dv4sub
#   define  dvmul_ SL_dvmul_
#   define  dvmul SL_dvmul
#   define  dv2mul SL_dv2mul
#   define  dv3mul SL_dv3mul
#   define  dv4mul SL_dv4mul
#   define  dvmuls_ SL_dvmuls_
#   define  dvmuls SL_dvmuls
#   define  dv2muls SL_dv2muls
#   define  dv3muls SL_dv3muls
#   define  dv4muls SL_dv4muls
#   define  dvdiv_ SL_dvdiv_
#   define  dvdiv SL_dvdiv
#   define  dv2div SL_dv2div
#   define  dv3div SL_dv3div
#   define  dv4div SL_dv4div
#   define  dvdivs_ SL_dvdivs_
#   define  dvdivs SL_dvdivs
#   define  dv2divs SL_dv2divs
#   define  dv3divs SL_dv3divs
#   define  dv4divs SL_dv4divs
#   define  dvaddS_ SL_dvaddS_
#   define  dvaddS SL_dvaddS
#   define  dv2addS SL_dv2addS
#   define  dv3addS SL_dv3addS
#   define  dv4addS SL_dv4addS
#   define  dvsubS_ SL_dvsubS_
#   define  dvsubS SL_dvsubS
#   define  dv2subS SL_dv2subS
#   define  dv3subS SL_dv3subS
#   define  dv4subS SL_dv4subS
#   define  dvaddM_ SL_dvaddM_
#   define  dvaddM SL_dvaddM
#   define  dv2addM SL_dv2addM
#   define  dv3addM SL_dv3addM
#   define  dv4addM SL_dv4addM
#   define  dvsubM_ SL_dvsubM_
#   define  dvsubM SL_dvsubM
#   define  dv2subM SL_dv2subM
#   define  dv3subM SL_dv3subM
#   define  dv4subM SL_dv4subM
#   define  dvaddSM_ SL_dvaddSM_
#   define  dvaddSM SL_dvaddSM
#   define  dv2addSM SL_dv2addSM
#   define  dv3addSM SL_dv3addSM
#   define  dv4addSM SL_dv4addSM
#   define  dvsubSM_ SL_dvsubSM_
#   define  dvsubSM SL_dvsubSM
#   define  dv2subSM SL_dv2subSM
#   define  dv3subSM SL_dv3subSM
#   define  dv4subSM SL_dv4subSM
#   define  dvSadd_ SL_dvSadd_
#   define  dvSadd SL_dvSadd
#   define  dv2Sadd SL_dv2Sadd
#   define  dv3Sadd SL_dv3Sadd
#   define  dv4Sadd SL_dv4Sadd
#   define  dvSsub_ SL_dvSsub_
#   define  dvSsub SL_dvSsub
#   define  dv2Ssub SL_dv2Ssub
#   define  dv3Ssub SL_dv3Ssub
#   define  dv4Ssub SL_dv4Ssub
#   define  dvmix_ SL_dvmix_
#   define  dvmix SL_dvmix
#   define  dv2mix SL_dv2mix
#   define  dv3mix SL_dv3mix
#   define  dv4mix SL_dv4mix
#   define  dvneg_ SL_dvneg_
#   define  dvneg SL_dvneg
#   define  dv2neg SL_dv2neg
#   define  dv3neg SL_dv3neg
#   define  dv4neg SL_dv4neg
#   define  dvabs_ SL_dvabs_
#   define  dvabs SL_dvabs
#   define  dv2abs SL_dv2abs
#   define  dv3abs SL_dv3abs
#   define  dv4abs SL_dv4abs
#   define  dvmin_ SL_dvmin_
#   define  dvmin SL_dvmin
#   define  dv2min SL_dv2min
#   define  dv3min SL_dv3min
#   define  dv4min SL_dv4min
#   define  dvmax_ SL_dvmax_
#   define  dvmax SL_dvmax
#   define  dv2max SL_dv2max
#   define  dv3max SL_dv3max
#   define  dv4max SL_dv4max
#   define  dvdot_ SL_dvdot_
#   define  dvdot SL_dvdot
#   define  dv2dot SL_dv2dot
#   define  dv3dot SL_dv3dot
#   define  dv4dot SL_dv4dot
#   define  dvlen_max_ SL_dvlen_max_
#   define  dvlen_max SL_dvlen_max
#   define  dv2len_max SL_dv2len_max
#   define  dv3len_max SL_dv3len_max
#   define  dv4len_max SL_dv4len_max
#   define  dvlen_manh_ SL_dvlen_manh_
#   define  dvlen_manh SL_dvlen_manh
#   define  dv2len_manh SL_dv2len_manh
#   define  dv3len_manh SL_dv3len_manh
#   define  dv4len_manh SL_dv4len_manh
#   define  dvlen_srq_ SL_dvlen_srq_
#   define  dvlen_srq SL_dvlen_srq
#   define  dv2len_sqr SL_dv2len_sqr
#   define  dv3len_sqr SL_dv3len_sqr
#   define  dv4len_sqr SL_dv4len_sqr
#   define  dvlen_ SL_dvlen_
#   define  dvlen SL_dvlen
#   define  dv2len SL_dv2len
#   define  dv3len SL_dv3len
#   define  dv4len SL_dv4len
#   define  dvdist_ SL_dvdist_
#   define  dvdist SL_dvdist
#   define  dv2dist SL_dv2dist
#   define  dv3dist SL_dv3dist
#   define  dv4dist SL_dv4dist
#   define  dv2refl SL_dv2refl
#   define  dv3refl SL_dv3refl
#   define  dv4refl SL_dv4refl
#   define  dv2refl_u SL_dv2refl_u
#   define  dv3refl_u SL_dv3refl_u
#   define  dv4refl_u SL_dv4refl_u
#   define  dv2align SL_dv2align
#   define  dv3align SL_dv3align
#   define  dv4align SL_dv4align
#   define  dv2align_u SL_dv2align_u
#   define  dv3align_u SL_dv3align_u
#   define  dv4align_u SL_dv4align_u
#   define  dv2proj SL_dv2proj
#   define  dv3proj SL_dv3proj
#   define  dv4proj SL_dv4proj
#   define  dv2proj_u SL_dv2proj_u
#   define  dv3proj_u SL_dv3proj_u
#   define  dv4proj_u SL_dv4proj_u
#   define  dvmods_ SL_dvmods_
#   define  dvmods SL_dvmods
#   define  dv2mods SL_dv2mods
#   define  dv3mods SL_dv3mods
#   define  dv4mods SL_dv4mods
#   define  dvmod_ SL_dvmod_
#   define  dvmod SL_dvmod
#   define  dv2mod SL_dv2mod
#   define  dv3mod SL_dv3mod
#   define  dv4mod SL_dv4mod
#   define  dvnorm_ SL_dvnorm_
#   define  dvnorm SL_dvnorm
#   define  dv2norm SL_dv2norm
#   define  dv3norm SL_dv3norm
#   define  dv4norm SL_dv4norm
#   define  dvfloor_ SL_dvfloor_
#   define  dvfloor SL_dvfloor
#   define  dv2floor SL_dv2floor
#   define  dv3floor SL_dv3floor
#   define  dv4floor SL_dv4floor
#   define  dvceil_ SL_dvceil_
#   define  dvceil SL_dvceil
#   define  dv2ceil SL_dv2ceil
#   define  dv3ceil SL_dv3ceil
#   define  dv4ceil SL_dv4ceil
#   define  dvfrac_ SL_dvfrac_
#   define  dvfrac SL_dvfrac
#   define  dv2frac SL_dv2frac
#   define  dv3frac SL_dv3frac
#   define  dv4frac SL_dv4frac
#   define  dvlerp_ SL_dvlerp_
#   define  dvlerp SL_dvlerp
#   define  dv2lerp SL_dv2lerp
#   define  dv3lerp SL_dv3lerp
#   define  dv4lerp SL_dv4lerp
#   define  dv2serp SL_dv2serp
#   define  dv3serp SL_dv3serp
#   define  dv4serp SL_dv4serp
#   define  dv2angle SL_dv2angle
#   define  dv2from_angle SL_dv2from_angle
#   define  dv3from_yawPitch SL_dv3from_yawPitch
#   define  dv2rot_sc SL_dv2rot_sc
#   define  dv2rot_cs SL_dv2rot_cs
#   define  dv2rot SL_dv2rot
#   define  dv2cross SL_dv2cross
#   define  dv3cross SL_dv3cross
#   define  bv2_zero SL_bv2_zero
#   define  bv2_one SL_bv2_one
#   define  bv2_right SL_bv2_right
#   define  bv2_up SL_bv2_up
#   define  bv3_zero SL_bv3_zero
#   define  bv3_one SL_bv3_one
#   define  bv3_right SL_bv3_right
#   define  bv3_up SL_bv3_up
#   define  bv3_forw SL_bv3_forw
#   define  bv4_zero SL_bv4_zero
#   define  bv4_one SL_bv4_one
#   define  bv4_white SL_bv4_white
#   define  bv4_black SL_bv4_black
#   define  bv4_red SL_bv4_red
#   define  bv4_green SL_bv4_green
#   define  bv4_blue SL_bv4_blue
#   define  bv4_yellow SL_bv4_yellow
#   define  bv4_cyan SL_bv4_cyan
#   define  bv4_purple SL_bv4_purple
#   define  bv2_ SL_bv2_
#   define  bv3_ SL_bv3_
#   define  bv4_ SL_bv4_
#   define  bv2s SL_bv2s
#   define  bv3s SL_bv3s
#   define  bv4s SL_bv4s
#   define  bvv SL_bvv
#   define  bv2v SL_bv2v
#   define  bv3v SL_bv3v
#   define  bv4v SL_bv4v
#   define  bvequ_ SL_bvequ_
#   define  bvequ SL_bvequ
#   define  bv2equ SL_bv2equ
#   define  bv3equ SL_bv3equ
#   define  bv4equ SL_bv4equ
#   define  bvadd_ SL_bvadd_
#   define  bvadd SL_bvadd
#   define  bv2add SL_bv2add
#   define  bv3add SL_bv3add
#   define  bv4add SL_bv4add
#   define  bvsub_ SL_bvsub_
#   define  bvsub SL_bvsub
#   define  bv2sub SL_bv2sub
#   define  bv3sub SL_bv3sub
#   define  bv4sub SL_bv4sub
#   define  bvmul_ SL_bvmul_
#   define  bvmul SL_bvmul
#   define  bv2mul SL_bv2mul
#   define  bv3mul SL_bv3mul
#   define  bv4mul SL_bv4mul
#   define  bvmuls_ SL_bvmuls_
#   define  bvmuls SL_bvmuls
#   define  bv2muls SL_bv2muls
#   define  bv3muls SL_bv3muls
#   define  bv4muls SL_bv4muls
#   define  bvdiv_ SL_bvdiv_
#   define  bvdiv SL_bvdiv
#   define  bv2div SL_bv2div
#   define  bv3div SL_bv3div
#   define  bv4div SL_bv4div
#   define  bvdivs_ SL_bvdivs_
#   define  bvdivs SL_bvdivs
#   define  bv2divs SL_bv2divs
#   define  bv3divs SL_bv3divs
#   define  bv4divs SL_bv4divs
#   define  bvaddS_ SL_bvaddS_
#   define  bvaddS SL_bvaddS
#   define  bv2addS SL_bv2addS
#   define  bv3addS SL_bv3addS
#   define  bv4addS SL_bv4addS
#   define  bvsubS_ SL_bvsubS_
#   define  bvsubS SL_bvsubS
#   define  bv2subS SL_bv2subS
#   define  bv3subS SL_bv3subS
#   define  bv4subS SL_bv4subS
#   define  bvaddM_ SL_bvaddM_
#   define  bvaddM SL_bvaddM
#   define  bv2addM SL_bv2addM
#   define  bv3addM SL_bv3addM
#   define  bv4addM SL_bv4addM
#   define  bvsubM_ SL_bvsubM_
#   define  bvsubM SL_bvsubM
#   define  bv2subM SL_bv2subM
#   define  bv3subM SL_bv3subM
#   define  bv4subM SL_bv4subM
#   define  bvaddSM_ SL_bvaddSM_
#   define  bvaddSM SL_bvaddSM
#   define  bv2addSM SL_bv2addSM
#   define  bv3addSM SL_bv3addSM
#   define  bv4addSM SL_bv4addSM
#   define  bvsubSM_ SL_bvsubSM_
#   define  bvsubSM SL_bvsubSM
#   define  bv2subSM SL_bv2subSM
#   define  bv3subSM SL_bv3subSM
#   define  bv4subSM SL_bv4subSM
#   define  bvSadd_ SL_bvSadd_
#   define  bvSadd SL_bvSadd
#   define  bv2Sadd SL_bv2Sadd
#   define  bv3Sadd SL_bv3Sadd
#   define  bv4Sadd SL_bv4Sadd
#   define  bvSsub_ SL_bvSsub_
#   define  bvSsub SL_bvSsub
#   define  bv2Ssub SL_bv2Ssub
#   define  bv3Ssub SL_bv3Ssub
#   define  bv4Ssub SL_bv4Ssub
#   define  bvmix_ SL_bvmix_
#   define  bvmix SL_bvmix
#   define  bv2mix SL_bv2mix
#   define  bv3mix SL_bv3mix
#   define  bv4mix SL_bv4mix
#   define  bvmin_ SL_bvmin_
#   define  bvmin SL_bvmin
#   define  bv2min SL_bv2min
#   define  bv3min SL_bv3min
#   define  bv4min SL_bv4min
#   define  bvmax_ SL_bvmax_
#   define  bvmax SL_bvmax
#   define  bv2max SL_bv2max
#   define  bv3max SL_bv3max
#   define  bv4max SL_bv4max
#   define  bvdot_ SL_bvdot_
#   define  bvdot SL_bvdot
#   define  bv2dot SL_bv2dot
#   define  bv3dot SL_bv3dot
#   define  bv4dot SL_bv4dot
#   define  bvlen_max_ SL_bvlen_max_
#   define  bvlen_max SL_bvlen_max
#   define  bv2len_max SL_bv2len_max
#   define  bv3len_max SL_bv3len_max
#   define  bv4len_max SL_bv4len_max
#   define  bvlen_manh_ SL_bvlen_manh_
#   define  bvlen_manh SL_bvlen_manh
#   define  bv2len_manh SL_bv2len_manh
#   define  bv3len_manh SL_bv3len_manh
#   define  bv4len_manh SL_bv4len_manh
#   define  bvlen_srq_ SL_bvlen_srq_
#   define  bvlen_srq SL_bvlen_srq
#   define  bv2len_sqr SL_bv2len_sqr
#   define  bv3len_sqr SL_bv3len_sqr
#   define  bv4len_sqr SL_bv4len_sqr
#   define  bvlen_ SL_bvlen_
#   define  bvlen SL_bvlen
#   define  bv2len SL_bv2len
#   define  bv3len SL_bv3len
#   define  bv4len SL_bv4len
#   define  bvdist_ SL_bvdist_
#   define  bvdist SL_bvdist
#   define  bv2dist SL_bv2dist
#   define  bv3dist SL_bv3dist
#   define  bv4dist SL_bv4dist
#   define  bvand_ SL_bvand_
#   define  bvand SL_bvand
#   define  bv2and SL_bv2and
#   define  bv3and SL_bv3and
#   define  bv4and SL_bv4and
#   define  bvor_ SL_bvor_
#   define  bvor SL_bvor
#   define  bv2or SL_bv2or
#   define  bv3or SL_bv3or
#   define  bv4or SL_bv4or
#   define  bvxor_ SL_bvxor_
#   define  bvxor SL_bvxor
#   define  bv2xor SL_bv2xor
#   define  bv3xor SL_bv3xor
#   define  bv4xor SL_bv4xor
#   define  bvnot_ SL_bvnot_
#   define  bvnot SL_bvnot
#   define  bv2not SL_bv2not
#   define  bv3not SL_bv3not
#   define  bv4not SL_bv4not
#   define  bvlshfts_ SL_bvlshfts_
#   define  bvlshfts SL_bvlshfts
#   define  bv2lshfts SL_bv2lshfts
#   define  bv3lshfts SL_bv3lshfts
#   define  bv4lshfts SL_bv4lshfts
#   define  bvlshft_ SL_bvlshft_
#   define  bvlshft SL_bvlshft
#   define  bv2lshft SL_bv2lshft
#   define  bv3lshft SL_bv3lshft
#   define  bv4lshft SL_bv4lshft
#   define  bvrshfts_ SL_bvrshfts_
#   define  bvrshfts SL_bvrshfts
#   define  bv2rshfts SL_bv2rshfts
#   define  bv3rshfts SL_bv3rshfts
#   define  bv4rshfts SL_bv4rshfts
#   define  bvrshft_ SL_bvrshft_
#   define  bvrshft SL_bvrshft
#   define  bv2rshft SL_bv2rshft
#   define  bv3rshft SL_bv3rshft
#   define  bv4rshft SL_bv4rshft
#   define  iv2_zero SL_iv2_zero
#   define  iv2_one SL_iv2_one
#   define  iv2_right SL_iv2_right
#   define  iv2_up SL_iv2_up
#   define  iv2_left SL_iv2_left
#   define  iv2_down SL_iv2_down
#   define  iv3_zero SL_iv3_zero
#   define  iv3_one SL_iv3_one
#   define  iv3_right SL_iv3_right
#   define  iv3_up SL_iv3_up
#   define  iv3_forw SL_iv3_forw
#   define  iv3_left SL_iv3_left
#   define  iv3_down SL_iv3_down
#   define  iv3_back SL_iv3_back
#   define  iv4_zero SL_iv4_zero
#   define  iv4_one SL_iv4_one
#   define  iv2_ SL_iv2_
#   define  iv3_ SL_iv3_
#   define  iv4_ SL_iv4_
#   define  iv2s SL_iv2s
#   define  iv3s SL_iv3s
#   define  iv4s SL_iv4s
#   define  ivv SL_ivv
#   define  iv2v SL_iv2v
#   define  iv3v SL_iv3v
#   define  iv4v SL_iv4v
#   define  ivequ_ SL_ivequ_
#   define  ivequ SL_ivequ
#   define  iv2equ SL_iv2equ
#   define  iv3equ SL_iv3equ
#   define  iv4equ SL_iv4equ
#   define  ivadd_ SL_ivadd_
#   define  ivadd SL_ivadd
#   define  iv2add SL_iv2add
#   define  iv3add SL_iv3add
#   define  iv4add SL_iv4add
#   define  ivsub_ SL_ivsub_
#   define  ivsub SL_ivsub
#   define  iv2sub SL_iv2sub
#   define  iv3sub SL_iv3sub
#   define  iv4sub SL_iv4sub
#   define  ivmul_ SL_ivmul_
#   define  ivmul SL_ivmul
#   define  iv2mul SL_iv2mul
#   define  iv3mul SL_iv3mul
#   define  iv4mul SL_iv4mul
#   define  ivmuls_ SL_ivmuls_
#   define  ivmuls SL_ivmuls
#   define  iv2muls SL_iv2muls
#   define  iv3muls SL_iv3muls
#   define  iv4muls SL_iv4muls
#   define  ivdiv_ SL_ivdiv_
#   define  ivdiv SL_ivdiv
#   define  iv2div SL_iv2div
#   define  iv3div SL_iv3div
#   define  iv4div SL_iv4div
#   define  ivdivs_ SL_ivdivs_
#   define  ivdivs SL_ivdivs
#   define  iv2divs SL_iv2divs
#   define  iv3divs SL_iv3divs
#   define  iv4divs SL_iv4divs
#   define  ivaddS_ SL_ivaddS_
#   define  ivaddS SL_ivaddS
#   define  iv2addS SL_iv2addS
#   define  iv3addS SL_iv3addS
#   define  iv4addS SL_iv4addS
#   define  ivsubS_ SL_ivsubS_
#   define  ivsubS SL_ivsubS
#   define  iv2subS SL_iv2subS
#   define  iv3subS SL_iv3subS
#   define  iv4subS SL_iv4subS
#   define  ivaddM_ SL_ivaddM_
#   define  ivaddM SL_ivaddM
#   define  iv2addM SL_iv2addM
#   define  iv3addM SL_iv3addM
#   define  iv4addM SL_iv4addM
#   define  ivsubM_ SL_ivsubM_
#   define  ivsubM SL_ivsubM
#   define  iv2subM SL_iv2subM
#   define  iv3subM SL_iv3subM
#   define  iv4subM SL_iv4subM
#   define  ivaddSM_ SL_ivaddSM_
#   define  ivaddSM SL_ivaddSM
#   define  iv2addSM SL_iv2addSM
#   define  iv3addSM SL_iv3addSM
#   define  iv4addSM SL_iv4addSM
#   define  ivsubSM_ SL_ivsubSM_
#   define  ivsubSM SL_ivsubSM
#   define  iv2subSM SL_iv2subSM
#   define  iv3subSM SL_iv3subSM
#   define  iv4subSM SL_iv4subSM
#   define  ivSadd_ SL_ivSadd_
#   define  ivSadd SL_ivSadd
#   define  iv2Sadd SL_iv2Sadd
#   define  iv3Sadd SL_iv3Sadd
#   define  iv4Sadd SL_iv4Sadd
#   define  ivSsub_ SL_ivSsub_
#   define  ivSsub SL_ivSsub
#   define  iv2Ssub SL_iv2Ssub
#   define  iv3Ssub SL_iv3Ssub
#   define  iv4Ssub SL_iv4Ssub
#   define  ivmix_ SL_ivmix_
#   define  ivmix SL_ivmix
#   define  iv2mix SL_iv2mix
#   define  iv3mix SL_iv3mix
#   define  iv4mix SL_iv4mix
#   define  ivneg_ SL_ivneg_
#   define  ivneg SL_ivneg
#   define  iv2neg SL_iv2neg
#   define  iv3neg SL_iv3neg
#   define  iv4neg SL_iv4neg
#   define  ivabs_ SL_ivabs_
#   define  ivabs SL_ivabs
#   define  iv2abs SL_iv2abs
#   define  iv3abs SL_iv3abs
#   define  iv4abs SL_iv4abs
#   define  ivmin_ SL_ivmin_
#   define  ivmin SL_ivmin
#   define  iv2min SL_iv2min
#   define  iv3min SL_iv3min
#   define  iv4min SL_iv4min
#   define  ivmax_ SL_ivmax_
#   define  ivmax SL_ivmax
#   define  iv2max SL_iv2max
#   define  iv3max SL_iv3max
#   define  iv4max SL_iv4max
#   define  ivdot_ SL_ivdot_
#   define  ivdot SL_ivdot
#   define  iv2dot SL_iv2dot
#   define  iv3dot SL_iv3dot
#   define  iv4dot SL_iv4dot
#   define  ivlen_max_ SL_ivlen_max_
#   define  ivlen_max SL_ivlen_max
#   define  iv2len_max SL_iv2len_max
#   define  iv3len_max SL_iv3len_max
#   define  iv4len_max SL_iv4len_max
#   define  ivlen_manh_ SL_ivlen_manh_
#   define  ivlen_manh SL_ivlen_manh
#   define  iv2len_manh SL_iv2len_manh
#   define  iv3len_manh SL_iv3len_manh
#   define  iv4len_manh SL_iv4len_manh
#   define  ivlen_srq_ SL_ivlen_srq_
#   define  ivlen_srq SL_ivlen_srq
#   define  iv2len_sqr SL_iv2len_sqr
#   define  iv3len_sqr SL_iv3len_sqr
#   define  iv4len_sqr SL_iv4len_sqr
#   define  ivlen_ SL_ivlen_
#   define  ivlen SL_ivlen
#   define  iv2len SL_iv2len
#   define  iv3len SL_iv3len
#   define  iv4len SL_iv4len
#   define  ivdist_ SL_ivdist_
#   define  ivdist SL_ivdist
#   define  iv2dist SL_iv2dist
#   define  iv3dist SL_iv3dist
#   define  iv4dist SL_iv4dist
#   define  iv2refl SL_iv2refl
#   define  iv3refl SL_iv3refl
#   define  iv4refl SL_iv4refl
#   define  iv2refl_u SL_iv2refl_u
#   define  iv3refl_u SL_iv3refl_u
#   define  iv4refl_u SL_iv4refl_u
#   define  iv2align SL_iv2align
#   define  iv3align SL_iv3align
#   define  iv4align SL_iv4align
#   define  iv2align_u SL_iv2align_u
#   define  iv3align_u SL_iv3align_u
#   define  iv4align_u SL_iv4align_u
#   define  iv2proj SL_iv2proj
#   define  iv3proj SL_iv3proj
#   define  iv4proj SL_iv4proj
#   define  iv2proj_u SL_iv2proj_u
#   define  iv3proj_u SL_iv3proj_u
#   define  iv4proj_u SL_iv4proj_u
#   define  ivmods_ SL_ivmods_
#   define  ivmods SL_ivmods
#   define  iv2mods SL_iv2mods
#   define  iv3mods SL_iv3mods
#   define  iv4mods SL_iv4mods
#   define  ivmod_ SL_ivmod_
#   define  ivmod SL_ivmod
#   define  iv2mod SL_iv2mod
#   define  iv3mod SL_iv3mod
#   define  iv4mod SL_iv4mod
#   define  iv2cross SL_iv2cross
#   define  iv3cross SL_iv3cross
#   define  ivand_ SL_ivand_
#   define  ivand SL_ivand
#   define  iv2and SL_iv2and
#   define  iv3and SL_iv3and
#   define  iv4and SL_iv4and
#   define  ivor_ SL_ivor_
#   define  ivor SL_ivor
#   define  iv2or SL_iv2or
#   define  iv3or SL_iv3or
#   define  iv4or SL_iv4or
#   define  ivxor_ SL_ivxor_
#   define  ivxor SL_ivxor
#   define  iv2xor SL_iv2xor
#   define  iv3xor SL_iv3xor
#   define  iv4xor SL_iv4xor
#   define  ivnot_ SL_ivnot_
#   define  ivnot SL_ivnot
#   define  iv2not SL_iv2not
#   define  iv3not SL_iv3not
#   define  iv4not SL_iv4not
#   define  ivlshfts_ SL_ivlshfts_
#   define  ivlshfts SL_ivlshfts
#   define  iv2lshfts SL_iv2lshfts
#   define  iv3lshfts SL_iv3lshfts
#   define  iv4lshfts SL_iv4lshfts
#   define  ivlshft_ SL_ivlshft_
#   define  ivlshft SL_ivlshft
#   define  iv2lshft SL_iv2lshft
#   define  iv3lshft SL_iv3lshft
#   define  iv4lshft SL_iv4lshft
#   define  ivrshfts_ SL_ivrshfts_
#   define  ivrshfts SL_ivrshfts
#   define  iv2rshfts SL_iv2rshfts
#   define  iv3rshfts SL_iv3rshfts
#   define  iv4rshfts SL_iv4rshfts
#   define  ivrshft_ SL_ivrshft_
#   define  ivrshft SL_ivrshft
#   define  iv2rshft SL_iv2rshft
#   define  iv3rshft SL_iv3rshft
#   define  iv4rshft SL_iv4rshft
#   define  uv2_zero SL_uv2_zero
#   define  uv2_one SL_uv2_one
#   define  uv2_right SL_uv2_right
#   define  uv2_up SL_uv2_up
#   define  uv3_zero SL_uv3_zero
#   define  uv3_one SL_uv3_one
#   define  uv3_right SL_uv3_right
#   define  uv3_up SL_uv3_up
#   define  uv3_forw SL_uv3_forw
#   define  uv4_zero SL_uv4_zero
#   define  uv4_one SL_uv4_one
#   define  uv2_ SL_uv2_
#   define  uv3_ SL_uv3_
#   define  uv4_ SL_uv4_
#   define  uv2s SL_uv2s
#   define  uv3s SL_uv3s
#   define  uv4s SL_uv4s
#   define  uvv SL_uvv
#   define  uv2v SL_uv2v
#   define  uv3v SL_uv3v
#   define  uv4v SL_uv4v
#   define  uvequ_ SL_uvequ_
#   define  uvequ SL_uvequ
#   define  uv2equ SL_uv2equ
#   define  uv3equ SL_uv3equ
#   define  uv4equ SL_uv4equ
#   define  uvadd_ SL_uvadd_
#   define  uvadd SL_uvadd
#   define  uv2add SL_uv2add
#   define  uv3add SL_uv3add
#   define  uv4add SL_uv4add
#   define  uvsub_ SL_uvsub_
#   define  uvsub SL_uvsub
#   define  uv2sub SL_uv2sub
#   define  uv3sub SL_uv3sub
#   define  uv4sub SL_uv4sub
#   define  uvmul_ SL_uvmul_
#   define  uvmul SL_uvmul
#   define  uv2mul SL_uv2mul
#   define  uv3mul SL_uv3mul
#   define  uv4mul SL_uv4mul
#   define  uvmuls_ SL_uvmuls_
#   define  uvmuls SL_uvmuls
#   define  uv2muls SL_uv2muls
#   define  uv3muls SL_uv3muls
#   define  uv4muls SL_uv4muls
#   define  uvdiv_ SL_uvdiv_
#   define  uvdiv SL_uvdiv
#   define  uv2div SL_uv2div
#   define  uv3div SL_uv3div
#   define  uv4div SL_uv4div
#   define  uvdivs_ SL_uvdivs_
#   define  uvdivs SL_uvdivs
#   define  uv2divs SL_uv2divs
#   define  uv3divs SL_uv3divs
#   define  uv4divs SL_uv4divs
#   define  uvaddS_ SL_uvaddS_
#   define  uvaddS SL_uvaddS
#   define  uv2addS SL_uv2addS
#   define  uv3addS SL_uv3addS
#   define  uv4addS SL_uv4addS
#   define  uvsubS_ SL_uvsubS_
#   define  uvsubS SL_uvsubS
#   define  uv2subS SL_uv2subS
#   define  uv3subS SL_uv3subS
#   define  uv4subS SL_uv4subS
#   define  uvaddM_ SL_uvaddM_
#   define  uvaddM SL_uvaddM
#   define  uv2addM SL_uv2addM
#   define  uv3addM SL_uv3addM
#   define  uv4addM SL_uv4addM
#   define  uvsubM_ SL_uvsubM_
#   define  uvsubM SL_uvsubM
#   define  uv2subM SL_uv2subM
#   define  uv3subM SL_uv3subM
#   define  uv4subM SL_uv4subM
#   define  uvaddSM_ SL_uvaddSM_
#   define  uvaddSM SL_uvaddSM
#   define  uv2addSM SL_uv2addSM
#   define  uv3addSM SL_uv3addSM
#   define  uv4addSM SL_uv4addSM
#   define  uvsubSM_ SL_uvsubSM_
#   define  uvsubSM SL_uvsubSM
#   define  uv2subSM SL_uv2subSM
#   define  uv3subSM SL_uv3subSM
#   define  uv4subSM SL_uv4subSM
#   define  uvSadd_ SL_uvSadd_
#   define  uvSadd SL_uvSadd
#   define  uv2Sadd SL_uv2Sadd
#   define  uv3Sadd SL_uv3Sadd
#   define  uv4Sadd SL_uv4Sadd
#   define  uvSsub_ SL_uvSsub_
#   define  uvSsub SL_uvSsub
#   define  uv2Ssub SL_uv2Ssub
#   define  uv3Ssub SL_uv3Ssub
#   define  uv4Ssub SL_uv4Ssub
#   define  uvmix_ SL_uvmix_
#   define  uvmix SL_uvmix
#   define  uv2mix SL_uv2mix
#   define  uv3mix SL_uv3mix
#   define  uv4mix SL_uv4mix
#   define  uvmin_ SL_uvmin_
#   define  uvmin SL_uvmin
#   define  uv2min SL_uv2min
#   define  uv3min SL_uv3min
#   define  uv4min SL_uv4min
#   define  uvmax_ SL_uvmax_
#   define  uvmax SL_uvmax
#   define  uv2max SL_uv2max
#   define  uv3max SL_uv3max
#   define  uv4max SL_uv4max
#   define  uvdot_ SL_uvdot_
#   define  uvdot SL_uvdot
#   define  uv2dot SL_uv2dot
#   define  uv3dot SL_uv3dot
#   define  uv4dot SL_uv4dot
#   define  uvlen_max_ SL_uvlen_max_
#   define  uvlen_max SL_uvlen_max
#   define  uv2len_max SL_uv2len_max
#   define  uv3len_max SL_uv3len_max
#   define  uv4len_max SL_uv4len_max
#   define  uvlen_manh_ SL_uvlen_manh_
#   define  uvlen_manh SL_uvlen_manh
#   define  uv2len_manh SL_uv2len_manh
#   define  uv3len_manh SL_uv3len_manh
#   define  uv4len_manh SL_uv4len_manh
#   define  uvlen_srq_ SL_uvlen_srq_
#   define  uvlen_srq SL_uvlen_srq
#   define  uv2len_sqr SL_uv2len_sqr
#   define  uv3len_sqr SL_uv3len_sqr
#   define  uv4len_sqr SL_uv4len_sqr
#   define  uvlen_ SL_uvlen_
#   define  uvlen SL_uvlen
#   define  uv2len SL_uv2len
#   define  uv3len SL_uv3len
#   define  uv4len SL_uv4len
#   define  uvdist_ SL_uvdist_
#   define  uvdist SL_uvdist
#   define  uv2dist SL_uv2dist
#   define  uv3dist SL_uv3dist
#   define  uv4dist SL_uv4dist
#   define  uv2refl SL_uv2refl
#   define  uv3refl SL_uv3refl
#   define  uv4refl SL_uv4refl
#   define  uv2refl_u SL_uv2refl_u
#   define  uv3refl_u SL_uv3refl_u
#   define  uv4refl_u SL_uv4refl_u
#   define  uv2align SL_uv2align
#   define  uv3align SL_uv3align
#   define  uv4align SL_uv4align
#   define  uv2align_u SL_uv2align_u
#   define  uv3align_u SL_uv3align_u
#   define  uv4align_u SL_uv4align_u
#   define  uv2proj SL_uv2proj
#   define  uv3proj SL_uv3proj
#   define  uv4proj SL_uv4proj
#   define  uv2proj_u SL_uv2proj_u
#   define  uv3proj_u SL_uv3proj_u
#   define  uv4proj_u SL_uv4proj_u
#   define  uvmods_ SL_uvmods_
#   define  uvmods SL_uvmods
#   define  uv2mods SL_uv2mods
#   define  uv3mods SL_uv3mods
#   define  uv4mods SL_uv4mods
#   define  uvmod_ SL_uvmod_
#   define  uvmod SL_uvmod
#   define  uv2mod SL_uv2mod
#   define  uv3mod SL_uv3mod
#   define  uv4mod SL_uv4mod
#   define  uvand_ SL_uvand_
#   define  uvand SL_uvand
#   define  uv2and SL_uv2and
#   define  uv3and SL_uv3and
#   define  uv4and SL_uv4and
#   define  uvor_ SL_uvor_
#   define  uvor SL_uvor
#   define  uv2or SL_uv2or
#   define  uv3or SL_uv3or
#   define  uv4or SL_uv4or
#   define  uvxor_ SL_uvxor_
#   define  uvxor SL_uvxor
#   define  uv2xor SL_uv2xor
#   define  uv3xor SL_uv3xor
#   define  uv4xor SL_uv4xor
#   define  uvnot_ SL_uvnot_
#   define  uvnot SL_uvnot
#   define  uv2not SL_uv2not
#   define  uv3not SL_uv3not
#   define  uv4not SL_uv4not
#   define  uvlshfts_ SL_uvlshfts_
#   define  uvlshfts SL_uvlshfts
#   define  uv2lshfts SL_uv2lshfts
#   define  uv3lshfts SL_uv3lshfts
#   define  uv4lshfts SL_uv4lshfts
#   define  uvlshft_ SL_uvlshft_
#   define  uvlshft SL_uvlshft
#   define  uv2lshft SL_uv2lshft
#   define  uv3lshft SL_uv3lshft
#   define  uv4lshft SL_uv4lshft
#   define  uvrshfts_ SL_uvrshfts_
#   define  uvrshfts SL_uvrshfts
#   define  uv2rshfts SL_uv2rshfts
#   define  uv3rshfts SL_uv3rshfts
#   define  uv4rshfts SL_uv4rshfts
#   define  uvrshft_ SL_uvrshft_
#   define  uvrshft SL_uvrshft
#   define  uv2rshft SL_uv2rshft
#   define  uv3rshft SL_uv3rshft
#   define  uv4rshft SL_uv4rshft
#   define  liv2_zero SL_liv2_zero
#   define  liv2_one SL_liv2_one
#   define  liv2_right SL_liv2_right
#   define  liv2_up SL_liv2_up
#   define  liv2_left SL_liv2_left
#   define  liv2_down SL_liv2_down
#   define  liv3_zero SL_liv3_zero
#   define  liv3_one SL_liv3_one
#   define  liv3_right SL_liv3_right
#   define  liv3_up SL_liv3_up
#   define  liv3_forw SL_liv3_forw
#   define  liv3_left SL_liv3_left
#   define  liv3_down SL_liv3_down
#   define  liv3_back SL_liv3_back
#   define  liv4_zero SL_liv4_zero
#   define  liv4_one SL_liv4_one
#   define  liv2_ SL_liv2_
#   define  liv3_ SL_liv3_
#   define  liv4_ SL_liv4_
#   define  liv2s SL_liv2s
#   define  liv3s SL_liv3s
#   define  liv4s SL_liv4s
#   define  livv SL_livv
#   define  liv2v SL_liv2v
#   define  liv3v SL_liv3v
#   define  liv4v SL_liv4v
#   define  livequ_ SL_livequ_
#   define  livequ SL_livequ
#   define  liv2equ SL_liv2equ
#   define  liv3equ SL_liv3equ
#   define  liv4equ SL_liv4equ
#   define  livadd_ SL_livadd_
#   define  livadd SL_livadd
#   define  liv2add SL_liv2add
#   define  liv3add SL_liv3add
#   define  liv4add SL_liv4add
#   define  livsub_ SL_livsub_
#   define  livsub SL_livsub
#   define  liv2sub SL_liv2sub
#   define  liv3sub SL_liv3sub
#   define  liv4sub SL_liv4sub
#   define  livmul_ SL_livmul_
#   define  livmul SL_livmul
#   define  liv2mul SL_liv2mul
#   define  liv3mul SL_liv3mul
#   define  liv4mul SL_liv4mul
#   define  livmuls_ SL_livmuls_
#   define  livmuls SL_livmuls
#   define  liv2muls SL_liv2muls
#   define  liv3muls SL_liv3muls
#   define  liv4muls SL_liv4muls
#   define  livdiv_ SL_livdiv_
#   define  livdiv SL_livdiv
#   define  liv2div SL_liv2div
#   define  liv3div SL_liv3div
#   define  liv4div SL_liv4div
#   define  livdivs_ SL_livdivs_
#   define  livdivs SL_livdivs
#   define  liv2divs SL_liv2divs
#   define  liv3divs SL_liv3divs
#   define  liv4divs SL_liv4divs
#   define  livaddS_ SL_livaddS_
#   define  livaddS SL_livaddS
#   define  liv2addS SL_liv2addS
#   define  liv3addS SL_liv3addS
#   define  liv4addS SL_liv4addS
#   define  livsubS_ SL_livsubS_
#   define  livsubS SL_livsubS
#   define  liv2subS SL_liv2subS
#   define  liv3subS SL_liv3subS
#   define  liv4subS SL_liv4subS
#   define  livaddM_ SL_livaddM_
#   define  livaddM SL_livaddM
#   define  liv2addM SL_liv2addM
#   define  liv3addM SL_liv3addM
#   define  liv4addM SL_liv4addM
#   define  livsubM_ SL_livsubM_
#   define  livsubM SL_livsubM
#   define  liv2subM SL_liv2subM
#   define  liv3subM SL_liv3subM
#   define  liv4subM SL_liv4subM
#   define  livaddSM_ SL_livaddSM_
#   define  livaddSM SL_livaddSM
#   define  liv2addSM SL_liv2addSM
#   define  liv3addSM SL_liv3addSM
#   define  liv4addSM SL_liv4addSM
#   define  livsubSM_ SL_livsubSM_
#   define  livsubSM SL_livsubSM
#   define  liv2subSM SL_liv2subSM
#   define  liv3subSM SL_liv3subSM
#   define  liv4subSM SL_liv4subSM
#   define  livSadd_ SL_livSadd_
#   define  livSadd SL_livSadd
#   define  liv2Sadd SL_liv2Sadd
#   define  liv3Sadd SL_liv3Sadd
#   define  liv4Sadd SL_liv4Sadd
#   define  livSsub_ SL_livSsub_
#   define  livSsub SL_livSsub
#   define  liv2Ssub SL_liv2Ssub
#   define  liv3Ssub SL_liv3Ssub
#   define  liv4Ssub SL_liv4Ssub
#   define  livmix_ SL_livmix_
#   define  livmix SL_livmix
#   define  liv2mix SL_liv2mix
#   define  liv3mix SL_liv3mix
#   define  liv4mix SL_liv4mix
#   define  livneg_ SL_livneg_
#   define  livneg SL_livneg
#   define  liv2neg SL_liv2neg
#   define  liv3neg SL_liv3neg
#   define  liv4neg SL_liv4neg
#   define  livabs_ SL_livabs_
#   define  livabs SL_livabs
#   define  liv2abs SL_liv2abs
#   define  liv3abs SL_liv3abs
#   define  liv4abs SL_liv4abs
#   define  livmin_ SL_livmin_
#   define  livmin SL_livmin
#   define  liv2min SL_liv2min
#   define  liv3min SL_liv3min
#   define  liv4min SL_liv4min
#   define  livmax_ SL_livmax_
#   define  livmax SL_livmax
#   define  liv2max SL_liv2max
#   define  liv3max SL_liv3max
#   define  liv4max SL_liv4max
#   define  livdot_ SL_livdot_
#   define  livdot SL_livdot
#   define  liv2dot SL_liv2dot
#   define  liv3dot SL_liv3dot
#   define  liv4dot SL_liv4dot
#   define  livlen_max_ SL_livlen_max_
#   define  livlen_max SL_livlen_max
#   define  liv2len_max SL_liv2len_max
#   define  liv3len_max SL_liv3len_max
#   define  liv4len_max SL_liv4len_max
#   define  livlen_manh_ SL_livlen_manh_
#   define  livlen_manh SL_livlen_manh
#   define  liv2len_manh SL_liv2len_manh
#   define  liv3len_manh SL_liv3len_manh
#   define  liv4len_manh SL_liv4len_manh
#   define  livlen_srq_ SL_livlen_srq_
#   define  livlen_srq SL_livlen_srq
#   define  liv2len_sqr SL_liv2len_sqr
#   define  liv3len_sqr SL_liv3len_sqr
#   define  liv4len_sqr SL_liv4len_sqr
#   define  livlen_ SL_livlen_
#   define  livlen SL_livlen
#   define  liv2len SL_liv2len
#   define  liv3len SL_liv3len
#   define  liv4len SL_liv4len
#   define  livdist_ SL_livdist_
#   define  livdist SL_livdist
#   define  liv2dist SL_liv2dist
#   define  liv3dist SL_liv3dist
#   define  liv4dist SL_liv4dist
#   define  liv2refl SL_liv2refl
#   define  liv3refl SL_liv3refl
#   define  liv4refl SL_liv4refl
#   define  liv2refl_u SL_liv2refl_u
#   define  liv3refl_u SL_liv3refl_u
#   define  liv4refl_u SL_liv4refl_u
#   define  liv2align SL_liv2align
#   define  liv3align SL_liv3align
#   define  liv4align SL_liv4align
#   define  liv2align_u SL_liv2align_u
#   define  liv3align_u SL_liv3align_u
#   define  liv4align_u SL_liv4align_u
#   define  liv2proj SL_liv2proj
#   define  liv3proj SL_liv3proj
#   define  liv4proj SL_liv4proj
#   define  liv2proj_u SL_liv2proj_u
#   define  liv3proj_u SL_liv3proj_u
#   define  liv4proj_u SL_liv4proj_u
#   define  livmods_ SL_livmods_
#   define  livmods SL_livmods
#   define  liv2mods SL_liv2mods
#   define  liv3mods SL_liv3mods
#   define  liv4mods SL_liv4mods
#   define  livmod_ SL_livmod_
#   define  livmod SL_livmod
#   define  liv2mod SL_liv2mod
#   define  liv3mod SL_liv3mod
#   define  liv4mod SL_liv4mod
#   define  liv2cross SL_liv2cross
#   define  liv3cross SL_liv3cross
#   define  livand_ SL_livand_
#   define  livand SL_livand
#   define  liv2and SL_liv2and
#   define  liv3and SL_liv3and
#   define  liv4and SL_liv4and
#   define  livor_ SL_livor_
#   define  livor SL_livor
#   define  liv2or SL_liv2or
#   define  liv3or SL_liv3or
#   define  liv4or SL_liv4or
#   define  livxor_ SL_livxor_
#   define  livxor SL_livxor
#   define  liv2xor SL_liv2xor
#   define  liv3xor SL_liv3xor
#   define  liv4xor SL_liv4xor
#   define  livnot_ SL_livnot_
#   define  livnot SL_livnot
#   define  liv2not SL_liv2not
#   define  liv3not SL_liv3not
#   define  liv4not SL_liv4not
#   define  livlshfts_ SL_livlshfts_
#   define  livlshfts SL_livlshfts
#   define  liv2lshfts SL_liv2lshfts
#   define  liv3lshfts SL_liv3lshfts
#   define  liv4lshfts SL_liv4lshfts
#   define  livlshft_ SL_livlshft_
#   define  livlshft SL_livlshft
#   define  liv2lshft SL_liv2lshft
#   define  liv3lshft SL_liv3lshft
#   define  liv4lshft SL_liv4lshft
#   define  livrshfts_ SL_livrshfts_
#   define  livrshfts SL_livrshfts
#   define  liv2rshfts SL_liv2rshfts
#   define  liv3rshfts SL_liv3rshfts
#   define  liv4rshfts SL_liv4rshfts
#   define  livrshft_ SL_livrshft_
#   define  livrshft SL_livrshft
#   define  liv2rshft SL_liv2rshft
#   define  liv3rshft SL_liv3rshft
#   define  liv4rshft SL_liv4rshft
#   define  luv2_zero SL_luv2_zero
#   define  luv2_one SL_luv2_one
#   define  luv2_right SL_luv2_right
#   define  luv2_up SL_luv2_up
#   define  luv3_zero SL_luv3_zero
#   define  luv3_one SL_luv3_one
#   define  luv3_right SL_luv3_right
#   define  luv3_up SL_luv3_up
#   define  luv3_forw SL_luv3_forw
#   define  luv4_zero SL_luv4_zero
#   define  luv4_one SL_luv4_one
#   define  luv2_ SL_luv2_
#   define  luv3_ SL_luv3_
#   define  luv4_ SL_luv4_
#   define  luv2s SL_luv2s
#   define  luv3s SL_luv3s
#   define  luv4s SL_luv4s
#   define  luvv SL_luvv
#   define  luv2v SL_luv2v
#   define  luv3v SL_luv3v
#   define  luv4v SL_luv4v
#   define  luvequ_ SL_luvequ_
#   define  luvequ SL_luvequ
#   define  luv2equ SL_luv2equ
#   define  luv3equ SL_luv3equ
#   define  luv4equ SL_luv4equ
#   define  luvadd_ SL_luvadd_
#   define  luvadd SL_luvadd
#   define  luv2add SL_luv2add
#   define  luv3add SL_luv3add
#   define  luv4add SL_luv4add
#   define  luvsub_ SL_luvsub_
#   define  luvsub SL_luvsub
#   define  luv2sub SL_luv2sub
#   define  luv3sub SL_luv3sub
#   define  luv4sub SL_luv4sub
#   define  luvmul_ SL_luvmul_
#   define  luvmul SL_luvmul
#   define  luv2mul SL_luv2mul
#   define  luv3mul SL_luv3mul
#   define  luv4mul SL_luv4mul
#   define  luvmuls_ SL_luvmuls_
#   define  luvmuls SL_luvmuls
#   define  luv2muls SL_luv2muls
#   define  luv3muls SL_luv3muls
#   define  luv4muls SL_luv4muls
#   define  luvdiv_ SL_luvdiv_
#   define  luvdiv SL_luvdiv
#   define  luv2div SL_luv2div
#   define  luv3div SL_luv3div
#   define  luv4div SL_luv4div
#   define  luvdivs_ SL_luvdivs_
#   define  luvdivs SL_luvdivs
#   define  luv2divs SL_luv2divs
#   define  luv3divs SL_luv3divs
#   define  luv4divs SL_luv4divs
#   define  luvaddS_ SL_luvaddS_
#   define  luvaddS SL_luvaddS
#   define  luv2addS SL_luv2addS
#   define  luv3addS SL_luv3addS
#   define  luv4addS SL_luv4addS
#   define  luvsubS_ SL_luvsubS_
#   define  luvsubS SL_luvsubS
#   define  luv2subS SL_luv2subS
#   define  luv3subS SL_luv3subS
#   define  luv4subS SL_luv4subS
#   define  luvaddM_ SL_luvaddM_
#   define  luvaddM SL_luvaddM
#   define  luv2addM SL_luv2addM
#   define  luv3addM SL_luv3addM
#   define  luv4addM SL_luv4addM
#   define  luvsubM_ SL_luvsubM_
#   define  luvsubM SL_luvsubM
#   define  luv2subM SL_luv2subM
#   define  luv3subM SL_luv3subM
#   define  luv4subM SL_luv4subM
#   define  luvaddSM_ SL_luvaddSM_
#   define  luvaddSM SL_luvaddSM
#   define  luv2addSM SL_luv2addSM
#   define  luv3addSM SL_luv3addSM
#   define  luv4addSM SL_luv4addSM
#   define  luvsubSM_ SL_luvsubSM_
#   define  luvsubSM SL_luvsubSM
#   define  luv2subSM SL_luv2subSM
#   define  luv3subSM SL_luv3subSM
#   define  luv4subSM SL_luv4subSM
#   define  luvSadd_ SL_luvSadd_
#   define  luvSadd SL_luvSadd
#   define  luv2Sadd SL_luv2Sadd
#   define  luv3Sadd SL_luv3Sadd
#   define  luv4Sadd SL_luv4Sadd
#   define  luvSsub_ SL_luvSsub_
#   define  luvSsub SL_luvSsub
#   define  luv2Ssub SL_luv2Ssub
#   define  luv3Ssub SL_luv3Ssub
#   define  luv4Ssub SL_luv4Ssub
#   define  luvmix_ SL_luvmix_
#   define  luvmix SL_luvmix
#   define  luv2mix SL_luv2mix
#   define  luv3mix SL_luv3mix
#   define  luv4mix SL_luv4mix
#   define  luvmin_ SL_luvmin_
#   define  luvmin SL_luvmin
#   define  luv2min SL_luv2min
#   define  luv3min SL_luv3min
#   define  luv4min SL_luv4min
#   define  luvmax_ SL_luvmax_
#   define  luvmax SL_luvmax
#   define  luv2max SL_luv2max
#   define  luv3max SL_luv3max
#   define  luv4max SL_luv4max
#   define  luvdot_ SL_luvdot_
#   define  luvdot SL_luvdot
#   define  luv2dot SL_luv2dot
#   define  luv3dot SL_luv3dot
#   define  luv4dot SL_luv4dot
#   define  luvlen_max_ SL_luvlen_max_
#   define  luvlen_max SL_luvlen_max
#   define  luv2len_max SL_luv2len_max
#   define  luv3len_max SL_luv3len_max
#   define  luv4len_max SL_luv4len_max
#   define  luvlen_manh_ SL_luvlen_manh_
#   define  luvlen_manh SL_luvlen_manh
#   define  luv2len_manh SL_luv2len_manh
#   define  luv3len_manh SL_luv3len_manh
#   define  luv4len_manh SL_luv4len_manh
#   define  luvlen_srq_ SL_luvlen_srq_
#   define  luvlen_srq SL_luvlen_srq
#   define  luv2len_sqr SL_luv2len_sqr
#   define  luv3len_sqr SL_luv3len_sqr
#   define  luv4len_sqr SL_luv4len_sqr
#   define  luvlen_ SL_luvlen_
#   define  luvlen SL_luvlen
#   define  luv2len SL_luv2len
#   define  luv3len SL_luv3len
#   define  luv4len SL_luv4len
#   define  luvdist_ SL_luvdist_
#   define  luvdist SL_luvdist
#   define  luv2dist SL_luv2dist
#   define  luv3dist SL_luv3dist
#   define  luv4dist SL_luv4dist
#   define  luv2refl SL_luv2refl
#   define  luv3refl SL_luv3refl
#   define  luv4refl SL_luv4refl
#   define  luv2refl_u SL_luv2refl_u
#   define  luv3refl_u SL_luv3refl_u
#   define  luv4refl_u SL_luv4refl_u
#   define  luv2align SL_luv2align
#   define  luv3align SL_luv3align
#   define  luv4align SL_luv4align
#   define  luv2align_u SL_luv2align_u
#   define  luv3align_u SL_luv3align_u
#   define  luv4align_u SL_luv4align_u
#   define  luv2proj SL_luv2proj
#   define  luv3proj SL_luv3proj
#   define  luv4proj SL_luv4proj
#   define  luv2proj_u SL_luv2proj_u
#   define  luv3proj_u SL_luv3proj_u
#   define  luv4proj_u SL_luv4proj_u
#   define  luvmods_ SL_luvmods_
#   define  luvmods SL_luvmods
#   define  luv2mods SL_luv2mods
#   define  luv3mods SL_luv3mods
#   define  luv4mods SL_luv4mods
#   define  luvmod_ SL_luvmod_
#   define  luvmod SL_luvmod
#   define  luv2mod SL_luv2mod
#   define  luv3mod SL_luv3mod
#   define  luv4mod SL_luv4mod
#   define  luvand_ SL_luvand_
#   define  luvand SL_luvand
#   define  luv2and SL_luv2and
#   define  luv3and SL_luv3and
#   define  luv4and SL_luv4and
#   define  luvor_ SL_luvor_
#   define  luvor SL_luvor
#   define  luv2or SL_luv2or
#   define  luv3or SL_luv3or
#   define  luv4or SL_luv4or
#   define  luvxor_ SL_luvxor_
#   define  luvxor SL_luvxor
#   define  luv2xor SL_luv2xor
#   define  luv3xor SL_luv3xor
#   define  luv4xor SL_luv4xor
#   define  luvnot_ SL_luvnot_
#   define  luvnot SL_luvnot
#   define  luv2not SL_luv2not
#   define  luv3not SL_luv3not
#   define  luv4not SL_luv4not
#   define  luvlshfts_ SL_luvlshfts_
#   define  luvlshfts SL_luvlshfts
#   define  luv2lshfts SL_luv2lshfts
#   define  luv3lshfts SL_luv3lshfts
#   define  luv4lshfts SL_luv4lshfts
#   define  luvlshft_ SL_luvlshft_
#   define  luvlshft SL_luvlshft
#   define  luv2lshft SL_luv2lshft
#   define  luv3lshft SL_luv3lshft
#   define  luv4lshft SL_luv4lshft
#   define  luvrshfts_ SL_luvrshfts_
#   define  luvrshfts SL_luvrshfts
#   define  luv2rshfts SL_luv2rshfts
#   define  luv3rshfts SL_luv3rshfts
#   define  luv4rshfts SL_luv4rshfts
#   define  luvrshft_ SL_luvrshft_
#   define  luvrshft SL_luvrshft
#   define  luv2rshft SL_luv2rshft
#   define  luv3rshft SL_luv3rshft
#   define  luv4rshft SL_luv4rshft
#endif

#endif // _SL_VECTOR_H_

// vector.h: THIS FILE WAS GENERATED ON 09/10/2026 AT 02:24:41
