#include "tasklib.hpp"
#include "utilities.hpp"

class TaskC : public TaskLib
{
private:
    int total_test_count;
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
    TaskC();

    // virtual function inherited from parent class
    virtual void generate_task_test(int task_num);
    virtual void generate_task_control(int task_num);
    virtual void set_execute_argv(int task_num);
    virtual void print_extral_info(int task_num);
    virtual int get_total_test_count(int task_num) const;
    virtual int check_program(int task_num) const;
    virtual ~TaskC() {}
};

extern "C" TaskLib *create()
{
    return new TaskC;
}
extern "C" void destroy(TaskLib *t)
{
    delete t;
}