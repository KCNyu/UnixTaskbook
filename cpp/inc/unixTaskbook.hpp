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

	std::string task_lib_name;
	std::string task_name;
	std::string task_program_path;
	int task_num;

	std::string language_option;
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
	void parse_task_name(std::string &program);
	void parse_compile_argv(std::string program, char **&compile_argv);
	void parse_execute_argv(char **&execute_argv);

public:
	UnixTaskbook(int argc, char *argv[]);
	void load_task_lib();
	void close_task_lib();
	void print_task_info(int task_num, std::string language_option);
	void compile_program(const std::string &program);
	void create_test();
	void execute_program();
	int check_program_result(int test_num, bool print_option);
	void upload_program(const std::string &program);
	void check_program_dir(const std::string &dir);
	int execute_run(const std::string pre_task_name);
	void parse_task_name(const std::string pre_task_name);
	void run();
	~UnixTaskbook();
};

#endif