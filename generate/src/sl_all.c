#define SL_STRIP_PREFIX
#define SL_IMPLEMENTATION
// #include "../../include/struct/array.h"
// #include "../../include/misc/io.h"
#include "generate.h"

#ifdef _WIN32
#   define S_PATH "C:/Users/vlada/Desktop/Coding/C/SupSy/"
#else
#   define S_PATH "/home/supsy/Coding/C/SupSy/"
#endif

usize ifdef(array(char) *dict, u8 *_p)
{
    char *p = (char *)_p;
    usize depth = 1;
    while (*p) {
        if (strstart(p, "#if")) ++depth; // , printf("[+] Depth = %d\n", depth);
        if (strstart(p, "#endif")) --depth; // , printf("[-] Depth = %d\n", depth);
        if (depth == 0) break;
        arrayAdd(*dict, *p);
        ++p;
    }
    p += sizeof("#endif") + 1;
    while (isblank(*p)) ++p;
    
    return (usize)p - (usize)_p;
}

int main(int argc, char **argv)
{
    char *paths[] = {
        "base.h",
        
        "struct/allocator.h",
        "struct/array.h",
        "struct/list.h",
        "struct/dict.h",
        "struct/arena.h",
        "struct/tuple.h",

        "misc/io.h",
        "misc/async.h",
        "misc/log.h",
        "misc/tui.h",
        
        "math/math.h",
        "math/vector.h",
        "math/quaternion.h",
        "math/matrix.h",
        // "math/block_matrix.h",
        "math/noise.h",
        "math/algorithm.h",
    };

    array(char) strip_prefix = arrayCreate(char, 2048);
    array(char) implementation = arrayCreate(char, 2048);
    array(char) no_defines = arrayCreate(char, 2048);
    
    FILE *f = fopen(S_PATH"SupSyLibraries/include/sl_all.h", "w");
    aforeach(path, slice_(ptr(char), static_count(paths), paths))
    {
        printf("[%zu] %s\n", aindex(path), *path);
        push("// SOURCE: %s\n", *path);
        usize size;
        char *src = readEntireFile(tmpf(S_PATH"SupSyLibraries/include/%s", *path), &size);
        if (src == NULL)
        {
            fprintf(stderr, "[ERROR] File %s does not exist!\n", tmpf(S_PATH"SupSyLibraries/include/%s", *path));
        }

        usize ifdef_depth = 0;
        aforeach(p, slice_(char, size, src))
        {
            if (strstart(p, "#ifdef SL_IMPLEMENTATION")) {
                p += sizeof("#ifdef SL_IMPLEMENTATION");
                p += ifdef(&implementation, p);
            }
            else if (strstart(p, "#ifdef SL_STRIP_PREFIX")) {
                p += sizeof("#ifdef SL_STRIP_PREFIX");
                p += ifdef(&strip_prefix, p);
            }
            else if (strstart(p, "#ifndef SL_NO_DEFINES")) {
                p += sizeof("#ifndef SL_NO_DEFINES");
                p += ifdef(&no_defines, p);
            }
            if (strstart(p, "#include \"")) push("// ");
            pushc(*p);
        }

        free(src);
        push("\n\n\n\n\n\n");
    }

    arrayAdd(implementation, 0);
    arrayAdd(strip_prefix, 0);
    arrayAdd(no_defines, 0);

    push("#ifdef SL_IMPLEMENTATION%s#endif\n\n\n", implementation.data);
    push("#ifdef SL_STRIP_PREFIX%s#endif\n\n\n", strip_prefix.data);
    push("#ifndef SL_NO_DEFINES%s#endif\n\n\n", no_defines.data);

    pushGenerationData(f, "sl_all.h");
    fclose(f);
}