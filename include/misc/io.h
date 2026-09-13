#ifndef _SL_IO_H_
#define _SL_IO_H_

/*
 *  IO: Utilities for io. 
 *  
 *  TODO:
 *  - Give access to the va_list to the custom formating functions to allow passing structs by value
 *  - Use "length" and "precision" and other base formating arguments in custom print
 * 
*/

#include "../base.h"

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



// typedef struct sl_path
// {
// } sl_path;



typedef int sl_func_print(void *output_stream, const char *format, ...);                                                        /// @brief Generic functions type (which can deal with either a string or a FILE)
typedef int sl_func_vprint(void *output_stream, const char *format, va_list list);                                              /// @brief Generic functions type (which can deal with either a string or a FILE)
typedef struct sl_stream { union { FILE *file; char *string; void *generic; }; bool is_str; } sl_stream;                        /// @brief Stream structure. Abstracts the funcdamental type for print-type functions
#define sl_stream_(dst) _Generic((dst), sl_stream: (dst), default: ((sl_stream){.file = (dst), .is_str = _Generic((dst), FILE *: false, default: true)})) /// @brief Generic stream constructor /// @param dst Either a `char *`, `FILE *` or another `sl_stream`

SL_header int __SL_stream_vprintf(sl_stream stream, const char *fmt, va_list list);
SL_header int __SL_stream_printf(sl_stream stream, const char *fmt, ...);
/// @brief Generic printf
/// @note Equivalent to calls to either `fprintf` or `sprintf`
#define SL_gprintf(stream, fmt, ...) _Generic((stream), \
    sl_stream: (__SL_stream_printf),                    \
    FILE *:    (fprintf),                               \
    default:   (sprintf)                                \
)(stream, fmt, ##__VA_ARGS__)

/// @brief Generic vprintf
/// @note Equivalent to calls to either `vfprintf` or `vsprintf`
#define SL_vgprintf(stream, fmt, list)  _Generic((stream),                              \
    sl_stream: ((stream).is_str ? (sl_func_print*)vsprintf : (sl_func_print*)vfprintf), \
    FILE *:    ((sl_func_print*)vfprintf),                                              \
    default:   ((sl_func_print*)vsprintf)                                               \
)((stream).generic, fmt, list)

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



#ifdef SL_STRIP_PREFIX
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
#   define  gprintBin       SL_printBin
#   define  printBin        SL_printBin
#   define  gprintHex       SL_gprintHex
#   define  printHex        SL_printHex
#endif



#ifdef SL_IMPLEMENTATION
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
    if (!f) return NULL;

    fseek(f, 0, SEEK_END);
    usize len = ftell(f);
    if (size) *size = len;
    fseek(f, 0, SEEK_SET);

    char *data = malloc(len + 1); // + '\0'
    if (!data) return NULL;
    fread(data, 1, len, f);
    data[len] = '\0';

    fclose(f);
    return data;
}
SL_header bool SL_writeEntireFile(const char *path, usize size, void *data)
{
    FILE *f = fopen(path, "wb");
    if (!f) return false;

    bool writtenAll = fwrite(data, size, 1, f) == size;

    fclose(f);
    return writtenAll;
}

SL_header int __SL_stream_vprintf(sl_stream stream, const char *fmt, va_list list) {
    return (stream.is_str ? (sl_func_vprint *)vsprintf : (sl_func_vprint *)vfprintf)(stream.generic, fmt, list);
}
SL_header int __SL_stream_printf(sl_stream stream, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    int ret = __SL_stream_vprintf(stream, fmt, args);
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