#include "utbThread.hpp"

utbThread::utbThread()
{
#if defined __linux__
    library_name = "libutbThread.so";
#elif defined __APPLE__
    library_name = "libutbThread.dylib";
#endif
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
}

void utbThread::utb_generate_task_test(int task_num)
{
    utilities::init_random_test_files_name(test_files, 1);

    res_l = 0;
    res_d = 0;

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
void utbThread::thread_test(std::string option_alg)
{
    start = times(&tmsstart);
#if defined __x86_64__ && defined __linux__
    if (option_alg == "sum")
    {
        std::for_each(std::execution::par_unseq, arr.begin(), arr.end(), [&](auto num)
                      { res_l = res_l + num; });
    }
    else if (option_alg == "sum_positive")
    {
        std::for_each(std::execution::par_unseq, arr.begin(), arr.end(), [&](auto num)
                      { if(num>0) res_l = res_l + num; });
    }
    else if (option_alg == "avg_positive")
    {
        std::for_each(std::execution::par_unseq, arr.begin(), arr.end(), [&](auto num)
                      { if(num>0) res_d = res_d + num; });
        res_d = res_d / arr.size();
    }
    else if (option_alg == "count_positive")
    {
        res_l = std::count_if(std::execution::par_unseq, arr.begin(), arr.end(), [&](auto num)
                              { return num > 0; });
    }
    else if (option_alg == "sum_positive_index")
    {
        for (size_t i = 0; i < arr.size(); i++)
        {
            if (arr[i] > 0)
            {
                res_d = res_d + i;
            }
        }
    }
    else if (option_alg == "avg_even")
    {
        std::for_each(std::execution::par_unseq, arr.begin(), arr.end(), [&](auto num)
                      { if(num%2==0) res_d = res_d + num; });
        res_d = res_d / arr.size();
    }
    else if (option_alg == "count_even")
    {
        res_l = std::count_if(std::execution::par_unseq, arr.begin(), arr.end(), [&](auto num)
                              { return num % 2 == 0; });
    }
    else if (option_alg == "sum_even_index")
    {
        for (size_t i = 0; i < arr.size(); i++)
        {
            if (arr[i] % 2 == 0)
            {
                res_d = res_d + i;
            }
        }
    }
#elif defined __aarch64__ || defined __arm__ || defined __APPLE__
    if (option_alg == "sum")
    {
        std::for_each(arr.begin(), arr.end(), [&](auto num)
                      { res_l = res_l + num; });
    }
    else if (option_alg == "sum_positive")
    {
        std::for_each(arr.begin(), arr.end(), [&](auto num)
                      { if(num>0) res_l = res_l + num; });
    }
    else if (option_alg == "avg_positive")
    {
        std::for_each(arr.begin(), arr.end(), [&](auto num)
                      { if(num>0) res_d = res_d + num; });
        res_d = res_d / arr.size();
    }
    else if (option_alg == "count_positive")
    {
        res_l = std::count_if(arr.begin(), arr.end(), [&](auto num)
                              { return num > 0; });
    }
    else if (option_alg == "sum_positive_index")
    {
        for (size_t i = 0; i < arr.size(); i++)
        {
            if (arr[i] > 0)
            {
                res_d = res_d + i;
            }
        }
    }
    else if (option_alg == "avg_even")
    {
        std::for_each(arr.begin(), arr.end(), [&](auto num)
                      { if(num%2==0) res_d = res_d + num; });
        res_d = res_d / arr.size();
    }
    else if (option_alg == "count_even")
    {
        res_l = std::count_if(arr.begin(), arr.end(), [&](auto num)
                              { return num % 2 == 0; });
    }
    else if (option_alg == "sum_even_index")
    {
        for (size_t i = 0; i < arr.size(); i++)
        {
            if (arr[i] % 2 == 0)
            {
                res_d = res_d + i;
            }
        }
    }
#endif
    end = times(&tmsend);

    std::ofstream outfile(control_file);

    if (res_l != 0)
    {
        outfile << "res = " << res_l << std::endl;
    }
    else
    {
        outfile << "res = " << res_d << std::endl;
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
    print_time(std::cout);
}
int utbThread::utb_check_program(int test_num) const
{
    std::ifstream in(test_files[0]);
    std::string line;
    if (res_l != 0)
    {
        long res = 0;
        int flag = 0;
        while (std::getline(in, line))
        {
            if (line.find("res") != std::string::npos)
            {
                res = std::stol(line.substr(line.find("=") + 1));
                if ((res_l != res) && flag != 1)
                {
                    return 1;
                }
                flag++;
            }
        }
    }
    else
    {
        double res = 0;
        int flag = 0;
        while (std::getline(in, line))
        {
            if (line.find("res") != std::string::npos)
            {
                res = std::stod(line.substr(line.find("=") + 1));
                if ((fabs(res_d - res) > 1E-10) && flag != 1)
                {
                    return 1;
                }
                flag++;
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
std::vector<double> utbThread::get_time() const
{
    auto sec = [](long ticks) -> double
    {
        return (double)ticks / sysconf(_SC_CLK_TCK);
    };

    return {sec(end - start), sec(tmsend.tms_utime - tmsstart.tms_utime), sec(tmsend.tms_stime - tmsstart.tms_stime)};
}
void utbThread::print_time(std::ostream &out) const
{
    std::cout.setf(std::ios::fixed);

    out << "\nFYI the correct runtime is from unixTaskbook" << std::endl;
    out << std::setprecision(2) << "realtime - " << get_time()[0] << " , usertime - " << get_time()[1] << " , sys time - " << get_time()[2] << std::endl
        << std::endl;
}