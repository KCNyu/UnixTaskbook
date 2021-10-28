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

void checkTasklib(char *tasklib, char taskgroup)
{
	sprintf(tasklib, "libtask%c.so", taskgroup);
	handler = dlopen(tasklib, RTLD_LAZY);
	if (handler == NULL)
	{
		printf("%s\n", dlerror());
		exit(-1);
	}
}
void checkTasknum(int tasknum)
{
	int (*getMaxtasknum)() = dlsym(handler, "getMaxtasknum");
	int maxtasknum = getMaxtasknum();
	if (tasknum < 1 || tasknum > maxtasknum)
	{
		printf("Error: Wrong task number: %d\n", tasknum);
		exit(4);
	}
}
void checkTaskresult(char *filename, char *controlfilename, int tt)
{
	printf("%sChecking results...\n%s", BLUE, RESET);
	showfile(filename, "Result file: ", 2);

	int (*filecompare)(char *, char *) = dlsym(handler, "filecompare");
	int rescomp = filecompare(filename, controlfilename);
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
void complieProgram(char *program, char *outfilename)
{
	if (!fileexists(program))
	{
		printf("Error: Checked program %s not found\n", program);
		exit(5);
	}
	char logfilename[150];
	strcpy(logfilename, program);
	strcat(logfilename, ".gcclog");
	strcpy(outfilename, program);
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
		execlp("gcc", "gcc", "-Wall", program, "-o", outfilename, (char *)0);
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
		exit(6);
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
}
void runTasktest(char taskgroup, int tasknum, char *filename, char *outfilename, int tt)
{
	int nargs = 1;
	char filename2[20];
	for (int i = 0; i < 10; i++)
		args[i] = (char *)0;
	printf("%sTest %d (of %d):\n%s", BLUE, tt, totaltests, RESET);
	void (*data)(int *, char **, char *, char *, int, int) = dlsym(handler, "data");
	data(&nargs, args, filename, filename2, tasknum, tt);
	void (*printData)(char *, int, char **, char *, char *, char *) = dlsym(handler, "printData");
	printData(cmd, nargs, args, outfilename, filename, filename2);
	if (taskgroup == 'B')
	{
		showfile(filename, "Input file: ", 0);
	}
	else if (taskgroup == 'C')
	{
		if (strlen(filename2) == 0)
			showfile(filename, "Input file: ", 2);
		else
		{
			showfile(filename, "Input file1: ", 2);
			showfile(filename2, "Input file2: ", 2);
		}
	}
	else if (taskgroup == 'D')
	{
		// showfile(filename, "Input file: ", 0);
	}
	printf("Program output:\n%s\n", hline);
	void (*execData)(char *, char *, int, char **) = dlsym(handler, "execData");

	int f, status;
	pid_t pid = fork();
	if (pid == 0)
	{
		execData(outfilename, filename, nargs, args);
		printf("%sError when running program %s\n%s.", RED, outfilename, RESET);
		exit(7);
	}
	pid = waitpid(pid, &status, 0);
	printf("\n%s\n", hline);
	if (pid < 0)
		err_sys("Error during running: ");
}
void printTask(int tasknum, char *language)
{
	printf("%sTASK INFO:%s\n", BLUE, RESET);
	void (*printTaskInfo)(int, char *) = dlsym(handler, "printTaskInfo");
	printTaskInfo(tasknum, language);
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