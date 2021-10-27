#ifndef TASKB_H
#define TASKB_H

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

extern char testfilename[50];
extern char *testfileext;
extern char *controlfilename;
extern char *hline;
extern int totaltests;
extern int maxtasknum;
extern int flines;
extern char cmd[1000];
extern char *args[10];
extern int textdatasize;
extern const char *TaskInfoRussian[];
extern const char *TaskInfoChinese[];

void data(char *filename, int tasknum, int testnum);
void printTaskInfo(int tasknum, char *language);
int filecompare(char *name1, char *name2);
int getMaxtasknum();

#endif /* TASKB_H */