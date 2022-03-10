#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <limits.h>
#include <sys/stat.h>
#include <sys/types.h>
void err_sys(const char *info)
{
    perror(info);
    exit(1);
}
typedef int Myfunc(const char *, const struct stat *, int);
static Myfunc myfunc;
static int myscan(char *, Myfunc *);
static int dopath(Myfunc *);
int main(int argc, char *argv[])
{
    int ret = 0;
#if 0
    if (argc != 2)
        printf("Usage: scandir <initial directory>\n");
    else
    {
        ret = myscan(argv[1], myfunc); /* performs all work */
        //printf("OK\n");
    }
#endif
    if (argc == 1)
    {
        ret = myscan(".", myfunc); /* performs all work */
    }
    else
    {
        ret = myscan(argv[1], myfunc); /* performs all work */
    }
    return ret;
}

#define FILEINFO 1         /* not a directory */
#define DIRINFO 2          /* accessible directory */
#define NODIRINFO 3        /* unaccessible directory */
#define NOFILEINFO 4       /* unknown file type */
static char fullpath[300]; /* full path to each file */
static int myscan(char *initpathname, Myfunc *func)
{
    strcpy(fullpath, initpathname);
    return dopath(func);
}
static int dopath(Myfunc *func)
{
    struct stat statbuf;
    struct dirent *dirp;
    DIR *dp;
    int ret;
    if (lstat(fullpath, &statbuf) < 0) /* stat error */
        return func(fullpath, &statbuf, NOFILEINFO);
    if (S_ISDIR(statbuf.st_mode) == 0) /* not a directory */
        return (func(fullpath, &statbuf, FILEINFO));
    /*
     * This is a directory. Call func(),
     * then process all files in this directory recursively.
     */
    if ((ret = func(fullpath, &statbuf, DIRINFO)) != 0)
        return ret;
    size_t n = strlen(fullpath);
    fullpath[n++] = '/';
    fullpath[n] = 0;
    if ((dp = opendir(fullpath)) == NULL) /* unaccessible directory */
        return func(fullpath, &statbuf, NODIRINFO);
    while ((dirp = readdir(dp)) != NULL)
    {
        if (strcmp(dirp->d_name, ".") == 0 ||
            strcmp(dirp->d_name, "..") == 0)
            continue;                       /* skip "." и ".." */
        strcpy(&fullpath[n], dirp->d_name); /* add name after slash */
        if ((ret = dopath(func)) != 0)      /* recursive call */
            break;                          /* error */
    }
    fullpath[n - 1] = 0; /* remove right part of the filename */
    if (closedir(dp) < 0)
        err_sys("closedir error");
    return ret;
}
static int myfunc(const char *pathname, const struct stat *statptr, int type)
{
    /*
    switch (type)
    {
    case FILEINFO:
        if (S_ISREG(statptr->st_mode))
            printf("File: ");
        else if (S_ISFIFO(statptr->st_mode))
            printf("FIFO: ");
        else if (S_ISLNK(statptr->st_mode))
            printf("Link: ");
        else if (S_ISSOCK(statptr->st_mode))
            printf("Socket: ");
        break;
    case DIRINFO:
        printf("Dir: ");
        break;
    case NODIRINFO:
        printf("Unaccessible dir: ");
        break;
    default:
        printf("Unknown filetype: ");
    }
    */
    printf("%s\n", pathname);
    return 0;
}