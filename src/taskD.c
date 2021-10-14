#include "taskD.h"
#include "variable.h"

const char *DTaskInfoRussian[] = {
	"Написать программу shellD1, моделирующую конструкцию командного интерпретатора:\ncmdA A1 A2 … AN ; cmdB B1 B2 … BM\nЭта конструкция обеспечивает последовательное выполнение команд cmdA и cmdB:вначале запускается команда cmdA с параметрами A1, A2, …, AN, затем запускается команда cmdB с параметрами B1, B2, …, BM. Каждая команда использует стандартный вывод на экран.\nФормат вызова программы shellD1:\nshellD1 cmdA N A1 A2 … AN cmdB M B1 B2 … BM\n"
};
const char *DTaskInfoChinese[] = {
	"一\n"
};
void dataD(char *filename, int *nargs, int tasknum, int testnum)
{
	for (int i = 0; i < 8; i++)
		filename[i] = (char)(rand() % 26 + 97);
	filename[8] = '\0';
	strcat(filename, testfileext);
	int f = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	close(f);
	// rand args
	*nargs = 6 + 1;
	for (int i = 0; i < *nargs; i++)
	{
		args[i] = (char *)malloc(50);
	}
	strcpy(args[1],"ls");
	strcpy(args[2],"1");
	strcpy(args[3],"-r");
	strcpy(args[4],"cat");
	strcpy(args[5],"1");
	strcpy(args[6],"/etc/passwd");
	// end
	f = open(controlfilename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	int backup = dup(STDOUT_FILENO);
	dup2(f, STDOUT_FILENO);
	close(f);
	switch (tasknum)
	{
	case 1:
		system("ls -r; cat /etc/passwd");
		break;
	default:
		break;
	}
	dup2(backup,STDOUT_FILENO);
}
