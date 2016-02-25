#include <windows.h>
#include "my_crt.h"

void exit(int _Code);
extern int main(int, char**);

void my_crt_entry()
{
    int ret, i;
    int argc = 0;
    char* cl;
    char* argv[10];
    char token[] = " \t";

    // Analyze the command line
    cl = GetCommandLineA();
    argv[0] = _strtok(cl, token);
    argc++;
    for(i = 1; i < 10; i++) {
        if (argv[i - 1] != NULL) {
            argv[i] = _strtok(NULL, token);
            argc++;
        }
    }

    // Init heap
    if (!heap_init()) {
        exit(1);
    }

    // Init IO, do nothing here

    // main entry
    ret = main(argc, argv);

    exit(ret);
}

void exit(int _Code)
{
    ExitProcess(_Code);
}

