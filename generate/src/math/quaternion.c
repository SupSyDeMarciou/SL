#define SL_GEN_MAIN
#define SL_IMPLEMENTATION
#include "genmaths.h"

void pushQuatDef(FILE *f, type qtype) {

    print("/// @brief Quaternion of %s\n", ctypeAsStr(qtype.as.c));
    print(
        "typedef union {\n"
        "    %s data[4];\n"
        "    struct { %s a, b, c, d; };\n"
        "    struct { %s w, x, y, z; };\n"
        "    struct { %s r; union { %s iv; struct { %s i, j, k; }; }; };\n"
        "} %sq;\n",
        ctypeAsStr(qtype.as.c), ctypeAsStr(qtype.as.c), ctypeAsStr(qtype.as.c), ctypeAsStr(qtype.as.c), typeAsStr(V(qtype.as.c, 3), false), ctypeAsStr(qtype.as.c), ctypePrefixAsStr(qtype.as.c)
    );
    print("\n");
    pushDefine(f, qtype, "_zero", "     ((@o){0})");
    pushDefine(f, qtype, "_identity", " ((@o){.a = 1, .b = 0, .c = 0, .d = 0})");
    print("\n");
}

void pushQuatOp(FILE *f, const char *name, func_sig sig, const char *desc, const char *pre, const char *def) {
    
    pushFuncCommon(f, name, sig, desc, pre, 0);

    switch (sig.ret.variant) {
        case VARIANT_C: {
            if (def[0] == '%' && def[1] == 'S') def += 2; // Ignore "single line" prefix

            print("return ");
            pushFmtIndex(f, sig, def, .tab = 1);
            print(";");
        } break;

        case VARIANT_Q: {
            if (def[0] == '%' && def[1] == 'S') { // Single line result
                print("return ");
                pushFmtIndex(f, sig, def + 2, .tab = 1);
                print(";");
            }
            else { // Basic structured result
                print("return (%s) {\n        ", typeAsStr(sig.ret, false));
                pushFmtQ(f, sig, 0, def, .tab = 2);
                for (usize i = 1; i < 4; ++i) {
                    print(",\n        ");
                    pushFmtQ(f, sig, i, def, .tab = 2);
                }
                print("\n    };");
            }
        } break;
    
        case VARIANT_V: {
            if (def[0] == '%' && def[1] == 'S') def += 2; // Ignore "single line" prefix

            print("return ");
            pushFmtIndex(f, sig, def, .tab = 1);
            print(";");
        } break;

        default: SL_terminate(-1, "Return type \"%s\" not handled!", typeAsStr(sig.ret, false)); break;
    }

    pushFuncDefinitionEnd(f);
}

int main() {
    
    type qtypes[2] = {Q(TYPE_FLOAT), Q(TYPE_DOUBLE)};
    
    FILE *f = fopen(S_PATH"SupSyLibraries/include/math/quaternion.h", "w");
    print("#ifndef __SL_QUATERNION_H\n#define __SL_QUATERNION_H\n\n#include \"../base.h\"\n\n#include \"math.h\"\n#include \"vector.h\"\n\n");
    
    #define qtype qtypes[i]
    #define ctype C(qtypes[i].as.c)

    pushDefine_(f, "XPD_Q", "(Q) (Q).w, (Q).x, (Q).y, (Q).z");
    pushDefine_(f, "FMT_Q", "(fmt) \"quat(\"fmt\" + \"fmt\"i + \"fmt\"j + \"fmt\"k)\"");

    print("#pragma region ARITHMETIC\n\n");

    for (usize i = 0; i < 2; ++i) pushQuatDef(f, qtype);
    print("\n\n");
    for (usize i = 0; i < 2; ++i) pushDefine(f, qtype, "_", "(R, I, J, K) ((@o){.r = R, .i = I, .j = J, .k = K})");
    for (usize i = 0; i < 2; ++i) pushDefine(f, qtype, "v", "(R, IV)      ((@o){.r = R, .iv = IV})");
    for (usize i = 0; i < 2; ++i) pushDefine(f, qtype, "q", "(Q)          ((@o){"SL_PREFIX"XPD_Q(Q)})");
    print("\n");
    pushDefine(f, qtypes[0], "asfv4", "(Q)     (*($Ov4*)Q.data)");
    pushDefine(f, qtypes[1], "asdv4", "(Q)     (*($Ov4*)Q.data)");
    print("\n\n\n");
    
    for (usize i = 0; i < 2; ++i) pushQuatOp(f, "add",      sig(qtype, qtype, var("lhs", qtype), var("rhs", qtype)), "Addition of two @o", NULL, "# = lhs# + rhs#");
    for (usize i = 0; i < 2; ++i) pushQuatOp(f, "sub",      sig(qtype, qtype, var("lhs", qtype), var("rhs", qtype)), "Difference of two @o", NULL, "# = lhs# - rhs#");
    for (usize i = 0; i < 2; ++i) pushQuatOp(f, "mul",      sig(qtype, qtype, var("lhs", qtype), var("rhs", qtype)), "Multiplication of two @o", NULL, 
        "%S(@o) {\n"
        "    .a = lhs.a*rhs.w - lhs.b*rhs.x - lhs.c*rhs.y - lhs.d*rhs.z,\n"
        "    .b = lhs.a*rhs.x + lhs.b*rhs.w + lhs.c*rhs.z - lhs.d*rhs.y,\n"
        "    .c = lhs.a*rhs.y - lhs.b*rhs.z + lhs.c*rhs.w + lhs.d*rhs.x,\n"
        "    .d = lhs.a*rhs.z + lhs.b*rhs.y - lhs.c*rhs.x + lhs.d*rhs.w\n}"
    );
    for (usize i = 0; i < 2; ++i) pushQuatOp(f, "neg",      sig(qtype, qtype, var("q", qtype)), "Negation of a @o", NULL, "# = -q#");
    for (usize i = 0; i < 2; ++i) pushQuatOp(f, "scale",    sig(qtype, qtype, var("q", qtype), var("s", ctype)), "Component-wise multiplication of a @o with a scalar", NULL, "# = q# * s");
    for (usize i = 0; i < 2; ++i) pushQuatOp(f, "len_sqr",  sig(qtype, F64,   var("q", qtype)), "Canonic squared length of a @o", NULL, "q.a * q.a + q.b * q.b + q.c * q.c + q.d * q.d");
    for (usize i = 0; i < 2; ++i) pushQuatOp(f, "len",      sig(qtype, F64,   var("q", qtype)), "Canonic length of a @o", NULL, i ? "sqrt("SL_PREFIX"$olen_sqr(q))" : "sqrtf("SL_PREFIX"$olen_sqr(q))");
    
    for (usize i = 0; i < 2; ++i) pushQuatOp(f, "norm",     sig(qtype, qtype, var("q", qtype)), "Normalization of a @o", "double inv_len = 1.0 / "SL_PREFIX"$olen(q);", "# = q# * inv_len");
    for (usize i = 0; i < 2; ++i) pushQuatOp(f, "trsp",     sig(qtype, qtype, var("q", qtype)), "Transposition of a @o", NULL, "%S(@o) {\n    .a = q.a,\n    .b = -q.b,\n    .c = -q.c,\n    .d = -q.d\n}");
    for (usize i = 0; i < 2; ++i) pushQuatOp(f, "inv",      sig(qtype, qtype, var("q", qtype)), "Inversion of a @o", "double inv_len = 1.0 / "SL_PREFIX"$olen_sqr(q);", "%S(@o) {\n    .a = q.a * inv_len,\n    .b = -q.b * inv_len,\n    .c = -q.c * inv_len,\n    .d = -q.d * inv_len\n}");
    for (usize i = 0; i < 2; ++i) pushQuatOp(f, "div",      sig(qtype, qtype, var("lhs", qtype), var("rhs", qtype)), "Division of two @o", NULL, "%S"SL_PREFIX"$omul(lhs, "SL_PREFIX"$oinv(rhs))");

    for (usize i = 0; i < 2; ++i) pushQuatOp(f, "exp",      sig(qtype, qtype, var("q", qtype)), "Exponential of a @o", "double ex = exp(q.r);\ndouble angle = "SL_PREFIX"$Ov3len(q.iv);\ndouble sin_angle = angle < 1e-8 ? 0.0 : ex * sin(angle) / angle;", "%S(@o) {\n    .r = ex * cos(angle),\n    .i = q.i * sin_angle,\n    .j = q.j * sin_angle,\n    .k = q.k * sin_angle\n}");
    for (usize i = 0; i < 2; ++i) pushQuatOp(f, "ln",       sig(qtype, qtype, var("q", qtype)), "Logarithm of a @o", "double len = "SL_PREFIX"$olen(q);\ndouble arg = len < 1e-8 ? 0.0 : acos(q.r / len) / "SL_PREFIX"$Ov3len(q.iv);", "%S(@o) {\n    .r = log(len),\n    .i = q.i * arg,\n    .j = q.j * arg,\n    .k = q.k * arg\n}");
    for (usize i = 0; i < 2; ++i) pushQuatOp(f, "ln_u",     sig(qtype, qtype, var("q", qtype)), "Logarithm of a @o of assumed unit length", "double arg = acos(q.r) / "SL_PREFIX"$Ov3len(q.iv);", "%S(@o) {\n    .r = 0,\n    .i = q.i * arg,\n    .j = q.j * arg,\n    .k = q.k * arg\n}");
    for (usize i = 0; i < 2; ++i) pushQuatOp(f, "pow",      sig(qtype, qtype, var("q", qtype), var("t", ctype)), "@o raised to the power of a @v1", 
        "double len = "SL_PREFIX"$olen(q);\n"
        "if (len < 1e-8) return "SL_PREFIX"@o_zero;\n"
        "double len_p = pow(len, t);\n"
        "double len_iv = "SL_PREFIX"$Ov3len(q.iv);\n"
        "if (len_iv < 1e-8) return "SL_PREFIX"@o_(len_p, 0, 0, 0);\n"
        "double arg = acos(q.w / len) * t;\n"
        "double sin_arg = sin(arg) / len_iv * len_p;", 
        "%S(@o) {\n    .w = cos(arg) * len_p,\n    .x = q.x * sin_arg,\n    .y = q.y * sin_arg,\n    .z = q.z * sin_arg\n}"
    );
    for (usize i = 0; i < 2; ++i) pushQuatOp(f, "pow_u",    sig(qtype, qtype, var("q", qtype), var("t", ctype)), "@o of assumed unit length raised to the power of a @v1", "double len_iv = "SL_PREFIX"$Ov3len(q.iv);\nif (len_iv < 1e-8) return "SL_PREFIX"@o_identity;\ndouble arg = acos(q.w) * t;\ndouble sin_arg = sin(arg) / len_iv;", "%S(@o) {\n    .w = cos(arg),\n    .x = q.x * sin_arg,\n    .y = q.y * sin_arg,\n    .z = q.z * sin_arg\n}");

    for (usize i = 0; i < 2; ++i) pushQuatOp(f, "rot", sig(qtype, V(qtype.as.c, 3), var("q", qtype), var("v", V(qtype.as.c, 3))), 
        "Rotation of a @v1 by a @o",
        "@O w2 = q.w * q.w, x2 = q.x * q.x, y2 = q.y * q.y, z2 = q.z * q.z;\n"
        "@O wx = q.w * q.x, wy = q.w * q.y, wz = q.w * q.z, xy = q.x * q.y, yz = q.y * q.z, xz = q.x * q.z;\n",
        "%S"SL_PREFIX"@v1_(\n"
        "    v.x * (w2 + x2 - y2 - z2) + 2 * ((xy + wz) * v.y + (xz - wy) * v.z),\n"
        "    v.y * (w2 - x2 + y2 - z2) + 2 * ((xy - wz) * v.x + (yz + wx) * v.z),\n"
        "    v.z * (w2 - x2 - y2 + z2) + 2 * ((xz + wy) * v.x + (yz - wx) * v.y)\n"
        ")"
    );
    for (usize i = 0; i < 2; ++i) pushQuatOp(f, "slerp", sig(qtype, qtype, var("a", qtype), var("b", qtype), var("t", ctype)), 
        "Spherical interpolation with parameter @v2 t from @o a to @o b\nnote With unit quaternions, this acts as an interpolation between two rotations",
        NULL,
        "%S"SL_PREFIX"$omul(a, "SL_PREFIX"$opow("SL_PREFIX"$omul("SL_PREFIX"$oinv(a), b), t))"
    );
    for (usize i = 0; i < 2; ++i) pushQuatOp(f, "slerp_u", sig(qtype, qtype, var("a", qtype), var("b", qtype), var("t", ctype)), 
        "Spherical interpolation with parameter @v2 t from @o a to @o b, both assumed of unit length\nnote This acts as an interpolation between two rotations, allways following the shortest path",
        "@o inv_a = "SL_PREFIX"$otrsp(a);\n"
        "@o delta_q = "SL_PREFIX"$omul(inv_a, b);\n"
        "if (delta_q.w < 0.0) delta_q = "SL_PREFIX"$omul(inv_a, "SL_PREFIX"$oneg(b));\n",
        "%S"SL_PREFIX"$omul(a, "SL_PREFIX"$opow_u(delta_q, t))"
    );

    print("\n#pragma endregion ARITHMETIC\n#pragma region CONVERSION\n");

    for (usize i = 0; i < 2; ++i) pushQuatOp(f, "from_euler", sig(qtype, qtype, var("yaw", F64), var("pitch", F64), var("roll", F64)), "Unit @o representing XYZ (yaw pitch roll) euler rotation",
    "double sy, cy; sincos(yaw * 0.5, &sy, &cy);\ndouble sp, cp; sincos(pitch * 0.5, &sp, &cp);\ndouble sr, cr; sincos(roll * 0.5, &sr, &cr);",
    "%S(@o) {\n"
    "   .a = cr*cp*cy - sr*sp*sy,\n"
    "   .b = cr*sp*cy - sr*cp*sy,\n"
    "   .c = sr*sp*cy + cr*cp*sy,\n"
    "   .d = sr*cp*cy + cr*sp*sy\n"
    "}");
    for (usize i = 0; i < 2; ++i) pushQuatOp(f, "to_euler", sig(qtype, V(qtype.as.c, 3), var("q", qtype)), "Assumed unit @o to euler angles representing XYZ (yaw pitch roll) rotation",
        "double a =  q.w - q.x,\n"
        "       b =  q.y - q.z,\n"
        "       c =  q.x + q.w,\n"
        "       d = -q.z - q.y;\n"
        "\n"
        "double t1, t3, t1h = 0.0;\n"
        "double t2 = acos(2.0 * (a*a + b*b) / (a*a + b*b + c*c + d*d) - 1.0);\n"
        "double tp = atan2(b, a);\n"
        "double tm = atan2(d, c);\n"
        "\n"
        "if (t2 < 1e-8) {\n"
        "    t1 = t1h;\n"
        "    t3 = 2.0 * tp - t1h;\n"
        "}\n"
        "else if (SL_PI - t2 < 1e-8) {\n"
        "    t1 = t1h;\n"
        "    t3 = 2.0 * tm + t1h;\n"
        "}\n"
        "else {\n"
        "    t1 = tp - tm;\n"
        "    t3 = tp + tm;\n"
        "}\n",
        "(@r) {\n    .x = fmod(t1 + SL_TAU, SL_TAU),\n    .y = fmod(t2 - SL_PI/2 + SL_TAU, SL_TAU),\n    .z = fmod(SL_TAU - t3, SL_TAU)\n}"
    );
    for (usize i = 0; i < 2; ++i) pushQuatOp(f, "from_angleAxis", sig(qtype, qtype, var("angle", F64), var("axis", V(qtype.as.c, 3))), 
        "Unit @o based on angle-axis pair", "double sin_angle = sin(angle *= 0.5);",
        "%S(@o) {\n    .r = cos(angle),\n    .iv = "SL_PREFIX"$v1muls(axis, sin_angle)\n}"
    );
    for (usize i = 0; i < 2; ++i) pushQuatOp(f, "from_fromTo", sig(qtype, qtype, var("from", V(qtype.as.c, 3)), var("to", V(qtype.as.c, 3))), 
        "Unit @o representing the rotation from one @v1 to another @v1",
        "SL_terminate(-1, \"[UNIPMLEMENTED]\");\n"
        "@v0 axis = "SL_PREFIX"$v0cross(from, to);\nif (axis.x || axis.y || axis.z) {\n    float angle = acos("SL_PREFIX"$v0dot(from, to));\n    return "SL_PREFIX"$rfrom_angleAxis(angle, "SL_PREFIX"$v0norm(axis));\n}",
        "%S"SL_PREFIX"@o_identity"
    );

    // TODO: add "from_rotVec"
    // TODO: add "to_rotVec"

    for (usize i = 0; i < 2; ++i) pushQuatOp(f, "from_v4",  sig(qtype, qtype, var("v", V(qtype.as.c, 4))), "@o from a @v0", NULL, "%S(@r) { .w = v.x, .x = v.y, .y = v.z, .z = v.w }");
    for (usize i = 0; i < 2; ++i) pushQuatOp(f, "to_v4",    sig(qtype, V(qtype.as.c, 4), var("q", qtype)), "@o to a @r",    NULL, "%S(@r) { .x = q.w, .y = q.x, .z = q.y, .w = q.z }");

    print("\n#pragma endregion CONVERSION\n");
    pushStripPrefix(f);

    print("\n#endif // __SL_QUATERNION_H");
    fclose(f);

    return 0;
}