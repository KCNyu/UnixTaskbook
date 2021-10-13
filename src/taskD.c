#include "taskD.h"
#include "variable.h"

const char *DTaskInfoRussian[] = {
	"Написать программу shellD1, моделирующую конструкцию командного интерпретатора:\ncmdA A1 A2 … AN ; cmdB B1 B2 … BM\nЭта конструкция обеспечивает последовательное выполнение команд cmdA и cmdB:вначале запускается команда cmdA с параметрами A1, A2, …, AN, затем запускается команда cmdB с параметрами B1, B2, …, BM. Каждая команда использует стандартный вывод на экран.\nФормат вызова программы shellD1:\nshellD1 cmdA N A1 A2 … AN cmdB M B1 B2 … BM\n"
};
const char *DTaskInfoChinese[] = {
	"一"
};	
void dataD(char *filename, int *nargs, int tasknum, int testnum)
{
	for (int i = 0; i < 8; i++)
		filename[i] = (char)(rand() % 26 + 97);
	filename[8] = '\0';
	strcat(filename, testfileext);
	// rand args
	*nargs = 6 + 1;
	for (int i = 0; i < *nargs; i++)
	{
		args[i] = (char *)malloc(50);
	}
	args[1] = "ls";
	args[2] = "1";
	args[3] = "-l";
	args[4] = "ps";
	args[5] = "1";
	args[6] = "-u";
	int N = atoi(args[2]);
	int M = atoi(args[3 + N + 1]);
	// end
	int f = open(controlfilename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	dup2(f, STDOUT_FILENO);
	close(f);
	int pid;
	switch (tasknum)
	{
	case 1:
		pid = fork();
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
		break;
	default:
		break;
	}
}