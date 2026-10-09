#ifndef _SL_DICT_H_
#define _SL_DICT_H_

/*
 *  HASH: generic dictionaries in C. 
 *  
 *  TODO:
 *  - Add expansion of dict based on a heuristic
 * 
*/

#include "../base.h"
#include "array.h"



#define SL_DICT_BASE_CAPACITY 32

/// @brief Define a new type of dictionary
/// @param key_type Type of the key representing
/// @param value_type Type of the value to be stored
/// @note You can refer to the dict using "dict(key_type, value_type)" or directly with "{key_type}_{value_type}_d"
#define SL_DEF_DICT(key_type, value_type) \
    typedef struct CAT(SL_dict(key_type, value_type), _bucket) { struct CAT(SL_dict(key_type, value_type), _bucket) *next; key_type key; value_type value; } CAT(SL_dict(key_type, value_type), _bucket); \
    typedef struct SL_dict(key_type, value_type) { \
        SL_ARRAY_FIELDS(CAT(SL_dict(key_type, value_type), _bucket) *); \
        usize (*hash)(const key_type *); \
        int   (*cmp)(const key_type *, const key_type *); \
    } SL_dict(key_type, value_type)

#define SL_dict(key_type, value_type) CAT(CAT(CAT(key_type, _), value_type), _dict)

typedef struct __dict_gen_bucket { struct __dict_gen_bucket *next; void *key; } __dict_gen_bucket;
struct __dict_gen {
    SL_ARRAY_FIELDS(__dict_gen_bucket *);
    usize (*hash)(const void *);
    int   (*cmp)(const void *, const void *);
};


/// @brief Create an empty dict
/// @param key_type Type of the key representing
/// @param value_type Type of the value to be stored
/// @param hash_func Function for hashing the key
/// @param cmp_func Function for compairing two keys
/// @param initialCapacity Maximum number of hashes possible
/// @param allocator_ Allocator
/// @return The newly created list
#define SL_dictCreateA_full(key_type, value_type, hash_func, cmp_func, initialCapacity, allocator_) ((SL_dict(key_type, value_type)){.data = SL_azalloc(allocator_, initialCapacity * sizeof(void *)), .capa = initialCapacity, .count = 0, .hash = hash_func, .cmp = cmp_func, .alloc = allocator_})
/// @brief Create an empty dict
/// @param key_type Type of the key representing
/// @param value_type Type of the value to be stored
/// @param initialCapacity Maximum number of hashes possible
/// @param allocator_ Allocator
/// @return The newly created list
#define SL_dictCreateA(key_type, value_type, initialCapacity, allocator_) SL_dictCreateA_full(key_type, value_type, key_type##_hash, key_type##_cmp, initialCapacity, allocator_)
/// @brief Create an empty dict
/// @param key_type Type of the key representing
/// @param value_type Type of the value to be stored
/// @param hash_func Function for hashing the key
/// @param cmp_func Function for compairing two keys
/// @param initialCapacity Maximum number of hashes possible
/// @return The newly created list
#define SL_dictCreate_full(key_type, value_type, hash_func, cmp_func, initialCapacity) SL_dictCreateA_full(key_type, value_type, hash_func, cmp_func, initialCapacity, std_allocator)
/// @brief Create an empty dict
/// @param key_type Type of the key representing
/// @param value_type Type of the value to be stored
/// @param initialCapacity Maximum number of hashes possible
/// @return The newly created list
#define SL_dictCreate(key_type, value_type, initialCapacity) SL_dictCreateA(key_type, value_type, initialCapacity, std_allocator)

/// @brief Clear every entry in dict
/// @param dict Dict
SL_header void __SL_dictClear(struct __dict_gen *dict);
/// @brief Clear every entry in dict
/// @param dict Dict
#define SL_dictClear(dict) (__SL_dictClear((void*)&(dict).data))
/// @brief Free dict's resources and reset its value
/// @param dict Dict
#define SL_dictDestroy(dict) (__SL_dictClear((void*)&(dict)), SL_afree((dict).alloc, (dict).data), memset(&(dict), 0, sizeof(dict)))

/// @brief Hash a key using a dict's hash function
/// @param dict Dict
/// @param key Pointer to key
/// @return The hashed key 
#define SL_dictHash2(dict, key) ((dict).hash(key) % (dict).capa)
/// @brief Hash a key using a dict's hash function
/// @param dict Dict
/// @param key Key
/// @return The hashed key 
#define SL_dictHash(dict, key) SL_dictHash2(dict, __SL_PTR(key))
/// @brief Compare two keys using a dict's cmp function
/// @param dict Dict
/// @param a Pointer to first key
/// @param b Pointer to second key
/// @return Whether the two keys match 
#define SL_dictCmp2(dict, a, b) ((dict).cmp(a, b))
/// @brief Compare two keys using a dict's cmp function
/// @param dict Dict
/// @param a First key
/// @param b Second key
/// @return Whether the two keys match 
#define SL_dictCmp(dict, a, b) SL_dictCmp2(dict, __SL_PTR(a), __SL_PTR(b))

SL_header void *__SL_dictGet(struct __dict_gen *dict, usize keySize, const void *key);
/// @brief Get value assciated with key in dict
/// @param dict Dict
/// @param key_ Key
/// @return A pointer to the value if found, NULL otherwise
/// @note Error status is recorded in SL_ERROR
#define SL_dictGet(dict, key_) ((typeof((*(dict).data)->value)*)__SL_dictGet((void *)&(dict), sizeof((*(dict).data)->key), __SL_PTR_T(typeof((*(dict).data)->key), key_)))

SL_header void *__SL_dictAdd(struct __dict_gen *dict, usize keySize, const void *key, usize valueSize, const void *value);
/// @brief Get value assciated with key in dict
/// @param dict Dict
/// @param key_ Key
/// @param value_ Value
/// @return A pointer to the added value, or NULL in case of an error
/// @note Error status is recorded in SL_ERROR
#define SL_dictAdd(dict, key_, value_) ((typeof((*(dict).data)->value)*)__SL_dictAdd((void *)&(dict), sizeof((*(dict).data)->key), __SL_PTR_T(typeof((*(dict).data)->key), key_), sizeof((*(dict).data)->value), __SL_PTR_T(typeof((*(dict).data)->value), value_)))

SL_header bool __SL_dictRemove(struct __dict_gen *dict, usize keySize, void *key);
/// @brief Remove value assciated with key in dict
/// @param dict Dict
/// @param key Key
/// @return Wether the removal was successful
/// @note Error status is recorded in SL_ERROR
#define SL_dictRemove(dict, key) (__SL_dictRemove((void *)&(dict).data, sizeof(key), __SL_PTR(key)))
/// @brief Get the key associated with this value
/// @param dict The dictionnary
/// @param ptr The pointer to the dict value whose key to retrieve
/// @warning ptr is assumed to be a value returned from functions such as `dictGet`
#define SL_dictKey(dict, ptr) (typeof((dict).data[0]->key) *)((usize)(ptr) - sizeof(void *) - sizeof((dict).data[0]->key))



#define SL_dforeach(varname, dict) \
    for (typeof((dict).data) __##varname##_ARRAY__ = (dict).data, __##varname##_MAX__ = (dict).data + (dict).capa; __##varname##_ARRAY__ < __##varname##_MAX__; ++__##varname##_ARRAY__) \
    if ((*__##varname##_ARRAY__)) for (typeof((*__##varname##_ARRAY__)) varname = *__##varname##_ARRAY__; varname; varname = varname->next)



/// @brief Define a hash function to use with dict
/// @param type Type of the hashed key
/// @param key Name of the key operand
/// @return Definition of the function `usize {key_type}_hash(const {key_type} *{key_name})`
#define SL_DEF_HASH_FUNC(key_type, key_name) SL_header usize key_type##_hash(const key_type *key_name)



#ifdef SL_STRIP_PREFIX
#   define  DEF_DICT            SL_DEF_DICT
#   define  dict                SL_dict
#   define  dictCreate          SL_dictCreate
#   define  dictCreate_full     SL_dictCreate_full
#   define  dictCreateA         SL_dictCreateA
#   define  dictCreateA_full    SL_dictCreateA_full
#   define  dictClear           SL_dictClear
#   define  dictDestroy         SL_dictDestroy
#   define  dictCmp2            SL_dictCmp2
#   define  dictCmp             SL_dictCmp
#   define  dictHash2           SL_dictHash2
#   define  dictHash            SL_dictHash
#   define  dictGet             SL_dictGet
#   define  dictAdd             SL_dictAdd
#   define  dictRemove          SL_dictRemove
#   define  dictKey             SL_dictKey
#   define  dforeach            SL_dforeach
#   define  DEF_HASH_FUNC       SL_DEF_HASH_FUNC
#endif



#ifdef SL_IMPLEMENTATION
SL_header void __SL_dictClear(struct __dict_gen *dict)
{
    for (usize i = 0; i < dict->capa; ++i) {
        for (void *node = dict->data[i]; node; ) {
            void *temp = *(void**)node;
            SL_afree(dict->alloc, node);
            node = temp;
        }
        dict->data[i] = NULL;
    }
    dict->count = 0;
}

SL_header void *__SL_dictGet(struct __dict_gen *dict, usize keySize, const void *key)
{
    usize hash = dict->hash(key) % dict->capa;
    struct __dict_gen_bucket *node = dict->data[hash];
    while (node && dict->cmp(&node->key, key) != 0) node = node->next;
    return node ? (void *)node + sizeof(void *) + keySize : (__SL_ERROR(SL_ERROR_OUT_OF_BOUNDS), NULL);
}

SL_header void *__SL_dictAdd(struct __dict_gen *dict, usize keySize, const void *key, usize valueSize, const void *value)
{
    struct __dict_gen_bucket *new = SL_aalloc(dict->alloc, sizeof(void *) + keySize + valueSize);
    if (!new) return __SL_ERROR(SL_ERROR_MEMORY), NULL;
    if (!memcpy((void *)&new->key, key, keySize))               return SL_afree(dict->alloc, new), __SL_ERROR(SL_ERROR_MEMORY), NULL;
    if (!memcpy((void *)&new->key + keySize, value, valueSize)) return SL_afree(dict->alloc, new), __SL_ERROR(SL_ERROR_MEMORY), NULL;

    if (dict->capa == 0)
    {
        dict->data = SL_azalloc(dict->alloc, SL_DICT_BASE_CAPACITY * sizeof(void *));
        dict->capa = SL_DICT_BASE_CAPACITY;
    }
    else if (dict->count / (double)dict->capa > 3.0)
    {
        // We should double the bucket count and rehash everything
        usize new_capa = dict->capa * 2;
        struct __dict_gen_bucket **new_buckets = SL_azalloc(dict->alloc, new_capa * sizeof(void *));
        SL_aforeach(bucket, *dict)
        {
            struct __dict_gen_bucket *node = *bucket;
            while (node)
            {
                usize hash = dict->hash(node->key) % new_capa;
                node->next = dict->data[hash];
                dict->data[hash] = node;

                node = node->next;
            }
        }

        SL_afree(dict->alloc, dict->data);
        dict->data = new_buckets;
        dict->capa = new_capa;
    }
    
    usize hash = dict->hash(key) % dict->capa;
    new->next = dict->data[hash];
    dict->data[hash] = new;
    ++dict->count;
    return (void *)&new->key + keySize;
}

SL_header bool __SL_dictRemove(struct __dict_gen *dict, usize keySize, void *key)
{
    usize hash = dict->hash(key) % dict->capa;
    struct __dict_gen_bucket *node = dict->data[hash];

    if (!node) return __SL_ERROR(SL_ERROR_OUT_OF_BOUNDS), false;

    if (dict->cmp(&node->key, key) == 0) dict->data[hash] = node->next;
    else {
        while (node->next && dict->cmp(&node->next->key, key) != 0) node = node->next;

        if (node->next == NULL) return __SL_ERROR(SL_ERROR_OUT_OF_BOUNDS), false;

        struct __dict_gen_bucket *to_free = node->next;
        node->next = to_free->next;
        node = to_free;
    }

    SL_afree(dict->alloc, node);
    --dict->count;
    return true;
}
#endif



#ifndef SL_NO_DEFINES
SL_DEF_HASH_FUNC(charp, key) SL_implement
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
#endif // _SL_DICT_H_