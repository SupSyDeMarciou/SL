#ifndef _SL_ARENA_H_
#define _SL_ARENA_H_

/*
 *  ARENA: Arena allocator implementation
 *  
 *  TODO:
 *  - Better Arena (to be less dumb)
 * 
*/

#include "allocator.h"
#include "list.h"

typedef struct sl_arena {
    sl_allocator description;

    SL_list(void_p) buffers;
    void *currentPage;
    void *current;
    usize pageSize;
} sl_arena;

SL_header void *SL_arenaAlloc(sl_allocator *a_, usize size);
SL_header void *SL_arenaZalloc(sl_allocator *a_, usize size);
SL_header void *SL_arenaRealloc(sl_allocator *a_, void *memory, usize size);
SL_header void SL_arenaFree(sl_allocator *a_, void *memory);
SL_header void *SL_arenaClone(sl_allocator *a_, void *memory, usize size);

/// @brief Create an areana allocator
/// @param pageSize Capacity of each page
/// @return The newly created arena allocator
SL_header sl_arena SL_arenaCreate(usize pageSize);
/// @brief Free allocator's resources
/// @param arena Arena
SL_header void SL_arenaDestroy(sl_arena arena);



#ifdef SL_STRIP_PREFIX
    typedef sl_arena        arena;
#   define arenaCreate      SL_arenaCreate
#   define arenaDestroy     SL_arenaDestroy
#endif


#ifdef SL_IMPLEMENTATION
SL_header void *SL_arenaAlloc(sl_allocator *a_, usize size)
{
    sl_arena *a = (sl_arena*)a_;
    if ((usize)a->current - (usize)a->currentPage + size > a->pageSize) a->currentPage = a->current = *(void**)SL_listAddEnd(a->buffers, malloc(a->pageSize));

    void *ret = a->current;
    a->current += size;
    return ret;
}
SL_header void *SL_arenaZalloc(sl_allocator *a_, usize size)
{
    sl_arena *a = (sl_arena*)a_; 
    if ((usize)a->current - (usize)a->currentPage + size > a->pageSize) a->currentPage = a->current = *(void**)SL_listAddEnd(a->buffers, malloc(a->pageSize));

    void *ret = a->current;
    a->current += size;
    memset(ret, 0, size);
    return ret;
}
SL_header void *SL_arenaRealloc(sl_allocator *a_, void *memory, usize size)
{
    SL_terminate(-1, "[UNIMPLEMENTED]");
}
SL_header void SL_arenaFree(sl_allocator *a_, void *memory)
{
    SL_terminate(-1, "[UNIMPLEMENTED]");
}
SL_header void *SL_arenaClone(sl_allocator *a_, void *memory, usize size)
{
    void *ret = SL_arenaAlloc(a_, size);
    return ret ? memcpy(ret, memory, size) : NULL;
}

SL_header sl_arena SL_arenaCreate(usize pageSize)
{
    sl_arena ret = {
        .description = SL_allocator_(SL_arenaAlloc, SL_arenaZalloc, SL_arenaRealloc, SL_arenaFree, SL_arenaClone),
        .buffers = {0}, .currentPage = NULL, .current = NULL, .pageSize = pageSize
    };
    ret.currentPage = ret.current = *(void**)SL_listAddEnd(ret.buffers, malloc(pageSize));
    return ret;
}
/// @brief Free allocator's resources
/// @param arena Arena
SL_header void SL_arenaDestroy(sl_arena arena)
{
    SL_lforeach(map, arena.buffers) free(*map);
    SL_listClear(arena.buffers);
}
#endif
#endif // _SL_ARENA_H_