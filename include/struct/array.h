#ifndef _SL_ARRAY_H_
#define _SL_ARRAY_H_

/*
 *  ARRAY: generic dynamic array in C. 
 *  
 *  TODO:
 *  - Find a way to declare array of pointer types
 * 
*/

#include "../base.h"
#include "allocator.h"



/// @brief Define the fields to make a struct compatible with every "array" function
/// @param type type to be stored
#define SL_SLICE_FIELDS(type) type *data; usize count
#define SL_ARRAY_FIELDS(type) SL_SLICE_FIELDS(type); usize capa; sl_allocator *alloc
#define __SL_XPD_ARRAY(arr, ...) (void *) __VA_ARGS__ (arr).data, __VA_ARGS__ (arr).count, __VA_ARGS__ (arr).capa, (arr).alloc, sizeof(*(arr).data)
/// @brief Define a new type of dynamic array
/// @param type type to be stored
/// @return The types "{type}_a" and "{type}_s" for dynamic array and slice respectively
/// @note You can refer to the array using "array(type)" or directly by adding "_a" at the end of the type
#define SL_DEF_ARRAY(type) typedef struct SL_slice(type) { SL_SLICE_FIELDS(type); } SL_slice(type); typedef struct SL_array(type) { SL_ARRAY_FIELDS(type); } SL_array(type)

#define SL_array(type) CAT(type, _array)
#define SL_slice(type) CAT(type, _slice)
#define SL_slice_(type, count_, data_)     ((SL_slice(type)){.data = data_, .count = count_})
#define SL_slicea(type, array, start, end) ((SL_slice(type)){.data = (array).data + (start), .count = 1 + (end) - (start)})
#define SL_slicev(type, ...)               ((SL_slice(type)){.data = (type[]){__VA_ARGS__}, .count = (sizeof((type[]){__VA_ARGS__}) / sizeof(type))})

SL_DEF_ARRAY(void);



/// @brief Create an array with initial capacity in a specified allocator
/// @param type Type to be stored
/// @param capa_ Initial capacity
/// @param allocator_ Allocator
/// @return The newly created array
#define SL_arrayCreateA(type, capa_, allocator_) ((SL_array(type)){.data = (capa_) <= 0 ? NULL : SL_aalloc(allocator_, sizeof(type) * (capa_)), .capa = (capa_) <= 0 ? 0 : (capa_), .count = 0, .alloc = allocator_})
/// @brief Create an array with initial capacity
/// @param type Type to be stored
/// @param capa_ Initial capacity
/// @return The newly created array
#define SL_arrayCreate(type, capa_) SL_arrayCreateA(type, capa_, std_allocator)
/// @brief Free array's resources and reset its value
/// @param array Array
#define SL_arrayDestroy(array) (SL_afree((array).alloc, (array).data), memset(&array, 0, sizeof(array)), array)
/// @brief Clone array
/// @param array Array
/// @return A clone of array
/// @note Use this to avoid having shared "data" on multiple arrays
#define SL_arrayClone(array) ((typeof(array)){.data = SL_aclone((array).alloc, (array).data, sizeof(*(array).data) * (array).capa), .capa = (array).capa, .count = (array).count})
/// @brief Clone array in a specified allocator
/// @param array Array
/// @param allocator Allocator
/// @return A clone of array
/// @note Use this to avoid having shared "data" on multiple arrays
#define SL_arrayCloneA(array, allocator) ((typeof(array)){.data = SL_aclone(allocator, (array).data, sizeof(*(array).data) * (array).capa), .capa = (array).capa, .count = (array).count})

/// @brief Wrap a C array into an SL array
/// @param carray C array
/// @param span Number of values in the C array
/// @warning Opperations like "arrayAdd" may try to reallocate the array, so be careful with static memory and outside references.
#define SL_arrayWrap(type, span, carray) ((SL_array(type)){.data = carray, .capa = span, .count = span, .alloc = std_allocator})
/// @brief Wrap a C array into an SL array with a specified allocator
/// @param carray C array
/// @param span Number of values in the C array
/// @param allocator_ Allocator
/// @warning Opperations like "arrayAdd" may try to reallocate the array, so be careful with static memory and outside references.
#define SL_arrayWrapA(type, span, carray, allocator_) ((SL_array(type)){.data = carray, .capa = span, .count = span, .alloc = allocator_})
/// @brief Wrap a set of values into an SL array
/// @param ... Values
/// @warning Opperations like "arrayAdd" may try to reallocate the array, so be careful with static memory and outside references.
#define SL_arrayWrapVar(type, ...) ((SL_array(type)){.data = (type[]){__VA_ARGS__}, .capa = sizeof((type[]){__VA_ARGS__}) / sizeof(type), .count = sizeof((type[]){__VA_ARGS__}) / sizeof(type), .alloc = std_allocator})

#define SL_arrayFrom(type, span, carray)                 SL_arrayClone(SL_arrayWrap(type, span, carray))
#define SL_arrayFromA(type, span, carray, allocator_)    SL_arrayClone(SL_arrayWrapA(type, span, carray, allocator_))
#define SL_arrayFromVar(type, ...)                       SL_arrayClone(SL_arrayWrapVar(type, ##__VA_ARGS__))
#define SL_arrayFromVarA(type, allocator_, ...)          SL_arrayCloneA(SL_arrayWrapVar(type, ##__VA_ARGS__), allocator_)

/// @brief Get first value in array
/// @param array Array
/// @return A pointer to the value if found, NULL otherwise
#define SL_arrayFirst(array) ((array).count ? (array).data : NULL)
/// @brief Get last value in array
/// @param array Array
/// @return A pointer to the value if found, NULL otherwise
#define SL_arrayLast(array) ((array).count ? (array).data + (array).count - 1 : NULL)
SL_header void *__SL_arrayAt(void *data, usize count, usize elemSize, ssize index);
/// @brief Get value at index in array
/// @param array Array
/// @param index Index into the array. If negative, equivalent to ```SL_arrayAt(array, array.count + index)```
/// @return A pointer to the value if found, NULL otherwise
#define SL_arrayAt(array, index) ((typeof((array).data))__SL_arrayAt((array).data, (array).count, sizeof(*(array).data), index))



SL_header void *__SL_arrayInsertRange(void **array_data, usize *array_count, usize *array_capa, sl_allocator *alloc, usize elemSize, usize index, usize span, void *values);
/// @brief Insert range of values at index in array
/// @param array Array
/// @param index Index of first value into the array
/// @param span Number of values to insert
/// @param values Values to insert
/// @return Pointer to the first inserted value
/// @warning Will not insert if index is out of array bounds
/// @note Error status is recorded in SL_ERROR
#define SL_arrayInsertRange(array, index, span, values) ((typeof((array).data))__SL_arrayInsertRange(__SL_XPD_ARRAY(array, &), index, span, (void *)(typeof((array).data))values))
/// @brief Insert value at index in array
/// @param array Array
/// @param index Index into the array
/// @param value Value to insert
/// @return Pointer to the inserted value
/// @warning Will not insert if index is out of array bounds
/// @note Error status is recorded in SL_ERROR
#define SL_arrayInsert(array, index, value) SL_arrayInsertRange(array, index, 1, __SL_PTR(value))
/// @brief Insert range of values at index in array
/// @param array Array
/// @param index Index of first value into the array
/// @param span Number of values to insert
/// @param ... Values to insert
/// @return Pointer to the first inserted value
/// @warning Will not insert if index is out of array bounds
/// @note Error status is recorded in SL_ERROR
#define SL_arrayInsertVar(array, index, ...) ((typeof((array).data))__SL_arrayInsertRange(__SL_XPD_ARRAY(array, &), index, sizeof((typeof(*(array).data)[]){__VA_ARGS__}) / sizeof(*(array).data), (typeof(*(array).data)[]){__VA_ARGS__})) 



/// @brief Add range of values to end of array
/// @param array Array
/// @param span Number of values to insert
/// @param values Values to insert
/// @return Pointer to the first inserted value
/// @note Error status is recorded in SL_ERROR
#define SL_arrayAddRange(array, span, values) SL_arrayInsertRange(array, (array).count, span, values)
/// @brief Add range of values to end of array
/// @param array Array
/// @param ... Values to insert
/// @return Pointer to the first inserted value
/// @note Error status is recorded in SL_ERROR
#define SL_arrayAddVar(array, ...) SL_arrayInsertVar(array, (array).count, __VA_ARGS__)
/// @brief Add value to end of array
/// @param array Array
/// @param value Value to add
/// @return Pointer to the inserted value
/// @note Error status is recorded in SL_ERROR
#define SL_arrayAdd(array, value) SL_arrayAddRange(array, 1, (void *)__SL_PTR(value))
/// @brief Concatenate two arrays
/// @param a Left array
/// @param b Right array
/// @return Pointer to the first inserted value
/// @note Result is stored in a
/// @note Error status is recorded in SL_ERROR
#define SL_arrayCat(a, b) SL_arrayAddRange(a, (b).count, (b).data)

#define SL_arrayAddf(array, fmt, ...) (__SL_arrayInsertRange(__SL_XPD_ARRAY(array, &), (array).count, strlen(tmpf(fmt, ##__VA_ARGS__)), tmpf(NULL)))

SL_header bool __SL_arrayRemoveRange(void *array_data, usize *array_count, usize elemSize, usize index, usize span);
/// @brief Remove values from `index` to `index + span` from array
/// @param index Index of first value to remove
/// @param span Number of values to remove
/// @return Wether the removal was successful
/// @warning Will not remove if full span is outside of array bounds
/// @note Error status is recorded in SL_ERROR
#define SL_arrayRemoveRange(array, index, span) (__SL_arrayRemoveRange((void *)(array).data, &(array).count, sizeof(*(array).data), index, span))
/// @brief Remove value at index from array
/// @param index Index of the value to remove
/// @return Wether the removal was successful
/// @note Error status is recorded in SL_ERROR
#define SL_arrayRemove(array, index) SL_arrayRemoveRange(array, index, 1)

SL_header bool __SL_arrayRemoveUnordered(void *array_data, usize *array_count, usize elemSize, usize index);
/// @brief Remove value at index from array without regards for order
/// @param index Index of the value to remove
/// @return Wether the removal was successful
/// @warning The order of the elements inside of this array will not be preserved after this operation
/// @note Error status is recorded in SL_ERROR
#define SL_arrayRemoveUnordered(array, index) (__SL_arrayRemoveUnordered((array).data, &(array).count, sizeof(*(array).data), index))
/// @brief Take out last value of array
/// @param array Array
/// @return Pointer to popped value
/// @warning The pointer to the popped value is only garantied to be valid when this function is called
/// @note Error status is recorded in SL_ERROR
#define SL_arrayPop(array) ((array).count ? (array).data + --(array).count : __SL_ERROR(SL_ERR_OUT_OF_BOUNDS), NULL)



/// @brief Sort array using stdlib's "qsort"
/// @param array Array
/// @param condition Function which, given two consecutive values of the array, compares them and returns a positive int if their order is correct and a negative int if they should swap
/// @note Some basic qsort functions are provided. They are named "{type}_cmp" and "{type}_cmp_inv".
#define SL_arraySort(array, condition) (qsort((array).data, (array).count, sizeof(*(array).data), (int(*)(const void *, const void *))condition))

SL_header void __SL_arrayFill(void *array_data, usize array_count, usize elemSize, void *elem);
#define SL_arrayFill(array, value) __SL_arrayFill((array).data, (array).count, sizeof(*(array).data), __SL_PTR_T(typeof(*(array).data), value)), array

SL_header bool __SL_arraySetCapacity(void **array_data, usize *array_count, usize *array_capa, sl_allocator *alloc, usize elemSize, usize new_capa);
#define SL_arrayReserve(array, new_capacity) (__SL_arraySetCapacity(__SL_XPD_ARRAY(array, &), new_capacity))

/// @brief Print array to a stream with user defined formatting
/// @param array Array
/// @param dst Destination in which to print. Uses generic "gprintf" function to differenciate between printing to a string or a file
/// @param fmt The format of the data to print
/// @param varname The name of the iterator
/// @param ... How to expand the value stored to fit the format specified with 'fmt'
#define SL_arrayPrintf_full(array, dst, fmt, varname, ...) do { \
    if (!(array).data) SL_gprintf(dst, "array[]"); \
    else { \
        SL_aforeach(varname, array) SL_gprintf(dst, SL_aindex(varname) == 0 ? "array["fmt : ", "fmt, ##__VA_ARGS__); \
        SL_gprintf(dst, "]"); \
    } \
} while (0)
/// @brief Print array to a stream with user defined formatting
/// @param array Array
/// @param dst Destination in which to print. Uses generic "gprintf" function to differenciate between printing to a string or a file
/// @param fmt The format of the data to print
/// @param ... How to expand the value stored to fit the format specified with 'fmt'
#define SL_arrayPrintf(array, dst, fmt) SL_arrayPrintf_full(array, dst, fmt, __SL_VARNAME__, *__SL_VARNAME__)



/// @brief Iterate over every item into an array
/// @param varname The name of the iterator
/// @param array Array
/// @note "varname" is a pointer to a value in array at each iteration.
#define SL_aforeach(varname, array) for (typeof(*(array).data) *varname = (array).data, *__##varname##_MIN__ = (array).data, *__##varname##_MAX__ = (array).data + (array).count; varname < __##varname##_MAX__; ++varname)
/// @brief Index of element in array
/// @warning This is supposed to be used inside of the "aforeach" scope, no bound checks are done on this value
/// @returns The index of the element in the currently iterated array
#define SL_aindex(varname) (((usize)(varname) - (usize)(__##varname##_MIN__)) / sizeof(*varname))
#define SL_aindex_in(ptr, array) (((usize)(ptr) - (usize)((array).data)) / sizeof(*(array).data))

#define SL_anext(array, ptr) ((ptr) = ((ptr) >= (array).data + (array).count ? NULL : (ptr) + 1))



#ifdef SL_STRIP_PREFIX
#   define ARRAY_FIELDS         SL_ARRAY_FIELDS
#   define DEF_ARRAY            SL_DEF_ARRAY
#   define ARRAY_XPD            SL_ARRAY_XPD
#   define array                SL_array
#   define slice                SL_slice
#   define slice_               SL_slice_
#   define slicea               SL_slicea
#   define slicev               SL_slicev
#   define arrayCreate          SL_arrayCreate
#   define arrayCreateA         SL_arrayCreateA
#   define arrayDestroy         SL_arrayDestroy
#   define arrayClone           SL_arrayClone
#   define arrayCloneA          SL_arrayCloneA
#   define arrayWrap            SL_arrayWrap
#   define arrayWrapVar         SL_arrayWrapVar
#   define arrayFrom            SL_arrayFrom
#   define arrayFromA           SL_arrayFromA
#   define arrayFromVar         SL_arrayFromVar
#   define arrayFromVarA        SL_arrayFromVarA
#   define arrayFirst           SL_arrayFirst
#   define arrayLast            SL_arrayLast
#   define arrayAt              SL_arrayAt
#   define arrayCheckResize     SL_arrayCheckResize
#   define arrayInsertRange     SL_arrayInsertRange
#   define arrayInsert          SL_arrayInsert
#   define arrayInsertVar       SL_arrayInsertVar
#   define arrayAddRange        SL_arrayAddRange
#   define arrayAdd             SL_arrayAdd
#   define arrayAddVar          SL_arrayAddVar
#   define arrayCat             SL_arrayCat
#   define arrayRemoveRange     SL_arrayRemoveRange
#   define arrayRemove          SL_arrayRemove
#   define arrayRemoveUnordered SL_arrayRemoveUnordered
#   define arrayPop             SL_arrayPop
#   define arrayQSort           SL_arraySort
#   define arrayFill            SL_arrayFill
#   define arrayReserve         SL_arrayReserve
#   define arrayPrintf_full     SL_arrayPrintf_full
#   define arrayPrintf          SL_arrayPrintf
#   define aforeach             SL_aforeach
#   define aindex               SL_aindex
#   define aindex_in            SL_aindex_in
#endif

#ifdef SL_IMPLEMENTATION
SL_header void *__SL_arrayAt(void *data, usize count, usize elemSize, ssize index)
{
    if (index < 0) index = count + index;
    return index >= 0 && index < count ? data + index * elemSize : NULL;
}
SL_header bool __SL_arraySetCapacity(void **array_data, usize *array_count, usize *array_capa, sl_allocator *alloc, usize elemSize, usize new_capa)
{
    if (new_capa <= *array_capa) return true;

    if (*array_data == NULL) {
        *array_data = SL_aalloc(alloc, elemSize * (*array_capa = SL_alignPow2(new_capa)));
        return *array_data ? true : (__SL_ERROR(SL_ERR_MEMORY), false);
    }
    
    usize old_capa = *array_capa;
    do *array_capa <<= 1; while (new_capa > *array_capa);
    
    void *newData = SL_aalloc(alloc, elemSize * *array_capa);
    if (!newData) return __SL_ERROR(SL_ERR_MEMORY), false;
    memcpy(newData, *array_data, elemSize * old_capa);
    SL_afree(alloc, *array_data);
    *array_data = newData;

    // *array_data = SL_arealloc(alloc, *array_data, *array_capa);
    // if (!*array_data) return __SL_ERROR(SL_ERR_MEMORY), false;

    return true;
}

SL_header void *__SL_arrayInsertRange(void **array_data, usize *array_count, usize *array_capa, sl_allocator *alloc, usize elemSize, usize index, usize span, void *values)
{
    usize prev_count = *array_count;
    if (index > prev_count) return __SL_ERROR(SL_ERR_OUT_OF_BOUNDS), NULL;
    if (!__SL_arraySetCapacity(array_data, array_count, array_capa, alloc, elemSize, prev_count + span)) return __SL_ERROR(SL_ERR_MEMORY), NULL;
    
    void *firstElem = *array_data + elemSize * index;
    if (index < prev_count) memmove(firstElem + elemSize * span, firstElem, elemSize * (prev_count - index));

    if (values) memcpy(firstElem, values, elemSize * span);
    
    *array_count += span;
    return firstElem;
}
SL_header bool __SL_arrayRemoveRange(void *array_data, usize *array_count, usize elemSize, usize index, usize span)
{
    if (index + span > *array_count || span == 0) return __SL_ERROR(SL_ERR_OUT_OF_BOUNDS), false;
    memmove(array_data + elemSize * index, array_data + elemSize * (index + span), elemSize * ((*array_count -= span) - index + 1));
    return true;
}
SL_header bool __SL_arrayRemoveUnordered(void *array_data, usize *array_count, usize elemSize, usize index)
{
    if (*array_count <= index || index < 0) return __SL_ERROR(SL_ERR_OUT_OF_BOUNDS), false;
    memcpy (array_data + elemSize * index, array_data + elemSize * --*array_count, elemSize);
    return true;
}
SL_header void __SL_arrayFill(void *array_data, usize array_count, usize elemSize, void *elem)
{
    for (usize max = (usize)array_data + elemSize * array_count; (usize)array_data < max; array_data += elemSize) memcpy(array_data, elem, elemSize);
}
#endif



#ifndef SL_NO_DEFINES
    SL_DEF_ARRAY(bool);
    SL_DEF_ARRAY(int);    SL_DEF_ARRAY(uint);  SL_DEF_ARRAY(usize);  SL_DEF_ARRAY(ssize);
    SL_DEF_ARRAY(i8);     SL_DEF_ARRAY(i16);   SL_DEF_ARRAY(i32);    SL_DEF_ARRAY(i64);
    SL_DEF_ARRAY(u8);     SL_DEF_ARRAY(u16);   SL_DEF_ARRAY(u32);    SL_DEF_ARRAY(u64);
    SL_DEF_ARRAY(f16);    SL_DEF_ARRAY(f32);   SL_DEF_ARRAY(f64);    SL_DEF_ARRAY(f128);
    SL_DEF_ARRAY(SL_ptr(char));

    SL_DEF_ALIAS(SL_array(f32), SL_array(float));                       SL_DEF_ALIAS(SL_slice(f32), SL_slice(float)); 
    SL_DEF_ALIAS(SL_array(f64), SL_array(double));                      SL_DEF_ALIAS(SL_slice(f64), SL_slice(double));

    SL_DEF_ALIAS(SL_array(u8), SL_array(char8), SL_array(char));        SL_DEF_ALIAS(SL_slice(u8), SL_slice(char8), SL_slice(char));
    SL_DEF_ALIAS(SL_array(u16), SL_array(char16), SL_array(wchar_t));   SL_DEF_ALIAS(SL_slice(u16), SL_slice(char16), SL_slice(wchar_t));
    SL_DEF_ALIAS(SL_array(u32), SL_array(char32));                      SL_DEF_ALIAS(SL_slice(u32), SL_slice(char32));

    SL_DEF_ARRAY(void_p);
#endif
#endif // _SL_ARRAY_H_