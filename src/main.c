#include "taskchecker.h"

int main(int argc, char *argv[])
{
	srand((unsigned)time(0));
	removetstfiles();
	if (argc < 2)
	{
		printHelp();
		exit(2);
	}
	bool flag = false;
	char taskgroup;
	int tasknum;
	char *program = NULL;
	char language[10] = "ru";
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
				taskgroup = toupper(argv[i + 1][0]);
				tasknum = atoi(argv[i + 1] + 1);
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
				program = argv[i + 1];
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
	if (taskgroup < firsttaskgroup || taskgroup > lasttaskgroup)
	{
		printf("Error: Wrong task group: %c\n", taskgroup);
		exit(3);
	}
	switch (taskgroup)
	{
	case 'B':
		maxtasknum = 17;
		break;
	case 'C':
		maxtasknum = 16;
		break;
	case 'D':
		maxtasknum = 9;
		break;
	}
	if (tasknum < 1 || tasknum > maxtasknum)
	{
		printf("Error: Wrong task number: %d\n", tasknum);
		exit(4);
	}
	if (argc >= 2)
	{
		printTask(taskgroup, tasknum, language);
		if (argc == 2 || program == NULL)
			exit(0);
	}
	if (!fileexists(program))
	{
		printf("Error: Checked program %s not found\n", argv[2]);
		exit(5);
	}
	char logfilename[150];
	strcpy(logfilename, program);
	strcat(logfilename, ".gcclog");
	char outfilename[300];
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
		case 'D':
			dataD(filename, &nargs, tasknum, tt);
			sprintf(cmd, "%s ", outfilename);
			for (int i = 1; i < nargs; i++)
			{
				strcat(cmd, args[i]);
				strcat(cmd, " ");
			}
			puts(cmd);
			// showfile(filename, "Input file: ", 0);
			break;
		}
		printf("Program output:\n%s\n", hline);
		int f;
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
			case 'D':
				f = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
				dup2(f, STDOUT_FILENO);
				close(f);
				args[0] = (char *)malloc(50);
				strcpy(args[0], filename);
				execv(outfilename, args);
				break;
			}
			printf("%sError when running program %s\n%s.", RED, outfilename, RESET);
			exit(7);
		}
		pid = waitpid(pid, &status, 0);
		printf("\n%s\n", hline);
		if (pid < 0)
			err_sys("Error during running: ");
		// puts("Program successfully finished.");

		for (int i = 0; i < 10; i++)
		{
			free(args[i]);
		}
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
		case 'D':
			rescomp = filecompareD(filename, controlfilename);
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
