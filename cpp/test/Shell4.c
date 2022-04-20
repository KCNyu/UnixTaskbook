#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
	int fd[2];
	pipe(fd);
	char *args[100];
	for (int i = 0; i < argc; i++)
	{
		args[i] = (char*)malloc(50);
		strcpy(args[i],argv[i]);
	}
	int N = atoi(args[2]);
	int M = atoi(args[3 + N + 1]);
	int pid = fork();
	if (pid == 0)
	{

		dup2(fd[1],STDOUT_FILENO);
		close(fd[0]); close(fd[1]);
		strcpy(args[2], args[1]);
		args[2 + N + 1] = (char *)0;
		execvp(args[1], args + 2);
	}
	else
	{
		int status;
		waitpid(pid, &status, 0);
		dup2(fd[0],STDIN_FILENO);
		close(fd[0]); close(fd[1]);
		strcpy(args[4 + N], args[3 + N]);
		args[4 + N + M + 1] = (char *)0;
		execvp(args[2 + N + 1], args + 4 + N);
	}
	return 0;
}
