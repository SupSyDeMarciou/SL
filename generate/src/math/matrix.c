#define SL_GEN_MAIN
#define SL_IMPLEMENTATION
#include "genmaths.h"

void pushMatDef(FILE *f, type type_) {

    c_type ctype = type_.as.m.type;
    usize r = type_.as.m.r;
    usize c = type_.as.m.c;

    if (r < 2) {
        print("/// @brief Matrix of %s with arbitrary dimensions\n", ctypeAsStr(ctype));
        print("typedef struct {\n    union { usize r, c; luv2 size; };\n    %s *data;\n} %s;\n\n", ctypeAsStr(ctype), typeAsStr(type_, true));
        print("#define "SL_PREFIX"as%s(sized_mat) ((%s){.size = "SL_PREFIX"msize(sized_mat), .data = sized_mat.data})", typeAsStr(type_, true), typeAsStr(type_, true));
        prefDefAdd("as%s", typeAsStr(type_, true));
        print("\n");
        return;
    }

    print("/// @brief Matrix of %s of size %u x %u\n", ctypeAsStr(ctype), r, c);
    print("typedef union {\n    %s data[%u * %u];\n    %s m[%u][%u];\n    struct {\n", ctypeAsStr(ctype), r, c, ctypeAsStr(ctype), r, c);
    
    for (usize i = 0; i < c; ++i) {
        print("        %s m%u%u", ctypeAsStr(ctype), i, 0);
        for (usize j = 1; j < r; ++j) {
            print(", m%u%u", i, j);
        }
        print(";\n");
    }
    print("    };\n    struct { %s r0", typeAsStr(V(ctype, c), false));
    for (usize j = 1; j < r; ++j) print(", r%u", j);
    print("; };\n} %s;\n\n", typeAsStr(type_, false));

    pushDefine(f, type_, "_zero", " ((@o){0})");
    if (r == c) {
        char buffer[128];
        for (usize i = 0; i < c; ++i) for (usize j = 0; j < r; ++j) {
            usize I = i * r + j;
            buffer[3*I+0] = '0' + (i == j);
            if (I == r * c - 1) {
                buffer[3*I+1] = '\0';
                goto BREAK;
            }
            buffer[3*I+1] = ',';
            buffer[3*I+2] = ' ';
        }
BREAK:  
        pushDefine(f, type_, "_identity", " ((@o){ %s })", buffer);
    }
    print("\n");
}

void pushMatrixOp(FILE *f, const char *name, func_sig sig, const char *desc, const char *pre, const char *def) {

    if (sig.on.variant == VARIANT_M && (sig.on.as.m.r < 2 || sig.on.as.m.c < 2)) {
        return;
    }
    
    pushFuncCommon(f, name, sig, desc, pre, 0);

    switch (sig.ret.variant) {
        case VARIANT_C: {
            if (def[0] == '%' && def[1] == 'S') def += 2;

            print("return ");
            pushFmtIndex(f, sig, def, .tab = 1);
            print(";");
        } break;

        case VARIANT_V: {
            
            if (def[0] == '%' && def[1] == 'S') { // Single line result
                print("return ");
                pushFmtIndex(f, sig, def + 2, .tab = 1);
                print(";");
            }
            else { // Basic structured result
                print("return (%s) {\n        ", typeAsStr(sig.ret, false));
                pushFmtV(f, sig, 0, def, .tab = 2);
                for (usize i = 1; i < sig.ret.as.v.size; ++i) {
                    print(",\n        ");
                    pushFmtV(f, sig, i, def, .tab = 2);
                }
                print("\n    };");
            }
        } break;

        case VARIANT_M: {

            if (def[0] == '%' && def[1] == 'S') { // Single line result
                print("return ");
                pushFmtIndex(f, sig, def + 2, .tab = 1);
                print(";");
            }
            else { // Basic structured result
                print("return (%s) {\n        ", typeAsStr(sig.ret, false));

                for (usize i = 0; i < sig.ret.as.m.c; ++i) {
                    
                    pushFmtM(f, sig, i, 0, def, .tab = 2);
                    for (usize j = 1; j < sig.ret.as.m.r; ++j) {
                        print(", ");
                        pushFmtM(f, sig, i, j, def, .tab = 2);
                    }
                    if (i == sig.ret.as.m.c - 1) break; 
                    print(",\n        ");
                }
                print("\n    };");
            }
        } break;
    
        default: SL_terminate(-1, "Return type \"%s\" not handled!", typeAsStr(sig.ret, false)); break;
    }

    pushFuncDefinitionEnd(f);
}

int main() {

    c_type ctypes[] = {TYPE_I32, TYPE_I64, TYPE_U32, TYPE_U64, TYPE_FLOAT, TYPE_DOUBLE, TYPE_BOOL};
    const usize ctypes_count = static_count(ctypes);

    #define NB_M_VARIANTS 4
    type mtypes[sizeof(ctypes)/sizeof(c_type) * NB_M_VARIANTS]; // m, m2x2, m3x3, m4x4
    const usize vtypes_count = static_count(mtypes);

    for (usize i = 0; i < ctypes_count; ++i) {
        mtypes[NB_M_VARIANTS * i + 0] = (type) {
            .variant = VARIANT_M,
            .ptr = 0,
            .as.m = (mat_type) {
                .r = 0,
                .c = 0,
                .type = ctypes[i]
            }
        };
        for (usize j = 1; j < NB_M_VARIANTS; ++j) {
            mtypes[NB_M_VARIANTS * i + j] = (type) {
                .variant = VARIANT_M,
                .ptr = 0,
                .as.m = (mat_type) {
                    .r = j + 1,
                    .c = j + 1,
                    .type = ctypes[i]
                }
            };
        }
    }

    FILE *f = fopen(S_PATH"SupSyLibraries/include/math/matrix.h", "w");
    print("#ifndef __SL_MATRIX_H\n#define __SL_MATRIX_H\n\n#include \"../base.h\"\n#include \"vector.h\"\n#include \"quaternion.h\"\n\n");
    
    pushDefine_(f, "msize", "(M)      "SL_PREFIX"luv2_(sizeof(((typeof(M) *)NULL)->r0) / sizeof(((typeof(M) *)NULL)->m00), sizeof(((typeof(M) *)NULL)->r0) / sizeof(((typeof(M) *)NULL)->m00))");
    pushDefine_(f, "mget", "(M, i, j) ((M).data[j + i * (M).c])");
    print("\n");
    pushDefine_(f, "XPD_M2X2", "(M) (M).m00, (M).m01, (M).m10, (M).m11");
    pushDefine_(f, "XPD_M3X3", "(M) (M).m00, (M).m01, (M).m02, (M).m10, (M).m11, (M).m12, (M).m20, (M).m21, (M).m22");
    pushDefine_(f, "XPD_M4X4", "(M) (M).m00, (M).m01, (M).m02, (M).m03, (M).m10, (M).m11, (M).m12, (M).m13, (M).m20, (M).m21, (M).m22, (M).m23, (M).m30, (M).m31, (M).m32, (M).m33");
    print("\n");
    pushDefine_(f, "FMT_M2X2", "(fmt, ...) \"[ \"fmt\" \"fmt\" ]\"__VA_ARGS__\"[ \"fmt\" \"fmt\" ]\"");
    pushDefine_(f, "FMT_M3X3", "(fmt, ...) \"[ \"fmt\" \"fmt\" \"fmt\" ]\"__VA_ARGS__\"[ \"fmt\" \"fmt\" \"fmt\" ]\"__VA_ARGS__\"[ \"fmt\" \"fmt\" \"fmt\" ]\"");
    pushDefine_(f, "FMT_M4X4", "(fmt, ...) \"[ \"fmt\" \"fmt\" \"fmt\" \"fmt\" ]\"__VA_ARGS__\"[ \"fmt\" \"fmt\" \"fmt\" \"fmt\" ]\"__VA_ARGS__\"[ \"fmt\" \"fmt\" \"fmt\" \"fmt\" ]\"__VA_ARGS__\"[ \"fmt\" \"fmt\" \"fmt\" \"fmt\" ]\"");
    print("\n\n");


    for (usize i = 0; i < ctypes_count; ++i) {

        char buffer[1024];
        strcpy(buffer, ctypeAsStr(ctypes[i]));
        print("#pragma region %s\n\n", strupper(buffer));
        
        #define ctype C(ctypes[i])
        #define vtype V(ctypes[i], mtype.as.m.c)
        #define vltype V(ctypes[i], mtype.as.m.c - 1)
        #define vtype_(n) V(ctypes[i], 2)
        #define qtype Q(ctypes[i])
        #define mtype mtypes[NB_M_VARIANTS * i + j]

        for (usize j = 0; j < NB_M_VARIANTS; ++j) {
            pushMatDef(f, mtype);
            print("\n");

            if (j == 1) pushDefine(f, mtype, "diag", "(m00_, m11_) ((@o){.m00 = m00_, .m11 = m11_})");
            if (j == 2) pushDefine(f, mtype, "diag", "(m00_, m11_, m22_) ((@o){.m00 = m00_, .m11 = m11_, .m22 = m22_})");
            if (j == 3) pushDefine(f, mtype, "diag", "(m00_, m11_, m22_, m33_) ((@o){.m00 = m00_, .m11 = m11_, .m22 = m22_, .m33 = m33_})");
            
            // if (j == 1) pushDefine(f, mtype, "_", "(m00_, m01_, m10_, m11_) ((@o){.m00 = m00_, .m11 = m11_})");
            // if (j == 2) pushDefine(f, mtype, "_", "(m00_, m01_, m02_, m10_, m11_, m12_, m02_, m12_, m22_) ((@o){.m00 = m00_, .m11 = m11_, .m22 = m22_})");
            // if (j == 3) pushDefine(f, mtype, "_", "(m00_, m11_, m22_, m33_) ((@o){.m00 = m00_, .m11 = m11_, .m22 = m22_, .m33 = m33_})");

            print("\n");

            pushMatrixOp(f, "add",      sig(mtype, mtype, var("lhs", mtype), var("rhs", mtype)), "Addition of two @o", NULL, "# = lhs# + rhs#");
            pushMatrixOp(f, "sub",      sig(mtype, mtype, var("lhs", mtype), var("rhs", mtype)), "Difference of two @o", NULL, "# = lhs# - rhs#");
            
            if (j == 0) {
                // pushVectorOp(f, "mul",      sig(mtype, mtype, var("lhs", mtype), var("rhs", mtype)), "Product of two @o", NULL, "# = lhs# - rhs#");
            }
            else {
                pushMatrixOp(f, "mul",      sig(mtype, mtype, var("lhs", mtype), var("rhs", mtype)), "Product of two @o", 
                    "@o res = "SL_PREFIX"@o_zero;\n"
                    "for (usize k = 0; k < "SL_PREFIX"msize(lhs).x; ++k)\n"
                    "for (usize j = 0; j < "SL_PREFIX"msize(lhs).y; ++j)\n"
                    "for (usize i = 0; i < "SL_PREFIX"msize(lhs).x; ++i)\n"
                    "    res.m[i][j] += lhs.m[i][k] * rhs.m[k][j];\n"
                    ,
                    "%Sres"
                );
                pushMatrixOp(f, "muls",      sig(mtype, mtype, var("lhs", mtype), var("rhs", ctype)), "Component-wise multiplication of a @o with a scalar", NULL, "# = lhs# * rhs");
                pushMatrixOp(f, "mulv",      sig(mtype, vtype, var("lhs", mtype), var("rhs", vtype)), "Product of a @o and a @r", NULL,
                    j == 1 ? "%S"SL_PREFIX"@r_("SL_PREFIX"$rdot(lhs.r0, rhs), "SL_PREFIX"$rdot(lhs.r1, rhs))" :
                    j == 2 ? "%S"SL_PREFIX"@r_("SL_PREFIX"$rdot(lhs.r0, rhs), "SL_PREFIX"$rdot(lhs.r1, rhs), "SL_PREFIX"$rdot(lhs.r2, rhs))" :
                    "%S"SL_PREFIX"@r_("SL_PREFIX"$rdot(lhs.r0, rhs), "SL_PREFIX"$rdot(lhs.r1, rhs), "SL_PREFIX"$rdot(lhs.r2, rhs), "SL_PREFIX"$rdot(lhs.r3, rhs))"
                );
                if (j > 1) {
                    pushMatrixOp(f, "apply",      sig(mtype, V(ctypes[i], mtype.as.m.c - 1), var("m", mtype), var("v", vltype)), "Apply transformation represented by @o to a @r", NULL,
                        j == 2 ? tmpf("%%S"SL_PREFIX"$omulv(m, "SL_PREFIX"%sv(v, 1)).xy",  typeAsStr(vtype, false)) :
                                 tmpf("%%S"SL_PREFIX"$omulv(m, "SL_PREFIX"%sv(v, 1)).xyz", typeAsStr(vtype, false))
                    );
                }
                pushMatrixOp(f, "divs",      sig(mtype, mtype, var("lhs", mtype), var("rhs", ctype)), "Component-wise division of a @o with a scalar", NULL, "# = lhs# / rhs");
            }

            pushMatrixOp(f, "addS",     sig(mtype, mtype, var("lhs", mtype), var("rhs", mtype), var("s", ctype)), "Addition of two @o with lhs scaled by a @V2", NULL, "# = lhs# + rhs# * s");
            pushMatrixOp(f, "subS",     sig(mtype, mtype, var("lhs", mtype), var("rhs", mtype), var("s", ctype)), "Difference of two @o with lhs scaled by a @V2", NULL, "# = lhs# - rhs# * s");

            if (typeIsSigned(mtype)) 
            {
                pushMatrixOp(f, "neg",  sig(mtype, mtype, var("m", mtype)), "Negation of a @o", NULL, "# = -m#");
                pushMatrixOp(f, "abs",  sig(mtype, mtype, var("m", mtype)), "Component-wise absolute value of a @o", NULL, typeIsInt(mtype) ? "# = m# < 0 ? -m# : m#" : "# = fabs(m#)");
            }

            pushMatrixOp(f, "min",      sig(mtype, mtype, var("lhs", mtype), var("rhs", mtype)), "Component-wise minimum of two @o", NULL, "# = lhs# < rhs# ? lhs# : rhs#");
            pushMatrixOp(f, "max",      sig(mtype, mtype, var("lhs", mtype), var("rhs", mtype)), "Component-wise maximum of two @o", NULL, "# = lhs# > rhs# ? lhs# : rhs#");

            if (j == 0) {
                // pushMatrixOp(f, "trsp",     sig(mtype, mtype, var("m", mtype)), "Transposition of a @o", NULL, "# = m->data[i + j * C]");
            }
            else {
                pushMatrixOp(f, "trsp",     sig(mtype, mtype, var("m", mtype)), "Transposition of a @o", 
                    j == 1 ? SL_PREFIX"swap(m.m10, m.m01);" : 
                    j == 2 ? SL_PREFIX"swap(m.m10, m.m01);\n"SL_PREFIX"swap(m.m20, m.m02); "SL_PREFIX"swap(m.m21, m.m12);" : 
                             SL_PREFIX"swap(m.m10, m.m01);\n"SL_PREFIX"swap(m.m20, m.m02); "SL_PREFIX"swap(m.m12, m.m21);\n"SL_PREFIX"swap(m.m30, m.m03); "SL_PREFIX"swap(m.m31, m.m13);"SL_PREFIX"swap(m.m32, m.m23);"
                    , 
                "%Sm");

                pushMatrixOp(f, "trace",    sig(mtype, ctype, var("m", mtype)), "Trace of a @o", NULL,
                    j == 1 ? "%Sm.m00 + m.m11" : 
                    j == 2 ? "%Sm.m00 + m.m11 + m.m22" : 
                             "%Sm.m00 + m.m11 + m.m22 + m.m33"
                );
            }

            if (j == 0) {
                // ...
            }
            else {
                if (j == 1) pushMatrixOp(f, "det_xpd",
                    sig(mtype, ctype, var("m00", ctype), var("m01", ctype), var("m10", ctype), var("m11", ctype)), 
                    "Determinant of a @o", NULL, "%Sm00 * m11 - m01 * m10"
                );
                if (j == 2) pushMatrixOp(f, "det_xpd",
                    sig(mtype, ctype, var("m00", ctype), var("m01", ctype), var("m02", ctype), var("m10", ctype), var("m11", ctype), var("m12", ctype), var("m20", ctype), var("m21", ctype), var("m22", ctype)),
                    "Determinant of a @o", NULL, "%Sm00 * m11 * m22 + m01 * m12 * m20 + m02 * m10 * m21 - m02 * m11 * m20 - m12 * m21 * m00 - m22 * m01 * m10"
                );
                if (j == 3) pushMatrixOp(f, "det_xpd",
                    sig(mtype, ctype, var("m00", ctype), var("m01", ctype), var("m02", ctype), var("m03", ctype), var("m10", ctype), var("m11", ctype), var("m12", ctype), var("m13", ctype), var("m20", ctype), var("m21", ctype), var("m22", ctype), var("m23", ctype), var("m30", ctype), var("m31", ctype), var("m32", ctype), var("m33", ctype)),
                    "Determinant of a @o", NULL, 
                             "%Sm00 * "SL_PREFIX"$Om3x3det_xpd(m11, m12, m13, m21, m22, m23, m31, m32, m33)\n"
                        "     + m01 * "SL_PREFIX"$Om3x3det_xpd(m10, m12, m13, m20, m22, m23, m30, m32, m33)\n"
                        "     + m02 * "SL_PREFIX"$Om3x3det_xpd(m10, m11, m13, m20, m21, m23, m30, m31, m33)\n"
                        "     + m03 * "SL_PREFIX"$Om3x3det_xpd(m10, m11, m12, m20, m21, m22, m30, m31, m32)"
                );
                pushMatrixOp(f, "det", sig(mtype, ctype, var("m", mtype)), "Determinant of a @o", NULL, 
                    j == 1 ? "%S"SL_PREFIX"$odet_xpd("SL_PREFIX"XPD_M2X2(m))" :
                    j == 2 ? "%S"SL_PREFIX"$odet_xpd("SL_PREFIX"XPD_M3X3(m))" :
                                "%S"SL_PREFIX"$odet_xpd("SL_PREFIX"XPD_M4X4(m))"
                );
            }

            ///// INVERSIONS
            if (typeIsReal(mtype)) { // Only matrices of real numbers may be inverted
                
                if (j == 0); //
                if (j == 1) pushMatrixOp(f, "inv", sig(mtype, mtype, var("m", mtype)), "Inverse of a @o",
                    "@o trsp_comat = { .m00 = m.m11, .m10 = -m.m10, .m10 = -m.m10, .m11 = m.m00 };\n"
                    "\n"
                    "@O det = trsp_comat.m00 * m.m00 + trsp_comat.m01 * m.m10;\n"
                    "if (det == 0.0) return __SL_ERROR(SL_ERR_DIVISION_BY_ZERO), "SL_PREFIX"@o_zero;\n"
                    ,
                    "%S"SL_PREFIX"$omuls(trsp_comat, 1.0 / det)"
                );
                if (j == 2) pushMatrixOp(f, "inv", sig(mtype, mtype, var("m", mtype)), "Inverse of a @o",
                    "@o trsp_comat;\n"
                    "for (int i = 0; i < 3; ++i)\n"
                    "for (int j = 0; j < 3; ++j)\n"
                    "{\n"
                    "    trsp_comat.m[j][i] = ((i + j) & 1 ? -1 : 1) *\n"
                    "        "SL_PREFIX"$Om2x2det_xpd(\n"
                    "            m.m[1 - (i >= 1)][1 - (j >= 1)], m.m[1 - (i >= 1)][2 - (j >= 2)],\n"
                    "            m.m[2 - (i >= 2)][1 - (j >= 1)], m.m[2 - (i >= 2)][2 - (j >= 2)]\n"
                    "        );\n"
                    "}\n"
                    "\n"
                    "@O det = trsp_comat.m00 * m.m00 + trsp_comat.m01 * m.m10 + trsp_comat.m02 * m.m20;\n"
                    "if (det == 0.0) return __SL_ERROR(SL_ERR_DIVISION_BY_ZERO), "SL_PREFIX"@o_zero;\n"
                    , 
                    "%S"SL_PREFIX"$omuls(trsp_comat, 1.0 / det)"
                );
                if (j == 3) pushMatrixOp(f, "inv", sig(mtype, mtype, var("m", mtype)), "Inverse of a @o",
                    "@o trsp_comat;\n"
                    "for (int i = 0; i < 4; ++i)\n"
                    "for (int j = 0; j < 4; ++j)\n"
                    "{\n"
                    "    trsp_comat.m[j][i] = ((i + j) & 1 ? -1 : 1) *\n"
                    "        "SL_PREFIX"$Om3x3det_xpd(\n"
                    "            m.m[1 - (i >= 1)][1 - (j >= 1)], m.m[1 - (i >= 1)][2 - (j >= 2)], m.m[1 - (i >= 1)][3 - (j >= 3)],\n"
                    "            m.m[2 - (i >= 2)][1 - (j >= 1)], m.m[2 - (i >= 2)][2 - (j >= 2)], m.m[2 - (i >= 2)][3 - (j >= 3)],\n"
                    "            m.m[3 - (i >= 3)][1 - (j >= 1)], m.m[3 - (i >= 3)][2 - (j >= 2)], m.m[3 - (i >= 3)][3 - (j >= 3)]\n"
                    "        );\n"
                    "}\n"
                    "\n"
                    "@O det = trsp_comat.m00 * m.m00 + trsp_comat.m01 * m.m10 + trsp_comat.m02 * m.m20 + trsp_comat.m03 * m.m30;\n"
                    "if (det == 0.0) return __SL_ERROR(SL_ERR_DIVISION_BY_ZERO), "SL_PREFIX"@o_zero;\n"
                    , 
                    "%S"SL_PREFIX"$omuls(trsp_comat, 1.0 / det)"
                );
            }

            ///// ROTATIONS
            if (typeIsReal(mtype)) {
                if (j == 1) pushMatrixOp(f, "from_angle", sig(mtype, mtype, var("angle", ctype)), "Matrix @o representing a 2D rotation",
                    "double sin, cos; sincos(angle, &sin, &cos);\n"
                    ,
                    "%S(@o) {\n"
                    "    .m00 = -sin, .m01 = cos,\n"
                    "    .m10 =  cos, .m11 = sin\n"
                    "}"
                );
                if (j == 2) {
                    // pushMatrixOp(f, "from_angle", sig(mtype, mtype, var("angle", vtype)), "Matrix @o representing a 3D rotation",
                    //     "double sin, cos; sincos(angle, &sin, &cos);\n"
                    //     ,
                    //     "%S(@o) {\n"
                    //     "    .m00 = -sin, .m01 = cos,\n"
                    //     "    .m10 =  cos, .m11 = sin\n"
                    //     "}"
                    // );
                    pushMatrixOp(f, "from_quat", sig(mtype, mtype, var("quat", qtype)), "Matrix @o from a @V1",
                        "@O wx = quat.w*quat.x, wy = quat.w*quat.y, wz = quat.w*quat.z, xy = quat.x*quat.y, yz = quat.y*quat.z, xz = quat.x*quat.z;\n"
                        "@O w2 = quat.w*quat.w, x2 = quat.x*quat.x, y2 = quat.y*quat.y, z2 = quat.z*quat.z;\n"
                        ,
                        // "%S(@o) {\n"
                        // "    .m00 = w2 + x2 - y2 - z2, .m01 = 2 * (xy - wz),     .m02 = 2 * (xz + wy),\n"
                        // "    .m10 = 2 * (xy + wz),     .m11 = w2 - x2 + y2 - z2, .m12 = 2 * (yz - wx),\n"
                        // "    .m20 = 2 * (xz - wy),     .m21 = 2 * (yz + wx),     .m22 = w2 - x2 - y2 + z2\n"
                        // "}"
                        "%S(@o) {\n"
                        "    .m00 = w2 + x2 - y2 - z2, .m10 = 2 * (xy - wz),     .m20 = 2 * (xz + wy),\n"
                        "    .m01 = 2 * (xy + wz),     .m11 = w2 - x2 + y2 - z2, .m21 = 2 * (yz - wx),\n"
                        "    .m02 = 2 * (xz - wy),     .m12 = 2 * (yz + wx),     .m22 = w2 - x2 - y2 + z2\n"
                        "}"
                    );
                }
            }

            ///// TRANSFORMATIONS
            if (typeIsReal(mtype)) {
                if (j == 2) pushMatrixOp(f, "from_transform", sig(mtype, mtype, var("position", vltype), var("rotation", ctype), var("scale", vltype)), "Matrix @o representing a transformation",
                    "double sin, cos; sincos(rotation, &sin, &cos);\n"
                    ,
                    "%S(@o) {\n"
                    "    .m00 = scale.x * cos, .m01 = scale.y * -sin, .m02 = position.x,\n"
                    "    .m10 = scale.x * sin, .m11 = scale.y *  cos, .m12 = position.y,\n"
                    "    .m20 =           0.0, .m21 =            0.0, .m22 =        1.0\n"
                    "}"
                );
                if (j == 3) pushMatrixOp(f, "from_transform", sig(mtype, mtype, var("position", vltype), var("rotation", qtype), var("scale", vltype)), "Matrix @o representing a transformation",
                    "$Om3x3 rot = "SL_PREFIX"$Om3x3from_quat(rotation);\n"
                    ,
                    "%S(@o) {\n"
                    "    .m00 = scale.x * rot.m00, .m01 = scale.y * rot.m01, .m02 = scale.z * rot.m02, .m03 = position.x,\n"
                    "    .m10 = scale.x * rot.m10, .m11 = scale.y * rot.m11, .m12 = scale.z * rot.m12, .m13 = position.y,\n"
                    "    .m20 = scale.x * rot.m20, .m21 = scale.y * rot.m21, .m22 = scale.z * rot.m22, .m23 = position.z,\n"
                    "    .m30 =               0.0, .m31 =               0.0, .m32 =               0.0, .m33 =        1.0\n"
                    "}"
                );
            }
            ///// PROJECT
            if (typeIsReal(mtype) && j == 3) {
                pushMatrixOp(f, "from_projection", sig(mtype, mtype, var("planes", vtype_(2)), var("view_size", vtype_(2))), "Matrix @o representing a projection",
                    "double idepth = 1.0 / (planes.y - planes.x);\n"
                    ,
                    "%S(@o) {\n"
                    "    .m00 =       planes.x / view_size.x,\n"
                    "    .m11 =       planes.x / view_size.y,\n"
                    "    .m22 =      (planes.y + planes.x) * idepth, .m32 = 1.0,\n"
                    "    .m23 = -2 * (planes.y * planes.x) * idepth\n"
                    "}"
                );
            }
            
            /// TODO: dot product (standard like vector)
            /// TODO: rot by angle for 2x2 matrix, rot angle-axis + rot quaternion + rot euler angles for 3x3 matrix

            print("\n\n\n");
        }

        print("#pragma endregion %s\n", buffer);
    }

    pushStripPrefix(f);

    print("\n#endif // __SL_MATRIX_H");
    fclose(f);

    return 0;
}
