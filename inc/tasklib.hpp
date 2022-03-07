#ifndef TASKLIB_HPP
#define TASKLIB_HPP

#include "header.hpp"

class TaskLib
{
protected:
	std::vector<std::string> task_text_russian;
	std::vector<std::string> task_text_chinese;

	std::vector<std::string> complie_argv;

	std::vector<std::string> execute_argv;

	std::vector<std::string> test_files;
	std::string control_file = "_control.tst";
	std::string result_file;

	std::string complier;

	std::string library_name;

	int task_count;
	int output = 1;
	int f_control;
	int total_test_count;

public:
	// Public real function
	// Implemented by tasklib itself
	TaskLib() {}
	int get_task_count() const;
	std::vector<std::string> get_execute_argv() const;
	std::string get_task_info(int task_num, int language_option) const;

	// The virtual function (interface)
	// Implemented by each tasklib itself
	virtual void generate_task_test(int task_num) = 0;
	virtual void generate_task_control(int task_num) = 0;
	virtual void print_extral_info(int task_num) = 0;
	virtual int check_program(int task_num) const = 0;
	virtual ~TaskLib() {}

	// friend class
	friend class UnixTaskbook;
};

// the types of the class factories
typedef TaskLib *create_t();
typedef void destroy_t(TaskLib *);

#endif