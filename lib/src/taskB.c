#include "taskB.h"

char *testfileext = ".tst";
char *controlfilename = "_control.tst";
int maxtasknum = 17;

const char *TaskInfoRussian[] = {
    "Дан символьный файл. Изменить порядок следования его элементов на противоположный.\nНапример, файл с символами ABCDE должен измениться на EDCBA.\n",
    "Дан символьный файл. Заменить все входящие в него заглавные латинские буквы на маленькие и изменить порядок следования его элементов на противоположный.\nНапример, файл с символами A12BmnCD9E должен измениться на e9dcnmb21a\n",
    "Дан символьный файл, содержащий более 10 элементов.\nУменьшить его размер до 10 элементов, удалив из файла необходимое количество конечных элементов.\n",
    "Дан символьный файл, содержащий четное количество элементов.\nУдалить из данного файла вторую половину элементов.\n",
    "Дан символьный файл, содержащий более 10 элементов.\nУменьшить его размер до 10 элементов, удалив из файла необходимое количество начальных элементов.\n",
    "Дан символьный файл, содержащий четное количество элементов.\nУдалить из данного файла первую половину элементов.\n",
    "Дан символьный файл. Удалить из него все элементы с четными номерами (элементы нумеруются от 1).\nНапример, файл с символами ABCDEFG должен измениться на ACEG.\n",
    "Дан символьный файл. Удалить из него все цифровые символы.\nНапример, файл с символами A11B2CD43F должен измениться на ABCDF\n",
    "Дан символьный файл. Удалить из него все заглавные латинские буквы и изменить порядок следования его элементов на противоположный.\nНапример, файл с символами A11b2Cd43F должен измениться на 34d2b11.\n",
    "Дан символьный файл, содержащий менее 20 элементов. Увеличить его размер до 20 элементов, записав в начало файла необходимое количество символов «A».\n",
    "Дан символьный файл. Удвоить его размер, записав в конец файла все его исходные элементы (в том же порядке).\nНапример, файл с символами ABCD должен измениться на ABCDABCD.\n",
    "Дан символьный файл. Удвоить его размер, записав в конец файла все его исходные элементы (в обратном порядке).\nНапример, файл с символами ABCD должен измениться на ABCDDCBA.\n",
    "Дан символьный файл. Продублировать в нем все элементы с нечетными номерами (элементы нумеруются от 1).\nНапример, файл с символами ABCDEF должен измениться на AABCCDEEF.\n",
    "Дан символьный файл. Продублировать в нем все цифровые символы.\nНапример, файл с символами A23EF4S должен измениться на A2233EF44S\n",
    "Дан символьный файл. Заменить в нем каждый элемент с четным номером на два символа «X» (элементы нумеруются от 1).\nНапример, файл с символами ABCDEFдолжен измениться на AXXCXXEXX.\n",
    "Дан символьный файл. Заменить в нем каждый цифровой символ на три символа «A».\nНапример, файл с символами A1B2C34 должен измениться на AAAABAAACAAAAAA.\n",
    "Дан символьный файл с элементами A1, A2, …, AN (N — количество элементов в файле). Заменить исходное расположение его элементов на следующее:\nA1, AN, A2, AN−1, A3, …\nНапример, файл с символами ABCDEFGHI должен измениться на AIBHCGDFE.\n"};
const char *TaskInfoChinese[] = {
    "给定一个字符文件。 颠倒其元素的顺序。 \n例如，带有符号 ABCDE 的文件应更改为 EDCBA。\n",
    "给定一个字符文件。 将其中包含的所有大写拉丁字母替换为小写字母，并将其元素的顺序改为相反。\n例如，符号文件 A12BmnCD9E 应更改为 e9dcnmb21a。\n",
    "给定一个包含 10 个以上元素的字符文件。 通过从文件中删除所需数量的有限元素，将其大小减少到 10 个元素。\n",
    "给定一个包含偶数个元素的字符文件。 从此文件中删除项目的后半部分。\n",
    "给定一个包含 10 个以上元素的字符文件。 通过从文件中删除所需数量的初始元素，将其大小减少到 10 个元素。\n",
    "给定一个包含偶数个元素的字符文件。 从给定文件中删除项目的前半部分。\n",
    "给定一个字符文件。 从中删除所有偶数元素（元素从 1 开始编号）。\n例如，包含字符 ABCDEFG 的文件应更改为 ACEG。\n",
    "给定一个字符文件。 从中删除所有数字字符。\n例如，符号文件 A11B2CD43F 应更改为 ABCDF。\n",
    "给定一个字符文件。 从中删除所有大写拉丁字母并反转其元素的顺序。\n例如，带有符号 A11b2Cd43F 的文件应更改为 34d2b11。\n",
    "给定一个少于 20 个元素的字符文件。 通过在文件开头写入所需数量的字符“A”，将其大小增加到 20 个元素。\n",
    "给定一个字符文件。 通过将所有原始元素写入文件末尾（按相同顺序）将其大小加倍。\n例如，包含字符 ABCD 的文件应更改为 ABCDABCD。\n",
    "给定一个字符文件。 通过将其所有原始元素写入文件末尾（以相反顺序）将其大小加倍。\n例如，包含字符 ABCD 的文件应更改为 ABCDDCBA。\n",
    "给定一个字符文件。 复制其中的所有奇数元素（元素从 1 开始编号）。\n例如，包含字符 ABCDEF 的文件应更改为 AABCCDEEF。\n",
    "给定一个字符文件。 复制其中的所有数字字符。\n例如，字符文件中 A23EF4S 应更改为 A2233EF44S。\n",
    "给定一个字符文件。 将其中的每个偶数元素替换为两个“X”字符（元素从 1 开始编号）。\n例如，带有符号 ABCDEF 的文件应更改为 AXXCXXXXX。\n",
    "给定一个字符文件。 用三个“A”字符替换其中的每个数字字符。\n例如，字符文件 A1B2C34 应更改为 AAAABAAACAAAAAA。\n",
    "给定一个字符文件，其中包含元素 A1、A2、...、AN（N 是文件中的元素数）。 用以下内容替换其元素的原始布局：\nA1, AN, A2, AN − 1, A3, ....\n例如，带有符号 ABCDEFGHI 的文件应更改为 AIBHCGDFE。\n",
};
void data(int *nargs, char **args, char *filename, char *filename2, int tasknum, int testnum)
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
void printData(char *cmd, int nargs, char **args, char *outfilename, char *filename, char *filename2)
{
	sprintf(cmd, "%s ", outfilename);
	strcat(cmd, filename);
	puts(cmd);
}
void execData(char* outfilename,char* filename,int nargs,char** args)
{
	execl(outfilename, outfilename, filename, (char *)0);
}
int filecompare(char *name1, char *name2)
{
	int f1 = open(name1, O_RDONLY);
	int f2 = open(name2, O_RDONLY);
	char buf1[100];
	char buf2[100];
	int n1 = read(f1, buf1, sizeof(buf1));
	int n2 = read(f2, buf2, sizeof(buf2));
	close(f1);
	close(f2);
	if (n1 != n2)
		return 1;
	for (int i = 0; i < n1; i++)
		if (buf1[i] != buf2[i])
			return 2;
	return 0;
}
void printTaskInfo(int tasknum, char *language)
{
	if (strcmp(language, "ch") == 0)
		printf("%s", TaskInfoChinese[tasknum - 1]);
	else
		printf("%s", TaskInfoRussian[tasknum - 1]);
}
int getMaxtasknum()
{
	return maxtasknum;
}
