#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    char buf;
    int p[2];
    pipe(p);
    if (fork() == 0) // 子进程
    {
        read(p[0], &buf, 1);
        printf("%d: received ping\n", getpid());
        write(p[1], &buf, 1);
        close(p[0]);
        close(p[1]);
    }
    else // 父进程
    {
        write(p[1], "t", 1);
        wait(0);
        read(p[0], &buf, 1);
        printf("%d: received pong\n", getpid());
        close(p[0]);
        close(p[1]);
    }
    exit(0);
}