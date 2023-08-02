#include <stdio.h>
#include <string.h>
#include "hftlob.h"

int main(int argc, char* argv[])
{
    int i ;
    printf("Running main \n");
    for (int i =0;i<argc;++i)
    {
        if(strcmp(argv[i],"--test")==0)
        {
            printf("Running test\n\n");
            RunAllTests();
        }
    }

    return 0;
}