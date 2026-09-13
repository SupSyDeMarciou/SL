#include "../../../SupSyBuildSystem/sbs.h"
#define SL_IMPLEMENTATION
#include "../../include/struct/array.h"
#include "../../include/misc/tui.h"
#include "../../include/misc/io.h"

#ifdef _WIN32
#   define S_PATH "C:/Users/vlada/Desktop/Coding/C/SupSy/"
#else
#   define S_PATH "/home/supsy/Coding/C/SupSy/"
#endif
#define G_PATH S_PATH"SupSyLibraries/generate/"
#define CT(x) "%", x, "%"



int main(int argc, char **argv)
{
    SBS_rebuild(argc, argv, S_PATH"SupSyLibraries/include");
    sbs_run cmd = {0};

    SL_array(sl_cmd_arg) flags = SL_arrayCreate(sl_cmd_arg, 16);

    sl_cmd_arg *flag_debug = SL_arrayAdd(flags, sl_cmd_arg_toggle_("--debug",        NULL));
    sl_cmd_arg *flag_all   = SL_arrayAdd(flags, sl_cmd_arg_toggle_("--all",          NULL));
    sl_cmd_arg *flag_run   = SL_arrayAdd(flags, sl_cmd_arg_toggle_("--run",          NULL));
    
    sl_cmd_arg *flag_v     = SL_arrayAdd(flags, sl_cmd_arg_toggle_("--vector",       "-v"));
    sl_cmd_arg *flag_q     = SL_arrayAdd(flags, sl_cmd_arg_toggle_("--quaternion",   "-q"));
    sl_cmd_arg *flag_m     = SL_arrayAdd(flags, sl_cmd_arg_toggle_("--matrix",       "-m"));
    sl_cmd_arg *flag_bm    = SL_arrayAdd(flags, sl_cmd_arg_toggle_("--block-matrix", "-bm"));
    sl_cmd_arg *flag_sa    = SL_arrayAdd(flags, sl_cmd_arg_toggle_("--sl-all",       "-sa"));

    if (!SL_cmd_arg_parse(argc, argv, &flags))
    {
        SBS_logE("Failed to parse args");
        return 1;
    }
    
    SL_array(SL_ptr(char)) to_build = {0};
    if (flag_all->assigned || flag_v->assigned) SL_arrayAdd(to_build, (char *)"vector");
    if (flag_all->assigned || flag_q->assigned) SL_arrayAdd(to_build, (char *)"quaternion");
    if (flag_all->assigned || flag_m->assigned) SL_arrayAdd(to_build, (char *)"matrix");
    // if (flag_all->assigned || flag_bm->assigned) SL_arrayAdd(to_build, (char *)"block_matrix");
    
    SL_aforeach(f, to_build)
    {
        if (flag_debug->assigned) SBS_addTask(&cmd, "gcc", "-DDEBUG", "-o", G_PATH"bin/"CT(*f)SBS_EXECUTABLE_EXT, G_PATH"src/math/"CT(*f)".c");
        else                      SBS_addTask(&cmd, "gcc",             "-o", G_PATH"bin/"CT(*f)SBS_EXECUTABLE_EXT, G_PATH"src/math/"CT(*f)".c");
    }
    
    int err = SBS_run(&cmd, 1);
    if (err) return err;
    
    if ((flag_all->assigned || flag_sa->assigned) && !flag_debug->assigned) err = SBS_taskRun(sbs_task_("gcc", "-o", G_PATH"bin/sl_all", G_PATH"src/sl_all.c"));
    if (err) return err;

    SL_aforeach(f, to_build) SBS_addTask(&cmd, G_PATH"bin/"CT(*f) SBS_EXECUTABLE_EXT);
    err = SBS_run(&cmd, 1);
    if (err) return err;

    if ((flag_all->assigned || flag_sa->assigned)) return SBS_taskRun(sbs_task_(G_PATH"bin/sl_all"SBS_EXECUTABLE_EXT));
}