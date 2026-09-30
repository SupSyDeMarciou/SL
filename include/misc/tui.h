#ifndef _SL_TUI_H_
#define _SL_TUI_H_

#include "../base.h"
#include "../struct/array.h"

typedef enum sl_cmd_arg_type {
    SL_CMD_ARG_TOGGLE = 0,
    SL_CMD_ARG_INT,
    SL_CMD_ARG_REAL,
    SL_CMD_ARG_STRING,
    SL_CMD_ARG_UNKNOWN,
} sl_cmd_arg_type;
typedef union sl_cmd_arg_union {
    bool   toggle;
    i64    integer;
    double real;
    char  *string;
} sl_cmd_arg_union;
typedef struct sl_cmd_arg {
    sl_cmd_arg_type type;
    const char *name_long; 
    const char *name_short;
    sl_cmd_arg_union default_value;
    
    bool assigned;
    sl_cmd_arg_union assigned_value;
} sl_cmd_arg;
SL_DEF_ARRAY(sl_cmd_arg);

#define sl_cmd_arg_toggle_(name_long_, name_short_)           ((sl_cmd_arg){.type = SL_CMD_ARG_TOGGLE, .name_long = name_long_, .name_short = name_short_, .default_value = false,   .assigned = false, .assigned_value.toggle  = false})
#define sl_cmd_arg_integer_(name_long_, name_short_, default) ((sl_cmd_arg){.type = SL_CMD_ARG_INT,    .name_long = name_long_, .name_short = name_short_, .default_value = default, .assigned = false, .assigned_value.integer = default})
#define sl_cmd_arg_real_(name_long_, name_short_, default)    ((sl_cmd_arg){.type = SL_CMD_ARG_REAL,   .name_long = name_long_, .name_short = name_short_, .default_value = default, .assigned = false, .assigned_value.real    = default})
#define sl_cmd_arg_string_(name_long_, name_short_, default)  ((sl_cmd_arg){.type = SL_CMD_ARG_STRING, .name_long = name_long_, .name_short = name_short_, .default_value = default, .assigned = false, .assigned_value.string  = default})

SL_header bool SL_cmd_arg_parse(int argc, char **argv, SL_array(sl_cmd_arg) *arguments);



#ifdef SL_STRIP_PREFIX
    typedef sl_cmd_arg_type      cmd_arg_type;
    typedef sl_cmd_arg_union     cmd_arg_union;
    typedef sl_cmd_arg           cmd_arg;
#   define  cmd_arg_toggle_      sl_cmd_arg_toggle_
#   define  cmd_arg_integer_     sl_cmd_arg_integer_
#   define  cmd_arg_real_        sl_cmd_arg_real_
#   define  cmd_arg_string_      sl_cmd_arg_string_
#   define  cmd_arg_parse        SL_cmd_arg_parse
#endif



#ifdef SL_IMPLEMENTATION
SL_header bool SL_cmd_arg_parse(int argc, char **argv, SL_array(sl_cmd_arg) *arguments)
{
    for (usize i = 1; i < argc; ++i) { // Skip program name
        bool matched = false;
        for (usize j = 0; j < arguments->count && !matched; ++j)
        {
            if (
                (arguments->data[j].name_short == NULL || strcmp(argv[i], arguments->data[j].name_short) != 0) && 
                (arguments->data[j].name_long  == NULL || strcmp(argv[i], arguments->data[j].name_long)  != 0)
            ) continue;

            matched = true;
            switch (arguments->data[j].type)
            {
                case SL_CMD_ARG_TOGGLE: 
                {
                    arguments->data[j].assigned_value.toggle = true; 
                    arguments->data[j].assigned = true;
                } break;
                case SL_CMD_ARG_INT:
                {
                    if (++i == argc || argv[i][0] == '-') return __SL_ERROR(SL_ERROR_MISSING_VALUE), false;
                    arguments->data[j].assigned_value.integer = atoll(argv[i]);
                    arguments->data[j].assigned = true;
                } break;
                case SL_CMD_ARG_REAL:
                {
                    if (++i == argc || argv[i][0] == '-') return __SL_ERROR(SL_ERROR_MISSING_VALUE), false;
                    arguments->data[j].assigned_value.real = atof(argv[i]);
                    arguments->data[j].assigned = true;
                } break;
                case SL_CMD_ARG_STRING:
                {
                    if (++i == argc || argv[i][0] == '-') return __SL_ERROR(SL_ERROR_MISSING_VALUE), false;
                    arguments->data[j].assigned_value.string = argv[i];
                    arguments->data[j].assigned = true;
                } break;
                
                default:
                {
                    return __SL_ERROR(SL_ERROR_OUT_OF_BOUNDS), false;
                } break;
            }
        }

        if (!matched && argv[i])
        {
            char *assigned_value = NULL;
            if (i + 1 == argc || argv[i + 1][0] == '-') assigned_value = argv[++i];
            SL_arrayAdd(*arguments, ((sl_cmd_arg){.type = SL_CMD_ARG_UNKNOWN, .name_long = argv[i], .name_short = argv[i], .assigned = true, .assigned_value.string = assigned_value}) );
        }
    }

    return true;
}
#endif


#endif // _SL_TUI_H_