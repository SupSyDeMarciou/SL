#ifndef _SL_LIST_H_
#define _SL_LIST_H_

/*
 *  LIST: generic chained lists in C. 
 *  
 *  TODO:
 *  - Add variants with ranges and other chained lists
 * 
*/

#include <SL/base.h>
#include <SL/struct/allocator.h>
#include <SL/misc/io.h>



/// @brief Define the fields to make a struct compatible with every "list" function
/// @param type type to be stored
/// @param node_name name of the "node" structure holding the actual data
#define SL_LIST_FIELDS(type, node_name) struct node_name { struct node_name *next; type data; } *first, *last; usize count; sl_allocator *alloc
/// @brief Define the fields to make a struct compatible with every "dlist" function
/// @param type type to be stored
/// @param node_name name of the "node" structure holding the actual data
#define SL_DLIST_FIELDS(type, node_name) struct node_name { struct node_name *next, *prev; type data; } *first, *last; usize count; sl_allocator *alloc

/// @brief Define a new type of chained list
/// @param type type to be stored
/// @return Defines linked list "{type}_list" and double linked list "{type}_dlist", as well as associated "node" types
/// @note You can refer to the list using "list(type)" or directly by adding "_list" at the end of the type
#define SL_DEF_LIST(type) \
    typedef struct CAT(type, _list_node)  { struct CAT(type, _list_node)  *next;        type data; } CAT(type, _list_node);  typedef struct SL_list(type)  { CAT(type, _list_node)  *first, *last; usize count; sl_allocator *alloc; } SL_list(type); \
    typedef struct CAT(type, _dlist_node) { struct CAT(type, _dlist_node) *next, *prev; type data; } CAT(type, _dlist_node); typedef struct SL_dlist(type) { CAT(type, _dlist_node) *first, *last; usize count; sl_allocator *alloc; } SL_dlist(type)

#define SL_list(type)  CAT(type, _list)
#define SL_dlist(type) CAT(type, _dlist)



typedef struct __list_gen_node __list_gen_node;                                               //
struct __list_gen_node { __list_gen_node *next; void *data; };                                // For generic functions like "listNodeAt"

typedef struct __dlist_gen_node __dlist_gen_node;                                             //
struct __dlist_gen_node { __dlist_gen_node *next, *prev; void *data; };                       // For generic functions like "dlistNodeAt"

#define __SL_XPD_LIST(list, ...) ((void *)__VA_ARGS__(list).first), ((void *)__VA_ARGS__(list).last), __VA_ARGS__(list).count, (list).alloc
#define __SL_IS_DLIST(list)      (offsetof(typeof(*(list).first), data) == offsetof(__dlist_gen_node, data))



/// @brief Create an empty list in a specified allocator
/// @param type Type to be stored
/// @param allocator_ Allocator
/// @return The newly created list
#define SL_listCreateA(type, allocator_)  (SL_list(type){.alloc = allocator_})
/// @brief Create an empty list in a specified allocator
/// @param type Type to be stored
/// @param allocator_ Allocator
/// @return The newly created list
#define SL_dlistCreateA(type, allocator_) (SL_dlist(type){.alloc = allocator_})
/// @brief Free list's resources and reset its value
/// @param list List
#define SL_listClear(list) do { \
    while ((list).first) { \
        (list).last = (list).first->next; \
        SL_afree((list).alloc, (list).first); \
        (list).first = (list).last; \
    } \
    (list).first = NULL; \
    (list).last = NULL; \
    (list).count = 0; \
} while (0)



/// @brief Get first value in list
/// @param list List
/// @return A pointer to the value if exists, NULL otherwise
/// @note Error status is recorded in SL_ERROR
#define SL_listFirst(list) ((typeof((list).first->data) *)((list).first ? &(list).first->data : (__SL_ERROR(SL_ERROR_OUT_OF_BOUNDS), NULL)))
/// @brief Get last value in list
/// @param list List
/// @return A pointer to the value if exists, NULL otherwise
/// @note Error status is recorded in SL_ERROR
#define SL_listLast(list)  ((typeof((list).first->data) *)((list).last ? &(list).last->data : (__SL_ERROR(SL_ERROR_OUT_OF_BOUNDS), NULL)))

SL_header void *__SL_listNodeAt (void *first, void *last, usize count, usize index);
SL_header void *__SL_dlistNodeAt(void *first, void *last, usize count, usize index);
SL_header void *__SL_listValueFromNode(void *node_ptr, bool is_dlist);
/// @brief Get value at index in list
/// @param list List
/// @param index Index into the list
/// @return A pointer to the value if found, NULL otherwise
/// @note Error status is recorded in SL_ERROR
#define SL_listAt(list, index) ((typeof((list).first->data)*)__SL_listValueFromNode((__SL_IS_DLIST(list) ? __SL_dlistNodeAt : __SL_listNodeAt)((void *)(list).first, (void *)(list).last, (list).count, index), __SL_IS_DLIST(list)))

SL_header void *__SL_listInsert (void **first, void **last, usize *count, sl_allocator *alloc, usize elemSize, usize index, void *value);
SL_header void *__SL_dlistInsert(void **first, void **last, usize *count, sl_allocator *alloc, usize elemSize, usize index, void *value);
/// @brief Insert value at index in list
/// @param list List
/// @param index Index into the list
/// @param value Value to insert
/// @return Pointer to the added value
/// @note Error status is recorded in SL_ERROR
#define SL_listInsert(list, _index, value) ((typeof((list).first->data) *)(__SL_IS_DLIST(list) ? __SL_dlistInsert : __SL_listInsert)(__SL_XPD_LIST(list, &), sizeof((list).first->data), _index, __SL_PTR_T(typeof((list).first->data), value)))
/// @brief Insert value of other type at index in list
/// @param list List
/// @param index Index into the list
/// @param value Value to insert
/// @return Pointer to the added value
/// @note Error status is recorded in SL_ERROR
/// @warning The value inserted will have the memory size of the expression `value`
#define SL_listInsert_typed(list, _index, value) ((typeof(value) *)(__SL_IS_DLIST(list) ? __SL_dlistInsert : __SL_listInsert)(__SL_XPD_LIST(list, &), sizeof(value), _index, (void *)__SL_PTR(value)))
/// @brief Add value to start of list
/// @param list List
/// @param value Value to add
/// @return Pointer to the added value
/// @return Pointer to the added value
/// @note Error status is recorded in SL_ERROR
#define SL_listAdd_first(list, value) SL_listInsert((list), 0, (value))
/// @brief Add value to end of list
/// @param list List
/// @param value Value to add
/// @return Pointer to the added value
/// @note Error status is recorded in SL_ERROR
#define SL_listAdd(list, value) SL_listInsert((list), (list).count, (value))

SL_header bool __SL_listRemove (void **first, void **last, usize *count, sl_allocator *alloc, usize elemSize, usize index, void *into);
SL_header bool __SL_dlistRemove(void **first, void **last, usize *count, sl_allocator *alloc, usize elemSize, usize index, void *into);
/// @brief Remove a node at index in list and store its value in "into"
/// @param list List
/// @param index Index into the list
/// @param into Pointer to a variable in which to store the popped value
/// @return Wether the node was successfully removed
/// @note Error status is recorded in SL_ERROR
#define SL_listPop(list, index, into) ((__SL_IS_DLIST(list) ? __SL_dlistRemove : __SL_listRemove)(__SL_XPD_LIST(list, &), sizeof((list).first->data), index, into))
/// @brief Remove a node at index in list
/// @param list List
/// @param index Index into the list
/// @return Wether the node was successfully removed
/// @note Error status is recorded in SL_ERROR
#define SL_listRemove(list, index) SL_listPop(list, index, NULL)
SL_header bool __SL_listRemove_ref (void **first, void **last, usize *count, sl_allocator *alloc, void *ptr_to_value);
SL_header bool __SL_dlistRemove_ref(void **first, void **last, usize *count, sl_allocator *alloc, void *ptr_to_value);
/// @brief Remove a node by reference in list
/// @param list List
/// @param ptr_to_value A pointer to a value stored in the list (as outputed by functions such as `listAt` or `listAddEnd`)
/// @return Wether the node was successfully removed
/// @note Error status is recorded in SL_ERROR
#define SL_listRemove_ref(list, ptr_to_value) ((__SL_IS_DLIST(list) ? __SL_dlistRemove_ref : __SL_listRemove_ref)(__SL_XPD_LIST(list, &), ptr_to_value))



/// @brief Iterate over every item into a list
/// @param varname The name of the iterator
/// @param list List
/// @note "varname" is a pointer to a value in list at each iteration.
/// @note Can be used with both "list" and "dlist" types.
#define SL_lforeach(varname, list) \
for ( \
    typeof((list).first->data) *varname = (list).first ? &list.first->data : NULL, *__##varname##_NEXT__ = SL_lnext((list), varname), *__##varname##_INDEX__ = (void *)0; \
    varname; \
    (varname = __##varname##_NEXT__), __##varname##_NEXT__ = SL_lnext((list), varname), (__##varname##_INDEX__ = (typeof(__##varname##_INDEX__))((char *)__##varname##_INDEX__ + 1)) \
)
#define SL_lindex(varname)   ((usize)__##varname##_INDEX__)
#define SL_lnext(list, ptr)  (                       (ptr) && ((typeof((list).first))((void *)(ptr) - (1 + __SL_IS_DLIST(list)) * sizeof(void *)))->next ? &((typeof((list).first))((void *)(ptr) - (1 + __SL_IS_DLIST(list)) * sizeof(void *)))->next->data : NULL)
#define SL_dlprev(list, ptr) (__SL_IS_DLIST(list) && (ptr) && ((typeof((list).first))((void *)(ptr) -                         2 * sizeof(void *)))->prev ? &((typeof((list).first))((void *)(ptr) -                         2 * sizeof(void *)))->prev->data : NULL)



/// @brief Print list to an arbitrary reciever with user defined formatting
/// @param dst Destination in which to print. Uses generic "gprintf" function to differenciate between printing to a string or a file
/// @param list List
/// @param fmt The format of the data to print
/// @param varname The name of the iterator
/// @param ... How to expand the value stored to fit the format specified with 'fmt'
/// @note Can be used with both "list" and "dlist" types.
#define SL_listPrintf_full(dst, list, fmt, varname, ...) do { \
    if (!(list).first) SL_gprintf(dst, "list[]"); \
    else { \
        SL_lforeach(varname, list) SL_gprintf(dst, SL_lindex(varname) == 0 ? "list["fmt : ", "fmt, ##__VA_ARGS__); \
        SL_gprintf(dst, "]"); \
    } \
} while (0)

/// @brief Print list to a string
/// @param dst Destination string
/// @param list List
/// @param fmt The format of the data to print
#define SL_listPrintf(dst, list, fmt) SL_listPrintf_full(dst, list, fmt, __SL_VARNAME__, *__SL_VARNAME__)



#define SL_putList_full(...) SL_PUT_WRAPPER(SL_listPrintf_full(SL_PUT_TARGET, __VA_ARGS__))
#define SL_putList(...)      SL_PUT_WRAPPER(SL_listPrintf(SL_PUT_TARGET, __VA_ARGS__))



#ifdef SL_STRIP_PREFIX
#   define LIST_FIELDS      SL_LIST_FIELDS
#   define DEF_LIST         SL_DEF_LIST
#   define list             SL_list
#   define dlist            SL_dlist
#   define listCreateA      SL_listCreateA
#   define dlistCreateA     SL_dlistCreateA
#   define listDestroy      SL_listClear
#   define listFirst        SL_listFirst
#   define listLast         SL_listLast
#   define listAt           SL_listAt
#   define listInsert       SL_listInsert
#   define listAdd          SL_listAdd
#   define listAdd_first    SL_listAdd_first
#   define listRemove       SL_listRemove
#   define listRemove_ref   SL_listRemove_ref
#   define listPop          SL_listPop
#   define lforeach         SL_lforeach
#   define lindex           SL_lindex
#   define lnext            SL_lnext
#   define dlprev           SL_dlprev
#   define listPrintf_full  SL_listPrintf_full
#   define listPrintf       SL_listPrintf
#   define putList_full     SL_putList_full
#   define putList          SL_putList
#endif



#ifdef SL_IMPLEMENTATION
SL_header void *__SL_listNodeAt(void *first, void *last, usize count, usize index)
{
    (void)last; (void)count;

    while (first && index) --index, first = ((__list_gen_node *)first)->next;
    return first ? first : (__SL_ERROR(SL_ERROR_OUT_OF_BOUNDS), NULL);
}
SL_header void *__SL_dlistNodeAt(void *first, void *last, usize count, usize index)
{
    if (index > count / 2) {
        index = count - 1 - index;
        __dlist_gen_node *cur = last;
        while (cur && index) --index, cur = cur->prev;
        return cur ? cur : (__SL_ERROR(SL_ERROR_OUT_OF_BOUNDS), NULL);
    }
    else {
        __dlist_gen_node *cur = first;
        while (cur && index) --index, cur = cur->next;
        return cur ? cur : (__SL_ERROR(SL_ERROR_OUT_OF_BOUNDS), NULL);
    }
}
SL_header void *__SL_listValueFromNode(void *node_ptr, bool is_dlist)
{ 
    return node_ptr ? (void *)node_ptr + (1 + is_dlist) * sizeof(void *) : NULL; 
}
SL_header void *__SL_listNodeFromValue(void *value_ptr, bool is_dlist)
{ 
    return value_ptr ? (void *)value_ptr - (1 + is_dlist) * sizeof(void *) : NULL; 
}

SL_header void *__SL_listInsert(void **first, void **last, usize *count, sl_allocator *alloc, usize elemSize, usize index, void *value)
{
    if (index > *count) return __SL_ERROR(SL_ERROR_OUT_OF_BOUNDS), NULL;
    
    __list_gen_node *node_ptr = SL_aalloc(alloc, sizeof(void *) + elemSize);
    if (value) memcpy((void *)node_ptr + sizeof(void *), value, elemSize);
    
    if (index == 0) {
        if (!*last) *last = node_ptr;
        node_ptr->next = *first;
        *first = node_ptr;
    }
    else if (index == *count) {
        if (!*first) *first = node_ptr;
        else *(void **)*last = node_ptr;
        node_ptr->next = NULL;
        *last = node_ptr;
    }
    else {
        __list_gen_node *parent = __SL_listNodeAt(*first, NULL, 0, index - 1);
        node_ptr->next = parent->next;
        parent->next = node_ptr;
    }    
    
    ++*count;
    return &node_ptr->data;
}
SL_header void *__SL_dlistInsert(void **first, void **last, usize *count, sl_allocator *alloc, usize elemSize, usize index, void *value)
{
    if (index > *count) return __SL_ERROR(SL_ERROR_OUT_OF_BOUNDS), NULL;

    __dlist_gen_node *node_ptr = SL_aalloc(alloc, elemSize + 2 * sizeof(void *));
    if (value) memcpy(&node_ptr->data, value, elemSize);
    
    if (index == 0) {
        node_ptr->next = *first;
        node_ptr->prev = NULL;
        if (node_ptr->next) node_ptr->next->prev = node_ptr;
        
        *first = node_ptr;
        if (!*last) *last = node_ptr;
    }
    else if (index == *count) {
        node_ptr->next = NULL;
        node_ptr->prev = *last;
        if (node_ptr->prev) node_ptr->prev->next = node_ptr;
        
        *last = node_ptr;
        if (!*first) *first = node_ptr;
    }
    else {
        __dlist_gen_node *atIdx = __SL_dlistNodeAt(*first, *last, *count, index);
        node_ptr->next = atIdx;
        node_ptr->prev = atIdx->prev;
        atIdx->prev    = node_ptr;
    }

    ++*count;
    return &node_ptr->data;
}

SL_header bool __SL_listRemove(void **first, void **last, usize *count, sl_allocator *alloc, usize elemSize, usize index, void *into)
{
    __list_gen_node *to_free;
    if (index == 0) {
        to_free = *first;
        if (!to_free) return __SL_ERROR(SL_ERROR_OUT_OF_BOUNDS), false;
        *first = to_free->next;
        if (!*first) *last = NULL;
    }
    else {
        __list_gen_node *parent = __SL_listNodeAt(*first, NULL, 0, index - 1);
        if (!parent || !parent->next) return false;
        to_free = parent->next;
        parent->next = to_free->next;
    }

    if (into) memcpy(into, (void *)to_free + sizeof(void *), elemSize);
    SL_afree(alloc, to_free);
    --*count;
    return true;
}
#include <assert.h>
SL_header bool __SL_dlistRemove(void **first, void **last, usize *count, sl_allocator *alloc, usize index, usize elemSize, void *into)
{
    __dlist_gen_node *at = __SL_dlistNodeAt(*first, *last, *count, index);
    if (!at) return false;
    
    if (at == *first) {
        assert(at->prev == NULL);
        *first = at->next;
        if (*first) ((__dlist_gen_node*)*first)->prev = NULL;
        else *last = NULL;
        
    }
    else if (at == *last) {
        assert(at->next == NULL);
        *last = at->prev;
        if (*last) ((__dlist_gen_node*)*last)->next = NULL;
        else *first = NULL;
    }
    else {
        at->prev->next = at->next;
        at->next->prev = at->prev;
    }

    if (into) memcpy(into, &at->data, elemSize);
    SL_afree(alloc, at);
    --*count;
    return true;
}

SL_header bool __SL_listRemove_ref(void **first, void **last, usize *count, sl_allocator *alloc, void *ptr_to_value)
{
    __list_gen_node *to_free = ptr_to_value - sizeof(void *);

    if (to_free == *first) {
        *first = to_free->next;
        if (!*first) *last = NULL;
    }
    else {
        __list_gen_node *parent = *first;

        if (parent) while (parent->next && parent->next != to_free) parent = parent->next;
        if (!parent || !parent->next) return __SL_ERROR(SL_ERROR_OUT_OF_BOUNDS), false;

        parent->next = to_free->next;
        if (parent->next == NULL) *last = parent;
    }

    SL_afree(alloc, to_free);
    --*count;
    return true;
}
SL_header bool __SL_dlistRemove_ref(void **first, void **last, usize *count, sl_allocator *alloc, void *ptr_to_value)
{
    __dlist_gen_node *at = ptr_to_value - 2 * sizeof(void *);

    if (at == *first) {
        assert(at->prev == NULL);
        *first = at->next;
        if (*first) ((__dlist_gen_node*)*first)->prev = NULL;
        else *last = NULL;
        
    }
    else if (at == *last) {
        assert(at->next == NULL);
        *last = at->prev;
        if (*last) ((__dlist_gen_node*)*last)->next = NULL;
        else *first = NULL;
    }
    else {
        at->prev->next = at->next;
        at->next->prev = at->prev;
    }

    SL_afree(alloc, at);
    --*count;
    return true;
}
#endif



#ifndef SL_NO_DEFINES
    SL_DEF_LIST(bool);
    SL_DEF_LIST(int);   SL_DEF_LIST(uint);  SL_DEF_LIST(usize);  SL_DEF_LIST(ssize);
    SL_DEF_LIST(i8);    SL_DEF_LIST(i16);   SL_DEF_LIST(i32);    SL_DEF_LIST(i64);
    SL_DEF_LIST(u8);    SL_DEF_LIST(u16);   SL_DEF_LIST(u32);    SL_DEF_LIST(u64);
    SL_DEF_LIST(f32);   SL_DEF_LIST(f64);
    SL_DEF_LIST(SL_ptr(char));

    typedef SL_list(f32) SL_list(float);                    typedef SL_dlist(f32) SL_dlist(float); 
    typedef SL_list(f64) SL_list(double);                   typedef SL_dlist(f64) SL_dlist(double);

    typedef SL_list(u8)  SL_list(ch8),  SL_list(char);      typedef SL_dlist(u8)  SL_dlist(ch8),  SL_dlist(char);
    typedef SL_list(u16) SL_list(ch16), SL_list(wchar_t);   typedef SL_dlist(u16) SL_dlist(ch16), SL_dlist(wchar_t);
    typedef SL_list(u32) SL_list(ch32);                     typedef SL_dlist(u32) SL_dlist(ch32);

    SL_DEF_LIST(SL_ptr(void));
#endif
#endif // _SL_LIST_H_