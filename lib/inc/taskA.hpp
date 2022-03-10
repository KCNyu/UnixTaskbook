#include "tasklib.hpp"
#include "utilities.hpp"

class TaskA : public TaskLib
{
private:
    std::string sys_cmd;
    std::string work_dir;
    std::string execute_dir;
    std::vector<std::string> extension_name;
    std::vector<std::string> sub_dir;

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

public:
    TaskA();

    // virtual function inherited from parent class
    virtual void generate_task_test(int task_num);
    virtual void generate_task_control(int task_num);
    virtual void print_extral_info(int task_num);
    virtual int check_program(int task_num) const;
    virtual ~TaskA() {}

    // Helper functions are optional
    // In order to implement the above interface, it is assisted by providing
    void generate_test_file(std::string dirname, int count);
};

extern "C" TaskLib *create()
{
    return new TaskA;
}
extern "C" void destroy(TaskLib *t)
{
    delete t;
}