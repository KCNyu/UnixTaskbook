#include "tasklib.hpp"
#include "utilities.hpp"
#include <sstream>

class utbText : public TaskLib
{
private:
    int f1, f2;
    char S[50];
    int n, n2;
    char buf[200];
    char buf2[200];
    char empty = '\n';
    int j = 0;
    int K;
    bool use_flag = false;
    std::vector<std::string> text_data;

protected:
    void test1();
    void test2();
    void test3();
    void test4();
    void test5();
    void test6();
    void test7();
    void test8();
    void test9();
    void test10();
    void test11();
    void test12();
    void test13();
    void test14();
    void test15();
    void test16();

public:
    utbText();

    // virtual function inherited from parent class
    virtual void utb_generate_task_test(int task_num);
    virtual void utb_generate_task_control(int task_num);
    virtual void utb_print_extral_info(int task_num);
    virtual int utb_check_program(int task_num) const;
    virtual ~utbText() {}

    // Helper functions are optional
    // In order to implement the above interface, it is assisted by providing
};

extern "C" TaskLib *create()
{
    return new utbText;
}
extern "C" void destroy(TaskLib *t)
{
    delete t;
}