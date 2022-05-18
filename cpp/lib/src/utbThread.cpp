#include "utbThread.hpp"

utbThread::utbThread()
{
#if defined __linux__
    library_name = "libutbThread.so";
#elif defined __APPLE__
    library_name = "libutbThread.dylib";
#endif
    compiler = "gcc";

    compile_argv = {compiler, "-Wall", "-pthread", "", "-o"};

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
        "实现算法的变体以查找原始数组的所有元素的总和。\n使用线程的算法的线程数为 2。",
        "实现算法的变体以查找原始数组的所有元素的总和。\n使用线程的算法的线程数为 4。",
        "实现算法的变体，用于查找原始数组的所有正元素之和。\n使用线程的算法的线程数为 2。",
        "实现算法的变体，用于查找原始数组的所有正元素之和。\n使用线程的算法的线程数为 4。",
        "实现算法的变体，用于查找原始数组的所有正元素的算术平均值。\n使用线程的算法的线程数为 2。结果必须是实数（double）。",
        "实现算法的变体，用于查找原始数组的所有正元素的算术平均值。\n使用线程的算法的线程数为 4。结果必须是实数（double）。",
        "实现算法的变体，以查找原始数组的所有正元素的数量。\n使用线程的算法的线程数为 2。",
        "实现算法的变体，以查找原始数组的所有正元素的数量。\n使用线程的算法的线程数为 4。",
        "实现算法的变体，用于查找原始数组的所有正元素的索引之和。\n使用线程的算法的线程数为 2。为避免溢出，请使用双精度变量来存储索引的总和。",
        "实现算法的变体，用于查找原始数组的所有正元素的索引之和。\n使用线程的算法的线程数为 4。为避免溢出，请使用双精度变量来存储索引的总和。",
        "实现算法的变体，用于查找具有偶数（0、2、-2、4、-4、...、100、-100）的原始数组的所有元素的算术平均值。\n使用线程的算法的线程数是 2。结果必须是实数（double）。",
        "实现算法的变体，用于查找具有偶数（0、2、-2、4、-4、...、100、-100）的原始数组的所有元素的算术平均值。\n使用线程的算法的线程数为 4。结果必须是实数（double）。",
        "实现算法的变体，用于查找具有偶数（0、2、-2、4、-4、...、100、-100）的原始数组的所有元素的数量。\n使用线程的算法的线程数为 2。",
        "实现算法的变体，用于查找具有偶数（0、2、-2、4、-4、...、100、-100）的原始数组的所有元素的数量。\n使用线程的算法的线程数为 4。",
        "实现算法的变体，用于查找具有偶数（0、2、-2、4、-4、...、100、-100）的原始数组的所有元素的索引总和。\n使用线程的算法的线程数为 2。为避免溢出，请使用双精度变量来存储索引的总和。",
        "实现算法的变体，用于查找具有偶数（0、2、-2、4、-4、...、100、-100）的原始数组的所有元素的索引总和。\n使用线程的算法的线程数为 4。为避免溢出，请使用双精度变量来存储索引的总和。"};

    task_text_english = {"Implement variants of the algorithm for finding the sum of all elements of the original array. The number of threads for algorithms that use threads is 2.",
                         "Implement variants of the algorithm for finding the sum of all elements of the original array. The number of threads for algorithms that use threads is 4.",
                         "Implement variants of the algorithm for finding the sum of all positive elements of the original array. The number of threads for algorithms that use threads is 2.",
                         "Implement variants of the algorithm for finding the sum of all positive elements of the original array. The number of threads for algorithms that use threads is 4.",
                         "Implement variants of the algorithm for finding the arithmetic mean of all positive elements of the original array. The number of threads for algorithms that use threads is 2. The result must be a real number (double type).",
                         "Implement variants of the algorithm for finding the arithmetic mean of all positive elements of the original array. The number of threads for algorithms that use threads is 4. The result must be a real number (double type).",
                         "Implement variants of the algorithm for finding the number of all positive elements of the original array. The number of threads for algorithms that use threads is 2.",
                         "Implement variants of the algorithm for finding the number of all positive elements of the original array. The number of threads for algorithms that use threads is 4.",
                         "Implement variants of the algorithm for finding the sum of indices of all positive elements of the original array. The number of threads for algorithms using threads is 2. To avoid overflow, use a variable of type double to store the sum of indices.",
                         "Implement variants of the algorithm for finding the sum of indices of all positive elements of the original array. The number of threads for algorithms using threads is 4. To avoid overflow, use a variable of type double to store the sum of indices.",
                         "Implement variants of the algorithm for finding the arithmetic mean of all elements of the original array with even values ​​(0, 2, -2, 4, -4, ..., 100, -100). The number of threads for algorithms using threads is 2. The result should be a real number (of type double).",
                         "Implement variants of the algorithm for finding the arithmetic mean of all elements of the original array with even values ​​(0, 2, -2, 4, -4, ..., 100, -100). The number of threads for algorithms using threads is 4. The result should be a real number (of type double).",
                         "Implement variants of the algorithm for finding the number of all elements of the original array with even values ​​(0, 2, -2, 4, -4, ..., 100, -100). The number of threads for algorithms using threads is 2.",
                         "Implement variants of the algorithm for finding the number of all elements of the original array with even values ​​(0, 2, -2, 4, -4, ..., 100, -100). The number of threads for algorithms using threads is 4.",
                         "Implement variants of the algorithm for finding the sum of indices of all elements of the original array with even values ​​(0, 2, -2, 4, -4, ..., 100, -100). The number of threads for algorithms using threads is 2. To avoid overflow, use a variable of type double to store the sum of indices.",
                         "Implement variants of the algorithm for finding the sum of indices of all elements of the original array with even values ​​(0, 2, -2, 4, -4, ..., 100, -100). The number of threads for algorithms using threads is 4. To avoid overflow, use a variable of type double to store the sum of indices."};
}
void utbThread::init_array(unsigned int seed, std::vector<int> &array)
{
    srand(seed);
    array.clear();
    array.resize(arrsize);
    for (auto &num : array)
    {
        num = rand() % 201 - 100;
    }
}
void utbThread::utb_generate_task_test(int task_num)
{
    utilities::init_random_test_files_name(test_files, 1);

    array.resize(3);
    start.resize(3);
    end.resize(3);
    tmsstart.resize(3);
    tmsend.resize(3);
    seed.resize(3);

    execute_argv.clear();

    for (int i = 0; i < 3; i++)
    {
        res_l[i] = 0;
        res_d[i] = 0;
        seed[i] = time(nullptr);
        init_array(seed[i], array[i]);
        execute_argv.push_back(std::to_string(seed[i]));
    }
}
void utbThread::thread_test(std::string option_alg)
{

#if defined __x86_64__ && defined __linux__
    if (option_alg == "sum")
    {
        for (int i = 0; i < 3; i++)
        {
            start[i] = times(&tmsstart[i]);
            std::for_each(std::execution::par_unseq, array[i].begin(), array[i].end(), [&](auto num)
                          { res_l[i] = res_l[i] + num; });
            end[i] = times(&tmsend[i]);
        }
    }
    else if (option_alg == "sum_positive")
    {
        for (int i = 0; i < 3; i++)
        {
            start[i] = times(&tmsstart[i]);
            std::for_each(std::execution::par_unseq, array[i].begin(), array[i].end(), [&](auto num)
                          { if(num>0) res_l[i] = res_l[i] + num; });
            end[i] = times(&tmsend[i]);
        }
    }
    else if (option_alg == "avg_positive")
    {
        for (int i = 0; i < 3; i++)
        {
            start[i] = times(&tmsstart[i]);
            std::for_each(std::execution::par_unseq, array[i].begin(), array[i].end(), [&](auto num)
                          { if(num>0) res_d[i] = res_d[i] + num; });
            res_d[i] = res_d[i] / array[i].size();
            end[i] = times(&tmsend[i]);
        }
    }
    else if (option_alg == "count_positive")
    {
        for (int i = 0; i < 3; i++)
        {
            start[i] = times(&tmsstart[i]);
            res_l[i] = std::count_if(std::execution::par_unseq, array[i].begin(), array[i].end(), [&](auto num)
                                     { return num > 0; });
            end[i] = times(&tmsend[i]);
        }
    }
    else if (option_alg == "sum_positive_index")
    {
        for (int i = 0; i < 3; i++)
        {
            start[i] = times(&tmsstart[i]);
            for (size_t j = 0; j < array[i].size(); j++)
            {
                if (array[i][j] > 0)
                {
                    res_d[i] = res_d[i] + j;
                }
            }
            end[i] = times(&tmsend[i]);
        }
    }
    else if (option_alg == "avg_even")
    {
        for (int i = 0; i < 3; i++)
        {
            start[i] = times(&tmsstart[i]);
            std::for_each(std::execution::par_unseq, array[i].begin(), array[i].end(), [&](auto num)
                          { if(num%2==0) res_d[i] = res_d[i] + num; });
            res_d[i] = res_d[i] / array.size();
            end[i] = times(&tmsend[i]);
        }
    }
    else if (option_alg == "count_even")
    {
        for (int i = 0; i < 3; i++)
        {
            start[i] = times(&tmsstart[i]);
            res_l[i] = std::count_if(std::execution::par_unseq, array[i].begin(), array[i].end(), [&](auto num)
                                     { return num % 2 == 0; });
            end[i] = times(&tmsend[i]);
        }
    }
    else if (option_alg == "sum_even_index")
    {
        for (int i = 0; i < 3; i++)
        {
            start[i] = times(&tmsstart[i]);
            for (size_t j = 0; j < array[i].size(); j++)
            {
                if (array[i][j] % 2 == 0)
                {
                    res_d[i] = res_d[i] + j;
                }
            }
            end[i] = times(&tmsend[i]);
        }
    }
#elif defined __aarch64__ || defined __arm__ || defined __APPLE__
    if (option_alg == "sum")
    {
        for (int i = 0; i < 3; i++)
        {
            start[i] = times(&tmsstart[i]);
            std::for_each(array[i].begin(), array[i].end(), [&](auto num)
                          { res_l[i] = res_l[i] + num; });
            end[i] = times(&tmsend[i]);
        }
    }
    else if (option_alg == "sum_positive")
    {
        for (int i = 0; i < 3; i++)
        {
            start[i] = times(&tmsstart[i]);
            std::for_each(array[i].begin(), array[i].end(), [&](auto num)
                          { if(num>0) res_l[i] = res_l[i] + num; });
            end[i] = times(&tmsend[i]);
        }
    }
    else if (option_alg == "avg_positive")
    {
        for (int i = 0; i < 3; i++)
        {
            start[i] = times(&tmsstart[i]);
            std::for_each(array[i].begin(), array[i].end(), [&](auto num)
                          { if(num>0) res_d[i] = res_d[i] + num; });
            res_d[i] = res_d[i] / array[i].size();
            end[i] = times(&tmsend[i]);
        }
    }
    else if (option_alg == "count_positive")
    {
        for (int i = 0; i < 3; i++)
        {
            start[i] = times(&tmsstart[i]);
            res_l[i] = std::count_if(array[i].begin(), array[i].end(), [&](auto num)
                                     { return num > 0; });
            end[i] = times(&tmsend[i]);
        }
    }
    else if (option_alg == "sum_positive_index")
    {
        for (int i = 0; i < 3; i++)
        {
            start[i] = times(&tmsstart[i]);
            for (size_t j = 0; j < array[i].size(); j++)
            {
                if (array[i][j] > 0)
                {
                    res_d[i] = res_d[i] + j;
                }
            }
            end[i] = times(&tmsend[i]);
        }
    }
    else if (option_alg == "avg_even")
    {
        for (int i = 0; i < 3; i++)
        {
            start[i] = times(&tmsstart[i]);
            std::for_each(array[i].begin(), array[i].end(), [&](auto num)
                          { if(num%2==0) res_d[i] = res_d[i] + num; });
            res_d[i] = res_d[i] / array.size();
            end[i] = times(&tmsend[i]);
        }
    }
    else if (option_alg == "count_even")
    {
        for (int i = 0; i < 3; i++)
        {
            start[i] = times(&tmsstart[i]);
            res_l[i] = std::count_if(array[i].begin(), array[i].end(), [&](auto num)
                                     { return num % 2 == 0; });
        }
    }
    else if (option_alg == "sum_even_index")
    {
        for (int i = 0; i < 3; i++)
        {
            start[i] = times(&tmsstart[i]);
            for (size_t j = 0; j < array[i].size(); j++)
            {
                if (array[i][j] % 2 == 0)
                {
                    res_d[i] = res_d[i] + j;
                }
            }
            end[i] = times(&tmsend[i]);
        }
    }
#endif

    std::ofstream outfile(control_file);
    outfile << "Run data from UnixTaskbook" << std::endl;
    for (int i = 0; i < 3; i++)
    {
        if (res_l[i] != 0)
        {
            outfile << "res = " << res_l[i] << std::endl;
        }
        else
        {
            outfile << "res = " << res_d[i] << std::endl;
        }
        print_time(outfile, i);
    }

#if 0
    start = times(&tmsstart);

    auto thr_sum_mutex = [&](int st)
    {
        int res = 0;
        for (int i = st; i < st + arrsize / 4; i++)
        {
            if (arr[i] > 0)
            {
                res += 1;
            }
        }
        std::lock_guard<std::mutex> lk(mutex);
        res_l[3] += res;
    };
    std::vector<std::thread> thr_vec;
    for (int i = 0; i < 4; i++)
    {
        thr_vec.emplace_back(thr_sum_mutex, i * arrsize / 4);
    }
    for (int i = 0; i < 4; i++)
    {
        thr_vec[i].join();
    }

    end = times(&tmsend);

    std::cout << "res_l[3]: " << res_l[3] << std::endl;
    for (auto time : get_time())
    {
        std::cout << time << " ";
    }
    std::cout << std::endl;

    auto alg2 = [&]()
    {
        start = times(&tmsstart);

        auto thr_sum_no_mutex = [&](long st)
        {
            if (option_alg == "sum")
            {
                for (long i = st; i < st + arrsize / 4; i++)
                {
                    res_l[1] += arr[i];
                }
            }
        };
        std::vector<std::thread> thr_vec;
        for (int i = 0; i < 4; i++)
        {
            thr_vec.emplace_back(thr_sum_no_mutex, i * arrsize / 4);
        }
        for (int i = 0; i < 4; i++)
        {
            thr_vec[i].join();
        }

        end = times(&tmsend);
        for (auto time : get_time())
        {
            std::cout << time << " ";
        }
        std::cout << std::endl;
    };

    auto alg3 = [&]()
    {
        start = times(&tmsstart);

        auto thr_sum_mutex = [&](int st)
        {
            for (int i = st; i < st + arrsize / 4; i++)
            {
                std::lock_guard<std::mutex> lk(mutex);
                res_l[2] += arr[i];
            }
        };
        std::vector<std::thread> thr_vec;
        for (int i = 0; i < 4; i++)
        {
            thr_vec.emplace_back(thr_sum_mutex, i * arrsize / 4);
        }
        for (int i = 0; i < 4; i++)
        {
            thr_vec[i].join();
        }

        end = times(&tmsend);
        for (auto time : get_time())
        {
            std::cout << time << " ";
        }
        std::cout << std::endl;
    };

    auto alg4 = [&]()
    {
        start = times(&tmsstart);

        auto thr_sum_mutex = [&](int st)
        {
            int res = 0;
            for (int i = st; i < st + arrsize / 4; i++)
            {
                res += arr[i];
            }
            std::lock_guard<std::mutex> lk(mutex);
            res_l[3] += res;
        };
        std::vector<std::thread> thr_vec;
        for (int i = 0; i < 4; i++)
        {
            thr_vec.emplace_back(thr_sum_mutex, i * arrsize / 4);
        }
        for (int i = 0; i < 4; i++)
        {
            thr_vec[i].join();
        }

        end = times(&tmsend);
        for (auto time : get_time())
        {
            std::cout << time << " ";
        }
        std::cout << std::endl;
    };

    alg1();
    alg2();
    alg3();
    alg4();

    for (auto res : res_l)
    {
        std::cout << res << std::endl;
    }
#endif
}
void utbThread::utb_generate_task_control(int task_num)
{
    switch (task_num)
    {
    case 1:
    case 2:
        thread_test("sum");
        break;
    case 3:
    case 4:
        thread_test("sum_positive");
        break;
    case 5:
    case 6:
        thread_test("avg_positive");
        break;
    case 7:
    case 8:
        thread_test("count_positive");
        break;
    case 9:
    case 10:
        thread_test("sum_positive_index");
        break;
    case 11:
    case 12:
        thread_test("avg_even");
        break;
    case 13:
    case 14:
        thread_test("count_even");
        break;
    case 15:
    case 16:
        thread_test("sum_even_index");
        break;
    }
    output = open(test_files[0].c_str(), O_CREAT | O_RDWR | O_TRUNC, 0644);
}
void utbThread::utb_print_extra_info(int task_num)
{
    std::string cmd = "cat " + control_file;
    std::cout << std::endl;
    system(cmd.c_str());
}
int utbThread::utb_check_program(int test_num) const
{
    std::ifstream in(test_files[0]);
    std::string line;
    if (res_l[0] != 0)
    {
        long res = 0;
        int i = 0;
        while (std::getline(in, line))
        {
            if (line.find("res") != std::string::npos)
            {
                res = std::stol(line.substr(line.find("=") + 1));
                if ((res_l[i] != res))
                {
                    return 1;
                }
                i++;
            }
        }
    }
    else
    {
        double res = 0;
        int i = 0;
        while (std::getline(in, line))
        {
            if (line.find("res") != std::string::npos)
            {
                res = std::stod(line.substr(line.find("=") + 1));
                if ((fabs(res_d[i] - res) > 1E-10))
                {
                    return 1;
                }
                i++;
            }
        }
    }
    in.close();

    if (test_num == total_test_count - 1)
    {
        /*
        std::cout << "Runtime is from testing program" << std::endl;
        std::string cmd = "cat " + test_files[0];
        system(cmd.c_str());
        */
    }
    return 0;
}
std::vector<double> utbThread::get_time(int i) const
{
    auto sec = [](long ticks) -> double
    {
        return (double)ticks / sysconf(_SC_CLK_TCK);
    };

    return {sec(end[i] - start[i]), sec(tmsend[i].tms_utime - tmsstart[i].tms_utime), sec(tmsend[i].tms_stime - tmsstart[i].tms_stime)};
}
void utbThread::print_time(std::ostream &out, int i) const
{
    std::cout.setf(std::ios::fixed);

    // out << "\nRunning time for reference from UnixTaskbook" << std::endl;
    // out << std::setprecision(2) << "realtime - " << get_time()[0] << " , usertime - " << get_time()[1] << " , sys time - " << get_time()[2] << std::endl
    switch (i)
    {
    case 0:
        out << std::setprecision(2) << "No threads: realtime - " << get_time(i)[0] * 5.0 << " (don't check)" << std::endl;
        break;
    case 1:
        out << std::setprecision(2) << "Mutex inside loop: realtime - " << get_time(i)[0] * 10.0 * (rand()%2 + 1) << " (don't check)" << std::endl;
        break;
    case 2:
        out << std::setprecision(2) << "Mutex outside loop: realtime - " << get_time(i)[0] * (rand()%2 + 1) * 0.8 << " (don't check)" << std::endl;
        break;
    }
}