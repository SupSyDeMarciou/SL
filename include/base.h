#ifndef _SL_BASE_H_
#define _SL_BASE_H_

/*
 *  BASE: Useful constructs reused throughout the SL
 */

#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__))
#   define __SL_POSIX__
#endif



#ifndef SL_NO_STDLIB
    #include <stdint.h>
    #include <stdbool.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <stddef.h>
    #include <stdarg.h>
    #include <string.h>
    #include <errno.h>
    #include <math.h>
    #include <ctype.h>
    #include <time.h>
    #include <pthread.h>

    #ifdef __SL_POSIX__ 
    #   include <unistd.h>
    #endif
#endif


#ifndef CAT
#   define __CAT(x, y) x##y
#   define CAT(x, ...) __CAT(x, __VA_ARGS__)
#endif

#ifndef thread_local
#   define thread_local _Thread_local
#endif
#if defined(__clang__) || defined(__GNUC__)
#   define typeof __typeof__
#endif

#ifndef SL_header
#   define SL_header static inline
#endif
#if defined(SL_IMPLEMENTATION)
#   define SL_implement(...) __VA_ARGS__
#else
#   define SL_implement(...)
#endif

#define __SL_DEF_CMP_FUNC(type, lhs, rhs, header, impl) header int type##_cmp(const type *lhs, const type *rhs); header int type##_cmp_inv(const type *lhs, const type *rhs) impl({ return -type##_cmp(lhs, rhs); }); header int type##_cmp(const type *lhs, const type *rhs) 
/// @brief Define a comparaison function to use with qsort or dict
/// @param type Type of the compared values
/// @param lhs The name of the left operand
/// @param rhs The name of the right operand
/// @note `lhs` and `rhs` are pointers to their values
/// @return Definition of functions `int {type}_cmp(const type *lhs, const type *rhs)` and `int {type}_cmp_inv(const type *lhs, const type *rhs)`, the second function returning the opposite of the first
#define SL_DEF_CMP_FUNC(type, lhs, rhs) __SL_DEF_CMP_FUNC(type, lhs, rhs, , CAT)



#pragma region TYPES

#define SL_ptr(type)  CAT(type, p)
#define SL_ptr2(type) CAT(type, pp)
#define SL_ptr3(type) CAT(type, ppp)
#define SL_DEF_PTR(type) \
    typedef type   *CAT(type, p); \
    typedef type  **CAT(type, pp); \
    typedef type ***CAT(type, ppp)
#define SL_ALIAS_PTR(base_type, new_type) \
    typedef CAT(base_type, p)   CAT(new_type, p); \
    typedef CAT(base_type, pp)  CAT(new_type, pp); \
    typedef CAT(base_type, ppp) CAT(new_type, ppp)

SL_DEF_PTR(void); SL_DEF_PTR(int); SL_DEF_PTR(char); SL_DEF_PTR(float); SL_DEF_PTR(double);

#ifdef bool
#   undef bool
    typedef _Bool bool;
    SL_DEF_PTR(bool);
#   define bool bool
#endif

#ifdef complex
#   undef complex
    typedef _Complex complex;
    SL_DEF_PTR(complex);
#   define complex complex
#   ifdef I
#       undef I
#       define lj _Complex_I
#   endif
#endif

typedef unsigned    uint;   SL_DEF_PTR(uint);
typedef size_t      usize;  SL_DEF_PTR(usize);

#ifdef __SL_POSIX__
    typedef ssize_t ssize;  SL_DEF_PTR(ssize);
#else
    typedef int64_t ssize;  SL_DEF_PTR(ssize);
#endif

typedef uint8_t     u8;     SL_DEF_PTR(u8);
typedef uint16_t    u16;    SL_DEF_PTR(u16);
typedef uint32_t    u32;    SL_DEF_PTR(u32);
typedef uint64_t    u64;    SL_DEF_PTR(u64);
typedef int8_t      i8;     SL_DEF_PTR(i8);
typedef int16_t     i16;    SL_DEF_PTR(i16);
typedef int32_t     i32;    SL_DEF_PTR(i32);
typedef int64_t     i64;    SL_DEF_PTR(i64);
#ifdef _INT128_DEFINED
typedef __int128_t  i128;   SL_DEF_PTR(i128);
typedef __uint128_t u128;   SL_DEF_PTR(u128);
#endif

typedef char        ch8;  SL_DEF_PTR(ch8);
typedef wchar_t     ch16; SL_DEF_PTR(ch16);
typedef u32         ch32; SL_DEF_PTR(ch32);

typedef _Float16    f16;    SL_DEF_PTR(f16);
typedef float       f32;    SL_DEF_PTR(f32);
typedef double      f64;    SL_DEF_PTR(f64);
typedef __float128  f128;   SL_DEF_PTR(f128);

#pragma endregion TYPES



#pragma region ERROR

typedef enum sl_error {
    SL_ERROR_NONE = 0,

    SL_ERROR_OUT_OF_BOUNDS,               /// @brief When a value is not stored within a container
    SL_ERROR_MEMORY,                      /// @brief Errors from `malloc`, `memcpy`, `memmove`, etc.
    SL_ERROR_DIVISION_BY_ZERO,            /// @brief When a division by zero occurs
    SL_ERROR_MISSMATCHING_DIMENSIONS,     /// @brief When two operands which are expected to share the same dimensions do not 
    SL_ERROR_THREAD_CREATE,               /// @brief When `pthread_create` fails
    SL_ERROR_THREAD_JOIN,                 /// @brief When `pthread_join` fails
    SL_ERROR_DUPLICATE,                   /// @brief When data is supposed to be unique
    SL_ERROR_MISSING_VALUE,               /// @brief When an expected piece of data is missing
} sl_error;

SL_header sl_error __SL_ERROR(sl_error);
#define SL_ERROR (__SL_ERROR(SL_ERROR_NONE))
SL_header const char *SL_strerr(sl_error error);

#define SL_terminate(error_code, msg, ...) (fprintf(stderr, "%s:%u@%s - [TERMINATED(%d)] " msg, __FILE__, __LINE__, __func__, error_code, ##__VA_ARGS__), exit(error_code))

#pragma endregion ERROR



#pragma region MEMORY

#if defined(__GNUC__) || defined(__clang__)
#   define __SL_PTR(...) ((typeof(__VA_ARGS__)[1]){__VA_ARGS__})
#   define __SL_PTR_T(type, ...) ((type[1]){(type)(__VA_ARGS__)})
#else
#   define __SL_PTR(...) (&(__VA_ARGS__))
#   define __SL_PTR_T(type, ...) (&((type)(__VA_ARGS__)))
#endif

/// @brief Clone a memory block
/// @param memory Source
/// @param size Size of the source in bytes
/// @return The newly cloned memory
SL_header void *memclone(void *memory, size_t size);

/// @brief Allocate and fill memory on the heap
/// @param ... The value with which to fill the newly allocated memory
/// @return The newly allocated memory
#define SL_new(...) ((typeof(__VA_ARGS__) *)memclone(__SL_PTR((__VA_ARGS__)), sizeof(__VA_ARGS__)))
/// @brief Allocate and fill memory on the heap from a static array
/// @param ... The array with which to fill the newly allocated memory
/// @return The newly allocated memory
#define SL_new_sa(...) ((typeof((__VA_ARGS__)[0]) *)memclone(__VA_ARGS__, sizeof(__VA_ARGS__)))
/// @brief Elements count in a static array
/// @param static_array Static array
/// @return The number of elements in the static array
#define SL_sa_count(static_array) (sizeof(static_array) / sizeof((static_array)[0]))
/// @brief Swap values in variables a and b
/// @param a The first operand
/// @param b The second operand
#define SL_swap(a, b) do { typeof(a) __SL_SWAP__ = (a); (a) = (b); (b) = __SL_SWAP__; } while (0)

/// @brief Align `n` to the next power of two
/// @param n The value to approach
/// @return The smallest power of two greater than `n`
SL_header u64 SL_alignPow2(u64 n);

#ifndef __SL_POSIX__
    SL_header char *strdup(const char *src);
#endif

#pragma endregion MEMORY



#ifdef SL_STRIP_PREFIX
#   define  ptr             SL_ptr
#   define  DEF_PTR         SL_DEF_PTR
#   define  new             SL_new
#   define  new_sa          SL_new_sa
#   define  sa_count        SL_sa_count
#   define  swap            SL_swap
#   define  alignPow2       SL_alignPow2
#   define  DEF_CMP_FUNC    SL_DEF_CMP_FUNC
#endif



#ifdef SL_IMPLEMENTATION
SL_header sl_error __SL_ERROR(sl_error new_error)
{
    static sl_error error = SL_ERROR_NONE;

    sl_error last_error = error;
    error = new_error;
    return last_error;
}

SL_header const char *SL_strerr(sl_error error)
{
    switch (error) {
        case SL_ERROR_NONE:                    return "NO ERROR";
        case SL_ERROR_OUT_OF_BOUNDS:           return "OUT OF BOUNDS";
        case SL_ERROR_MEMORY:                  return "MEMORY";
        case SL_ERROR_DIVISION_BY_ZERO:        return "DIVISION BY ZERO";
        case SL_ERROR_MISSMATCHING_DIMENSIONS: return "MISSMATCHING DIMENSIONS";
        case SL_ERROR_THREAD_CREATE:           return "THREAD CREATE";
        case SL_ERROR_THREAD_JOIN:             return "THREAD JOIN";
        case SL_ERROR_DUPLICATE:               return "DUPLICATE";
        case SL_ERROR_MISSING_VALUE:           return "MISSING VALUE";
        default: return "[UNKNOWN ERROR]";
    }
}

SL_header void *memclone(void *memory, size_t size)
{
    void *newData = malloc(size);
    return newData ? memcpy(newData, memory, size) : (__SL_ERROR(SL_ERROR_MEMORY), NULL);
}

SL_header u64 SL_alignPow2(u64 n) {
    u64 i = 1;
    while (i < n) i <<= 1;
    return i;
}

#ifndef __SL_POSIX__
    SL_header char *strdup(const char *src)
    {
        char *ret = malloc(strlen(src) + 1);
        return ret ? strcpy(ret, src) : NULL; 
    }
#endif
#endif



#ifndef SL_NO_DEFINES
    __SL_DEF_CMP_FUNC(int,    a, b, SL_header, SL_implement) SL_implement({ return *a < *b ? -1 : *a - *b; });
    __SL_DEF_CMP_FUNC(i8,     a, b, SL_header, SL_implement) SL_implement({ return *a < *b ? -1 : *a - *b; });
    __SL_DEF_CMP_FUNC(i16,    a, b, SL_header, SL_implement) SL_implement({ return *a < *b ? -1 : *a - *b; });
    __SL_DEF_CMP_FUNC(i32,    a, b, SL_header, SL_implement) SL_implement({ return *a < *b ? -1 : *a - *b; });
    __SL_DEF_CMP_FUNC(i64,    a, b, SL_header, SL_implement) SL_implement({ return *a < *b ? -1 : *a - *b; });
    __SL_DEF_CMP_FUNC(uint,   a, b, SL_header, SL_implement) SL_implement({ return *a < *b ? -1 : *a - *b; });
    __SL_DEF_CMP_FUNC(u8,     a, b, SL_header, SL_implement) SL_implement({ return *a < *b ? -1 : *a - *b; });
    __SL_DEF_CMP_FUNC(u16,    a, b, SL_header, SL_implement) SL_implement({ return *a < *b ? -1 : *a - *b; });
    __SL_DEF_CMP_FUNC(u32,    a, b, SL_header, SL_implement) SL_implement({ return *a < *b ? -1 : *a - *b; });
    __SL_DEF_CMP_FUNC(u64,    a, b, SL_header, SL_implement) SL_implement({ return *a < *b ? -1 : *a - *b; });
    __SL_DEF_CMP_FUNC(ssize,  a, b, SL_header, SL_implement) SL_implement({ return *a < *b ? -1 : *a - *b; });
    __SL_DEF_CMP_FUNC(usize,  a, b, SL_header, SL_implement) SL_implement({ return *a < *b ? -1 : *a - *b; });
    __SL_DEF_CMP_FUNC(float,  a, b, SL_header, SL_implement) SL_implement({ return *a < *b ? -1 : *a - *b; });
    __SL_DEF_CMP_FUNC(double, a, b, SL_header, SL_implement) SL_implement({ return *a < *b ? -1 : *a - *b; });
    __SL_DEF_CMP_FUNC(bool,   a, b, SL_header, SL_implement) SL_implement({ return !*a && *b ? -1 : (*a && !*b ? 1 : 0); });

    __SL_DEF_CMP_FUNC(charp,  a, b, SL_header, SL_implement) SL_implement({ return strcmp(*a, *b); });
#endif
#endif // _SL_BASE_H_
