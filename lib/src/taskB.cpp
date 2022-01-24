#include "taskB.hpp"

TaskB::TaskB()
{
	library_name = "libtaskB.so";
	complier = "gcc";
	complie_argv = {complier, "-Wall", "", "-o"};
	task_count = 17;
	task_text_russian = {
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
	task_text_chinese = {
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
}