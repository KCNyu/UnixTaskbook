#ifndef TASKCHECKER_HPP
#define TASKCHECKER_HPP

#include "tasklib.hpp"
#include "utilities.hpp"

#define VALID_I(i) (i + 1 < argc)
#define VALID_ARG(str1, str2) (strcmp(argv[i], str1) == 0 || strcmp(argv[i], str2) == 0)

class TaskChecker
{
private:
	void *handle;
	TaskLib *tasklib;
	std::vector<std::string> supported_complier = {"gcc", "g++"};
	int task_argc;
	std::vector<std::string> task_argv;
	std::string tasklib_name;
	std::string task_name;
	int task_num;
	std::string language_option;
	std::string program;

public:
	TaskChecker(int argc, char *argv[]);
	void check_task_lib();
	void print_task_info(int task_num, std::string language_option);
	void print_default_help();
	void parse_command(int argc, char *argv[]);
	void parse_task_name();
	void complie_program(std::string program);
	void run();
	~TaskChecker();
};

#endif