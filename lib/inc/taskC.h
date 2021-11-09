#ifndef TASKC_H
#define TASKC_H

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <dirent.h>
#include <limits.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>

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

char *testfileext;
char *controlfilename;
int textdatasize;
int maxtasknum;
const char *TaskInfoRussian[];
const char *TaskInfoChinese[];
char *textdata[];

void data(int *nargs, char **args, char *filename, char *filename2, int tasknum, int testnum);
void printData(char *cmd, int nargs, char **args, char *outfilename, char *filename, char *filename2);
void execData(char *outfilename, char *filename, int nargs, char **args);
int filecompare(char *name1, char *name2);
void printTaskInfo(int tasknum, char *language);
int getMaxtasknum();
ssize_t readline(int fd, void *sbuf, size_t sbufsize);

const struct TaskChecker taskchecker = {
    .getMaxtasknum = getMaxtasknum,
    .filecompare = filecompare,
    .data = data,
    .printData = printData,
    .execData = execData,
    .printTaskInfo = printTaskInfo,
};

#endif /* TASKC_H */