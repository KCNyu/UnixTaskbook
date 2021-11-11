#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

void err_sys(const char *info)
{
    perror(info);
    exit(1);
}

void checkarg(char *arg)
{
    if (arg == (char *)0)
    {
        printf("Not enough arguments.\n");
        exit(1);
    }
}

int main(int argc, char *argv[])
{
    // Step 1. Processing arguments
    if (argc < 4)
    {
        printf("Not enough arguments (< 4).\n");
        return 1;
    }

    char **p = ++argv;
    char *fname = *p++;
    char *cmd;
    char **cmdarg;

    cmd = *p++;
    checkarg(cmd);
    char *snum = *p++;
    checkarg(snum);
    int n = atoi(snum);
    if (n < 0 || n > 10)
    {
        printf("Wrong number of arguments: %s", snum);
        return 1;
    }
    cmdarg = (char **)malloc((n + 2) * sizeof(char *));
    cmdarg[0] = cmd;
    for (int i = 1; i <= n; i++)
    {
        cmdarg[i] = *p++;
        checkarg(cmdarg[i]);
    }
    cmdarg[n + 1] = (char *)0;

    // Step 2. Opening descriptors
    pid_t pid;
    int status;
    int fdout;
    fdout = open(fname, O_WRONLY | O_CREAT | O_TRUNC, 0777);

    // Step 3. Executing cmdA
    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0)
    { // child process (cmdA)
        dup2(fdout, STDOUT_FILENO);
        close(fdout);
        execvp(cmd, cmdarg);
        printf("cannot execute: %s\n", cmd);
        return 2;
    }
    close(fdout);
    if (waitpid(pid, &status, 0) < 0)
        err_sys("waitpid error");
    return 0;
}