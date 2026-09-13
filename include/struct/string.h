#ifndef _SL_STRING_H_
#define _SL_STRING_H_

/*
 *  STRING: Improvement on the base C strings for string analysis. String building would be done with `array(char)` structure.
 *  
 *  TODO:
 *  - Support every <string.h> function:
 *      - strcmp, strcasecmp
 *      - 
 *  - Trim left/right/both
 *  - Split (returns array of "string_slice")
 *  - Start, end factor matching
 * 
*/

#include "../base.h"
#include "array.h"
#include "../math/math.h"

typedef SL_slice(char) sl_string;
SL_DEF_ARRAY(sl_string);

#define SL_string_(cstr)        (string) {.data = cstr, .count = strlen(cstr)}
#define SL_stringc(static_cstr) (string) {.data = static_cstr, .count = sizeof(static_cstr) - 1}
#define SL_stringa(char_array)  SL_slicea(char, char_array)

#define SL_stringLen(str) ((str).count)

/// @brief String comparison
/// @param lhs Left string
/// @param rhs Right string
/// @return The lexicographic order between `lhs` and `rhs`
/// @note Equivalent of `strncmp`
SL_header int SL_stringCmp(sl_string lhs, sl_string rhs);
/// @brief Check if `fact` can be found at start of `str`
/// @param str The string to check
/// @param fact The string to find
/// @return Whether `fact` was found at start of `str`
SL_header bool SL_stringStart(sl_string str, sl_string fact);
/// @brief Check if `fact` can be found at end of `str`
/// @param str The string to check
/// @param fact The string to find
/// @return Whether `fact` was found at end of `str`
SL_header bool SL_stringEnd(sl_string str, sl_string fact);
/// @brief Check if `fact` can be found within `str`
/// @param str The string to check
/// @param fact The string to find
/// @return The index of the first occurence of `fact` in `str`, `-1` if not found
SL_header ssize SL_stringFind(sl_string str, sl_string fact);

/// @brief Remove whitespace characters at the start of the string
/// @param str The string to trim
/// @return The trimmed string
SL_header sl_string SL_stringTrimStart(sl_string str);
/// @brief Remove whitespace characters at the end of the string
/// @param str The string to trim
/// @return The trimmed string
SL_header sl_string SL_stringTrimEnd(sl_string str);
/// @brief Remove whitespace characters at the start and the end of the string
/// @param str The string to trim
/// @return The trimmed string
SL_header sl_string SL_stringTrim(sl_string str);

/// @brief Split string along `separator`
/// @param str The string to split
/// @param separator The separator to use
/// @param into An array into which the substrings will be stored
/// @return The number of separators encountered
/// @note Empty substrings are not returned
SL_header usize SL_stringSplit(sl_string str, sl_string separator, SL_array(sl_string) *into);
/// @brief Extract a substring from a string
/// @param str The string from which to extract
/// @param start The index of the first character to extract
/// @param count The number of characters to extract
/// @return The extracted substring
SL_header sl_string SL_stringSlice(sl_string str, usize start, usize count);

/// @brief Turn every lowercase character in `str` to uppercase
/// @param str The string to turn "upper"
/// @return The string
/// @note This function actively modifies the string
SL_header sl_string SL_stringUpper(sl_string str);
/// @brief Turn every uppercase character in `str` to lowercase
/// @param str The string to turn "lower"
/// @return The string
/// @note This function actively modifies the string
SL_header sl_string SL_stringLower(sl_string str);
/// @brief Turn first character of `str` to uppercase
/// @param str The string to turn capitalize
/// @return The string
/// @note This function actively modifies the string
SL_header sl_string SL_stringCapitalize(sl_string str);

#ifdef SL_STRIP_PREFIX
    typedef sl_string       string;
    SL_DEF_ALIAS(SL_array(sl_string), SL_array(string));
#   define  string_         SL_string_
#   define  stringc         SL_stringc
#   define  stringa         SL_stringa
#   define  stringLen       SL_stringLen
#   define  stringCmp       SL_stringCmp
#   define  stringStart     SL_stringStart
#   define  stringEnd       SL_stringEnd
#   define  stringFind      SL_stringFind
#   define  stringTrimStart SL_stringTrimStart
#   define  stringTrimEnd   SL_stringTrimEnd
#   define  stringTrim      SL_stringTrim
#   define  stringSplit     SL_stringSplit
#   define  stringSlice     SL_stringSlice
#   define  stringUpper     SL_stringUpper
#   define  stringLower     SL_stringLower
#   define  stringCapitalize SL_stringCapitalize
#   define  string_cmp      sl_string_cmp
#endif

#ifdef SL_IMPLEMENTATION
SL_header int SL_stringCmp(sl_string lhs, sl_string rhs)
{
    return strncmp(lhs.data, rhs.data, SL_u64min(lhs.count, rhs.count));
}
SL_header bool SL_stringStart(sl_string str, sl_string fact)
{
    if (str.count < fact.count) return false;
    if (str.data == fact.data) return str.count >= fact.count;

    const char *a = str.data, *b = fact.data;
    for (const char *max_a = str.data + fact.count; max_a > a; ++a, ++b) if (*a != *b) return false;
    return true;
}
SL_header bool SL_stringEnd(sl_string str, sl_string fact)
{
    if (str.count < fact.count) return false;

    const char *a = str.data + str.count - 1, *b = fact.data + fact.count - 1;
    for (const char *min_a = str.data; min_a <= a; --a, --b) if (*a != *b) return false;
    return true;
}
SL_header ssize SL_stringFind(sl_string str, sl_string fact)
{
    if (str.count < fact.count) return -1;

    const char *max_strc = str.data + str.count;
    for (const char *str_start = str.data; (usize)str.data < (usize)max_strc; ++str.data, --str.count) 
        if (SL_stringStart(str, fact)) return (ssize)str.data - (ssize)str_start;

    return -1;
}

SL_header sl_string SL_stringTrimStart(sl_string str)
{
    char *a = str.data;
    for (const char *max_a = str.data + str.count; max_a > a && isspace(*a); ++a);
    return (sl_string){.data = a, .count = str.count + (usize)a - (usize)str.data};
}
SL_header sl_string SL_stringTrimEnd(sl_string str)
{
    char *a = str.data + str.count - 1;
    for (const char *min_a = str.data; min_a <= a && isspace(*a); --a);
    return (sl_string){.data = str.data, .count = (usize)a - (usize)str.data};
}
SL_header sl_string SL_stringTrim(sl_string str)
{
    return SL_stringTrimStart(SL_stringTrimEnd(str));
}

SL_header usize SL_stringSplit(sl_string str, sl_string separator, SL_array(sl_string) *into)
{
    usize separator_count = 0;
    char *str_start = str.data;
    const char *max_strc = str.data + str.count;
    while ((usize)str.data < (usize)max_strc)
    {
        if (separator_count += SL_stringStart(str, separator))
        {
            if ((usize)str_start < (usize)str.data) SL_arrayAdd(*into, ((sl_string){.data = str_start, .count = (usize)str.data - (usize)str_start}));
            str.data  += separator.count;
            str.count += separator.count;
            str_start  = str.data;
        }
        else ++str.data, --str.count;
    }
    if (str_start < max_strc) SL_arrayAdd(*into, ((sl_string){.data = str_start, .count = (usize)max_strc - (usize)str_start}));

    return separator_count;
}
SL_header sl_string SL_stringSlice(sl_string str, usize start, usize count)
{
    return (sl_string){.data = start > str.count ? NULL : str.data + start, .count = SL_i64min(start + count, str.count) - start};
}

SL_header sl_string SL_stringUpper(sl_string str)
{
    char *c = str.data;
    for (const char *max = c + str.count; c < max; ++c) *c = toupper(*c);
    return str;
}
SL_header sl_string SL_stringLower(sl_string str)
{
    char *c = str.data;
    for (const char *max = c + str.count; c < max; ++c) *c = tolower(*c);
    return str;
}
SL_header sl_string SL_stringCapitalize(sl_string str)
{
    *str.data = toupper(*str.data);
    return str;
}
#endif

#ifndef SL_NO_DEFINES
    __SL_DEF_CMP_FUNC(sl_string, lhs, rhs, SL_header, SL_implement) SL_implement({ return SL_stringCmp(*lhs, *rhs); });
#endif

#endif // _SL_STRING_H_