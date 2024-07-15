#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user/user.h"

void xargs_exec(int argc, char *initial_argv[], char *arg)
{
    if (fork() == 0)
    {
        char *argv[MAXARG];
        for (int i = 0; i < argc; i++)
        {
            argv[i] = initial_argv[i];
        }
        argv[argc] = arg;
        exec(argv[0], argv);
        fprintf(2, "exec %s failed", argv[0]);
        exit(1);
    }
    else
    {
        wait(0);
    }
}

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        printf("usage: xargs command [initial-args]\n");
        exit(1);
    }
    char buf[512];
    int initial_argc = argc - 1;
    char *initial_argv[MAXARG];
    int i = 0;
    for (int j = 0; j < argc; j++)
    {
        initial_argv[j] = argv[j + 1];
    }
    while (read(0, &buf[i], 1) > 0)
    {
        if (buf[i] == '\n')
        {
            buf[i] = 0;
            xargs_exec(initial_argc, initial_argv, buf);
            i = 0;
        }
        else
        {
            i++;
        }
    }
    if (i > 0) // 处理最后一行没加换行符的情况
    {
        buf[i] = 0;
        xargs_exec(initial_argc, initial_argv, buf);
    }
    exit(0);
}