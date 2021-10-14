#ifndef TASKCHECKER_H
#define TASKCHECKER_H

#include "color.h"
#include "taskB.h"
#include "taskC.h"
#include "taskD.h"
#include "variable.h"

void removetstfiles();
void showfile(char *name, char *comment, int filetype);
int filecompareB(char *name1, char *name2);
int filecompareC(char *name1, char *name2);
int filecompareD(char *name1, char *name2);
int fileexists(char *name);
void printTask(char taskgroup, int tasknum, char *language);
void printHelp();
#define VALID_I(i) (i + 1 < argc)
#define VALID_ARG(str1, str2) (strcmp(argv[i], str1) == 0 || strcmp(argv[i], str2) == 0)

#endif