#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    if(argc <= 1)
    {
        printf("Error: No argument passed in \n");
        exit(0);
    }

    sleep(atoi(argv[1]));
    exit(0);
}
