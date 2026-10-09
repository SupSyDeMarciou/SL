#define SL_STRIP_PREFIX
#define SL_IMPLEMENTATION
#include "../include/sl.h"



SL_DEF_DICT(ptr(char), ptr(char));
SL_DEF_DICT(uint, uint);
SL_DEF_HASH_FUNC(uint, key) { return *key; }

int foo(uint ID, uint seconds);
SL_DEF_ASYNC(foo, uint, ID, uint, seconds);

int foo(uint ID, uint milli_seconds)
{
    printf("[%u] Starting FOO (%u)\n", ID, milli_seconds);
    sleep_m(milli_seconds);
    if (ID < 2) await(foo_async(ID + 1, milli_seconds));
    sleep_m(milli_seconds);
    printf("[%u] Finished FOO (%u)\n", ID, milli_seconds);
    return 0;
}



int main()
{
    const foo_task *p = foo_async(0, 200);
    sleep_m(200);
    if (p->status != SL_TASK_DONE) printf("Didn't finish\n");
    printf("back to main\n");
    await(p);

    fv3 *v1 = new(fv3_(0, 1, 2));
    printf("v1 = (%f, %f, %f)\n", v1->x, v1->y, v1->z);

    f64 f = SL_PI;
    printf("double f = %lf\n", f);

    dict(uint, uint) udico = SL_dictCreate(uint, uint, 1024);
    dictAdd(udico, 0,    101);
    dictAdd(udico, 1024, 102);
    dictAdd(udico, 10,   103);

    dictRemove(udico, 0);

    put("udico: dict[ ", PUT_WRAPPER(
        bool first = true;
        dforeach(pair, udico) {
            first ? first = false : gprintf(PUT_TARGET, ", ");
            gprintf(PUT_TARGET, "{ %u: %u }", pair->key, pair->value);
        }
    ), " ]\n");
    
    uint *ures = SL_dictGet(udico, 1024);
    put("Dico[1024] = %u\n", *ures);
    ures = SL_dictGet(udico, 10);
    put("Dico[10] = %u\n", *ures);
    dictClear(udico);

    array(uint) temp = arrayCreate(uint, 10); 
    array(uint) a = {0};

    arrayAdd(a, 1);
    arrayAdd(a, 2);
    arrayAdd(a, 3);
    uint values0[] = {4, 5, 6, 7, 8};
    arrayAdd_range(a, 5, values0);
    
    if (!arrayInsert(a, 1, 10)) put("ERROR 0\n");

    uint values[] = {20, 21};
    if (!arrayInsert_range(a, 7, 2, values)) put("ERROR 1\n");

    arrayRemove(a, 7);
    arrayRemove_range(a, 2, 2);

    SL_arrayInsert_var(a, 0, 100, 101, 102);
    SL_arrayAdd_var(a, 200);

    arraySort(a, uint_cmp);
    put("Array: (%zu / %zu) ", a.count, a.capa, putArray(a, "%u"), "\n");
    
    arrayDestroy(a);
    put("Array = (%p, %zu, %zu)\n", a.data, a.capa, a.capa);
    
    list(uint) b = {0};

    listAdd(b, 0);
    listAdd(b, 1);
    listAdd(b, 2);
    listAdd_first(b, 3);
    
    listInsert(b, 4, 10);
    listInsert(b, 2, 101);
    
    usize idx = 40;
    if (!listRemove(b, idx)) put("  # Error: %s\n", SL_strerr(SL_ERROR));
    
    put("List: ", putList(b, "%u"), "\n");
    put("List[3] = %u\n", *listAt(b, 3));
}