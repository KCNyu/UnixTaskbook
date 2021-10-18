#ifndef TASKD_H
#define TASKD_H

#include "utilities.h"

extern const char *DTaskInfoRussian[];
extern const char *DTaskInfoChinese[];
extern const char **DTaskTestCmd[];

char *initCmd(int *nargs, const char* conjunctions);
void dataD(char *filename, int *nargs, int tasknum, int testnum);

#endif /* TASKD_H */
