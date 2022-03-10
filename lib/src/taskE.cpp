#include "taskE.hpp"

TaskE::TaskE()
{
    library_name = "libtaskE.so";

    complier = "gcc";

    complie_argv = {complier, "-Wall", "-pthread", "", "-o"};

    task_count = 16;

    total_test_count = 3;

    task_text_russian = {
        "Реализовать варианты алгоритма нахождения суммы всех элементов исходного массива. Количество потоков для алгоритмов, использующих потоки, равно 2.",
        "Реализовать варианты алгоритма нахождения суммы всех элементов исходного массива. Количество потоков для алгоритмов, использующих потоки, равно 4.",
        "Реализовать варианты алгоритма нахождения суммы всех положительных элементов исходного массива. Количество потоков для алгоритмов, использующих потоки, равно 2.",
        "Реализовать варианты алгоритма нахождения суммы всех положительных элементов исходного массива. Количество потоков для алгоритмов, использующих потоки, равно 4.",
        "Реализовать варианты алгоритма нахождения среднего арифметического всех положительных элементов исходного массива. Количество потоков для алгоритмов, использующих потоки, равно 2. Результат должен быть вещественным числом (типа double).",
        "Реализовать варианты алгоритма нахождения среднего арифметического всех положительных элементов исходного массива. Количество потоков для алгоритмов, использующих потоки, равно 4. Результат должен быть вещественным числом (типа double).",
        "Реализовать варианты алгоритма нахождения количества всех положительных элементов исходного массива. Количество потоков для алгоритмов, использующих потоки, равно 2.",
        "Реализовать варианты алгоритма нахождения количества всех положительных элементов исходного массива. Количество потоков для алгоритмов, использующих потоки, равно 4.",
        "Реализовать варианты алгоритма нахождения суммы индексов всех положительных элементов исходного массива. Количество потоков для алгоритмов, использующих потоки, равно 2. Чтобы избежать переполнения, использовать для хранения суммы индексов переменную типа double.",
        "Реализовать варианты алгоритма нахождения суммы индексов всех положительных элементов исходного массива. Количество потоков для алгоритмов, использующих потоки, равно 4. Чтобы избежать переполнения, использовать для хранения суммы индексов переменную типа double.",
        "Реализовать варианты алгоритма нахождения среднего арифметического всех элементов исходного массива с четными значениями (0, 2, -2, 4, -4, ..., 100, -100). Количество потоков для алгоритмов, использующих потоки, равно 2. Результат должен быть вещественным числом (типа double).",
        "Реализовать варианты алгоритма нахождения среднего арифметического всех элементов исходного массива с четными значениями (0, 2, -2, 4, -4, ..., 100, -100). Количество потоков для алгоритмов, использующих потоки, равно 4. Результат должен быть вещественным числом (типа double).",
        "Реализовать варианты алгоритма нахождения количества всех элементов исходного массива с четными значениями (0, 2, -2, 4, -4, ..., 100, -100). Количество потоков для алгоритмов, использующих потоки, равно 2.",
        "Реализовать варианты алгоритма нахождения количества всех элементов исходного массива с четными значениями (0, 2, -2, 4, -4, ..., 100, -100). Количество потоков для алгоритмов, использующих потоки, равно 4.",
        "Реализовать варианты алгоритма нахождения суммы индексов всех элементов исходного массива с четными значениями (0, 2, -2, 4, -4, ..., 100, -100). Количество потоков для алгоритмов, использующих потоки, равно 2. Чтобы избежать переполнения, использовать для хранения суммы индексов переменную типа double.",
        "Реализовать варианты алгоритма нахождения суммы индексов всех элементов исходного массива с четными значениями (0, 2, -2, 4, -4, ..., 100, -100). Количество потоков для алгоритмов, использующих потоки, равно 4. Чтобы избежать переполнения, использовать для хранения суммы индексов переменную типа double."};

    task_text_chinese = {
        "实现算法的变体以查找原始数组的所有元素的总和。 使用线程的算法的线程数为 2。",
        "实现算法的变体以查找原始数组的所有元素的总和。 使用线程的算法的线程数为 4。",
        "实现算法的变体，用于查找原始数组的所有正元素之和。 使用线程的算法的线程数为 2。",
        "实现算法的变体，用于查找原始数组的所有正元素之和。 使用线程的算法的线程数为 4。",
        "实现算法的变体，用于查找原始数组的所有正元素的算术平均值。 使用线程的算法的线程数为 2。结果必须是实数（double）。",
        "实现算法的变体，用于查找原始数组的所有正元素的算术平均值。 使用线程的算法的线程数为 4。结果必须是实数（double）。",
        "实现算法的变体，以查找原始数组的所有正元素的数量。 使用线程的算法的线程数为 2。",
        "实现算法的变体，以查找原始数组的所有正元素的数量。 使用线程的算法的线程数为 4。",
        "实现算法的变体，用于查找原始数组的所有正元素的索引之和。 使用线程的算法的线程数为 2。为避免溢出，请使用双精度变量来存储索引的总和。",
        "实现算法的变体，用于查找原始数组的所有正元素的索引之和。 使用线程的算法的线程数为 4。为避免溢出，请使用双精度变量来存储索引的总和。",
        "实现算法的变体，用于查找具有偶数（0、2、-2、4、-4、...、100、-100）的原始数组的所有元素的算术平均值。 使用线程的算法的线程数是 2。结果必须是实数（double）。",
        "实现算法的变体，用于查找具有偶数（0、2、-2、4、-4、...、100、-100）的原始数组的所有元素的算术平均值。 使用线程的算法的线程数为 4。结果必须是实数（double）。",
        "实现算法的变体，用于查找具有偶数（0、2、-2、4、-4、...、100、-100）的原始数组的所有元素的数量。 使用线程的算法的线程数为 2。",
        "实现算法的变体，用于查找具有偶数（0、2、-2、4、-4、...、100、-100）的原始数组的所有元素的数量。 使用线程的算法的线程数为 4。",
        "实现算法的变体，用于查找具有偶数（0、2、-2、4、-4、...、100、-100）的原始数组的所有元素的索引总和。 使用线程的算法的线程数为 2。为避免溢出，请使用双精度变量来存储索引的总和。",
        "实现算法的变体，用于查找具有偶数（0、2、-2、4、-4、...、100、-100）的原始数组的所有元素的索引总和。 使用线程的算法的线程数为 4。为避免溢出，请使用双精度变量来存储索引的总和。"};
}

void TaskE::generate_task_test(int task_num)
{
    utilities::init_random_test_files_name(test_files, 1);

    seed = time(nullptr);
    srand(seed);

    arr.resize(arrsize);
    for (auto &num : arr)
    {
        num = rand() % 201 - 100;
    }

    execute_argv.clear();
    execute_argv.push_back(std::to_string(seed));
}
void TaskE::generate_task_control(int task_num)
{
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
    }
}
void TaskE::print_extral_info(int task_num)
{
}
int TaskE::check_program(int task_num) const
{
    return 1;
}