#include "tasklib.hpp"
#include "utilities.hpp"

class utbFile : public TaskLib
{
private:
	char c[50];
	size_t sz;

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
	utbFile();

	// virtual function inherited from parent class
	virtual void utb_generate_task_test(int task_num);
	virtual void utb_generate_task_control(int task_num);
	virtual void utb_print_extral_info(int task_num);
	virtual int utb_check_program(int task_num) const;
	virtual ~utbFile() {}

	// Helper functions are optional
	// In order to implement the above interface, it is assisted by providing
};

extern "C" TaskLib *create()
{
	return new utbFile;
}
extern "C" void destroy(TaskLib *t)
{
	delete t;
}