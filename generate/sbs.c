#include "../../SupSyBuildSystem/sbs.h"
#define SL_IMPLEMENTATION
#include "../include/SL/struct/array.h"
#include "../include/SL/misc/tui.h"
#include "../include/SL/misc/io.h"

#define PATH "/home/supsy/Coding/C/SupSy/SupSyLibraries/"

typedef struct entry { const char *folder, *file; } entry;
SL_DEF_ARRAY(entry);
#define entry_(a, b) ((entry){a, b})

#define FF(e) "%", (e)->file, "%"
#define FE(e) "%", (e)->folder, "%" FF(e)

int main(int argc, char **argv)
{
    SBS_rebuild(argc, argv, "-I"PATH"include");
    int err;

    SL_array(sl_cmd_arg) flags = SL_arrayCreate(sl_cmd_arg, 16);

    sl_cmd_arg *flag_debug = SL_arrayAdd(flags, sl_cmd_arg_toggle_("--debug",        NULL));
    sl_cmd_arg *flag_all   = SL_arrayAdd(flags, sl_cmd_arg_toggle_("--all",          NULL));
    sl_cmd_arg *flag_run   = SL_arrayAdd(flags, sl_cmd_arg_toggle_("--run",          NULL));
    
    sl_cmd_arg *flag_v     = SL_arrayAdd(flags, sl_cmd_arg_toggle_("--vector",       "-v"));
    sl_cmd_arg *flag_q     = SL_arrayAdd(flags, sl_cmd_arg_toggle_("--quaternion",   "-q"));
    sl_cmd_arg *flag_m     = SL_arrayAdd(flags, sl_cmd_arg_toggle_("--matrix",       "-m"));
    sl_cmd_arg *flag_bm    = SL_arrayAdd(flags, sl_cmd_arg_toggle_("--block-matrix", "-bm"));
    sl_cmd_arg *flag_sa    = SL_arrayAdd(flags, sl_cmd_arg_toggle_("--sl-all",       "-sa"));

    if (!SL_cmd_arg_parse(argc, argv, SL_slicea(sl_cmd_arg, flags, 0, flags.count), NULL))
    {
        SBS_logE("Failed to parse args");
        return 1;
    }

    SL_array(entry) to_build = {0};
    if (flag_all->assigned || flag_v->assigned) SL_arrayAdd(to_build, entry_("math/", "vector"));
    if (flag_all->assigned || flag_q->assigned) SL_arrayAdd(to_build, entry_("math/", "quaternion"));
    if (flag_all->assigned || flag_m->assigned) SL_arrayAdd(to_build, entry_("math/", "matrix"));
    // if (flag_all->assigned || flag_bm->assigned) SL_arrayAdd(to_build, entry_("math/", "block_matrix"));
    if (flag_all->assigned || flag_sa->assigned) SL_arrayAdd(to_build, entry_("", "sl_all"));

    sbs_run cmd = {0};
    SL_aforeach(e, to_build) SBS_addTask(&cmd, "cc", 
        flag_debug->assigned ? "-DDEBUG" : "-UDEBUG", 
        "-I"PATH"include/", "-o",
        PATH"generate/bin/"FF(e)SBS_EXECUTABLE_EXT, 
        PATH"generate/src/"FE(e)".c"
    );
    if (err = SBS_run(&cmd, 1)) return err;

    SL_aforeach(e, to_build) if (e->folder[0]) SBS_addTask(&cmd, PATH"generate/bin/"FF(e)SBS_EXECUTABLE_EXT);
    if (err = SBS_run(&cmd, 1)) return err;

    if ((flag_all->assigned || flag_sa->assigned)) return SBS_taskRun(PATH"generate/bin/sl_all"SBS_EXECUTABLE_EXT);
}