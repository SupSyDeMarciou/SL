#ifndef _SL_BASE_H_
#define _SL_BASE_H_

/*
 *  BASE: Useful constructs which aren't big enough to warant their own header file. 
 *  
 *  TODO:
 *  - 
 * 
*/

#ifndef SL_NO_STDLIB
    #include <stdint.h>
    #include <stdbool.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <stddef.h>
    #include <string.h>
    #include <math.h>
    #include <stdarg.h>
    #include <ctype.h>

    #ifdef _WIN32
    #   define sleep _sleep
    #else
    #   include <unistd.h>
    #endif
#endif

#ifndef SL_header
#   define SL_header static inline
#endif
#ifndef thread_local
#   define thread_local _Thread_local
#endif
#if defined(__clang__) || defined(__GNUC__)
#   define typeof __typeof__
#endif

#ifndef SL_always_inline
#   ifdef _MSC_VER
#       define SL_always_inline __forceinline
#   elif defined(__GNUC__)
#       define SL_always_inline __attribute__((__always_inline__))
#   elif defined(__clang__)
#       if __has_attribute(__always_inline__)
#           define SL_always_inline __attribute__((__always_inline__))
#       else
#           define SL_always_inline inline
#       endif
#   else
#       define SL_always_inline inline
#   endif
#endif

#if defined(SL_IMPLEMENTATION)
#   define SL_implement(...) __VA_ARGS__
#else
#   define SL_implement(...)
#endif

#ifndef STR
#   define __STR(value) #value
#   define STR(value) __STR(value)
#endif

#ifndef CAT
#   define __CAT(x, y) x##y
#   define CAT(x, y) __CAT(x, y)
#endif

#ifndef NOP
#   define NOP(x) x
#endif



#pragma region TYPES

#define SL_ptr(type) CAT(type, _p)
#define SL_DEF_PTR(type) \
    typedef type   *CAT(type, _p); \
    typedef type  **CAT(type, _pp); \
    typedef type ***CAT(type, _ppp)
#define SL_ALIAS_PTR(base_type, new_type) \
    typedef CAT(base_type, _p)   CAT(new_type, _p); \
    typedef CAT(base_type, _pp)  CAT(new_type, _pp); \
    typedef CAT(base_type, _ppp) CAT(new_type, _ppp)

SL_DEF_PTR(void); SL_DEF_PTR(int); SL_DEF_PTR(char); SL_DEF_PTR(float); SL_DEF_PTR(double);

#ifdef bool
#   undef bool
    typedef _Bool bool;
    SL_DEF_PTR(bool);
#   define bool bool
#endif

#ifdef complex
#   ifdef I
#       undef I
#       define lj _Complex_I
#   endif
    SL_DEF_PTR(complex);
#endif

typedef unsigned    uint;   SL_DEF_PTR(uint);
typedef size_t      usize;  SL_DEF_PTR(usize);  typedef ssize_t     ssize;      SL_DEF_PTR(ssize);

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

typedef char        char8;  SL_DEF_PTR(char8);
typedef wchar_t     char16; SL_DEF_PTR(char16);
typedef u32         char32; SL_DEF_PTR(char32);

typedef _Float16    f16;    SL_DEF_PTR(f16);
typedef float       f32;    SL_DEF_PTR(f32);
typedef double      f64;    SL_DEF_PTR(f64);
typedef __float128  f128;   SL_DEF_PTR(f128);

#define SL_DEF_ALIAS(base_type, ...) typedef base_type __VA_ARGS__

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

#define SL_terminate(error_code, msg, ...) (fprintf(stderr, "%s:%u@%s - [TERMINATED(%d)] " msg, __FILE__, __LINE__, __FUNCTION__, error_code, ##__VA_ARGS__), exit(error_code))

#pragma endregion ERROR



#pragma region GENERIC

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
#define new(...) ((typeof(__VA_ARGS__) *)memclone(__SL_PTR((__VA_ARGS__)), sizeof(__VA_ARGS__)))
/// @brief Allocate and fill memory on the heap from a static array
/// @param ... The array with which to fill the newly allocated memory
/// @return The newly allocated memory
#define new_sa(...) ((typeof((__VA_ARGS__)[0]) *)memclone(__VA_ARGS__, sizeof(__VA_ARGS__)))

#define SL_static_count(static_array) (sizeof(static_array) / sizeof((static_array)[0]))

#define SL_min(a, b) ((a) < (b) ? (a) : (b))
#define SL_max(a, b) ((a) > (b) ? (a) : (b))

#define SL_swap(a, b) do { typeof(a) __SL_SWAP__ = (a); (a) = (b); (b) = __SL_SWAP__; } while (0)
#define __SL_swapi(a, b, cast) (*(cast *)&(a) ^= *(cast *)&(b), *(cast *)&(b) ^= *(cast *)&(a), *(cast *)&(a) ^= *(cast *)&(b))
#define SL_swapi(a, b) (                     \
    sizeof(a) == 1 ? __SL_swapi(a, b, u8)  : \
    sizeof(a) == 2 ? __SL_swapi(a, b, u16) : \
    sizeof(a) == 3 ? __SL_swapi(a, b, u32) : \
                     __SL_swapi(a, b, u64)   \
)

/// @brief Temporary formated string
/// @param fmt The format. If `NULL`, returns the last temporary string
/// @param ... Additionnal arguments to format
/// @return The temporary formatted string
/// @warning This string is only valid until the next use of `tmpf`. DO NOT FREE THIS STRING
SL_header char *SL_tmpf(const char *fmt, ...);
#define SL_strf(fmt, ...) strdup(SL_tmpf(fmt, ##__VA_ARGS__))

/// @brief Align `n` to the next power of two
/// @param n The value to approach
/// @return The smallest power of two greater than `n`
SL_header u64 SL_alignPow2(u64 n);

#define __SL_DEF_CMP_FUNC(type, lhs, rhs, header, impl) header int type##_cmp(const type *lhs, const type *rhs); header int type##_cmp_inv(const type *lhs, const type *rhs) impl({ return -type##_cmp(lhs, rhs); }); header int type##_cmp(const type *lhs, const type *rhs) 
/// @brief Define a comparaison function to use with qsort or dict
/// @param type Type of the compared values
/// @param lhs The name of the left operand
/// @param rhs The name of the right operand
/// @note `lhs` and `rhs` are pointers to their values
/// @return Definition of functions `int {type}_cmp(const type *lhs, const type *rhs)` and `int {type}_cmp_inv(const type *lhs, const type *rhs)`, the second function returning the opposite of the first
#define SL_DEF_CMP_FUNC(type, lhs, rhs) __SL_DEF_CMP_FUNC(type, lhs, rhs, , NOP)
/// @brief Define a hash function to use with dict
/// @param type Type of the hashed key
/// @param key Name of the key operand
/// @return Definition of the function `usize {type}_hash(const type *key, usize size)`
#define SL_DEF_HASH_FUNC(type, key) SL_header usize type##_hash(const type *key)

#pragma endregion GENERIC



#ifdef SL_STRIP_PREFIX
#   define ptr              SL_ptr
#   define DEF_PTR          SL_DEF_PTR
#   define DEF_ALIAS        SL_DEF_ALIAS
#   define gprintf          SL_gprintf
#   define vgprintf         SL_vgprintf
#   define tmpf             SL_tmpf
#   define strf             SL_strf
#   define alignPow2        SL_alignPow2
#   define static_count     SL_static_count
#   define DEF_CMP_FUNC     SL_DEF_CMP_FUNC
#   define DEF_HASH_FUNC    SL_DEF_HASH_FUNC
#endif



#ifdef SL_IMPLEMENTATION
sl_error __SL_ERROR(sl_error new_error)
{
    static sl_error error = SL_ERROR_NONE;

    sl_error cur_error = error;
    error = new_error;
    return cur_error;
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
    return newData ? memcpy(newData, memory, size) : NULL;
}

SL_header char *SL_tmpf(const char *fmt, ...)
{
    static thread_local char *tmp = NULL;
    static thread_local usize capa = 0;
    if (fmt == NULL) return tmp;

    va_list args0; va_start(args0, fmt);
    
    va_list args1; va_copy(args1, args0);
    usize print_len = 1 + vsnprintf(tmp, capa, fmt, args1);
    va_end(args1);

    if (print_len >= capa) {
        if (tmp) free(tmp);
        tmp = malloc(capa = SL_alignPow2(print_len));
        vsnprintf(tmp, capa, fmt, args0);
    }
    va_end(args0);
    
    return tmp;
}

SL_header u64 SL_alignPow2(u64 n) {
    u64 i = 1;
    while (i < n) i <<= 1;
    return i;
}
#endif




#ifndef SL_NO_DEFINES
    __SL_DEF_CMP_FUNC(int,    a, b, SL_header, SL_implement) SL_implement({ return (i64)*a - (i64)*b; });
    __SL_DEF_CMP_FUNC(i8,     a, b, SL_header, SL_implement) SL_implement({ return (i64)*a - (i64)*b; });
    __SL_DEF_CMP_FUNC(i16,    a, b, SL_header, SL_implement) SL_implement({ return (i64)*a - (i64)*b; });
    __SL_DEF_CMP_FUNC(i32,    a, b, SL_header, SL_implement) SL_implement({ return (i64)*a - (i64)*b; });
    __SL_DEF_CMP_FUNC(i64,    a, b, SL_header, SL_implement) SL_implement({ return *a < *b ? -1 : (*a > *b ? 1 : 0); });
    __SL_DEF_CMP_FUNC(uint,   a, b, SL_header, SL_implement) SL_implement({ return (i64)*a - (i64)*b; });
    __SL_DEF_CMP_FUNC(u8,     a, b, SL_header, SL_implement) SL_implement({ return (i64)*a - (i64)*b; });
    __SL_DEF_CMP_FUNC(u16,    a, b, SL_header, SL_implement) SL_implement({ return (i64)*a - (i64)*b; });
    __SL_DEF_CMP_FUNC(u32,    a, b, SL_header, SL_implement) SL_implement({ return (i64)*a - (i64)*b; });
    __SL_DEF_CMP_FUNC(u64,    a, b, SL_header, SL_implement) SL_implement({ return *a < *b ? -1 : (*a > *b ? 1 : 0); });
    __SL_DEF_CMP_FUNC(ssize,  a, b, SL_header, SL_implement) SL_implement({ return *a < *b ? -1 : (*a > *b ? 1 : 0); });
    __SL_DEF_CMP_FUNC(usize,  a, b, SL_header, SL_implement) SL_implement({ return *a < *b ? -1 : (*a > *b ? 1 : 0); });
    __SL_DEF_CMP_FUNC(float,  a, b, SL_header, SL_implement) SL_implement({ return *a < *b ? -1 : (*a > *b ? 1 : 0); });
    __SL_DEF_CMP_FUNC(double, a, b, SL_header, SL_implement) SL_implement({ return *a < *b ? -1 : (*a > *b ? 1 : 0); });
    __SL_DEF_CMP_FUNC(bool,   a, b, SL_header, SL_implement) SL_implement({ return !*a && *b ? -1 : (*a && !*b ? 1 : 0); });

    __SL_DEF_CMP_FUNC(char_p, a, b, SL_header, SL_implement) SL_implement({ return strcmp(*a, *b); });
    SL_DEF_HASH_FUNC(char_p, key) SL_implement
    ({
        usize h = 0x02468ACE;
        for (const char *c = *key; *c; ++c) {
            h ^= *c;
            h *= 0x5bd1e995;
            h ^= h >> 15;
        }
        return h;
    });
#endif

#endif // _SL_BASE_H_
