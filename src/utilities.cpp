#include "utilities.hpp"

bool fileexists(std::string filename)
{
	int f = open(filename.c_str(), O_RDONLY);
	if (f == -1)
	{
		return false;
	}
	close(f);
	return true;
}
void show_file(const char *name, char *comment, int filetype)
// filetype == 0 for binary and .gcclog files,
//             1 for _control.tst file,
//             2 for other .tst files
{
	int flines = 1000;
	char cmd[200];
	if (filetype != 1)
		printf("%s===%s%s===%s\n", CYAN, comment, name, BROWN);
	else
		printf("%s===%s===%s\n", CYAN, comment, BROWN);
	if (filetype == 0 || flines >= 1000)
	{
		sprintf(cmd, "cat %s", name);
		system(cmd);
		printf("%s===End Of File===%s\n", CYAN, RESET);
	}
	else
	{
		int f = open(name, O_RDONLY);
		int n;
		int cnt = 0;
		while ((n = read_line(f, cmd, 200)) > 0)
		{
			cnt++;
			if (cnt <= flines)
				printf("%s", cmd);
			else
			{
				break;
			}
		}
		close(f);
		if (cnt <= flines)
			printf("%s===End of file===%s\n", CYAN, RESET);
		else
			printf("%s===%d initial lines of file are shown===%s\n", CYAN, flines, RESET);
	}
}
ssize_t read_line(int fd, void *sbuf, size_t sbufsize)
{
	ssize_t n, rc;
	char c, *ptr;
	ptr = (char*)sbuf;
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