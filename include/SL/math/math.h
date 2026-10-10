#ifndef _SL_MATH_H_
#define _SL_MATH_H_

/*
 *  MATH: Math related functions and constructs. 
 *  
 *  TODO:
 *  - Provide more hashing functions
 * 
*/

#include <SL/base.h>

/// @brief The ratio of the circumference to the diameter
#define SL_PI 3.1415926535897931
/// @brief The ratio of the circumference to the radius
#define SL_TAU 6.2831853071796
/// @brief The ratio of 2*PI rad over 360°
#define SL_DEG_TO_RAD (SL_TAU / 360.0)
/// @brief The ratio of 360° over 2*PI rad
#define SL_RAD_TO_DEG (360.0 / SL_PI)
/// @brief Euler's number, e
#define SL_E 2.7182818284590452
/// @brief Golden ratio
#define SL_PHI 1.6180339887498948482045868

#define SL_FLOAT_MAX HUGE_VALF
#define SL_DOUBLE_MAX HUGE_VAL

/// @brief Get minimum value between a and b
/// @param a The first value
/// @param b The second value
/// @return The minimum of a and b
SL_header uint SL_umin(uint a, uint b);
/// @brief Get minimum value between a and b
/// @param a The first value
/// @param b The second value
/// @return The minimum of a and b
SL_header u64 SL_u64min(u64 a, u64 b);
/// @brief Get minimum value between a and b
/// @param a The first value
/// @param b The second value
/// @return The minimum of a and b
SL_header int SL_imin(int a, int b);
/// @brief Get minimum value between a and b
/// @param a The first value
/// @param b The second value
/// @return The minimum of a and b
SL_header i64 SL_i64min(i64 a, i64 b);
/// @brief Get minimum value between a and b
/// @param a The first value
/// @param b The second value
/// @return The minimum of a and b
SL_header float SL_fmin(float a, float b);
/// @brief Get minimum value between a and b
/// @param a The first value
/// @param b The second value
/// @return The minimum of a and b
SL_header double SL_dmin(double a, double b);

/// @brief Get maximum value between a and b
/// @param a The first value
/// @param b The second value
/// @return The maximum of a and b
SL_header uint SL_umax(uint a, uint b);
/// @brief Get maximum value between a and b
/// @param a The first value
/// @param b The second value
/// @return The maximum of a and b
SL_header u64 SL_u64max(u64 a, u64 b);
/// @brief Get maximum value between a and b
/// @param a The first value
/// @param b The second value
/// @return The maximum of a and b
SL_header int SL_imax(int a, int b);
/// @brief Get maximum value between a and b
/// @param a The first value
/// @param b The second value
/// @return The maximum of a and b
SL_header i64 SL_i64max(i64 a, i64 b);
/// @brief Get maximum value between a and b
/// @param a The first value
/// @param b The second value
/// @return The maximum of a and b
SL_header float SL_fmax(float a, float b);
/// @brief Get maximum value between a and b
/// @param a The first value
/// @param b The second value
/// @return The maximum of a and b
SL_header double SL_dmax(double a, double b);

/// @brief Sign of a an int
/// @param i The int
/// @return The sign of i
SL_header int SL_isign(int i);
/// @brief Sign of a an int64
/// @param i The i64
/// @return The sign of i
SL_header i64 SL_i64sign(i64 i);
/// @brief Sign of a an float
/// @param f The float
/// @return The sign of f
SL_header float SL_fsign(float f);
/// @brief Sign of a an double
/// @param f The double
/// @return The sign of f
SL_header double SL_dsign(double f);

/// @brief Floor f to the closest step
/// @param f The value to floor
/// @param step_size The size of a step
/// @return The greatest step lower than f
SL_header float SL_fstep(float f, float step_size);
/// @brief Floor f to the closest step
/// @param f The value to floor
/// @param step_size The size of a step
/// @return The greatest step lower than f
SL_header double SL_dstep(double f, double step_size);

/// @brief Linear interpolation between two floats
/// @param lhs The source float
/// @param rhs The destination float
/// @param t The interpolation factor
/// @return The resulting interpolated value
SL_header float SL_flerp(float lhs, float rhs, float t);
/// @brief Linear interpolation between two doubles
/// @param lhs The source double
/// @param rhs The destination double
/// @param t The interpolation factor
/// @return The resulting interpolated value
SL_header double SL_dlerp(double lhs, double rhs, double t);

/// @brief Clamp f between two values (low and high bounds)
/// @param f The value to clamp
/// @param min The low bound
/// @param max The high bound
/// @return The clamped value of f
SL_header float SL_fclamp(float f, float min, float max);
/// @brief Clamp f between two values (low and high bounds)
/// @param f The value to clamp
/// @param min The low bound
/// @param max The high bound
/// @return The clamped value of f
SL_header double SL_dclamp(double f, double min, double max);

/// @brief Interpret bits of a u32 as those of a float
/// @param u The u32
/// @return The resulting float
SL_header float SL_inplaceU32ToFloat(u32 u);
/// @brief Interpret bits of a float as those of a u32
/// @param f The float
/// @return The resulting u32
SL_header u32 SL_inplaceFloatToU32(float f);
/// @brief Interpret bits of a u64 as those of a double
/// @param u The u64
/// @return The resulting double
SL_header double SL_inplaceU64ToDouble(u64 u);
/// @brief Interpret bits of a double as those of a u64
/// @param f The double
/// @return The resulting u64
SL_header u64 SL_inplaceDoubleToU64(double f);
/// @brief Interpret bits of a u32 as the mantissa of a float brought back the the [0.0f, 1.0f] range
/// @param u The u32
/// @return The resulting float
SL_header float SL_inplaceU32ToFloat01(u32 u);
/// @brief Interpret bits of a u64 as the mantissa of a double brought back the the [0.0, 1.0] range
/// @param u The u64
/// @return The resulting double
SL_header double SL_inplaceU64ToDouble01(u64 u);

/// @brief PCG hashing of a u32
/// @param u The u32
/// @return The hashed u32
SL_header u32 SL_u32hash_PCG(u32 u);
/// @brief Set the seed of the pseudo-random u32 generator
/// @param new_seed The new seed
/// @note Based on the PCG hash
SL_header void SL_u32srand(u32 new_seed);
/// @brief Generate a pseudo-random u32
/// @return The random u32
SL_header u32 SL_u32rand();
/// @brief Generate a pseudo-random u32 in the range [low, high]
/// @param low Lowest value
/// @param high Highest value
/// @return A value between low and high
SL_header u32 SL_u32rand_in(u32 low, u32 high);

/// @brief Generate a pseudo-random float in the range [0.0f, 1.0f]
/// @return The randomly generated float
SL_header float SL_frand();
/// @brief Generate a pseudo-random double in the range [0.0, 1.0]
/// @return The randomly generated double
SL_header double SL_drand();
/// @brief Generate a pseudo-random float in the range [low, high]
/// @param low Lowest value
/// @param high Highest value
/// @return The randomly generated float
SL_header float SL_frand_in(float low, float high);
/// @brief Generate a pseudo-random double in the range [low, high]
/// @param low Lowest value
/// @param high Highest value
/// @return The randomly generated double
SL_header double SL_drand_in(double low, double high);

#ifndef _WIN32
    SL_header void sincos(double angle, double *s, double *c);
#endif



#ifdef SL_STRIP_PREFIX
#   define PI                       SL_PI
#   define TAU                      SL_TAU
#   define DEG_TO_RAD               SL_DEG_TO_RAD
#   define RAD_TO_DEG               SL_RAD_TO_DEG
#   define E                        SL_E
#   define PHI                      SL_PHI
#   define FLOAT_MAX                SL_FLOAT_MAX
#   define DOUBLE_MAX               SL_DOUBLE_MAX
#   define umin                     SL_umin
#   define u64min                   SL_u64min
#   define imin                     SL_imin
#   define i64min                   SL_i64min
#   define fmin                     SL_fmin
#   define dmin                     SL_dmin
#   define umax                     SL_umax
#   define u64max                   SL_u64max
#   define imax                     SL_imax
#   define i64max                   SL_i64max
#   define fmax                     SL_fmax
#   define dmax                     SL_dmax
#   define isign                    SL_isign
#   define i64sign                  SL_i64sign
#   define fsign                    SL_fsign
#   define dsign                    SL_dsign
#   define fstep                    SL_fstep
#   define dstep                    SL_dstep
#   define flerp                    SL_flerp
#   define dlerp                    SL_dlerp
#   define fclamp                   SL_fclamp
#   define dclamp                   SL_dclamp
#   define inplaceU32ToFloat        SL_inplaceU32ToFloat
#   define inplaceFloatToU32        SL_inplaceFloatToU32
#   define inplaceU64ToDouble       SL_inplaceU64ToDouble
#   define inplaceDoubleToU64       SL_inplaceDoubleToU64
#   define inplaceU32ToFloat01      SL_inplaceU32ToFloat01
#   define inplaceU64ToDouble01     SL_inplaceU64ToDouble01
#   define u32hash_PCG              SL_u32hash_PCG
#   define u32srand                 SL_u32srand
#   define u32rand                  SL_u32rand
#   define u32rand_in               SL_u32rand_in
#   define frand                    SL_frand
#   define drand                    SL_drand
#   define frand_in                 SL_frand_in
#   define drand_in                 SL_drand_in
#endif



#ifdef SL_IMPLEMENTATION
SL_header u32 SL_umin(u32 a, u32 b)          { return a < b ? a : b; }
SL_header u64 SL_u64min(u64 a, u64 b)        { return a < b ? a : b; }
SL_header int SL_imin(int a, int b)          { return a < b ? a : b; }
SL_header i64 SL_i64min(i64 a, i64 b)        { return a < b ? a : b; }
SL_header float SL_fmin(float a, float b)    { return a < b ? a : b; }
SL_header double SL_dmin(double a, double b) { return a < b ? a : b; }

SL_header u32 SL_umax(u32 a, u32 b)          { return a > b ? a : b; }
SL_header u64 SL_u64max(u64 a, u64 b)        { return a > b ? a : b; }
SL_header int SL_imax(int a, int b)          { return a > b ? a : b; }
SL_header i64 SL_i64max(i64 a, i64 b)        { return a > b ? a : b; }
SL_header float SL_fmax(float a, float b)    { return a > b ? a : b; }
SL_header double SL_dmax(double a, double b) { return a > b ? a : b; }

SL_header int SL_isign(int i)   { return i == 0    ? 0    : i > 0    ? 1    : -1;    }
SL_header i64 SL_i64sign(i64 i) { return i == 0    ? 0    : i > 0    ? 1    : -1;    }
SL_header f32 SL_fsign(f32 f)   { return f == 0.0f ? 0.0f : f > 0.0f ? 1.0f : -1.0f; }
SL_header f64 SL_dsign(f64 f)   { return f == 0.0  ? 0.0  : f > 0.0  ? 1.0  : -1.0;  }

SL_header float SL_fstep(float f, float step_size) { return floorf(f / step_size) * step_size; }
SL_header double SL_dstep(double f, double step_size) { return floor(f / step_size) * step_size; }
SL_header float SL_flerp(float a, float b, float t) { return a + (b - a) * t; }
SL_header double SL_dlerp(double a, double b, double t) { return a + (b - a) * t; }
SL_header float SL_fclamp(float f, float min, float max) { return f < min ? min : (f > max ? max : f); }
SL_header double SL_dclamp(double f, double min, double max) { return f < min ? min : (f > max ? max : f); }

SL_header float SL_inplaceU32ToFloat(u32 u) {
    union { float f; u32 u; } val = {.u = u};
    return val.f;
}
SL_header u32 SL_inplaceFloatToU32(float f) {
    union { float f; u32 u; } val = {.f = f};
    return val.u;
}
SL_header double SL_inplaceU64ToDouble(u64 u) {
    union { double d; u64 u; } val = {.u = u};
    return val.d;
}
SL_header u64 SL_inplaceDoubleToU64(double f) {
    union { double f; u64 u; } val = {.f = f};
    return val.u;
}

SL_header float SL_inplaceU32ToFloat01(u32 u) {
    union { float f; u32 u; } val = {.u = (u & 0x007FFFFFu) | 0x3F800000u};
    return val.f - 1.0f;
}
SL_header double SL_inplaceU64ToDouble01(u64 u) {
    union { double f; u64 u; } val = {.u = (u & 0x000FFFFFFFFFFFFFllu) | 0x3FF0000000000000llu};
    return val.f - 1.0;
}

SL_header u32 SL_u32hash_PCG(u32 u) {
    u32 state = u * 747796405u + 2891336453u;
    u32 word = ((state >> ((state >> 28) + 4)) ^ state) * 277803737u;
    return (word >> 22) ^ word;
}
static u32 __SL_RAND_SEED__ = 0;
SL_header void SL_u32srand(u32 new_seed) { __SL_RAND_SEED__ = new_seed; };
SL_header u32 SL_u32rand() { return __SL_RAND_SEED__ = SL_u32hash_PCG(__SL_RAND_SEED__); }
SL_header u32 SL_u32rand_in(u32 low, u32 high) { return high <= low ? low : low + (SL_u32rand() % (high - low)); }

SL_header float SL_frand() { return SL_inplaceU32ToFloat01(SL_u32rand()); }
SL_header double SL_drand() { return SL_inplaceU64ToDouble01(((u64)SL_u32rand() << 32LLU) | (u64)SL_u32rand()); }
SL_header float SL_frand_in(float low, float high) { return low + SL_frand() * (high - low); }
SL_header double SL_drand_in(double low, double high) { return low + SL_drand() * (high - low); }

#ifndef _WIN32
    SL_header void sincos(double angle, double *s, double *c)
    {
        *s = sin(angle);
        *c = cos(angle);
    }
#endif
#endif
#endif // _SL_MATH_H_