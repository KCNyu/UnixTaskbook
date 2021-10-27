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

char *testfileext;
char *controlfilename;
int textdatasize;
const char *TaskInfoRussian[];
const char *TaskInfoChinese[];
char *textdata[];

void data(char** args, char *filename, char *filename2, int *nargs, int tasknum, int testnum);
int filecompare(char *name1, char *name2);
void printTaskInfo(int tasknum, char *language);
int getMaxtasknum();
ssize_t readline(int fd, void *sbuf, size_t sbufsize);

#endif /* TASKC_H */