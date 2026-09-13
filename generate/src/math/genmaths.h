#ifndef __SL_GEN_MATHS_H
#define __SL_GEN_MATHS_H

#define SL_STRIP_PREFIX
#include "../../../include/math/math.h"
#include "../../../include/misc/io.h"
#include "../../../include/struct/array.h"

#ifdef _WIN32
#   define S_PATH "C:/Users/vlada/Desktop/Coding/C/SupSy/"
#else
#   define S_PATH "/home/supsy/Coding/C/SupSy/"
#endif

#ifdef NO_PREFIX
#   define SL_PREFIX
#else
#   define SL_PREFIX "SL_"
#endif

#pragma region TYPE

typedef enum CType {
    TYPE_VOID = 0,
    TYPE_BOOL,
    TYPE_USIZE,
    TYPE_I8,
    TYPE_U8,
    TYPE_I16,
    TYPE_U16,
    TYPE_I32,
    TYPE_U32,
    TYPE_I64,
    TYPE_U64,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    __TYPE_ALIAS__,
    TYPE_I,
    TYPE_U,
    TYPE_LI,
    TYPE_LU,
} c_type;
static c_type ctype_parent[] = {
    [TYPE_U8] = TYPE_U64,       [TYPE_U16] = TYPE_U64,
    [TYPE_U32] = TYPE_U64,      [TYPE_U64] = TYPE_U64,
    [TYPE_I8] = TYPE_I64,       [TYPE_I16] = TYPE_I64,
    [TYPE_I32] = TYPE_I64,      [TYPE_I64] = TYPE_I64,
    [TYPE_FLOAT] = TYPE_DOUBLE, [TYPE_DOUBLE] = TYPE_DOUBLE,
    [TYPE_BOOL] = TYPE_U64,

    [TYPE_I] = TYPE_I64,        [TYPE_LI] = TYPE_I64,
    [TYPE_U] = TYPE_U64,        [TYPE_LU] = TYPE_U64,
};
static c_type ctype_alias[] = {
    [TYPE_I] = TYPE_I32,
    [TYPE_LI] = TYPE_I64,
    [TYPE_U] = TYPE_U32,
    [TYPE_LU] = TYPE_U64,
};
SL_header char *ctypeAsStr(c_type type) {
    switch (type) {
    case TYPE_VOID: return "void";
    case TYPE_BOOL: return "bool";
    case TYPE_I8: return "i8";
    case TYPE_U8: return "u8";
    case TYPE_I16: return "i16";
    case TYPE_U16: return "u16";
    case TYPE_I32: return "i32";
    case TYPE_U32: return "u32";
    case TYPE_I64: return "i64";
    case TYPE_U64: return "u64";
    case TYPE_FLOAT: return "float";
    case TYPE_DOUBLE: return "double";

    case TYPE_I: return "int";
    case TYPE_U: return "uint";
    case TYPE_LI: return "i64";
    case TYPE_LU: return "u64";

    case TYPE_USIZE: return "usize";
    default: return "[UNIMPLEMENTED]";
    }
}
SL_header char *ctypePrefixAsStr(c_type type) {
  switch (type) {
  case TYPE_VOID:
    return "void";
  case TYPE_BOOL:
    return "b";
  case TYPE_I8:
    return "i8";
  case TYPE_U8:
    return "u8";
  case TYPE_I16:
    return "i16";
  case TYPE_U16:
    return "u16";
  case TYPE_I32:
    return "i32";
  case TYPE_U32:
    return "u32";
  case TYPE_I64:
    return "i64";
  case TYPE_U64:
    return "u64";
  case TYPE_FLOAT:
    return "f";
  case TYPE_DOUBLE:
    return "d";

  case TYPE_I:
    return "i";
  case TYPE_U:
    return "u";
  case TYPE_LI:
    return "li";
  case TYPE_LU:
    return "lu";

  case TYPE_USIZE:
    return "us";

  default:
    return "[UNIMPLEMENTED]";
  }
}

#undef print
#ifdef DEBUG
#   define print(msg, ...) fprintf(stdout, msg, ##__VA_ARGS__)
#   define putc(char) fputc(char, stdout)
#else
#   define print(msg, ...) fprintf(f, msg, ##__VA_ARGS__)
#   define putc(char) fputc(char, f)
#endif

typedef struct VectorType {
  c_type type;
  usize size;
} vec_type;
SL_header char *vtypeAsStr(vec_type type, bool funcName) {
  static char buffer[32];
  if (type.type == TYPE_VOID)
    sprintf(buffer, "vec");
  else if (type.size > 1)
    sprintf(buffer, "%sv%u", ctypePrefixAsStr(type.type), type.size);
  else if (type.size == 0)
    sprintf(buffer, "%sv", ctypePrefixAsStr(type.type));
  else if (funcName)
    sprintf(buffer, "%sv", ctypePrefixAsStr(type.type));
  else
    sprintf(buffer, "%s*", ctypeAsStr(type.type));
  return buffer;
}

typedef struct QuaternionType {
  c_type type;
} quat_type;
SL_header char *qtypeAsStr(quat_type type) {
  static char buffer[32];
  if (type.type == TYPE_VOID)
    sprintf(buffer, "quat");
  else
    sprintf(buffer, "%sq", ctypePrefixAsStr(type.type));
  return buffer;
}

typedef struct MatrixType {
  c_type type;
  usize r, c;
} mat_type;
SL_header char *mtypeAsStr(mat_type type) {
  static char buffer[32];
  if (type.type == TYPE_VOID)
    sprintf(buffer, "mat");
  else if (!type.c)
    sprintf(buffer, "%sm", ctypePrefixAsStr(type.type));
  else
    sprintf(buffer, "%sm%ux%u", ctypePrefixAsStr(type.type), type.r, type.c);
  return buffer;
}

typedef struct BlockMatrixType {
  c_type type;
} bmat_type;
SL_header char *btypeAsStr(bmat_type type) {
  static char buffer[32];
  if (type.type == TYPE_VOID)
    sprintf(buffer, "block_mat");
  else
    sprintf(buffer, "%sbm", ctypePrefixAsStr(type.type));
  return buffer;
}

typedef enum TypeVariant {
  VARIANT_C = 0,
  VARIANT_V,
  VARIANT_Q,
  VARIANT_M,
  VARIANT_B,
} type_variant;

typedef struct Type {
  type_variant variant;
  union {
    c_type c;
    vec_type v;
    quat_type q;
    mat_type m;
    bmat_type b;
  } as;
  usize ptr;
} type;
SL_DEF_ARRAY(type);
SL_header char *typeAsStr(type t, bool funcName) {
  static char buffer[8][32];
  static usize buffI = 0;
  buffI = (buffI + 1) % 8;

  int l = 0;

  switch (t.variant) {
  case VARIANT_C:
    l = sprintf(buffer[buffI],
                funcName ? ctypePrefixAsStr(t.as.c) : ctypeAsStr(t.as.c));
    break;
  case VARIANT_V:
    l = sprintf(buffer[buffI], vtypeAsStr(t.as.v, funcName));
    break;
  case VARIANT_Q:
    l = sprintf(buffer[buffI], qtypeAsStr(t.as.q));
    break;
  case VARIANT_M:
    l = sprintf(buffer[buffI], mtypeAsStr(t.as.m));
    break;
  case VARIANT_B:
    l = sprintf(buffer[buffI], btypeAsStr(t.as.b));
    break;
  default:
    break;
  }
  if (l < 0)
    SL_terminate(-1, "Failed to print type");

  if (!funcName)
    while (t.ptr--)
      buffer[buffI][l++] = '*';
  buffer[buffI][l] = '\0';
  return buffer[buffI];
}

SL_header bool typeIsSigned(type t) {
  return ctype_parent[t.as.c] == TYPE_I64 ||
         ctype_parent[t.as.c] == TYPE_DOUBLE;
}
SL_header bool typeIsInt(type t) {
  return ctype_parent[t.as.c] == TYPE_I64 || ctype_parent[t.as.c] == TYPE_U64;
}
SL_header bool typeIsReal(type t) {
  return ctype_parent[t.as.c] == TYPE_FLOAT ||
         ctype_parent[t.as.c] == TYPE_DOUBLE;
}

#define F32 ((type){.variant = VARIANT_C, .as.c = TYPE_FLOAT, .ptr = 0})
#define F32_ ((type){.variant = VARIANT_C, .as.c = TYPE_FLOAT, .ptr = 1})
#define F64 ((type){.variant = VARIANT_C, .as.c = TYPE_DOUBLE, .ptr = 0})
#define F64_ ((type){.variant = VARIANT_C, .as.c = TYPE_DOUBLE, .ptr = 1})
#define I8 ((type){.variant = VARIANT_C, .as.c = TYPE_I8, .ptr = 0})
#define I8_ ((type){.variant = VARIANT_C, .as.c = TYPE_I8, .ptr = 1})
#define I16 ((type){.variant = VARIANT_C, .as.c = TYPE_I16, .ptr = 0})
#define I16_ ((type){.variant = VARIANT_C, .as.c = TYPE_I16, .ptr = 1})
#define I32 ((type){.variant = VARIANT_C, .as.c = TYPE_I32, .ptr = 0})
#define I32_ ((type){.variant = VARIANT_C, .as.c = TYPE_I32, .ptr = 1})
#define I64 ((type){.variant = VARIANT_C, .as.c = TYPE_I64, .ptr = 0})
#define I64_ ((type){.variant = VARIANT_C, .as.c = TYPE_I64, .ptr = 1})
#define U8 ((type){.variant = VARIANT_C, .as.c = TYPE_U8, .ptr = 0})
#define U8_ ((type){.variant = VARIANT_C, .as.c = TYPE_U8, .ptr = 1})
#define U16 ((type){.variant = VARIANT_C, .as.c = TYPE_U16, .ptr = 0})
#define U16_ ((type){.variant = VARIANT_C, .as.c = TYPE_U16, .ptr = 1})
#define U32 ((type){.variant = VARIANT_C, .as.c = TYPE_U32, .ptr = 0})
#define U32_ ((type){.variant = VARIANT_C, .as.c = TYPE_U32, .ptr = 1})
#define U64 ((type){.variant = VARIANT_C, .as.c = TYPE_U64, .ptr = 0})
#define U64_ ((type){.variant = VARIANT_C, .as.c = TYPE_U64, .ptr = 1})
#define BOOL ((type){.variant = VARIANT_C, .as.c = TYPE_BOOL, .ptr = 0})
#define BOOL_ ((type){.variant = VARIANT_C, .as.c = TYPE_BOOL, .ptr = 1})

#define C(ctype) ((type){.variant = VARIANT_C, .as.c = ctype, .ptr = 0})
#define C_(ctype) ((type){.variant = VARIANT_C, .as.c = ctype, .ptr = 1})
#define V(ctype, dim)                                                          \
  ((type){.variant = VARIANT_V, .as.v = {.size = dim, .type = ctype}, .ptr = 0})
#define V_(ctype, dim)                                                         \
  ((type){.variant = VARIANT_V, .as.v = {.size = dim, .type = ctype}, .ptr = 1})
#define Q(ctype)                                                               \
  ((type){.variant = VARIANT_Q, .as.q = {.type = ctype}, .ptr = 0})
#define Q_(ctype)                                                              \
  ((type){.variant = VARIANT_Q, .as.q = {.type = ctype}, .ptr = 1})
#define M(ctype, R, C)                                                         \
  ((type){.variant = VARIANT_M,                                                \
          .as.m = {.r = R, .c = C, .type = ctype},                             \
          .ptr = 0})
#define M_(ctype, R, C)                                                        \
  ((type){.variant = VARIANT_M,                                                \
          .as.m = {.r = R, .c = C, .type = ctype},                             \
          .ptr = 1})
#define B(ctype)                                                               \
  ((type){.variant = VARIANT_B, .as.b = {.type = ctype}, .ptr = 0})
#define B_(ctype)                                                              \
  ((type){.variant = VARIANT_B, .as.b = {.type = ctype}, .ptr = 1})

#pragma endregion TYPE

#pragma region BUILD

#ifdef SL_GEN_MAIN
char __DEF_BUFFER__[512];
array(ptr(char)) TYPES = {0};
array(ptr(char)) DEFINITIONS = {0};
array(ptr(char)) IMPLEMENTATIONS = {0};
// usize SL_ERROR = SL_ERR_NONE;
#else
extern char __DEF_BUFFER__[512];
extern array(ptr(char)) TYPES;
extern array(ptr(char)) DEFINITIONS;
extern array(ptr(char)) IMPLEMENTATIONS;
#endif
#define prefDefAdd(fmt, ...)                                                   \
  arrayAdd(DEFINITIONS, (sprintf(__DEF_BUFFER__, fmt, ##__VA_ARGS__),          \
                         strdup(__DEF_BUFFER__)))

typedef struct Variable {
  char *name;
  type type;
} var;
#define var(name_, type_) ((var){.name = name_, .type = type_})

typedef struct FunctionSignature {
  type on, ret;
  usize var_count;
  var *vars;
} func_sig;
SL_header void funcSigSwitchType(func_sig *sig, c_type oldType,
                                 c_type newType) {
  if (sig->on.as.c == oldType)
    sig->on.as.c = newType;
  if (sig->ret.as.c == oldType)
    sig->ret.as.c = newType;
  for (usize i = 0; i < sig->var_count; ++i)
    if (sig->vars[i].type.as.c == oldType)
      sig->vars[i].type.as.c = newType;
}
#define sig(type_on, type_ret, ...)                                            \
  ((func_sig){.on = type_on,                                                   \
              .ret = type_ret,                                                 \
              .var_count = sizeof((var[]){__VA_ARGS__}) / sizeof(var),         \
              .vars = (var[]){__VA_ARGS__}})

typedef struct FunctionDefinition {
  char *name;
  func_sig signature;

  char *pre;
  char *desc;
  int desc_typeOffset;

  bool oneLiner; // Only print op[0] once as return value
  char *op[4];   // Operation for each individual line until vec4/quat
                 // If only first, then reuse, if all are empty then only "pre"
} func_def;

typedef enum FormatHash {
  FMT_HASH_INDEX,
  FMT_HASH_V,
  FMT_HASH_Q,
  FMT_HASH_M,
  FMT_HASH_B,
} fmt_hash;
typedef struct {
  usize comp2;
  int var_offset;
  usize tab;
  const char *newline;
} push_fmt_string_params;

SL_header void pushFmtString_params(FILE *f, func_sig sig, fmt_hash fmt,
                                    usize comp, const char *str,
                                    push_fmt_string_params params) {
  for (const char *c = str; *c; ++c)
    switch (*c) {
    case '\n': {
      if (params.newline[0] != '\n') {
        print(params.newline);
        for (usize j = (c[1] == '\0'); j < params.tab; ++j)
          print("    ");
      } else {
        putc('\n');
        for (usize j = (c[1] == '\0'); j < params.tab; ++j)
          print("    ");
        print(params.newline + 1);
      }
    } break;
    case '#':
      switch (fmt) {
      case -1:
        print("#");
        break;
      case FMT_HASH_V:
        print(".%c", comp == 3 ? 'w' : 'x' + comp);
        break;
      case FMT_HASH_Q:
        print(".%c", 'w' + comp);
        break;
      case FMT_HASH_M:
        print(".m%d%d", comp, params.comp2);
        break;
      case FMT_HASH_B:
        print(".m%d%d", comp, params.comp2);
        break;
      default:
        print("[i]");
        break;
      }
      break;
    case '@':
    case '$': {
      bool funcName = *c == '$';
      switch (*++c) {
      case 'r':
        print(typeAsStr(sig.ret, funcName));
        break; // Return full type
      case 'R':
        print(typeAsStr(
            (type){.variant = VARIANT_C, .as.c = sig.ret.as.c, .ptr = 0},
            funcName));
        break; // Return ctype
      case 'o':
        print(typeAsStr(sig.on, funcName));
        break; // "On" full type
      case 'O':
        print(typeAsStr(
            (type){.variant = VARIANT_C, .as.c = sig.on.as.c, .ptr = 0},
            funcName));
        break; // "On" ctype
      case 'v':
        print(
            typeAsStr(sig.vars[*++c - '0' + params.var_offset].type, funcName));
        break; // var[i] full type
      case 'V':
        print(typeAsStr(
            (type){.variant = VARIANT_C,
                   .as.c = sig.vars[*++c - '0' + params.var_offset].type.as.c,
                   .ptr = 0},
            funcName));
        break; // var[i] ctype

      default:
        SL_terminate(-1, "Failed to parse \'%c%c\'", *(c - 1), *c);
      }
    } break;
    default:
      putc(*c);
      break;
    }
}
#define pushFmtString(f, sig, fmt, comp, str, ...)                             \
  (pushFmtString_params(f, sig, fmt, comp, str,                                \
                        (push_fmt_string_params){.comp2 = 0,                   \
                                                 .var_offset = 0,              \
                                                 .tab = 0,                     \
                                                 .newline = "\n",              \
                                                 ##__VA_ARGS__}))

#define pushFmtIndex(f, sig, str, ...)                                         \
  (pushFmtString(f, sig, FMT_HASH_INDEX, 0, str, ##__VA_ARGS__))
#define pushFmtV(f, sig, comp, str, ...)                                       \
  (pushFmtString(f, sig, FMT_HASH_V, comp, str, ##__VA_ARGS__))
#define pushFmtQ(f, sig, comp, str, ...)                                       \
  (pushFmtString(f, sig, FMT_HASH_Q, comp, str, ##__VA_ARGS__))
#define pushFmtM(f, sig, comp1, comp2_, str, ...)                              \
  (pushFmtString(f, sig, FMT_HASH_M, comp1, str, .comp2 = comp2_,              \
                 ##__VA_ARGS__))

SL_header void pushFuncDefinitionStart(FILE *f) {
  print("\n#if defined(SL_IMPLEMENTATION)\n{\n    ");
}
SL_header void pushFuncDefinitionEnd(FILE *f) {
  print("\n}\n#else\n;\n#endif\n");
}

SL_header void pushFuncDescription(FILE *f, func_sig sig, const char *desc,
                                   int var_offset) {
  print("/// @brief ");
  pushFmtIndex(f, sig, desc, .var_offset = var_offset, .newline = "\n/// @");
}
SL_header void pushFuncCommon(FILE *f, const char *name, func_sig sig,
                              const char *desc, const char *pre,
                              int var_offset) {
  prefDefAdd("%s%s", typeAsStr(sig.on, true), name);

  pushFuncDescription(f, sig, desc, var_offset);
  print("\n" SL_PREFIX "header %s SL_%s%s(", typeAsStr(sig.ret, false),
        typeAsStr(sig.on, true), name);
  if (sig.var_count) {
    print("%s %s", typeAsStr(sig.vars[0].type, false), sig.vars[0].name);
    for (usize i = 1; i < sig.var_count; ++i)
      print(", %s %s", typeAsStr(sig.vars[i].type, false), sig.vars[i].name);
  }
  print(")");
  pushFuncDefinitionStart(f);
  if (pre) {
    pushFmtIndex(f, sig, pre, .tab = 1);
    print("\n    ");
  }
}

#define pushType(f, fmt, ...)                                                  \
  (arrayAdd(TYPES, strf(fmt, ##__VA_ARGS__)),                                  \
   print("typedef struct " SL_PREFIX "%s " SL_PREFIX "%s;\nstruct " SL_PREFIX  \
         "%s\n",                                                               \
         tmpf(NULL), tmpf(NULL)))
#define pushDefine_(f, name, def, ...)                                         \
  do {                                                                         \
    prefDefAdd("%s", name);                                                    \
    print("#define " SL_PREFIX "%s", name);                                    \
    pushFmtString(f, sig(I64, I64), -1, 0, tmpf(def, ##__VA_ARGS__),           \
                  .newline = "\\\n");                                          \
    putc('\n');                                                                \
  } while (0)
#define pushDefine(f, on, name, def, ...)                                      \
  do {                                                                         \
    prefDefAdd("%s%s", typeAsStr(on, true), name);                             \
    print("#define " SL_PREFIX "%s%s", typeAsStr(on, true), name);             \
    pushFmtString(f, sig(on, on), -1, 0, tmpf(def, ##__VA_ARGS__),             \
                  .newline = "\\\n");                                          \
    putc('\n');                                                                \
  } while (0)

SL_header void pushImplementation(FILE *f) {
  print("#ifdef SL_IMPLEMENTATION\n");

  print("#endif\n");
}

SL_header void pushStripPrefix(FILE *f) {
#ifdef SL_PREFIX
  usize max_name_len = 0;
  aforeach(def, DEFINITIONS) {
    usize name_len = strlen(*def);
    max_name_len = max_name_len > name_len ? max_name_len : name_len;
  }
  aforeach(def, TYPES) {
    usize name_len = strlen(*def);
    max_name_len = max_name_len > name_len ? max_name_len : name_len;
  }

  print("#ifdef SL_STRIP_PREFIX\n");
  for (usize i = 0; i < DEFINITIONS.count; ++i)
    print("#   define  %.*s " SL_PREFIX "%s\n", max_name_len,
          DEFINITIONS.data[i], DEFINITIONS.data[i]);
  for (usize i = 0; i < TYPES.count; ++i)
    print("    typedef %.*s " SL_PREFIX "%s\n", max_name_len, TYPES.data[i],
          TYPES.data[i]);
  print("#endif\n");
#endif
}

#pragma endregion BUILD

#endif
