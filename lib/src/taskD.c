#include "taskD.h"

char *testfileext = ".tst";
char *controlfilename = "_control.tst";
int maxtasknum = 9;

const char *TaskInfoRussian[] = {
    "Написать программу shellD1, моделирующую конструкцию командного интерпретатора:\ncmdA A1 A2 … AN ; cmdB B1 B2 … BM\nЭта конструкция обеспечивает последовательное выполнение команд cmdA и cmdB:вначале запускается команда cmdA с параметрами A1, A2, …, AN, затем запускается команда cmdB с параметрами B1, B2, …, BM. Каждая команда использует стандартный вывод на экран.\nФормат вызова программы shellD1:\nshellD1 cmdA N A1 A2 … AN cmdB M B1 B2 … BM\n",
    "Написать программу shellD2, моделирующую конструкцию командного интерпретатора:\ncmdA A1 A2 … AN && cmdB B1 B2 … BMЭта конструкция выполняет следующие действия. Вначале запускается команда cmdA с параметрами A1, A2, …, AN; если эта команда завершилась успешно (код выхода равен 0), то запускается команда cmdB с параметрами B1, B2, …, BM. Каждая команда использует стандартный вывод на экран.\nФормат вызова программы shellD2:\nshellD2 cmdA N A1 A2 … AN cmdB M B1 B2 … BM\n",
    "Написать программу shellD3, моделирующую конструкцию командного интерпретатора:\ncmdA A1 A2 … AN || cmdB B1 B2 … BM\nЭта конструкция выполняет следующие действия. Вначале запускается команда cmdA с параметрами A1, A2, …, AN; если эта команда завершилась с ошибкой (код выхода не равен 0), то запускается команда cmdB с параметрами B1, B2, …, BM. Каждая команда использует стандартный вывод на экран.\nФормат вызова программы shellD3:shellD3 cmdA N A1 A2 … AN cmdB M B1 B2 … BM\n",
    "Написать программу shellD4, моделирующую конструкцию командного интерпретатора:\ncmdA A1 A2 … AN | cmdB B1 B2 … BM\nЭта конструкция выполняет следующие действия. Вначале запускается команда cmdA с параметрами A1, A2, …, AN; вывод этой команды перенаправляется на вход команды команда cmdB с параметрами B1, B2, …, BM (т. е. организуется конвейер). Команда cmdB использует стандартный вывод на экран.\nФормат вызова программы shellD4:\nshellD4 cmdA N A1 A2 … AN cmdB M B1 B2 … BM\n",
    "Написать программу shellD5, моделирующую конструкцию командного интерпретатора:\ncmdA A1 A2 … AN < file\nЭта конструкция обеспечивает выполнение команды cmdA с параметрами A1, A2, …, AN, причем ввод этой команды перенаправляется из файла с именем file (который должен существовать). Команда cmdA использует стандартный вывод на экран.\nФормат вызова программы shellD5:\nshellD5 file cmdA N A1 A2 … AN\n",
    "Написать программу shellD6, моделирующую конструкцию командного интерпретатора:\ncmdA A1 A2 … AN > file\nЭта конструкция обеспечивает выполнение команды cmdA с параметрами A1, A2, …, AN, причем вывод этой команды перенаправляется в файл с именем file. Если указанный файл отсутствует, то он создается, если он существует, то его прежнее содержимое удаляется.\nФормат вызова программы shellD6:\nshellD6 file cmdA N A1 A2 … AN\n",
    "Написать программу shellD7, моделирующую конструкцию командного интерпретатора:\ncmdA A1 A2 ... AN >> file\nЭта конструкция обеспечивает выполнение команды cmdA с параметрами A1, A2, ..., AN, причем вывод этой команды перенаправляется в файл с именем file. Если указанный файл отсутствует, то он создается, если он существует, то новое содержимое добавляется в его конец.\nФормат вызова программы shellD7:\nshellD7 file cmdA N A1 A2 ... AN\n",
    "Написать программу shellD8, моделирующую конструкцию командного интерпретатора:\n( cmdA A1 A2 ... AN ; cmdB B1 B2 ... BM ) > file\nЭта конструкция обеспечивает последовательное выполнение команд cmdA и cmdB: вначале запускается команда cmdA с параметрами A1, A2, ..., AN, затем запускается команда cmdB с параметрами B1, B2, ..., BM. При этом вывод каждой команды перенаправляется в файл с именем file. Если указанный файл отсутствует, то он создается, если он существует, то его прежнее содержимое удаляется.\nФормат вызова программы shellD8:\nshellD8 file cmdA N A1 A2 ... AN cmdB M B1 B2 ... BM\n",
    "Написать программу shellD9, моделирующую конструкцию командного интерпретатора:\n( cmdA A1 A2 ... AN || cmdB B1 B2 ... BM ) | cmdC C1 C2 ... CP >> file\nЭта конструкция выполняет следующие действия. Вначале запускается команда cmdA с параметрами A1, A2, ..., AN; если эта программа завершилась с ошибкой (код выхода не равен 0), то запускается команда cmdB с параметрами B1, B2, ..., BM. Стандартный вывод успешно проработавшей команды перенаправляется на стандартный ввод команды cmdC с параметрами C1, C2, ..., CP. Стандартный вывод команды cmdC перенаправляется в файл file, причем если файл не существует, то он создается, а если существует, то дополняется новыми данными.\nФормат вызова программы shellD9:\nshellD9 file cmdA N A1 A2 ... AN cmdB M B1 B2 ... BM cmdC P C1 C2 ... CP\n"
};
const char *TaskInfoChinese[] = {
    "编写一个模拟shell结构的shellD1程序：\ncmdA A1 A2…AN ; cmdB B1 B2… BM \n这种结构确保了 cmdA 和 cmdB 命令的顺序执行：首先，cmdA 命令使用 A1、A2、…、AN 参数启动，然后使用 B1、B2、…、BM 参数启动 cmdB 命令参数启动。 每个命令使用标准输出到屏幕。\n调用shellD1程序的格式为：\nshellD1 cmdA N A1 A2…AN cmdB M B1 B2…BM\n",
    "编写一个模拟shell结构的shellD2程序：\ncmdA A1 A2... AN && cmdB B1 B2... BM \n此构造执行以下操作。 首先，使用参数 A1、A2、…、AN 启动 cmdA 命令； 如果此命令成功（退出代码为 0），则使用参数 B1、B2、…、BM 启动 cmdB 命令。 每个命令都使用标准输出到屏幕。\n调用shellD2程序的格式为：\nshellD2 cmdA N A1 A2…AN cmdB M B1 B2…BM\n",
    "编写一个模拟shell结构的shellD3程序：\ncmdA A1 A2 ... AN || cmdB B1 B2 ... BM \n此构造执行以下操作。首先，cmdA 命令使用参数 A1、A2、.. ., AN；如果此命令失败（退出代码不等于0），则启动带有参数B1、B2、...、BM的cmdB命令。每个命令都使用标准输出到屏幕。\n格式shellD3程序的调用是：shellD3 cmdA N A1 A2…AN cmdB M B1 B2…BM\n", 
    "编写一个模拟shell结构的shellD4程序：\ncmdA A1 A2…AN | cmdB B1 B2…BM该命令重定向到命令输入cmdB命令，参数为B1,B2,...,BM（即组织了一个管道）。cmdB命令使用标准输出到屏幕。\nshellD4程序调用的格式是：\nshellD4 cmdA N A1 A2…AN cmdB M B1 B2…BM\n",
    "编写一个模拟shell结构的shellD5程序：\ncmdA A1 A2…AN <file\n这个构造提供了带有参数A1,A2,…,AN的cmdA命令的执行，并且这个命令的输入是从一个文件重定向的命名文件（必须存在）。cmdA命令使用标准输出到屏幕。\n调用shellD5程序的格式是：\nshellD5文件cmdA N A1 A2 ... AN\n",
    "编写一个模拟shell结构的shellD6程序：\ncmdA A1 A2…AN>文件\n这个结构提供了cmdA命令的执行，参数为A1，A2，…，AN，这个命令的输出被重定向到一个文件命名文件。如果指定的文件不存在，则创建，如果存在，则删除其先前的内容。\n调用shellD6程序的格式：\nshellD6文件cmdA N A1 A2 ... AN\n",
    "编写一个模拟shell结构的shellD7程序：\ncmdA A1 A2 ... AN >> file\n这个结构保证cmdA命令执行时带有参数A1，A2，...，AN，以及这个命令的输出重定向到名为 file 的文件。如果指定的文件不存在，则创建它，如果存在，则将新内容附加到其末尾。\nshellD7 程序的调用格式：\nshellD7 file cmdA N A1 A2 。 .. AN\n",
    "编写一个模拟shell结构的shellD8程序：\n(cmdA A1 A2 ... AN; cmdB B1 B2 ... BM)> file \n这个结构保证了cmdA和cmdB命令的顺序执行：首先, cmdA 命令以参数 A1, A2, ..., AN 运行，然后 cmdB 命令以参数 B1, B2, ..., BM 运行。在这种情况下，每个命令的输出都被重定向到一个文件名为file。如果指定的文件不存在，则创建，如果存在，则删除其先前的内容。\nshellD8程序调用格式：\nshellD8文件cmdA N A1 A2 ... AN cmdB M B1 B2 ... BM\n",
    "编写一个程序 shellD9 来模拟 shell 构造：\n(cmdA A1 A2 ... AN || cmdB B1 B2 ... BM) | cmdC C1 C2 ... CP >> file\n此构造执行以下操作。命令带有参数 A1, A2, ..., AN 的 cmdA；如果此程序因错误而终止（退出代码不为 0），则使用参数 B1, B2, ..., BM 运行 cmdB 命令。处理成功的命令重定向到cmdC命令的标准输入，参数为C1,C2,...,CP，cmdC命令的标准输出重定向到文件file，如果文件不存在，则\nshellD9 程序调用格式：\nshellD9 文件 cmdA N A1 A2 ... AN cmdB M B1 B2 ... BM cmdC P C1 C2 ... CP\n"
};

const char *c1[] = {"ls", "1", "-r"};
const char *c2[] = {"df", "2", "-P", "-h"};
const char *c3[] = {"cat", "1", "/etc/passwd"};
const char *c4[] = {"date", "3", "-d", "-1day", "+%Y-%m-%d"};
const char **DTaskTestCmd[] = {c1, c2, c3, c4};
char *initCmd1(char **args, int *nargs)
{
    int A = rand() % 4;
    const char **cmd1 = DTaskTestCmd[A];
    int size_cmd1 = 2 + atoi(cmd1[1]);
    *nargs = size_cmd1 + 2;
    char *sys_cmd = (char *)malloc(100);
    for (int i = 2; i < *nargs; i++)
    {
        args[i] = (char *)malloc(50);
        strcpy(args[i], cmd1[i - 2]);
        if (i != 3)
        {
            strcat(sys_cmd, args[i]);
            strcat(sys_cmd, " ");
        }
    }
    return sys_cmd;
}
char *initCmd2(char **args, int *nargs, const char *conjunctions)
{
    int A = rand() % 4, B = rand() % 4;
    const char **cmd1 = DTaskTestCmd[A], **cmd2 = DTaskTestCmd[B];
    int size_cmd1 = 2 + atoi(cmd1[1]);
    int size_cmd2 = 2 + atoi(cmd2[1]);
    *nargs = size_cmd1 + size_cmd2 + 1;
    char *sys_cmd = (char *)malloc(100);
    for (int i = 1; i < *nargs; i++)
    {
        args[i] = (char *)malloc(50);
        if (i <= size_cmd1)
        {
            strcpy(args[i], cmd1[i - 1]);
            if (i != 2)
            {
                strcat(sys_cmd, args[i]);
                strcat(sys_cmd, " ");
                if (i == size_cmd1)
                    strcat(sys_cmd, conjunctions);
            }
        }
        else
        {
            strcpy(args[i], cmd2[i - size_cmd1 - 1]);
            if (i != size_cmd1 + 2)
            {
                strcat(sys_cmd, args[i]);
                strcat(sys_cmd, " ");
            }
        }
    }
    return sys_cmd;
}
void data(int *nargs, char **args, char *filename, char *filename2, int tasknum, int testnum)
{
    for (int i = 0; i < 8; i++)
        filename[i] = (char)(rand() % 26 + 97);
    filename[8] = '\0';
    strcat(filename, testfileext);
    // Generate the test file in advance to make the ls command work normally
    int f = open(filename, O_CREAT | O_TRUNC, 0777);
    close(f);

    f = open(controlfilename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    int backup = dup(STDOUT_FILENO);
    char *sys_cmd = NULL;
    switch (tasknum)
    {
    case 1:
        dup2(f, STDOUT_FILENO);
        close(f);
        sys_cmd = initCmd2(args, nargs, ";");
        system(sys_cmd);
        break;
    case 2:
        dup2(f, STDOUT_FILENO);
        close(f);
        sys_cmd = initCmd2(args, nargs, "&&");
        system(sys_cmd);
        break;
    case 3:
        dup2(f, STDOUT_FILENO);
        close(f);
        sys_cmd = initCmd2(args, nargs, "||");
        system(sys_cmd);
        break;
    case 4:
        dup2(f, STDOUT_FILENO);
        close(f);
        sys_cmd = initCmd2(args, nargs, "|");
        system(sys_cmd);
        break;
    case 6:
        dup2(f, STDOUT_FILENO);
        sys_cmd = initCmd1(args, nargs);
        args[1] = (char *)malloc(50);
        strcpy(args[1], filename);
        system(sys_cmd);
        close(f);
        break;
    }
    dup2(backup, STDOUT_FILENO);
    free(sys_cmd);
}
int filecompare(char *name1, char *name2)
{
    int f1 = open(name1, O_RDONLY);
    int f2 = open(name2, O_RDONLY);
    char buf1[50000];
    char buf2[50000];
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
void printData(char *cmd, int nargs, char **args, char *outfilename, char *filename, char *filename2)
{
    sprintf(cmd, "%s ", outfilename);
    for (int i = 1; i < nargs; i++)
    {
        strcat(cmd, args[i]);
        strcat(cmd, " ");
    }
    puts(cmd);
}
void execData(char *outfilename, char *filename, int nargs, char **args)
{
    int f = open(filename, O_WRONLY, 0777);
    dup2(f, STDOUT_FILENO);
    close(f);
    args[0] = (char *)malloc(50);
    strcpy(args[0], filename);
    execv(outfilename, args);
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