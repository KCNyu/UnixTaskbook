#include "tasklib.hpp"
#include "utilities.hpp"

class TaskD : public TaskLib
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
    TaskD();

    // virtual function inherited from parent class
    virtual void generate_task_test(int task_num);
    virtual void generate_task_control(int task_num);
    virtual void print_extral_info(int task_num);
    virtual int check_program(int task_num) const;
    virtual ~TaskD() {}

    // Helper functions are optional
    // In order to implement the above interface, it is assisted by providing
    void init_random_test_files_name(size_t test_file_count);
    bool foo_judge(std::string cmd);
    void init_helper_sys_cmd(std::string split);
};

extern "C" TaskLib *create()
{
    return new TaskD;
}
extern "C" void destroy(TaskLib *t)
{
    delete t;
}