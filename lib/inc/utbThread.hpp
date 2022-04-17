#include "tasklib.hpp"
#include "utilities.hpp"
#include <sys/times.h>
#include <algorithm>
#if defined __x86_64__
#include <execution>
#endif
#include <atomic>
#include <fstream>
#include <iomanip>
#include <cmath>

int res_nmd = 0;
class utbThread : public TaskLib
{
private:
    const size_t arrsize = 80000000;
    std::vector<std::vector<int>> array;
    std::vector<unsigned int> seed;
    //std::atomic<long> res_l[3];
    //std::atomic<double> res_d[3];
    long res_l[3];
    double res_d[3];
    std::vector<struct tms> tmsstart, tmsend;
    std::vector<clock_t> start, end;

protected:
    void thread_test(std::string option_alg);
    void init_array(unsigned int seed, std::vector<int> &array);

public:
    utbThread();

    // virtual function inherited from parent class
    virtual void utb_generate_task_test(int task_num);
    virtual void utb_generate_task_control(int task_num);
    virtual void utb_print_extra_info(int task_num);
    virtual int utb_check_program(int test_num) const;
    virtual ~utbThread() {}

    // Helper functions are optional
    // In order to implement the above interface, it is assisted by providing
    std::vector<double> get_time(int i) const;
    void print_time(std::ostream &out, int i) const;
};

extern "C" TaskLib *create()
{
    return new utbThread;
}
extern "C" void destroy(TaskLib *t)
{
    delete t;
}