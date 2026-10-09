#ifndef _SL_IO_H_
#define _SL_IO_H_

/*
 *  IO: Utilities for io. 
 *  
 *  TODO:
 *  - Fix unexpected results when streaming to a `char *`. Should add a position to enable multiple calls to gprintf to be concatenated (specificaly when reusing the stream in the context of the `put`)
 *  - Utilities for manipulating path (extracting file extension, file name, folder hierarchy, stepping through ?)
 *  
*/

#include "../base.h"

/// @brief Temporary formated string
/// @param fmt The format. If `NULL`, returns the last temporary string
/// @param ... Additionnal arguments to format
/// @return The temporary formatted string
/// @warning This string is only valid until the next use of `tmpf`. DO NOT FREE THIS STRING
SL_header char *SL_tmpf(const char *fmt, ...);
#define SL_strf(fmt, ...) strdup(SL_tmpf(fmt, ##__VA_ARGS__))

/// @brief Transform evrey character in a string based on an input function
/// @param str String to transform
/// @param func Function to apply
/// @return The input string, to allow chaining functions
SL_header char *SL_strtrsfrm(char *str, int (*func)(int));
/// @brief Apply "toupper" function to every character in string
/// @param str String to turn uppercase
/// @return The input string, to allow chaining functions
SL_header char *SL_strupper(char *str);
/// @brief Apply "tolower" function to every character in string
/// @param str String to turn uppercase
/// @return The input string, to allow chaning functions
SL_header char *SL_strlower(char *str);
/// @brief Check wether a string starts with another
/// @param str String in which to search
/// @param fact Substring to find
/// @return True if str starts with fact
SL_header bool SL_strstart(const char *str, const char *fact);
/// @brief Check wether a string ends with another
/// @param str String in which to search
/// @param fact Substring to find
/// @return True if str ends with fact
SL_header bool SL_strend(const char *str, const char *fact);

/// @brief Read the entirety of a file and dump it into a string
/// @param path Path to the file
/// @param size Pointer in which to store the size read (may be NULL)
/// @return The file data as a NULL-terminated string
SL_header char *SL_readEntireFile(const char *path, usize *size);
/// @brief Write the entirety of a file
/// @param path Path to the file
/// @param size Size of the data to write in bytes
/// @param data Data to write
/// @return Wether the process was a success
SL_header bool SL_writeEntireFile(const char *path, usize size, void *data);



/// TODO: Path utilities for extracting file extension, file name, folder hierarchy, stepping through ? 
// typedef struct sl_path
// {
// } sl_path;



typedef int sl_func_print(void *output_stream, const char *format, ...);                                                        /// @brief Generic function type (which can deal with either a str or a FILE)
typedef int sl_func_vprint(void *output_stream, const char *format, va_list list);                                              /// @brief Generic function type (which can deal with either a str or a FILE)
typedef struct sl_stream { union { FILE *file; struct sl_stream_str { char *ptr; int at; } *str; void *generic; }; bool is_str; } sl_stream;  /// @brief Stream structure. Abstracts the fundamental type for print-type functions
/// @brief Generic stream constructor
/// @param dst Either a `char *`, `FILE *` or another `sl_stream`
#define sl_stream_(dst) _Generic((dst),         \
    sl_stream: (dst),                           \
    FILE *: ((sl_stream) {                      \
        .file = *(void**)__SL_PTR(dst),         \
        .is_str = false                         \
    }),                                         \
    char *: ((sl_stream) {                      \
        .str = __SL_PTR((struct sl_stream_str){ \
            .ptr = *(void**)__SL_PTR(dst),      \
            .at = 0                             \
        }),                                     \
        .is_str = true                          \
    })                                          \
)
SL_header int SL_streamClose(sl_stream stream);

SL_header int __SL_streamPrintf(sl_stream stream, const char *fmt, ...);
/// @brief Generic printf
/// @note Equivalent to calls to either `fprintf` or `sprintf`
#define SL_gprintf(stream, fmt, ...) __SL_streamPrintf(sl_stream_(stream), fmt, ##__VA_ARGS__)

SL_header int __SL_streamVprintf(sl_stream stream, const char *fmt, va_list list);
/// @brief Generic vprintf
/// @note Equivalent to calls to either `vfprintf` or `vsprintf`
#define SL_vgprintf(stream, fmt, list) __SL_streamVprintf(sl_stream_(stream), fmt, list)

SL_header int __SL_gprintBin(sl_stream dst, usize size, void *data);
/// @brief Print a value's binary representation
/// @param dst Stream in which to print
/// @param val The value to print
#define SL_gprintBin(dst, val) (__SL_gprintBin(sl_stream_(dst), sizeof(val), __SL_PTR(val)))
/// @brief Print a value's binary representation to standard output
/// @param val The value to print
#define SL_printBin(val) SL_gprintBin(stdout, val)
    
SL_header int __SL_gprintHex(sl_stream dst, usize size, void *data);
/// @brief Print a value's hexadecimal representation
/// @param dst Stream in which to print
/// @param val The value to print
#define SL_gprintHex(dst, val) (__SL_gprintHex(sl_stream_(dst), sizeof(val), __SL_PTR(val)))
/// @brief Print a value's hexadecimal representation to standard output
/// @param val The value to print
#define SL_printHex(val) SL_gprintHex(stdout, val)



#define SL_PUT_TARGET __SL_FPUT_STREAM
#define SL_PUT_WRAPPER(...) NULL); do { __VA_ARGS__; } while (0); __SL_streamPrintf(SL_PUT_TARGET

#define SL_gput(dst, ...) do { sl_stream SL_PUT_TARGET = sl_stream_(dst); __SL_streamPrintf(SL_PUT_TARGET, ##__VA_ARGS__, NULL); } while (0)
#define SL_put(...) SL_gput(stdout, ##__VA_ARGS__)

#define SL_putBin(val) SL_PUT_WRAPPER(SL_gprintBin(SL_PUT_TARGET, val))
#define SL_putHex(val) SL_PUT_WRAPPER(SL_gprintHex(SL_PUT_TARGET, val))



#ifdef SL_STRIP_PREFIX
#   define  tmpf            SL_tmpf
#   define  strf            SL_strf
#   define  strtrsfrm       SL_strtrsfrm
#   define  strupper        SL_strupper
#   define  strlower        SL_strlower
#   define  strstart        SL_strstart
#   define  strend          SL_strend
#   define  readEntireFile  SL_readEntireFile
#   define  writeEntireFile SL_writeEntireFile
    typedef sl_stream       stream;
#   define  gprintf         SL_gprintf
#   define  vgprintf        SL_vgprintf
#   define  gprintBin       SL_gprintBin
#   define  printBin        SL_printBin
#   define  gprintHex       SL_gprintHex
#   define  printHex        SL_printHex
#   define  PUT_TARGET      SL_PUT_TARGET
#   define  PUT_WRAPPER     SL_PUT_WRAPPER
#   define  gput            SL_gput
#   define  put             SL_put
#   define  putBin          SL_putBin
#   define  putHex          SL_putHex
#endif



#ifdef SL_IMPLEMENTATION
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

SL_header char *SL_strtrsfrm(char *str, int (*func)(int))
{
    for (char *c = str; *c; (*c = func(*c)), ++c);
    return str;
}
SL_header char *SL_strupper(char *str)
{
    for (char *c = str; *c; (*c = toupper(*c)), ++c);
    return str;
}
SL_header char *SL_strlower(char *str)
{
    for (char *c = str; *c; (*c = tolower(*c))) ++c;
    return str;
}
SL_header bool SL_strstart(const char *str, const char *fact)
{
    while (*str && *fact && *str == *fact) ++fact, ++str;
    return *fact == '\0';
}
SL_header bool SL_strend(const char *str, const char *fact)
{
    const char *end = str + strlen(str) - strlen(fact);
    while (*end && *fact && *end == *fact) ++fact, ++end;
    return *fact == '\0';
}

SL_header char *SL_readEntireFile(const char *path, usize *size)
{
    FILE *f = fopen(path, "rb");
    if (!f) return __SL_ERROR(SL_ERROR_MISSING_VALUE), NULL;

    fseek(f, 0, SEEK_END);
    usize len = ftell(f);
    if (size) *size = len;
    fseek(f, 0, SEEK_SET);

    char *data = malloc(len + 1); // + '\0'
    if (!data) return __SL_ERROR(SL_ERROR_MEMORY), NULL;
    fread(data, 1, len, f);
    data[len] = '\0';

    fclose(f);
    return data;
}
SL_header bool SL_writeEntireFile(const char *path, usize size, void *data)
{
    FILE *f = fopen(path, "wb");
    if (!f) return __SL_ERROR(SL_ERROR_MISSING_VALUE), false;

    bool writtenAll = fwrite(data, size, 1, f) == size;

    fclose(f);
    return writtenAll;
}

SL_header int SL_streamClose(sl_stream stream)
{
    if (stream.is_str) return free(stream.str->ptr), 0;
    else return fclose(stream.file);
}
SL_header int __SL_streamVprintf(sl_stream stream, const char *fmt, va_list list) {
    if (!fmt) return 0;
    if (stream.is_str)
    {
        int ret = vsprintf(stream.str->ptr + stream.str->at, fmt, list);
        stream.str->at += ret;
        return ret;
    }
    else return vfprintf(stream.file, fmt, list);
}
SL_header int __SL_streamPrintf(sl_stream stream, const char *fmt, ...) {
    if (!fmt) return 0;
    va_list args;
    va_start(args, fmt);
    int ret = __SL_streamVprintf(stream, fmt, args);
    va_end(args);
    return ret;
}

SL_header int __SL_gprintBin(sl_stream dst, usize size, void *data)
{
    int ret = SL_gprintf(dst, "0b");
    for (usize i = 0; i < size; ++i) {
        u8 v = ((u8 *)data)[size - 1 - i];
        ret += SL_gprintf(dst, "%c%c%c%c%c%c%c%c%c",
            (v & 128) ? '1' : '0', (v & 64) ? '1' : '0', (v & 32) ? '1' : '0', (v & 16) ? '1' : '0',
            (v & 8)   ? '1' : '0', (v & 4)  ? '1' : '0', (v & 2)  ? '1' : '0', (v & 1)  ? '1' : '0', i + 1 < size ? '\'' : 0
        );
    }
    return ret;
}
SL_header int __SL_gprintHex(sl_stream dst, usize size, void *data)
{
    int ret = SL_gprintf(dst, "0x");
    for (usize i = 0; i < size; ++i) {
        u8 v = ((u8 *)data)[size - 1 - i];
        u8 h = (v >> 4) & 0x0F, l = v & 0x0F;
        ret += SL_gprintf(dst, "%c%c", (h > 9) ? ('A' + h - 10) : ('0' + h), (h > 9) ? ('A' + l - 10) : ('0' + l));
    }
    return ret;
}
#endif
#endif // _SL_IO_H_