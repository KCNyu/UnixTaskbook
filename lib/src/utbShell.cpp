#include "utbShell.hpp"

utbShell::utbShell()
{
#if defined __linux__
    library_name = "libutbShell.so";
#elif defined __APPLE__
    library_name = "libutbShell.dylib";
#endif
    complier = "gcc";

    complie_argv = {complier, "-Wall", "", "-o"};

    task_count = 9;

    total_test_count = 3;

    random_cmds = {
        {"ls", "1", "-R"},
        {"df", "2", "-P", "-h"},
        {"ls", "2", "-a", "-U"},
        {"cat", "1", "/etc/passwd"},
        {"date", "3", "-d", "-1day", "+%Y-%m-%d"},
        {"grep", "4", "-r", "-n", "var", "/etc/passwd"},
        {"stat", "2", "-L", "/etc/opt"},
        {"echo", "1", "hello world!"}};

    random_cmds_stdout = {
        {"cat", "1", "-b"}};

    random_cmds_stdin = {
        {"wc", "2", "-l", "-w"}};

    task_text_russian = {
        "Написать программу shellD1, моделирующую конструкцию командного интерпретатора:\ncmdA A1 A2 … AN ; cmdB B1 B2 … BM\nЭта конструкция обеспечивает последовательное выполнение команд cmdA и cmdB:вначале запускается команда cmdA с параметрами A1, A2, …, AN, затем запускается команда cmdB с параметрами B1, B2, …, BM. Каждая команда использует стандартный вывод на экран.\nФормат вызова программы shellD1:\nshellD1 cmdA N A1 A2 … AN cmdB M B1 B2 … BM",
        "Написать программу shellD2, моделирующую конструкцию командного интерпретатора:\ncmdA A1 A2 … AN && cmdB B1 B2 … BMЭта конструкция выполняет следующие действия. Вначале запускается команда cmdA с параметрами A1, A2, …, AN; если эта команда завершилась успешно (код выхода равен 0), то запускается команда cmdB с параметрами B1, B2, …, BM. Каждая команда использует стандартный вывод на экран.\nФормат вызова программы shellD2:\nshellD2 cmdA N A1 A2 … AN cmdB M B1 B2 … BM",
        "Написать программу shellD3, моделирующую конструкцию командного интерпретатора:\ncmdA A1 A2 … AN || cmdB B1 B2 … BM\nЭта конструкция выполняет следующие действия. Вначале запускается команда cmdA с параметрами A1, A2, …, AN; если эта команда завершилась с ошибкой (код выхода не равен 0), то запускается команда cmdB с параметрами B1, B2, …, BM. Каждая команда использует стандартный вывод на экран.\nФормат вызова программы shellD3:shellD3 cmdA N A1 A2 … AN cmdB M B1 B2 … BM",
        "Написать программу shellD4, моделирующую конструкцию командного интерпретатора:\ncmdA A1 A2 … AN | cmdB B1 B2 … BM\nЭта конструкция выполняет следующие действия. Вначале запускается команда cmdA с параметрами A1, A2, …, AN; вывод этой команды перенаправляется на вход команды команда cmdB с параметрами B1, B2, …, BM (т. е. организуется конвейер). Команда cmdB использует стандартный вывод на экран.\nФормат вызова программы shellD4:\nshellD4 cmdA N A1 A2 … AN cmdB M B1 B2 … BM",
        "Написать программу shellD5, моделирующую конструкцию командного интерпретатора:\ncmdA A1 A2 … AN < file\nЭта конструкция обеспечивает выполнение команды cmdA с параметрами A1, A2, …, AN, причем ввод этой команды перенаправляется из файла с именем file (который должен существовать). Команда cmdA использует стандартный вывод на экран.\nФормат вызова программы shellD5:\nshellD5 file cmdA N A1 A2 … AN",
        "Написать программу shellD6, моделирующую конструкцию командного интерпретатора:\ncmdA A1 A2 … AN > file\nЭта конструкция обеспечивает выполнение команды cmdA с параметрами A1, A2, …, AN, причем вывод этой команды перенаправляется в файл с именем file. Если указанный файл отсутствует, то он создается, если он существует, то его прежнее содержимое удаляется.\nФормат вызова программы shellD6:\nshellD6 file cmdA N A1 A2 … AN",
        "Написать программу shellD7, моделирующую конструкцию командного интерпретатора:\ncmdA A1 A2 ... AN >> file\nЭта конструкция обеспечивает выполнение команды cmdA с параметрами A1, A2, ..., AN, причем вывод этой команды перенаправляется в файл с именем file. Если указанный файл отсутствует, то он создается, если он существует, то новое содержимое добавляется в его конец.\nФормат вызова программы shellD7:\nshellD7 file cmdA N A1 A2 ... AN",
        "Написать программу shellD8, моделирующую конструкцию командного интерпретатора:\n( cmdA A1 A2 ... AN ; cmdB B1 B2 ... BM ) > file\nЭта конструкция обеспечивает последовательное выполнение команд cmdA и cmdB: вначале запускается команда cmdA с параметрами A1, A2, ..., AN, затем запускается команда cmdB с параметрами B1, B2, ..., BM. При этом вывод каждой команды перенаправляется в файл с именем file. Если указанный файл отсутствует, то он создается, если он существует, то его прежнее содержимое удаляется.\nФормат вызова программы shellD8:\nshellD8 file cmdA N A1 A2 ... AN cmdB M B1 B2 ... BM",
        "Написать программу shellD9, моделирующую конструкцию командного интерпретатора:\n( cmdA A1 A2 ... AN || cmdB B1 B2 ... BM ) | cmdC C1 C2 ... CP >> file\nЭта конструкция выполняет следующие действия. Вначале запускается команда cmdA с параметрами A1, A2, ..., AN; если эта программа завершилась с ошибкой (код выхода не равен 0), то запускается команда cmdB с параметрами B1, B2, ..., BM. Стандартный вывод успешно проработавшей команды перенаправляется на стандартный ввод команды cmdC с параметрами C1, C2, ..., CP. Стандартный вывод команды cmdC перенаправляется в файл file, причем если файл не существует, то он создается, а если существует, то дополняется новыми данными.\nФормат вызова программы shellD9:\nshellD9 file cmdA N A1 A2 ... AN cmdB M B1 B2 ... BM cmdC P C1 C2 ... CP"};
    task_text_chinese = {
        "编写一个模拟shell结构的shellD1程序：\ncmdA A1 A2…AN ; cmdB B1 B2… BM \n这种结构确保了 cmdA 和 cmdB 命令的顺序执行：首先，cmdA 命令使用 A1、A2、…、AN 参数启动，然后使用 B1、B2、…、BM 参数启动 cmdB 命令参数启动。 每个命令使用标准输出到屏幕。\n调用shellD1程序的格式为：\nshellD1 cmdA N A1 A2…AN cmdB M B1 B2…BM",
        "编写一个模拟shell结构的shellD2程序：\ncmdA A1 A2... AN && cmdB B1 B2... BM \n此构造执行以下操作。 首先，使用参数 A1、A2、…、AN 启动 cmdA 命令； 如果此命令成功（退出代码为 0），则使用参数 B1、B2、…、BM 启动 cmdB 命令。 每个命令都使用标准输出到屏幕。\n调用shellD2程序的格式为：\nshellD2 cmdA N A1 A2…AN cmdB M B1 B2…BM",
        "编写一个模拟shell结构的shellD3程序：\ncmdA A1 A2 ... AN || cmdB B1 B2 ... BM \n此构造执行以下操作。首先，cmdA 命令使用参数 A1、A2、.. ., AN；如果此命令失败（退出代码不等于0），则启动带有参数B1、B2、...、BM的cmdB命令。每个命令都使用标准输出到屏幕。\n格式shellD3程序的调用是：shellD3 cmdA N A1 A2…AN cmdB M B1 B2…BM",
        "编写一个模拟shell结构的shellD4程序：\ncmdA A1 A2…AN | cmdB B1 B2…BM该命令重定向到命令输入cmdB命令，参数为B1,B2,...,BM（即组织了一个管道）。cmdB命令使用标准输出到屏幕。\nshellD4程序调用的格式是：\nshellD4 cmdA N A1 A2…AN cmdB M B1 B2…BM",
        "编写一个模拟shell结构的shellD5程序：\ncmdA A1 A2…AN <file\n这个构造提供了带有参数A1,A2,…,AN的cmdA命令的执行，并且这个命令的输入是从一个文件重定向的命名文件（必须存在）。cmdA命令使用标准输出到屏幕。\n调用shellD5程序的格式是：\nshellD5 file cmdA N A1 A2 ... AN",
        "编写一个模拟shell结构的shellD6程序：\ncmdA A1 A2…AN>文件\n这个结构提供了cmdA命令的执行，参数为A1，A2，…，AN，这个命令的输出被重定向到一个文件命名文件。如果指定的文件不存在，则创建，如果存在，则删除其先前的内容。\n调用shellD6程序的格式：\nshellD6 file cmdA N A1 A2 ... AN",
        "编写一个模拟shell结构的shellD7程序：\ncmdA A1 A2 ... AN >> file\n这个结构保证cmdA命令执行时带有参数A1，A2，...，AN，以及这个命令的输出重定向到名为 file 的文件。如果指定的文件不存在，则创建它，如果存在，则将新内容附加到其末尾。\nshellD7 程序的调用格式：\nshellD7 file cmdA N A1 A2 。 .. AN",
        "编写一个模拟shell结构的shellD8程序：\n(cmdA A1 A2 ... AN; cmdB B1 B2 ... BM)> file \n这个结构保证了cmdA和cmdB命令的顺序执行：首先, cmdA 命令以参数 A1, A2, ..., AN 运行，然后 cmdB 命令以参数 B1, B2, ..., BM 运行。在这种情况下，每个命令的输出都被重定向到一个文件名为file。如果指定的文件不存在，则创建，如果存在，则删除其先前的内容。\nshellD8程序调用格式：\nshellD8 file cmdA N A1 A2 ... AN cmdB M B1 B2 ... BM",
        "编写一个模拟shell结构的shellD9程序：\n(cmdA A1 A2 ... AN || cmdB B1 B2 ... BM) | cmdC C1 C2 ... CP >> file\n此构造执行以下操作。命令带有参数 A1, A2, ..., AN 的 cmdA；如果此程序因错误而终止（退出代码不为 0），则使用参数 B1, B2, ..., BM 运行 cmdB 命令。处理成功的命令重定向到cmdC命令的标准输入，参数为C1,C2,...,CP，cmdC命令的标准输出重定向到文件file，如果文件不存在，则\nshellD9 程序调用格式：\nshellD9 file cmdA N A1 A2 ... AN cmdB M B1 B2 ... BM cmdC P C1 C2 ... CP"};

    task_text_english = {
        "Write a shellD1 program that simulates the command interpreter construct:\ncmdA A1 A2 ... AN ; cmdB B1 B2 ... BM\nThis construct ensures that the cmdA and cmdB commands are executed sequentially: first, the cmdA command is launched with the parameters A1, A2, ..., AN, then the command cmdB with parameters B1, B2, ..., BM Each command uses the standard output to the screen.\nFormat of the shellD1 program call:\nshellD1 cmdA N A1 A2 ... AN cmdB M B1 B2 ... BM",
        "Write a shellD2 program that simulates a shell construct:\ncmdA A1 A2 ... AN && cmdB B1 B2 ... BM This construct does the following. First, the cmdA command is run with the parameters A1, A2, ..., AN; if this command succeeds (the exit code is 0), then the cmdB command is run with the parameters B1, B2, ..., BM. Each command uses the standard output to the screen.\nThe format of the shellD2 program call is:\nshellD2 cmdA N A1 A2 ... AN cmdB M B1 B2 ... BM",
        "Write a shellD3 program that simulates a shell construct:\ncmdA A1 A2 ... AN || cmdB B1 B2 ... BM\nThis construct does the following. First, the cmdA command is run with the parameters A1, A2, ..., AN; if this command ends with an error (exit code is not equal to 0), then the cmdB command is run with the parameters B1, B2, ..., BM. Each command uses the standard output to the screen.\nThe format of the shellD3 program call is: shellD3 cmdA N A1 A2 ... AN cmdB M B1 B2 ... BM",
        "Write a shellD4 program that simulates the shell construct:\ncmdA A1 A2 ... AN | cmdB B1 B2 ... BM\nThis construct does the following. First, the cmdA command is run with parameters A1, A2, ..., AN; the output of this command is redirected to the command input cmdB command with parameters B1, B2, …, BM (i.e., pipeline is organized.) The cmdB command uses the standard output to the screen.\nThe format of the shellD4 program call is:\nshellD4 cmdA N A1 A2 … AN cmdB M B1 B2 … BM",
        "Write a shellD5 program that simulates the shell construct:\ncmdA A1 A2 ... AN < file\nThis construct executes the cmdA command with parameters A1, A2, ..., AN, with the command's input redirected from a file named file (which must exist) .The cmdA command uses the standard output to the screen.\nThe format for calling the shellD5 program is:\nshellD5 file cmdA N A1 A2 ... AN",
        "Write a shellD6 program that simulates the shell construct:\ncmdA A1 A2 ... AN > file\nThis construct executes the cmdA command with the parameters A1, A2, ..., AN, and the output of this command is redirected to a file named file. If the specified file does not exist , then it is created, if it exists, then its previous contents are deleted.\nThe shellD6 program call format is:\nshellD6 file cmdA N A1 A2 ... AN",
        "Write a shellD7 program that simulates the shell construct:\ncmdA A1 A2 ... AN >> file\nThis construct executes the cmdA command with parameters A1, A2, ..., AN, and redirects the output of this command to a file named file If the specified file does not exist, then it is created, if it exists, then new content is added to its end.\nFormat of calling the shellD7 program:\nshellD7 file cmdA N A1 A2 ... AN",
        "Write a shellD8 program that simulates the shell construct:\n( cmdA A1 A2 ... AN ; cmdB B1 B2 ... BM ) > file\nThis construct ensures that the cmdA and cmdB commands are executed sequentially: first, the cmdA command is run with the parameters A1, A2, ..., AN, then the cmdB command is run with the parameters B1, B2, ..., BM. This redirects the output of each command to a file named file. If the specified file does not exist, then it is created, if it exists, then its previous content is deleted.\nThe shellD8 program call format is:\nshellD8 file cmdA N A1 A2 ... AN cmdB M B1 B2 ... BM",
        "Write a shellD9 program that simulates a shell construct:\n( cmdA A1 A2 ... AN || cmdB B1 B2 ... BM ) | cmdC C1 C2 ... CP >> file\nThis construct does the following. Runs first cmdA command with parameters A1, A2, ..., AN, if this program terminated with an error (exit code not equal to 0), then the cmdB command with parameters B1, B2, ..., BM is run. The standard output of a successful command is redirected to the standard input of the cmdC command with the parameters C1, C2, ..., CP. The standard output of the cmdC command is redirected to the file file, and if the file does not exist, then it is created, and if it exists, it is supplemented with new data.\nFormat of calling the shellD9 program :\nshellD9 file cmdA N A1 A2 ... AN cmdB M B1 B2 ... BM cmdC P C1 C2 ... CP"};
}
bool utbShell::foo_judge(std::string cmd)
{
    bool judge_num = (cmd == "0" || cmd == "1" || cmd == "2" || cmd == "3" || cmd == "4");
    return judge_num;
}
void utbShell::utb_generate_task_test(int task_num)
{
    utilities::init_random_test_files_name(test_files, 1);

    // Generate the test file in advance to make the ls command work normally
    f = open(test_files[0].c_str(), O_CREAT | O_TRUNC | O_WRONLY, 0644);
    close(f);
}
void utbShell::init_helper_sys_cmd(std::string split)
{
    int split_index = 0;
    for (size_t i = 0; i < execute_argv.size(); i++)
    {
        split_index--;
        if (foo_judge(execute_argv[i]))
        {
            split_index = atoi(execute_argv[i].c_str());
            continue;
        }

        sys_cmd += execute_argv[i] + (i != execute_argv.size() - 1 ? " " : "");

        if (split_index == 0 && i != execute_argv.size() - 1)
        {
            sys_cmd += split;
        }
    }
}
void utbShell::test1()
{
    execute_argv = random_cmds[rand() % random_cmds.size()];
    for (auto cmd : random_cmds[rand() % random_cmds.size()])
    {
        execute_argv.push_back(cmd);
    }

    sys_cmd = "(";
    init_helper_sys_cmd(";");
    sys_cmd += ") > " + control_file;

    system(sys_cmd.c_str());
}
void utbShell::test2()
{
    execute_argv = random_cmds[rand() % random_cmds.size()];
    for (auto cmd : random_cmds[rand() % random_cmds.size()])
    {
        execute_argv.push_back(cmd);
    }

    sys_cmd = "(";
    init_helper_sys_cmd("&&");
    sys_cmd += ") > " + control_file;

    system(sys_cmd.c_str());
}
void utbShell::test3()
{
    execute_argv = random_cmds[rand() % random_cmds.size()];
    for (auto cmd : random_cmds[rand() % random_cmds.size()])
    {
        execute_argv.push_back(cmd);
    }

    sys_cmd = "(";
    init_helper_sys_cmd("||");
    sys_cmd += ") > " + control_file;

    system(sys_cmd.c_str());
}
void utbShell::test4()
{
    execute_argv = random_cmds[rand() % random_cmds.size()];
    for (auto cmd : random_cmds_stdout[rand() % random_cmds_stdout.size()])
    {
        execute_argv.push_back(cmd);
    }

    sys_cmd = "(";
    init_helper_sys_cmd("|");
    sys_cmd += ") > " + control_file;

    system(sys_cmd.c_str());
}
void utbShell::test5()
{
    execute_argv = random_cmds_stdin[rand() % random_cmds_stdin.size()];
    execute_argv.insert(execute_argv.begin(), "/etc/passwd");

    sys_cmd = "";
    execute_argv.push_back("/etc/passwd");
    init_helper_sys_cmd("<");
    execute_argv.pop_back();
    sys_cmd = sys_cmd.substr(12);
    sys_cmd = "(" + sys_cmd + ") > " + control_file;

    puts(sys_cmd.c_str());
    system(sys_cmd.c_str());
}
void utbShell::test6()
{
    execute_argv = random_cmds[rand() % random_cmds.size()];
    execute_argv.insert(execute_argv.begin(), test_files[0]);

    sys_cmd = "";
    init_helper_sys_cmd(">");
    sys_cmd = sys_cmd.substr(test_files[0].size() + 1);
    sys_cmd += " > " + control_file;

    system(sys_cmd.c_str());
}
void utbShell::test7()
{
    execute_argv = random_cmds[rand() % random_cmds.size()];
    execute_argv.insert(execute_argv.begin(), test_files[0]);

    sys_cmd = "";
    init_helper_sys_cmd(">>");
    sys_cmd = sys_cmd.substr(test_files[0].size() + 1);
    sys_cmd += " > " + control_file;

    system(sys_cmd.c_str());
}
void utbShell::test8()
{
    execute_argv = random_cmds[rand() % random_cmds.size()];
    for (auto cmd : random_cmds[rand() % random_cmds.size()])
    {
        execute_argv.push_back(cmd);
    }
    execute_argv.insert(execute_argv.begin(), test_files[0]);

    sys_cmd = "";
    init_helper_sys_cmd(";");
    sys_cmd = sys_cmd.substr(test_files[0].size() + 1);
    sys_cmd = "(" + sys_cmd + ") > " + control_file;

    system(sys_cmd.c_str());
}
void utbShell::test9()
{
    execute_argv = random_cmds[rand() % random_cmds.size()];
    for (auto cmd : random_cmds[rand() % random_cmds.size()])
    {
        execute_argv.push_back(cmd);
    }

    sys_cmd = "";
    init_helper_sys_cmd("||");
    sys_cmd = "(" + sys_cmd + ") |";

    for (auto cmd : random_cmds_stdout[rand() % random_cmds_stdout.size()])
    {
        execute_argv.push_back(cmd);
        if (foo_judge(cmd))
        {
            continue;
        }
        sys_cmd += " " + cmd;
    }
    execute_argv.insert(execute_argv.begin(), test_files[0]);

    sys_cmd += " >> " + control_file;

    system(sys_cmd.c_str());
}
void utbShell::utb_generate_task_control(int task_num)
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
    }

    output = open(test_files[0].c_str(), O_WRONLY | O_TRUNC, 0644);

    close(f_control);
}
void utbShell::utb_print_extra_info(int task_num)
{
}
int utbShell::utb_check_program(int test_num) const
{
    return utilities::compare_file(test_files[0], control_file);
}