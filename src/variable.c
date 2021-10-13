#include "variable.h"

char testfilename[50];
char *testfileext = ".tst";
char *controlfilename = "_control.tst";
char *hline = "------------------------------------------------------";
int totaltests = 3;
int maxtasknum = 0;
int flines = 1000;
char firsttaskgroup = 'B';
char lasttaskgroup = 'D';
char cmd[1000];
char *args[10];
int textdatasize = 85;