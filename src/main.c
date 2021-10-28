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

	int tasknum;
	char taskgroup, program[20], language[10], tasklib[30];
	analyseCmd(argc, argv, &taskgroup, &tasknum, program, language);

	checkTasklib(tasklib, taskgroup);
	checkTasknum(tasknum);
	if (argc >= 2)
	{
		printTask(tasknum, language);
		if (argc == 2 || program == NULL)
			exit(0);
	}

	char outfilename[300];
	complieProgram(program, outfilename);

	printf("%s-2-Running and checking...\n%s", BLUE, RESET);
	char filename[20];
	for (int tt = 1; tt <= totaltests; tt++)
	{
		runTasktest(taskgroup, tasknum, filename, outfilename, tt);
		checkTaskresult(filename, controlfilename, tt);
	}
	printf("%sTesting successfully finished.\n%s", GREEN, RESET);
	return 0;
}
