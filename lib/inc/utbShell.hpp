#include "tasklib.hpp"
#include "utilities.hpp"

class utbShell : public TaskLib
{
private:
    std::vector<std::vector<std::string>> random_cmds;
    std::vector<std::vector<std::string>> random_cmds_stdout;
    std::vector<std::vector<std::string>> random_cmds_stdin;

    int f;
    int backup;
    std::string sys_cmd;

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
    utbShell();

    // virtual function inherited from parent class
    virtual void utb_generate_task_test(int task_num);
    virtual void utb_generate_task_control(int task_num);
    virtual void utb_print_extral_info(int task_num);
    virtual int utb_check_program(int test_num) const;
    virtual ~utbShell() {}

    // Helper functions are optional
    // In order to implement the above interface, it is assisted by providing
    bool foo_judge(std::string cmd);
    void init_helper_sys_cmd(std::string split);
};

extern "C" TaskLib *create()
{
    return new utbShell;
}
extern "C" void destroy(TaskLib *t)
{
    delete t;
}