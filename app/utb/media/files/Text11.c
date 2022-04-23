/*
给定一个整数 K 和一个文本文件。
从文件中删除行号 K（行从 1 开始编号）。
如果没有带有此编号的行，则保持文件不变。
*/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#include <stdlib.h>
#define BUFFSIZE 4096
static int read_cnt;
static char *read_ptr;
static char read_buf[BUFFSIZE];

void err_sys(const char *info)
{
	perror(info);
	exit(1);
}
static ssize_t my_read(int fd, char *ptr)
{
	if (read_cnt <= 0)
	{
		if ((read_cnt = read(fd, read_buf, sizeof(read_buf))) < 0)
			return -1;
		else if (read_cnt == 0)
			return 0;
		read_ptr = read_buf;
	}
	read_cnt--;
	*ptr = *read_ptr++;
	return 1;
}
ssize_t readline(int fd, void *sbuf, size_t sbufsize)
{
	ssize_t n, rc;
	char c, *ptr;
	ptr = sbuf;
	for (n = 1; n < sbufsize; n++)
	{
		if ((rc = my_read(fd, &c)) == 1)
		{
			if (c == '\r')
			{
				n--;
				continue;
			}
			*ptr++ = c;
			if (c == '\n')
			{
				*ptr = 0;
				return n;
			}
		}
		else if (rc == 0)
		{
			*ptr = 0;
			return n - 1;
		}
		else
			return -1;
	}
	*ptr = 0;
	return n - 1;
}
ssize_t readlinebuf(void **ppbuf)
{
	if (read_cnt)
		*ppbuf = read_ptr;
	return read_cnt;
}
int main(int argc, char **argv)
{
	if (argc != 3)
	{
		// printf("Usage: changefile <filename>");
		printf("Usage: taskxx.out k <filename>");
		return 1;
	}
	char s[300];
	char S[BUFFSIZE];
	strcpy(S, argv[1]);
	strcat(S, "\n");
	strcpy(s, "cp test0.txt ");
	strcat(s, argv[2]);
	// printf(s);
	// printf("\n");
	// system(s);

	int f1 = open(argv[2], O_RDONLY);
	if (f1 == -1)
		err_sys(argv[2]);

	struct stat statbuf;
	if (stat(argv[2], &statbuf) != 0)
		err_sys(argv[2]);

	char *tmpfilename = "tmpfile.tmp";
	int f2 = open(tmpfilename, O_WRONLY | O_CREAT | O_TRUNC, statbuf.st_mode);

	if (f2 == -1)
		err_sys(tmpfilename);

	int i = 1;
	ssize_t n;
	char buf[BUFFSIZE];
	int size = strlen(S);
	//printf(S);
	int k = atoi(argv[1]);
	int j = 0;
	while ((n = readline(f1, buf, sizeof(buf))) > 0)
	{
		j++;
		if (j == k)
			continue;
		write(f2, buf, n);
		// printf(buf);
	}
	close(f1);
	close(f2);
	rename(tmpfilename, argv[2]);
	// printf("\n OK");
	return 0;
}
