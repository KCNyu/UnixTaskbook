#include "taskchecker.h"

void removetstfiles()
{
	struct dirent *dirp;
	DIR *dp = opendir(".");
	while ((dirp = readdir(dp)) != NULL)
	{
		char *p = strrchr(dirp->d_name, '.');
		if (p != NULL && (strcmp(p, ".tst") == 0 || strcmp(p, ".gcclog") == 0))
			unlink(dirp->d_name);
	}
}

void showfile(char *name, char *comment, int filetype)
// filetype == 0 for binary and .gcclog files,
//             1 for _control.tst file,
//             2 for other .tst files
{
	char cmd[200];
	if (filetype != 1)
		printf("%s===%s%s===%s\n", CYAN, comment, name, BROWN);
	else
		printf("%s===%s===%s\n", CYAN, comment, BROWN);
	if (filetype == 0 || flines >= 1000)
	{
		sprintf(cmd, "cat %s", name);
		system(cmd);
		printf("%s===End Of File===%s\n", CYAN, RESET);
	}
	else
	{
		int f = open(name, O_RDONLY);
		int n;
		int cnt = 0;
		while ((n = readline(f, cmd, 200)) > 0)
		{
			cnt++;
			if (cnt <= flines)
				printf("%s", cmd);
			else
			{
				break;
			}
		}
		close(f);
		if (cnt <= flines)
			printf("%s===End of file===%s\n", CYAN, RESET);
		else
			printf("%s===%d initial lines of file are shown===%s\n", CYAN, flines, RESET);
	}
}

int filecompareB(char *name1, char *name2)
{
	int f1 = open(name1, O_RDONLY);
	int f2 = open(name2, O_RDONLY);
	char buf1[100];
	char buf2[100];
	int n1 = read(f1, buf1, sizeof(buf1));
	int n2 = read(f2, buf2, sizeof(buf2));
	close(f1);
	close(f2);
	if (n1 != n2)
		return 1;
	for (int i = 0; i < n1; i++)
		if (buf1[i] != buf2[i])
			return 2;
	return 0;
}

int filecompareC(char *name1, char *name2)
{
	int f1 = open(name1, O_RDONLY);
	int f2 = open(name2, O_RDONLY);
	char buf1[100];
	char buf2[100];
	int res = 0;
	int n1, n2;
	while (1)
	{
		n1 = readline(f1, buf1, 100);
		n2 = readline(f2, buf2, 100);
		if (n1 != n2)
		{
			res = 1;
			break;
		}
		if (n1 == 0)
			break;
		else if (strcmp(buf1, buf2) != 0)
		{
			res = 2;
			break;
		}
	}
	close(f1);
	close(f2);
	return res;
}

int filecompareD(char *name1, char *name2)
{
	int f1 = open(name1, O_RDONLY);
	int f2 = open(name2, O_RDONLY);
	char buf1[50000];
	char buf2[50000];
	int n1 = read(f1, buf1, sizeof(buf1));
	int n2 = read(f2, buf2, sizeof(buf2));
	close(f1);
	close(f2);
	if (n1 != n2)
		return 1;
	for (int i = 0; i < n1; i++)
		if (buf1[i] != buf2[i])
			return 2;
	return 0;
}

int fileexists(char *name)
{
	int f = open(name, O_RDONLY);
	if (f == -1)
		return 0;
	close(f);
	return 1;
}

void printTask(char taskgroup, int tasknum, char *language)
{
	printf("%sTASK INFO:%s\n", BLUE, RESET);
	switch (taskgroup)
	{
	case 'B':
		if (strcmp(language, "ch") == 0)
			printf("%s", BTaskInfoChinese[tasknum - 1]);
		else
			printf("%s", BTaskInfoRussian[tasknum - 1]);
		break;
	case 'C':
		if (strcmp(language, "ch") == 0)
			printf("%s", CTaskInfoChinese[tasknum - 1]);
		else
			printf("%s", CTaskInfoRussian[tasknum - 1]);
		break;
	case 'D':
		if (strcmp(language, "ch") == 0)
			printf("%s", DTaskInfoChinese[tasknum - 1]);
		else
			printf("%s", DTaskInfoRussian[tasknum - 1]);
		break;
	}
}
void analyseCmd(int argc, char **argv, char *taskgroup, int *tasknum, char *program, char *language)
{
	bool flag = false;
	for (int i = 1; i < argc; i++)
	{
		if (flag)
		{
			flag = false;
			continue;
		}
		if (VALID_ARG("-t", "--taskname"))
		{
			if (VALID_I(i))
			{
				*taskgroup = toupper(argv[i + 1][0]);
				*tasknum = atoi(argv[i + 1] + 1);
				flag = true;
			}
		}
		else if (VALID_ARG("-l", "--language"))
		{
			if (VALID_I(i))
			{
				strcpy(language, argv[i + 1]);
				flag = true;
			}
		}
		else if (VALID_ARG("-p", "--program"))
		{
			if (VALID_I(i))
			{
				strcpy(program, argv[i + 1]);
				flag = true;
			}
		}
		else if (VALID_ARG("-d", "--directory"))
		{
		}
		else if (VALID_ARG("-n", "--number"))
		{
			if (VALID_I(i))
			{
				flines = atoi(argv[i + 1]);
				if (flines <= 0)
					flines = 5;
				flag = true;
			}
		}
		else if (VALID_ARG("-h", "--help"))
		{
			printHelp();
			exit(2);
		}
		else
		{
			printf("Error: invalid option '%s'\n", argv[i]);
			exit(2);
		}
	}
}
void printHelp()
{
	printf("%sUsage%s: TaskChecker [OPTION]... [FILE]...\n", BLUE, RESET);
	printf("Development of a system for automatic verification of educational tasks in Linux.\nMandatory arguments to long options are mandatory for short options too.\n");
	printf("-t, --taskname		  display the taskInfo\n");
	printf("-l, --language		  language be displayed  <default Russian> <support [ru] [en] [ch]>\n");
	printf("-p, --program		  check single program\n");
	printf("-d, --directory		  check all programs in the directory\n");
	printf("-n, --number		  number of file lines\n");
	printf("-h, --help		  display this help and exit\n");
}