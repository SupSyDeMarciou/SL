#define SL_GEN_MAIN
#define SL_IMPLEMENTATION
#include "../generate.h"

void pushVectorDef(FILE *f, type vtype) {

    type ctype = C(vtype.as.v.type);
    usize size = vtype.as.v.size;

    if (ctype.as.c > __TYPE_ALIAS__) // Is aliased type
    {
        type vtype_p = V(ctype_alias[ctype.as.c], size);
        char temp[512];

        push("typedef %s %s;\n", typeAsStr(vtype_p, false), typeAsStr(vtype, true));
        if (size < 2) return;
        
        pushDefine(f, vtype, "_zero", "  "SL_PREFIX"%s_zero", typeAsStr(vtype_p, true));
        pushDefine(f, vtype, "_one", "   "SL_PREFIX"%s_one", typeAsStr(vtype_p, true));
        if (size == 4) return;

        pushDefine(f, vtype, "_right", " "SL_PREFIX"%s_right", typeAsStr(vtype_p, true));
        pushDefine(f, vtype, "_up", "    "SL_PREFIX"%s_up", typeAsStr(vtype_p, true));
        if (size > 2) pushDefine(f, vtype, "_forw", "  "SL_PREFIX"%s_forw", typeAsStr(vtype_p, true));
        
        if (!typeIsSigned(vtype)) return;
        pushDefine(f, vtype, "_left", "  "SL_PREFIX"%s_left", typeAsStr(vtype_p, true));
        pushDefine(f, vtype, "_down", "  "SL_PREFIX"%s_down", typeAsStr(vtype_p, true));
        if (size > 2) pushDefine(f, vtype, "_back", "  "SL_PREFIX"%s_back", typeAsStr(vtype_p, true));
        
        return;
    }

    if (vtype.as.v.size < 2) // Is arbitrary size
    {
        push("/// @brief Vector of %s with arbitrary dimension\n", typeAsStr(ctype, false));
        push("typedef struct {\n    const usize count;\n    %s *data;\n} %sv;\n\n", typeAsStr(ctype, false), typeAsStr(ctype, true));
        return;
    }

    const char *ctype_s  = typeAsStr(ctype, false);
    const char *ctype_f  = typeAsStr(ctype, true);
    const char *vtype2_s = typeAsStr(V(ctype.as.c, 2), false);
    const char *vtype3_s = typeAsStr(V(ctype.as.c, 3), false);

    push("/// @brief Vector of %s with dimension %zu\n", ctype_s, size);
    push("typedef union {\n    %s data[%zu];\n", ctype_s, size);
    switch (size) {
        case 2: {
            push("    struct {\n        union { %s x, r, u; };\n        union { %s y, g, v; };\n    };\n", ctype_s, ctype_s);  
        } break;
        case 3: {
            push("    struct {\n        union { %s x, r, u; };\n        union { %s y, g, v; };\n        union { %s z, b, s; };\n    };\n", ctype_s, ctype_s, ctype_s);
            push("    struct {\n        union { %s __x, __r, __u; };\n        union { %s yz, gb, vs; };\n    };\n", ctype_s, vtype2_s);
            push("    struct {\n        union { %s xy, rg, uv; };\n        union { %s __z, __b, __s; };\n    };\n", vtype2_s, ctype_s);
        } break;
        case 4: {
            push("    struct {\n        union { %s x, r, u; };\n        union { %s y, g, v; };\n        union { %s z, b, s; };\n        union { %s w, a, t; };\n    };\n", ctype_s, ctype_s, ctype_s, ctype_s);
            push("    struct {\n        union { %s __x0, __r0, __u0; };\n        union { %s yz, gb, vs; };\n        union { %s __w0, __a0, __t0; };\n    };\n", ctype_s, vtype2_s, ctype_s);
            push("    struct {\n        union { %s xy, rb, uv; };\n        union { %s zw, ba, st; };\n    };\n", vtype2_s, vtype2_s);
            push("    struct {\n        union { %s xyz, rgb, uvs; };\n        union { %s __w1, __a1, __t1; };\n    };\n", vtype3_s, ctype_s);
            push("    struct {\n        union { %s __x1, __r1, __u1; };\n        union { %s yzw, gba, vst; };\n    };\n", ctype_s, vtype3_s);
        } break;
    }
    push("} %s;\n", typeAsStr(vtype, false));
    push("\n");

    switch (size) {
        case 2: {
            pushDefine(f, vtype, "_zero",   "  ((@o){.x =  0, .y =  0})");
            pushDefine(f, vtype, "_one",   "   ((@o){.x =  1, .y =  1})");
            pushDefine(f, vtype, "_right",   " ((@o){.x =  1, .y =  0})");
            pushDefine(f, vtype, "_up",   "    ((@o){.x =  0, .y =  1})");
            if (!typeIsSigned(vtype)) break;

            pushDefine(f, vtype, "_left",   "  ((@o){.x = -1, .y =  0})");
            pushDefine(f, vtype, "_down",   "  ((@o){.x =  0, .y = -1})");
        } break;
        case 3: {
            pushDefine(f, vtype, "_zero",   "  ((@o){.x =  0, .y =  0, .z =  0})");
            pushDefine(f, vtype, "_one",   "   ((@o){.x =  1, .y =  1, .z =  1})");
            pushDefine(f, vtype, "_right",   " ((@o){.x =  1, .y =  0, .z =  0})");
            pushDefine(f, vtype, "_up",   "    ((@o){.x =  0, .y =  1, .z =  0})");
            pushDefine(f, vtype, "_forw",   "  ((@o){.x =  0, .y =  0, .z =  1})");
            if (!typeIsSigned(vtype)) break;
            
            pushDefine(f, vtype, "_left",   "  ((@o){.x = -1, .y =  0, .z =  0})");
            pushDefine(f, vtype, "_down",   "  ((@o){.x =  0, .y = -1, .z =  0})");
            pushDefine(f, vtype, "_back",   "  ((@o){.x =  0, .y =  0, .z = -1})");
        } break;
        case 4: {
            pushDefine(f, vtype, "_zero",   "  ((@o){.x = 0, .y = 0, .z = 0, .w = 0})");
            pushDefine(f, vtype, "_one",   "   ((@o){.x = 1, .y = 1, .z = 1, .w = 1})");
            push("\n");
            pushDefine(f, vtype, "_white",   "  ((@o){.x = 1, .y = 1, .z = 1, .w = 1})");
            pushDefine(f, vtype, "_black",   "  ((@o){.x = 0, .y = 0, .z = 0, .w = 1})");
            pushDefine(f, vtype, "_red",   "    ((@o){.x = 1, .y = 0, .z = 0, .w = 1})");
            pushDefine(f, vtype, "_green",   "  ((@o){.x = 0, .y = 1, .z = 0, .w = 1})");
            pushDefine(f, vtype, "_blue",   "   ((@o){.x = 0, .y = 0, .z = 1, .w = 1})");
            pushDefine(f, vtype, "_yellow",   " ((@o){.x = 1, .y = 1, .z = 0, .w = 1})");
            pushDefine(f, vtype, "_cyan",   "   ((@o){.x = 0, .y = 1, .z = 1, .w = 1})");
            pushDefine(f, vtype, "_purple",   " ((@o){.x = 1, .y = 0, .z = 1, .w = 1})");
        } break;
    }
    push("\n");
}

void pushVectorOp(FILE *f, const char *name, func_sig sig, const char *desc, const char *pre, const char *def)
{
    const usize size = sig.on.as.v.size;
    const type ctype = C(sig.on.as.v.type);

    if (sig.on.as.c > __TYPE_ALIAS__) { // TYPE ALIAS : define everything
        if (size < 2) {
            char new_name[32]; snprintf(new_name, 32, "%s_", name);
            pushDefine(f, sig.on, new_name, " "SL_PREFIX"%s%s", typeAsStr(V(ctype_alias[sig.on.as.v.type], size), true), new_name);
        }
        pushDefine(f, sig.on, name, " "SL_PREFIX"%s%s", typeAsStr(V(ctype_alias[sig.on.as.v.type], size), true), name);
        return;
    }

    
    if (sig.on.variant == VARIANT_V && size < 2) // Special handeling of the long vector types
    {
        bool returns_scalar = sig.ret.variant == VARIANT_C;
        var new_vars[sig.vars.count + 2];
        memcpy(new_vars, sig.vars.data, sizeof(var) * sig.vars.count);
        sig.vars = slice_(var, sig.vars.count, new_vars);
        
        if (!returns_scalar) new_vars[sig.vars.count++] = var("dest", sig.on);
        new_vars[sig.vars.count++] = var("count", C(TYPE_USIZE));
        


        aforeach(var, sig.vars) if (var->type.variant == VARIANT_V) (var->type.variant = VARIANT_C), ++var->type.ptr;
        if (sig.ret.variant == VARIANT_V) (sig.ret.variant = VARIANT_C), ++sig.ret.ptr;
        char new_name[128];  strcat(strcpy(new_name, name), "_");
        char new_desc[512];  strcat(strcpy(new_desc, desc), "\nnote All vectors are assumed to be of size \'count\'");
        if (!returns_scalar) strcat(new_desc, "\nnote Result is stored in \'dest\' (which is returned to allow chaining function calls)");
        pushFuncCommon(f, new_name, sig, new_desc, pre, 0);
        {
            if (def[0] == '%' && def[1] == 'S') { // Single line result
                push("return ");
                pushFmtIndex(f, sig, def + 2, .tab = 1);
                push(";");
            }
            else {
                push("for (usize i = 0; i < count; ++i) dest");
                pushFmtIndex(f, sig, def);
                push(";\n    return dest;");
            }
        }
        pushFuncDefinitionEnd(f);



        --sig.vars.count;
        aforeach(var, sig.vars) if (var->type.ptr > 0) (var->type.variant = VARIANT_V), --var->type.ptr;
        if (sig.ret.ptr > 0) (sig.ret.variant = VARIANT_V), --sig.ret.ptr;
        if (!returns_scalar) strcat(strcpy(new_desc, desc), "\nnote Result is stored in \'dest\' (which is returned to allow chaining function calls)");
        pushFuncCommon(f, name, sig, new_desc, NULL, 0);
        {
            if (returns_scalar) push("return SL_%s%s_(", typeAsStr(sig.on, true), name);
            else push("(void)SL_%s%s_(", typeAsStr(sig.on, true), name);
            
            aforeach(var, sig.vars) {
                if (var->type.variant == VARIANT_V) push("%s.data, ", var->name); 
                else push("%s, ", var->name);
            }
    
            if (returns_scalar) push("%s.count);", sig.vars.data[0].name);
            else push("dest.count);\n    return dest;");
        }
        pushFuncDefinitionEnd(f);
        
        return;
    }
    
    pushFuncCommon(f, name, sig, desc, pre, 0);
    switch (sig.ret.variant) {
        case VARIANT_C: {
            if (def[0] == '%' && def[1] == 'S') def += 2;

            push("return ");
            pushFmtIndex(f, sig, def, .tab = 1);
            push(";");
        } break;

        case VARIANT_V: {
            
            if (def[0] == '%' && def[1] == 'S') { // Single line result
                push("return ");
                pushFmtIndex(f, sig, def + 2, .tab = 1);
                push(";");
            }
            else { // Basic structured result
                push("return (%s) {\n        ", typeAsStr(sig.ret, false));
                pushFmtV(f, sig, 0, def, .tab = 2);
                for (usize i = 1; i < sig.ret.as.v.size; ++i) {
                    push(",\n        ");
                    pushFmtV(f, sig, i, def, .tab = 2);
                }
                push("\n    };");
            }
        } break;
    
        default: SL_terminate(-1, "Return type \"%s\" not handled!", typeAsStr(sig.ret, false)); break;
    }
    pushFuncDefinitionEnd(f);
}

int main() {

    const c_type ctypes[] = { TYPE_I8, TYPE_I16, TYPE_I32, TYPE_I64, TYPE_U8, TYPE_U16, TYPE_U32, TYPE_U64, TYPE_FLOAT, TYPE_DOUBLE, TYPE_BOOL, TYPE_I, TYPE_U, TYPE_LI, TYPE_LU };
    const usize ctypes_count = sa_count(ctypes);

    type vtypes[ctypes_count * 4]; // v2, v3, v4, [v and ctype *]
    const usize vtypes_count = sa_count(vtypes);

    for (usize i = 0; i < ctypes_count; ++i)
    for (usize j = 0; j < 4; ++j)
        vtypes[j + i * 4] = V(ctypes[i], j == 0 ? 0 : j + 1);

    FILE *f = openFile("math/vector.h");
    push("#ifndef _SL_VECTOR_H_\n#define _SL_VECTOR_H_\n\n#include <SL/base.h>\n#include <SL/math/math.h>\n\n");

    pushDefine_(f, "XPD_V", "(V)  (V).count, (V).data");
    pushDefine_(f, "XPD_V2", "(V) (V).x, (V).y");
    pushDefine_(f, "XPD_V3", "(V) (V).x, (V).y, (V).z");
    pushDefine_(f, "XPD_V4", "(V) (V).x, (V).y, (V).z, (V).w");
    push("\n");
    pushDefine_(f, "FMT_V2", "(fmt) \"v2(\"fmt\", \"fmt\")\"");
    pushDefine_(f, "FMT_V3", "(fmt) \"v3(\"fmt\", \"fmt\", \"fmt\")\"");
    pushDefine_(f, "FMT_V4", "(fmt) \"v4(\"fmt\", \"fmt\", \"fmt\", \"fmt\")\"");
    push("\n");
    // pushDefine_(f, "vsize", "(V) ((sizeof(V) / sizeof(((typeof(V) *)(NULL))->data[0])) == 1 ? *(usize*)&(V) : (sizeof(V) / sizeof(((typeof(V) *)(NULL))->data[0])))");
    pushDefine_(f, "vsize", "(V) (sizeof(V) / sizeof(((typeof(V) *)(NULL))->data[0]))");
    push("\n");
    
    for (usize i = 0; i < ctypes_count; ++i)
    {
        #define ctype     C(ctypes[i])
        #define ctype_p   C(ctype_parent[ctypes[i]])
        #define vtype_(j) vtypes[4 * i + j]
        #define vtype     vtypes[4 * i + j]

        push("#pragma region %s\n\n", strupper(tmpf(typeAsStr(ctype, false))));
        
        for (usize j = 0; j < 4; ++j) pushVectorDef(f, vtype);
        push("\n\n");

        pushDefine(f, vtype_(1), "_", "(X, Y)       ((@o){.x = X, .y = Y})");
        pushDefine(f, vtype_(2), "_", "(X, Y, Z)    ((@o){.x = X, .y = Y, .z = Z})");
        pushDefine(f, vtype_(3), "_", "(X, Y, Z, W) ((@o){.x = X, .y = Y, .z = Z, .w = W})");
        push("\n");
        pushDefine(f, vtype_(1), "s", "(S)          ((@o){.x = S, .y = S})");
        pushDefine(f, vtype_(2), "s", "(S)          ((@o){.x = S, .y = S, .z = S})");
        pushDefine(f, vtype_(3), "s", "(S)          ((@o){.x = S, .y = S, .z = S, .w = S})");
        push("\n");
        pushDefine(f, vtype_(0), "v", "(V)           ((@o){.count = vsize(V), .data = (V).data})");
        pushDefine(f, vtype_(1), "v", "(V, ...)     ((@o){.x = (V).x, .y = (V).y})");
        pushDefine(f, vtype_(2), "v", "(V, ...)     ((@o){.x = (V).x, .y = (V).y, .z = ("SL_PREFIX"vsize(V) >= 3 ? (V).data[2] : (0, ##__VA_ARGS__))})");
        pushDefine(f, vtype_(3), "v", "(V, ...)     ((@o){.x = (V).x, .y = (V).y, .z = ("SL_PREFIX"vsize(V) >= 3 ? (V).data[2] : ((const float[]){0, ##__VA_ARGS__, 0})[1]), .w = ("SL_PREFIX"vsize(V) >= 4 ? (V).data[3] : ((const float[]){0, ##__VA_ARGS__, 0, 0})[2])})");

        push("\n\n\n");
        
        // Equality
        {
            pushVectorOp(f, "equ", sig(vtype_(0), BOOL, var("lhs", vtype_(0)), var("rhs", vtype_(0))), "Equality of two @o", "@r dest = true;", " &= lhs# == rhs#");
            pushVectorOp(f, "equ", sig(vtype_(1), BOOL, var("lhs", vtype_(1)), var("rhs", vtype_(1))), "Equality of two @o", NULL, "%Slhs.x == rhs.x && lhs.y == rhs.y");
            pushVectorOp(f, "equ", sig(vtype_(2), BOOL, var("lhs", vtype_(2)), var("rhs", vtype_(2))), "Equality of two @o", NULL, "%Slhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z");
            pushVectorOp(f, "equ", sig(vtype_(3), BOOL, var("lhs", vtype_(3)), var("rhs", vtype_(3))), "Equality of two @o", NULL, "%Slhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w");
        }
        for (usize j = 0; j < 4; ++j) pushVectorOp(f, "add",        sig(vtype, vtype, var("lhs", vtype), var("rhs", vtype)), "Addition of two @o", NULL, "# = lhs# + rhs#");
        for (usize j = 0; j < 4; ++j) pushVectorOp(f, "sub",        sig(vtype, vtype, var("lhs", vtype), var("rhs", vtype)), "Difference of two @o", NULL, "# = lhs# - rhs#");
        for (usize j = 0; j < 4; ++j) pushVectorOp(f, "mul",        sig(vtype, vtype, var("lhs", vtype), var("rhs", vtype)), "Component-wise multiplication of two @o", NULL, "# = lhs# * rhs#");
        for (usize j = 0; j < 4; ++j) pushVectorOp(f, "muls",       sig(vtype, vtype, var("lhs", vtype), var("rhs", ctype)), "Component-wise multiplication of a @o with a scalar", NULL, "# = lhs# * rhs");
        for (usize j = 0; j < 4; ++j) pushVectorOp(f, "div",        sig(vtype, vtype, var("lhs", vtype), var("rhs", vtype)), "Component-wise division of two @o", NULL, "# = lhs# / rhs#");
        for (usize j = 0; j < 4; ++j) pushVectorOp(f, "divs",       sig(vtype, vtype, var("lhs", vtype), var("rhs", ctype)), "Component-wise division of a @o with a scalar", NULL, "# = lhs# / rhs");
        for (usize j = 0; j < 4; ++j) pushVectorOp(f, "addS",       sig(vtype, vtype, var("lhs", vtype), var("rhs", vtype), var("s", ctype)), "Addition of two @o with lhs scaled by a @V2", NULL, "# = lhs# + rhs# * s");
        for (usize j = 0; j < 4; ++j) pushVectorOp(f, "subS",       sig(vtype, vtype, var("lhs", vtype), var("rhs", vtype), var("s", ctype)), "Difference of two @o with lhs scaled by a @V2", NULL, "# = lhs# - rhs# * s");
        for (usize j = 0; j < 4; ++j) pushVectorOp(f, "addM",       sig(vtype, vtype, var("lhs", vtype), var("rhs", vtype), var("m", vtype)), "Addition of two @o with lhs multiplied with a @V2", NULL, "# = lhs# + rhs# * m#");
        for (usize j = 0; j < 4; ++j) pushVectorOp(f, "subM",       sig(vtype, vtype, var("lhs", vtype), var("rhs", vtype), var("m", vtype)), "Difference of two @o with lhs multiplied with a @V2", NULL, "# = lhs# - rhs# * m#");
        for (usize j = 0; j < 4; ++j) pushVectorOp(f, "addSM",      sig(vtype, vtype, var("lhs", vtype), var("rhs", vtype), var("s", ctype), var("m", vtype)), "Addition of two @o with lhs scaled by @V2 and multiplied with a @V3", NULL, "# = lhs# + rhs# * s * m#");
        for (usize j = 0; j < 4; ++j) pushVectorOp(f, "subSM",      sig(vtype, vtype, var("lhs", vtype), var("rhs", vtype), var("s", ctype), var("m", vtype)), "Difference of two @o with lhs scaled by @V2 and multiplied with a @V3", NULL, "# = lhs# - rhs# * s * m#");
        for (usize j = 0; j < 4; ++j) pushVectorOp(f, "Sadd",       sig(vtype, vtype, var("lhs", vtype), var("s", ctype), var("rhs", vtype)), "Addition of two @o with rhs scaled by a @V1", NULL, "# = lhs# * s + rhs#");
        for (usize j = 0; j < 4; ++j) pushVectorOp(f, "Ssub",       sig(vtype, vtype, var("lhs", vtype), var("s", ctype), var("rhs", vtype)), "Difference of two @o with rhs scaled by a @V1", NULL, "# = lhs# * s - rhs#");
        for (usize j = 0; j < 4; ++j) pushVectorOp(f, "mix",        sig(vtype, vtype, var("lhs", vtype), var("lhs_w", ctype), var("rhs", vtype), var("rhs_w", ctype)), "Weighted sum of two @o", NULL, "# = lhs# * lhs_w + rhs# * rhs_w");
        
        if (typeIsSigned(ctype)) { // Signed vector functions only
            for (usize j = 0; j < 4; ++j) pushVectorOp(f, "neg",    sig(vtype, vtype, var("v", vtype)), "Negation of a @o", NULL, "# = -v#");
            for (usize j = 0; j < 4; ++j) pushVectorOp(f, "abs",    sig(vtype, vtype, var("v", vtype)), "Component-wise absolute value of a @o", NULL, typeIsInt(ctype) ? "# = v# < 0 ? -v# : v#" : "# = fabs(v#)");
        }
        
        for (usize j = 0; j < 4; ++j) pushVectorOp(f, "min",        sig(vtype, vtype, var("lhs", vtype), var("rhs", vtype)), "Component-wise minimum of two @o", NULL, "# = lhs# < rhs# ? lhs# : rhs#");
        for (usize j = 0; j < 4; ++j) pushVectorOp(f, "max",        sig(vtype, vtype, var("lhs", vtype), var("rhs", vtype)), "Component-wise maximum of two @o", NULL, "# = lhs# > rhs# ? lhs# : rhs#");
        
        { // Dot product
            pushVectorOp(f, "dot",          sig(vtype_(0), ctype_p, var("lhs", vtype_(0)), var("rhs", vtype_(0))), "Dot product of two @o", "@r dest = 0;", " += lhs# * rhs#");
            pushVectorOp(f, "dot",          sig(vtype_(1), ctype_p, var("lhs", vtype_(1)), var("rhs", vtype_(1))), "Dot product of two @o", NULL, "lhs.x * rhs.x + lhs.y * rhs.y");
            pushVectorOp(f, "dot",          sig(vtype_(2), ctype_p, var("lhs", vtype_(2)), var("rhs", vtype_(2))), "Dot product of two @o", NULL, "lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z");
            pushVectorOp(f, "dot",          sig(vtype_(3), ctype_p, var("lhs", vtype_(3)), var("rhs", vtype_(3))), "Dot product of two @o", NULL, "lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w");
        }
        const char *pre = typeIsSigned(ctype) ? "v = "SL_PREFIX"$v0abs(v);" : NULL;
        { // Infinite length (max component)
            pushVectorOp(f, "len_max",  sig(vtype_(0), ctype_p, var("v", vtype_(0))), "Maximum component of a @o", "@r dest = 0;", 
                typeIsReal(ctype) ? " = fabs(v#) > dest ? fabs(v#) : dest" :
                typeIsSigned(ctype) ? " = llabs(v#) > dest ? llabs(v#) : dest" : 
                " = v# > dest ? v# : dest"
            );
            pushVectorOp(f, "len_max",  sig(vtype_(1), ctype_p, var("v", vtype_(1))), "Maximum component of a @o", pre, "v.x > v.y ? v.x : v.y");
            pushVectorOp(f, "len_max",  sig(vtype_(2), ctype_p, var("v", vtype_(2))), "Maximum component of a @o", pre, "v.x > v.y ? (v.x > v.z ? v.x : v.z) : (v.y > v.z ? v.y : v.z)");
            pushVectorOp(f, "len_max",  sig(vtype_(3), ctype_p, var("v", vtype_(3))), "Maximum component of a @o", pre, "v.x > v.y ? (v.x > v.z ? (v.x > v.w ? v.x : v.w) : (v.z > v.w ? v.z : v.w)) : (v.y > v.z ? (v.y > v.w ? v.y : v.w) : (v.z > v.w ? v.z : v.w))");
        }
        { // Manhattan (or taxicab) length
            pushVectorOp(f, "len_manh", sig(vtype_(0), ctype_p, var("v", vtype_(0))), "Manhattan (or taxicab) length of a @o", "@r dest = 0;", 
                typeIsReal(ctype) ? " += fabs(v#)" :
                typeIsSigned(ctype) ? " += llabs(v#)" : 
                " += v#"
            );
            pushVectorOp(f, "len_manh", sig(vtype_(1), ctype_p, var("v", vtype_(1))), "Manhattan (or taxicab) length of a @o", pre, "v.x + v.y");
            pushVectorOp(f, "len_manh", sig(vtype_(2), ctype_p, var("v", vtype_(2))), "Manhattan (or taxicab) length of a @o", pre, "v.x + v.y + v.z");
            pushVectorOp(f, "len_manh", sig(vtype_(3), ctype_p, var("v", vtype_(3))), "Manhattan (or taxicab) length of a @o", pre, "v.x + v.y + v.z + v.w");
        }
        /***************************/ pushVectorOp(f, "len_srq",    sig(vtype_(0), ctype_p, var("v", vtype_(0))), "Squared euclidean length of a @o", NULL, "%S"SL_PREFIX"$odot_(v, v, count)");
        for (usize j = 1; j < 4; ++j) pushVectorOp(f, "len_sqr",    sig(vtype,     ctype_p, var("v", vtype)), "Square length of a @o", NULL, SL_PREFIX"$odot(v, v)");

        /***************************/ pushVectorOp(f, "len",        sig(vtype_(0), F64, var("v", vtype_(0))), "Euclidean length of a @o", NULL, "%Ssqrt("SL_PREFIX"$odot_(v, v, count))");
        for (usize j = 1; j < 4; ++j) pushVectorOp(f, "len",        sig(vtype,     F64, var("v", vtype)), "Euclidean length of a @o", NULL, "sqrt("SL_PREFIX"$odot(v, v))");

        /***************************/ pushVectorOp(f, "dist",       sig(vtype_(0), F64, var("lhs", vtype_(0)), var("rhs", vtype_(0))), "Euclidean distance bewteen two @o", "@r accum = 0;\nfor (int i = 0; i < count; ++i) accum += (lhs[i] - rhs[i]) * (lhs[i] - rhs[i]);", "%Ssqrt(accum)");
        for (usize j = 1; j < 4; ++j) pushVectorOp(f, "dist",       sig(vtype,     F64, var("lhs", vtype), var("rhs", vtype)), "Euclidean distance between two @o", NULL, SL_PREFIX"$olen("SL_PREFIX"$osub(lhs, rhs))");
        
        if (ctype.as.c != TYPE_BOOL) // These operations don't really make sense for booleans
        {
            for (usize j = 1; j < 4; ++j) pushVectorOp(f, "refl",       sig(vtype,     vtype, var("v", vtype), var("n", vtype)), "Reflection of @o v around vector @o n", NULL, "%SSL_$osubS(v, n, 2.0 * SL_$odot(v, n) / SL_$odot(n, n))");
            for (usize j = 1; j < 4; ++j) pushVectorOp(f, "refl_u",     sig(vtype,     vtype, var("v", vtype), var("n", vtype)), "Reflection of @o v around vector @o n assumed to be of unit length", NULL, "%SSL_$osubS(v, n, 2.0 * SL_$odot(v, n))");
            for (usize j = 1; j < 4; ++j) pushVectorOp(f, "align",      sig(vtype,     vtype, var("v", vtype), var("n", vtype)), "Get component of @o v in direction @o n", NULL, "%SSL_$omuls(n, SL_$odot(v, n) / SL_$odot(n, n))");
            for (usize j = 1; j < 4; ++j) pushVectorOp(f, "align_u",    sig(vtype,     vtype, var("v", vtype), var("n", vtype)), "Get component of @o v in direction @o n assumed to be of unit length", NULL, "%SSL_$omuls(n, SL_$odot(v, n))");
            for (usize j = 1; j < 4; ++j) pushVectorOp(f, "proj",       sig(vtype,     vtype, var("v", vtype), var("n", vtype)), "Project @o v on plane with normal @o n",  NULL, "%SSL_$osub(v, SL_$oalign(v, n))");
            for (usize j = 1; j < 4; ++j) pushVectorOp(f, "proj_u",     sig(vtype,     vtype, var("v", vtype), var("n", vtype)), "Project @o v on plane with normal @o n",  NULL, "%SSL_$osub(v, SL_$oalign_u(v, n))");

            for (usize j = 0; j < 4; ++j) pushVectorOp(f, "mods",   sig(vtype, vtype, var("v", vtype), var("n", ctype)), "Component-wise modulo of a @o by scalar n", NULL, typeIsReal(ctype) ? "# = fmod(v#, n)" : "# = v# % n");
            for (usize j = 0; j < 4; ++j) pushVectorOp(f, "mod",    sig(vtype, vtype, var("v", vtype), var("n", vtype)), "Component-wise modulo of a @o by @o n", NULL, typeIsReal(ctype) ? "# = fmod(v#, n#)" : "# = v# % n#");
        }

        if (typeIsReal(ctype)) // Only floating point vector may be properly normalized and have other continous operations performed on
        {
            /***************************/ pushVectorOp(f, "norm",   sig(vtype_(0), vtype_(0), var("v", vtype_(0))), "Normalization of a @o", "double inv_len = 1.0 / "SL_PREFIX"$olen_(v, count);", "# = v# * inv_len");
            for (usize j = 1; j < 4; ++j) pushVectorOp(f, "norm",   sig(vtype, vtype, var("v", vtype)), "Normalization of a @o", "double inv_len = 1.0 / "SL_PREFIX"@olen(v);", "# = v# * inv_len");
            
            for (usize j = 0; j < 4; ++j) pushVectorOp(f, "floor",  sig(vtype, vtype, var("v", vtype)), "Component-wise flooring of a @o", NULL, "# = floor(v#)");
            for (usize j = 0; j < 4; ++j) pushVectorOp(f, "ceil",   sig(vtype, vtype, var("v", vtype)), "Component-wise ceiling of a @o", NULL, "# = ceil(v#)");
            for (usize j = 0; j < 4; ++j) pushVectorOp(f, "frac",   sig(vtype, vtype, var("v", vtype)), "Component-wise fractional part of a @o", NULL, "# = v# - floor(v#)");
            for (usize j = 0; j < 4; ++j) pushVectorOp(f, "lerp",   sig(vtype, vtype, var("lhs", vtype), var("rhs", vtype), var("t", ctype)), "Linear interpolation of two @o", NULL, "# = lhs# + (rhs# - lhs#) * t");
            for (usize j = 1; j < 4; ++j) pushVectorOp(f, "serp",   sig(vtype, vtype, var("lhs", vtype), var("rhs", vtype), var("t", ctype)), "Spherical interpolation of two @o", "@O angle = acos("SL_PREFIX"$odot("SL_PREFIX"$onorm(lhs), "SL_PREFIX"$onorm(rhs)));\n@O inv_sin = 1.0 / sin(angle);\n@O a = sin(angle * t) * inv_sin;\n@O b = sin(angle * (1 - t)) * inv_sin;", "# = lhs# * a + rhs# * b");
            
            pushVectorOp(f, "angle",         sig(vtype_(1), F64,       var("v", vtype_(1))), "Angle on the 2D plane formed by a @o", NULL, "%Satan2(v.y, v.x)");
            pushVectorOp(f, "from_angle",    sig(vtype_(1), vtype_(1), var("angle", ctype)), "Unit @o oriented based on given angle", "double c, s; sincos(angle, &s, &c);", "%S"SL_PREFIX"$o_(c, s)");
            pushVectorOp(f, "from_yawPitch", sig(vtype_(2), vtype_(2), var("yaw", ctype), var("pitch", ctype)), "Unit @o oriented based on given angles", "double cy, sy; sincos(yaw, &sy, &cy);\ndouble cp, sp; sincos(pitch, &sp, &cp);", "%S"SL_PREFIX"$o_(sy * cp, sp, cy * cp)");
            pushVectorOp(f, "rot_sc",        sig(vtype_(1), vtype_(1), var("v", vtype_(1)), var("sina", ctype), var("cosa", ctype)), "Rotate @o by angle encoded by `cosa` and `sina`", NULL, "%S"SL_PREFIX"$o_(v.x * cosa - v.y * sina, v.y * cosa + v.x * sina)");
            pushVectorOp(f, "rot_cs",        sig(vtype_(1), vtype_(1), var("v", vtype_(1)), var("cs", vtype_(1))), "Rotate @o by angle encoded in vector `cs`", NULL, "%S"SL_PREFIX"$o_(v.x * cs.x - v.y * cs.y, v.x * cs.y + v.y * cs.x)");
            pushVectorOp(f, "rot",           sig(vtype_(1), vtype_(1), var("v", vtype_(1)), var("a", ctype)), "Rotate @o by angle", "double sina, cosa; sincos(a, &sina, &cosa);", "%S"SL_PREFIX"$orot_sc(v, sina, cosa)");
        }
        if (typeIsSigned(ctype)) // Cross product only makes sense for signed types
        {
            pushVectorOp(f, "cross",        sig(vtype_(1), ctype_p, var("lhs", vtype_(1)), var("rhs", vtype_(1))), "Cross-product of two @o", NULL, "lhs.x * rhs.y - lhs.y * rhs.x");
            pushVectorOp(f, "cross",        sig(vtype_(2), vtype_(2), var("lhs", vtype_(2)), var("rhs", vtype_(2))), "Cross-product of two @o", NULL, "%S(@o) {\n    .x = lhs.y * rhs.z - lhs.z * rhs.y,\n    .y = lhs.z * rhs.x - lhs.x * rhs.z,\n    .z = lhs.x * rhs.y - lhs.y * rhs.x\n}");
        }

        if (typeIsInt(ctype)) // Binary operations
        {
            for (usize j = 0; j < 4; ++j) pushVectorOp(f, "and",    sig(vtype, vtype, var("lhs", vtype), var("rhs", vtype)), "Component-wise binary AND of two @o",                     NULL, "# = lhs# & rhs#");
            for (usize j = 0; j < 4; ++j) pushVectorOp(f, "or",     sig(vtype, vtype, var("lhs", vtype), var("rhs", vtype)), "Component-wise binary OR of two @o",                      NULL, "# = lhs# | rhs#");
            for (usize j = 0; j < 4; ++j) pushVectorOp(f, "xor",    sig(vtype, vtype, var("lhs", vtype), var("rhs", vtype)), "Component-wise binary XOR of two @o",                     NULL, "# = lhs# ^ rhs#");
            for (usize j = 0; j < 4; ++j) pushVectorOp(f, "not",    sig(vtype, vtype, var("v", vtype)),                      "Component-wise binary NOT of a @o",                       NULL, "# = ~v#");
            for (usize j = 0; j < 4; ++j) pushVectorOp(f, "lshfts", sig(vtype, vtype, var("lhs", vtype), var("rhs", ctype)), "Component-wise binary LEFT-SHIFT of a @o by integer n",   NULL, "# = lhs# << rhs");
            for (usize j = 0; j < 4; ++j) pushVectorOp(f, "lshft",  sig(vtype, vtype, var("lhs", vtype), var("rhs", vtype)), "Component-wise binary LEFT-SHIFT of a @o by @o n",        NULL, "# = lhs# << rhs#");
            for (usize j = 0; j < 4; ++j) pushVectorOp(f, "rshfts", sig(vtype, vtype, var("lhs", vtype), var("rhs", ctype)), "Component-wise binary RIGHT-SHIFT of a @o by interger n", NULL, "# = lhs# >> rhs");
            for (usize j = 0; j < 4; ++j) pushVectorOp(f, "rshft",  sig(vtype, vtype, var("lhs", vtype), var("rhs", vtype)), "Component-wise binary RIGHT-SHIFT of a @o by @o n",       NULL, "# = lhs# >> rhs#");
        }

        push("#pragma endregion %s\n", strupper(tmpf(typeAsStr(ctype, false))));
    }

    // pushImplementation(f);
    pushStripPrefix(f);

    push("\n#endif // _SL_VECTOR_H_\n\n");
    pushGenerationData(f, "vector.h");
    return fclose(f);
}