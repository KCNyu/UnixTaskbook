#include "tasklib.hpp"
#include "utilities.hpp"

class TaskB : public TaskLib
{
private:
	char c[50];
	size_t sz;
	int f_control;
	int total_test_count;

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
	void test17();

public:
	TaskB();

	// virtual function inherited from parent class
	virtual void generate_task_test(int task_num);
	virtual void generate_task_control(int task_num);
	virtual void set_execute_argv(int task_num);
	virtual void print_extral_info(int task_num);
	virtual int get_total_test_count(int task_num) const;
	virtual ~TaskB() {}

	// Helper functions are optional
	// In order to implement the above interface, it is assisted by providing
	void init_random_test_files_name(size_t test_file_count);
};

extern "C" TaskLib *create()
{
	return new TaskB;
}
extern "C" void destroy(TaskLib *t)
{
	delete t;
}