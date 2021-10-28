#ifndef TASKCHECKER_H
#define TASKCHECKER_H

#include "color.h"
#include "variable.h"
#include "utilities.h"

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

#define VALID_I(i) (i + 1 < argc)
#define VALID_ARG(str1, str2) (strcmp(argv[i], str1) == 0 || strcmp(argv[i], str2) == 0)

#endif