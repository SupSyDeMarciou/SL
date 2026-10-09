#ifndef _SL_TUPLE_H_
#define _SL_TUPLE_H_

#include "../base.h"

#define SL_DEF_TUPLE2(t0, t1)             typedef struct tuple2(t0, t1)             { u8 count[0][2]; t0 v0; t1 v1; }                      tuple2(t0, t1)
#define SL_DEF_TUPLE3(t0, t1, t2)         typedef struct tuple3(t0, t1, t2)         { u8 count[0][3]; t0 v0; t1 v1; t2 v2; }               tuple3(t0, t1, t2)
#define SL_DEF_TUPLE4(t0, t1, t2, t3)     typedef struct tuple4(t0, t1, t2, t3)     { u8 count[0][4]; t0 v0; t1 v1; t2 v2; t3 v3; }        tuple4(t0, t1, t2, t3)
#define SL_DEF_TUPLE5(t0, t1, t2, t3, t4) typedef struct tuple5(t0, t1, t2, t3, t4) { u8 count[0][5]; t0 v0; t1 v1; t2 v2; t3 v3; t4 v4; } tuple5(t0, t1, t2, t3, t4)

#define SL_DEF_TUPLE(n, ...) SL_DEF_TUPPLE##n(__VA_ARGS__)

#define tuple2(t0, t1)             CAT(CAT(CAT(tuple_, t0), _), t1)
#define tuple3(t0, t1, t2)         CAT(CAT(tuple2(t0, t1), _), t2)
#define tuple4(t0, t1, t2, t3)     CAT(CAT(tuple3(t0, t1, t2), _), t3)
#define tuple5(t0, t1, t2, t3, t4) CAT(CAT(tuple4(t0, t1, t2, t3), _), t4)

#define tuple(n, ...)  CAT(tuple, n)(__VA_ARGS__)
#define tuple_count(t) sizeof((t).count[0])

#define XPD_TUPLE2(t) t.d0, t.d1
#define XPD_TUPLE3(t) XPD_TUPLE2(t), t.d3
#define XPD_TUPLE4(t) XPD_TUPLE3(t), t.d4
#define XPD_TUPLE5(t) XPD_TUPLE4(t), t.d5

#endif // _SL_TUPLE_H_