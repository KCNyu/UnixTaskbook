#ifndef UTILITIES_H
#define UTILITIES_H

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

void err_sys(const char *info);
ssize_t readline(int fd, void *sbuf, size_t sbufsize);

#endif /* UTILITIES_H */