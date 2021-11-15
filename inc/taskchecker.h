#ifndef TASKCHECKER_H
#define TASKCHECKER_H

#include "color.h"
#include "variable.h"
#include "utilities.h"
#include "service.h"

typedef int GetMaxTasknum();
typedef int FileCompare(char *, char *);
typedef void GenerateData(int *, char **, char *, char *, int, int);
typedef void PrintData(char *, int, char **, char *, char *, char *);
typedef void ExecData(char *, char *, int, char **);
typedef void PrintTaskInfo(int, char *);
struct TaskChecker
{
	GetMaxTasknum *getMaxtasknum;
	FileCompare *filecompare;
	GenerateData *data;
	PrintData *printData;
	ExecData *execData;
	PrintTaskInfo *printTaskInfo;
};
const struct TaskChecker *taskchecker;
void removetstfiles();
void showfile(char *name, char *comment, int filetype);
void analyseCmd(int argc, char **argv, char *taskgroup, int *tasknum, char *program, char *language);
void printTask(int tasknum, char *language);
void checkTasklib(char *tasklib, char taskgroup);
void checkTasknum(int tasknum);
void checkTaskresult(char *filename, char *controlfilename, int tt);
void complieProgram(char *program, char *outfilename);
void runTasktest(char taskgroup, int tasknum, char *filename, char *outfilename, int tt);
void printHelp();
void updateTaskCode(char *program);

#define VALID_I(i) (i + 1 < argc)
#define VALID_ARG(str1, str2) (strcmp(argv[i], str1) == 0 || strcmp(argv[i], str2) == 0)

#endif