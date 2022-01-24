#ifndef TASKLIB_HPP
#define TASKLIB_HPP

#include "header.hpp"

class TaskLib
{
protected:
	std::vector<std::string> task_text_russian;
	std::vector<std::string> task_text_chinese;
	std::vector<std::string> task_argv;
	std::string control_file = "_control.tst";
	std::string result_file;
	std::string complier;
	std::string library_name;
	int task_argc;
	int task_count;
	int file_input;
	int file_output;

public:
	TaskLib() {}
	virtual ~TaskLib() {}
	int get_task_count() const;
	std::string get_task_info(int task_num, int language_option) const;
	//virtual void generate_task_test(int task_num) const;
	friend class TaskChecker;
};

// the types of the class factories
typedef TaskLib *create_t();
typedef void destroy_t(TaskLib *);

#endif