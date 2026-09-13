#ifndef __SL_MATRIX_H
#define __SL_MATRIX_H

#include "../base.h"
#include "vector.h"
#include "quaternion.h"

#define SL_msize(M)      SL_luv2_(sizeof(((typeof(M) *)NULL)->r0) / sizeof(((typeof(M) *)NULL)->m00), sizeof(((typeof(M) *)NULL)->r0) / sizeof(((typeof(M) *)NULL)->m00))
#define SL_mget(M, i, j) ((M).data[j + i * (M).c])

#define SL_XPD_M2X2(M) (M).m00, (M).m01, (M).m10, (M).m11
#define SL_XPD_M3X3(M) (M).m00, (M).m01, (M).m02, (M).m10, (M).m11, (M).m12, (M).m20, (M).m21, (M).m22
#define SL_XPD_M4X4(M) (M).m00, (M).m01, (M).m02, (M).m03, (M).m10, (M).m11, (M).m12, (M).m13, (M).m20, (M).m21, (M).m22, (M).m23, (M).m30, (M).m31, (M).m32, (M).m33

#define SL_FMT_M2X2(fmt, ...) "[ "fmt" "fmt" ]"__VA_ARGS__"[ "fmt" "fmt" ]"
#define SL_FMT_M3X3(fmt, ...) "[ "fmt" "fmt" "fmt" ]"__VA_ARGS__"[ "fmt" "fmt" "fmt" ]"__VA_ARGS__"[ "fmt" "fmt" "fmt" ]"
#define SL_FMT_M4X4(fmt, ...) "[ "fmt" "fmt" "fmt" "fmt" ]"__VA_ARGS__"[ "fmt" "fmt" "fmt" "fmt" ]"__VA_ARGS__"[ "fmt" "fmt" "fmt" "fmt" ]"__VA_ARGS__"[ "fmt" "fmt" "fmt" "fmt" ]"


#pragma region I32

/// @brief Matrix of i32 with arbitrary dimensions
typedef struct {
    union { usize r, c; luv2 size; };
    i32 *data;
} i32m;

#define SL_asi32m(sized_mat) ((i32m){.size = SL_msize(sized_mat), .data = sized_mat.data})





/// @brief Matrix of i32 of size 2 x 2
typedef union {
    i32 data[2 * 2];
    i32 m[2][2];
    struct {
        i32 m00, m01;
        i32 m10, m11;
    };
    struct { i32v2 r0, r1; };
} i32m2x2;

#define SL_i32m2x2_zero ((i32m2x2){0})
#define SL_i32m2x2_identity ((i32m2x2){ 1, 0, 0, 1 })


#define SL_i32m2x2diag(m00_, m11_) ((i32m2x2){.m00 = m00_, .m11 = m11_})

/// @brief Addition of two i32m2x2
SL_header i32m2x2 SL_i32m2x2add(i32m2x2 lhs, i32m2x2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32m2x2) {
        .m00 = lhs.m00 + rhs.m00, .m01 = lhs.m01 + rhs.m01,
        .m10 = lhs.m10 + rhs.m10, .m11 = lhs.m11 + rhs.m11
    };
}
#else
;
#endif
/// @brief Difference of two i32m2x2
SL_header i32m2x2 SL_i32m2x2sub(i32m2x2 lhs, i32m2x2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32m2x2) {
        .m00 = lhs.m00 - rhs.m00, .m01 = lhs.m01 - rhs.m01,
        .m10 = lhs.m10 - rhs.m10, .m11 = lhs.m11 - rhs.m11
    };
}
#else
;
#endif
/// @brief Product of two i32m2x2
SL_header i32m2x2 SL_i32m2x2mul(i32m2x2 lhs, i32m2x2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    i32m2x2 res = SL_i32m2x2_zero;
    for (usize k = 0; k < SL_msize(lhs).x; ++k)
    for (usize j = 0; j < SL_msize(lhs).y; ++j)
    for (usize i = 0; i < SL_msize(lhs).x; ++i)
        res.m[i][j] += lhs.m[i][k] * rhs.m[k][j];

    return res;
}
#else
;
#endif
/// @brief Component-wise multiplication of a i32m2x2 with a scalar
SL_header i32m2x2 SL_i32m2x2muls(i32m2x2 lhs, i32 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32m2x2) {
        .m00 = lhs.m00 * rhs, .m01 = lhs.m01 * rhs,
        .m10 = lhs.m10 * rhs, .m11 = lhs.m11 * rhs
    };
}
#else
;
#endif
/// @brief Product of a i32m2x2 and a i32v2
SL_header i32v2 SL_i32m2x2mulv(i32m2x2 lhs, i32v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i32v2_(SL_i32v2dot(lhs.r0, rhs), SL_i32v2dot(lhs.r1, rhs));
}
#else
;
#endif
/// @brief Component-wise division of a i32m2x2 with a scalar
SL_header i32m2x2 SL_i32m2x2divs(i32m2x2 lhs, i32 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32m2x2) {
        .m00 = lhs.m00 / rhs, .m01 = lhs.m01 / rhs,
        .m10 = lhs.m10 / rhs, .m11 = lhs.m11 / rhs
    };
}
#else
;
#endif
/// @brief Addition of two i32m2x2 with lhs scaled by a i32
SL_header i32m2x2 SL_i32m2x2addS(i32m2x2 lhs, i32m2x2 rhs, i32 s)
#if defined(SL_IMPLEMENTATION)
{
    return (i32m2x2) {
        .m00 = lhs.m00 + rhs.m00 * s, .m01 = lhs.m01 + rhs.m01 * s,
        .m10 = lhs.m10 + rhs.m10 * s, .m11 = lhs.m11 + rhs.m11 * s
    };
}
#else
;
#endif
/// @brief Difference of two i32m2x2 with lhs scaled by a i32
SL_header i32m2x2 SL_i32m2x2subS(i32m2x2 lhs, i32m2x2 rhs, i32 s)
#if defined(SL_IMPLEMENTATION)
{
    return (i32m2x2) {
        .m00 = lhs.m00 - rhs.m00 * s, .m01 = lhs.m01 - rhs.m01 * s,
        .m10 = lhs.m10 - rhs.m10 * s, .m11 = lhs.m11 - rhs.m11 * s
    };
}
#else
;
#endif
/// @brief Negation of a i32m2x2
SL_header i32m2x2 SL_i32m2x2neg(i32m2x2 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i32m2x2) {
        .m00 = -m.m00, .m01 = -m.m01,
        .m10 = -m.m10, .m11 = -m.m11
    };
}
#else
;
#endif
/// @brief Component-wise absolute value of a i32m2x2
SL_header i32m2x2 SL_i32m2x2abs(i32m2x2 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i32m2x2) {
        .m00 = m.m00 < 0 ? -m.m00 : m.m00, .m01 = m.m01 < 0 ? -m.m01 : m.m01,
        .m10 = m.m10 < 0 ? -m.m10 : m.m10, .m11 = m.m11 < 0 ? -m.m11 : m.m11
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two i32m2x2
SL_header i32m2x2 SL_i32m2x2min(i32m2x2 lhs, i32m2x2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32m2x2) {
        .m00 = lhs.m00 < rhs.m00 ? lhs.m00 : rhs.m00, .m01 = lhs.m01 < rhs.m01 ? lhs.m01 : rhs.m01,
        .m10 = lhs.m10 < rhs.m10 ? lhs.m10 : rhs.m10, .m11 = lhs.m11 < rhs.m11 ? lhs.m11 : rhs.m11
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two i32m2x2
SL_header i32m2x2 SL_i32m2x2max(i32m2x2 lhs, i32m2x2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32m2x2) {
        .m00 = lhs.m00 > rhs.m00 ? lhs.m00 : rhs.m00, .m01 = lhs.m01 > rhs.m01 ? lhs.m01 : rhs.m01,
        .m10 = lhs.m10 > rhs.m10 ? lhs.m10 : rhs.m10, .m11 = lhs.m11 > rhs.m11 ? lhs.m11 : rhs.m11
    };
}
#else
;
#endif
/// @brief Transposition of a i32m2x2
SL_header i32m2x2 SL_i32m2x2trsp(i32m2x2 m)
#if defined(SL_IMPLEMENTATION)
{
    SL_swap(m.m10, m.m01);
    return m;
}
#else
;
#endif
/// @brief Trace of a i32m2x2
SL_header i32 SL_i32m2x2trace(i32m2x2 m)
#if defined(SL_IMPLEMENTATION)
{
    return m.m00 + m.m11;
}
#else
;
#endif
/// @brief Determinant of a i32m2x2
SL_header i32 SL_i32m2x2det_xpd(i32 m00, i32 m01, i32 m10, i32 m11)
#if defined(SL_IMPLEMENTATION)
{
    return m00 * m11 - m01 * m10;
}
#else
;
#endif
/// @brief Determinant of a i32m2x2
SL_header i32 SL_i32m2x2det(i32m2x2 m)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i32m2x2det_xpd(SL_XPD_M2X2(m));
}
#else
;
#endif



/// @brief Matrix of i32 of size 3 x 3
typedef union {
    i32 data[3 * 3];
    i32 m[3][3];
    struct {
        i32 m00, m01, m02;
        i32 m10, m11, m12;
        i32 m20, m21, m22;
    };
    struct { i32v3 r0, r1, r2; };
} i32m3x3;

#define SL_i32m3x3_zero ((i32m3x3){0})
#define SL_i32m3x3_identity ((i32m3x3){ 1, 0, 0, 0, 1, 0, 0, 0, 1 })


#define SL_i32m3x3diag(m00_, m11_, m22_) ((i32m3x3){.m00 = m00_, .m11 = m11_, .m22 = m22_})

/// @brief Addition of two i32m3x3
SL_header i32m3x3 SL_i32m3x3add(i32m3x3 lhs, i32m3x3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32m3x3) {
        .m00 = lhs.m00 + rhs.m00, .m01 = lhs.m01 + rhs.m01, .m02 = lhs.m02 + rhs.m02,
        .m10 = lhs.m10 + rhs.m10, .m11 = lhs.m11 + rhs.m11, .m12 = lhs.m12 + rhs.m12,
        .m20 = lhs.m20 + rhs.m20, .m21 = lhs.m21 + rhs.m21, .m22 = lhs.m22 + rhs.m22
    };
}
#else
;
#endif
/// @brief Difference of two i32m3x3
SL_header i32m3x3 SL_i32m3x3sub(i32m3x3 lhs, i32m3x3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32m3x3) {
        .m00 = lhs.m00 - rhs.m00, .m01 = lhs.m01 - rhs.m01, .m02 = lhs.m02 - rhs.m02,
        .m10 = lhs.m10 - rhs.m10, .m11 = lhs.m11 - rhs.m11, .m12 = lhs.m12 - rhs.m12,
        .m20 = lhs.m20 - rhs.m20, .m21 = lhs.m21 - rhs.m21, .m22 = lhs.m22 - rhs.m22
    };
}
#else
;
#endif
/// @brief Product of two i32m3x3
SL_header i32m3x3 SL_i32m3x3mul(i32m3x3 lhs, i32m3x3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    i32m3x3 res = SL_i32m3x3_zero;
    for (usize k = 0; k < SL_msize(lhs).x; ++k)
    for (usize j = 0; j < SL_msize(lhs).y; ++j)
    for (usize i = 0; i < SL_msize(lhs).x; ++i)
        res.m[i][j] += lhs.m[i][k] * rhs.m[k][j];

    return res;
}
#else
;
#endif
/// @brief Component-wise multiplication of a i32m3x3 with a scalar
SL_header i32m3x3 SL_i32m3x3muls(i32m3x3 lhs, i32 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32m3x3) {
        .m00 = lhs.m00 * rhs, .m01 = lhs.m01 * rhs, .m02 = lhs.m02 * rhs,
        .m10 = lhs.m10 * rhs, .m11 = lhs.m11 * rhs, .m12 = lhs.m12 * rhs,
        .m20 = lhs.m20 * rhs, .m21 = lhs.m21 * rhs, .m22 = lhs.m22 * rhs
    };
}
#else
;
#endif
/// @brief Product of a i32m3x3 and a i32v3
SL_header i32v3 SL_i32m3x3mulv(i32m3x3 lhs, i32v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i32v3_(SL_i32v3dot(lhs.r0, rhs), SL_i32v3dot(lhs.r1, rhs), SL_i32v3dot(lhs.r2, rhs));
}
#else
;
#endif
/// @brief Apply transformation represented by i32m3x3 to a i32v2
SL_header i32v2 SL_i32m3x3apply(i32m3x3 m, i32v2 v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i32m3x3mulv(m, SL_i32v3v(v, 1)).xy;
}
#else
;
#endif
/// @brief Component-wise division of a i32m3x3 with a scalar
SL_header i32m3x3 SL_i32m3x3divs(i32m3x3 lhs, i32 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32m3x3) {
        .m00 = lhs.m00 / rhs, .m01 = lhs.m01 / rhs, .m02 = lhs.m02 / rhs,
        .m10 = lhs.m10 / rhs, .m11 = lhs.m11 / rhs, .m12 = lhs.m12 / rhs,
        .m20 = lhs.m20 / rhs, .m21 = lhs.m21 / rhs, .m22 = lhs.m22 / rhs
    };
}
#else
;
#endif
/// @brief Addition of two i32m3x3 with lhs scaled by a i32
SL_header i32m3x3 SL_i32m3x3addS(i32m3x3 lhs, i32m3x3 rhs, i32 s)
#if defined(SL_IMPLEMENTATION)
{
    return (i32m3x3) {
        .m00 = lhs.m00 + rhs.m00 * s, .m01 = lhs.m01 + rhs.m01 * s, .m02 = lhs.m02 + rhs.m02 * s,
        .m10 = lhs.m10 + rhs.m10 * s, .m11 = lhs.m11 + rhs.m11 * s, .m12 = lhs.m12 + rhs.m12 * s,
        .m20 = lhs.m20 + rhs.m20 * s, .m21 = lhs.m21 + rhs.m21 * s, .m22 = lhs.m22 + rhs.m22 * s
    };
}
#else
;
#endif
/// @brief Difference of two i32m3x3 with lhs scaled by a i32
SL_header i32m3x3 SL_i32m3x3subS(i32m3x3 lhs, i32m3x3 rhs, i32 s)
#if defined(SL_IMPLEMENTATION)
{
    return (i32m3x3) {
        .m00 = lhs.m00 - rhs.m00 * s, .m01 = lhs.m01 - rhs.m01 * s, .m02 = lhs.m02 - rhs.m02 * s,
        .m10 = lhs.m10 - rhs.m10 * s, .m11 = lhs.m11 - rhs.m11 * s, .m12 = lhs.m12 - rhs.m12 * s,
        .m20 = lhs.m20 - rhs.m20 * s, .m21 = lhs.m21 - rhs.m21 * s, .m22 = lhs.m22 - rhs.m22 * s
    };
}
#else
;
#endif
/// @brief Negation of a i32m3x3
SL_header i32m3x3 SL_i32m3x3neg(i32m3x3 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i32m3x3) {
        .m00 = -m.m00, .m01 = -m.m01, .m02 = -m.m02,
        .m10 = -m.m10, .m11 = -m.m11, .m12 = -m.m12,
        .m20 = -m.m20, .m21 = -m.m21, .m22 = -m.m22
    };
}
#else
;
#endif
/// @brief Component-wise absolute value of a i32m3x3
SL_header i32m3x3 SL_i32m3x3abs(i32m3x3 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i32m3x3) {
        .m00 = m.m00 < 0 ? -m.m00 : m.m00, .m01 = m.m01 < 0 ? -m.m01 : m.m01, .m02 = m.m02 < 0 ? -m.m02 : m.m02,
        .m10 = m.m10 < 0 ? -m.m10 : m.m10, .m11 = m.m11 < 0 ? -m.m11 : m.m11, .m12 = m.m12 < 0 ? -m.m12 : m.m12,
        .m20 = m.m20 < 0 ? -m.m20 : m.m20, .m21 = m.m21 < 0 ? -m.m21 : m.m21, .m22 = m.m22 < 0 ? -m.m22 : m.m22
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two i32m3x3
SL_header i32m3x3 SL_i32m3x3min(i32m3x3 lhs, i32m3x3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32m3x3) {
        .m00 = lhs.m00 < rhs.m00 ? lhs.m00 : rhs.m00, .m01 = lhs.m01 < rhs.m01 ? lhs.m01 : rhs.m01, .m02 = lhs.m02 < rhs.m02 ? lhs.m02 : rhs.m02,
        .m10 = lhs.m10 < rhs.m10 ? lhs.m10 : rhs.m10, .m11 = lhs.m11 < rhs.m11 ? lhs.m11 : rhs.m11, .m12 = lhs.m12 < rhs.m12 ? lhs.m12 : rhs.m12,
        .m20 = lhs.m20 < rhs.m20 ? lhs.m20 : rhs.m20, .m21 = lhs.m21 < rhs.m21 ? lhs.m21 : rhs.m21, .m22 = lhs.m22 < rhs.m22 ? lhs.m22 : rhs.m22
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two i32m3x3
SL_header i32m3x3 SL_i32m3x3max(i32m3x3 lhs, i32m3x3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32m3x3) {
        .m00 = lhs.m00 > rhs.m00 ? lhs.m00 : rhs.m00, .m01 = lhs.m01 > rhs.m01 ? lhs.m01 : rhs.m01, .m02 = lhs.m02 > rhs.m02 ? lhs.m02 : rhs.m02,
        .m10 = lhs.m10 > rhs.m10 ? lhs.m10 : rhs.m10, .m11 = lhs.m11 > rhs.m11 ? lhs.m11 : rhs.m11, .m12 = lhs.m12 > rhs.m12 ? lhs.m12 : rhs.m12,
        .m20 = lhs.m20 > rhs.m20 ? lhs.m20 : rhs.m20, .m21 = lhs.m21 > rhs.m21 ? lhs.m21 : rhs.m21, .m22 = lhs.m22 > rhs.m22 ? lhs.m22 : rhs.m22
    };
}
#else
;
#endif
/// @brief Transposition of a i32m3x3
SL_header i32m3x3 SL_i32m3x3trsp(i32m3x3 m)
#if defined(SL_IMPLEMENTATION)
{
    SL_swap(m.m10, m.m01);
    SL_swap(m.m20, m.m02); SL_swap(m.m21, m.m12);
    return m;
}
#else
;
#endif
/// @brief Trace of a i32m3x3
SL_header i32 SL_i32m3x3trace(i32m3x3 m)
#if defined(SL_IMPLEMENTATION)
{
    return m.m00 + m.m11 + m.m22;
}
#else
;
#endif
/// @brief Determinant of a i32m3x3
SL_header i32 SL_i32m3x3det_xpd(i32 m00, i32 m01, i32 m02, i32 m10, i32 m11, i32 m12, i32 m20, i32 m21, i32 m22)
#if defined(SL_IMPLEMENTATION)
{
    return m00 * m11 * m22 + m01 * m12 * m20 + m02 * m10 * m21 - m02 * m11 * m20 - m12 * m21 * m00 - m22 * m01 * m10;
}
#else
;
#endif
/// @brief Determinant of a i32m3x3
SL_header i32 SL_i32m3x3det(i32m3x3 m)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i32m3x3det_xpd(SL_XPD_M3X3(m));
}
#else
;
#endif



/// @brief Matrix of i32 of size 4 x 4
typedef union {
    i32 data[4 * 4];
    i32 m[4][4];
    struct {
        i32 m00, m01, m02, m03;
        i32 m10, m11, m12, m13;
        i32 m20, m21, m22, m23;
        i32 m30, m31, m32, m33;
    };
    struct { i32v4 r0, r1, r2, r3; };
} i32m4x4;

#define SL_i32m4x4_zero ((i32m4x4){0})
#define SL_i32m4x4_identity ((i32m4x4){ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 })


#define SL_i32m4x4diag(m00_, m11_, m22_, m33_) ((i32m4x4){.m00 = m00_, .m11 = m11_, .m22 = m22_, .m33 = m33_})

/// @brief Addition of two i32m4x4
SL_header i32m4x4 SL_i32m4x4add(i32m4x4 lhs, i32m4x4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32m4x4) {
        .m00 = lhs.m00 + rhs.m00, .m01 = lhs.m01 + rhs.m01, .m02 = lhs.m02 + rhs.m02, .m03 = lhs.m03 + rhs.m03,
        .m10 = lhs.m10 + rhs.m10, .m11 = lhs.m11 + rhs.m11, .m12 = lhs.m12 + rhs.m12, .m13 = lhs.m13 + rhs.m13,
        .m20 = lhs.m20 + rhs.m20, .m21 = lhs.m21 + rhs.m21, .m22 = lhs.m22 + rhs.m22, .m23 = lhs.m23 + rhs.m23,
        .m30 = lhs.m30 + rhs.m30, .m31 = lhs.m31 + rhs.m31, .m32 = lhs.m32 + rhs.m32, .m33 = lhs.m33 + rhs.m33
    };
}
#else
;
#endif
/// @brief Difference of two i32m4x4
SL_header i32m4x4 SL_i32m4x4sub(i32m4x4 lhs, i32m4x4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32m4x4) {
        .m00 = lhs.m00 - rhs.m00, .m01 = lhs.m01 - rhs.m01, .m02 = lhs.m02 - rhs.m02, .m03 = lhs.m03 - rhs.m03,
        .m10 = lhs.m10 - rhs.m10, .m11 = lhs.m11 - rhs.m11, .m12 = lhs.m12 - rhs.m12, .m13 = lhs.m13 - rhs.m13,
        .m20 = lhs.m20 - rhs.m20, .m21 = lhs.m21 - rhs.m21, .m22 = lhs.m22 - rhs.m22, .m23 = lhs.m23 - rhs.m23,
        .m30 = lhs.m30 - rhs.m30, .m31 = lhs.m31 - rhs.m31, .m32 = lhs.m32 - rhs.m32, .m33 = lhs.m33 - rhs.m33
    };
}
#else
;
#endif
/// @brief Product of two i32m4x4
SL_header i32m4x4 SL_i32m4x4mul(i32m4x4 lhs, i32m4x4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    i32m4x4 res = SL_i32m4x4_zero;
    for (usize k = 0; k < SL_msize(lhs).x; ++k)
    for (usize j = 0; j < SL_msize(lhs).y; ++j)
    for (usize i = 0; i < SL_msize(lhs).x; ++i)
        res.m[i][j] += lhs.m[i][k] * rhs.m[k][j];

    return res;
}
#else
;
#endif
/// @brief Component-wise multiplication of a i32m4x4 with a scalar
SL_header i32m4x4 SL_i32m4x4muls(i32m4x4 lhs, i32 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32m4x4) {
        .m00 = lhs.m00 * rhs, .m01 = lhs.m01 * rhs, .m02 = lhs.m02 * rhs, .m03 = lhs.m03 * rhs,
        .m10 = lhs.m10 * rhs, .m11 = lhs.m11 * rhs, .m12 = lhs.m12 * rhs, .m13 = lhs.m13 * rhs,
        .m20 = lhs.m20 * rhs, .m21 = lhs.m21 * rhs, .m22 = lhs.m22 * rhs, .m23 = lhs.m23 * rhs,
        .m30 = lhs.m30 * rhs, .m31 = lhs.m31 * rhs, .m32 = lhs.m32 * rhs, .m33 = lhs.m33 * rhs
    };
}
#else
;
#endif
/// @brief Product of a i32m4x4 and a i32v4
SL_header i32v4 SL_i32m4x4mulv(i32m4x4 lhs, i32v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i32v4_(SL_i32v4dot(lhs.r0, rhs), SL_i32v4dot(lhs.r1, rhs), SL_i32v4dot(lhs.r2, rhs), SL_i32v4dot(lhs.r3, rhs));
}
#else
;
#endif
/// @brief Apply transformation represented by i32m4x4 to a i32v3
SL_header i32v3 SL_i32m4x4apply(i32m4x4 m, i32v3 v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i32m4x4mulv(m, SL_i32v4v(v, 1)).xyz;
}
#else
;
#endif
/// @brief Component-wise division of a i32m4x4 with a scalar
SL_header i32m4x4 SL_i32m4x4divs(i32m4x4 lhs, i32 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32m4x4) {
        .m00 = lhs.m00 / rhs, .m01 = lhs.m01 / rhs, .m02 = lhs.m02 / rhs, .m03 = lhs.m03 / rhs,
        .m10 = lhs.m10 / rhs, .m11 = lhs.m11 / rhs, .m12 = lhs.m12 / rhs, .m13 = lhs.m13 / rhs,
        .m20 = lhs.m20 / rhs, .m21 = lhs.m21 / rhs, .m22 = lhs.m22 / rhs, .m23 = lhs.m23 / rhs,
        .m30 = lhs.m30 / rhs, .m31 = lhs.m31 / rhs, .m32 = lhs.m32 / rhs, .m33 = lhs.m33 / rhs
    };
}
#else
;
#endif
/// @brief Addition of two i32m4x4 with lhs scaled by a i32
SL_header i32m4x4 SL_i32m4x4addS(i32m4x4 lhs, i32m4x4 rhs, i32 s)
#if defined(SL_IMPLEMENTATION)
{
    return (i32m4x4) {
        .m00 = lhs.m00 + rhs.m00 * s, .m01 = lhs.m01 + rhs.m01 * s, .m02 = lhs.m02 + rhs.m02 * s, .m03 = lhs.m03 + rhs.m03 * s,
        .m10 = lhs.m10 + rhs.m10 * s, .m11 = lhs.m11 + rhs.m11 * s, .m12 = lhs.m12 + rhs.m12 * s, .m13 = lhs.m13 + rhs.m13 * s,
        .m20 = lhs.m20 + rhs.m20 * s, .m21 = lhs.m21 + rhs.m21 * s, .m22 = lhs.m22 + rhs.m22 * s, .m23 = lhs.m23 + rhs.m23 * s,
        .m30 = lhs.m30 + rhs.m30 * s, .m31 = lhs.m31 + rhs.m31 * s, .m32 = lhs.m32 + rhs.m32 * s, .m33 = lhs.m33 + rhs.m33 * s
    };
}
#else
;
#endif
/// @brief Difference of two i32m4x4 with lhs scaled by a i32
SL_header i32m4x4 SL_i32m4x4subS(i32m4x4 lhs, i32m4x4 rhs, i32 s)
#if defined(SL_IMPLEMENTATION)
{
    return (i32m4x4) {
        .m00 = lhs.m00 - rhs.m00 * s, .m01 = lhs.m01 - rhs.m01 * s, .m02 = lhs.m02 - rhs.m02 * s, .m03 = lhs.m03 - rhs.m03 * s,
        .m10 = lhs.m10 - rhs.m10 * s, .m11 = lhs.m11 - rhs.m11 * s, .m12 = lhs.m12 - rhs.m12 * s, .m13 = lhs.m13 - rhs.m13 * s,
        .m20 = lhs.m20 - rhs.m20 * s, .m21 = lhs.m21 - rhs.m21 * s, .m22 = lhs.m22 - rhs.m22 * s, .m23 = lhs.m23 - rhs.m23 * s,
        .m30 = lhs.m30 - rhs.m30 * s, .m31 = lhs.m31 - rhs.m31 * s, .m32 = lhs.m32 - rhs.m32 * s, .m33 = lhs.m33 - rhs.m33 * s
    };
}
#else
;
#endif
/// @brief Negation of a i32m4x4
SL_header i32m4x4 SL_i32m4x4neg(i32m4x4 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i32m4x4) {
        .m00 = -m.m00, .m01 = -m.m01, .m02 = -m.m02, .m03 = -m.m03,
        .m10 = -m.m10, .m11 = -m.m11, .m12 = -m.m12, .m13 = -m.m13,
        .m20 = -m.m20, .m21 = -m.m21, .m22 = -m.m22, .m23 = -m.m23,
        .m30 = -m.m30, .m31 = -m.m31, .m32 = -m.m32, .m33 = -m.m33
    };
}
#else
;
#endif
/// @brief Component-wise absolute value of a i32m4x4
SL_header i32m4x4 SL_i32m4x4abs(i32m4x4 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i32m4x4) {
        .m00 = m.m00 < 0 ? -m.m00 : m.m00, .m01 = m.m01 < 0 ? -m.m01 : m.m01, .m02 = m.m02 < 0 ? -m.m02 : m.m02, .m03 = m.m03 < 0 ? -m.m03 : m.m03,
        .m10 = m.m10 < 0 ? -m.m10 : m.m10, .m11 = m.m11 < 0 ? -m.m11 : m.m11, .m12 = m.m12 < 0 ? -m.m12 : m.m12, .m13 = m.m13 < 0 ? -m.m13 : m.m13,
        .m20 = m.m20 < 0 ? -m.m20 : m.m20, .m21 = m.m21 < 0 ? -m.m21 : m.m21, .m22 = m.m22 < 0 ? -m.m22 : m.m22, .m23 = m.m23 < 0 ? -m.m23 : m.m23,
        .m30 = m.m30 < 0 ? -m.m30 : m.m30, .m31 = m.m31 < 0 ? -m.m31 : m.m31, .m32 = m.m32 < 0 ? -m.m32 : m.m32, .m33 = m.m33 < 0 ? -m.m33 : m.m33
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two i32m4x4
SL_header i32m4x4 SL_i32m4x4min(i32m4x4 lhs, i32m4x4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32m4x4) {
        .m00 = lhs.m00 < rhs.m00 ? lhs.m00 : rhs.m00, .m01 = lhs.m01 < rhs.m01 ? lhs.m01 : rhs.m01, .m02 = lhs.m02 < rhs.m02 ? lhs.m02 : rhs.m02, .m03 = lhs.m03 < rhs.m03 ? lhs.m03 : rhs.m03,
        .m10 = lhs.m10 < rhs.m10 ? lhs.m10 : rhs.m10, .m11 = lhs.m11 < rhs.m11 ? lhs.m11 : rhs.m11, .m12 = lhs.m12 < rhs.m12 ? lhs.m12 : rhs.m12, .m13 = lhs.m13 < rhs.m13 ? lhs.m13 : rhs.m13,
        .m20 = lhs.m20 < rhs.m20 ? lhs.m20 : rhs.m20, .m21 = lhs.m21 < rhs.m21 ? lhs.m21 : rhs.m21, .m22 = lhs.m22 < rhs.m22 ? lhs.m22 : rhs.m22, .m23 = lhs.m23 < rhs.m23 ? lhs.m23 : rhs.m23,
        .m30 = lhs.m30 < rhs.m30 ? lhs.m30 : rhs.m30, .m31 = lhs.m31 < rhs.m31 ? lhs.m31 : rhs.m31, .m32 = lhs.m32 < rhs.m32 ? lhs.m32 : rhs.m32, .m33 = lhs.m33 < rhs.m33 ? lhs.m33 : rhs.m33
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two i32m4x4
SL_header i32m4x4 SL_i32m4x4max(i32m4x4 lhs, i32m4x4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i32m4x4) {
        .m00 = lhs.m00 > rhs.m00 ? lhs.m00 : rhs.m00, .m01 = lhs.m01 > rhs.m01 ? lhs.m01 : rhs.m01, .m02 = lhs.m02 > rhs.m02 ? lhs.m02 : rhs.m02, .m03 = lhs.m03 > rhs.m03 ? lhs.m03 : rhs.m03,
        .m10 = lhs.m10 > rhs.m10 ? lhs.m10 : rhs.m10, .m11 = lhs.m11 > rhs.m11 ? lhs.m11 : rhs.m11, .m12 = lhs.m12 > rhs.m12 ? lhs.m12 : rhs.m12, .m13 = lhs.m13 > rhs.m13 ? lhs.m13 : rhs.m13,
        .m20 = lhs.m20 > rhs.m20 ? lhs.m20 : rhs.m20, .m21 = lhs.m21 > rhs.m21 ? lhs.m21 : rhs.m21, .m22 = lhs.m22 > rhs.m22 ? lhs.m22 : rhs.m22, .m23 = lhs.m23 > rhs.m23 ? lhs.m23 : rhs.m23,
        .m30 = lhs.m30 > rhs.m30 ? lhs.m30 : rhs.m30, .m31 = lhs.m31 > rhs.m31 ? lhs.m31 : rhs.m31, .m32 = lhs.m32 > rhs.m32 ? lhs.m32 : rhs.m32, .m33 = lhs.m33 > rhs.m33 ? lhs.m33 : rhs.m33
    };
}
#else
;
#endif
/// @brief Transposition of a i32m4x4
SL_header i32m4x4 SL_i32m4x4trsp(i32m4x4 m)
#if defined(SL_IMPLEMENTATION)
{
    SL_swap(m.m10, m.m01);
    SL_swap(m.m20, m.m02); SL_swap(m.m12, m.m21);
    SL_swap(m.m30, m.m03); SL_swap(m.m31, m.m13);SL_swap(m.m32, m.m23);
    return m;
}
#else
;
#endif
/// @brief Trace of a i32m4x4
SL_header i32 SL_i32m4x4trace(i32m4x4 m)
#if defined(SL_IMPLEMENTATION)
{
    return m.m00 + m.m11 + m.m22 + m.m33;
}
#else
;
#endif
/// @brief Determinant of a i32m4x4
SL_header i32 SL_i32m4x4det_xpd(i32 m00, i32 m01, i32 m02, i32 m03, i32 m10, i32 m11, i32 m12, i32 m13, i32 m20, i32 m21, i32 m22, i32 m23, i32 m30, i32 m31, i32 m32, i32 m33)
#if defined(SL_IMPLEMENTATION)
{
    return m00 * SL_i32m3x3det_xpd(m11, m12, m13, m21, m22, m23, m31, m32, m33)
         + m01 * SL_i32m3x3det_xpd(m10, m12, m13, m20, m22, m23, m30, m32, m33)
         + m02 * SL_i32m3x3det_xpd(m10, m11, m13, m20, m21, m23, m30, m31, m33)
         + m03 * SL_i32m3x3det_xpd(m10, m11, m12, m20, m21, m22, m30, m31, m32);
}
#else
;
#endif
/// @brief Determinant of a i32m4x4
SL_header i32 SL_i32m4x4det(i32m4x4 m)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i32m4x4det_xpd(SL_XPD_M4X4(m));
}
#else
;
#endif



#pragma endregion I32
#pragma region I64

/// @brief Matrix of i64 with arbitrary dimensions
typedef struct {
    union { usize r, c; luv2 size; };
    i64 *data;
} i64m;

#define SL_asi64m(sized_mat) ((i64m){.size = SL_msize(sized_mat), .data = sized_mat.data})





/// @brief Matrix of i64 of size 2 x 2
typedef union {
    i64 data[2 * 2];
    i64 m[2][2];
    struct {
        i64 m00, m01;
        i64 m10, m11;
    };
    struct { i64v2 r0, r1; };
} i64m2x2;

#define SL_i64m2x2_zero ((i64m2x2){0})
#define SL_i64m2x2_identity ((i64m2x2){ 1, 0, 0, 1 })


#define SL_i64m2x2diag(m00_, m11_) ((i64m2x2){.m00 = m00_, .m11 = m11_})

/// @brief Addition of two i64m2x2
SL_header i64m2x2 SL_i64m2x2add(i64m2x2 lhs, i64m2x2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64m2x2) {
        .m00 = lhs.m00 + rhs.m00, .m01 = lhs.m01 + rhs.m01,
        .m10 = lhs.m10 + rhs.m10, .m11 = lhs.m11 + rhs.m11
    };
}
#else
;
#endif
/// @brief Difference of two i64m2x2
SL_header i64m2x2 SL_i64m2x2sub(i64m2x2 lhs, i64m2x2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64m2x2) {
        .m00 = lhs.m00 - rhs.m00, .m01 = lhs.m01 - rhs.m01,
        .m10 = lhs.m10 - rhs.m10, .m11 = lhs.m11 - rhs.m11
    };
}
#else
;
#endif
/// @brief Product of two i64m2x2
SL_header i64m2x2 SL_i64m2x2mul(i64m2x2 lhs, i64m2x2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    i64m2x2 res = SL_i64m2x2_zero;
    for (usize k = 0; k < SL_msize(lhs).x; ++k)
    for (usize j = 0; j < SL_msize(lhs).y; ++j)
    for (usize i = 0; i < SL_msize(lhs).x; ++i)
        res.m[i][j] += lhs.m[i][k] * rhs.m[k][j];

    return res;
}
#else
;
#endif
/// @brief Component-wise multiplication of a i64m2x2 with a scalar
SL_header i64m2x2 SL_i64m2x2muls(i64m2x2 lhs, i64 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64m2x2) {
        .m00 = lhs.m00 * rhs, .m01 = lhs.m01 * rhs,
        .m10 = lhs.m10 * rhs, .m11 = lhs.m11 * rhs
    };
}
#else
;
#endif
/// @brief Product of a i64m2x2 and a i64v2
SL_header i64v2 SL_i64m2x2mulv(i64m2x2 lhs, i64v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i64v2_(SL_i64v2dot(lhs.r0, rhs), SL_i64v2dot(lhs.r1, rhs));
}
#else
;
#endif
/// @brief Component-wise division of a i64m2x2 with a scalar
SL_header i64m2x2 SL_i64m2x2divs(i64m2x2 lhs, i64 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64m2x2) {
        .m00 = lhs.m00 / rhs, .m01 = lhs.m01 / rhs,
        .m10 = lhs.m10 / rhs, .m11 = lhs.m11 / rhs
    };
}
#else
;
#endif
/// @brief Addition of two i64m2x2 with lhs scaled by a i64
SL_header i64m2x2 SL_i64m2x2addS(i64m2x2 lhs, i64m2x2 rhs, i64 s)
#if defined(SL_IMPLEMENTATION)
{
    return (i64m2x2) {
        .m00 = lhs.m00 + rhs.m00 * s, .m01 = lhs.m01 + rhs.m01 * s,
        .m10 = lhs.m10 + rhs.m10 * s, .m11 = lhs.m11 + rhs.m11 * s
    };
}
#else
;
#endif
/// @brief Difference of two i64m2x2 with lhs scaled by a i64
SL_header i64m2x2 SL_i64m2x2subS(i64m2x2 lhs, i64m2x2 rhs, i64 s)
#if defined(SL_IMPLEMENTATION)
{
    return (i64m2x2) {
        .m00 = lhs.m00 - rhs.m00 * s, .m01 = lhs.m01 - rhs.m01 * s,
        .m10 = lhs.m10 - rhs.m10 * s, .m11 = lhs.m11 - rhs.m11 * s
    };
}
#else
;
#endif
/// @brief Negation of a i64m2x2
SL_header i64m2x2 SL_i64m2x2neg(i64m2x2 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i64m2x2) {
        .m00 = -m.m00, .m01 = -m.m01,
        .m10 = -m.m10, .m11 = -m.m11
    };
}
#else
;
#endif
/// @brief Component-wise absolute value of a i64m2x2
SL_header i64m2x2 SL_i64m2x2abs(i64m2x2 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i64m2x2) {
        .m00 = m.m00 < 0 ? -m.m00 : m.m00, .m01 = m.m01 < 0 ? -m.m01 : m.m01,
        .m10 = m.m10 < 0 ? -m.m10 : m.m10, .m11 = m.m11 < 0 ? -m.m11 : m.m11
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two i64m2x2
SL_header i64m2x2 SL_i64m2x2min(i64m2x2 lhs, i64m2x2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64m2x2) {
        .m00 = lhs.m00 < rhs.m00 ? lhs.m00 : rhs.m00, .m01 = lhs.m01 < rhs.m01 ? lhs.m01 : rhs.m01,
        .m10 = lhs.m10 < rhs.m10 ? lhs.m10 : rhs.m10, .m11 = lhs.m11 < rhs.m11 ? lhs.m11 : rhs.m11
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two i64m2x2
SL_header i64m2x2 SL_i64m2x2max(i64m2x2 lhs, i64m2x2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64m2x2) {
        .m00 = lhs.m00 > rhs.m00 ? lhs.m00 : rhs.m00, .m01 = lhs.m01 > rhs.m01 ? lhs.m01 : rhs.m01,
        .m10 = lhs.m10 > rhs.m10 ? lhs.m10 : rhs.m10, .m11 = lhs.m11 > rhs.m11 ? lhs.m11 : rhs.m11
    };
}
#else
;
#endif
/// @brief Transposition of a i64m2x2
SL_header i64m2x2 SL_i64m2x2trsp(i64m2x2 m)
#if defined(SL_IMPLEMENTATION)
{
    SL_swap(m.m10, m.m01);
    return m;
}
#else
;
#endif
/// @brief Trace of a i64m2x2
SL_header i64 SL_i64m2x2trace(i64m2x2 m)
#if defined(SL_IMPLEMENTATION)
{
    return m.m00 + m.m11;
}
#else
;
#endif
/// @brief Determinant of a i64m2x2
SL_header i64 SL_i64m2x2det_xpd(i64 m00, i64 m01, i64 m10, i64 m11)
#if defined(SL_IMPLEMENTATION)
{
    return m00 * m11 - m01 * m10;
}
#else
;
#endif
/// @brief Determinant of a i64m2x2
SL_header i64 SL_i64m2x2det(i64m2x2 m)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i64m2x2det_xpd(SL_XPD_M2X2(m));
}
#else
;
#endif



/// @brief Matrix of i64 of size 3 x 3
typedef union {
    i64 data[3 * 3];
    i64 m[3][3];
    struct {
        i64 m00, m01, m02;
        i64 m10, m11, m12;
        i64 m20, m21, m22;
    };
    struct { i64v3 r0, r1, r2; };
} i64m3x3;

#define SL_i64m3x3_zero ((i64m3x3){0})
#define SL_i64m3x3_identity ((i64m3x3){ 1, 0, 0, 0, 1, 0, 0, 0, 1 })


#define SL_i64m3x3diag(m00_, m11_, m22_) ((i64m3x3){.m00 = m00_, .m11 = m11_, .m22 = m22_})

/// @brief Addition of two i64m3x3
SL_header i64m3x3 SL_i64m3x3add(i64m3x3 lhs, i64m3x3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64m3x3) {
        .m00 = lhs.m00 + rhs.m00, .m01 = lhs.m01 + rhs.m01, .m02 = lhs.m02 + rhs.m02,
        .m10 = lhs.m10 + rhs.m10, .m11 = lhs.m11 + rhs.m11, .m12 = lhs.m12 + rhs.m12,
        .m20 = lhs.m20 + rhs.m20, .m21 = lhs.m21 + rhs.m21, .m22 = lhs.m22 + rhs.m22
    };
}
#else
;
#endif
/// @brief Difference of two i64m3x3
SL_header i64m3x3 SL_i64m3x3sub(i64m3x3 lhs, i64m3x3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64m3x3) {
        .m00 = lhs.m00 - rhs.m00, .m01 = lhs.m01 - rhs.m01, .m02 = lhs.m02 - rhs.m02,
        .m10 = lhs.m10 - rhs.m10, .m11 = lhs.m11 - rhs.m11, .m12 = lhs.m12 - rhs.m12,
        .m20 = lhs.m20 - rhs.m20, .m21 = lhs.m21 - rhs.m21, .m22 = lhs.m22 - rhs.m22
    };
}
#else
;
#endif
/// @brief Product of two i64m3x3
SL_header i64m3x3 SL_i64m3x3mul(i64m3x3 lhs, i64m3x3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    i64m3x3 res = SL_i64m3x3_zero;
    for (usize k = 0; k < SL_msize(lhs).x; ++k)
    for (usize j = 0; j < SL_msize(lhs).y; ++j)
    for (usize i = 0; i < SL_msize(lhs).x; ++i)
        res.m[i][j] += lhs.m[i][k] * rhs.m[k][j];

    return res;
}
#else
;
#endif
/// @brief Component-wise multiplication of a i64m3x3 with a scalar
SL_header i64m3x3 SL_i64m3x3muls(i64m3x3 lhs, i64 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64m3x3) {
        .m00 = lhs.m00 * rhs, .m01 = lhs.m01 * rhs, .m02 = lhs.m02 * rhs,
        .m10 = lhs.m10 * rhs, .m11 = lhs.m11 * rhs, .m12 = lhs.m12 * rhs,
        .m20 = lhs.m20 * rhs, .m21 = lhs.m21 * rhs, .m22 = lhs.m22 * rhs
    };
}
#else
;
#endif
/// @brief Product of a i64m3x3 and a i64v3
SL_header i64v3 SL_i64m3x3mulv(i64m3x3 lhs, i64v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i64v3_(SL_i64v3dot(lhs.r0, rhs), SL_i64v3dot(lhs.r1, rhs), SL_i64v3dot(lhs.r2, rhs));
}
#else
;
#endif
/// @brief Apply transformation represented by i64m3x3 to a i64v2
SL_header i64v2 SL_i64m3x3apply(i64m3x3 m, i64v2 v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i64m3x3mulv(m, SL_i64v3v(v, 1)).xy;
}
#else
;
#endif
/// @brief Component-wise division of a i64m3x3 with a scalar
SL_header i64m3x3 SL_i64m3x3divs(i64m3x3 lhs, i64 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64m3x3) {
        .m00 = lhs.m00 / rhs, .m01 = lhs.m01 / rhs, .m02 = lhs.m02 / rhs,
        .m10 = lhs.m10 / rhs, .m11 = lhs.m11 / rhs, .m12 = lhs.m12 / rhs,
        .m20 = lhs.m20 / rhs, .m21 = lhs.m21 / rhs, .m22 = lhs.m22 / rhs
    };
}
#else
;
#endif
/// @brief Addition of two i64m3x3 with lhs scaled by a i64
SL_header i64m3x3 SL_i64m3x3addS(i64m3x3 lhs, i64m3x3 rhs, i64 s)
#if defined(SL_IMPLEMENTATION)
{
    return (i64m3x3) {
        .m00 = lhs.m00 + rhs.m00 * s, .m01 = lhs.m01 + rhs.m01 * s, .m02 = lhs.m02 + rhs.m02 * s,
        .m10 = lhs.m10 + rhs.m10 * s, .m11 = lhs.m11 + rhs.m11 * s, .m12 = lhs.m12 + rhs.m12 * s,
        .m20 = lhs.m20 + rhs.m20 * s, .m21 = lhs.m21 + rhs.m21 * s, .m22 = lhs.m22 + rhs.m22 * s
    };
}
#else
;
#endif
/// @brief Difference of two i64m3x3 with lhs scaled by a i64
SL_header i64m3x3 SL_i64m3x3subS(i64m3x3 lhs, i64m3x3 rhs, i64 s)
#if defined(SL_IMPLEMENTATION)
{
    return (i64m3x3) {
        .m00 = lhs.m00 - rhs.m00 * s, .m01 = lhs.m01 - rhs.m01 * s, .m02 = lhs.m02 - rhs.m02 * s,
        .m10 = lhs.m10 - rhs.m10 * s, .m11 = lhs.m11 - rhs.m11 * s, .m12 = lhs.m12 - rhs.m12 * s,
        .m20 = lhs.m20 - rhs.m20 * s, .m21 = lhs.m21 - rhs.m21 * s, .m22 = lhs.m22 - rhs.m22 * s
    };
}
#else
;
#endif
/// @brief Negation of a i64m3x3
SL_header i64m3x3 SL_i64m3x3neg(i64m3x3 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i64m3x3) {
        .m00 = -m.m00, .m01 = -m.m01, .m02 = -m.m02,
        .m10 = -m.m10, .m11 = -m.m11, .m12 = -m.m12,
        .m20 = -m.m20, .m21 = -m.m21, .m22 = -m.m22
    };
}
#else
;
#endif
/// @brief Component-wise absolute value of a i64m3x3
SL_header i64m3x3 SL_i64m3x3abs(i64m3x3 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i64m3x3) {
        .m00 = m.m00 < 0 ? -m.m00 : m.m00, .m01 = m.m01 < 0 ? -m.m01 : m.m01, .m02 = m.m02 < 0 ? -m.m02 : m.m02,
        .m10 = m.m10 < 0 ? -m.m10 : m.m10, .m11 = m.m11 < 0 ? -m.m11 : m.m11, .m12 = m.m12 < 0 ? -m.m12 : m.m12,
        .m20 = m.m20 < 0 ? -m.m20 : m.m20, .m21 = m.m21 < 0 ? -m.m21 : m.m21, .m22 = m.m22 < 0 ? -m.m22 : m.m22
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two i64m3x3
SL_header i64m3x3 SL_i64m3x3min(i64m3x3 lhs, i64m3x3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64m3x3) {
        .m00 = lhs.m00 < rhs.m00 ? lhs.m00 : rhs.m00, .m01 = lhs.m01 < rhs.m01 ? lhs.m01 : rhs.m01, .m02 = lhs.m02 < rhs.m02 ? lhs.m02 : rhs.m02,
        .m10 = lhs.m10 < rhs.m10 ? lhs.m10 : rhs.m10, .m11 = lhs.m11 < rhs.m11 ? lhs.m11 : rhs.m11, .m12 = lhs.m12 < rhs.m12 ? lhs.m12 : rhs.m12,
        .m20 = lhs.m20 < rhs.m20 ? lhs.m20 : rhs.m20, .m21 = lhs.m21 < rhs.m21 ? lhs.m21 : rhs.m21, .m22 = lhs.m22 < rhs.m22 ? lhs.m22 : rhs.m22
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two i64m3x3
SL_header i64m3x3 SL_i64m3x3max(i64m3x3 lhs, i64m3x3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64m3x3) {
        .m00 = lhs.m00 > rhs.m00 ? lhs.m00 : rhs.m00, .m01 = lhs.m01 > rhs.m01 ? lhs.m01 : rhs.m01, .m02 = lhs.m02 > rhs.m02 ? lhs.m02 : rhs.m02,
        .m10 = lhs.m10 > rhs.m10 ? lhs.m10 : rhs.m10, .m11 = lhs.m11 > rhs.m11 ? lhs.m11 : rhs.m11, .m12 = lhs.m12 > rhs.m12 ? lhs.m12 : rhs.m12,
        .m20 = lhs.m20 > rhs.m20 ? lhs.m20 : rhs.m20, .m21 = lhs.m21 > rhs.m21 ? lhs.m21 : rhs.m21, .m22 = lhs.m22 > rhs.m22 ? lhs.m22 : rhs.m22
    };
}
#else
;
#endif
/// @brief Transposition of a i64m3x3
SL_header i64m3x3 SL_i64m3x3trsp(i64m3x3 m)
#if defined(SL_IMPLEMENTATION)
{
    SL_swap(m.m10, m.m01);
    SL_swap(m.m20, m.m02); SL_swap(m.m21, m.m12);
    return m;
}
#else
;
#endif
/// @brief Trace of a i64m3x3
SL_header i64 SL_i64m3x3trace(i64m3x3 m)
#if defined(SL_IMPLEMENTATION)
{
    return m.m00 + m.m11 + m.m22;
}
#else
;
#endif
/// @brief Determinant of a i64m3x3
SL_header i64 SL_i64m3x3det_xpd(i64 m00, i64 m01, i64 m02, i64 m10, i64 m11, i64 m12, i64 m20, i64 m21, i64 m22)
#if defined(SL_IMPLEMENTATION)
{
    return m00 * m11 * m22 + m01 * m12 * m20 + m02 * m10 * m21 - m02 * m11 * m20 - m12 * m21 * m00 - m22 * m01 * m10;
}
#else
;
#endif
/// @brief Determinant of a i64m3x3
SL_header i64 SL_i64m3x3det(i64m3x3 m)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i64m3x3det_xpd(SL_XPD_M3X3(m));
}
#else
;
#endif



/// @brief Matrix of i64 of size 4 x 4
typedef union {
    i64 data[4 * 4];
    i64 m[4][4];
    struct {
        i64 m00, m01, m02, m03;
        i64 m10, m11, m12, m13;
        i64 m20, m21, m22, m23;
        i64 m30, m31, m32, m33;
    };
    struct { i64v4 r0, r1, r2, r3; };
} i64m4x4;

#define SL_i64m4x4_zero ((i64m4x4){0})
#define SL_i64m4x4_identity ((i64m4x4){ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 })


#define SL_i64m4x4diag(m00_, m11_, m22_, m33_) ((i64m4x4){.m00 = m00_, .m11 = m11_, .m22 = m22_, .m33 = m33_})

/// @brief Addition of two i64m4x4
SL_header i64m4x4 SL_i64m4x4add(i64m4x4 lhs, i64m4x4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64m4x4) {
        .m00 = lhs.m00 + rhs.m00, .m01 = lhs.m01 + rhs.m01, .m02 = lhs.m02 + rhs.m02, .m03 = lhs.m03 + rhs.m03,
        .m10 = lhs.m10 + rhs.m10, .m11 = lhs.m11 + rhs.m11, .m12 = lhs.m12 + rhs.m12, .m13 = lhs.m13 + rhs.m13,
        .m20 = lhs.m20 + rhs.m20, .m21 = lhs.m21 + rhs.m21, .m22 = lhs.m22 + rhs.m22, .m23 = lhs.m23 + rhs.m23,
        .m30 = lhs.m30 + rhs.m30, .m31 = lhs.m31 + rhs.m31, .m32 = lhs.m32 + rhs.m32, .m33 = lhs.m33 + rhs.m33
    };
}
#else
;
#endif
/// @brief Difference of two i64m4x4
SL_header i64m4x4 SL_i64m4x4sub(i64m4x4 lhs, i64m4x4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64m4x4) {
        .m00 = lhs.m00 - rhs.m00, .m01 = lhs.m01 - rhs.m01, .m02 = lhs.m02 - rhs.m02, .m03 = lhs.m03 - rhs.m03,
        .m10 = lhs.m10 - rhs.m10, .m11 = lhs.m11 - rhs.m11, .m12 = lhs.m12 - rhs.m12, .m13 = lhs.m13 - rhs.m13,
        .m20 = lhs.m20 - rhs.m20, .m21 = lhs.m21 - rhs.m21, .m22 = lhs.m22 - rhs.m22, .m23 = lhs.m23 - rhs.m23,
        .m30 = lhs.m30 - rhs.m30, .m31 = lhs.m31 - rhs.m31, .m32 = lhs.m32 - rhs.m32, .m33 = lhs.m33 - rhs.m33
    };
}
#else
;
#endif
/// @brief Product of two i64m4x4
SL_header i64m4x4 SL_i64m4x4mul(i64m4x4 lhs, i64m4x4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    i64m4x4 res = SL_i64m4x4_zero;
    for (usize k = 0; k < SL_msize(lhs).x; ++k)
    for (usize j = 0; j < SL_msize(lhs).y; ++j)
    for (usize i = 0; i < SL_msize(lhs).x; ++i)
        res.m[i][j] += lhs.m[i][k] * rhs.m[k][j];

    return res;
}
#else
;
#endif
/// @brief Component-wise multiplication of a i64m4x4 with a scalar
SL_header i64m4x4 SL_i64m4x4muls(i64m4x4 lhs, i64 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64m4x4) {
        .m00 = lhs.m00 * rhs, .m01 = lhs.m01 * rhs, .m02 = lhs.m02 * rhs, .m03 = lhs.m03 * rhs,
        .m10 = lhs.m10 * rhs, .m11 = lhs.m11 * rhs, .m12 = lhs.m12 * rhs, .m13 = lhs.m13 * rhs,
        .m20 = lhs.m20 * rhs, .m21 = lhs.m21 * rhs, .m22 = lhs.m22 * rhs, .m23 = lhs.m23 * rhs,
        .m30 = lhs.m30 * rhs, .m31 = lhs.m31 * rhs, .m32 = lhs.m32 * rhs, .m33 = lhs.m33 * rhs
    };
}
#else
;
#endif
/// @brief Product of a i64m4x4 and a i64v4
SL_header i64v4 SL_i64m4x4mulv(i64m4x4 lhs, i64v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i64v4_(SL_i64v4dot(lhs.r0, rhs), SL_i64v4dot(lhs.r1, rhs), SL_i64v4dot(lhs.r2, rhs), SL_i64v4dot(lhs.r3, rhs));
}
#else
;
#endif
/// @brief Apply transformation represented by i64m4x4 to a i64v3
SL_header i64v3 SL_i64m4x4apply(i64m4x4 m, i64v3 v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i64m4x4mulv(m, SL_i64v4v(v, 1)).xyz;
}
#else
;
#endif
/// @brief Component-wise division of a i64m4x4 with a scalar
SL_header i64m4x4 SL_i64m4x4divs(i64m4x4 lhs, i64 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64m4x4) {
        .m00 = lhs.m00 / rhs, .m01 = lhs.m01 / rhs, .m02 = lhs.m02 / rhs, .m03 = lhs.m03 / rhs,
        .m10 = lhs.m10 / rhs, .m11 = lhs.m11 / rhs, .m12 = lhs.m12 / rhs, .m13 = lhs.m13 / rhs,
        .m20 = lhs.m20 / rhs, .m21 = lhs.m21 / rhs, .m22 = lhs.m22 / rhs, .m23 = lhs.m23 / rhs,
        .m30 = lhs.m30 / rhs, .m31 = lhs.m31 / rhs, .m32 = lhs.m32 / rhs, .m33 = lhs.m33 / rhs
    };
}
#else
;
#endif
/// @brief Addition of two i64m4x4 with lhs scaled by a i64
SL_header i64m4x4 SL_i64m4x4addS(i64m4x4 lhs, i64m4x4 rhs, i64 s)
#if defined(SL_IMPLEMENTATION)
{
    return (i64m4x4) {
        .m00 = lhs.m00 + rhs.m00 * s, .m01 = lhs.m01 + rhs.m01 * s, .m02 = lhs.m02 + rhs.m02 * s, .m03 = lhs.m03 + rhs.m03 * s,
        .m10 = lhs.m10 + rhs.m10 * s, .m11 = lhs.m11 + rhs.m11 * s, .m12 = lhs.m12 + rhs.m12 * s, .m13 = lhs.m13 + rhs.m13 * s,
        .m20 = lhs.m20 + rhs.m20 * s, .m21 = lhs.m21 + rhs.m21 * s, .m22 = lhs.m22 + rhs.m22 * s, .m23 = lhs.m23 + rhs.m23 * s,
        .m30 = lhs.m30 + rhs.m30 * s, .m31 = lhs.m31 + rhs.m31 * s, .m32 = lhs.m32 + rhs.m32 * s, .m33 = lhs.m33 + rhs.m33 * s
    };
}
#else
;
#endif
/// @brief Difference of two i64m4x4 with lhs scaled by a i64
SL_header i64m4x4 SL_i64m4x4subS(i64m4x4 lhs, i64m4x4 rhs, i64 s)
#if defined(SL_IMPLEMENTATION)
{
    return (i64m4x4) {
        .m00 = lhs.m00 - rhs.m00 * s, .m01 = lhs.m01 - rhs.m01 * s, .m02 = lhs.m02 - rhs.m02 * s, .m03 = lhs.m03 - rhs.m03 * s,
        .m10 = lhs.m10 - rhs.m10 * s, .m11 = lhs.m11 - rhs.m11 * s, .m12 = lhs.m12 - rhs.m12 * s, .m13 = lhs.m13 - rhs.m13 * s,
        .m20 = lhs.m20 - rhs.m20 * s, .m21 = lhs.m21 - rhs.m21 * s, .m22 = lhs.m22 - rhs.m22 * s, .m23 = lhs.m23 - rhs.m23 * s,
        .m30 = lhs.m30 - rhs.m30 * s, .m31 = lhs.m31 - rhs.m31 * s, .m32 = lhs.m32 - rhs.m32 * s, .m33 = lhs.m33 - rhs.m33 * s
    };
}
#else
;
#endif
/// @brief Negation of a i64m4x4
SL_header i64m4x4 SL_i64m4x4neg(i64m4x4 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i64m4x4) {
        .m00 = -m.m00, .m01 = -m.m01, .m02 = -m.m02, .m03 = -m.m03,
        .m10 = -m.m10, .m11 = -m.m11, .m12 = -m.m12, .m13 = -m.m13,
        .m20 = -m.m20, .m21 = -m.m21, .m22 = -m.m22, .m23 = -m.m23,
        .m30 = -m.m30, .m31 = -m.m31, .m32 = -m.m32, .m33 = -m.m33
    };
}
#else
;
#endif
/// @brief Component-wise absolute value of a i64m4x4
SL_header i64m4x4 SL_i64m4x4abs(i64m4x4 m)
#if defined(SL_IMPLEMENTATION)
{
    return (i64m4x4) {
        .m00 = m.m00 < 0 ? -m.m00 : m.m00, .m01 = m.m01 < 0 ? -m.m01 : m.m01, .m02 = m.m02 < 0 ? -m.m02 : m.m02, .m03 = m.m03 < 0 ? -m.m03 : m.m03,
        .m10 = m.m10 < 0 ? -m.m10 : m.m10, .m11 = m.m11 < 0 ? -m.m11 : m.m11, .m12 = m.m12 < 0 ? -m.m12 : m.m12, .m13 = m.m13 < 0 ? -m.m13 : m.m13,
        .m20 = m.m20 < 0 ? -m.m20 : m.m20, .m21 = m.m21 < 0 ? -m.m21 : m.m21, .m22 = m.m22 < 0 ? -m.m22 : m.m22, .m23 = m.m23 < 0 ? -m.m23 : m.m23,
        .m30 = m.m30 < 0 ? -m.m30 : m.m30, .m31 = m.m31 < 0 ? -m.m31 : m.m31, .m32 = m.m32 < 0 ? -m.m32 : m.m32, .m33 = m.m33 < 0 ? -m.m33 : m.m33
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two i64m4x4
SL_header i64m4x4 SL_i64m4x4min(i64m4x4 lhs, i64m4x4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64m4x4) {
        .m00 = lhs.m00 < rhs.m00 ? lhs.m00 : rhs.m00, .m01 = lhs.m01 < rhs.m01 ? lhs.m01 : rhs.m01, .m02 = lhs.m02 < rhs.m02 ? lhs.m02 : rhs.m02, .m03 = lhs.m03 < rhs.m03 ? lhs.m03 : rhs.m03,
        .m10 = lhs.m10 < rhs.m10 ? lhs.m10 : rhs.m10, .m11 = lhs.m11 < rhs.m11 ? lhs.m11 : rhs.m11, .m12 = lhs.m12 < rhs.m12 ? lhs.m12 : rhs.m12, .m13 = lhs.m13 < rhs.m13 ? lhs.m13 : rhs.m13,
        .m20 = lhs.m20 < rhs.m20 ? lhs.m20 : rhs.m20, .m21 = lhs.m21 < rhs.m21 ? lhs.m21 : rhs.m21, .m22 = lhs.m22 < rhs.m22 ? lhs.m22 : rhs.m22, .m23 = lhs.m23 < rhs.m23 ? lhs.m23 : rhs.m23,
        .m30 = lhs.m30 < rhs.m30 ? lhs.m30 : rhs.m30, .m31 = lhs.m31 < rhs.m31 ? lhs.m31 : rhs.m31, .m32 = lhs.m32 < rhs.m32 ? lhs.m32 : rhs.m32, .m33 = lhs.m33 < rhs.m33 ? lhs.m33 : rhs.m33
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two i64m4x4
SL_header i64m4x4 SL_i64m4x4max(i64m4x4 lhs, i64m4x4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (i64m4x4) {
        .m00 = lhs.m00 > rhs.m00 ? lhs.m00 : rhs.m00, .m01 = lhs.m01 > rhs.m01 ? lhs.m01 : rhs.m01, .m02 = lhs.m02 > rhs.m02 ? lhs.m02 : rhs.m02, .m03 = lhs.m03 > rhs.m03 ? lhs.m03 : rhs.m03,
        .m10 = lhs.m10 > rhs.m10 ? lhs.m10 : rhs.m10, .m11 = lhs.m11 > rhs.m11 ? lhs.m11 : rhs.m11, .m12 = lhs.m12 > rhs.m12 ? lhs.m12 : rhs.m12, .m13 = lhs.m13 > rhs.m13 ? lhs.m13 : rhs.m13,
        .m20 = lhs.m20 > rhs.m20 ? lhs.m20 : rhs.m20, .m21 = lhs.m21 > rhs.m21 ? lhs.m21 : rhs.m21, .m22 = lhs.m22 > rhs.m22 ? lhs.m22 : rhs.m22, .m23 = lhs.m23 > rhs.m23 ? lhs.m23 : rhs.m23,
        .m30 = lhs.m30 > rhs.m30 ? lhs.m30 : rhs.m30, .m31 = lhs.m31 > rhs.m31 ? lhs.m31 : rhs.m31, .m32 = lhs.m32 > rhs.m32 ? lhs.m32 : rhs.m32, .m33 = lhs.m33 > rhs.m33 ? lhs.m33 : rhs.m33
    };
}
#else
;
#endif
/// @brief Transposition of a i64m4x4
SL_header i64m4x4 SL_i64m4x4trsp(i64m4x4 m)
#if defined(SL_IMPLEMENTATION)
{
    SL_swap(m.m10, m.m01);
    SL_swap(m.m20, m.m02); SL_swap(m.m12, m.m21);
    SL_swap(m.m30, m.m03); SL_swap(m.m31, m.m13);SL_swap(m.m32, m.m23);
    return m;
}
#else
;
#endif
/// @brief Trace of a i64m4x4
SL_header i64 SL_i64m4x4trace(i64m4x4 m)
#if defined(SL_IMPLEMENTATION)
{
    return m.m00 + m.m11 + m.m22 + m.m33;
}
#else
;
#endif
/// @brief Determinant of a i64m4x4
SL_header i64 SL_i64m4x4det_xpd(i64 m00, i64 m01, i64 m02, i64 m03, i64 m10, i64 m11, i64 m12, i64 m13, i64 m20, i64 m21, i64 m22, i64 m23, i64 m30, i64 m31, i64 m32, i64 m33)
#if defined(SL_IMPLEMENTATION)
{
    return m00 * SL_i64m3x3det_xpd(m11, m12, m13, m21, m22, m23, m31, m32, m33)
         + m01 * SL_i64m3x3det_xpd(m10, m12, m13, m20, m22, m23, m30, m32, m33)
         + m02 * SL_i64m3x3det_xpd(m10, m11, m13, m20, m21, m23, m30, m31, m33)
         + m03 * SL_i64m3x3det_xpd(m10, m11, m12, m20, m21, m22, m30, m31, m32);
}
#else
;
#endif
/// @brief Determinant of a i64m4x4
SL_header i64 SL_i64m4x4det(i64m4x4 m)
#if defined(SL_IMPLEMENTATION)
{
    return SL_i64m4x4det_xpd(SL_XPD_M4X4(m));
}
#else
;
#endif



#pragma endregion I64
#pragma region U32

/// @brief Matrix of u32 with arbitrary dimensions
typedef struct {
    union { usize r, c; luv2 size; };
    u32 *data;
} u32m;

#define SL_asu32m(sized_mat) ((u32m){.size = SL_msize(sized_mat), .data = sized_mat.data})





/// @brief Matrix of u32 of size 2 x 2
typedef union {
    u32 data[2 * 2];
    u32 m[2][2];
    struct {
        u32 m00, m01;
        u32 m10, m11;
    };
    struct { u32v2 r0, r1; };
} u32m2x2;

#define SL_u32m2x2_zero ((u32m2x2){0})
#define SL_u32m2x2_identity ((u32m2x2){ 1, 0, 0, 1 })


#define SL_u32m2x2diag(m00_, m11_) ((u32m2x2){.m00 = m00_, .m11 = m11_})

/// @brief Addition of two u32m2x2
SL_header u32m2x2 SL_u32m2x2add(u32m2x2 lhs, u32m2x2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32m2x2) {
        .m00 = lhs.m00 + rhs.m00, .m01 = lhs.m01 + rhs.m01,
        .m10 = lhs.m10 + rhs.m10, .m11 = lhs.m11 + rhs.m11
    };
}
#else
;
#endif
/// @brief Difference of two u32m2x2
SL_header u32m2x2 SL_u32m2x2sub(u32m2x2 lhs, u32m2x2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32m2x2) {
        .m00 = lhs.m00 - rhs.m00, .m01 = lhs.m01 - rhs.m01,
        .m10 = lhs.m10 - rhs.m10, .m11 = lhs.m11 - rhs.m11
    };
}
#else
;
#endif
/// @brief Product of two u32m2x2
SL_header u32m2x2 SL_u32m2x2mul(u32m2x2 lhs, u32m2x2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    u32m2x2 res = SL_u32m2x2_zero;
    for (usize k = 0; k < SL_msize(lhs).x; ++k)
    for (usize j = 0; j < SL_msize(lhs).y; ++j)
    for (usize i = 0; i < SL_msize(lhs).x; ++i)
        res.m[i][j] += lhs.m[i][k] * rhs.m[k][j];

    return res;
}
#else
;
#endif
/// @brief Component-wise multiplication of a u32m2x2 with a scalar
SL_header u32m2x2 SL_u32m2x2muls(u32m2x2 lhs, u32 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32m2x2) {
        .m00 = lhs.m00 * rhs, .m01 = lhs.m01 * rhs,
        .m10 = lhs.m10 * rhs, .m11 = lhs.m11 * rhs
    };
}
#else
;
#endif
/// @brief Product of a u32m2x2 and a u32v2
SL_header u32v2 SL_u32m2x2mulv(u32m2x2 lhs, u32v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u32v2_(SL_u32v2dot(lhs.r0, rhs), SL_u32v2dot(lhs.r1, rhs));
}
#else
;
#endif
/// @brief Component-wise division of a u32m2x2 with a scalar
SL_header u32m2x2 SL_u32m2x2divs(u32m2x2 lhs, u32 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32m2x2) {
        .m00 = lhs.m00 / rhs, .m01 = lhs.m01 / rhs,
        .m10 = lhs.m10 / rhs, .m11 = lhs.m11 / rhs
    };
}
#else
;
#endif
/// @brief Addition of two u32m2x2 with lhs scaled by a u32
SL_header u32m2x2 SL_u32m2x2addS(u32m2x2 lhs, u32m2x2 rhs, u32 s)
#if defined(SL_IMPLEMENTATION)
{
    return (u32m2x2) {
        .m00 = lhs.m00 + rhs.m00 * s, .m01 = lhs.m01 + rhs.m01 * s,
        .m10 = lhs.m10 + rhs.m10 * s, .m11 = lhs.m11 + rhs.m11 * s
    };
}
#else
;
#endif
/// @brief Difference of two u32m2x2 with lhs scaled by a u32
SL_header u32m2x2 SL_u32m2x2subS(u32m2x2 lhs, u32m2x2 rhs, u32 s)
#if defined(SL_IMPLEMENTATION)
{
    return (u32m2x2) {
        .m00 = lhs.m00 - rhs.m00 * s, .m01 = lhs.m01 - rhs.m01 * s,
        .m10 = lhs.m10 - rhs.m10 * s, .m11 = lhs.m11 - rhs.m11 * s
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two u32m2x2
SL_header u32m2x2 SL_u32m2x2min(u32m2x2 lhs, u32m2x2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32m2x2) {
        .m00 = lhs.m00 < rhs.m00 ? lhs.m00 : rhs.m00, .m01 = lhs.m01 < rhs.m01 ? lhs.m01 : rhs.m01,
        .m10 = lhs.m10 < rhs.m10 ? lhs.m10 : rhs.m10, .m11 = lhs.m11 < rhs.m11 ? lhs.m11 : rhs.m11
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two u32m2x2
SL_header u32m2x2 SL_u32m2x2max(u32m2x2 lhs, u32m2x2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32m2x2) {
        .m00 = lhs.m00 > rhs.m00 ? lhs.m00 : rhs.m00, .m01 = lhs.m01 > rhs.m01 ? lhs.m01 : rhs.m01,
        .m10 = lhs.m10 > rhs.m10 ? lhs.m10 : rhs.m10, .m11 = lhs.m11 > rhs.m11 ? lhs.m11 : rhs.m11
    };
}
#else
;
#endif
/// @brief Transposition of a u32m2x2
SL_header u32m2x2 SL_u32m2x2trsp(u32m2x2 m)
#if defined(SL_IMPLEMENTATION)
{
    SL_swap(m.m10, m.m01);
    return m;
}
#else
;
#endif
/// @brief Trace of a u32m2x2
SL_header u32 SL_u32m2x2trace(u32m2x2 m)
#if defined(SL_IMPLEMENTATION)
{
    return m.m00 + m.m11;
}
#else
;
#endif
/// @brief Determinant of a u32m2x2
SL_header u32 SL_u32m2x2det_xpd(u32 m00, u32 m01, u32 m10, u32 m11)
#if defined(SL_IMPLEMENTATION)
{
    return m00 * m11 - m01 * m10;
}
#else
;
#endif
/// @brief Determinant of a u32m2x2
SL_header u32 SL_u32m2x2det(u32m2x2 m)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u32m2x2det_xpd(SL_XPD_M2X2(m));
}
#else
;
#endif



/// @brief Matrix of u32 of size 3 x 3
typedef union {
    u32 data[3 * 3];
    u32 m[3][3];
    struct {
        u32 m00, m01, m02;
        u32 m10, m11, m12;
        u32 m20, m21, m22;
    };
    struct { u32v3 r0, r1, r2; };
} u32m3x3;

#define SL_u32m3x3_zero ((u32m3x3){0})
#define SL_u32m3x3_identity ((u32m3x3){ 1, 0, 0, 0, 1, 0, 0, 0, 1 })


#define SL_u32m3x3diag(m00_, m11_, m22_) ((u32m3x3){.m00 = m00_, .m11 = m11_, .m22 = m22_})

/// @brief Addition of two u32m3x3
SL_header u32m3x3 SL_u32m3x3add(u32m3x3 lhs, u32m3x3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32m3x3) {
        .m00 = lhs.m00 + rhs.m00, .m01 = lhs.m01 + rhs.m01, .m02 = lhs.m02 + rhs.m02,
        .m10 = lhs.m10 + rhs.m10, .m11 = lhs.m11 + rhs.m11, .m12 = lhs.m12 + rhs.m12,
        .m20 = lhs.m20 + rhs.m20, .m21 = lhs.m21 + rhs.m21, .m22 = lhs.m22 + rhs.m22
    };
}
#else
;
#endif
/// @brief Difference of two u32m3x3
SL_header u32m3x3 SL_u32m3x3sub(u32m3x3 lhs, u32m3x3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32m3x3) {
        .m00 = lhs.m00 - rhs.m00, .m01 = lhs.m01 - rhs.m01, .m02 = lhs.m02 - rhs.m02,
        .m10 = lhs.m10 - rhs.m10, .m11 = lhs.m11 - rhs.m11, .m12 = lhs.m12 - rhs.m12,
        .m20 = lhs.m20 - rhs.m20, .m21 = lhs.m21 - rhs.m21, .m22 = lhs.m22 - rhs.m22
    };
}
#else
;
#endif
/// @brief Product of two u32m3x3
SL_header u32m3x3 SL_u32m3x3mul(u32m3x3 lhs, u32m3x3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    u32m3x3 res = SL_u32m3x3_zero;
    for (usize k = 0; k < SL_msize(lhs).x; ++k)
    for (usize j = 0; j < SL_msize(lhs).y; ++j)
    for (usize i = 0; i < SL_msize(lhs).x; ++i)
        res.m[i][j] += lhs.m[i][k] * rhs.m[k][j];

    return res;
}
#else
;
#endif
/// @brief Component-wise multiplication of a u32m3x3 with a scalar
SL_header u32m3x3 SL_u32m3x3muls(u32m3x3 lhs, u32 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32m3x3) {
        .m00 = lhs.m00 * rhs, .m01 = lhs.m01 * rhs, .m02 = lhs.m02 * rhs,
        .m10 = lhs.m10 * rhs, .m11 = lhs.m11 * rhs, .m12 = lhs.m12 * rhs,
        .m20 = lhs.m20 * rhs, .m21 = lhs.m21 * rhs, .m22 = lhs.m22 * rhs
    };
}
#else
;
#endif
/// @brief Product of a u32m3x3 and a u32v3
SL_header u32v3 SL_u32m3x3mulv(u32m3x3 lhs, u32v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u32v3_(SL_u32v3dot(lhs.r0, rhs), SL_u32v3dot(lhs.r1, rhs), SL_u32v3dot(lhs.r2, rhs));
}
#else
;
#endif
/// @brief Apply transformation represented by u32m3x3 to a u32v2
SL_header u32v2 SL_u32m3x3apply(u32m3x3 m, u32v2 v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u32m3x3mulv(m, SL_u32v3v(v, 1)).xy;
}
#else
;
#endif
/// @brief Component-wise division of a u32m3x3 with a scalar
SL_header u32m3x3 SL_u32m3x3divs(u32m3x3 lhs, u32 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32m3x3) {
        .m00 = lhs.m00 / rhs, .m01 = lhs.m01 / rhs, .m02 = lhs.m02 / rhs,
        .m10 = lhs.m10 / rhs, .m11 = lhs.m11 / rhs, .m12 = lhs.m12 / rhs,
        .m20 = lhs.m20 / rhs, .m21 = lhs.m21 / rhs, .m22 = lhs.m22 / rhs
    };
}
#else
;
#endif
/// @brief Addition of two u32m3x3 with lhs scaled by a u32
SL_header u32m3x3 SL_u32m3x3addS(u32m3x3 lhs, u32m3x3 rhs, u32 s)
#if defined(SL_IMPLEMENTATION)
{
    return (u32m3x3) {
        .m00 = lhs.m00 + rhs.m00 * s, .m01 = lhs.m01 + rhs.m01 * s, .m02 = lhs.m02 + rhs.m02 * s,
        .m10 = lhs.m10 + rhs.m10 * s, .m11 = lhs.m11 + rhs.m11 * s, .m12 = lhs.m12 + rhs.m12 * s,
        .m20 = lhs.m20 + rhs.m20 * s, .m21 = lhs.m21 + rhs.m21 * s, .m22 = lhs.m22 + rhs.m22 * s
    };
}
#else
;
#endif
/// @brief Difference of two u32m3x3 with lhs scaled by a u32
SL_header u32m3x3 SL_u32m3x3subS(u32m3x3 lhs, u32m3x3 rhs, u32 s)
#if defined(SL_IMPLEMENTATION)
{
    return (u32m3x3) {
        .m00 = lhs.m00 - rhs.m00 * s, .m01 = lhs.m01 - rhs.m01 * s, .m02 = lhs.m02 - rhs.m02 * s,
        .m10 = lhs.m10 - rhs.m10 * s, .m11 = lhs.m11 - rhs.m11 * s, .m12 = lhs.m12 - rhs.m12 * s,
        .m20 = lhs.m20 - rhs.m20 * s, .m21 = lhs.m21 - rhs.m21 * s, .m22 = lhs.m22 - rhs.m22 * s
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two u32m3x3
SL_header u32m3x3 SL_u32m3x3min(u32m3x3 lhs, u32m3x3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32m3x3) {
        .m00 = lhs.m00 < rhs.m00 ? lhs.m00 : rhs.m00, .m01 = lhs.m01 < rhs.m01 ? lhs.m01 : rhs.m01, .m02 = lhs.m02 < rhs.m02 ? lhs.m02 : rhs.m02,
        .m10 = lhs.m10 < rhs.m10 ? lhs.m10 : rhs.m10, .m11 = lhs.m11 < rhs.m11 ? lhs.m11 : rhs.m11, .m12 = lhs.m12 < rhs.m12 ? lhs.m12 : rhs.m12,
        .m20 = lhs.m20 < rhs.m20 ? lhs.m20 : rhs.m20, .m21 = lhs.m21 < rhs.m21 ? lhs.m21 : rhs.m21, .m22 = lhs.m22 < rhs.m22 ? lhs.m22 : rhs.m22
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two u32m3x3
SL_header u32m3x3 SL_u32m3x3max(u32m3x3 lhs, u32m3x3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32m3x3) {
        .m00 = lhs.m00 > rhs.m00 ? lhs.m00 : rhs.m00, .m01 = lhs.m01 > rhs.m01 ? lhs.m01 : rhs.m01, .m02 = lhs.m02 > rhs.m02 ? lhs.m02 : rhs.m02,
        .m10 = lhs.m10 > rhs.m10 ? lhs.m10 : rhs.m10, .m11 = lhs.m11 > rhs.m11 ? lhs.m11 : rhs.m11, .m12 = lhs.m12 > rhs.m12 ? lhs.m12 : rhs.m12,
        .m20 = lhs.m20 > rhs.m20 ? lhs.m20 : rhs.m20, .m21 = lhs.m21 > rhs.m21 ? lhs.m21 : rhs.m21, .m22 = lhs.m22 > rhs.m22 ? lhs.m22 : rhs.m22
    };
}
#else
;
#endif
/// @brief Transposition of a u32m3x3
SL_header u32m3x3 SL_u32m3x3trsp(u32m3x3 m)
#if defined(SL_IMPLEMENTATION)
{
    SL_swap(m.m10, m.m01);
    SL_swap(m.m20, m.m02); SL_swap(m.m21, m.m12);
    return m;
}
#else
;
#endif
/// @brief Trace of a u32m3x3
SL_header u32 SL_u32m3x3trace(u32m3x3 m)
#if defined(SL_IMPLEMENTATION)
{
    return m.m00 + m.m11 + m.m22;
}
#else
;
#endif
/// @brief Determinant of a u32m3x3
SL_header u32 SL_u32m3x3det_xpd(u32 m00, u32 m01, u32 m02, u32 m10, u32 m11, u32 m12, u32 m20, u32 m21, u32 m22)
#if defined(SL_IMPLEMENTATION)
{
    return m00 * m11 * m22 + m01 * m12 * m20 + m02 * m10 * m21 - m02 * m11 * m20 - m12 * m21 * m00 - m22 * m01 * m10;
}
#else
;
#endif
/// @brief Determinant of a u32m3x3
SL_header u32 SL_u32m3x3det(u32m3x3 m)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u32m3x3det_xpd(SL_XPD_M3X3(m));
}
#else
;
#endif



/// @brief Matrix of u32 of size 4 x 4
typedef union {
    u32 data[4 * 4];
    u32 m[4][4];
    struct {
        u32 m00, m01, m02, m03;
        u32 m10, m11, m12, m13;
        u32 m20, m21, m22, m23;
        u32 m30, m31, m32, m33;
    };
    struct { u32v4 r0, r1, r2, r3; };
} u32m4x4;

#define SL_u32m4x4_zero ((u32m4x4){0})
#define SL_u32m4x4_identity ((u32m4x4){ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 })


#define SL_u32m4x4diag(m00_, m11_, m22_, m33_) ((u32m4x4){.m00 = m00_, .m11 = m11_, .m22 = m22_, .m33 = m33_})

/// @brief Addition of two u32m4x4
SL_header u32m4x4 SL_u32m4x4add(u32m4x4 lhs, u32m4x4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32m4x4) {
        .m00 = lhs.m00 + rhs.m00, .m01 = lhs.m01 + rhs.m01, .m02 = lhs.m02 + rhs.m02, .m03 = lhs.m03 + rhs.m03,
        .m10 = lhs.m10 + rhs.m10, .m11 = lhs.m11 + rhs.m11, .m12 = lhs.m12 + rhs.m12, .m13 = lhs.m13 + rhs.m13,
        .m20 = lhs.m20 + rhs.m20, .m21 = lhs.m21 + rhs.m21, .m22 = lhs.m22 + rhs.m22, .m23 = lhs.m23 + rhs.m23,
        .m30 = lhs.m30 + rhs.m30, .m31 = lhs.m31 + rhs.m31, .m32 = lhs.m32 + rhs.m32, .m33 = lhs.m33 + rhs.m33
    };
}
#else
;
#endif
/// @brief Difference of two u32m4x4
SL_header u32m4x4 SL_u32m4x4sub(u32m4x4 lhs, u32m4x4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32m4x4) {
        .m00 = lhs.m00 - rhs.m00, .m01 = lhs.m01 - rhs.m01, .m02 = lhs.m02 - rhs.m02, .m03 = lhs.m03 - rhs.m03,
        .m10 = lhs.m10 - rhs.m10, .m11 = lhs.m11 - rhs.m11, .m12 = lhs.m12 - rhs.m12, .m13 = lhs.m13 - rhs.m13,
        .m20 = lhs.m20 - rhs.m20, .m21 = lhs.m21 - rhs.m21, .m22 = lhs.m22 - rhs.m22, .m23 = lhs.m23 - rhs.m23,
        .m30 = lhs.m30 - rhs.m30, .m31 = lhs.m31 - rhs.m31, .m32 = lhs.m32 - rhs.m32, .m33 = lhs.m33 - rhs.m33
    };
}
#else
;
#endif
/// @brief Product of two u32m4x4
SL_header u32m4x4 SL_u32m4x4mul(u32m4x4 lhs, u32m4x4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    u32m4x4 res = SL_u32m4x4_zero;
    for (usize k = 0; k < SL_msize(lhs).x; ++k)
    for (usize j = 0; j < SL_msize(lhs).y; ++j)
    for (usize i = 0; i < SL_msize(lhs).x; ++i)
        res.m[i][j] += lhs.m[i][k] * rhs.m[k][j];

    return res;
}
#else
;
#endif
/// @brief Component-wise multiplication of a u32m4x4 with a scalar
SL_header u32m4x4 SL_u32m4x4muls(u32m4x4 lhs, u32 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32m4x4) {
        .m00 = lhs.m00 * rhs, .m01 = lhs.m01 * rhs, .m02 = lhs.m02 * rhs, .m03 = lhs.m03 * rhs,
        .m10 = lhs.m10 * rhs, .m11 = lhs.m11 * rhs, .m12 = lhs.m12 * rhs, .m13 = lhs.m13 * rhs,
        .m20 = lhs.m20 * rhs, .m21 = lhs.m21 * rhs, .m22 = lhs.m22 * rhs, .m23 = lhs.m23 * rhs,
        .m30 = lhs.m30 * rhs, .m31 = lhs.m31 * rhs, .m32 = lhs.m32 * rhs, .m33 = lhs.m33 * rhs
    };
}
#else
;
#endif
/// @brief Product of a u32m4x4 and a u32v4
SL_header u32v4 SL_u32m4x4mulv(u32m4x4 lhs, u32v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u32v4_(SL_u32v4dot(lhs.r0, rhs), SL_u32v4dot(lhs.r1, rhs), SL_u32v4dot(lhs.r2, rhs), SL_u32v4dot(lhs.r3, rhs));
}
#else
;
#endif
/// @brief Apply transformation represented by u32m4x4 to a u32v3
SL_header u32v3 SL_u32m4x4apply(u32m4x4 m, u32v3 v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u32m4x4mulv(m, SL_u32v4v(v, 1)).xyz;
}
#else
;
#endif
/// @brief Component-wise division of a u32m4x4 with a scalar
SL_header u32m4x4 SL_u32m4x4divs(u32m4x4 lhs, u32 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32m4x4) {
        .m00 = lhs.m00 / rhs, .m01 = lhs.m01 / rhs, .m02 = lhs.m02 / rhs, .m03 = lhs.m03 / rhs,
        .m10 = lhs.m10 / rhs, .m11 = lhs.m11 / rhs, .m12 = lhs.m12 / rhs, .m13 = lhs.m13 / rhs,
        .m20 = lhs.m20 / rhs, .m21 = lhs.m21 / rhs, .m22 = lhs.m22 / rhs, .m23 = lhs.m23 / rhs,
        .m30 = lhs.m30 / rhs, .m31 = lhs.m31 / rhs, .m32 = lhs.m32 / rhs, .m33 = lhs.m33 / rhs
    };
}
#else
;
#endif
/// @brief Addition of two u32m4x4 with lhs scaled by a u32
SL_header u32m4x4 SL_u32m4x4addS(u32m4x4 lhs, u32m4x4 rhs, u32 s)
#if defined(SL_IMPLEMENTATION)
{
    return (u32m4x4) {
        .m00 = lhs.m00 + rhs.m00 * s, .m01 = lhs.m01 + rhs.m01 * s, .m02 = lhs.m02 + rhs.m02 * s, .m03 = lhs.m03 + rhs.m03 * s,
        .m10 = lhs.m10 + rhs.m10 * s, .m11 = lhs.m11 + rhs.m11 * s, .m12 = lhs.m12 + rhs.m12 * s, .m13 = lhs.m13 + rhs.m13 * s,
        .m20 = lhs.m20 + rhs.m20 * s, .m21 = lhs.m21 + rhs.m21 * s, .m22 = lhs.m22 + rhs.m22 * s, .m23 = lhs.m23 + rhs.m23 * s,
        .m30 = lhs.m30 + rhs.m30 * s, .m31 = lhs.m31 + rhs.m31 * s, .m32 = lhs.m32 + rhs.m32 * s, .m33 = lhs.m33 + rhs.m33 * s
    };
}
#else
;
#endif
/// @brief Difference of two u32m4x4 with lhs scaled by a u32
SL_header u32m4x4 SL_u32m4x4subS(u32m4x4 lhs, u32m4x4 rhs, u32 s)
#if defined(SL_IMPLEMENTATION)
{
    return (u32m4x4) {
        .m00 = lhs.m00 - rhs.m00 * s, .m01 = lhs.m01 - rhs.m01 * s, .m02 = lhs.m02 - rhs.m02 * s, .m03 = lhs.m03 - rhs.m03 * s,
        .m10 = lhs.m10 - rhs.m10 * s, .m11 = lhs.m11 - rhs.m11 * s, .m12 = lhs.m12 - rhs.m12 * s, .m13 = lhs.m13 - rhs.m13 * s,
        .m20 = lhs.m20 - rhs.m20 * s, .m21 = lhs.m21 - rhs.m21 * s, .m22 = lhs.m22 - rhs.m22 * s, .m23 = lhs.m23 - rhs.m23 * s,
        .m30 = lhs.m30 - rhs.m30 * s, .m31 = lhs.m31 - rhs.m31 * s, .m32 = lhs.m32 - rhs.m32 * s, .m33 = lhs.m33 - rhs.m33 * s
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two u32m4x4
SL_header u32m4x4 SL_u32m4x4min(u32m4x4 lhs, u32m4x4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32m4x4) {
        .m00 = lhs.m00 < rhs.m00 ? lhs.m00 : rhs.m00, .m01 = lhs.m01 < rhs.m01 ? lhs.m01 : rhs.m01, .m02 = lhs.m02 < rhs.m02 ? lhs.m02 : rhs.m02, .m03 = lhs.m03 < rhs.m03 ? lhs.m03 : rhs.m03,
        .m10 = lhs.m10 < rhs.m10 ? lhs.m10 : rhs.m10, .m11 = lhs.m11 < rhs.m11 ? lhs.m11 : rhs.m11, .m12 = lhs.m12 < rhs.m12 ? lhs.m12 : rhs.m12, .m13 = lhs.m13 < rhs.m13 ? lhs.m13 : rhs.m13,
        .m20 = lhs.m20 < rhs.m20 ? lhs.m20 : rhs.m20, .m21 = lhs.m21 < rhs.m21 ? lhs.m21 : rhs.m21, .m22 = lhs.m22 < rhs.m22 ? lhs.m22 : rhs.m22, .m23 = lhs.m23 < rhs.m23 ? lhs.m23 : rhs.m23,
        .m30 = lhs.m30 < rhs.m30 ? lhs.m30 : rhs.m30, .m31 = lhs.m31 < rhs.m31 ? lhs.m31 : rhs.m31, .m32 = lhs.m32 < rhs.m32 ? lhs.m32 : rhs.m32, .m33 = lhs.m33 < rhs.m33 ? lhs.m33 : rhs.m33
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two u32m4x4
SL_header u32m4x4 SL_u32m4x4max(u32m4x4 lhs, u32m4x4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u32m4x4) {
        .m00 = lhs.m00 > rhs.m00 ? lhs.m00 : rhs.m00, .m01 = lhs.m01 > rhs.m01 ? lhs.m01 : rhs.m01, .m02 = lhs.m02 > rhs.m02 ? lhs.m02 : rhs.m02, .m03 = lhs.m03 > rhs.m03 ? lhs.m03 : rhs.m03,
        .m10 = lhs.m10 > rhs.m10 ? lhs.m10 : rhs.m10, .m11 = lhs.m11 > rhs.m11 ? lhs.m11 : rhs.m11, .m12 = lhs.m12 > rhs.m12 ? lhs.m12 : rhs.m12, .m13 = lhs.m13 > rhs.m13 ? lhs.m13 : rhs.m13,
        .m20 = lhs.m20 > rhs.m20 ? lhs.m20 : rhs.m20, .m21 = lhs.m21 > rhs.m21 ? lhs.m21 : rhs.m21, .m22 = lhs.m22 > rhs.m22 ? lhs.m22 : rhs.m22, .m23 = lhs.m23 > rhs.m23 ? lhs.m23 : rhs.m23,
        .m30 = lhs.m30 > rhs.m30 ? lhs.m30 : rhs.m30, .m31 = lhs.m31 > rhs.m31 ? lhs.m31 : rhs.m31, .m32 = lhs.m32 > rhs.m32 ? lhs.m32 : rhs.m32, .m33 = lhs.m33 > rhs.m33 ? lhs.m33 : rhs.m33
    };
}
#else
;
#endif
/// @brief Transposition of a u32m4x4
SL_header u32m4x4 SL_u32m4x4trsp(u32m4x4 m)
#if defined(SL_IMPLEMENTATION)
{
    SL_swap(m.m10, m.m01);
    SL_swap(m.m20, m.m02); SL_swap(m.m12, m.m21);
    SL_swap(m.m30, m.m03); SL_swap(m.m31, m.m13);SL_swap(m.m32, m.m23);
    return m;
}
#else
;
#endif
/// @brief Trace of a u32m4x4
SL_header u32 SL_u32m4x4trace(u32m4x4 m)
#if defined(SL_IMPLEMENTATION)
{
    return m.m00 + m.m11 + m.m22 + m.m33;
}
#else
;
#endif
/// @brief Determinant of a u32m4x4
SL_header u32 SL_u32m4x4det_xpd(u32 m00, u32 m01, u32 m02, u32 m03, u32 m10, u32 m11, u32 m12, u32 m13, u32 m20, u32 m21, u32 m22, u32 m23, u32 m30, u32 m31, u32 m32, u32 m33)
#if defined(SL_IMPLEMENTATION)
{
    return m00 * SL_u32m3x3det_xpd(m11, m12, m13, m21, m22, m23, m31, m32, m33)
         + m01 * SL_u32m3x3det_xpd(m10, m12, m13, m20, m22, m23, m30, m32, m33)
         + m02 * SL_u32m3x3det_xpd(m10, m11, m13, m20, m21, m23, m30, m31, m33)
         + m03 * SL_u32m3x3det_xpd(m10, m11, m12, m20, m21, m22, m30, m31, m32);
}
#else
;
#endif
/// @brief Determinant of a u32m4x4
SL_header u32 SL_u32m4x4det(u32m4x4 m)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u32m4x4det_xpd(SL_XPD_M4X4(m));
}
#else
;
#endif



#pragma endregion U32
#pragma region U64

/// @brief Matrix of u64 with arbitrary dimensions
typedef struct {
    union { usize r, c; luv2 size; };
    u64 *data;
} u64m;

#define SL_asu64m(sized_mat) ((u64m){.size = SL_msize(sized_mat), .data = sized_mat.data})





/// @brief Matrix of u64 of size 2 x 2
typedef union {
    u64 data[2 * 2];
    u64 m[2][2];
    struct {
        u64 m00, m01;
        u64 m10, m11;
    };
    struct { u64v2 r0, r1; };
} u64m2x2;

#define SL_u64m2x2_zero ((u64m2x2){0})
#define SL_u64m2x2_identity ((u64m2x2){ 1, 0, 0, 1 })


#define SL_u64m2x2diag(m00_, m11_) ((u64m2x2){.m00 = m00_, .m11 = m11_})

/// @brief Addition of two u64m2x2
SL_header u64m2x2 SL_u64m2x2add(u64m2x2 lhs, u64m2x2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64m2x2) {
        .m00 = lhs.m00 + rhs.m00, .m01 = lhs.m01 + rhs.m01,
        .m10 = lhs.m10 + rhs.m10, .m11 = lhs.m11 + rhs.m11
    };
}
#else
;
#endif
/// @brief Difference of two u64m2x2
SL_header u64m2x2 SL_u64m2x2sub(u64m2x2 lhs, u64m2x2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64m2x2) {
        .m00 = lhs.m00 - rhs.m00, .m01 = lhs.m01 - rhs.m01,
        .m10 = lhs.m10 - rhs.m10, .m11 = lhs.m11 - rhs.m11
    };
}
#else
;
#endif
/// @brief Product of two u64m2x2
SL_header u64m2x2 SL_u64m2x2mul(u64m2x2 lhs, u64m2x2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    u64m2x2 res = SL_u64m2x2_zero;
    for (usize k = 0; k < SL_msize(lhs).x; ++k)
    for (usize j = 0; j < SL_msize(lhs).y; ++j)
    for (usize i = 0; i < SL_msize(lhs).x; ++i)
        res.m[i][j] += lhs.m[i][k] * rhs.m[k][j];

    return res;
}
#else
;
#endif
/// @brief Component-wise multiplication of a u64m2x2 with a scalar
SL_header u64m2x2 SL_u64m2x2muls(u64m2x2 lhs, u64 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64m2x2) {
        .m00 = lhs.m00 * rhs, .m01 = lhs.m01 * rhs,
        .m10 = lhs.m10 * rhs, .m11 = lhs.m11 * rhs
    };
}
#else
;
#endif
/// @brief Product of a u64m2x2 and a u64v2
SL_header u64v2 SL_u64m2x2mulv(u64m2x2 lhs, u64v2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u64v2_(SL_u64v2dot(lhs.r0, rhs), SL_u64v2dot(lhs.r1, rhs));
}
#else
;
#endif
/// @brief Component-wise division of a u64m2x2 with a scalar
SL_header u64m2x2 SL_u64m2x2divs(u64m2x2 lhs, u64 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64m2x2) {
        .m00 = lhs.m00 / rhs, .m01 = lhs.m01 / rhs,
        .m10 = lhs.m10 / rhs, .m11 = lhs.m11 / rhs
    };
}
#else
;
#endif
/// @brief Addition of two u64m2x2 with lhs scaled by a u64
SL_header u64m2x2 SL_u64m2x2addS(u64m2x2 lhs, u64m2x2 rhs, u64 s)
#if defined(SL_IMPLEMENTATION)
{
    return (u64m2x2) {
        .m00 = lhs.m00 + rhs.m00 * s, .m01 = lhs.m01 + rhs.m01 * s,
        .m10 = lhs.m10 + rhs.m10 * s, .m11 = lhs.m11 + rhs.m11 * s
    };
}
#else
;
#endif
/// @brief Difference of two u64m2x2 with lhs scaled by a u64
SL_header u64m2x2 SL_u64m2x2subS(u64m2x2 lhs, u64m2x2 rhs, u64 s)
#if defined(SL_IMPLEMENTATION)
{
    return (u64m2x2) {
        .m00 = lhs.m00 - rhs.m00 * s, .m01 = lhs.m01 - rhs.m01 * s,
        .m10 = lhs.m10 - rhs.m10 * s, .m11 = lhs.m11 - rhs.m11 * s
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two u64m2x2
SL_header u64m2x2 SL_u64m2x2min(u64m2x2 lhs, u64m2x2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64m2x2) {
        .m00 = lhs.m00 < rhs.m00 ? lhs.m00 : rhs.m00, .m01 = lhs.m01 < rhs.m01 ? lhs.m01 : rhs.m01,
        .m10 = lhs.m10 < rhs.m10 ? lhs.m10 : rhs.m10, .m11 = lhs.m11 < rhs.m11 ? lhs.m11 : rhs.m11
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two u64m2x2
SL_header u64m2x2 SL_u64m2x2max(u64m2x2 lhs, u64m2x2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64m2x2) {
        .m00 = lhs.m00 > rhs.m00 ? lhs.m00 : rhs.m00, .m01 = lhs.m01 > rhs.m01 ? lhs.m01 : rhs.m01,
        .m10 = lhs.m10 > rhs.m10 ? lhs.m10 : rhs.m10, .m11 = lhs.m11 > rhs.m11 ? lhs.m11 : rhs.m11
    };
}
#else
;
#endif
/// @brief Transposition of a u64m2x2
SL_header u64m2x2 SL_u64m2x2trsp(u64m2x2 m)
#if defined(SL_IMPLEMENTATION)
{
    SL_swap(m.m10, m.m01);
    return m;
}
#else
;
#endif
/// @brief Trace of a u64m2x2
SL_header u64 SL_u64m2x2trace(u64m2x2 m)
#if defined(SL_IMPLEMENTATION)
{
    return m.m00 + m.m11;
}
#else
;
#endif
/// @brief Determinant of a u64m2x2
SL_header u64 SL_u64m2x2det_xpd(u64 m00, u64 m01, u64 m10, u64 m11)
#if defined(SL_IMPLEMENTATION)
{
    return m00 * m11 - m01 * m10;
}
#else
;
#endif
/// @brief Determinant of a u64m2x2
SL_header u64 SL_u64m2x2det(u64m2x2 m)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u64m2x2det_xpd(SL_XPD_M2X2(m));
}
#else
;
#endif



/// @brief Matrix of u64 of size 3 x 3
typedef union {
    u64 data[3 * 3];
    u64 m[3][3];
    struct {
        u64 m00, m01, m02;
        u64 m10, m11, m12;
        u64 m20, m21, m22;
    };
    struct { u64v3 r0, r1, r2; };
} u64m3x3;

#define SL_u64m3x3_zero ((u64m3x3){0})
#define SL_u64m3x3_identity ((u64m3x3){ 1, 0, 0, 0, 1, 0, 0, 0, 1 })


#define SL_u64m3x3diag(m00_, m11_, m22_) ((u64m3x3){.m00 = m00_, .m11 = m11_, .m22 = m22_})

/// @brief Addition of two u64m3x3
SL_header u64m3x3 SL_u64m3x3add(u64m3x3 lhs, u64m3x3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64m3x3) {
        .m00 = lhs.m00 + rhs.m00, .m01 = lhs.m01 + rhs.m01, .m02 = lhs.m02 + rhs.m02,
        .m10 = lhs.m10 + rhs.m10, .m11 = lhs.m11 + rhs.m11, .m12 = lhs.m12 + rhs.m12,
        .m20 = lhs.m20 + rhs.m20, .m21 = lhs.m21 + rhs.m21, .m22 = lhs.m22 + rhs.m22
    };
}
#else
;
#endif
/// @brief Difference of two u64m3x3
SL_header u64m3x3 SL_u64m3x3sub(u64m3x3 lhs, u64m3x3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64m3x3) {
        .m00 = lhs.m00 - rhs.m00, .m01 = lhs.m01 - rhs.m01, .m02 = lhs.m02 - rhs.m02,
        .m10 = lhs.m10 - rhs.m10, .m11 = lhs.m11 - rhs.m11, .m12 = lhs.m12 - rhs.m12,
        .m20 = lhs.m20 - rhs.m20, .m21 = lhs.m21 - rhs.m21, .m22 = lhs.m22 - rhs.m22
    };
}
#else
;
#endif
/// @brief Product of two u64m3x3
SL_header u64m3x3 SL_u64m3x3mul(u64m3x3 lhs, u64m3x3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    u64m3x3 res = SL_u64m3x3_zero;
    for (usize k = 0; k < SL_msize(lhs).x; ++k)
    for (usize j = 0; j < SL_msize(lhs).y; ++j)
    for (usize i = 0; i < SL_msize(lhs).x; ++i)
        res.m[i][j] += lhs.m[i][k] * rhs.m[k][j];

    return res;
}
#else
;
#endif
/// @brief Component-wise multiplication of a u64m3x3 with a scalar
SL_header u64m3x3 SL_u64m3x3muls(u64m3x3 lhs, u64 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64m3x3) {
        .m00 = lhs.m00 * rhs, .m01 = lhs.m01 * rhs, .m02 = lhs.m02 * rhs,
        .m10 = lhs.m10 * rhs, .m11 = lhs.m11 * rhs, .m12 = lhs.m12 * rhs,
        .m20 = lhs.m20 * rhs, .m21 = lhs.m21 * rhs, .m22 = lhs.m22 * rhs
    };
}
#else
;
#endif
/// @brief Product of a u64m3x3 and a u64v3
SL_header u64v3 SL_u64m3x3mulv(u64m3x3 lhs, u64v3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u64v3_(SL_u64v3dot(lhs.r0, rhs), SL_u64v3dot(lhs.r1, rhs), SL_u64v3dot(lhs.r2, rhs));
}
#else
;
#endif
/// @brief Apply transformation represented by u64m3x3 to a u64v2
SL_header u64v2 SL_u64m3x3apply(u64m3x3 m, u64v2 v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u64m3x3mulv(m, SL_u64v3v(v, 1)).xy;
}
#else
;
#endif
/// @brief Component-wise division of a u64m3x3 with a scalar
SL_header u64m3x3 SL_u64m3x3divs(u64m3x3 lhs, u64 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64m3x3) {
        .m00 = lhs.m00 / rhs, .m01 = lhs.m01 / rhs, .m02 = lhs.m02 / rhs,
        .m10 = lhs.m10 / rhs, .m11 = lhs.m11 / rhs, .m12 = lhs.m12 / rhs,
        .m20 = lhs.m20 / rhs, .m21 = lhs.m21 / rhs, .m22 = lhs.m22 / rhs
    };
}
#else
;
#endif
/// @brief Addition of two u64m3x3 with lhs scaled by a u64
SL_header u64m3x3 SL_u64m3x3addS(u64m3x3 lhs, u64m3x3 rhs, u64 s)
#if defined(SL_IMPLEMENTATION)
{
    return (u64m3x3) {
        .m00 = lhs.m00 + rhs.m00 * s, .m01 = lhs.m01 + rhs.m01 * s, .m02 = lhs.m02 + rhs.m02 * s,
        .m10 = lhs.m10 + rhs.m10 * s, .m11 = lhs.m11 + rhs.m11 * s, .m12 = lhs.m12 + rhs.m12 * s,
        .m20 = lhs.m20 + rhs.m20 * s, .m21 = lhs.m21 + rhs.m21 * s, .m22 = lhs.m22 + rhs.m22 * s
    };
}
#else
;
#endif
/// @brief Difference of two u64m3x3 with lhs scaled by a u64
SL_header u64m3x3 SL_u64m3x3subS(u64m3x3 lhs, u64m3x3 rhs, u64 s)
#if defined(SL_IMPLEMENTATION)
{
    return (u64m3x3) {
        .m00 = lhs.m00 - rhs.m00 * s, .m01 = lhs.m01 - rhs.m01 * s, .m02 = lhs.m02 - rhs.m02 * s,
        .m10 = lhs.m10 - rhs.m10 * s, .m11 = lhs.m11 - rhs.m11 * s, .m12 = lhs.m12 - rhs.m12 * s,
        .m20 = lhs.m20 - rhs.m20 * s, .m21 = lhs.m21 - rhs.m21 * s, .m22 = lhs.m22 - rhs.m22 * s
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two u64m3x3
SL_header u64m3x3 SL_u64m3x3min(u64m3x3 lhs, u64m3x3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64m3x3) {
        .m00 = lhs.m00 < rhs.m00 ? lhs.m00 : rhs.m00, .m01 = lhs.m01 < rhs.m01 ? lhs.m01 : rhs.m01, .m02 = lhs.m02 < rhs.m02 ? lhs.m02 : rhs.m02,
        .m10 = lhs.m10 < rhs.m10 ? lhs.m10 : rhs.m10, .m11 = lhs.m11 < rhs.m11 ? lhs.m11 : rhs.m11, .m12 = lhs.m12 < rhs.m12 ? lhs.m12 : rhs.m12,
        .m20 = lhs.m20 < rhs.m20 ? lhs.m20 : rhs.m20, .m21 = lhs.m21 < rhs.m21 ? lhs.m21 : rhs.m21, .m22 = lhs.m22 < rhs.m22 ? lhs.m22 : rhs.m22
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two u64m3x3
SL_header u64m3x3 SL_u64m3x3max(u64m3x3 lhs, u64m3x3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64m3x3) {
        .m00 = lhs.m00 > rhs.m00 ? lhs.m00 : rhs.m00, .m01 = lhs.m01 > rhs.m01 ? lhs.m01 : rhs.m01, .m02 = lhs.m02 > rhs.m02 ? lhs.m02 : rhs.m02,
        .m10 = lhs.m10 > rhs.m10 ? lhs.m10 : rhs.m10, .m11 = lhs.m11 > rhs.m11 ? lhs.m11 : rhs.m11, .m12 = lhs.m12 > rhs.m12 ? lhs.m12 : rhs.m12,
        .m20 = lhs.m20 > rhs.m20 ? lhs.m20 : rhs.m20, .m21 = lhs.m21 > rhs.m21 ? lhs.m21 : rhs.m21, .m22 = lhs.m22 > rhs.m22 ? lhs.m22 : rhs.m22
    };
}
#else
;
#endif
/// @brief Transposition of a u64m3x3
SL_header u64m3x3 SL_u64m3x3trsp(u64m3x3 m)
#if defined(SL_IMPLEMENTATION)
{
    SL_swap(m.m10, m.m01);
    SL_swap(m.m20, m.m02); SL_swap(m.m21, m.m12);
    return m;
}
#else
;
#endif
/// @brief Trace of a u64m3x3
SL_header u64 SL_u64m3x3trace(u64m3x3 m)
#if defined(SL_IMPLEMENTATION)
{
    return m.m00 + m.m11 + m.m22;
}
#else
;
#endif
/// @brief Determinant of a u64m3x3
SL_header u64 SL_u64m3x3det_xpd(u64 m00, u64 m01, u64 m02, u64 m10, u64 m11, u64 m12, u64 m20, u64 m21, u64 m22)
#if defined(SL_IMPLEMENTATION)
{
    return m00 * m11 * m22 + m01 * m12 * m20 + m02 * m10 * m21 - m02 * m11 * m20 - m12 * m21 * m00 - m22 * m01 * m10;
}
#else
;
#endif
/// @brief Determinant of a u64m3x3
SL_header u64 SL_u64m3x3det(u64m3x3 m)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u64m3x3det_xpd(SL_XPD_M3X3(m));
}
#else
;
#endif



/// @brief Matrix of u64 of size 4 x 4
typedef union {
    u64 data[4 * 4];
    u64 m[4][4];
    struct {
        u64 m00, m01, m02, m03;
        u64 m10, m11, m12, m13;
        u64 m20, m21, m22, m23;
        u64 m30, m31, m32, m33;
    };
    struct { u64v4 r0, r1, r2, r3; };
} u64m4x4;

#define SL_u64m4x4_zero ((u64m4x4){0})
#define SL_u64m4x4_identity ((u64m4x4){ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 })


#define SL_u64m4x4diag(m00_, m11_, m22_, m33_) ((u64m4x4){.m00 = m00_, .m11 = m11_, .m22 = m22_, .m33 = m33_})

/// @brief Addition of two u64m4x4
SL_header u64m4x4 SL_u64m4x4add(u64m4x4 lhs, u64m4x4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64m4x4) {
        .m00 = lhs.m00 + rhs.m00, .m01 = lhs.m01 + rhs.m01, .m02 = lhs.m02 + rhs.m02, .m03 = lhs.m03 + rhs.m03,
        .m10 = lhs.m10 + rhs.m10, .m11 = lhs.m11 + rhs.m11, .m12 = lhs.m12 + rhs.m12, .m13 = lhs.m13 + rhs.m13,
        .m20 = lhs.m20 + rhs.m20, .m21 = lhs.m21 + rhs.m21, .m22 = lhs.m22 + rhs.m22, .m23 = lhs.m23 + rhs.m23,
        .m30 = lhs.m30 + rhs.m30, .m31 = lhs.m31 + rhs.m31, .m32 = lhs.m32 + rhs.m32, .m33 = lhs.m33 + rhs.m33
    };
}
#else
;
#endif
/// @brief Difference of two u64m4x4
SL_header u64m4x4 SL_u64m4x4sub(u64m4x4 lhs, u64m4x4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64m4x4) {
        .m00 = lhs.m00 - rhs.m00, .m01 = lhs.m01 - rhs.m01, .m02 = lhs.m02 - rhs.m02, .m03 = lhs.m03 - rhs.m03,
        .m10 = lhs.m10 - rhs.m10, .m11 = lhs.m11 - rhs.m11, .m12 = lhs.m12 - rhs.m12, .m13 = lhs.m13 - rhs.m13,
        .m20 = lhs.m20 - rhs.m20, .m21 = lhs.m21 - rhs.m21, .m22 = lhs.m22 - rhs.m22, .m23 = lhs.m23 - rhs.m23,
        .m30 = lhs.m30 - rhs.m30, .m31 = lhs.m31 - rhs.m31, .m32 = lhs.m32 - rhs.m32, .m33 = lhs.m33 - rhs.m33
    };
}
#else
;
#endif
/// @brief Product of two u64m4x4
SL_header u64m4x4 SL_u64m4x4mul(u64m4x4 lhs, u64m4x4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    u64m4x4 res = SL_u64m4x4_zero;
    for (usize k = 0; k < SL_msize(lhs).x; ++k)
    for (usize j = 0; j < SL_msize(lhs).y; ++j)
    for (usize i = 0; i < SL_msize(lhs).x; ++i)
        res.m[i][j] += lhs.m[i][k] * rhs.m[k][j];

    return res;
}
#else
;
#endif
/// @brief Component-wise multiplication of a u64m4x4 with a scalar
SL_header u64m4x4 SL_u64m4x4muls(u64m4x4 lhs, u64 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64m4x4) {
        .m00 = lhs.m00 * rhs, .m01 = lhs.m01 * rhs, .m02 = lhs.m02 * rhs, .m03 = lhs.m03 * rhs,
        .m10 = lhs.m10 * rhs, .m11 = lhs.m11 * rhs, .m12 = lhs.m12 * rhs, .m13 = lhs.m13 * rhs,
        .m20 = lhs.m20 * rhs, .m21 = lhs.m21 * rhs, .m22 = lhs.m22 * rhs, .m23 = lhs.m23 * rhs,
        .m30 = lhs.m30 * rhs, .m31 = lhs.m31 * rhs, .m32 = lhs.m32 * rhs, .m33 = lhs.m33 * rhs
    };
}
#else
;
#endif
/// @brief Product of a u64m4x4 and a u64v4
SL_header u64v4 SL_u64m4x4mulv(u64m4x4 lhs, u64v4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u64v4_(SL_u64v4dot(lhs.r0, rhs), SL_u64v4dot(lhs.r1, rhs), SL_u64v4dot(lhs.r2, rhs), SL_u64v4dot(lhs.r3, rhs));
}
#else
;
#endif
/// @brief Apply transformation represented by u64m4x4 to a u64v3
SL_header u64v3 SL_u64m4x4apply(u64m4x4 m, u64v3 v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u64m4x4mulv(m, SL_u64v4v(v, 1)).xyz;
}
#else
;
#endif
/// @brief Component-wise division of a u64m4x4 with a scalar
SL_header u64m4x4 SL_u64m4x4divs(u64m4x4 lhs, u64 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64m4x4) {
        .m00 = lhs.m00 / rhs, .m01 = lhs.m01 / rhs, .m02 = lhs.m02 / rhs, .m03 = lhs.m03 / rhs,
        .m10 = lhs.m10 / rhs, .m11 = lhs.m11 / rhs, .m12 = lhs.m12 / rhs, .m13 = lhs.m13 / rhs,
        .m20 = lhs.m20 / rhs, .m21 = lhs.m21 / rhs, .m22 = lhs.m22 / rhs, .m23 = lhs.m23 / rhs,
        .m30 = lhs.m30 / rhs, .m31 = lhs.m31 / rhs, .m32 = lhs.m32 / rhs, .m33 = lhs.m33 / rhs
    };
}
#else
;
#endif
/// @brief Addition of two u64m4x4 with lhs scaled by a u64
SL_header u64m4x4 SL_u64m4x4addS(u64m4x4 lhs, u64m4x4 rhs, u64 s)
#if defined(SL_IMPLEMENTATION)
{
    return (u64m4x4) {
        .m00 = lhs.m00 + rhs.m00 * s, .m01 = lhs.m01 + rhs.m01 * s, .m02 = lhs.m02 + rhs.m02 * s, .m03 = lhs.m03 + rhs.m03 * s,
        .m10 = lhs.m10 + rhs.m10 * s, .m11 = lhs.m11 + rhs.m11 * s, .m12 = lhs.m12 + rhs.m12 * s, .m13 = lhs.m13 + rhs.m13 * s,
        .m20 = lhs.m20 + rhs.m20 * s, .m21 = lhs.m21 + rhs.m21 * s, .m22 = lhs.m22 + rhs.m22 * s, .m23 = lhs.m23 + rhs.m23 * s,
        .m30 = lhs.m30 + rhs.m30 * s, .m31 = lhs.m31 + rhs.m31 * s, .m32 = lhs.m32 + rhs.m32 * s, .m33 = lhs.m33 + rhs.m33 * s
    };
}
#else
;
#endif
/// @brief Difference of two u64m4x4 with lhs scaled by a u64
SL_header u64m4x4 SL_u64m4x4subS(u64m4x4 lhs, u64m4x4 rhs, u64 s)
#if defined(SL_IMPLEMENTATION)
{
    return (u64m4x4) {
        .m00 = lhs.m00 - rhs.m00 * s, .m01 = lhs.m01 - rhs.m01 * s, .m02 = lhs.m02 - rhs.m02 * s, .m03 = lhs.m03 - rhs.m03 * s,
        .m10 = lhs.m10 - rhs.m10 * s, .m11 = lhs.m11 - rhs.m11 * s, .m12 = lhs.m12 - rhs.m12 * s, .m13 = lhs.m13 - rhs.m13 * s,
        .m20 = lhs.m20 - rhs.m20 * s, .m21 = lhs.m21 - rhs.m21 * s, .m22 = lhs.m22 - rhs.m22 * s, .m23 = lhs.m23 - rhs.m23 * s,
        .m30 = lhs.m30 - rhs.m30 * s, .m31 = lhs.m31 - rhs.m31 * s, .m32 = lhs.m32 - rhs.m32 * s, .m33 = lhs.m33 - rhs.m33 * s
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two u64m4x4
SL_header u64m4x4 SL_u64m4x4min(u64m4x4 lhs, u64m4x4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64m4x4) {
        .m00 = lhs.m00 < rhs.m00 ? lhs.m00 : rhs.m00, .m01 = lhs.m01 < rhs.m01 ? lhs.m01 : rhs.m01, .m02 = lhs.m02 < rhs.m02 ? lhs.m02 : rhs.m02, .m03 = lhs.m03 < rhs.m03 ? lhs.m03 : rhs.m03,
        .m10 = lhs.m10 < rhs.m10 ? lhs.m10 : rhs.m10, .m11 = lhs.m11 < rhs.m11 ? lhs.m11 : rhs.m11, .m12 = lhs.m12 < rhs.m12 ? lhs.m12 : rhs.m12, .m13 = lhs.m13 < rhs.m13 ? lhs.m13 : rhs.m13,
        .m20 = lhs.m20 < rhs.m20 ? lhs.m20 : rhs.m20, .m21 = lhs.m21 < rhs.m21 ? lhs.m21 : rhs.m21, .m22 = lhs.m22 < rhs.m22 ? lhs.m22 : rhs.m22, .m23 = lhs.m23 < rhs.m23 ? lhs.m23 : rhs.m23,
        .m30 = lhs.m30 < rhs.m30 ? lhs.m30 : rhs.m30, .m31 = lhs.m31 < rhs.m31 ? lhs.m31 : rhs.m31, .m32 = lhs.m32 < rhs.m32 ? lhs.m32 : rhs.m32, .m33 = lhs.m33 < rhs.m33 ? lhs.m33 : rhs.m33
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two u64m4x4
SL_header u64m4x4 SL_u64m4x4max(u64m4x4 lhs, u64m4x4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (u64m4x4) {
        .m00 = lhs.m00 > rhs.m00 ? lhs.m00 : rhs.m00, .m01 = lhs.m01 > rhs.m01 ? lhs.m01 : rhs.m01, .m02 = lhs.m02 > rhs.m02 ? lhs.m02 : rhs.m02, .m03 = lhs.m03 > rhs.m03 ? lhs.m03 : rhs.m03,
        .m10 = lhs.m10 > rhs.m10 ? lhs.m10 : rhs.m10, .m11 = lhs.m11 > rhs.m11 ? lhs.m11 : rhs.m11, .m12 = lhs.m12 > rhs.m12 ? lhs.m12 : rhs.m12, .m13 = lhs.m13 > rhs.m13 ? lhs.m13 : rhs.m13,
        .m20 = lhs.m20 > rhs.m20 ? lhs.m20 : rhs.m20, .m21 = lhs.m21 > rhs.m21 ? lhs.m21 : rhs.m21, .m22 = lhs.m22 > rhs.m22 ? lhs.m22 : rhs.m22, .m23 = lhs.m23 > rhs.m23 ? lhs.m23 : rhs.m23,
        .m30 = lhs.m30 > rhs.m30 ? lhs.m30 : rhs.m30, .m31 = lhs.m31 > rhs.m31 ? lhs.m31 : rhs.m31, .m32 = lhs.m32 > rhs.m32 ? lhs.m32 : rhs.m32, .m33 = lhs.m33 > rhs.m33 ? lhs.m33 : rhs.m33
    };
}
#else
;
#endif
/// @brief Transposition of a u64m4x4
SL_header u64m4x4 SL_u64m4x4trsp(u64m4x4 m)
#if defined(SL_IMPLEMENTATION)
{
    SL_swap(m.m10, m.m01);
    SL_swap(m.m20, m.m02); SL_swap(m.m12, m.m21);
    SL_swap(m.m30, m.m03); SL_swap(m.m31, m.m13);SL_swap(m.m32, m.m23);
    return m;
}
#else
;
#endif
/// @brief Trace of a u64m4x4
SL_header u64 SL_u64m4x4trace(u64m4x4 m)
#if defined(SL_IMPLEMENTATION)
{
    return m.m00 + m.m11 + m.m22 + m.m33;
}
#else
;
#endif
/// @brief Determinant of a u64m4x4
SL_header u64 SL_u64m4x4det_xpd(u64 m00, u64 m01, u64 m02, u64 m03, u64 m10, u64 m11, u64 m12, u64 m13, u64 m20, u64 m21, u64 m22, u64 m23, u64 m30, u64 m31, u64 m32, u64 m33)
#if defined(SL_IMPLEMENTATION)
{
    return m00 * SL_u64m3x3det_xpd(m11, m12, m13, m21, m22, m23, m31, m32, m33)
         + m01 * SL_u64m3x3det_xpd(m10, m12, m13, m20, m22, m23, m30, m32, m33)
         + m02 * SL_u64m3x3det_xpd(m10, m11, m13, m20, m21, m23, m30, m31, m33)
         + m03 * SL_u64m3x3det_xpd(m10, m11, m12, m20, m21, m22, m30, m31, m32);
}
#else
;
#endif
/// @brief Determinant of a u64m4x4
SL_header u64 SL_u64m4x4det(u64m4x4 m)
#if defined(SL_IMPLEMENTATION)
{
    return SL_u64m4x4det_xpd(SL_XPD_M4X4(m));
}
#else
;
#endif



#pragma endregion U64
#pragma region FLOAT

/// @brief Matrix of float with arbitrary dimensions
typedef struct {
    union { usize r, c; luv2 size; };
    float *data;
} fm;

#define SL_asfm(sized_mat) ((fm){.size = SL_msize(sized_mat), .data = sized_mat.data})





/// @brief Matrix of float of size 2 x 2
typedef union {
    float data[2 * 2];
    float m[2][2];
    struct {
        float m00, m01;
        float m10, m11;
    };
    struct { fv2 r0, r1; };
} fm2x2;

#define SL_fm2x2_zero ((fm2x2){0})
#define SL_fm2x2_identity ((fm2x2){ 1, 0, 0, 1 })


#define SL_fm2x2diag(m00_, m11_) ((fm2x2){.m00 = m00_, .m11 = m11_})

/// @brief Addition of two fm2x2
SL_header fm2x2 SL_fm2x2add(fm2x2 lhs, fm2x2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (fm2x2) {
        .m00 = lhs.m00 + rhs.m00, .m01 = lhs.m01 + rhs.m01,
        .m10 = lhs.m10 + rhs.m10, .m11 = lhs.m11 + rhs.m11
    };
}
#else
;
#endif
/// @brief Difference of two fm2x2
SL_header fm2x2 SL_fm2x2sub(fm2x2 lhs, fm2x2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (fm2x2) {
        .m00 = lhs.m00 - rhs.m00, .m01 = lhs.m01 - rhs.m01,
        .m10 = lhs.m10 - rhs.m10, .m11 = lhs.m11 - rhs.m11
    };
}
#else
;
#endif
/// @brief Product of two fm2x2
SL_header fm2x2 SL_fm2x2mul(fm2x2 lhs, fm2x2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    fm2x2 res = SL_fm2x2_zero;
    for (usize k = 0; k < SL_msize(lhs).x; ++k)
    for (usize j = 0; j < SL_msize(lhs).y; ++j)
    for (usize i = 0; i < SL_msize(lhs).x; ++i)
        res.m[i][j] += lhs.m[i][k] * rhs.m[k][j];

    return res;
}
#else
;
#endif
/// @brief Component-wise multiplication of a fm2x2 with a scalar
SL_header fm2x2 SL_fm2x2muls(fm2x2 lhs, float rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (fm2x2) {
        .m00 = lhs.m00 * rhs, .m01 = lhs.m01 * rhs,
        .m10 = lhs.m10 * rhs, .m11 = lhs.m11 * rhs
    };
}
#else
;
#endif
/// @brief Product of a fm2x2 and a fv2
SL_header fv2 SL_fm2x2mulv(fm2x2 lhs, fv2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_fv2_(SL_fv2dot(lhs.r0, rhs), SL_fv2dot(lhs.r1, rhs));
}
#else
;
#endif
/// @brief Component-wise division of a fm2x2 with a scalar
SL_header fm2x2 SL_fm2x2divs(fm2x2 lhs, float rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (fm2x2) {
        .m00 = lhs.m00 / rhs, .m01 = lhs.m01 / rhs,
        .m10 = lhs.m10 / rhs, .m11 = lhs.m11 / rhs
    };
}
#else
;
#endif
/// @brief Addition of two fm2x2 with lhs scaled by a float
SL_header fm2x2 SL_fm2x2addS(fm2x2 lhs, fm2x2 rhs, float s)
#if defined(SL_IMPLEMENTATION)
{
    return (fm2x2) {
        .m00 = lhs.m00 + rhs.m00 * s, .m01 = lhs.m01 + rhs.m01 * s,
        .m10 = lhs.m10 + rhs.m10 * s, .m11 = lhs.m11 + rhs.m11 * s
    };
}
#else
;
#endif
/// @brief Difference of two fm2x2 with lhs scaled by a float
SL_header fm2x2 SL_fm2x2subS(fm2x2 lhs, fm2x2 rhs, float s)
#if defined(SL_IMPLEMENTATION)
{
    return (fm2x2) {
        .m00 = lhs.m00 - rhs.m00 * s, .m01 = lhs.m01 - rhs.m01 * s,
        .m10 = lhs.m10 - rhs.m10 * s, .m11 = lhs.m11 - rhs.m11 * s
    };
}
#else
;
#endif
/// @brief Negation of a fm2x2
SL_header fm2x2 SL_fm2x2neg(fm2x2 m)
#if defined(SL_IMPLEMENTATION)
{
    return (fm2x2) {
        .m00 = -m.m00, .m01 = -m.m01,
        .m10 = -m.m10, .m11 = -m.m11
    };
}
#else
;
#endif
/// @brief Component-wise absolute value of a fm2x2
SL_header fm2x2 SL_fm2x2abs(fm2x2 m)
#if defined(SL_IMPLEMENTATION)
{
    return (fm2x2) {
        .m00 = fabs(m.m00), .m01 = fabs(m.m01),
        .m10 = fabs(m.m10), .m11 = fabs(m.m11)
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two fm2x2
SL_header fm2x2 SL_fm2x2min(fm2x2 lhs, fm2x2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (fm2x2) {
        .m00 = lhs.m00 < rhs.m00 ? lhs.m00 : rhs.m00, .m01 = lhs.m01 < rhs.m01 ? lhs.m01 : rhs.m01,
        .m10 = lhs.m10 < rhs.m10 ? lhs.m10 : rhs.m10, .m11 = lhs.m11 < rhs.m11 ? lhs.m11 : rhs.m11
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two fm2x2
SL_header fm2x2 SL_fm2x2max(fm2x2 lhs, fm2x2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (fm2x2) {
        .m00 = lhs.m00 > rhs.m00 ? lhs.m00 : rhs.m00, .m01 = lhs.m01 > rhs.m01 ? lhs.m01 : rhs.m01,
        .m10 = lhs.m10 > rhs.m10 ? lhs.m10 : rhs.m10, .m11 = lhs.m11 > rhs.m11 ? lhs.m11 : rhs.m11
    };
}
#else
;
#endif
/// @brief Transposition of a fm2x2
SL_header fm2x2 SL_fm2x2trsp(fm2x2 m)
#if defined(SL_IMPLEMENTATION)
{
    SL_swap(m.m10, m.m01);
    return m;
}
#else
;
#endif
/// @brief Trace of a fm2x2
SL_header float SL_fm2x2trace(fm2x2 m)
#if defined(SL_IMPLEMENTATION)
{
    return m.m00 + m.m11;
}
#else
;
#endif
/// @brief Determinant of a fm2x2
SL_header float SL_fm2x2det_xpd(float m00, float m01, float m10, float m11)
#if defined(SL_IMPLEMENTATION)
{
    return m00 * m11 - m01 * m10;
}
#else
;
#endif
/// @brief Determinant of a fm2x2
SL_header float SL_fm2x2det(fm2x2 m)
#if defined(SL_IMPLEMENTATION)
{
    return SL_fm2x2det_xpd(SL_XPD_M2X2(m));
}
#else
;
#endif
/// @brief Inverse of a fm2x2
SL_header fm2x2 SL_fm2x2inv(fm2x2 m)
#if defined(SL_IMPLEMENTATION)
{
    fm2x2 trsp_comat = { .m00 = m.m11, .m10 = -m.m10, .m10 = -m.m10, .m11 = m.m00 };
    
    float det = trsp_comat.m00 * m.m00 + trsp_comat.m01 * m.m10;
    if (det == 0.0) return __SL_ERROR(SL_ERR_DIVISION_BY_ZERO), SL_fm2x2_zero;

    return SL_fm2x2muls(trsp_comat, 1.0 / det);
}
#else
;
#endif
/// @brief Matrix fm2x2 representing a 2D rotation
SL_header fm2x2 SL_fm2x2from_angle(float angle)
#if defined(SL_IMPLEMENTATION)
{
    double sin, cos; sincos(angle, &sin, &cos);

    return (fm2x2) {
        .m00 = -sin, .m01 = cos,
        .m10 =  cos, .m11 = sin
    };
}
#else
;
#endif



/// @brief Matrix of float of size 3 x 3
typedef union {
    float data[3 * 3];
    float m[3][3];
    struct {
        float m00, m01, m02;
        float m10, m11, m12;
        float m20, m21, m22;
    };
    struct { fv3 r0, r1, r2; };
} fm3x3;

#define SL_fm3x3_zero ((fm3x3){0})
#define SL_fm3x3_identity ((fm3x3){ 1, 0, 0, 0, 1, 0, 0, 0, 1 })


#define SL_fm3x3diag(m00_, m11_, m22_) ((fm3x3){.m00 = m00_, .m11 = m11_, .m22 = m22_})

/// @brief Addition of two fm3x3
SL_header fm3x3 SL_fm3x3add(fm3x3 lhs, fm3x3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (fm3x3) {
        .m00 = lhs.m00 + rhs.m00, .m01 = lhs.m01 + rhs.m01, .m02 = lhs.m02 + rhs.m02,
        .m10 = lhs.m10 + rhs.m10, .m11 = lhs.m11 + rhs.m11, .m12 = lhs.m12 + rhs.m12,
        .m20 = lhs.m20 + rhs.m20, .m21 = lhs.m21 + rhs.m21, .m22 = lhs.m22 + rhs.m22
    };
}
#else
;
#endif
/// @brief Difference of two fm3x3
SL_header fm3x3 SL_fm3x3sub(fm3x3 lhs, fm3x3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (fm3x3) {
        .m00 = lhs.m00 - rhs.m00, .m01 = lhs.m01 - rhs.m01, .m02 = lhs.m02 - rhs.m02,
        .m10 = lhs.m10 - rhs.m10, .m11 = lhs.m11 - rhs.m11, .m12 = lhs.m12 - rhs.m12,
        .m20 = lhs.m20 - rhs.m20, .m21 = lhs.m21 - rhs.m21, .m22 = lhs.m22 - rhs.m22
    };
}
#else
;
#endif
/// @brief Product of two fm3x3
SL_header fm3x3 SL_fm3x3mul(fm3x3 lhs, fm3x3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    fm3x3 res = SL_fm3x3_zero;
    for (usize k = 0; k < SL_msize(lhs).x; ++k)
    for (usize j = 0; j < SL_msize(lhs).y; ++j)
    for (usize i = 0; i < SL_msize(lhs).x; ++i)
        res.m[i][j] += lhs.m[i][k] * rhs.m[k][j];

    return res;
}
#else
;
#endif
/// @brief Component-wise multiplication of a fm3x3 with a scalar
SL_header fm3x3 SL_fm3x3muls(fm3x3 lhs, float rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (fm3x3) {
        .m00 = lhs.m00 * rhs, .m01 = lhs.m01 * rhs, .m02 = lhs.m02 * rhs,
        .m10 = lhs.m10 * rhs, .m11 = lhs.m11 * rhs, .m12 = lhs.m12 * rhs,
        .m20 = lhs.m20 * rhs, .m21 = lhs.m21 * rhs, .m22 = lhs.m22 * rhs
    };
}
#else
;
#endif
/// @brief Product of a fm3x3 and a fv3
SL_header fv3 SL_fm3x3mulv(fm3x3 lhs, fv3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_fv3_(SL_fv3dot(lhs.r0, rhs), SL_fv3dot(lhs.r1, rhs), SL_fv3dot(lhs.r2, rhs));
}
#else
;
#endif
/// @brief Apply transformation represented by fm3x3 to a fv2
SL_header fv2 SL_fm3x3apply(fm3x3 m, fv2 v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_fm3x3mulv(m, SL_fv3v(v, 1)).xy;
}
#else
;
#endif
/// @brief Component-wise division of a fm3x3 with a scalar
SL_header fm3x3 SL_fm3x3divs(fm3x3 lhs, float rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (fm3x3) {
        .m00 = lhs.m00 / rhs, .m01 = lhs.m01 / rhs, .m02 = lhs.m02 / rhs,
        .m10 = lhs.m10 / rhs, .m11 = lhs.m11 / rhs, .m12 = lhs.m12 / rhs,
        .m20 = lhs.m20 / rhs, .m21 = lhs.m21 / rhs, .m22 = lhs.m22 / rhs
    };
}
#else
;
#endif
/// @brief Addition of two fm3x3 with lhs scaled by a float
SL_header fm3x3 SL_fm3x3addS(fm3x3 lhs, fm3x3 rhs, float s)
#if defined(SL_IMPLEMENTATION)
{
    return (fm3x3) {
        .m00 = lhs.m00 + rhs.m00 * s, .m01 = lhs.m01 + rhs.m01 * s, .m02 = lhs.m02 + rhs.m02 * s,
        .m10 = lhs.m10 + rhs.m10 * s, .m11 = lhs.m11 + rhs.m11 * s, .m12 = lhs.m12 + rhs.m12 * s,
        .m20 = lhs.m20 + rhs.m20 * s, .m21 = lhs.m21 + rhs.m21 * s, .m22 = lhs.m22 + rhs.m22 * s
    };
}
#else
;
#endif
/// @brief Difference of two fm3x3 with lhs scaled by a float
SL_header fm3x3 SL_fm3x3subS(fm3x3 lhs, fm3x3 rhs, float s)
#if defined(SL_IMPLEMENTATION)
{
    return (fm3x3) {
        .m00 = lhs.m00 - rhs.m00 * s, .m01 = lhs.m01 - rhs.m01 * s, .m02 = lhs.m02 - rhs.m02 * s,
        .m10 = lhs.m10 - rhs.m10 * s, .m11 = lhs.m11 - rhs.m11 * s, .m12 = lhs.m12 - rhs.m12 * s,
        .m20 = lhs.m20 - rhs.m20 * s, .m21 = lhs.m21 - rhs.m21 * s, .m22 = lhs.m22 - rhs.m22 * s
    };
}
#else
;
#endif
/// @brief Negation of a fm3x3
SL_header fm3x3 SL_fm3x3neg(fm3x3 m)
#if defined(SL_IMPLEMENTATION)
{
    return (fm3x3) {
        .m00 = -m.m00, .m01 = -m.m01, .m02 = -m.m02,
        .m10 = -m.m10, .m11 = -m.m11, .m12 = -m.m12,
        .m20 = -m.m20, .m21 = -m.m21, .m22 = -m.m22
    };
}
#else
;
#endif
/// @brief Component-wise absolute value of a fm3x3
SL_header fm3x3 SL_fm3x3abs(fm3x3 m)
#if defined(SL_IMPLEMENTATION)
{
    return (fm3x3) {
        .m00 = fabs(m.m00), .m01 = fabs(m.m01), .m02 = fabs(m.m02),
        .m10 = fabs(m.m10), .m11 = fabs(m.m11), .m12 = fabs(m.m12),
        .m20 = fabs(m.m20), .m21 = fabs(m.m21), .m22 = fabs(m.m22)
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two fm3x3
SL_header fm3x3 SL_fm3x3min(fm3x3 lhs, fm3x3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (fm3x3) {
        .m00 = lhs.m00 < rhs.m00 ? lhs.m00 : rhs.m00, .m01 = lhs.m01 < rhs.m01 ? lhs.m01 : rhs.m01, .m02 = lhs.m02 < rhs.m02 ? lhs.m02 : rhs.m02,
        .m10 = lhs.m10 < rhs.m10 ? lhs.m10 : rhs.m10, .m11 = lhs.m11 < rhs.m11 ? lhs.m11 : rhs.m11, .m12 = lhs.m12 < rhs.m12 ? lhs.m12 : rhs.m12,
        .m20 = lhs.m20 < rhs.m20 ? lhs.m20 : rhs.m20, .m21 = lhs.m21 < rhs.m21 ? lhs.m21 : rhs.m21, .m22 = lhs.m22 < rhs.m22 ? lhs.m22 : rhs.m22
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two fm3x3
SL_header fm3x3 SL_fm3x3max(fm3x3 lhs, fm3x3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (fm3x3) {
        .m00 = lhs.m00 > rhs.m00 ? lhs.m00 : rhs.m00, .m01 = lhs.m01 > rhs.m01 ? lhs.m01 : rhs.m01, .m02 = lhs.m02 > rhs.m02 ? lhs.m02 : rhs.m02,
        .m10 = lhs.m10 > rhs.m10 ? lhs.m10 : rhs.m10, .m11 = lhs.m11 > rhs.m11 ? lhs.m11 : rhs.m11, .m12 = lhs.m12 > rhs.m12 ? lhs.m12 : rhs.m12,
        .m20 = lhs.m20 > rhs.m20 ? lhs.m20 : rhs.m20, .m21 = lhs.m21 > rhs.m21 ? lhs.m21 : rhs.m21, .m22 = lhs.m22 > rhs.m22 ? lhs.m22 : rhs.m22
    };
}
#else
;
#endif
/// @brief Transposition of a fm3x3
SL_header fm3x3 SL_fm3x3trsp(fm3x3 m)
#if defined(SL_IMPLEMENTATION)
{
    SL_swap(m.m10, m.m01);
    SL_swap(m.m20, m.m02); SL_swap(m.m21, m.m12);
    return m;
}
#else
;
#endif
/// @brief Trace of a fm3x3
SL_header float SL_fm3x3trace(fm3x3 m)
#if defined(SL_IMPLEMENTATION)
{
    return m.m00 + m.m11 + m.m22;
}
#else
;
#endif
/// @brief Determinant of a fm3x3
SL_header float SL_fm3x3det_xpd(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22)
#if defined(SL_IMPLEMENTATION)
{
    return m00 * m11 * m22 + m01 * m12 * m20 + m02 * m10 * m21 - m02 * m11 * m20 - m12 * m21 * m00 - m22 * m01 * m10;
}
#else
;
#endif
/// @brief Determinant of a fm3x3
SL_header float SL_fm3x3det(fm3x3 m)
#if defined(SL_IMPLEMENTATION)
{
    return SL_fm3x3det_xpd(SL_XPD_M3X3(m));
}
#else
;
#endif
/// @brief Inverse of a fm3x3
SL_header fm3x3 SL_fm3x3inv(fm3x3 m)
#if defined(SL_IMPLEMENTATION)
{
    fm3x3 trsp_comat;
    for (int i = 0; i < 3; ++i)
    for (int j = 0; j < 3; ++j)
    {
        trsp_comat.m[j][i] = ((i + j) & 1 ? -1 : 1) *
            SL_fm2x2det_xpd(
                m.m[1 - (i >= 1)][1 - (j >= 1)], m.m[1 - (i >= 1)][2 - (j >= 2)],
                m.m[2 - (i >= 2)][1 - (j >= 1)], m.m[2 - (i >= 2)][2 - (j >= 2)]
            );
    }
    
    float det = trsp_comat.m00 * m.m00 + trsp_comat.m01 * m.m10 + trsp_comat.m02 * m.m20;
    if (det == 0.0) return __SL_ERROR(SL_ERR_DIVISION_BY_ZERO), SL_fm3x3_zero;

    return SL_fm3x3muls(trsp_comat, 1.0 / det);
}
#else
;
#endif
/// @brief Matrix fm3x3 from a float
SL_header fm3x3 SL_fm3x3from_quat(fq quat)
#if defined(SL_IMPLEMENTATION)
{
    float wx = quat.w*quat.x, wy = quat.w*quat.y, wz = quat.w*quat.z, xy = quat.x*quat.y, yz = quat.y*quat.z, xz = quat.x*quat.z;
    float w2 = quat.w*quat.w, x2 = quat.x*quat.x, y2 = quat.y*quat.y, z2 = quat.z*quat.z;

    return (fm3x3) {
        .m00 = w2 + x2 - y2 - z2, .m10 = 2 * (xy - wz),     .m20 = 2 * (xz + wy),
        .m01 = 2 * (xy + wz),     .m11 = w2 - x2 + y2 - z2, .m21 = 2 * (yz - wx),
        .m02 = 2 * (xz - wy),     .m12 = 2 * (yz + wx),     .m22 = w2 - x2 - y2 + z2
    };
}
#else
;
#endif
/// @brief Matrix fm3x3 representing a transformation
SL_header fm3x3 SL_fm3x3from_transform(fv2 position, float rotation, fv2 scale)
#if defined(SL_IMPLEMENTATION)
{
    double sin, cos; sincos(rotation, &sin, &cos);

    return (fm3x3) {
        .m00 = scale.x * cos, .m01 = scale.y * -sin, .m02 = position.x,
        .m10 = scale.x * sin, .m11 = scale.y *  cos, .m12 = position.y,
        .m20 =           0.0, .m21 =            0.0, .m22 =        1.0
    };
}
#else
;
#endif



/// @brief Matrix of float of size 4 x 4
typedef union {
    float data[4 * 4];
    float m[4][4];
    struct {
        float m00, m01, m02, m03;
        float m10, m11, m12, m13;
        float m20, m21, m22, m23;
        float m30, m31, m32, m33;
    };
    struct { fv4 r0, r1, r2, r3; };
} fm4x4;

#define SL_fm4x4_zero ((fm4x4){0})
#define SL_fm4x4_identity ((fm4x4){ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 })


#define SL_fm4x4diag(m00_, m11_, m22_, m33_) ((fm4x4){.m00 = m00_, .m11 = m11_, .m22 = m22_, .m33 = m33_})

/// @brief Addition of two fm4x4
SL_header fm4x4 SL_fm4x4add(fm4x4 lhs, fm4x4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (fm4x4) {
        .m00 = lhs.m00 + rhs.m00, .m01 = lhs.m01 + rhs.m01, .m02 = lhs.m02 + rhs.m02, .m03 = lhs.m03 + rhs.m03,
        .m10 = lhs.m10 + rhs.m10, .m11 = lhs.m11 + rhs.m11, .m12 = lhs.m12 + rhs.m12, .m13 = lhs.m13 + rhs.m13,
        .m20 = lhs.m20 + rhs.m20, .m21 = lhs.m21 + rhs.m21, .m22 = lhs.m22 + rhs.m22, .m23 = lhs.m23 + rhs.m23,
        .m30 = lhs.m30 + rhs.m30, .m31 = lhs.m31 + rhs.m31, .m32 = lhs.m32 + rhs.m32, .m33 = lhs.m33 + rhs.m33
    };
}
#else
;
#endif
/// @brief Difference of two fm4x4
SL_header fm4x4 SL_fm4x4sub(fm4x4 lhs, fm4x4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (fm4x4) {
        .m00 = lhs.m00 - rhs.m00, .m01 = lhs.m01 - rhs.m01, .m02 = lhs.m02 - rhs.m02, .m03 = lhs.m03 - rhs.m03,
        .m10 = lhs.m10 - rhs.m10, .m11 = lhs.m11 - rhs.m11, .m12 = lhs.m12 - rhs.m12, .m13 = lhs.m13 - rhs.m13,
        .m20 = lhs.m20 - rhs.m20, .m21 = lhs.m21 - rhs.m21, .m22 = lhs.m22 - rhs.m22, .m23 = lhs.m23 - rhs.m23,
        .m30 = lhs.m30 - rhs.m30, .m31 = lhs.m31 - rhs.m31, .m32 = lhs.m32 - rhs.m32, .m33 = lhs.m33 - rhs.m33
    };
}
#else
;
#endif
/// @brief Product of two fm4x4
SL_header fm4x4 SL_fm4x4mul(fm4x4 lhs, fm4x4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    fm4x4 res = SL_fm4x4_zero;
    for (usize k = 0; k < SL_msize(lhs).x; ++k)
    for (usize j = 0; j < SL_msize(lhs).y; ++j)
    for (usize i = 0; i < SL_msize(lhs).x; ++i)
        res.m[i][j] += lhs.m[i][k] * rhs.m[k][j];

    return res;
}
#else
;
#endif
/// @brief Component-wise multiplication of a fm4x4 with a scalar
SL_header fm4x4 SL_fm4x4muls(fm4x4 lhs, float rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (fm4x4) {
        .m00 = lhs.m00 * rhs, .m01 = lhs.m01 * rhs, .m02 = lhs.m02 * rhs, .m03 = lhs.m03 * rhs,
        .m10 = lhs.m10 * rhs, .m11 = lhs.m11 * rhs, .m12 = lhs.m12 * rhs, .m13 = lhs.m13 * rhs,
        .m20 = lhs.m20 * rhs, .m21 = lhs.m21 * rhs, .m22 = lhs.m22 * rhs, .m23 = lhs.m23 * rhs,
        .m30 = lhs.m30 * rhs, .m31 = lhs.m31 * rhs, .m32 = lhs.m32 * rhs, .m33 = lhs.m33 * rhs
    };
}
#else
;
#endif
/// @brief Product of a fm4x4 and a fv4
SL_header fv4 SL_fm4x4mulv(fm4x4 lhs, fv4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_fv4_(SL_fv4dot(lhs.r0, rhs), SL_fv4dot(lhs.r1, rhs), SL_fv4dot(lhs.r2, rhs), SL_fv4dot(lhs.r3, rhs));
}
#else
;
#endif
/// @brief Apply transformation represented by fm4x4 to a fv3
SL_header fv3 SL_fm4x4apply(fm4x4 m, fv3 v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_fm4x4mulv(m, SL_fv4v(v, 1)).xyz;
}
#else
;
#endif
/// @brief Component-wise division of a fm4x4 with a scalar
SL_header fm4x4 SL_fm4x4divs(fm4x4 lhs, float rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (fm4x4) {
        .m00 = lhs.m00 / rhs, .m01 = lhs.m01 / rhs, .m02 = lhs.m02 / rhs, .m03 = lhs.m03 / rhs,
        .m10 = lhs.m10 / rhs, .m11 = lhs.m11 / rhs, .m12 = lhs.m12 / rhs, .m13 = lhs.m13 / rhs,
        .m20 = lhs.m20 / rhs, .m21 = lhs.m21 / rhs, .m22 = lhs.m22 / rhs, .m23 = lhs.m23 / rhs,
        .m30 = lhs.m30 / rhs, .m31 = lhs.m31 / rhs, .m32 = lhs.m32 / rhs, .m33 = lhs.m33 / rhs
    };
}
#else
;
#endif
/// @brief Addition of two fm4x4 with lhs scaled by a float
SL_header fm4x4 SL_fm4x4addS(fm4x4 lhs, fm4x4 rhs, float s)
#if defined(SL_IMPLEMENTATION)
{
    return (fm4x4) {
        .m00 = lhs.m00 + rhs.m00 * s, .m01 = lhs.m01 + rhs.m01 * s, .m02 = lhs.m02 + rhs.m02 * s, .m03 = lhs.m03 + rhs.m03 * s,
        .m10 = lhs.m10 + rhs.m10 * s, .m11 = lhs.m11 + rhs.m11 * s, .m12 = lhs.m12 + rhs.m12 * s, .m13 = lhs.m13 + rhs.m13 * s,
        .m20 = lhs.m20 + rhs.m20 * s, .m21 = lhs.m21 + rhs.m21 * s, .m22 = lhs.m22 + rhs.m22 * s, .m23 = lhs.m23 + rhs.m23 * s,
        .m30 = lhs.m30 + rhs.m30 * s, .m31 = lhs.m31 + rhs.m31 * s, .m32 = lhs.m32 + rhs.m32 * s, .m33 = lhs.m33 + rhs.m33 * s
    };
}
#else
;
#endif
/// @brief Difference of two fm4x4 with lhs scaled by a float
SL_header fm4x4 SL_fm4x4subS(fm4x4 lhs, fm4x4 rhs, float s)
#if defined(SL_IMPLEMENTATION)
{
    return (fm4x4) {
        .m00 = lhs.m00 - rhs.m00 * s, .m01 = lhs.m01 - rhs.m01 * s, .m02 = lhs.m02 - rhs.m02 * s, .m03 = lhs.m03 - rhs.m03 * s,
        .m10 = lhs.m10 - rhs.m10 * s, .m11 = lhs.m11 - rhs.m11 * s, .m12 = lhs.m12 - rhs.m12 * s, .m13 = lhs.m13 - rhs.m13 * s,
        .m20 = lhs.m20 - rhs.m20 * s, .m21 = lhs.m21 - rhs.m21 * s, .m22 = lhs.m22 - rhs.m22 * s, .m23 = lhs.m23 - rhs.m23 * s,
        .m30 = lhs.m30 - rhs.m30 * s, .m31 = lhs.m31 - rhs.m31 * s, .m32 = lhs.m32 - rhs.m32 * s, .m33 = lhs.m33 - rhs.m33 * s
    };
}
#else
;
#endif
/// @brief Negation of a fm4x4
SL_header fm4x4 SL_fm4x4neg(fm4x4 m)
#if defined(SL_IMPLEMENTATION)
{
    return (fm4x4) {
        .m00 = -m.m00, .m01 = -m.m01, .m02 = -m.m02, .m03 = -m.m03,
        .m10 = -m.m10, .m11 = -m.m11, .m12 = -m.m12, .m13 = -m.m13,
        .m20 = -m.m20, .m21 = -m.m21, .m22 = -m.m22, .m23 = -m.m23,
        .m30 = -m.m30, .m31 = -m.m31, .m32 = -m.m32, .m33 = -m.m33
    };
}
#else
;
#endif
/// @brief Component-wise absolute value of a fm4x4
SL_header fm4x4 SL_fm4x4abs(fm4x4 m)
#if defined(SL_IMPLEMENTATION)
{
    return (fm4x4) {
        .m00 = fabs(m.m00), .m01 = fabs(m.m01), .m02 = fabs(m.m02), .m03 = fabs(m.m03),
        .m10 = fabs(m.m10), .m11 = fabs(m.m11), .m12 = fabs(m.m12), .m13 = fabs(m.m13),
        .m20 = fabs(m.m20), .m21 = fabs(m.m21), .m22 = fabs(m.m22), .m23 = fabs(m.m23),
        .m30 = fabs(m.m30), .m31 = fabs(m.m31), .m32 = fabs(m.m32), .m33 = fabs(m.m33)
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two fm4x4
SL_header fm4x4 SL_fm4x4min(fm4x4 lhs, fm4x4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (fm4x4) {
        .m00 = lhs.m00 < rhs.m00 ? lhs.m00 : rhs.m00, .m01 = lhs.m01 < rhs.m01 ? lhs.m01 : rhs.m01, .m02 = lhs.m02 < rhs.m02 ? lhs.m02 : rhs.m02, .m03 = lhs.m03 < rhs.m03 ? lhs.m03 : rhs.m03,
        .m10 = lhs.m10 < rhs.m10 ? lhs.m10 : rhs.m10, .m11 = lhs.m11 < rhs.m11 ? lhs.m11 : rhs.m11, .m12 = lhs.m12 < rhs.m12 ? lhs.m12 : rhs.m12, .m13 = lhs.m13 < rhs.m13 ? lhs.m13 : rhs.m13,
        .m20 = lhs.m20 < rhs.m20 ? lhs.m20 : rhs.m20, .m21 = lhs.m21 < rhs.m21 ? lhs.m21 : rhs.m21, .m22 = lhs.m22 < rhs.m22 ? lhs.m22 : rhs.m22, .m23 = lhs.m23 < rhs.m23 ? lhs.m23 : rhs.m23,
        .m30 = lhs.m30 < rhs.m30 ? lhs.m30 : rhs.m30, .m31 = lhs.m31 < rhs.m31 ? lhs.m31 : rhs.m31, .m32 = lhs.m32 < rhs.m32 ? lhs.m32 : rhs.m32, .m33 = lhs.m33 < rhs.m33 ? lhs.m33 : rhs.m33
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two fm4x4
SL_header fm4x4 SL_fm4x4max(fm4x4 lhs, fm4x4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (fm4x4) {
        .m00 = lhs.m00 > rhs.m00 ? lhs.m00 : rhs.m00, .m01 = lhs.m01 > rhs.m01 ? lhs.m01 : rhs.m01, .m02 = lhs.m02 > rhs.m02 ? lhs.m02 : rhs.m02, .m03 = lhs.m03 > rhs.m03 ? lhs.m03 : rhs.m03,
        .m10 = lhs.m10 > rhs.m10 ? lhs.m10 : rhs.m10, .m11 = lhs.m11 > rhs.m11 ? lhs.m11 : rhs.m11, .m12 = lhs.m12 > rhs.m12 ? lhs.m12 : rhs.m12, .m13 = lhs.m13 > rhs.m13 ? lhs.m13 : rhs.m13,
        .m20 = lhs.m20 > rhs.m20 ? lhs.m20 : rhs.m20, .m21 = lhs.m21 > rhs.m21 ? lhs.m21 : rhs.m21, .m22 = lhs.m22 > rhs.m22 ? lhs.m22 : rhs.m22, .m23 = lhs.m23 > rhs.m23 ? lhs.m23 : rhs.m23,
        .m30 = lhs.m30 > rhs.m30 ? lhs.m30 : rhs.m30, .m31 = lhs.m31 > rhs.m31 ? lhs.m31 : rhs.m31, .m32 = lhs.m32 > rhs.m32 ? lhs.m32 : rhs.m32, .m33 = lhs.m33 > rhs.m33 ? lhs.m33 : rhs.m33
    };
}
#else
;
#endif
/// @brief Transposition of a fm4x4
SL_header fm4x4 SL_fm4x4trsp(fm4x4 m)
#if defined(SL_IMPLEMENTATION)
{
    SL_swap(m.m10, m.m01);
    SL_swap(m.m20, m.m02); SL_swap(m.m12, m.m21);
    SL_swap(m.m30, m.m03); SL_swap(m.m31, m.m13);SL_swap(m.m32, m.m23);
    return m;
}
#else
;
#endif
/// @brief Trace of a fm4x4
SL_header float SL_fm4x4trace(fm4x4 m)
#if defined(SL_IMPLEMENTATION)
{
    return m.m00 + m.m11 + m.m22 + m.m33;
}
#else
;
#endif
/// @brief Determinant of a fm4x4
SL_header float SL_fm4x4det_xpd(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33)
#if defined(SL_IMPLEMENTATION)
{
    return m00 * SL_fm3x3det_xpd(m11, m12, m13, m21, m22, m23, m31, m32, m33)
         + m01 * SL_fm3x3det_xpd(m10, m12, m13, m20, m22, m23, m30, m32, m33)
         + m02 * SL_fm3x3det_xpd(m10, m11, m13, m20, m21, m23, m30, m31, m33)
         + m03 * SL_fm3x3det_xpd(m10, m11, m12, m20, m21, m22, m30, m31, m32);
}
#else
;
#endif
/// @brief Determinant of a fm4x4
SL_header float SL_fm4x4det(fm4x4 m)
#if defined(SL_IMPLEMENTATION)
{
    return SL_fm4x4det_xpd(SL_XPD_M4X4(m));
}
#else
;
#endif
/// @brief Inverse of a fm4x4
SL_header fm4x4 SL_fm4x4inv(fm4x4 m)
#if defined(SL_IMPLEMENTATION)
{
    fm4x4 trsp_comat;
    for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j)
    {
        trsp_comat.m[j][i] = ((i + j) & 1 ? -1 : 1) *
            SL_fm3x3det_xpd(
                m.m[1 - (i >= 1)][1 - (j >= 1)], m.m[1 - (i >= 1)][2 - (j >= 2)], m.m[1 - (i >= 1)][3 - (j >= 3)],
                m.m[2 - (i >= 2)][1 - (j >= 1)], m.m[2 - (i >= 2)][2 - (j >= 2)], m.m[2 - (i >= 2)][3 - (j >= 3)],
                m.m[3 - (i >= 3)][1 - (j >= 1)], m.m[3 - (i >= 3)][2 - (j >= 2)], m.m[3 - (i >= 3)][3 - (j >= 3)]
            );
    }
    
    float det = trsp_comat.m00 * m.m00 + trsp_comat.m01 * m.m10 + trsp_comat.m02 * m.m20 + trsp_comat.m03 * m.m30;
    if (det == 0.0) return __SL_ERROR(SL_ERR_DIVISION_BY_ZERO), SL_fm4x4_zero;

    return SL_fm4x4muls(trsp_comat, 1.0 / det);
}
#else
;
#endif
/// @brief Matrix fm4x4 representing a transformation
SL_header fm4x4 SL_fm4x4from_transform(fv3 position, fq rotation, fv3 scale)
#if defined(SL_IMPLEMENTATION)
{
    fm3x3 rot = SL_fm3x3from_quat(rotation);

    return (fm4x4) {
        .m00 = scale.x * rot.m00, .m01 = scale.y * rot.m01, .m02 = scale.z * rot.m02, .m03 = position.x,
        .m10 = scale.x * rot.m10, .m11 = scale.y * rot.m11, .m12 = scale.z * rot.m12, .m13 = position.y,
        .m20 = scale.x * rot.m20, .m21 = scale.y * rot.m21, .m22 = scale.z * rot.m22, .m23 = position.z,
        .m30 =               0.0, .m31 =               0.0, .m32 =               0.0, .m33 =        1.0
    };
}
#else
;
#endif
/// @brief Matrix fm4x4 representing a projection
SL_header fm4x4 SL_fm4x4from_projection(fv2 planes, fv2 view_size)
#if defined(SL_IMPLEMENTATION)
{
    double idepth = 1.0 / (planes.y - planes.x);

    return (fm4x4) {
        .m00 =       planes.x / view_size.x,
        .m11 =       planes.x / view_size.y,
        .m22 =      (planes.y + planes.x) * idepth, .m32 = 1.0,
        .m23 = -2 * (planes.y * planes.x) * idepth
    };
}
#else
;
#endif



#pragma endregion FLOAT
#pragma region DOUBLE

/// @brief Matrix of double with arbitrary dimensions
typedef struct {
    union { usize r, c; luv2 size; };
    double *data;
} dm;

#define SL_asdm(sized_mat) ((dm){.size = SL_msize(sized_mat), .data = sized_mat.data})





/// @brief Matrix of double of size 2 x 2
typedef union {
    double data[2 * 2];
    double m[2][2];
    struct {
        double m00, m01;
        double m10, m11;
    };
    struct { dv2 r0, r1; };
} dm2x2;

#define SL_dm2x2_zero ((dm2x2){0})
#define SL_dm2x2_identity ((dm2x2){ 1, 0, 0, 1 })


#define SL_dm2x2diag(m00_, m11_) ((dm2x2){.m00 = m00_, .m11 = m11_})

/// @brief Addition of two dm2x2
SL_header dm2x2 SL_dm2x2add(dm2x2 lhs, dm2x2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (dm2x2) {
        .m00 = lhs.m00 + rhs.m00, .m01 = lhs.m01 + rhs.m01,
        .m10 = lhs.m10 + rhs.m10, .m11 = lhs.m11 + rhs.m11
    };
}
#else
;
#endif
/// @brief Difference of two dm2x2
SL_header dm2x2 SL_dm2x2sub(dm2x2 lhs, dm2x2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (dm2x2) {
        .m00 = lhs.m00 - rhs.m00, .m01 = lhs.m01 - rhs.m01,
        .m10 = lhs.m10 - rhs.m10, .m11 = lhs.m11 - rhs.m11
    };
}
#else
;
#endif
/// @brief Product of two dm2x2
SL_header dm2x2 SL_dm2x2mul(dm2x2 lhs, dm2x2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    dm2x2 res = SL_dm2x2_zero;
    for (usize k = 0; k < SL_msize(lhs).x; ++k)
    for (usize j = 0; j < SL_msize(lhs).y; ++j)
    for (usize i = 0; i < SL_msize(lhs).x; ++i)
        res.m[i][j] += lhs.m[i][k] * rhs.m[k][j];

    return res;
}
#else
;
#endif
/// @brief Component-wise multiplication of a dm2x2 with a scalar
SL_header dm2x2 SL_dm2x2muls(dm2x2 lhs, double rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (dm2x2) {
        .m00 = lhs.m00 * rhs, .m01 = lhs.m01 * rhs,
        .m10 = lhs.m10 * rhs, .m11 = lhs.m11 * rhs
    };
}
#else
;
#endif
/// @brief Product of a dm2x2 and a dv2
SL_header dv2 SL_dm2x2mulv(dm2x2 lhs, dv2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_dv2_(SL_dv2dot(lhs.r0, rhs), SL_dv2dot(lhs.r1, rhs));
}
#else
;
#endif
/// @brief Component-wise division of a dm2x2 with a scalar
SL_header dm2x2 SL_dm2x2divs(dm2x2 lhs, double rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (dm2x2) {
        .m00 = lhs.m00 / rhs, .m01 = lhs.m01 / rhs,
        .m10 = lhs.m10 / rhs, .m11 = lhs.m11 / rhs
    };
}
#else
;
#endif
/// @brief Addition of two dm2x2 with lhs scaled by a double
SL_header dm2x2 SL_dm2x2addS(dm2x2 lhs, dm2x2 rhs, double s)
#if defined(SL_IMPLEMENTATION)
{
    return (dm2x2) {
        .m00 = lhs.m00 + rhs.m00 * s, .m01 = lhs.m01 + rhs.m01 * s,
        .m10 = lhs.m10 + rhs.m10 * s, .m11 = lhs.m11 + rhs.m11 * s
    };
}
#else
;
#endif
/// @brief Difference of two dm2x2 with lhs scaled by a double
SL_header dm2x2 SL_dm2x2subS(dm2x2 lhs, dm2x2 rhs, double s)
#if defined(SL_IMPLEMENTATION)
{
    return (dm2x2) {
        .m00 = lhs.m00 - rhs.m00 * s, .m01 = lhs.m01 - rhs.m01 * s,
        .m10 = lhs.m10 - rhs.m10 * s, .m11 = lhs.m11 - rhs.m11 * s
    };
}
#else
;
#endif
/// @brief Negation of a dm2x2
SL_header dm2x2 SL_dm2x2neg(dm2x2 m)
#if defined(SL_IMPLEMENTATION)
{
    return (dm2x2) {
        .m00 = -m.m00, .m01 = -m.m01,
        .m10 = -m.m10, .m11 = -m.m11
    };
}
#else
;
#endif
/// @brief Component-wise absolute value of a dm2x2
SL_header dm2x2 SL_dm2x2abs(dm2x2 m)
#if defined(SL_IMPLEMENTATION)
{
    return (dm2x2) {
        .m00 = fabs(m.m00), .m01 = fabs(m.m01),
        .m10 = fabs(m.m10), .m11 = fabs(m.m11)
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two dm2x2
SL_header dm2x2 SL_dm2x2min(dm2x2 lhs, dm2x2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (dm2x2) {
        .m00 = lhs.m00 < rhs.m00 ? lhs.m00 : rhs.m00, .m01 = lhs.m01 < rhs.m01 ? lhs.m01 : rhs.m01,
        .m10 = lhs.m10 < rhs.m10 ? lhs.m10 : rhs.m10, .m11 = lhs.m11 < rhs.m11 ? lhs.m11 : rhs.m11
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two dm2x2
SL_header dm2x2 SL_dm2x2max(dm2x2 lhs, dm2x2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (dm2x2) {
        .m00 = lhs.m00 > rhs.m00 ? lhs.m00 : rhs.m00, .m01 = lhs.m01 > rhs.m01 ? lhs.m01 : rhs.m01,
        .m10 = lhs.m10 > rhs.m10 ? lhs.m10 : rhs.m10, .m11 = lhs.m11 > rhs.m11 ? lhs.m11 : rhs.m11
    };
}
#else
;
#endif
/// @brief Transposition of a dm2x2
SL_header dm2x2 SL_dm2x2trsp(dm2x2 m)
#if defined(SL_IMPLEMENTATION)
{
    SL_swap(m.m10, m.m01);
    return m;
}
#else
;
#endif
/// @brief Trace of a dm2x2
SL_header double SL_dm2x2trace(dm2x2 m)
#if defined(SL_IMPLEMENTATION)
{
    return m.m00 + m.m11;
}
#else
;
#endif
/// @brief Determinant of a dm2x2
SL_header double SL_dm2x2det_xpd(double m00, double m01, double m10, double m11)
#if defined(SL_IMPLEMENTATION)
{
    return m00 * m11 - m01 * m10;
}
#else
;
#endif
/// @brief Determinant of a dm2x2
SL_header double SL_dm2x2det(dm2x2 m)
#if defined(SL_IMPLEMENTATION)
{
    return SL_dm2x2det_xpd(SL_XPD_M2X2(m));
}
#else
;
#endif
/// @brief Inverse of a dm2x2
SL_header dm2x2 SL_dm2x2inv(dm2x2 m)
#if defined(SL_IMPLEMENTATION)
{
    dm2x2 trsp_comat = { .m00 = m.m11, .m10 = -m.m10, .m10 = -m.m10, .m11 = m.m00 };
    
    double det = trsp_comat.m00 * m.m00 + trsp_comat.m01 * m.m10;
    if (det == 0.0) return __SL_ERROR(SL_ERR_DIVISION_BY_ZERO), SL_dm2x2_zero;

    return SL_dm2x2muls(trsp_comat, 1.0 / det);
}
#else
;
#endif
/// @brief Matrix dm2x2 representing a 2D rotation
SL_header dm2x2 SL_dm2x2from_angle(double angle)
#if defined(SL_IMPLEMENTATION)
{
    double sin, cos; sincos(angle, &sin, &cos);

    return (dm2x2) {
        .m00 = -sin, .m01 = cos,
        .m10 =  cos, .m11 = sin
    };
}
#else
;
#endif



/// @brief Matrix of double of size 3 x 3
typedef union {
    double data[3 * 3];
    double m[3][3];
    struct {
        double m00, m01, m02;
        double m10, m11, m12;
        double m20, m21, m22;
    };
    struct { dv3 r0, r1, r2; };
} dm3x3;

#define SL_dm3x3_zero ((dm3x3){0})
#define SL_dm3x3_identity ((dm3x3){ 1, 0, 0, 0, 1, 0, 0, 0, 1 })


#define SL_dm3x3diag(m00_, m11_, m22_) ((dm3x3){.m00 = m00_, .m11 = m11_, .m22 = m22_})

/// @brief Addition of two dm3x3
SL_header dm3x3 SL_dm3x3add(dm3x3 lhs, dm3x3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (dm3x3) {
        .m00 = lhs.m00 + rhs.m00, .m01 = lhs.m01 + rhs.m01, .m02 = lhs.m02 + rhs.m02,
        .m10 = lhs.m10 + rhs.m10, .m11 = lhs.m11 + rhs.m11, .m12 = lhs.m12 + rhs.m12,
        .m20 = lhs.m20 + rhs.m20, .m21 = lhs.m21 + rhs.m21, .m22 = lhs.m22 + rhs.m22
    };
}
#else
;
#endif
/// @brief Difference of two dm3x3
SL_header dm3x3 SL_dm3x3sub(dm3x3 lhs, dm3x3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (dm3x3) {
        .m00 = lhs.m00 - rhs.m00, .m01 = lhs.m01 - rhs.m01, .m02 = lhs.m02 - rhs.m02,
        .m10 = lhs.m10 - rhs.m10, .m11 = lhs.m11 - rhs.m11, .m12 = lhs.m12 - rhs.m12,
        .m20 = lhs.m20 - rhs.m20, .m21 = lhs.m21 - rhs.m21, .m22 = lhs.m22 - rhs.m22
    };
}
#else
;
#endif
/// @brief Product of two dm3x3
SL_header dm3x3 SL_dm3x3mul(dm3x3 lhs, dm3x3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    dm3x3 res = SL_dm3x3_zero;
    for (usize k = 0; k < SL_msize(lhs).x; ++k)
    for (usize j = 0; j < SL_msize(lhs).y; ++j)
    for (usize i = 0; i < SL_msize(lhs).x; ++i)
        res.m[i][j] += lhs.m[i][k] * rhs.m[k][j];

    return res;
}
#else
;
#endif
/// @brief Component-wise multiplication of a dm3x3 with a scalar
SL_header dm3x3 SL_dm3x3muls(dm3x3 lhs, double rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (dm3x3) {
        .m00 = lhs.m00 * rhs, .m01 = lhs.m01 * rhs, .m02 = lhs.m02 * rhs,
        .m10 = lhs.m10 * rhs, .m11 = lhs.m11 * rhs, .m12 = lhs.m12 * rhs,
        .m20 = lhs.m20 * rhs, .m21 = lhs.m21 * rhs, .m22 = lhs.m22 * rhs
    };
}
#else
;
#endif
/// @brief Product of a dm3x3 and a dv3
SL_header dv3 SL_dm3x3mulv(dm3x3 lhs, dv3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_dv3_(SL_dv3dot(lhs.r0, rhs), SL_dv3dot(lhs.r1, rhs), SL_dv3dot(lhs.r2, rhs));
}
#else
;
#endif
/// @brief Apply transformation represented by dm3x3 to a dv2
SL_header dv2 SL_dm3x3apply(dm3x3 m, dv2 v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_dm3x3mulv(m, SL_dv3v(v, 1)).xy;
}
#else
;
#endif
/// @brief Component-wise division of a dm3x3 with a scalar
SL_header dm3x3 SL_dm3x3divs(dm3x3 lhs, double rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (dm3x3) {
        .m00 = lhs.m00 / rhs, .m01 = lhs.m01 / rhs, .m02 = lhs.m02 / rhs,
        .m10 = lhs.m10 / rhs, .m11 = lhs.m11 / rhs, .m12 = lhs.m12 / rhs,
        .m20 = lhs.m20 / rhs, .m21 = lhs.m21 / rhs, .m22 = lhs.m22 / rhs
    };
}
#else
;
#endif
/// @brief Addition of two dm3x3 with lhs scaled by a double
SL_header dm3x3 SL_dm3x3addS(dm3x3 lhs, dm3x3 rhs, double s)
#if defined(SL_IMPLEMENTATION)
{
    return (dm3x3) {
        .m00 = lhs.m00 + rhs.m00 * s, .m01 = lhs.m01 + rhs.m01 * s, .m02 = lhs.m02 + rhs.m02 * s,
        .m10 = lhs.m10 + rhs.m10 * s, .m11 = lhs.m11 + rhs.m11 * s, .m12 = lhs.m12 + rhs.m12 * s,
        .m20 = lhs.m20 + rhs.m20 * s, .m21 = lhs.m21 + rhs.m21 * s, .m22 = lhs.m22 + rhs.m22 * s
    };
}
#else
;
#endif
/// @brief Difference of two dm3x3 with lhs scaled by a double
SL_header dm3x3 SL_dm3x3subS(dm3x3 lhs, dm3x3 rhs, double s)
#if defined(SL_IMPLEMENTATION)
{
    return (dm3x3) {
        .m00 = lhs.m00 - rhs.m00 * s, .m01 = lhs.m01 - rhs.m01 * s, .m02 = lhs.m02 - rhs.m02 * s,
        .m10 = lhs.m10 - rhs.m10 * s, .m11 = lhs.m11 - rhs.m11 * s, .m12 = lhs.m12 - rhs.m12 * s,
        .m20 = lhs.m20 - rhs.m20 * s, .m21 = lhs.m21 - rhs.m21 * s, .m22 = lhs.m22 - rhs.m22 * s
    };
}
#else
;
#endif
/// @brief Negation of a dm3x3
SL_header dm3x3 SL_dm3x3neg(dm3x3 m)
#if defined(SL_IMPLEMENTATION)
{
    return (dm3x3) {
        .m00 = -m.m00, .m01 = -m.m01, .m02 = -m.m02,
        .m10 = -m.m10, .m11 = -m.m11, .m12 = -m.m12,
        .m20 = -m.m20, .m21 = -m.m21, .m22 = -m.m22
    };
}
#else
;
#endif
/// @brief Component-wise absolute value of a dm3x3
SL_header dm3x3 SL_dm3x3abs(dm3x3 m)
#if defined(SL_IMPLEMENTATION)
{
    return (dm3x3) {
        .m00 = fabs(m.m00), .m01 = fabs(m.m01), .m02 = fabs(m.m02),
        .m10 = fabs(m.m10), .m11 = fabs(m.m11), .m12 = fabs(m.m12),
        .m20 = fabs(m.m20), .m21 = fabs(m.m21), .m22 = fabs(m.m22)
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two dm3x3
SL_header dm3x3 SL_dm3x3min(dm3x3 lhs, dm3x3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (dm3x3) {
        .m00 = lhs.m00 < rhs.m00 ? lhs.m00 : rhs.m00, .m01 = lhs.m01 < rhs.m01 ? lhs.m01 : rhs.m01, .m02 = lhs.m02 < rhs.m02 ? lhs.m02 : rhs.m02,
        .m10 = lhs.m10 < rhs.m10 ? lhs.m10 : rhs.m10, .m11 = lhs.m11 < rhs.m11 ? lhs.m11 : rhs.m11, .m12 = lhs.m12 < rhs.m12 ? lhs.m12 : rhs.m12,
        .m20 = lhs.m20 < rhs.m20 ? lhs.m20 : rhs.m20, .m21 = lhs.m21 < rhs.m21 ? lhs.m21 : rhs.m21, .m22 = lhs.m22 < rhs.m22 ? lhs.m22 : rhs.m22
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two dm3x3
SL_header dm3x3 SL_dm3x3max(dm3x3 lhs, dm3x3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (dm3x3) {
        .m00 = lhs.m00 > rhs.m00 ? lhs.m00 : rhs.m00, .m01 = lhs.m01 > rhs.m01 ? lhs.m01 : rhs.m01, .m02 = lhs.m02 > rhs.m02 ? lhs.m02 : rhs.m02,
        .m10 = lhs.m10 > rhs.m10 ? lhs.m10 : rhs.m10, .m11 = lhs.m11 > rhs.m11 ? lhs.m11 : rhs.m11, .m12 = lhs.m12 > rhs.m12 ? lhs.m12 : rhs.m12,
        .m20 = lhs.m20 > rhs.m20 ? lhs.m20 : rhs.m20, .m21 = lhs.m21 > rhs.m21 ? lhs.m21 : rhs.m21, .m22 = lhs.m22 > rhs.m22 ? lhs.m22 : rhs.m22
    };
}
#else
;
#endif
/// @brief Transposition of a dm3x3
SL_header dm3x3 SL_dm3x3trsp(dm3x3 m)
#if defined(SL_IMPLEMENTATION)
{
    SL_swap(m.m10, m.m01);
    SL_swap(m.m20, m.m02); SL_swap(m.m21, m.m12);
    return m;
}
#else
;
#endif
/// @brief Trace of a dm3x3
SL_header double SL_dm3x3trace(dm3x3 m)
#if defined(SL_IMPLEMENTATION)
{
    return m.m00 + m.m11 + m.m22;
}
#else
;
#endif
/// @brief Determinant of a dm3x3
SL_header double SL_dm3x3det_xpd(double m00, double m01, double m02, double m10, double m11, double m12, double m20, double m21, double m22)
#if defined(SL_IMPLEMENTATION)
{
    return m00 * m11 * m22 + m01 * m12 * m20 + m02 * m10 * m21 - m02 * m11 * m20 - m12 * m21 * m00 - m22 * m01 * m10;
}
#else
;
#endif
/// @brief Determinant of a dm3x3
SL_header double SL_dm3x3det(dm3x3 m)
#if defined(SL_IMPLEMENTATION)
{
    return SL_dm3x3det_xpd(SL_XPD_M3X3(m));
}
#else
;
#endif
/// @brief Inverse of a dm3x3
SL_header dm3x3 SL_dm3x3inv(dm3x3 m)
#if defined(SL_IMPLEMENTATION)
{
    dm3x3 trsp_comat;
    for (int i = 0; i < 3; ++i)
    for (int j = 0; j < 3; ++j)
    {
        trsp_comat.m[j][i] = ((i + j) & 1 ? -1 : 1) *
            SL_dm2x2det_xpd(
                m.m[1 - (i >= 1)][1 - (j >= 1)], m.m[1 - (i >= 1)][2 - (j >= 2)],
                m.m[2 - (i >= 2)][1 - (j >= 1)], m.m[2 - (i >= 2)][2 - (j >= 2)]
            );
    }
    
    double det = trsp_comat.m00 * m.m00 + trsp_comat.m01 * m.m10 + trsp_comat.m02 * m.m20;
    if (det == 0.0) return __SL_ERROR(SL_ERR_DIVISION_BY_ZERO), SL_dm3x3_zero;

    return SL_dm3x3muls(trsp_comat, 1.0 / det);
}
#else
;
#endif
/// @brief Matrix dm3x3 from a double
SL_header dm3x3 SL_dm3x3from_quat(dq quat)
#if defined(SL_IMPLEMENTATION)
{
    double wx = quat.w*quat.x, wy = quat.w*quat.y, wz = quat.w*quat.z, xy = quat.x*quat.y, yz = quat.y*quat.z, xz = quat.x*quat.z;
    double w2 = quat.w*quat.w, x2 = quat.x*quat.x, y2 = quat.y*quat.y, z2 = quat.z*quat.z;

    return (dm3x3) {
        .m00 = w2 + x2 - y2 - z2, .m10 = 2 * (xy - wz),     .m20 = 2 * (xz + wy),
        .m01 = 2 * (xy + wz),     .m11 = w2 - x2 + y2 - z2, .m21 = 2 * (yz - wx),
        .m02 = 2 * (xz - wy),     .m12 = 2 * (yz + wx),     .m22 = w2 - x2 - y2 + z2
    };
}
#else
;
#endif
/// @brief Matrix dm3x3 representing a transformation
SL_header dm3x3 SL_dm3x3from_transform(dv2 position, double rotation, dv2 scale)
#if defined(SL_IMPLEMENTATION)
{
    double sin, cos; sincos(rotation, &sin, &cos);

    return (dm3x3) {
        .m00 = scale.x * cos, .m01 = scale.y * -sin, .m02 = position.x,
        .m10 = scale.x * sin, .m11 = scale.y *  cos, .m12 = position.y,
        .m20 =           0.0, .m21 =            0.0, .m22 =        1.0
    };
}
#else
;
#endif



/// @brief Matrix of double of size 4 x 4
typedef union {
    double data[4 * 4];
    double m[4][4];
    struct {
        double m00, m01, m02, m03;
        double m10, m11, m12, m13;
        double m20, m21, m22, m23;
        double m30, m31, m32, m33;
    };
    struct { dv4 r0, r1, r2, r3; };
} dm4x4;

#define SL_dm4x4_zero ((dm4x4){0})
#define SL_dm4x4_identity ((dm4x4){ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 })


#define SL_dm4x4diag(m00_, m11_, m22_, m33_) ((dm4x4){.m00 = m00_, .m11 = m11_, .m22 = m22_, .m33 = m33_})

/// @brief Addition of two dm4x4
SL_header dm4x4 SL_dm4x4add(dm4x4 lhs, dm4x4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (dm4x4) {
        .m00 = lhs.m00 + rhs.m00, .m01 = lhs.m01 + rhs.m01, .m02 = lhs.m02 + rhs.m02, .m03 = lhs.m03 + rhs.m03,
        .m10 = lhs.m10 + rhs.m10, .m11 = lhs.m11 + rhs.m11, .m12 = lhs.m12 + rhs.m12, .m13 = lhs.m13 + rhs.m13,
        .m20 = lhs.m20 + rhs.m20, .m21 = lhs.m21 + rhs.m21, .m22 = lhs.m22 + rhs.m22, .m23 = lhs.m23 + rhs.m23,
        .m30 = lhs.m30 + rhs.m30, .m31 = lhs.m31 + rhs.m31, .m32 = lhs.m32 + rhs.m32, .m33 = lhs.m33 + rhs.m33
    };
}
#else
;
#endif
/// @brief Difference of two dm4x4
SL_header dm4x4 SL_dm4x4sub(dm4x4 lhs, dm4x4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (dm4x4) {
        .m00 = lhs.m00 - rhs.m00, .m01 = lhs.m01 - rhs.m01, .m02 = lhs.m02 - rhs.m02, .m03 = lhs.m03 - rhs.m03,
        .m10 = lhs.m10 - rhs.m10, .m11 = lhs.m11 - rhs.m11, .m12 = lhs.m12 - rhs.m12, .m13 = lhs.m13 - rhs.m13,
        .m20 = lhs.m20 - rhs.m20, .m21 = lhs.m21 - rhs.m21, .m22 = lhs.m22 - rhs.m22, .m23 = lhs.m23 - rhs.m23,
        .m30 = lhs.m30 - rhs.m30, .m31 = lhs.m31 - rhs.m31, .m32 = lhs.m32 - rhs.m32, .m33 = lhs.m33 - rhs.m33
    };
}
#else
;
#endif
/// @brief Product of two dm4x4
SL_header dm4x4 SL_dm4x4mul(dm4x4 lhs, dm4x4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    dm4x4 res = SL_dm4x4_zero;
    for (usize k = 0; k < SL_msize(lhs).x; ++k)
    for (usize j = 0; j < SL_msize(lhs).y; ++j)
    for (usize i = 0; i < SL_msize(lhs).x; ++i)
        res.m[i][j] += lhs.m[i][k] * rhs.m[k][j];

    return res;
}
#else
;
#endif
/// @brief Component-wise multiplication of a dm4x4 with a scalar
SL_header dm4x4 SL_dm4x4muls(dm4x4 lhs, double rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (dm4x4) {
        .m00 = lhs.m00 * rhs, .m01 = lhs.m01 * rhs, .m02 = lhs.m02 * rhs, .m03 = lhs.m03 * rhs,
        .m10 = lhs.m10 * rhs, .m11 = lhs.m11 * rhs, .m12 = lhs.m12 * rhs, .m13 = lhs.m13 * rhs,
        .m20 = lhs.m20 * rhs, .m21 = lhs.m21 * rhs, .m22 = lhs.m22 * rhs, .m23 = lhs.m23 * rhs,
        .m30 = lhs.m30 * rhs, .m31 = lhs.m31 * rhs, .m32 = lhs.m32 * rhs, .m33 = lhs.m33 * rhs
    };
}
#else
;
#endif
/// @brief Product of a dm4x4 and a dv4
SL_header dv4 SL_dm4x4mulv(dm4x4 lhs, dv4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_dv4_(SL_dv4dot(lhs.r0, rhs), SL_dv4dot(lhs.r1, rhs), SL_dv4dot(lhs.r2, rhs), SL_dv4dot(lhs.r3, rhs));
}
#else
;
#endif
/// @brief Apply transformation represented by dm4x4 to a dv3
SL_header dv3 SL_dm4x4apply(dm4x4 m, dv3 v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_dm4x4mulv(m, SL_dv4v(v, 1)).xyz;
}
#else
;
#endif
/// @brief Component-wise division of a dm4x4 with a scalar
SL_header dm4x4 SL_dm4x4divs(dm4x4 lhs, double rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (dm4x4) {
        .m00 = lhs.m00 / rhs, .m01 = lhs.m01 / rhs, .m02 = lhs.m02 / rhs, .m03 = lhs.m03 / rhs,
        .m10 = lhs.m10 / rhs, .m11 = lhs.m11 / rhs, .m12 = lhs.m12 / rhs, .m13 = lhs.m13 / rhs,
        .m20 = lhs.m20 / rhs, .m21 = lhs.m21 / rhs, .m22 = lhs.m22 / rhs, .m23 = lhs.m23 / rhs,
        .m30 = lhs.m30 / rhs, .m31 = lhs.m31 / rhs, .m32 = lhs.m32 / rhs, .m33 = lhs.m33 / rhs
    };
}
#else
;
#endif
/// @brief Addition of two dm4x4 with lhs scaled by a double
SL_header dm4x4 SL_dm4x4addS(dm4x4 lhs, dm4x4 rhs, double s)
#if defined(SL_IMPLEMENTATION)
{
    return (dm4x4) {
        .m00 = lhs.m00 + rhs.m00 * s, .m01 = lhs.m01 + rhs.m01 * s, .m02 = lhs.m02 + rhs.m02 * s, .m03 = lhs.m03 + rhs.m03 * s,
        .m10 = lhs.m10 + rhs.m10 * s, .m11 = lhs.m11 + rhs.m11 * s, .m12 = lhs.m12 + rhs.m12 * s, .m13 = lhs.m13 + rhs.m13 * s,
        .m20 = lhs.m20 + rhs.m20 * s, .m21 = lhs.m21 + rhs.m21 * s, .m22 = lhs.m22 + rhs.m22 * s, .m23 = lhs.m23 + rhs.m23 * s,
        .m30 = lhs.m30 + rhs.m30 * s, .m31 = lhs.m31 + rhs.m31 * s, .m32 = lhs.m32 + rhs.m32 * s, .m33 = lhs.m33 + rhs.m33 * s
    };
}
#else
;
#endif
/// @brief Difference of two dm4x4 with lhs scaled by a double
SL_header dm4x4 SL_dm4x4subS(dm4x4 lhs, dm4x4 rhs, double s)
#if defined(SL_IMPLEMENTATION)
{
    return (dm4x4) {
        .m00 = lhs.m00 - rhs.m00 * s, .m01 = lhs.m01 - rhs.m01 * s, .m02 = lhs.m02 - rhs.m02 * s, .m03 = lhs.m03 - rhs.m03 * s,
        .m10 = lhs.m10 - rhs.m10 * s, .m11 = lhs.m11 - rhs.m11 * s, .m12 = lhs.m12 - rhs.m12 * s, .m13 = lhs.m13 - rhs.m13 * s,
        .m20 = lhs.m20 - rhs.m20 * s, .m21 = lhs.m21 - rhs.m21 * s, .m22 = lhs.m22 - rhs.m22 * s, .m23 = lhs.m23 - rhs.m23 * s,
        .m30 = lhs.m30 - rhs.m30 * s, .m31 = lhs.m31 - rhs.m31 * s, .m32 = lhs.m32 - rhs.m32 * s, .m33 = lhs.m33 - rhs.m33 * s
    };
}
#else
;
#endif
/// @brief Negation of a dm4x4
SL_header dm4x4 SL_dm4x4neg(dm4x4 m)
#if defined(SL_IMPLEMENTATION)
{
    return (dm4x4) {
        .m00 = -m.m00, .m01 = -m.m01, .m02 = -m.m02, .m03 = -m.m03,
        .m10 = -m.m10, .m11 = -m.m11, .m12 = -m.m12, .m13 = -m.m13,
        .m20 = -m.m20, .m21 = -m.m21, .m22 = -m.m22, .m23 = -m.m23,
        .m30 = -m.m30, .m31 = -m.m31, .m32 = -m.m32, .m33 = -m.m33
    };
}
#else
;
#endif
/// @brief Component-wise absolute value of a dm4x4
SL_header dm4x4 SL_dm4x4abs(dm4x4 m)
#if defined(SL_IMPLEMENTATION)
{
    return (dm4x4) {
        .m00 = fabs(m.m00), .m01 = fabs(m.m01), .m02 = fabs(m.m02), .m03 = fabs(m.m03),
        .m10 = fabs(m.m10), .m11 = fabs(m.m11), .m12 = fabs(m.m12), .m13 = fabs(m.m13),
        .m20 = fabs(m.m20), .m21 = fabs(m.m21), .m22 = fabs(m.m22), .m23 = fabs(m.m23),
        .m30 = fabs(m.m30), .m31 = fabs(m.m31), .m32 = fabs(m.m32), .m33 = fabs(m.m33)
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two dm4x4
SL_header dm4x4 SL_dm4x4min(dm4x4 lhs, dm4x4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (dm4x4) {
        .m00 = lhs.m00 < rhs.m00 ? lhs.m00 : rhs.m00, .m01 = lhs.m01 < rhs.m01 ? lhs.m01 : rhs.m01, .m02 = lhs.m02 < rhs.m02 ? lhs.m02 : rhs.m02, .m03 = lhs.m03 < rhs.m03 ? lhs.m03 : rhs.m03,
        .m10 = lhs.m10 < rhs.m10 ? lhs.m10 : rhs.m10, .m11 = lhs.m11 < rhs.m11 ? lhs.m11 : rhs.m11, .m12 = lhs.m12 < rhs.m12 ? lhs.m12 : rhs.m12, .m13 = lhs.m13 < rhs.m13 ? lhs.m13 : rhs.m13,
        .m20 = lhs.m20 < rhs.m20 ? lhs.m20 : rhs.m20, .m21 = lhs.m21 < rhs.m21 ? lhs.m21 : rhs.m21, .m22 = lhs.m22 < rhs.m22 ? lhs.m22 : rhs.m22, .m23 = lhs.m23 < rhs.m23 ? lhs.m23 : rhs.m23,
        .m30 = lhs.m30 < rhs.m30 ? lhs.m30 : rhs.m30, .m31 = lhs.m31 < rhs.m31 ? lhs.m31 : rhs.m31, .m32 = lhs.m32 < rhs.m32 ? lhs.m32 : rhs.m32, .m33 = lhs.m33 < rhs.m33 ? lhs.m33 : rhs.m33
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two dm4x4
SL_header dm4x4 SL_dm4x4max(dm4x4 lhs, dm4x4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (dm4x4) {
        .m00 = lhs.m00 > rhs.m00 ? lhs.m00 : rhs.m00, .m01 = lhs.m01 > rhs.m01 ? lhs.m01 : rhs.m01, .m02 = lhs.m02 > rhs.m02 ? lhs.m02 : rhs.m02, .m03 = lhs.m03 > rhs.m03 ? lhs.m03 : rhs.m03,
        .m10 = lhs.m10 > rhs.m10 ? lhs.m10 : rhs.m10, .m11 = lhs.m11 > rhs.m11 ? lhs.m11 : rhs.m11, .m12 = lhs.m12 > rhs.m12 ? lhs.m12 : rhs.m12, .m13 = lhs.m13 > rhs.m13 ? lhs.m13 : rhs.m13,
        .m20 = lhs.m20 > rhs.m20 ? lhs.m20 : rhs.m20, .m21 = lhs.m21 > rhs.m21 ? lhs.m21 : rhs.m21, .m22 = lhs.m22 > rhs.m22 ? lhs.m22 : rhs.m22, .m23 = lhs.m23 > rhs.m23 ? lhs.m23 : rhs.m23,
        .m30 = lhs.m30 > rhs.m30 ? lhs.m30 : rhs.m30, .m31 = lhs.m31 > rhs.m31 ? lhs.m31 : rhs.m31, .m32 = lhs.m32 > rhs.m32 ? lhs.m32 : rhs.m32, .m33 = lhs.m33 > rhs.m33 ? lhs.m33 : rhs.m33
    };
}
#else
;
#endif
/// @brief Transposition of a dm4x4
SL_header dm4x4 SL_dm4x4trsp(dm4x4 m)
#if defined(SL_IMPLEMENTATION)
{
    SL_swap(m.m10, m.m01);
    SL_swap(m.m20, m.m02); SL_swap(m.m12, m.m21);
    SL_swap(m.m30, m.m03); SL_swap(m.m31, m.m13);SL_swap(m.m32, m.m23);
    return m;
}
#else
;
#endif
/// @brief Trace of a dm4x4
SL_header double SL_dm4x4trace(dm4x4 m)
#if defined(SL_IMPLEMENTATION)
{
    return m.m00 + m.m11 + m.m22 + m.m33;
}
#else
;
#endif
/// @brief Determinant of a dm4x4
SL_header double SL_dm4x4det_xpd(double m00, double m01, double m02, double m03, double m10, double m11, double m12, double m13, double m20, double m21, double m22, double m23, double m30, double m31, double m32, double m33)
#if defined(SL_IMPLEMENTATION)
{
    return m00 * SL_dm3x3det_xpd(m11, m12, m13, m21, m22, m23, m31, m32, m33)
         + m01 * SL_dm3x3det_xpd(m10, m12, m13, m20, m22, m23, m30, m32, m33)
         + m02 * SL_dm3x3det_xpd(m10, m11, m13, m20, m21, m23, m30, m31, m33)
         + m03 * SL_dm3x3det_xpd(m10, m11, m12, m20, m21, m22, m30, m31, m32);
}
#else
;
#endif
/// @brief Determinant of a dm4x4
SL_header double SL_dm4x4det(dm4x4 m)
#if defined(SL_IMPLEMENTATION)
{
    return SL_dm4x4det_xpd(SL_XPD_M4X4(m));
}
#else
;
#endif
/// @brief Inverse of a dm4x4
SL_header dm4x4 SL_dm4x4inv(dm4x4 m)
#if defined(SL_IMPLEMENTATION)
{
    dm4x4 trsp_comat;
    for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j)
    {
        trsp_comat.m[j][i] = ((i + j) & 1 ? -1 : 1) *
            SL_dm3x3det_xpd(
                m.m[1 - (i >= 1)][1 - (j >= 1)], m.m[1 - (i >= 1)][2 - (j >= 2)], m.m[1 - (i >= 1)][3 - (j >= 3)],
                m.m[2 - (i >= 2)][1 - (j >= 1)], m.m[2 - (i >= 2)][2 - (j >= 2)], m.m[2 - (i >= 2)][3 - (j >= 3)],
                m.m[3 - (i >= 3)][1 - (j >= 1)], m.m[3 - (i >= 3)][2 - (j >= 2)], m.m[3 - (i >= 3)][3 - (j >= 3)]
            );
    }
    
    double det = trsp_comat.m00 * m.m00 + trsp_comat.m01 * m.m10 + trsp_comat.m02 * m.m20 + trsp_comat.m03 * m.m30;
    if (det == 0.0) return __SL_ERROR(SL_ERR_DIVISION_BY_ZERO), SL_dm4x4_zero;

    return SL_dm4x4muls(trsp_comat, 1.0 / det);
}
#else
;
#endif
/// @brief Matrix dm4x4 representing a transformation
SL_header dm4x4 SL_dm4x4from_transform(dv3 position, dq rotation, dv3 scale)
#if defined(SL_IMPLEMENTATION)
{
    dm3x3 rot = SL_dm3x3from_quat(rotation);

    return (dm4x4) {
        .m00 = scale.x * rot.m00, .m01 = scale.y * rot.m01, .m02 = scale.z * rot.m02, .m03 = position.x,
        .m10 = scale.x * rot.m10, .m11 = scale.y * rot.m11, .m12 = scale.z * rot.m12, .m13 = position.y,
        .m20 = scale.x * rot.m20, .m21 = scale.y * rot.m21, .m22 = scale.z * rot.m22, .m23 = position.z,
        .m30 =               0.0, .m31 =               0.0, .m32 =               0.0, .m33 =        1.0
    };
}
#else
;
#endif
/// @brief Matrix dm4x4 representing a projection
SL_header dm4x4 SL_dm4x4from_projection(dv2 planes, dv2 view_size)
#if defined(SL_IMPLEMENTATION)
{
    double idepth = 1.0 / (planes.y - planes.x);

    return (dm4x4) {
        .m00 =       planes.x / view_size.x,
        .m11 =       planes.x / view_size.y,
        .m22 =      (planes.y + planes.x) * idepth, .m32 = 1.0,
        .m23 = -2 * (planes.y * planes.x) * idepth
    };
}
#else
;
#endif



#pragma endregion DOUBLE
#pragma region BOOL

/// @brief Matrix of bool with arbitrary dimensions
typedef struct {
    union { usize r, c; luv2 size; };
    bool *data;
} bm;

#define SL_asbm(sized_mat) ((bm){.size = SL_msize(sized_mat), .data = sized_mat.data})





/// @brief Matrix of bool of size 2 x 2
typedef union {
    bool data[2 * 2];
    bool m[2][2];
    struct {
        bool m00, m01;
        bool m10, m11;
    };
    struct { bv2 r0, r1; };
} bm2x2;

#define SL_bm2x2_zero ((bm2x2){0})
#define SL_bm2x2_identity ((bm2x2){ 1, 0, 0, 1 })


#define SL_bm2x2diag(m00_, m11_) ((bm2x2){.m00 = m00_, .m11 = m11_})

/// @brief Addition of two bm2x2
SL_header bm2x2 SL_bm2x2add(bm2x2 lhs, bm2x2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bm2x2) {
        .m00 = lhs.m00 + rhs.m00, .m01 = lhs.m01 + rhs.m01,
        .m10 = lhs.m10 + rhs.m10, .m11 = lhs.m11 + rhs.m11
    };
}
#else
;
#endif
/// @brief Difference of two bm2x2
SL_header bm2x2 SL_bm2x2sub(bm2x2 lhs, bm2x2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bm2x2) {
        .m00 = lhs.m00 - rhs.m00, .m01 = lhs.m01 - rhs.m01,
        .m10 = lhs.m10 - rhs.m10, .m11 = lhs.m11 - rhs.m11
    };
}
#else
;
#endif
/// @brief Product of two bm2x2
SL_header bm2x2 SL_bm2x2mul(bm2x2 lhs, bm2x2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    bm2x2 res = SL_bm2x2_zero;
    for (usize k = 0; k < SL_msize(lhs).x; ++k)
    for (usize j = 0; j < SL_msize(lhs).y; ++j)
    for (usize i = 0; i < SL_msize(lhs).x; ++i)
        res.m[i][j] += lhs.m[i][k] * rhs.m[k][j];

    return res;
}
#else
;
#endif
/// @brief Component-wise multiplication of a bm2x2 with a scalar
SL_header bm2x2 SL_bm2x2muls(bm2x2 lhs, bool rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bm2x2) {
        .m00 = lhs.m00 * rhs, .m01 = lhs.m01 * rhs,
        .m10 = lhs.m10 * rhs, .m11 = lhs.m11 * rhs
    };
}
#else
;
#endif
/// @brief Product of a bm2x2 and a bv2
SL_header bv2 SL_bm2x2mulv(bm2x2 lhs, bv2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_bv2_(SL_bv2dot(lhs.r0, rhs), SL_bv2dot(lhs.r1, rhs));
}
#else
;
#endif
/// @brief Component-wise division of a bm2x2 with a scalar
SL_header bm2x2 SL_bm2x2divs(bm2x2 lhs, bool rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bm2x2) {
        .m00 = lhs.m00 / rhs, .m01 = lhs.m01 / rhs,
        .m10 = lhs.m10 / rhs, .m11 = lhs.m11 / rhs
    };
}
#else
;
#endif
/// @brief Addition of two bm2x2 with lhs scaled by a bool
SL_header bm2x2 SL_bm2x2addS(bm2x2 lhs, bm2x2 rhs, bool s)
#if defined(SL_IMPLEMENTATION)
{
    return (bm2x2) {
        .m00 = lhs.m00 + rhs.m00 * s, .m01 = lhs.m01 + rhs.m01 * s,
        .m10 = lhs.m10 + rhs.m10 * s, .m11 = lhs.m11 + rhs.m11 * s
    };
}
#else
;
#endif
/// @brief Difference of two bm2x2 with lhs scaled by a bool
SL_header bm2x2 SL_bm2x2subS(bm2x2 lhs, bm2x2 rhs, bool s)
#if defined(SL_IMPLEMENTATION)
{
    return (bm2x2) {
        .m00 = lhs.m00 - rhs.m00 * s, .m01 = lhs.m01 - rhs.m01 * s,
        .m10 = lhs.m10 - rhs.m10 * s, .m11 = lhs.m11 - rhs.m11 * s
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two bm2x2
SL_header bm2x2 SL_bm2x2min(bm2x2 lhs, bm2x2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bm2x2) {
        .m00 = lhs.m00 < rhs.m00 ? lhs.m00 : rhs.m00, .m01 = lhs.m01 < rhs.m01 ? lhs.m01 : rhs.m01,
        .m10 = lhs.m10 < rhs.m10 ? lhs.m10 : rhs.m10, .m11 = lhs.m11 < rhs.m11 ? lhs.m11 : rhs.m11
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two bm2x2
SL_header bm2x2 SL_bm2x2max(bm2x2 lhs, bm2x2 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bm2x2) {
        .m00 = lhs.m00 > rhs.m00 ? lhs.m00 : rhs.m00, .m01 = lhs.m01 > rhs.m01 ? lhs.m01 : rhs.m01,
        .m10 = lhs.m10 > rhs.m10 ? lhs.m10 : rhs.m10, .m11 = lhs.m11 > rhs.m11 ? lhs.m11 : rhs.m11
    };
}
#else
;
#endif
/// @brief Transposition of a bm2x2
SL_header bm2x2 SL_bm2x2trsp(bm2x2 m)
#if defined(SL_IMPLEMENTATION)
{
    SL_swap(m.m10, m.m01);
    return m;
}
#else
;
#endif
/// @brief Trace of a bm2x2
SL_header bool SL_bm2x2trace(bm2x2 m)
#if defined(SL_IMPLEMENTATION)
{
    return m.m00 + m.m11;
}
#else
;
#endif
/// @brief Determinant of a bm2x2
SL_header bool SL_bm2x2det_xpd(bool m00, bool m01, bool m10, bool m11)
#if defined(SL_IMPLEMENTATION)
{
    return m00 * m11 - m01 * m10;
}
#else
;
#endif
/// @brief Determinant of a bm2x2
SL_header bool SL_bm2x2det(bm2x2 m)
#if defined(SL_IMPLEMENTATION)
{
    return SL_bm2x2det_xpd(SL_XPD_M2X2(m));
}
#else
;
#endif



/// @brief Matrix of bool of size 3 x 3
typedef union {
    bool data[3 * 3];
    bool m[3][3];
    struct {
        bool m00, m01, m02;
        bool m10, m11, m12;
        bool m20, m21, m22;
    };
    struct { bv3 r0, r1, r2; };
} bm3x3;

#define SL_bm3x3_zero ((bm3x3){0})
#define SL_bm3x3_identity ((bm3x3){ 1, 0, 0, 0, 1, 0, 0, 0, 1 })


#define SL_bm3x3diag(m00_, m11_, m22_) ((bm3x3){.m00 = m00_, .m11 = m11_, .m22 = m22_})

/// @brief Addition of two bm3x3
SL_header bm3x3 SL_bm3x3add(bm3x3 lhs, bm3x3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bm3x3) {
        .m00 = lhs.m00 + rhs.m00, .m01 = lhs.m01 + rhs.m01, .m02 = lhs.m02 + rhs.m02,
        .m10 = lhs.m10 + rhs.m10, .m11 = lhs.m11 + rhs.m11, .m12 = lhs.m12 + rhs.m12,
        .m20 = lhs.m20 + rhs.m20, .m21 = lhs.m21 + rhs.m21, .m22 = lhs.m22 + rhs.m22
    };
}
#else
;
#endif
/// @brief Difference of two bm3x3
SL_header bm3x3 SL_bm3x3sub(bm3x3 lhs, bm3x3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bm3x3) {
        .m00 = lhs.m00 - rhs.m00, .m01 = lhs.m01 - rhs.m01, .m02 = lhs.m02 - rhs.m02,
        .m10 = lhs.m10 - rhs.m10, .m11 = lhs.m11 - rhs.m11, .m12 = lhs.m12 - rhs.m12,
        .m20 = lhs.m20 - rhs.m20, .m21 = lhs.m21 - rhs.m21, .m22 = lhs.m22 - rhs.m22
    };
}
#else
;
#endif
/// @brief Product of two bm3x3
SL_header bm3x3 SL_bm3x3mul(bm3x3 lhs, bm3x3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    bm3x3 res = SL_bm3x3_zero;
    for (usize k = 0; k < SL_msize(lhs).x; ++k)
    for (usize j = 0; j < SL_msize(lhs).y; ++j)
    for (usize i = 0; i < SL_msize(lhs).x; ++i)
        res.m[i][j] += lhs.m[i][k] * rhs.m[k][j];

    return res;
}
#else
;
#endif
/// @brief Component-wise multiplication of a bm3x3 with a scalar
SL_header bm3x3 SL_bm3x3muls(bm3x3 lhs, bool rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bm3x3) {
        .m00 = lhs.m00 * rhs, .m01 = lhs.m01 * rhs, .m02 = lhs.m02 * rhs,
        .m10 = lhs.m10 * rhs, .m11 = lhs.m11 * rhs, .m12 = lhs.m12 * rhs,
        .m20 = lhs.m20 * rhs, .m21 = lhs.m21 * rhs, .m22 = lhs.m22 * rhs
    };
}
#else
;
#endif
/// @brief Product of a bm3x3 and a bv3
SL_header bv3 SL_bm3x3mulv(bm3x3 lhs, bv3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_bv3_(SL_bv3dot(lhs.r0, rhs), SL_bv3dot(lhs.r1, rhs), SL_bv3dot(lhs.r2, rhs));
}
#else
;
#endif
/// @brief Apply transformation represented by bm3x3 to a bv2
SL_header bv2 SL_bm3x3apply(bm3x3 m, bv2 v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_bm3x3mulv(m, SL_bv3v(v, 1)).xy;
}
#else
;
#endif
/// @brief Component-wise division of a bm3x3 with a scalar
SL_header bm3x3 SL_bm3x3divs(bm3x3 lhs, bool rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bm3x3) {
        .m00 = lhs.m00 / rhs, .m01 = lhs.m01 / rhs, .m02 = lhs.m02 / rhs,
        .m10 = lhs.m10 / rhs, .m11 = lhs.m11 / rhs, .m12 = lhs.m12 / rhs,
        .m20 = lhs.m20 / rhs, .m21 = lhs.m21 / rhs, .m22 = lhs.m22 / rhs
    };
}
#else
;
#endif
/// @brief Addition of two bm3x3 with lhs scaled by a bool
SL_header bm3x3 SL_bm3x3addS(bm3x3 lhs, bm3x3 rhs, bool s)
#if defined(SL_IMPLEMENTATION)
{
    return (bm3x3) {
        .m00 = lhs.m00 + rhs.m00 * s, .m01 = lhs.m01 + rhs.m01 * s, .m02 = lhs.m02 + rhs.m02 * s,
        .m10 = lhs.m10 + rhs.m10 * s, .m11 = lhs.m11 + rhs.m11 * s, .m12 = lhs.m12 + rhs.m12 * s,
        .m20 = lhs.m20 + rhs.m20 * s, .m21 = lhs.m21 + rhs.m21 * s, .m22 = lhs.m22 + rhs.m22 * s
    };
}
#else
;
#endif
/// @brief Difference of two bm3x3 with lhs scaled by a bool
SL_header bm3x3 SL_bm3x3subS(bm3x3 lhs, bm3x3 rhs, bool s)
#if defined(SL_IMPLEMENTATION)
{
    return (bm3x3) {
        .m00 = lhs.m00 - rhs.m00 * s, .m01 = lhs.m01 - rhs.m01 * s, .m02 = lhs.m02 - rhs.m02 * s,
        .m10 = lhs.m10 - rhs.m10 * s, .m11 = lhs.m11 - rhs.m11 * s, .m12 = lhs.m12 - rhs.m12 * s,
        .m20 = lhs.m20 - rhs.m20 * s, .m21 = lhs.m21 - rhs.m21 * s, .m22 = lhs.m22 - rhs.m22 * s
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two bm3x3
SL_header bm3x3 SL_bm3x3min(bm3x3 lhs, bm3x3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bm3x3) {
        .m00 = lhs.m00 < rhs.m00 ? lhs.m00 : rhs.m00, .m01 = lhs.m01 < rhs.m01 ? lhs.m01 : rhs.m01, .m02 = lhs.m02 < rhs.m02 ? lhs.m02 : rhs.m02,
        .m10 = lhs.m10 < rhs.m10 ? lhs.m10 : rhs.m10, .m11 = lhs.m11 < rhs.m11 ? lhs.m11 : rhs.m11, .m12 = lhs.m12 < rhs.m12 ? lhs.m12 : rhs.m12,
        .m20 = lhs.m20 < rhs.m20 ? lhs.m20 : rhs.m20, .m21 = lhs.m21 < rhs.m21 ? lhs.m21 : rhs.m21, .m22 = lhs.m22 < rhs.m22 ? lhs.m22 : rhs.m22
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two bm3x3
SL_header bm3x3 SL_bm3x3max(bm3x3 lhs, bm3x3 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bm3x3) {
        .m00 = lhs.m00 > rhs.m00 ? lhs.m00 : rhs.m00, .m01 = lhs.m01 > rhs.m01 ? lhs.m01 : rhs.m01, .m02 = lhs.m02 > rhs.m02 ? lhs.m02 : rhs.m02,
        .m10 = lhs.m10 > rhs.m10 ? lhs.m10 : rhs.m10, .m11 = lhs.m11 > rhs.m11 ? lhs.m11 : rhs.m11, .m12 = lhs.m12 > rhs.m12 ? lhs.m12 : rhs.m12,
        .m20 = lhs.m20 > rhs.m20 ? lhs.m20 : rhs.m20, .m21 = lhs.m21 > rhs.m21 ? lhs.m21 : rhs.m21, .m22 = lhs.m22 > rhs.m22 ? lhs.m22 : rhs.m22
    };
}
#else
;
#endif
/// @brief Transposition of a bm3x3
SL_header bm3x3 SL_bm3x3trsp(bm3x3 m)
#if defined(SL_IMPLEMENTATION)
{
    SL_swap(m.m10, m.m01);
    SL_swap(m.m20, m.m02); SL_swap(m.m21, m.m12);
    return m;
}
#else
;
#endif
/// @brief Trace of a bm3x3
SL_header bool SL_bm3x3trace(bm3x3 m)
#if defined(SL_IMPLEMENTATION)
{
    return m.m00 + m.m11 + m.m22;
}
#else
;
#endif
/// @brief Determinant of a bm3x3
SL_header bool SL_bm3x3det_xpd(bool m00, bool m01, bool m02, bool m10, bool m11, bool m12, bool m20, bool m21, bool m22)
#if defined(SL_IMPLEMENTATION)
{
    return m00 * m11 * m22 + m01 * m12 * m20 + m02 * m10 * m21 - m02 * m11 * m20 - m12 * m21 * m00 - m22 * m01 * m10;
}
#else
;
#endif
/// @brief Determinant of a bm3x3
SL_header bool SL_bm3x3det(bm3x3 m)
#if defined(SL_IMPLEMENTATION)
{
    return SL_bm3x3det_xpd(SL_XPD_M3X3(m));
}
#else
;
#endif



/// @brief Matrix of bool of size 4 x 4
typedef union {
    bool data[4 * 4];
    bool m[4][4];
    struct {
        bool m00, m01, m02, m03;
        bool m10, m11, m12, m13;
        bool m20, m21, m22, m23;
        bool m30, m31, m32, m33;
    };
    struct { bv4 r0, r1, r2, r3; };
} bm4x4;

#define SL_bm4x4_zero ((bm4x4){0})
#define SL_bm4x4_identity ((bm4x4){ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 })


#define SL_bm4x4diag(m00_, m11_, m22_, m33_) ((bm4x4){.m00 = m00_, .m11 = m11_, .m22 = m22_, .m33 = m33_})

/// @brief Addition of two bm4x4
SL_header bm4x4 SL_bm4x4add(bm4x4 lhs, bm4x4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bm4x4) {
        .m00 = lhs.m00 + rhs.m00, .m01 = lhs.m01 + rhs.m01, .m02 = lhs.m02 + rhs.m02, .m03 = lhs.m03 + rhs.m03,
        .m10 = lhs.m10 + rhs.m10, .m11 = lhs.m11 + rhs.m11, .m12 = lhs.m12 + rhs.m12, .m13 = lhs.m13 + rhs.m13,
        .m20 = lhs.m20 + rhs.m20, .m21 = lhs.m21 + rhs.m21, .m22 = lhs.m22 + rhs.m22, .m23 = lhs.m23 + rhs.m23,
        .m30 = lhs.m30 + rhs.m30, .m31 = lhs.m31 + rhs.m31, .m32 = lhs.m32 + rhs.m32, .m33 = lhs.m33 + rhs.m33
    };
}
#else
;
#endif
/// @brief Difference of two bm4x4
SL_header bm4x4 SL_bm4x4sub(bm4x4 lhs, bm4x4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bm4x4) {
        .m00 = lhs.m00 - rhs.m00, .m01 = lhs.m01 - rhs.m01, .m02 = lhs.m02 - rhs.m02, .m03 = lhs.m03 - rhs.m03,
        .m10 = lhs.m10 - rhs.m10, .m11 = lhs.m11 - rhs.m11, .m12 = lhs.m12 - rhs.m12, .m13 = lhs.m13 - rhs.m13,
        .m20 = lhs.m20 - rhs.m20, .m21 = lhs.m21 - rhs.m21, .m22 = lhs.m22 - rhs.m22, .m23 = lhs.m23 - rhs.m23,
        .m30 = lhs.m30 - rhs.m30, .m31 = lhs.m31 - rhs.m31, .m32 = lhs.m32 - rhs.m32, .m33 = lhs.m33 - rhs.m33
    };
}
#else
;
#endif
/// @brief Product of two bm4x4
SL_header bm4x4 SL_bm4x4mul(bm4x4 lhs, bm4x4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    bm4x4 res = SL_bm4x4_zero;
    for (usize k = 0; k < SL_msize(lhs).x; ++k)
    for (usize j = 0; j < SL_msize(lhs).y; ++j)
    for (usize i = 0; i < SL_msize(lhs).x; ++i)
        res.m[i][j] += lhs.m[i][k] * rhs.m[k][j];

    return res;
}
#else
;
#endif
/// @brief Component-wise multiplication of a bm4x4 with a scalar
SL_header bm4x4 SL_bm4x4muls(bm4x4 lhs, bool rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bm4x4) {
        .m00 = lhs.m00 * rhs, .m01 = lhs.m01 * rhs, .m02 = lhs.m02 * rhs, .m03 = lhs.m03 * rhs,
        .m10 = lhs.m10 * rhs, .m11 = lhs.m11 * rhs, .m12 = lhs.m12 * rhs, .m13 = lhs.m13 * rhs,
        .m20 = lhs.m20 * rhs, .m21 = lhs.m21 * rhs, .m22 = lhs.m22 * rhs, .m23 = lhs.m23 * rhs,
        .m30 = lhs.m30 * rhs, .m31 = lhs.m31 * rhs, .m32 = lhs.m32 * rhs, .m33 = lhs.m33 * rhs
    };
}
#else
;
#endif
/// @brief Product of a bm4x4 and a bv4
SL_header bv4 SL_bm4x4mulv(bm4x4 lhs, bv4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_bv4_(SL_bv4dot(lhs.r0, rhs), SL_bv4dot(lhs.r1, rhs), SL_bv4dot(lhs.r2, rhs), SL_bv4dot(lhs.r3, rhs));
}
#else
;
#endif
/// @brief Apply transformation represented by bm4x4 to a bv3
SL_header bv3 SL_bm4x4apply(bm4x4 m, bv3 v)
#if defined(SL_IMPLEMENTATION)
{
    return SL_bm4x4mulv(m, SL_bv4v(v, 1)).xyz;
}
#else
;
#endif
/// @brief Component-wise division of a bm4x4 with a scalar
SL_header bm4x4 SL_bm4x4divs(bm4x4 lhs, bool rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bm4x4) {
        .m00 = lhs.m00 / rhs, .m01 = lhs.m01 / rhs, .m02 = lhs.m02 / rhs, .m03 = lhs.m03 / rhs,
        .m10 = lhs.m10 / rhs, .m11 = lhs.m11 / rhs, .m12 = lhs.m12 / rhs, .m13 = lhs.m13 / rhs,
        .m20 = lhs.m20 / rhs, .m21 = lhs.m21 / rhs, .m22 = lhs.m22 / rhs, .m23 = lhs.m23 / rhs,
        .m30 = lhs.m30 / rhs, .m31 = lhs.m31 / rhs, .m32 = lhs.m32 / rhs, .m33 = lhs.m33 / rhs
    };
}
#else
;
#endif
/// @brief Addition of two bm4x4 with lhs scaled by a bool
SL_header bm4x4 SL_bm4x4addS(bm4x4 lhs, bm4x4 rhs, bool s)
#if defined(SL_IMPLEMENTATION)
{
    return (bm4x4) {
        .m00 = lhs.m00 + rhs.m00 * s, .m01 = lhs.m01 + rhs.m01 * s, .m02 = lhs.m02 + rhs.m02 * s, .m03 = lhs.m03 + rhs.m03 * s,
        .m10 = lhs.m10 + rhs.m10 * s, .m11 = lhs.m11 + rhs.m11 * s, .m12 = lhs.m12 + rhs.m12 * s, .m13 = lhs.m13 + rhs.m13 * s,
        .m20 = lhs.m20 + rhs.m20 * s, .m21 = lhs.m21 + rhs.m21 * s, .m22 = lhs.m22 + rhs.m22 * s, .m23 = lhs.m23 + rhs.m23 * s,
        .m30 = lhs.m30 + rhs.m30 * s, .m31 = lhs.m31 + rhs.m31 * s, .m32 = lhs.m32 + rhs.m32 * s, .m33 = lhs.m33 + rhs.m33 * s
    };
}
#else
;
#endif
/// @brief Difference of two bm4x4 with lhs scaled by a bool
SL_header bm4x4 SL_bm4x4subS(bm4x4 lhs, bm4x4 rhs, bool s)
#if defined(SL_IMPLEMENTATION)
{
    return (bm4x4) {
        .m00 = lhs.m00 - rhs.m00 * s, .m01 = lhs.m01 - rhs.m01 * s, .m02 = lhs.m02 - rhs.m02 * s, .m03 = lhs.m03 - rhs.m03 * s,
        .m10 = lhs.m10 - rhs.m10 * s, .m11 = lhs.m11 - rhs.m11 * s, .m12 = lhs.m12 - rhs.m12 * s, .m13 = lhs.m13 - rhs.m13 * s,
        .m20 = lhs.m20 - rhs.m20 * s, .m21 = lhs.m21 - rhs.m21 * s, .m22 = lhs.m22 - rhs.m22 * s, .m23 = lhs.m23 - rhs.m23 * s,
        .m30 = lhs.m30 - rhs.m30 * s, .m31 = lhs.m31 - rhs.m31 * s, .m32 = lhs.m32 - rhs.m32 * s, .m33 = lhs.m33 - rhs.m33 * s
    };
}
#else
;
#endif
/// @brief Component-wise minimum of two bm4x4
SL_header bm4x4 SL_bm4x4min(bm4x4 lhs, bm4x4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bm4x4) {
        .m00 = lhs.m00 < rhs.m00 ? lhs.m00 : rhs.m00, .m01 = lhs.m01 < rhs.m01 ? lhs.m01 : rhs.m01, .m02 = lhs.m02 < rhs.m02 ? lhs.m02 : rhs.m02, .m03 = lhs.m03 < rhs.m03 ? lhs.m03 : rhs.m03,
        .m10 = lhs.m10 < rhs.m10 ? lhs.m10 : rhs.m10, .m11 = lhs.m11 < rhs.m11 ? lhs.m11 : rhs.m11, .m12 = lhs.m12 < rhs.m12 ? lhs.m12 : rhs.m12, .m13 = lhs.m13 < rhs.m13 ? lhs.m13 : rhs.m13,
        .m20 = lhs.m20 < rhs.m20 ? lhs.m20 : rhs.m20, .m21 = lhs.m21 < rhs.m21 ? lhs.m21 : rhs.m21, .m22 = lhs.m22 < rhs.m22 ? lhs.m22 : rhs.m22, .m23 = lhs.m23 < rhs.m23 ? lhs.m23 : rhs.m23,
        .m30 = lhs.m30 < rhs.m30 ? lhs.m30 : rhs.m30, .m31 = lhs.m31 < rhs.m31 ? lhs.m31 : rhs.m31, .m32 = lhs.m32 < rhs.m32 ? lhs.m32 : rhs.m32, .m33 = lhs.m33 < rhs.m33 ? lhs.m33 : rhs.m33
    };
}
#else
;
#endif
/// @brief Component-wise maximum of two bm4x4
SL_header bm4x4 SL_bm4x4max(bm4x4 lhs, bm4x4 rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (bm4x4) {
        .m00 = lhs.m00 > rhs.m00 ? lhs.m00 : rhs.m00, .m01 = lhs.m01 > rhs.m01 ? lhs.m01 : rhs.m01, .m02 = lhs.m02 > rhs.m02 ? lhs.m02 : rhs.m02, .m03 = lhs.m03 > rhs.m03 ? lhs.m03 : rhs.m03,
        .m10 = lhs.m10 > rhs.m10 ? lhs.m10 : rhs.m10, .m11 = lhs.m11 > rhs.m11 ? lhs.m11 : rhs.m11, .m12 = lhs.m12 > rhs.m12 ? lhs.m12 : rhs.m12, .m13 = lhs.m13 > rhs.m13 ? lhs.m13 : rhs.m13,
        .m20 = lhs.m20 > rhs.m20 ? lhs.m20 : rhs.m20, .m21 = lhs.m21 > rhs.m21 ? lhs.m21 : rhs.m21, .m22 = lhs.m22 > rhs.m22 ? lhs.m22 : rhs.m22, .m23 = lhs.m23 > rhs.m23 ? lhs.m23 : rhs.m23,
        .m30 = lhs.m30 > rhs.m30 ? lhs.m30 : rhs.m30, .m31 = lhs.m31 > rhs.m31 ? lhs.m31 : rhs.m31, .m32 = lhs.m32 > rhs.m32 ? lhs.m32 : rhs.m32, .m33 = lhs.m33 > rhs.m33 ? lhs.m33 : rhs.m33
    };
}
#else
;
#endif
/// @brief Transposition of a bm4x4
SL_header bm4x4 SL_bm4x4trsp(bm4x4 m)
#if defined(SL_IMPLEMENTATION)
{
    SL_swap(m.m10, m.m01);
    SL_swap(m.m20, m.m02); SL_swap(m.m12, m.m21);
    SL_swap(m.m30, m.m03); SL_swap(m.m31, m.m13);SL_swap(m.m32, m.m23);
    return m;
}
#else
;
#endif
/// @brief Trace of a bm4x4
SL_header bool SL_bm4x4trace(bm4x4 m)
#if defined(SL_IMPLEMENTATION)
{
    return m.m00 + m.m11 + m.m22 + m.m33;
}
#else
;
#endif
/// @brief Determinant of a bm4x4
SL_header bool SL_bm4x4det_xpd(bool m00, bool m01, bool m02, bool m03, bool m10, bool m11, bool m12, bool m13, bool m20, bool m21, bool m22, bool m23, bool m30, bool m31, bool m32, bool m33)
#if defined(SL_IMPLEMENTATION)
{
    return m00 * SL_bm3x3det_xpd(m11, m12, m13, m21, m22, m23, m31, m32, m33)
         + m01 * SL_bm3x3det_xpd(m10, m12, m13, m20, m22, m23, m30, m32, m33)
         + m02 * SL_bm3x3det_xpd(m10, m11, m13, m20, m21, m23, m30, m31, m33)
         + m03 * SL_bm3x3det_xpd(m10, m11, m12, m20, m21, m22, m30, m31, m32);
}
#else
;
#endif
/// @brief Determinant of a bm4x4
SL_header bool SL_bm4x4det(bm4x4 m)
#if defined(SL_IMPLEMENTATION)
{
    return SL_bm4x4det_xpd(SL_XPD_M4X4(m));
}
#else
;
#endif



#pragma endregion BOOL
#ifdef SL_STRIP_PREFIX
#   define  msize SL_msize
#   define  mget SL_mget
#   define  XPD_M2X2 SL_XPD_M2X2
#   define  XPD_M3X3 SL_XPD_M3X3
#   define  XPD_M4X4 SL_XPD_M4X4
#   define  FMT_M2X2 SL_FMT_M2X2
#   define  FMT_M3X3 SL_FMT_M3X3
#   define  FMT_M4X4 SL_FMT_M4X4
#   define  asi32m SL_asi32m
#   define  i32m2x2_zero SL_i32m2x2_zero
#   define  i32m2x2_identity SL_i32m2x2_identity
#   define  i32m2x2diag SL_i32m2x2diag
#   define  i32m2x2add SL_i32m2x2add
#   define  i32m2x2sub SL_i32m2x2sub
#   define  i32m2x2mul SL_i32m2x2mul
#   define  i32m2x2muls SL_i32m2x2muls
#   define  i32m2x2mulv SL_i32m2x2mulv
#   define  i32m2x2divs SL_i32m2x2divs
#   define  i32m2x2addS SL_i32m2x2addS
#   define  i32m2x2subS SL_i32m2x2subS
#   define  i32m2x2neg SL_i32m2x2neg
#   define  i32m2x2abs SL_i32m2x2abs
#   define  i32m2x2min SL_i32m2x2min
#   define  i32m2x2max SL_i32m2x2max
#   define  i32m2x2trsp SL_i32m2x2trsp
#   define  i32m2x2trace SL_i32m2x2trace
#   define  i32m2x2det_xpd SL_i32m2x2det_xpd
#   define  i32m2x2det SL_i32m2x2det
#   define  i32m3x3_zero SL_i32m3x3_zero
#   define  i32m3x3_identity SL_i32m3x3_identity
#   define  i32m3x3diag SL_i32m3x3diag
#   define  i32m3x3add SL_i32m3x3add
#   define  i32m3x3sub SL_i32m3x3sub
#   define  i32m3x3mul SL_i32m3x3mul
#   define  i32m3x3muls SL_i32m3x3muls
#   define  i32m3x3mulv SL_i32m3x3mulv
#   define  i32m3x3apply SL_i32m3x3apply
#   define  i32m3x3divs SL_i32m3x3divs
#   define  i32m3x3addS SL_i32m3x3addS
#   define  i32m3x3subS SL_i32m3x3subS
#   define  i32m3x3neg SL_i32m3x3neg
#   define  i32m3x3abs SL_i32m3x3abs
#   define  i32m3x3min SL_i32m3x3min
#   define  i32m3x3max SL_i32m3x3max
#   define  i32m3x3trsp SL_i32m3x3trsp
#   define  i32m3x3trace SL_i32m3x3trace
#   define  i32m3x3det_xpd SL_i32m3x3det_xpd
#   define  i32m3x3det SL_i32m3x3det
#   define  i32m4x4_zero SL_i32m4x4_zero
#   define  i32m4x4_identity SL_i32m4x4_identity
#   define  i32m4x4diag SL_i32m4x4diag
#   define  i32m4x4add SL_i32m4x4add
#   define  i32m4x4sub SL_i32m4x4sub
#   define  i32m4x4mul SL_i32m4x4mul
#   define  i32m4x4muls SL_i32m4x4muls
#   define  i32m4x4mulv SL_i32m4x4mulv
#   define  i32m4x4apply SL_i32m4x4apply
#   define  i32m4x4divs SL_i32m4x4divs
#   define  i32m4x4addS SL_i32m4x4addS
#   define  i32m4x4subS SL_i32m4x4subS
#   define  i32m4x4neg SL_i32m4x4neg
#   define  i32m4x4abs SL_i32m4x4abs
#   define  i32m4x4min SL_i32m4x4min
#   define  i32m4x4max SL_i32m4x4max
#   define  i32m4x4trsp SL_i32m4x4trsp
#   define  i32m4x4trace SL_i32m4x4trace
#   define  i32m4x4det_xpd SL_i32m4x4det_xpd
#   define  i32m4x4det SL_i32m4x4det
#   define  asi64m SL_asi64m
#   define  i64m2x2_zero SL_i64m2x2_zero
#   define  i64m2x2_identity SL_i64m2x2_identity
#   define  i64m2x2diag SL_i64m2x2diag
#   define  i64m2x2add SL_i64m2x2add
#   define  i64m2x2sub SL_i64m2x2sub
#   define  i64m2x2mul SL_i64m2x2mul
#   define  i64m2x2muls SL_i64m2x2muls
#   define  i64m2x2mulv SL_i64m2x2mulv
#   define  i64m2x2divs SL_i64m2x2divs
#   define  i64m2x2addS SL_i64m2x2addS
#   define  i64m2x2subS SL_i64m2x2subS
#   define  i64m2x2neg SL_i64m2x2neg
#   define  i64m2x2abs SL_i64m2x2abs
#   define  i64m2x2min SL_i64m2x2min
#   define  i64m2x2max SL_i64m2x2max
#   define  i64m2x2trsp SL_i64m2x2trsp
#   define  i64m2x2trace SL_i64m2x2trace
#   define  i64m2x2det_xpd SL_i64m2x2det_xpd
#   define  i64m2x2det SL_i64m2x2det
#   define  i64m3x3_zero SL_i64m3x3_zero
#   define  i64m3x3_identity SL_i64m3x3_identity
#   define  i64m3x3diag SL_i64m3x3diag
#   define  i64m3x3add SL_i64m3x3add
#   define  i64m3x3sub SL_i64m3x3sub
#   define  i64m3x3mul SL_i64m3x3mul
#   define  i64m3x3muls SL_i64m3x3muls
#   define  i64m3x3mulv SL_i64m3x3mulv
#   define  i64m3x3apply SL_i64m3x3apply
#   define  i64m3x3divs SL_i64m3x3divs
#   define  i64m3x3addS SL_i64m3x3addS
#   define  i64m3x3subS SL_i64m3x3subS
#   define  i64m3x3neg SL_i64m3x3neg
#   define  i64m3x3abs SL_i64m3x3abs
#   define  i64m3x3min SL_i64m3x3min
#   define  i64m3x3max SL_i64m3x3max
#   define  i64m3x3trsp SL_i64m3x3trsp
#   define  i64m3x3trace SL_i64m3x3trace
#   define  i64m3x3det_xpd SL_i64m3x3det_xpd
#   define  i64m3x3det SL_i64m3x3det
#   define  i64m4x4_zero SL_i64m4x4_zero
#   define  i64m4x4_identity SL_i64m4x4_identity
#   define  i64m4x4diag SL_i64m4x4diag
#   define  i64m4x4add SL_i64m4x4add
#   define  i64m4x4sub SL_i64m4x4sub
#   define  i64m4x4mul SL_i64m4x4mul
#   define  i64m4x4muls SL_i64m4x4muls
#   define  i64m4x4mulv SL_i64m4x4mulv
#   define  i64m4x4apply SL_i64m4x4apply
#   define  i64m4x4divs SL_i64m4x4divs
#   define  i64m4x4addS SL_i64m4x4addS
#   define  i64m4x4subS SL_i64m4x4subS
#   define  i64m4x4neg SL_i64m4x4neg
#   define  i64m4x4abs SL_i64m4x4abs
#   define  i64m4x4min SL_i64m4x4min
#   define  i64m4x4max SL_i64m4x4max
#   define  i64m4x4trsp SL_i64m4x4trsp
#   define  i64m4x4trace SL_i64m4x4trace
#   define  i64m4x4det_xpd SL_i64m4x4det_xpd
#   define  i64m4x4det SL_i64m4x4det
#   define  asu32m SL_asu32m
#   define  u32m2x2_zero SL_u32m2x2_zero
#   define  u32m2x2_identity SL_u32m2x2_identity
#   define  u32m2x2diag SL_u32m2x2diag
#   define  u32m2x2add SL_u32m2x2add
#   define  u32m2x2sub SL_u32m2x2sub
#   define  u32m2x2mul SL_u32m2x2mul
#   define  u32m2x2muls SL_u32m2x2muls
#   define  u32m2x2mulv SL_u32m2x2mulv
#   define  u32m2x2divs SL_u32m2x2divs
#   define  u32m2x2addS SL_u32m2x2addS
#   define  u32m2x2subS SL_u32m2x2subS
#   define  u32m2x2min SL_u32m2x2min
#   define  u32m2x2max SL_u32m2x2max
#   define  u32m2x2trsp SL_u32m2x2trsp
#   define  u32m2x2trace SL_u32m2x2trace
#   define  u32m2x2det_xpd SL_u32m2x2det_xpd
#   define  u32m2x2det SL_u32m2x2det
#   define  u32m3x3_zero SL_u32m3x3_zero
#   define  u32m3x3_identity SL_u32m3x3_identity
#   define  u32m3x3diag SL_u32m3x3diag
#   define  u32m3x3add SL_u32m3x3add
#   define  u32m3x3sub SL_u32m3x3sub
#   define  u32m3x3mul SL_u32m3x3mul
#   define  u32m3x3muls SL_u32m3x3muls
#   define  u32m3x3mulv SL_u32m3x3mulv
#   define  u32m3x3apply SL_u32m3x3apply
#   define  u32m3x3divs SL_u32m3x3divs
#   define  u32m3x3addS SL_u32m3x3addS
#   define  u32m3x3subS SL_u32m3x3subS
#   define  u32m3x3min SL_u32m3x3min
#   define  u32m3x3max SL_u32m3x3max
#   define  u32m3x3trsp SL_u32m3x3trsp
#   define  u32m3x3trace SL_u32m3x3trace
#   define  u32m3x3det_xpd SL_u32m3x3det_xpd
#   define  u32m3x3det SL_u32m3x3det
#   define  u32m4x4_zero SL_u32m4x4_zero
#   define  u32m4x4_identity SL_u32m4x4_identity
#   define  u32m4x4diag SL_u32m4x4diag
#   define  u32m4x4add SL_u32m4x4add
#   define  u32m4x4sub SL_u32m4x4sub
#   define  u32m4x4mul SL_u32m4x4mul
#   define  u32m4x4muls SL_u32m4x4muls
#   define  u32m4x4mulv SL_u32m4x4mulv
#   define  u32m4x4apply SL_u32m4x4apply
#   define  u32m4x4divs SL_u32m4x4divs
#   define  u32m4x4addS SL_u32m4x4addS
#   define  u32m4x4subS SL_u32m4x4subS
#   define  u32m4x4min SL_u32m4x4min
#   define  u32m4x4max SL_u32m4x4max
#   define  u32m4x4trsp SL_u32m4x4trsp
#   define  u32m4x4trace SL_u32m4x4trace
#   define  u32m4x4det_xpd SL_u32m4x4det_xpd
#   define  u32m4x4det SL_u32m4x4det
#   define  asu64m SL_asu64m
#   define  u64m2x2_zero SL_u64m2x2_zero
#   define  u64m2x2_identity SL_u64m2x2_identity
#   define  u64m2x2diag SL_u64m2x2diag
#   define  u64m2x2add SL_u64m2x2add
#   define  u64m2x2sub SL_u64m2x2sub
#   define  u64m2x2mul SL_u64m2x2mul
#   define  u64m2x2muls SL_u64m2x2muls
#   define  u64m2x2mulv SL_u64m2x2mulv
#   define  u64m2x2divs SL_u64m2x2divs
#   define  u64m2x2addS SL_u64m2x2addS
#   define  u64m2x2subS SL_u64m2x2subS
#   define  u64m2x2min SL_u64m2x2min
#   define  u64m2x2max SL_u64m2x2max
#   define  u64m2x2trsp SL_u64m2x2trsp
#   define  u64m2x2trace SL_u64m2x2trace
#   define  u64m2x2det_xpd SL_u64m2x2det_xpd
#   define  u64m2x2det SL_u64m2x2det
#   define  u64m3x3_zero SL_u64m3x3_zero
#   define  u64m3x3_identity SL_u64m3x3_identity
#   define  u64m3x3diag SL_u64m3x3diag
#   define  u64m3x3add SL_u64m3x3add
#   define  u64m3x3sub SL_u64m3x3sub
#   define  u64m3x3mul SL_u64m3x3mul
#   define  u64m3x3muls SL_u64m3x3muls
#   define  u64m3x3mulv SL_u64m3x3mulv
#   define  u64m3x3apply SL_u64m3x3apply
#   define  u64m3x3divs SL_u64m3x3divs
#   define  u64m3x3addS SL_u64m3x3addS
#   define  u64m3x3subS SL_u64m3x3subS
#   define  u64m3x3min SL_u64m3x3min
#   define  u64m3x3max SL_u64m3x3max
#   define  u64m3x3trsp SL_u64m3x3trsp
#   define  u64m3x3trace SL_u64m3x3trace
#   define  u64m3x3det_xpd SL_u64m3x3det_xpd
#   define  u64m3x3det SL_u64m3x3det
#   define  u64m4x4_zero SL_u64m4x4_zero
#   define  u64m4x4_identity SL_u64m4x4_identity
#   define  u64m4x4diag SL_u64m4x4diag
#   define  u64m4x4add SL_u64m4x4add
#   define  u64m4x4sub SL_u64m4x4sub
#   define  u64m4x4mul SL_u64m4x4mul
#   define  u64m4x4muls SL_u64m4x4muls
#   define  u64m4x4mulv SL_u64m4x4mulv
#   define  u64m4x4apply SL_u64m4x4apply
#   define  u64m4x4divs SL_u64m4x4divs
#   define  u64m4x4addS SL_u64m4x4addS
#   define  u64m4x4subS SL_u64m4x4subS
#   define  u64m4x4min SL_u64m4x4min
#   define  u64m4x4max SL_u64m4x4max
#   define  u64m4x4trsp SL_u64m4x4trsp
#   define  u64m4x4trace SL_u64m4x4trace
#   define  u64m4x4det_xpd SL_u64m4x4det_xpd
#   define  u64m4x4det SL_u64m4x4det
#   define  asfm SL_asfm
#   define  fm2x2_zero SL_fm2x2_zero
#   define  fm2x2_identity SL_fm2x2_identity
#   define  fm2x2diag SL_fm2x2diag
#   define  fm2x2add SL_fm2x2add
#   define  fm2x2sub SL_fm2x2sub
#   define  fm2x2mul SL_fm2x2mul
#   define  fm2x2muls SL_fm2x2muls
#   define  fm2x2mulv SL_fm2x2mulv
#   define  fm2x2divs SL_fm2x2divs
#   define  fm2x2addS SL_fm2x2addS
#   define  fm2x2subS SL_fm2x2subS
#   define  fm2x2neg SL_fm2x2neg
#   define  fm2x2abs SL_fm2x2abs
#   define  fm2x2min SL_fm2x2min
#   define  fm2x2max SL_fm2x2max
#   define  fm2x2trsp SL_fm2x2trsp
#   define  fm2x2trace SL_fm2x2trace
#   define  fm2x2det_xpd SL_fm2x2det_xpd
#   define  fm2x2det SL_fm2x2det
#   define  fm2x2inv SL_fm2x2inv
#   define  fm2x2from_angle SL_fm2x2from_angle
#   define  fm3x3_zero SL_fm3x3_zero
#   define  fm3x3_identity SL_fm3x3_identity
#   define  fm3x3diag SL_fm3x3diag
#   define  fm3x3add SL_fm3x3add
#   define  fm3x3sub SL_fm3x3sub
#   define  fm3x3mul SL_fm3x3mul
#   define  fm3x3muls SL_fm3x3muls
#   define  fm3x3mulv SL_fm3x3mulv
#   define  fm3x3apply SL_fm3x3apply
#   define  fm3x3divs SL_fm3x3divs
#   define  fm3x3addS SL_fm3x3addS
#   define  fm3x3subS SL_fm3x3subS
#   define  fm3x3neg SL_fm3x3neg
#   define  fm3x3abs SL_fm3x3abs
#   define  fm3x3min SL_fm3x3min
#   define  fm3x3max SL_fm3x3max
#   define  fm3x3trsp SL_fm3x3trsp
#   define  fm3x3trace SL_fm3x3trace
#   define  fm3x3det_xpd SL_fm3x3det_xpd
#   define  fm3x3det SL_fm3x3det
#   define  fm3x3inv SL_fm3x3inv
#   define  fm3x3from_quat SL_fm3x3from_quat
#   define  fm3x3from_transform SL_fm3x3from_transform
#   define  fm4x4_zero SL_fm4x4_zero
#   define  fm4x4_identity SL_fm4x4_identity
#   define  fm4x4diag SL_fm4x4diag
#   define  fm4x4add SL_fm4x4add
#   define  fm4x4sub SL_fm4x4sub
#   define  fm4x4mul SL_fm4x4mul
#   define  fm4x4muls SL_fm4x4muls
#   define  fm4x4mulv SL_fm4x4mulv
#   define  fm4x4apply SL_fm4x4apply
#   define  fm4x4divs SL_fm4x4divs
#   define  fm4x4addS SL_fm4x4addS
#   define  fm4x4subS SL_fm4x4subS
#   define  fm4x4neg SL_fm4x4neg
#   define  fm4x4abs SL_fm4x4abs
#   define  fm4x4min SL_fm4x4min
#   define  fm4x4max SL_fm4x4max
#   define  fm4x4trsp SL_fm4x4trsp
#   define  fm4x4trace SL_fm4x4trace
#   define  fm4x4det_xpd SL_fm4x4det_xpd
#   define  fm4x4det SL_fm4x4det
#   define  fm4x4inv SL_fm4x4inv
#   define  fm4x4from_transform SL_fm4x4from_transform
#   define  fm4x4from_projection SL_fm4x4from_projection
#   define  asdm SL_asdm
#   define  dm2x2_zero SL_dm2x2_zero
#   define  dm2x2_identity SL_dm2x2_identity
#   define  dm2x2diag SL_dm2x2diag
#   define  dm2x2add SL_dm2x2add
#   define  dm2x2sub SL_dm2x2sub
#   define  dm2x2mul SL_dm2x2mul
#   define  dm2x2muls SL_dm2x2muls
#   define  dm2x2mulv SL_dm2x2mulv
#   define  dm2x2divs SL_dm2x2divs
#   define  dm2x2addS SL_dm2x2addS
#   define  dm2x2subS SL_dm2x2subS
#   define  dm2x2neg SL_dm2x2neg
#   define  dm2x2abs SL_dm2x2abs
#   define  dm2x2min SL_dm2x2min
#   define  dm2x2max SL_dm2x2max
#   define  dm2x2trsp SL_dm2x2trsp
#   define  dm2x2trace SL_dm2x2trace
#   define  dm2x2det_xpd SL_dm2x2det_xpd
#   define  dm2x2det SL_dm2x2det
#   define  dm2x2inv SL_dm2x2inv
#   define  dm2x2from_angle SL_dm2x2from_angle
#   define  dm3x3_zero SL_dm3x3_zero
#   define  dm3x3_identity SL_dm3x3_identity
#   define  dm3x3diag SL_dm3x3diag
#   define  dm3x3add SL_dm3x3add
#   define  dm3x3sub SL_dm3x3sub
#   define  dm3x3mul SL_dm3x3mul
#   define  dm3x3muls SL_dm3x3muls
#   define  dm3x3mulv SL_dm3x3mulv
#   define  dm3x3apply SL_dm3x3apply
#   define  dm3x3divs SL_dm3x3divs
#   define  dm3x3addS SL_dm3x3addS
#   define  dm3x3subS SL_dm3x3subS
#   define  dm3x3neg SL_dm3x3neg
#   define  dm3x3abs SL_dm3x3abs
#   define  dm3x3min SL_dm3x3min
#   define  dm3x3max SL_dm3x3max
#   define  dm3x3trsp SL_dm3x3trsp
#   define  dm3x3trace SL_dm3x3trace
#   define  dm3x3det_xpd SL_dm3x3det_xpd
#   define  dm3x3det SL_dm3x3det
#   define  dm3x3inv SL_dm3x3inv
#   define  dm3x3from_quat SL_dm3x3from_quat
#   define  dm3x3from_transform SL_dm3x3from_transform
#   define  dm4x4_zero SL_dm4x4_zero
#   define  dm4x4_identity SL_dm4x4_identity
#   define  dm4x4diag SL_dm4x4diag
#   define  dm4x4add SL_dm4x4add
#   define  dm4x4sub SL_dm4x4sub
#   define  dm4x4mul SL_dm4x4mul
#   define  dm4x4muls SL_dm4x4muls
#   define  dm4x4mulv SL_dm4x4mulv
#   define  dm4x4apply SL_dm4x4apply
#   define  dm4x4divs SL_dm4x4divs
#   define  dm4x4addS SL_dm4x4addS
#   define  dm4x4subS SL_dm4x4subS
#   define  dm4x4neg SL_dm4x4neg
#   define  dm4x4abs SL_dm4x4abs
#   define  dm4x4min SL_dm4x4min
#   define  dm4x4max SL_dm4x4max
#   define  dm4x4trsp SL_dm4x4trsp
#   define  dm4x4trace SL_dm4x4trace
#   define  dm4x4det_xpd SL_dm4x4det_xpd
#   define  dm4x4det SL_dm4x4det
#   define  dm4x4inv SL_dm4x4inv
#   define  dm4x4from_transform SL_dm4x4from_transform
#   define  dm4x4from_projection SL_dm4x4from_projection
#   define  asbm SL_asbm
#   define  bm2x2_zero SL_bm2x2_zero
#   define  bm2x2_identity SL_bm2x2_identity
#   define  bm2x2diag SL_bm2x2diag
#   define  bm2x2add SL_bm2x2add
#   define  bm2x2sub SL_bm2x2sub
#   define  bm2x2mul SL_bm2x2mul
#   define  bm2x2muls SL_bm2x2muls
#   define  bm2x2mulv SL_bm2x2mulv
#   define  bm2x2divs SL_bm2x2divs
#   define  bm2x2addS SL_bm2x2addS
#   define  bm2x2subS SL_bm2x2subS
#   define  bm2x2min SL_bm2x2min
#   define  bm2x2max SL_bm2x2max
#   define  bm2x2trsp SL_bm2x2trsp
#   define  bm2x2trace SL_bm2x2trace
#   define  bm2x2det_xpd SL_bm2x2det_xpd
#   define  bm2x2det SL_bm2x2det
#   define  bm3x3_zero SL_bm3x3_zero
#   define  bm3x3_identity SL_bm3x3_identity
#   define  bm3x3diag SL_bm3x3diag
#   define  bm3x3add SL_bm3x3add
#   define  bm3x3sub SL_bm3x3sub
#   define  bm3x3mul SL_bm3x3mul
#   define  bm3x3muls SL_bm3x3muls
#   define  bm3x3mulv SL_bm3x3mulv
#   define  bm3x3apply SL_bm3x3apply
#   define  bm3x3divs SL_bm3x3divs
#   define  bm3x3addS SL_bm3x3addS
#   define  bm3x3subS SL_bm3x3subS
#   define  bm3x3min SL_bm3x3min
#   define  bm3x3max SL_bm3x3max
#   define  bm3x3trsp SL_bm3x3trsp
#   define  bm3x3trace SL_bm3x3trace
#   define  bm3x3det_xpd SL_bm3x3det_xpd
#   define  bm3x3det SL_bm3x3det
#   define  bm4x4_zero SL_bm4x4_zero
#   define  bm4x4_identity SL_bm4x4_identity
#   define  bm4x4diag SL_bm4x4diag
#   define  bm4x4add SL_bm4x4add
#   define  bm4x4sub SL_bm4x4sub
#   define  bm4x4mul SL_bm4x4mul
#   define  bm4x4muls SL_bm4x4muls
#   define  bm4x4mulv SL_bm4x4mulv
#   define  bm4x4apply SL_bm4x4apply
#   define  bm4x4divs SL_bm4x4divs
#   define  bm4x4addS SL_bm4x4addS
#   define  bm4x4subS SL_bm4x4subS
#   define  bm4x4min SL_bm4x4min
#   define  bm4x4max SL_bm4x4max
#   define  bm4x4trsp SL_bm4x4trsp
#   define  bm4x4trace SL_bm4x4trace
#   define  bm4x4det_xpd SL_bm4x4det_xpd
#   define  bm4x4det SL_bm4x4det
#endif

#endif // __SL_MATRIX_H