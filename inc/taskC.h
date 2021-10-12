#ifndef TASKC_H
#define TASKC_H

#include "utilities.h"

extern const char *CTaskInfoRussian[];
extern const char *CTaskInfoChinese[];
extern char *textdata[];

void dataC(char *filename, char *filename2, int *nargs, int tasknum, int testnum);

#endif /* TASKC_H */