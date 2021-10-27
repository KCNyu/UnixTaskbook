#ifndef TASKD_H
#define TASKD_H

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
extern int textdatasize;
extern const char *TaskInfoRussian[];
extern const char *TaskInfoChinese[];
extern const char **DTaskTestCmd[];

char *initCmd1(char**args,int *nargs);
char *initCmd2(char** args,int *nargs, const char* conjunctions);
void data(char** args,char *filename, int *nargs, int tasknum, int testnum);
void printTaskInfo(int tasknum, char *language);
int filecompare(char *name1, char *name2);
int getMaxtasknum();
ssize_t readline(int fd, void *sbuf, size_t sbufsize);

#endif /* TASKD_H */
