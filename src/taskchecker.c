#include "color.h"
#include "taskB.h"
#include "taskC.h"
#include "utilities.h"
#include "variable.h"

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

int fileexists(char *name)
{
	int f = open(name, O_RDONLY);
	if (f == -1)
		return 0;
	close(f);
	return 1;
}

void PrintTask(char *name, char *language)
{
	char taskname[100];
	char c;
	sprintf(taskname, "./task/%s/%s.txt", language, name);
	int f = open(taskname, O_RDONLY);
	if (f == -1)
	{
		printf("open failed\n");
		return;
	}
	printf("%sTASK INFO:%s\n", BLUE, RESET);
	int n;
	while ((n = read(f, &c, 1)) != 0)
	{
		printf("%c", c);
	}
	close(f);
	printf("\n");
	getchar();
}
int main(int argc, char *argv[])
{
	srand((unsigned)time(0));
	removetstfiles();
	if (argc < 3)
	{
		printf("Format: TaskChecker <task name> <checking program> [<number of file lines>]\n");
		exit(2);
	}
	if (!fileexists(argv[2]))
	{
		printf("Error: Checked program %s not found\n", argv[2]);
		exit(3);
	}
	char taskgroup = toupper(argv[1][0]);
	int tasknum = atoi(argv[1] + 1);
	if (taskgroup < firsttaskgroup || taskgroup > lasttaskgroup)
	{
		printf("Error: Wrong task group: %c\n", taskgroup);
		exit(4);
	}
	switch (taskgroup)
	{
	case 'B':
		maxtasknum = 17;
		break;
	case 'C':
		maxtasknum = 16;
		break;
	}
	if (tasknum < 1 || tasknum > maxtasknum)
	{
		printf("Error: Wrong task number: %d\n", tasknum);
		exit(5);
	}
	if (argc > 3)
		flines = atoi(argv[3]);
	if (flines <= 0)
		flines = 5;
	PrintTask(argv[1],"Russian");
	char logfilename[150];
	strcpy(logfilename, argv[2]);
	strcat(logfilename, ".gcclog");
	char outfilename[300];
	strcpy(outfilename, argv[2]);
	char *p = strrchr(outfilename, '.');
	if (p != NULL)
		*p = '\0';
	strcat(outfilename, ".out");
	int flog = open(logfilename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (flog == -1)
		err_sys("Error during creation log-file: ");
	printf("%s-1-Compilation... %s", BLUE, RESET);
	unlink(outfilename);
	int pid = fork();
	if (pid == 0)
	{
		dup2(flog, 2);
		close(flog);
		execlp("gcc", "gcc", "-Wall", argv[2], "-o", outfilename, (char *)0);
		err_sys("Error when running gcc: ");
	}

	close(flog);
	int status;
	pid = waitpid(pid, &status, 0);
	if (pid < 0)
		err_sys("Error during compilation: ");
	if (!fileexists(outfilename))
	{
		printf("%sError: Compiler outputs some error messages (see file %s):%s\n", RED, logfilename, RESET);
		showfile(logfilename, "", 0);
		exit(5);
	}
	struct stat statbuf;
	stat(logfilename, &statbuf);
	if (statbuf.st_size > 0)
	{
		printf("%sCompiler outputs some warnings (see file %s):%s\n", MAGENTA, logfilename, RESET);
		showfile(logfilename, "", 0);
		printf("%sCompilation is partially successful.\n%s", MAGENTA, RESET);
	}
	else
	{
		unlink(logfilename);
		printf("%sCompilation is successful.\n%s", GREEN, RESET);
	}
	char filename[20];
	char filename2[20];
	int nargs = 1;
	printf("%s-2-Running and checking...\n%s", BLUE, RESET);
	for (int tt = 1; tt <= totaltests; tt++)
	{
		for (int i = 0; i < 10; i++)
			args[i] = (char *)0;
		printf("%sTest %d (of %d):\n%s", BLUE, tt, totaltests, RESET);
		switch (taskgroup)
		{
		case 'B':
			dataB(filename, tasknum, tt);
			sprintf(cmd, "%s ", outfilename);
			strcat(cmd, filename);
			puts(cmd);
			showfile(filename, "Input file: ", 0);
			break;
		case 'C':
			dataC(filename, filename2, &nargs, tasknum, tt);
			sprintf(cmd, "%s ", outfilename);
			for (int i = 1; i <= nargs; i++)
			{
				strcat(cmd, args[i]);
				strcat(cmd, " ");
			}
			puts(cmd);
			if (strlen(filename2) == 0)
				showfile(filename, "Input file: ", 2);
			else
			{
				showfile(filename, "Input file1: ", 2);
				showfile(filename2, "Input file2: ", 2);
			}
			break;
		}
		printf("Program output:\n%s\n", hline);
		pid = fork();
		if (pid == 0)
		{
			switch (taskgroup)
			{
			case 'B':
				execl(outfilename, outfilename, filename, (char *)0);
				break;
			case 'C':
				if (nargs == 1)
					execl(outfilename, outfilename, args[1], (char *)0);
				else if (nargs == 2)
					execl(outfilename, outfilename, args[1], args[2], (char *)0);
				break;
			}
			printf("%sError when running program %s\n%s.", RED, outfilename, RESET);
			exit(6);
		}
		pid = waitpid(pid, &status, 0);
		printf("\n%s\n", hline);
		if (pid < 0)
			err_sys("Error during running: ");
		//puts("Program successfully finished.");
		for (int i = 0; i < 10; i++)
			free(args[i]);

		printf("%sChecking results...\n%s", BLUE, RESET);
		showfile(filename, "Result file: ", 2);
		int rescomp;
		switch (taskgroup)
		{
		case 'B':
			rescomp = filecompareB(filename, controlfilename);
			break;
		case 'C':
			rescomp = filecompareC(filename, controlfilename);
			break;
		}
		switch (rescomp)
		{
		case 0:
			printf("%sCorrect!\n%s", GREEN, RESET);
			break;
		default:
			printf("%sWrong result.\n%s", RED, RESET);
			showfile(controlfilename, "Correct results must be as follows:", 1);
			printf("%sTest %d failed.\n%s", RED, tt, RESET);
			exit(7);
		}
	}
	printf("%sTesting successfully finished.\n%s", GREEN, RESET);
	return 0;
}