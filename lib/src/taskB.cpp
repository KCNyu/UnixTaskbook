#include "taskB.hpp"

TaskB::TaskB()
{
	library_name = "libtaskB.so";

	complier = "gcc";

	complie_argv = {complier, "-Wall", "", "-o"};

	task_count = 17;

	total_test_count = 3;

	task_text_russian = {
		"Дан символьный файл. Изменить порядок следования его элементов на противоположный.\nНапример, файл с символами ABCDE должен измениться на EDCBA.",
		"Дан символьный файл. Заменить все входящие в него заглавные латинские буквы на маленькие и изменить порядок следования его элементов на противоположный.\nНапример, файл с символами A12BmnCD9E должен измениться на e9dcnmb21a",
		"Дан символьный файл, содержащий более 10 элементов.\nУменьшить его размер до 10 элементов, удалив из файла необходимое количество конечных элементов.",
		"Дан символьный файл, содержащий четное количество элементов.\nУдалить из данного файла вторую половину элементов.",
		"Дан символьный файл, содержащий более 10 элементов.\nУменьшить его размер до 10 элементов, удалив из файла необходимое количество начальных элементов.",
		"Дан символьный файл, содержащий четное количество элементов.\nУдалить из данного файла первую половину элементов.",
		"Дан символьный файл. Удалить из него все элементы с четными номерами (элементы нумеруются от 1).\nНапример, файл с символами ABCDEFG должен измениться на ACEG.",
		"Дан символьный файл. Удалить из него все цифровые символы.\nНапример, файл с символами A11B2CD43F должен измениться на ABCDF",
		"Дан символьный файл. Удалить из него все заглавные латинские буквы и изменить порядок следования его элементов на противоположный.\nНапример, файл с символами A11b2Cd43F должен измениться на 34d2b11.",
		"Дан символьный файл, содержащий менее 20 элементов. Увеличить его размер до 20 элементов, записав в начало файла необходимое количество символов «A».",
		"Дан символьный файл. Удвоить его размер, записав в конец файла все его исходные элементы (в том же порядке).\nНапример, файл с символами ABCD должен измениться на ABCDABCD.",
		"Дан символьный файл. Удвоить его размер, записав в конец файла все его исходные элементы (в обратном порядке).\nНапример, файл с символами ABCD должен измениться на ABCDDCBA.",
		"Дан символьный файл. Продублировать в нем все элементы с нечетными номерами (элементы нумеруются от 1).\nНапример, файл с символами ABCDEF должен измениться на AABCCDEEF.",
		"Дан символьный файл. Продублировать в нем все цифровые символы.\nНапример, файл с символами A23EF4S должен измениться на A2233EF44S",
		"Дан символьный файл. Заменить в нем каждый элемент с четным номером на два символа «X» (элементы нумеруются от 1).\nНапример, файл с символами ABCDEFдолжен измениться на AXXCXXEXX.",
		"Дан символьный файл. Заменить в нем каждый цифровой символ на три символа «A».\nНапример, файл с символами A1B2C34 должен измениться на AAAABAAACAAAAAA.",
		"Дан символьный файл с элементами A1, A2, …, AN (N — количество элементов в файле). Заменить исходное расположение его элементов на следующее:\nA1, AN, A2, AN−1, A3, …\nНапример, файл с символами ABCDEFGHI должен измениться на AIBHCGDFE."};
	task_text_chinese = {
		"给定一个字符文件。 颠倒其元素的顺序。 \n例如，带有符号 ABCDE 的文件应更改为 EDCBA。",
		"给定一个字符文件。 将其中包含的所有大写拉丁字母替换为小写字母，并将其元素的顺序改为相反。\n例如，符号文件 A12BmnCD9E 应更改为 e9dcnmb21a。",
		"给定一个包含 10 个以上元素的字符文件。 通过从文件中删除所需数量的有限元素，将其大小减少到 10 个元素。",
		"给定一个包含偶数个元素的字符文件。 从此文件中删除项目的后半部分。",
		"给定一个包含 10 个以上元素的字符文件。 通过从文件中删除所需数量的初始元素，将其大小减少到 10 个元素。",
		"给定一个包含偶数个元素的字符文件。 从给定文件中删除项目的前半部分。",
		"给定一个字符文件。 从中删除所有偶数元素（元素从 1 开始编号）。\n例如，包含字符 ABCDEFG 的文件应更改为 ACEG。",
		"给定一个字符文件。 从中删除所有数字字符。\n例如，符号文件 A11B2CD43F 应更改为 ABCDF。",
		"给定一个字符文件。 从中删除所有大写拉丁字母并反转其元素的顺序。\n例如，带有符号 A11b2Cd43F 的文件应更改为 34d2b11。",
		"给定一个少于 20 个元素的字符文件。 通过在文件开头写入所需数量的字符“A”，将其大小增加到 20 个元素。",
		"给定一个字符文件。 通过将所有原始元素写入文件末尾（按相同顺序）将其大小加倍。\n例如，包含字符 ABCD 的文件应更改为 ABCDABCD。",
		"给定一个字符文件。 通过将其所有原始元素写入文件末尾（以相反顺序）将其大小加倍。\n例如，包含字符 ABCD 的文件应更改为 ABCDDCBA。",
		"给定一个字符文件。 复制其中的所有奇数元素（元素从 1 开始编号）。\n例如，包含字符 ABCDEF 的文件应更改为 AABCCDEEF。",
		"给定一个字符文件。 复制其中的所有数字字符。\n例如，字符文件中 A23EF4S 应更改为 A2233EF44S。",
		"给定一个字符文件。 将其中的每个偶数元素替换为两个“X”字符（元素从 1 开始编号）。\n例如，带有符号 ABCDEF 的文件应更改为 AXXCXXXXX。",
		"给定一个字符文件。 用三个“A”字符替换其中的每个数字字符。\n例如，字符文件 A1B2C34 应更改为 AAAABAAACAAAAAA。",
		"给定一个字符文件，其中包含元素 A1、A2、...、AN（N 是文件中的元素数）。 用以下内容替换其元素的原始布局：\nA1, AN, A2, AN − 1, A3, ....\n例如，带有符号 ABCDEFGHI 的文件应更改为 AIBHCGDFE。",
	};
}
void TaskB::test1()
{
	execute_argv = test_files;

	for (int i = sz - 1; i >= 0; i--)
	{
		write(f_control, &c[i], 1);
	}
}
void TaskB::test2()
{
	execute_argv = test_files;

	for (int i = sz - 1; i >= 0; i--)
	{
		c[i] = tolower(c[i]);
		write(f_control, &c[i], 1);
	}
}
void TaskB::test3()
{
	execute_argv = test_files;

	for (int i = 0; i < 10; i++)
	{
		write(f_control, &c[i], 1);
	}
}
void TaskB::test4()
{
	execute_argv = test_files;

	for (int i = 0; i < sz / 2; i++)
	{
		write(f_control, &c[i], 1);
	}
}
void TaskB::test5()
{
	execute_argv = test_files;

	for (int i = sz - 10; i < sz; i++)
	{
		write(f_control, &c[i], 1);
	}
}
void TaskB::test6()
{
	execute_argv = test_files;

	for (int i = sz / 2; i < sz; i++)
	{

		write(f_control, &c[i], 1);
	}
}
void TaskB::test7()
{
	execute_argv = test_files;

	for (int i = 0; i < sz; i++)
	{
		if (i % 2 == 0)
		{
			write(f_control, &c[i], 1);
		}
	}
}
void TaskB::test8()
{
	execute_argv = test_files;

	for (int i = 0; i < sz; i++)
	{
		if (!isdigit(c[i]))
		{
			write(f_control, &c[i], 1);
		}
	}
}
void TaskB::test9()
{
	execute_argv = test_files;

	for (int i = sz - 1; i >= 0; i--)
	{
		if (!isupper(c[i]))
		{
			write(f_control, &c[i], 1);
		}
	}
}
void TaskB::test10()
{
	execute_argv = test_files;

	for (int i = 0; i < 20 - sz; i++)
	{
		write(f_control, "A", 1);
	}
	for (int i = 0; i < sz; i++)
	{
		write(f_control, &c[i], 1);
	}
}
void TaskB::test11()
{
	execute_argv = test_files;

	for (int i = 0; i < sz; i++)
	{
		write(f_control, &c[i], 1);
	}
	for (int i = 0; i < sz; i++)
	{
		write(f_control, &c[i], 1);
	}
}
void TaskB::test12()
{
	execute_argv = test_files;

	for (int i = 0; i < sz; i++)
	{
		write(f_control, &c[i], 1);
	}

	for (int i = sz - 1; i >= 0; i--)
	{
		write(f_control, &c[i], 1);
	}
}
void TaskB::test13()
{
	execute_argv = test_files;

	for (int i = 0; i < sz; i++)
	{
		write(f_control, &c[i], 1);
		if (i % 2 == 0)
		{
			write(f_control, &c[i], 1);
		}
	}
}
void TaskB::test14()
{
	execute_argv = test_files;

	for (int i = 0; i < sz; i++)
	{
		write(f_control, &c[i], 1);
		if (isdigit(c[i]))
		{
			write(f_control, &c[i], 1);
		}
	}
}
void TaskB::test15()
{
	execute_argv = test_files;

	for (int i = 0; i < sz; i++)
	{
		if (i % 2 == 0)
		{
			write(f_control, &c[i], 1);
		}
		else
		{
			write(f_control, "XX", 2);
		}
	}
}
void TaskB::test16()
{
	execute_argv = test_files;

	for (int i = 0; i < sz; i++)
	{
		if (!isdigit(c[i]))
		{
			write(f_control, &c[i], 1);
		}
		else
		{
			write(f_control, "AAA", 3);
		}
	}
}
void TaskB::test17()
{
	execute_argv = test_files;

	for (int i = 0; i < sz / 2; i++)
	{
		write(f_control, &c[i], 1);
		write(f_control, &c[sz - i - 1], 1);
	}
	if (sz % 2 != 0)
	{
		write(f_control, &c[sz / 2], 1);
	}
}
void TaskB::generate_task_test(int task_num)
{

	init_random_test_files_name(test_files, 1);

	int f_test = open(test_files[0].c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);

	sz = (10 + rand() % 10) * 2;
	if (task_num == 10)
	{
		sz = 9 + rand() % 8;
	}
	if (task_num != 4 && task_num != 6)
	{
		sz += rand() % 2;
	}

	int r[4];

	do
	{
		for (size_t i = 0; i < 4; i++)
			r[i] = 0;

		for (size_t i = 0; i < sz; i++)
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
	write(f_test, c, sz);
	close(f_test);
}
void TaskB::generate_task_control(int task_num)
{
	f_control = open(control_file.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
	switch (task_num)
	{
	case 1:
		test1();
		break;
	case 2:
		test2();
		break;
	case 3:
		test3();
		break;
	case 4:
		test4();
		break;
	case 5:
		test5();
		break;
	case 6:
		test6();
		break;
	case 7:
		test7();
		break;
	case 8:
		test8();
		break;
	case 9:
		test9();
		break;
	case 10:
		test10();
		break;
	case 11:
		test11();
		break;
	case 12:
		test12();
		break;
	case 13:
		test13();
		break;
	case 14:
		test14();
		break;
	case 15:
		test15();
		break;
	case 16:
		test16();
		break;
	case 17:
		test17();
		break;
	}
	close(f_control);
}
void TaskB::print_extral_info(int task_num)
{
	show_file(test_files[0], "Input file: ", 0);
}
int TaskB::check_program(int task_num) const
{
	show_file(test_files[0], "Result file: ", 2);

	return compare_file(test_files[0], control_file);
}