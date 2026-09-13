#ifndef _SL_ALLOCATOR_H_
#define _SL_ALLOCATOR_H_

/*
 *  ALLOCATOR: allocator common ground for SL. It is used by many types such as array or list.  
 *  
 *  TODO:
 *  - Better Arena (to be less dumb)
 *  - Other kinds of allocators
 * 
*/

#include "../base.h"

typedef struct sl_allocator sl_allocator;
#define std_allocator ((sl_allocator *)NULL)

typedef void *sl_func_alloc    (sl_allocator *alloc, usize size);                               /// @brief Memory allocate prototype
typedef void *sl_func_zalloc   (sl_allocator *alloc, usize size);                               /// @brief Memory zero allocate prototype
typedef void *sl_func_realloc  (sl_allocator *alloc, void *memory, usize size);                 /// @brief Memory reallocate prototype
typedef void  sl_func_free     (sl_allocator *alloc, void *memory);                             /// @brief Memory free prototype
typedef void *sl_func_clone    (sl_allocator *alloc, void *memory, usize size);                 /// @brief Memory clone prototype

#define SL_aalloc(allocator, size)             (allocator == std_allocator ? malloc(size)        : (allocator)->alloc(allocator, size))              /// @brief Allocate memory with allocator
#define SL_azalloc(allocator, size)            (allocator == std_allocator ? calloc(1, size)     : (allocator)->zalloc(allocator, size))             /// @brief Allocate zeroed memory with allocator
#define SL_arealloc(allocator, ptr, size)      (allocator == std_allocator ? realloc(ptr, size)  : (allocator)->realloc(allocator, ptr, size))       /// @brief Reallocate memory with allocator
#define SL_afree(allocator, ptr)               (allocator == std_allocator ? free(ptr)           : (allocator)->free(allocator, ptr))                /// @brief Free memory with allocator
#define SL_aclone(allocator, src, size)        (allocator == std_allocator ? memclone(src, size) : (allocator)->clone(allocator, src, size))         /// @brief Clone memory with allocator    

struct sl_allocator {
    sl_func_alloc      *alloc;
    sl_func_zalloc     *zalloc;
    sl_func_realloc    *realloc;
    sl_func_free       *free;
    sl_func_clone      *clone;
};
/// @brief Create a new memory allocated
/// @param alloc Memory allocate function
/// @param zalloc Memory zero allocate function
/// @param realloc Memory reallocate function
/// @param free Memory free function
/// @param copy Memory copy function
/// @param move Memory move function
/// @param clone Memory clone function
/// @return The newly created allocator
#define SL_allocator_(alloc_, zalloc_, realloc_, free_, clone_) ((sl_allocator) { .alloc = alloc_, .zalloc = zalloc_, .realloc = realloc_, .free = free_, .clone = clone_})


#ifdef SL_STRIP_PREFIX
#   define  aalloc           SL_aalloc
#   define  azalloc          SL_azalloc
#   define  arealloc         SL_arealloc
#   define  afree            SL_afree
#   define  aclone           SL_aclone
    typedef sl_allocator     allocator;
#   define  allocator_       SL_allocator_
#endif

#endif // _SL_ALLOCATOR_H_