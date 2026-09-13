#define SL_STRIP_PREFIX
#define SL_IMPLEMENTATION
#include "../include/sl.h"



SL_DEF_DICT(ptr(char), ptr(char));
SL_DEF_DICT(uint, uint);
SL_DEF_HASH_FUNC(uint, key) { return *key; }

int foo(uint ID, uint seconds);
SL_DEF_ASYNC(foo, uint, ID, uint, seconds);

#include <unistd.h>
int foo(uint ID, uint seconds)
{
    printf("[%u] Starting FOO (%u)\n", ID, seconds);
    sleep(seconds);
    if (ID < 2) await(foo_async(ID, seconds));
    sleep(seconds);
    printf("[%u] Finished FOO (%u)\n", ID, seconds);
}

int main() { 
    // /*
    const foo_task *p = foo_async(0, 2000);
    sleep(2500);
    if (p->status != SL_TASK_DONE) printf("Didn't finish\n");
    printf("back to main\n");
    // while (p->state != SL_PROCESS_DONE);
    
    // float ret;
    // if (!await(p, &ret)) printf("ERROR: coudln't finish execution of BAR\n");
    // printf("Returned %f\n", ret);
    
    while (p->status == SL_TASK_DONE) sleep(1000);
    await(p);
    // */


    // fv3 *v0 = new(fv3); *v0 = fv3_(0, 1, 2);
    //     <=>
    fv3 *v1 = new(fv3_(0, 1, 2));

    printf("v1 = (%f, %f, %f)\n", v1->x, v1->y, v1->z);

    f64 f = SL_PI;
    printf("double f = %lf\n", f);

    fv3 x = fv3_(0, 0, 1), 
        y = fv3_(1, 0, 0),
        z = fv3_(0, 1, 0);

    i64v3 iw = i64v3_(10, 20, 30);
    printf("iw = (%d, %d, %d)\n", iw);

    // fv3 w = vadd(vsub(x, y), z);
    // printf("w = ("); aforeach(comp, arrayWrap(float, vcount(w), w.data)) if (comp + 1 == __comp_MAX__) printf("%f)\n", *comp); else printf("%f, ", *comp);
    
    // fv *test = malloc(sizeof(test->count) + sizeof(test->data[0]) * 8);
    // *(usize*)(&test) = 8;
    // #include <assert.h>
    // usize res = vcount(test);
    // printf("RES = %u\n", res);
    // assert(res == 8);

    dict(uint, uint) udico = SL_dictCreate(uint, uint, 1024);
    dictAdd(udico, 0,    101);
    dictAdd(udico, 1024, 102);
    dictAdd(udico, 10,   103);

    dictRemove(udico, 0);

    printf("udico: dict[");
    bool first = true;
    dforeach(pair, udico) {
        printf("{%u: %u}", pair->key, pair->value);
        if (!first) printf(", ");
        first = false;
    }
    printf("]\n");

    uint *ures = SL_dictGet(udico, 1024);
    printf("Dico[1024] = %u\n", *ures);
    ures = SL_dictGet(udico, 10);
    printf("Dico[10] = %u\n", *ures);
    dictClear(udico);

    array(uint) temp = arrayCreate(uint, 10); 
    array(uint) a = {0};

    arrayAdd(a, 1);
    arrayAdd(a, 2);
    arrayAdd(a, 3);
    uint values0[] = {4, 5, 6, 7, 8};
    arrayAddRange(a, 5, values0);
    
    if (!arrayInsert(a, 1, 10)) printf("ERROR 0\n");

    uint values[] = {20, 21};
    if (!arrayInsertRange(a, 7, 2, values)) printf("ERROR 1\n");

    arrayRemove(a, 7);
    arrayRemoveRange(a, 2, 2);

    SL_arrayInsertVar(a, 0, 100, 101, 102);
    SL_arrayAddVar(a, 200);

    arrayQSort(a, uint_cmp);
    printf("Array: (%u / %u) ", a.count, a.capa); SL_arrayPrintf(a, stdout, "%u"); printf("\n");
    
    arrayDestroy(a);
    printf("Array = (%p, %u, %u)\n", a.data, a.capa, a.capa);
    
    list(uint) b = {0};

    listAddEnd(b, 0);
    listAddEnd(b, 1);
    listAddEnd(b, 2);
    listAddEnd(b, 3);
    
    listInsert(b, 4, 10);
    listInsert(b, 2, 101);
    
    usize idx = 3;
    if (!listRemove(b, idx)) printf("Error: %s", SL_strerr(SL_ERROR));
    
    printf("List: "); listPrintf(b, stdout, "%u"); printf("\n");
    printf("List[3] = %u\n", *listAt(b, 3));
}