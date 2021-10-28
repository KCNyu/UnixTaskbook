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

extern char *testfileext;
extern char *controlfilename;
extern int maxtasknum;
extern const char *TaskInfoRussian[];
extern const char *TaskInfoChinese[];

void data(int *nargs, char** args, char *filename, char *filename2, int tasknum, int testnum);
void printData(char* cmd, int nargs, char** args, char* outfilename, char* filename, char* filename2);
void execData(char* outfilename,char* filename,int nargs,char** args);
void printTaskInfo(int tasknum, char *language);
int filecompare(char *name1, char *name2);
int getMaxtasknum();


#endif /* TASKB_H */