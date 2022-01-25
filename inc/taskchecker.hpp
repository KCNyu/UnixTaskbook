#ifndef TASKCHECKER_HPP
#define TASKCHECKER_HPP

#include "tasklib.hpp"
#include "utilities.hpp"

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
	std::string complie_out;
	std::string complie_log;
	cmdline::parser command_parser;

public:
	TaskChecker(int argc, char *argv[]);
	void check_task_lib();
	void print_task_info(int task_num, std::string language_option);
	void parse_command(int argc, char *argv[]);
	void parse_task_name();
	void parse_complie_argv(char **&complie_argv);
	void complie_program(std::string program);
	void run();
	~TaskChecker();
};

#endif