#ifndef _SL_QUATERNION_H_
#define _SL_QUATERNION_H_

#include "../base.h"

#include "math.h"
#include "vector.h"

#define SL_XPD_Q(Q) (Q).w, (Q).x, (Q).y, (Q).z
#define SL_FMT_Q(fmt) "quat("fmt" + "fmt"i + "fmt"j + "fmt"k)"

/// @brief Quaternion of float
typedef union {
    float data[4];
    struct { float a, b, c, d; };
    struct { float w, x, y, z; };
    struct { float r; union { fv3 iv; struct { float i, j, k; }; }; };
    fv4 fv4;
} fq;

#define SL_fq_zero     ((fq){.a = 0, .b = 0, .c = 0, .d = 0})
#define SL_fq_identity ((fq){.a = 1, .b = 0, .c = 0, .d = 0})

/// @brief Quaternion of double
typedef union {
    double data[4];
    struct { double a, b, c, d; };
    struct { double w, x, y, z; };
    struct { double r; union { dv3 iv; struct { double i, j, k; }; }; };
    dv4 dv4;
} dq;

#define SL_dq_zero     ((dq){.a = 0, .b = 0, .c = 0, .d = 0})
#define SL_dq_identity ((dq){.a = 1, .b = 0, .c = 0, .d = 0})



#define SL_fq_(R, I, J, K) ((fq){.r = R, .i = I, .j = J, .k = K})
#define SL_dq_(R, I, J, K) ((dq){.r = R, .i = I, .j = J, .k = K})
#define SL_fqv(R, IV)      ((fq){.r = R, .iv = IV})
#define SL_dqv(R, IV)      ((dq){.r = R, .iv = IV})
#define SL_fqq(Q)          ((fq){SL_XPD_Q(Q)})
#define SL_dqq(Q)          ((dq){SL_XPD_Q(Q)})



#pragma region ARITHMETIC

/// @brief Equality of two fq
SL_header bool SL_fqequ(fq lhs, fq rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.w == rhs.w && lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}
#else
;
#endif
/// @brief Equality of two dq
SL_header bool SL_dqequ(dq lhs, dq rhs)
#if defined(SL_IMPLEMENTATION)
{
    return lhs.w == rhs.w && lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}
#else
;
#endif
/// @brief Addition of two fq
SL_header fq SL_fqadd(fq lhs, fq rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (fq) {
        .w = lhs.w + rhs.w,
        .x = lhs.x + rhs.x,
        .y = lhs.y + rhs.y,
        .z = lhs.z + rhs.z
    };
}
#else
;
#endif
/// @brief Addition of two dq
SL_header dq SL_dqadd(dq lhs, dq rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (dq) {
        .w = lhs.w + rhs.w,
        .x = lhs.x + rhs.x,
        .y = lhs.y + rhs.y,
        .z = lhs.z + rhs.z
    };
}
#else
;
#endif
/// @brief Difference of two fq
SL_header fq SL_fqsub(fq lhs, fq rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (fq) {
        .w = lhs.w - rhs.w,
        .x = lhs.x - rhs.x,
        .y = lhs.y - rhs.y,
        .z = lhs.z - rhs.z
    };
}
#else
;
#endif
/// @brief Difference of two dq
SL_header dq SL_dqsub(dq lhs, dq rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (dq) {
        .w = lhs.w - rhs.w,
        .x = lhs.x - rhs.x,
        .y = lhs.y - rhs.y,
        .z = lhs.z - rhs.z
    };
}
#else
;
#endif
/// @brief Multiplication of two fq
SL_header fq SL_fqmul(fq lhs, fq rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (fq) {
        .a = lhs.a*rhs.w - lhs.b*rhs.x - lhs.c*rhs.y - lhs.d*rhs.z,
        .b = lhs.a*rhs.x + lhs.b*rhs.w + lhs.c*rhs.z - lhs.d*rhs.y,
        .c = lhs.a*rhs.y - lhs.b*rhs.z + lhs.c*rhs.w + lhs.d*rhs.x,
        .d = lhs.a*rhs.z + lhs.b*rhs.y - lhs.c*rhs.x + lhs.d*rhs.w
    };
}
#else
;
#endif
/// @brief Multiplication of two dq
SL_header dq SL_dqmul(dq lhs, dq rhs)
#if defined(SL_IMPLEMENTATION)
{
    return (dq) {
        .a = lhs.a*rhs.w - lhs.b*rhs.x - lhs.c*rhs.y - lhs.d*rhs.z,
        .b = lhs.a*rhs.x + lhs.b*rhs.w + lhs.c*rhs.z - lhs.d*rhs.y,
        .c = lhs.a*rhs.y - lhs.b*rhs.z + lhs.c*rhs.w + lhs.d*rhs.x,
        .d = lhs.a*rhs.z + lhs.b*rhs.y - lhs.c*rhs.x + lhs.d*rhs.w
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of a fq with a scalar
SL_header fq SL_fqmuls(fq q, float s)
#if defined(SL_IMPLEMENTATION)
{
    return (fq) {
        .w = q.w * s,
        .x = q.x * s,
        .y = q.y * s,
        .z = q.z * s
    };
}
#else
;
#endif
/// @brief Component-wise multiplication of a dq with a scalar
SL_header dq SL_dqmuls(dq q, double s)
#if defined(SL_IMPLEMENTATION)
{
    return (dq) {
        .w = q.w * s,
        .x = q.x * s,
        .y = q.y * s,
        .z = q.z * s
    };
}
#else
;
#endif
/// @brief Negation of a fq
SL_header fq SL_fqneg(fq q)
#if defined(SL_IMPLEMENTATION)
{
    return (fq) {
        .w = -q.w,
        .x = -q.x,
        .y = -q.y,
        .z = -q.z
    };
}
#else
;
#endif
/// @brief Negation of a dq
SL_header dq SL_dqneg(dq q)
#if defined(SL_IMPLEMENTATION)
{
    return (dq) {
        .w = -q.w,
        .x = -q.x,
        .y = -q.y,
        .z = -q.z
    };
}
#else
;
#endif
/// @brief Canonic squared length of a fq
SL_header double SL_fqlen_sqr(fq q)
#if defined(SL_IMPLEMENTATION)
{
    return q.a * q.a + q.b * q.b + q.c * q.c + q.d * q.d;
}
#else
;
#endif
/// @brief Canonic squared length of a dq
SL_header double SL_dqlen_sqr(dq q)
#if defined(SL_IMPLEMENTATION)
{
    return q.a * q.a + q.b * q.b + q.c * q.c + q.d * q.d;
}
#else
;
#endif
/// @brief Canonic length of a fq
SL_header double SL_fqlen(fq q)
#if defined(SL_IMPLEMENTATION)
{
    return sqrtf(SL_fqlen_sqr(q));
}
#else
;
#endif
/// @brief Canonic length of a dq
SL_header double SL_dqlen(dq q)
#if defined(SL_IMPLEMENTATION)
{
    return sqrt(SL_dqlen_sqr(q));
}
#else
;
#endif
/// @brief Normalization of a fq
SL_header fq SL_fqnorm(fq q)
#if defined(SL_IMPLEMENTATION)
{
    double inv_len = 1.0 / SL_fqlen(q);
    return (fq) {
        .w = q.w * inv_len,
        .x = q.x * inv_len,
        .y = q.y * inv_len,
        .z = q.z * inv_len
    };
}
#else
;
#endif
/// @brief Normalization of a dq
SL_header dq SL_dqnorm(dq q)
#if defined(SL_IMPLEMENTATION)
{
    double inv_len = 1.0 / SL_dqlen(q);
    return (dq) {
        .w = q.w * inv_len,
        .x = q.x * inv_len,
        .y = q.y * inv_len,
        .z = q.z * inv_len
    };
}
#else
;
#endif
/// @brief Transposition of a fq
SL_header fq SL_fqtrsp(fq q)
#if defined(SL_IMPLEMENTATION)
{
    return (fq) {
        .a = q.a,
        .b = -q.b,
        .c = -q.c,
        .d = -q.d
    };
}
#else
;
#endif
/// @brief Transposition of a dq
SL_header dq SL_dqtrsp(dq q)
#if defined(SL_IMPLEMENTATION)
{
    return (dq) {
        .a = q.a,
        .b = -q.b,
        .c = -q.c,
        .d = -q.d
    };
}
#else
;
#endif
/// @brief Inversion of a fq
SL_header fq SL_fqinv(fq q)
#if defined(SL_IMPLEMENTATION)
{
    double inv_len = 1.0 / SL_fqlen_sqr(q);
    return (fq) {
        .a = q.a * inv_len,
        .b = -q.b * inv_len,
        .c = -q.c * inv_len,
        .d = -q.d * inv_len
    };
}
#else
;
#endif
/// @brief Inversion of a dq
SL_header dq SL_dqinv(dq q)
#if defined(SL_IMPLEMENTATION)
{
    double inv_len = 1.0 / SL_dqlen_sqr(q);
    return (dq) {
        .a = q.a * inv_len,
        .b = -q.b * inv_len,
        .c = -q.c * inv_len,
        .d = -q.d * inv_len
    };
}
#else
;
#endif
/// @brief Division of two fq
SL_header fq SL_fqdiv(fq lhs, fq rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_fqmul(lhs, SL_fqinv(rhs));
}
#else
;
#endif
/// @brief Division of two dq
SL_header dq SL_dqdiv(dq lhs, dq rhs)
#if defined(SL_IMPLEMENTATION)
{
    return SL_dqmul(lhs, SL_dqinv(rhs));
}
#else
;
#endif
/// @brief Exponential of a fq
SL_header fq SL_fqexp(fq q)
#if defined(SL_IMPLEMENTATION)
{
    double ex = exp(q.r);
    double angle = SL_fv3len(q.iv);
    double sin_angle = angle < 1e-8 ? 0.0 : ex * sin(angle) / angle;
    return (fq) {
        .r = ex * cos(angle),
        .i = q.i * sin_angle,
        .j = q.j * sin_angle,
        .k = q.k * sin_angle
    };
}
#else
;
#endif
/// @brief Exponential of a dq
SL_header dq SL_dqexp(dq q)
#if defined(SL_IMPLEMENTATION)
{
    double ex = exp(q.r);
    double angle = SL_dv3len(q.iv);
    double sin_angle = angle < 1e-8 ? 0.0 : ex * sin(angle) / angle;
    return (dq) {
        .r = ex * cos(angle),
        .i = q.i * sin_angle,
        .j = q.j * sin_angle,
        .k = q.k * sin_angle
    };
}
#else
;
#endif
/// @brief Logarithm of a fq
SL_header fq SL_fqln(fq q)
#if defined(SL_IMPLEMENTATION)
{
    double len = SL_fqlen(q);
    double arg = len < 1e-8 ? 0.0 : acos(q.r / len) / SL_fv3len(q.iv);
    return (fq) {
        .r = log(len),
        .i = q.i * arg,
        .j = q.j * arg,
        .k = q.k * arg
    };
}
#else
;
#endif
/// @brief Logarithm of a dq
SL_header dq SL_dqln(dq q)
#if defined(SL_IMPLEMENTATION)
{
    double len = SL_dqlen(q);
    double arg = len < 1e-8 ? 0.0 : acos(q.r / len) / SL_dv3len(q.iv);
    return (dq) {
        .r = log(len),
        .i = q.i * arg,
        .j = q.j * arg,
        .k = q.k * arg
    };
}
#else
;
#endif
/// @brief Logarithm of a fq of assumed unit length
SL_header fq SL_fqln_u(fq q)
#if defined(SL_IMPLEMENTATION)
{
    double arg = acos(q.r) / SL_fv3len(q.iv);
    return (fq) {
        .r = 0,
        .i = q.i * arg,
        .j = q.j * arg,
        .k = q.k * arg
    };
}
#else
;
#endif
/// @brief Logarithm of a dq of assumed unit length
SL_header dq SL_dqln_u(dq q)
#if defined(SL_IMPLEMENTATION)
{
    double arg = acos(q.r) / SL_dv3len(q.iv);
    return (dq) {
        .r = 0,
        .i = q.i * arg,
        .j = q.j * arg,
        .k = q.k * arg
    };
}
#else
;
#endif
/// @brief fq raised to the power of a float
SL_header fq SL_fqpow(fq q, float t)
#if defined(SL_IMPLEMENTATION)
{
    double len = SL_fqlen(q);
    if (len < 1e-8) return SL_fq_zero;
    double len_p = pow(len, t);
    double len_iv = SL_fv3len(q.iv);
    if (len_iv < 1e-8) return SL_fq_(len_p, 0, 0, 0);
    double arg = acos(q.w / len) * t;
    double sin_arg = sin(arg) / len_iv * len_p;
    return (fq) {
        .w = cos(arg) * len_p,
        .x = q.x * sin_arg,
        .y = q.y * sin_arg,
        .z = q.z * sin_arg
    };
}
#else
;
#endif
/// @brief dq raised to the power of a double
SL_header dq SL_dqpow(dq q, double t)
#if defined(SL_IMPLEMENTATION)
{
    double len = SL_dqlen(q);
    if (len < 1e-8) return SL_dq_zero;
    double len_p = pow(len, t);
    double len_iv = SL_dv3len(q.iv);
    if (len_iv < 1e-8) return SL_dq_(len_p, 0, 0, 0);
    double arg = acos(q.w / len) * t;
    double sin_arg = sin(arg) / len_iv * len_p;
    return (dq) {
        .w = cos(arg) * len_p,
        .x = q.x * sin_arg,
        .y = q.y * sin_arg,
        .z = q.z * sin_arg
    };
}
#else
;
#endif
/// @brief fq of assumed unit length raised to the power of a float
SL_header fq SL_fqpow_u(fq q, float t)
#if defined(SL_IMPLEMENTATION)
{
    double len_iv = SL_fv3len(q.iv);
    if (len_iv < 1e-8) return SL_fq_identity;
    double arg = acos(q.w) * t;
    double sin_arg = sin(arg) / len_iv;
    return (fq) {
        .w = cos(arg),
        .x = q.x * sin_arg,
        .y = q.y * sin_arg,
        .z = q.z * sin_arg
    };
}
#else
;
#endif
/// @brief dq of assumed unit length raised to the power of a double
SL_header dq SL_dqpow_u(dq q, double t)
#if defined(SL_IMPLEMENTATION)
{
    double len_iv = SL_dv3len(q.iv);
    if (len_iv < 1e-8) return SL_dq_identity;
    double arg = acos(q.w) * t;
    double sin_arg = sin(arg) / len_iv;
    return (dq) {
        .w = cos(arg),
        .x = q.x * sin_arg,
        .y = q.y * sin_arg,
        .z = q.z * sin_arg
    };
}
#else
;
#endif
/// @brief Rotation of a fv3 by a fq
SL_header fv3 SL_fqrot(fq q, fv3 v)
#if defined(SL_IMPLEMENTATION)
{
    float w2 = q.w * q.w, x2 = q.x * q.x, y2 = q.y * q.y, z2 = q.z * q.z;
    float wx = q.w * q.x, wy = q.w * q.y, wz = q.w * q.z, xy = q.x * q.y, yz = q.y * q.z, xz = q.x * q.z;

    return SL_fv3_(
        v.x * (w2 + x2 - y2 - z2) + 2 * ((xy + wz) * v.y + (xz - wy) * v.z),
        v.y * (w2 - x2 + y2 - z2) + 2 * ((xy - wz) * v.x + (yz + wx) * v.z),
        v.z * (w2 - x2 - y2 + z2) + 2 * ((xz + wy) * v.x + (yz - wx) * v.y)
    );
}
#else
;
#endif
/// @brief Rotation of a dv3 by a dq
SL_header dv3 SL_dqrot(dq q, dv3 v)
#if defined(SL_IMPLEMENTATION)
{
    double w2 = q.w * q.w, x2 = q.x * q.x, y2 = q.y * q.y, z2 = q.z * q.z;
    double wx = q.w * q.x, wy = q.w * q.y, wz = q.w * q.z, xy = q.x * q.y, yz = q.y * q.z, xz = q.x * q.z;

    return SL_dv3_(
        v.x * (w2 + x2 - y2 - z2) + 2 * ((xy + wz) * v.y + (xz - wy) * v.z),
        v.y * (w2 - x2 + y2 - z2) + 2 * ((xy - wz) * v.x + (yz + wx) * v.z),
        v.z * (w2 - x2 - y2 + z2) + 2 * ((xz + wy) * v.x + (yz - wx) * v.y)
    );
}
#else
;
#endif
/// @brief Spherical interpolation with parameter float t from fq a to fq b
/// @note With unit quaternions, this acts as an interpolation between two rotations
SL_header fq SL_fqserp(fq a, fq b, float t)
#if defined(SL_IMPLEMENTATION)
{
    return SL_fqmul(a, SL_fqpow(SL_fqmul(SL_fqinv(a), b), t));
}
#else
;
#endif
/// @brief Spherical interpolation with parameter double t from dq a to dq b
/// @note With unit quaternions, this acts as an interpolation between two rotations
SL_header dq SL_dqserp(dq a, dq b, double t)
#if defined(SL_IMPLEMENTATION)
{
    return SL_dqmul(a, SL_dqpow(SL_dqmul(SL_dqinv(a), b), t));
}
#else
;
#endif
/// @brief Spherical interpolation with parameter float t from fq a to fq b, both assumed of unit length
/// @note This acts as an interpolation between two rotations, allways following the shortest path
SL_header fq SL_fqserp_u(fq a, fq b, float t)
#if defined(SL_IMPLEMENTATION)
{
    fq inv_a = SL_fqtrsp(a);
    fq delta_q = SL_fqmul(inv_a, b);
    if (delta_q.w < 0.0) delta_q = SL_fqmul(inv_a, SL_fqneg(b));

    return SL_fqmul(a, SL_fqpow_u(delta_q, t));
}
#else
;
#endif
/// @brief Spherical interpolation with parameter double t from dq a to dq b, both assumed of unit length
/// @note This acts as an interpolation between two rotations, allways following the shortest path
SL_header dq SL_dqserp_u(dq a, dq b, double t)
#if defined(SL_IMPLEMENTATION)
{
    dq inv_a = SL_dqtrsp(a);
    dq delta_q = SL_dqmul(inv_a, b);
    if (delta_q.w < 0.0) delta_q = SL_dqmul(inv_a, SL_dqneg(b));

    return SL_dqmul(a, SL_dqpow_u(delta_q, t));
}
#else
;
#endif


#pragma endregion ARITHMETIC

#pragma region CONVERSION

/// @brief Unit fq representing XYZ (yaw pitch roll) euler rotation
SL_header fq SL_fqfrom_euler(double yaw, double pitch, double roll)
#if defined(SL_IMPLEMENTATION)
{
    double sy, cy; sincos(yaw * 0.5, &sy, &cy);
    double sp, cp; sincos(pitch * 0.5, &sp, &cp);
    double sr, cr; sincos(roll * 0.5, &sr, &cr);
    return (fq) {
       .a = cr*cp*cy - sr*sp*sy,
       .b = cr*sp*cy - sr*cp*sy,
       .c = sr*sp*cy + cr*cp*sy,
       .d = sr*cp*cy + cr*sp*sy
    };
}
#else
;
#endif
/// @brief Unit dq representing XYZ (yaw pitch roll) euler rotation
SL_header dq SL_dqfrom_euler(double yaw, double pitch, double roll)
#if defined(SL_IMPLEMENTATION)
{
    double sy, cy; sincos(yaw * 0.5, &sy, &cy);
    double sp, cp; sincos(pitch * 0.5, &sp, &cp);
    double sr, cr; sincos(roll * 0.5, &sr, &cr);
    return (dq) {
       .a = cr*cp*cy - sr*sp*sy,
       .b = cr*sp*cy - sr*cp*sy,
       .c = sr*sp*cy + cr*cp*sy,
       .d = sr*cp*cy + cr*sp*sy
    };
}
#else
;
#endif
/// @brief Assumed unit fq to euler angles representing XYZ (yaw pitch roll) euler rotation
SL_header fv3 SL_fqto_euler(fq q)
#if defined(SL_IMPLEMENTATION)
{
    double a =  q.w - q.x,
           b =  q.y - q.z,
           c =  q.x + q.w,
           d = -q.z - q.y;
    
    double t1, t3, t1h = 0.0;
    double t2 = acos(2.0 * (a*a + b*b) / (a*a + b*b + c*c + d*d) - 1.0);
    double tp = atan2(b, a);
    double tm = atan2(d, c);
    
    if (t2 < 1e-8) {
        t1 = t1h;
        t3 = 2.0 * tp - t1h;
    }
    else if (SL_PI - t2 < 1e-8) {
        t1 = t1h;
        t3 = 2.0 * tm + t1h;
    }
    else {
        t1 = tp - tm;
        t3 = tp + tm;
    }

    return (fv3) {
        .x = fmod(t1 + SL_TAU, SL_TAU),
        .y = fmod(t2 - SL_PI/2 + SL_TAU, SL_TAU),
        .z = fmod(SL_TAU - t3, SL_TAU)
    };
}
#else
;
#endif
/// @brief Assumed unit dq to euler angles representing XYZ (yaw pitch roll) euler rotation
SL_header dv3 SL_dqto_euler(dq q)
#if defined(SL_IMPLEMENTATION)
{
    double a =  q.w - q.x,
           b =  q.y - q.z,
           c =  q.x + q.w,
           d = -q.z - q.y;
    
    double t1, t3, t1h = 0.0;
    double t2 = acos(2.0 * (a*a + b*b) / (a*a + b*b + c*c + d*d) - 1.0);
    double tp = atan2(b, a);
    double tm = atan2(d, c);
    
    if (t2 < 1e-8) {
        t1 = t1h;
        t3 = 2.0 * tp - t1h;
    }
    else if (SL_PI - t2 < 1e-8) {
        t1 = t1h;
        t3 = 2.0 * tm + t1h;
    }
    else {
        t1 = tp - tm;
        t3 = tp + tm;
    }

    return (dv3) {
        .x = fmod(t1 + SL_TAU, SL_TAU),
        .y = fmod(t2 - SL_PI/2 + SL_TAU, SL_TAU),
        .z = fmod(SL_TAU - t3, SL_TAU)
    };
}
#else
;
#endif
/// @brief Unit fq based on angle-axis pair
SL_header fq SL_fqfrom_axisAngle(fv3 axis, double angle)
#if defined(SL_IMPLEMENTATION)
{
    double sin_angle = sin(angle *= 0.5);
    return (fq) {
        .r = cos(angle),
        .iv = SL_fv3muls(axis, sin_angle)
    };
}
#else
;
#endif
/// @brief Unit dq based on angle-axis pair
SL_header dq SL_dqfrom_axisAngle(dv3 axis, double angle)
#if defined(SL_IMPLEMENTATION)
{
    double sin_angle = sin(angle *= 0.5);
    return (dq) {
        .r = cos(angle),
        .iv = SL_dv3muls(axis, sin_angle)
    };
}
#else
;
#endif
/// @brief Angle-axis pair based on assumed unit fq
/// @note The returned vector is of the form `(fv4){ .xyz = axis, .w = angle }`
SL_header fv4 SL_fqto_axisAngle(fq q)
#if defined(SL_IMPLEMENTATION)
{
    double sin_half_angle = SL_fv3len(q.iv);
    return (fv4) {
        .xyz = SL_fv3muls(q.iv, 1.0 / sin_half_angle),
        .w = 2.0 * asin(sin_half_angle)
    };
}
#else
;
#endif
/// @brief Angle-axis pair based on assumed unit dq
/// @note The returned vector is of the form `(dv4){ .xyz = axis, .w = angle }`
SL_header dv4 SL_dqto_axisAngle(dq q)
#if defined(SL_IMPLEMENTATION)
{
    double sin_half_angle = SL_dv3len(q.iv);
    return (dv4) {
        .xyz = SL_dv3muls(q.iv, 1.0 / sin_half_angle),
        .w = 2.0 * asin(sin_half_angle)
    };
}
#else
;
#endif
/// @brief Unit fq representing the rotation from one fv3 to another fv3
SL_header fq SL_fqfrom_fromTo(fv3 from, fv3 to)
#if defined(SL_IMPLEMENTATION)
{
    fv3 axis = SL_fv3cross(to, from);
    if (axis.x || axis.y || axis.z) {
        float angle = acos(SL_fv3dot(from, to));
        return SL_fqfrom_axisAngle(SL_fv3norm(axis), angle);
    }
    return SL_fq_identity;
}
#else
;
#endif
/// @brief Unit dq representing the rotation from one dv3 to another dv3
SL_header dq SL_dqfrom_fromTo(dv3 from, dv3 to)
#if defined(SL_IMPLEMENTATION)
{
    dv3 axis = SL_dv3cross(to, from);
    if (axis.x || axis.y || axis.z) {
        float angle = acos(SL_dv3dot(from, to));
        return SL_dqfrom_axisAngle(SL_dv3norm(axis), angle);
    }
    return SL_dq_identity;
}
#else
;
#endif

#pragma endregion CONVERSION

#ifdef SL_STRIP_PREFIX
#   define  XPD_Q SL_XPD_Q
#   define  FMT_Q SL_FMT_Q
#   define  fq_zero SL_fq_zero
#   define  fq_identity SL_fq_identity
#   define  dq_zero SL_dq_zero
#   define  dq_identity SL_dq_identity
#   define  fq_ SL_fq_
#   define  dq_ SL_dq_
#   define  fqv SL_fqv
#   define  dqv SL_dqv
#   define  fqq SL_fqq
#   define  dqq SL_dqq
#   define  fqequ SL_fqequ
#   define  dqequ SL_dqequ
#   define  fqadd SL_fqadd
#   define  dqadd SL_dqadd
#   define  fqsub SL_fqsub
#   define  dqsub SL_dqsub
#   define  fqmul SL_fqmul
#   define  dqmul SL_dqmul
#   define  fqmuls SL_fqmuls
#   define  dqmuls SL_dqmuls
#   define  fqneg SL_fqneg
#   define  dqneg SL_dqneg
#   define  fqlen_sqr SL_fqlen_sqr
#   define  dqlen_sqr SL_dqlen_sqr
#   define  fqlen SL_fqlen
#   define  dqlen SL_dqlen
#   define  fqnorm SL_fqnorm
#   define  dqnorm SL_dqnorm
#   define  fqtrsp SL_fqtrsp
#   define  dqtrsp SL_dqtrsp
#   define  fqinv SL_fqinv
#   define  dqinv SL_dqinv
#   define  fqdiv SL_fqdiv
#   define  dqdiv SL_dqdiv
#   define  fqexp SL_fqexp
#   define  dqexp SL_dqexp
#   define  fqln SL_fqln
#   define  dqln SL_dqln
#   define  fqln_u SL_fqln_u
#   define  dqln_u SL_dqln_u
#   define  fqpow SL_fqpow
#   define  dqpow SL_dqpow
#   define  fqpow_u SL_fqpow_u
#   define  dqpow_u SL_dqpow_u
#   define  fqrot SL_fqrot
#   define  dqrot SL_dqrot
#   define  fqserp SL_fqserp
#   define  dqserp SL_dqserp
#   define  fqserp_u SL_fqserp_u
#   define  dqserp_u SL_dqserp_u
#   define  fqfrom_euler SL_fqfrom_euler
#   define  dqfrom_euler SL_dqfrom_euler
#   define  fqto_euler SL_fqto_euler
#   define  dqto_euler SL_dqto_euler
#   define  fqfrom_axisAngle SL_fqfrom_axisAngle
#   define  dqfrom_axisAngle SL_dqfrom_axisAngle
#   define  fqto_axisAngle SL_fqto_axisAngle
#   define  dqto_axisAngle SL_dqto_axisAngle
#   define  fqfrom_fromTo SL_fqfrom_fromTo
#   define  dqfrom_fromTo SL_dqfrom_fromTo
#endif

#endif // _SL_QUATERNION_H_

// quaternion.h: THIS FILE WAS GENERATED ON 09/10/2026 AT 02:24:41
