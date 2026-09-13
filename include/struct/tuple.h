#ifndef _SL_TUPLE_H_
#define _SL_TUPLE_H_

#include "../base.h"

#define SL_DEF_TUPLE2(t0_, t1_)                typedef struct tuple2(t0_, t1_) { u8 count[0][2]; t0 d0; t1 d1; } tuple2(t0_, t1_)
#define SL_DEF_TUPLE3(t0_, t1_, t2_)           typedef struct tuple3(t0_, t1_, t2_) { u8 count[0][3]; t0 d0; t1 d1; t2 d2; } tuple3(t0_, t1_, t2_)
#define SL_DEF_TUPLE4(t0_, t1_, t2_, t3_)      typedef struct tuple4(t0_, t1_, t2_, t3_) { u8 count[0][4]; t0 d0; t1 d1; t2 d2; t3 d3; } tuple4(t0_, t1_, t2_, t3_)
#define SL_DEF_TUPLE5(t0_, t1_, t2_, t3_, t4_) typedef struct tuple5(t0_, t1_, t2_, t3_, t4_) { u8 count[0][5]; t0 d0; t1 d1; t2 d2; t3 d3; t4 d4; } tuple5(t0_, t1_, t2_, t3_, t4_)

#define SL_DEF_TUPLE(n, ...) SL_DEF_TUPPLE##n(__VA_ARGS__)

#define tuple2(t0_, t1_) CAT(CAT(tuple_, t0_), t1_)
#define tuple3(t0_, t1_, t2_) CAT(tuple2(t0_, t1_), t2_)
#define tuple4(t0_, t1_, t2_, t3_) CAT(tuple3(t0_, t1_, t2_), t3_)
#define tuple5(t0_, t1_, t2_, t3_, t4_) CAT(tuple4(t0_, t1_, t2_, t3_), t4_)

#define tuple(n, ...)  CAT(tuple, n)(__VA_ARGS__)
#define tuple_count(t) sizeof((t).count[0])

#define XPD_TUPLE2(t) t.d0, t.d1
#define XPD_TUPLE3(t) XPD_TUPLE2(t), t.d3
#define XPD_TUPLE4(t) XPD_TUPLE3(t), t.d4
#define XPD_TUPLE5(t) XPD_TUPLE4(t), t.d5

#endif // _SL_TUPLE_H_