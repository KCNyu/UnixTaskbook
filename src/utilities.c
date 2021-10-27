#include "utilities.h"

void err_sys(const char *info)
{
	perror(info);
	exit(1);
}
ssize_t readline(int fd, void *sbuf, size_t sbufsize)
{
	ssize_t n, rc;
	char c, *ptr;
	ptr = sbuf;
	for (n = 1; n < sbufsize; n++)
	{
		if ((rc = read(fd, &c, 1)) == 1)
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