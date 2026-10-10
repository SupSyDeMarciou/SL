#define SL_IMPLEMENTATION
#include "../generate.h"

#define S_PATH "C:/Users/vlada/Desktop/Coding/C/SupSy/"

int main(int argc, char **argv)
{
    FILE *f = fopen(S_PATH"SupSyLibraries/include/misc/async.h", "w");

    fputs(
        "typedef enum sl_task_status {\n"    
        "    SL_TASK_WAIT,\n"    
        "    SL_TASK_WORKING,\n"    
        "    SL_TASK_DONE,\n"
        "} sl_task_status;\n"
        "\n"
        
    , f);

    fclose(f);
}