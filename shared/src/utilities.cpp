#include "utilities.hpp"

bool exists_file(std::string filename)
{
	int f = open(filename.c_str(), O_RDONLY);
	if (f == -1)
	{
		return false;
	}
	close(f);
	return true;
}
void show_file(const char *name, const char *comment, int filetype)
// filetype == 0 for binary and .gcclog files,
//             1 for _control.tst file,
//             2 for other .tst files
{
	int flines = 1000;
	char cmd[200];
	if (filetype != 1)
	{
		std::cout << CYAN << "===" << comment << name << "===" << BROWN << std::endl;
	}
	else
	{
		std::cout << CYAN << "===" << comment << BROWN << std::endl;
	}
	if (filetype == 0 || flines >= 1000)
	{
		sprintf(cmd, "cat %s", name);
		system(cmd);
		LOG_FILE("\n===End Of File===");
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
			{
				std::cout << cmd;
			}
			else
			{
				break;
			}
		}
		close(f);
		if (cnt <= flines)
		{
			LOG_FILE("===End of file===");
		}
		else
		{
			LOG_FILE("===%d initial lines of file are shown===", flines);
		}
	}
}
void show_file(std::string name, const char *comment, int filetype)
{
	show_file(name.c_str(), comment, filetype);
}
ssize_t read_line(int fd, void *sbuf, size_t sbufsize)
{
	ssize_t n, rc;
	char c, *ptr;
	ptr = (char *)sbuf;
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
		{
			return -1;
		}
	}
	*ptr = 0;
	return n - 1;
}
int compare_file(const char *name1, const char *name2)
{
	int f1 = open(name1, O_RDONLY);
	int f2 = open(name2, O_RDONLY);
	char buf1[MAX_SIZE];
	char buf2[MAX_SIZE];
	int n1 = read(f1, buf1, sizeof(buf1));
	int n2 = read(f2, buf2, sizeof(buf2));
	close(f1);
	close(f2);
	if (n1 != n2)
	{
		return 1;
	}

	for (int i = 0; i < n1; i++)
	{
		if (buf1[i] != buf2[i])
		{
			return 2;
		}
	}

	return 0;
}
int compare_file(std::string name1, std::string name2)
{
	return compare_file(name1.c_str(), name2.c_str());
}