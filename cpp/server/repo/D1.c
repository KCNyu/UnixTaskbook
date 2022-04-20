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
		strcpy(args[2], args[1]);
		args[2 + N + 1] = (char *)0;
		execvp(args[1], args + 2);
	}
	int status;
	waitpid(pid, &status, 0);
	pid = fork();
	if (pid == 0)
	{
		strcpy(args[4 + N], args[3 + N]);
		args[4 + N + M + 1] = (char *)0;
		execvp(args[2 + N + 1], args + 4 + N);
	}
	waitpid(pid, &status, 0);
	return 0;
}
