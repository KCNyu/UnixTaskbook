#include "utbDir.hpp"

utbDir::utbDir()
{
#if defined __linux__
    library_name = "libutbDir.so";
#elif defined __APPLE__
    library_name = "libutbDir.dylib";
#endif

    complier = "gcc";

    complie_argv = {complier, "-Wall", "", "-o"};

    task_count = 9;

    total_test_count = 3;

    extension_name = {
        ".jpg",
        ".png",
        ".gif"};

    task_text_russian = {
        "При запуске программы выводится список файлов из текущего каталога (или каталога, указанного в качестве параметра командной строки). Информация о файлах должна выводиться в трех столбцах, содержащих имя файла, его размер (в байтах) и дату- время последнего изменения.",
        "При запуске программы выводится список файлов из текущего или указанного пользователем каталога с именами, имеющими указанное (непустое) расширение (например jpg). Каталог и требуемое расширение задаются пользователем в командной строке (первым указывается расширение, вторым — каталог). В случае отсутствия второго параметра обрабатывается текущий каталог. В случае отсутствия всех параметров выводится сообщение об ошибке. Информация о файлах должна выводиться в трех столбцах, содержащих имя файла, его размер (в байтах) и дату-время последнего изменения.",
        "При запуске программы выводится список файлов с требуемым (непустым) расширением во всех подкаталогах текущего каталога (или каталога, указанного в качестве параметра командной строки). Расширение указывается в качестве второго параметра; если оно не указано, то это означает, что надо вывести все файлы. Для каждого подкаталога вначале выводится его имя (начиная с имени исходного каталога), затем список имен содержащихся в нем файлов с требуемым расширением вместе с их размером в байтах (каждое имя выводится на новой строке с отступом, равным 4 пробелам).",
        "При запуске программы выводится сводная информация о файлах, имеющих требуемое (непустое) расширение, во всех подкаталогах текущего каталога (или каталога, указанного в качестве параметра командной строки). Расширение указывается в качестве второго параметра; если оно не указано, то надо анализировать все файлы. Для каждого подкаталога вначале выводится его имя (начиная с имени исходного каталога), затем (в этой же строке) количество файлов с требуемым расширением и их суммарный размер в байтах.",
        "При запуске программы выводится список файлов из текущего или указанного пользователем каталога с именами, удовлетворяющими заданному пользователем промежутку даты-времени последнего изменения (подкаталоги не обрабатываются; в качестве промежутка указывается начальная дата и конечная дата, которые могут совпадать). Каталог и промежуток времени задаются пользователем в командной строке в виде трех параметров. В случае отсутствия параметров командной строки выводятся все файлы из текущего каталога. Информация о файлах должна выводиться в трех столбцах, содержащих имя файла, его размер (в байтах) и дату-время последнего изменения.",
        "Создайте программу, сравнивающую содержимое двух указанных пользователем в командной строке каталогов (эти параметры командной строки являются обязательными). На экран выводятся три списка файлов: (1) список файлов, имеющихся в первом каталоге и отсутствующих во втором, (2) список файлов, имеющихся во втором и отсутствующих в первом, (3) список файлов, содержащихся в обоих каталогах (содержимое файлов с одинаковыми именами анализировать не требуется). В каждом списке имена файлов выводятся на отдельных строках.",
        "Создайте программу вычисляющую количество и суммарный размер всех файлов, находящихся в указанном каталоге и его подкаталогах и имеющих (непустое) расширение, указанное пользователем. Каталог верхнего уровня и расширение задаются пользователем в командной строке. Предусмотреть обработку ситуации, когда каталог указан, а расширение нет (в этом случае требуется анализировать все файлы). Если каталог также не указан, то обрабатывается текущий каталог. В параметрах командной строки может быть указано несколько расширений, в этом случае каждое расширение обрабатывается отдельно (обрабатываемый каталог всегда указывается первым параметром).",
        "Создайте программу, выполняющую поиск файлов в структуре вложенных друг в друга каталогов, исключая из рассмотрения некоторые каталоги. Имя начального каталога и имена исключаемых каталогов задаются пользователем в командной строке (имен исключаемых каталогов может быть несколько). Для всех найденных файлов выводится их полное имя, размер (в байтах) и дата-время последнего изменения. Если имена исключаемых каталогов не указаны, то обрабатываются все подкаталоги. При отсутствии всех параметров командной строки обрабатывается текущий каталог.",
        "При запуске программы выводится список подкаталогов текущего каталога (или каталога, указанного в качестве параметра командной строки). Выводятся подкаталоги всех уровней, для каждого каталога указывается полный путь, начиная с имени исходного каталога)."};

    task_text_chinese = {
        "启动程序时，将显示当前目录（或指定为命令行参数的目录）中的文件列表。 有关文件的信息应显示在三列中，包括文件名、文件大小（以字节为单位）和最后修改的日期时间。",
        "程序启动时，将显示当前或用户指定目录中具有指定（非空）扩展名（例如 jpg）的文件列表。目录和所需的扩展名由用户在命令行中指定（第一个是扩展名，第二个是目录）。如果缺少第二个参数，则处理当前目录。如果缺少所有参数，则会显示错误消息。有关文件的信息应显示在三列中，包括文件名、文件大小（以字节为单位）和最后修改的日期时间。",
        "启动程序时，将显示当前目录（或指定为命令行参数的目录）的所有子目录中具有所需（非空）扩展名的文件列表。扩展名指定为第二个参数；如果未指定，则表示应输出所有文件。对于每个子目录，首先显示它的名称（从源目录的名称开始），然后是它包含的文件的名称列表，以及所需的扩展名，以及它们的大小（以字节为单位）（每个名称都显示在新行，缩进 4 个空格）。",
        "启动程序时，将显示当前目录（或指定为命令行参数的目录）的所有子目录中具有所需（非空）扩展名的文件的摘要信息。 扩展名指定为第二个参数； 如果未指定，则必须分析所有文件。 对于每个子目录，首先显示其名称（从源目录的名称开始），然后（在同一行）显示具有所需扩展名的文件数及其总大小（以字节为单位）。",
        "程序启动时，显示当前或用户指定目录中的文件列表，其名称满足用户指定的上次修改的日期时间间隔（不处理子目录；间隔指定为开始日期和结束日期，可能相同）。目录和时间跨度由用户在命令行中指定为三个参数。如果没有命令行选项，则显示当前目录中的所有文件。有关文件的信息应显示在三列中，包括文件名、文件大小（以字节为单位）和最后修改的日期时间。",
        "创建一个程序，比较用户在命令行上指定的两个目录的内容（这些命令行选项是必需的）。 显示三个文件列表：（1）第一个目录中的文件列表，而不是第二个目录中的文件列表，（2）第二个目录中的文件列表，而不是第一个目录中的文件列表，（3）两个目录中的文件列表（不需要同名解析的文件内容）。 在每个列表中，文件名显示在单独的行中。",
        "创建一个程序，计算指定目录及其子目录中所有文件的数量和总大小，这些文件具有用户指定的（非空）扩展名。顶级目录和扩展名由用户在命令行上设置。用于处理指定目录但扩展名未指定的情况（此时需要对所有文件进行分析）。如果还没有指定目录，则处理当前目录。可以在命令行选项中指定多个扩展名，在这种情况下，每个扩展名都被单独处理（被处理的目录总是被指定为第一个参数）。",
        "编写一个程序，在嵌套目录结构中搜索文件，不考虑某些目录。初始目录名和要排除的目录名由用户在命令行中指定（排除目录名可以有多个）。对于所有找到的文件，将显示它们的全名、大小（以字节为单位）和上次修改的日期时间。如果未指定排除目录的名称，则处理所有子目录。如果缺少所有命令行选项，则处理当前目录。",
        "启动程序时，会显示当前目录（或指定为命令行参数的目录）的子目录列表。 显示所有级别的子目录，每个目录都指示完整路径，以源目录的名称开头）。"};
}
void utbDir::generate_test_file(std::string dirname, int count)
{
    for (int i = 0; i < 10 + count; i++)
    {
        std::string filename = utilities::generate_random_name(10);
        std::string filepath = dirname + "/" + filename + extension_name[rand() % extension_name.size()];
        std::ofstream ofs(filepath.c_str());
        ofs << utilities::generate_random_name(10);
        ofs.close();
    }
}
void utbDir::utb_generate_task_test(int task_num)
{
    utilities::init_random_test_files_name(test_files, 1);
    sub_dir.clear();
    work_dir = utilities::generate_random_name(10);
    mkdir(work_dir.c_str(), 0777);
    for (int i = 0; i < 1 + rand() % 5; i++)
    {
        for (int i = 0; i < 1 + rand() % 10; i++)
        {
            std::string dirname = utilities::generate_random_name(10);
            sub_dir.push_back(dirname);
            mkdir((work_dir + "/" + dirname).c_str(), 0777);
            generate_test_file(work_dir + "/" + dirname, rand() % 10);
        }
        generate_test_file(work_dir, rand() % 10);
    }

    execute_dir = work_dir + (rand() % 2 ? "/" + sub_dir[rand() % sub_dir.size()] : "");

    output = open(test_files[0].c_str(), O_CREAT | O_RDWR | O_TRUNC, 0644);
}
void utbDir::test1()
{
    sys_cmd = "( ls -l " + execute_dir + " | awk '{print $9 \" \" $5 \" \" $6}' ) > " +
              control_file;
    system(sys_cmd.c_str());

    execute_argv.clear();
    execute_argv.push_back(execute_dir);
}
void utbDir::test2()
{
    std::string test_extension = extension_name[rand() % extension_name.size()];
    sys_cmd = "( ls -l " + execute_dir + " | grep " + test_extension + " | awk '{print $9 \" \" $5 \" \" $6}' ) > " +
              control_file;
    system(sys_cmd.c_str());

    execute_argv.clear();

    execute_argv.push_back(test_extension);
    execute_argv.push_back(execute_dir);
}
void utbDir::test3()
{
    std::string test_extension = extension_name[rand() % extension_name.size()];
    sys_cmd = "(ls -l -R " + execute_dir + " | grep \"^d\" | awk '{print $9}' | while read dir; do\n\techo \"dir: $dir\"\n\tls -l -R " + execute_dir + "/$dir | grep \"" + test_extension + "\" | awk '{print \"    \" $9 \" \" $5}'\ndone) > " +
              control_file;
    system(sys_cmd.c_str());

    execute_argv.clear();

    execute_argv.push_back(test_extension);
    execute_argv.push_back(execute_dir);
}
void utbDir::test4()
{
    execute_dir = work_dir;
    std::string test_extension = extension_name[rand() % extension_name.size()];
    sys_cmd = "( ls -l " + execute_dir + "| grep \"^d\" | awk '{print $9}' | while read dir; do\n\tcd " + execute_dir + "/$dir\n\techo $dir\n\tls -l -R $dir | grep " + test_extension + "| awk '{print $5}' | awk '{sum+=$1}END{print sum}'\n\tcd ..\ndone\n ) > " +
              control_file;
    std::cout << sys_cmd << std::endl;
    system(sys_cmd.c_str());

    execute_argv.clear();
    execute_argv.push_back(test_extension);
    execute_argv.push_back(execute_dir);
}
void utbDir::test5()
{
}
void utbDir::test6()
{
    execute_dir = work_dir + "/" + sub_dir[rand() % sub_dir.size()];
    std::string execute_dir2 = work_dir + "/" + sub_dir[rand() % sub_dir.size()];
    sys_cmd = "( diff -rq " + execute_dir + " " + execute_dir2 + " | grep -E \"^Only in " + execute_dir + "\" | sed -n 's/://p' | awk '{print $3\"/\"$4}' ) >> " +
              control_file;
    system(sys_cmd.c_str());
    sys_cmd = "( diff -rq " + execute_dir + " " + execute_dir2 + " | grep -E \"^Only in " + execute_dir2 + "\" | sed -n 's/://p' | awk '{print $3\"/\"$4}' ) >> " +
              control_file;
    system(sys_cmd.c_str());
    sys_cmd = "( for file in $(find " + execute_dir + " -type f | awk -F \"/\" '{print $NF}'); do find " + execute_dir2 + " -type f -iname \"$file\" | awk -F \"/\" '{print $NF}'; done ) >> " +
              control_file;
    system(sys_cmd.c_str());

    execute_argv.clear();
    execute_argv.push_back(execute_dir);
    execute_argv.push_back(execute_dir2);
}
void utbDir::test7()
{
    std::string test_extension = extension_name[rand() % extension_name.size()];
    sys_cmd = "ls -l -R "+ execute_dir + " | grep " + test_extension + " | wc -l > " + control_file;
    system(sys_cmd.c_str());
    sys_cmd = "ls -l -R "+ execute_dir + " | grep " + test_extension + " | awk '{print $5}' | awk '{sum+=$1}END{print sum}' >> " + control_file;
    system(sys_cmd.c_str());

    execute_argv.clear();
    execute_argv.push_back(test_extension);
    execute_argv.push_back(execute_dir);
}
void utbDir::test8()
{
}
void utbDir::test9()
{
    execute_dir = work_dir;
#if defined __APPLE__
    sys_cmd = "echo " + execute_dir + " > " + control_file;
    system(sys_cmd.c_str());
#endif
    sys_cmd = "ls -R -a " + execute_dir + " | grep \":$\" | sed -e 's/:$//'" + " >> " + control_file;
    system(sys_cmd.c_str());

    execute_argv.clear();
    execute_argv.push_back(execute_dir);
}
void utbDir::utb_generate_task_control(int task_num)
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

    close(f_control);
}
void utbDir::utb_print_extral_info(int task_num)
{
}
int utbDir::utb_check_program(int task_num) const
{
    std::string cmd = "rm -rf " + work_dir + " && (sort " + test_files[0] + " -o " + test_files[0] + ")";
    system(cmd.c_str());

    utilities::show_file(test_files[0], "Result file: ", 2);

    return utilities::compare_file(test_files[0], control_file);
}