#include "variable.h"

char *testfileext = ".tst";
char *controlfilename = "_control.tst";
char *hline = "------------------------------------------------------";
int totaltests = 3;
int maxtasknum = 0;
int flines = 1000;
char cmd[1000];
char *args[10];
void *handler = (void*)0;