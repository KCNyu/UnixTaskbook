#include "taskB.h"
#include "variable.h"

void dataB(char *filename, int tasknum, int testnum)
{
	for (int i = 0; i < 8; i++)
		filename[i] = (char)(rand() % 26 + 97);
	filename[8] = '\0';
	strcat(filename, testfileext);
	int f = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	int sz = (10 + rand() % 10) * 2;
	if (tasknum == 10)
		sz = 9 + rand() % 8;
	if (tasknum != 4 && tasknum != 6)
		sz += rand() % 2;
	char c[50];
	int r[4];
	do
	{
		for (int i = 0; i < 4; i++)
			r[i] = 0;

		for (int i = 0; i < sz; i++)
			switch (rand() % 4)
			{
			case 0:
				c[i] = (char)(rand() % 10 + 48);
				r[0]++;
				break;
			case 1:
				c[i] = (char)(rand() % 26 + 65);
				r[1]++;
				break;
			case 2:
				c[i] = (char)(rand() % 26 + 97);
				r[2]++;
				break;
			case 3:
				c[i] = (char)(rand() % 16 + 33);
				r[3]++;
				break;
			}
	} while (r[0] < 2 || r[1] < 2 || r[2] < 2 || r[3] < 2);
	write(f, c, sz);
	close(f);
	f = open(controlfilename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	char c0 = 'A';
	char *xx = "XX";
	char *aaa = "AAA";
	switch (tasknum)
	{
	case 1:
		for (int i = sz - 1; i >= 0; i--)
			write(f, &c[i], 1);
		break;
	case 2:
		for (int i = sz - 1; i >= 0; i--)
		{
			c[i] = tolower(c[i]);
			write(f, &c[i], 1);
		}
		break;
	case 3:
		for (int i = 0; i < 10; i++)
			write(f, &c[i], 1);
		break;
	case 4:
		for (int i = 0; i < sz / 2; i++)
			write(f, &c[i], 1);
		break;
	case 5:
		for (int i = sz - 10; i < sz; i++)
			write(f, &c[i], 1);
		break;
	case 6:
		for (int i = sz / 2; i < sz; i++)
			write(f, &c[i], 1);
		break;
	case 7:
		for (int i = 0; i < sz; i++)
			if (i % 2 == 0)
				write(f, &c[i], 1);
		break;
	case 8:
		for (int i = 0; i < sz; i++)
			if (!isdigit(c[i]))
				write(f, &c[i], 1);
		break;
	case 9:
		for (int i = sz - 1; i >= 0; i--)
			if (!isupper(c[i]))
				write(f, &c[i], 1);
		break;
	case 10:
		for (int i = 0; i < 20 - sz; i++)
			write(f, &c0, 1);
		for (int i = 0; i < sz; i++)
			write(f, &c[i], 1);
		break;
	case 11:
		for (int i = 0; i < sz; i++)
			write(f, &c[i], 1);
		for (int i = 0; i < sz; i++)
			write(f, &c[i], 1);
		break;
	case 12:
		for (int i = 0; i < sz; i++)
			write(f, &c[i], 1);
		for (int i = sz - 1; i >= 0; i--)
			write(f, &c[i], 1);
		break;
	case 13:
		for (int i = 0; i < sz; i++)
		{
			write(f, &c[i], 1);
			if (i % 2 == 0)
				write(f, &c[i], 1);
		}
		break;
	case 14:
		for (int i = 0; i < sz; i++)
		{
			write(f, &c[i], 1);
			if (isdigit(c[i]))
				write(f, &c[i], 1);
		}
		break;
	case 15:
		for (int i = 0; i < sz; i++)
		{
			if (i % 2 == 0)
				write(f, &c[i], 1);
			else
				write(f, xx, 2);
		}
		break;
	case 16:
		for (int i = 0; i < sz; i++)
		{
			if (!isdigit(c[i]))
				write(f, &c[i], 1);
			else
				write(f, aaa, 3);
		}
		break;
	case 17:
		for (int i = 0; i < sz / 2; i++)
		{
			write(f, &c[i], 1);
			write(f, &c[sz - i - 1], 1);
		}
		if (sz % 2 != 0)
			write(f, &c[sz / 2], 1);
		break;
	}
	close(f);
}