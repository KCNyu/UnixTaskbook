#ifndef UNIXTASKBOOK_HPP
#define UNIXTASKBOOK_HPP

#include "tasklib.hpp"
#include "utilities.hpp"
#include "service.hpp"

class UnixTaskbook
{
private:
	void *handle;
	TaskLib *tasklib;
	std::vector<std::string> supported_compiler = {"gcc", "g++"};
	int task_argc;
	std::string tasklib_name;
	std::string task_name;
	int task_num;
	std::string language_option;
	std::string program;
	std::string compile_out;
	std::string compile_log;
	std::string check_dir;
	std::vector<std::string> files;
	bool is_online = true;
	cmdline::parser command_parser;
	bool print_option = false;

protected:
	void check_task_lib();
	void parse_command(int argc, char *argv[]);
	void parse_task_name();
	void parse_compile_argv(std::string program, char **&compile_argv);
	void parse_execute_argv(char **&execute_argv);

public:
	UnixTaskbook(int argc, char *argv[]);
	void load_task_lib();
	void close_task_lib();
	void print_task_info(int task_num, std::string language_option);
	void compile_program(std::string program);
	void create_test(std::string program);
	void execute_program(std::string program);
	void check_program_result(std::string program, int test_num, bool print_option);
	void upload_program(std::string program);
	void check_program_dir(std::string dir);
	void execute_run(std::string program);
	void parse_task_name(std::string program);
	void run();
	~UnixTaskbook();
};

#endif