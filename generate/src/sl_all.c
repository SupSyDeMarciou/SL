#define SL_STRIP_PREFIX
#define SL_IMPLEMENTATION
#include "../include/sl.h"

int fprint_time(FILE *fd)
{
    time_t timestamp = time(NULL);
    struct tm * pTime = localtime(&timestamp);

    char buffer[512];
    strftime(buffer, 512, "%d/%m/%Y %H:%M:%S", pTime);
    return fprintf(fd, "%s", buffer);
}

#define S_PATH "C:/Users/vlada/Desktop/Coding/C/SupSy/"

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
    
    FILE *f = fopen(S_PATH"SupSyLibraries/include/sl_all.h", "wb");
    aforeach(path, slice_(ptr(char), paths, static_count(paths)))
    {
        printf("[%d] %s\n", aindex(path), *path);
        fprintf(f, "// SOURCE: %s\n", *path);
        usize size;
        char *src = readEntireFile(tmpf(S_PATH"SupSyLibraries/include/%s", *path), &size);
        if (src == NULL)
        {
            fprintf(stderr, "[ERROR] File %s does not exist!\n", tmpf(S_PATH"SupSyLibraries/include/%s", *path));
        }

        aforeach(p, slice_(char, src, size))
        {
            if      (strstart(p, "#ifdef SL_IMPLEMENTATION")) {
                p += sizeof("#ifdef SL_IMPLEMENTATION");
                for (; !strstart(p, "#endif"); ++p) arrayAdd(implementation, *p);
                p += sizeof("#endif") + 1;
                while (isblank(*p)) ++p;
            }
            else if (strstart(p, "#ifdef SL_STRIP_PREFIX")) {
                p += sizeof("#ifdef SL_STRIP_PREFIX");
                for (; !strstart(p, "#endif"); ++p) arrayAdd(strip_prefix, *p);
                p += sizeof("#endif") + 1;
                while (isblank(*p)) ++p;
            }
            else if (strstart(p, "#ifndef SL_NO_DEFINES")) {
                p += sizeof("#ifndef SL_NO_DEFINES");
                for (; !strstart(p, "#endif"); ++p) arrayAdd(no_defines, *p);
                p += sizeof("#endif") + 1;
                while (isblank(*p)) ++p;
            }
            if (strstart(p, "#include \"")) fputs("// ", f);
            fputc(*p, f);
        }

        free(src);
        fputs("\n\n\n\n\n\n", f);
    }

    arrayAdd(implementation, 0);
    arrayAdd(strip_prefix, 0);
    arrayAdd(no_defines, 0);

    fprintf(f, "#ifdef SL_IMPLEMENTATION%s#endif\n\n\n", implementation.data);
    fprintf(f, "#ifdef SL_STRIP_PREFIX%s#endif\n\n\n", strip_prefix.data);
    fprintf(f, "#ifndef SL_NO_DEFINES%s#endif\n\n\n", no_defines.data);

    fprintf(f, "// This file was generated on "); fprint_time(f); 
    fclose(f);
}