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
    std::vector<int> arr;
    unsigned int seed;
    struct tms tmsstart, tmsend;
    clock_t start, end;
    std::atomic<long> res_l;
    std::atomic<double> res_d;

protected:
    void thread_test(std::string option_alg);

public:
    utbThread();

    // virtual function inherited from parent class
    virtual void generate_task_test(int task_num);
    virtual void generate_task_control(int task_num);
    virtual void print_extral_info(int task_num);
    virtual int check_program(int task_num) const;
    virtual ~utbThread() {}

    // Helper functions are optional
    // In order to implement the above interface, it is assisted by providing
    std::vector<double> get_time();
    void print_time(std::ostream &out);
};

extern "C" TaskLib *create()
{
    return new utbThread;
}
extern "C" void destroy(TaskLib *t)
{
    delete t;
}