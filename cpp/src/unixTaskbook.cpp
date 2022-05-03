#include "unixTaskbook.hpp"

UnixTaskbook::UnixTaskbook(int argc, char *argv[])
{
	// parse
	parse_command(argc, argv);
}
UnixTaskbook::~UnixTaskbook()
{
	// close_task_lib();
}
void UnixTaskbook::load_task_lib()
{
	// load the task library
	handle = dlopen(task_lib_name.c_str(), RTLD_LAZY);
	dlopen_error_handle(handle, "Cannot load library: ");

	// load the create symbols
	create_t *create_tasklib = (create_t *)dlsym(handle, "create");
	dlsym_error_handle(dlerror(), "Cannot load symbol create: ");

	// create an instance of the class
	tasklib = create_tasklib();

	// check validity
	check_task_lib();
}
void UnixTaskbook::close_task_lib()
{
	// load the destroy symbols
	destroy_t *destroy_tasklib = (destroy_t *)dlsym(handle, "destroy");
	dlsym_error_handle(dlerror(), "Cannot load symbol destroy: ");

	// destroy the class
	destroy_tasklib(tasklib);

	// unload the task library
	dlclose(handle);
}
void UnixTaskbook::check_task_lib()
{
	// check task count
	assert(tasklib->get_task_count() == tasklib->task_text_russian.size());
	assert(tasklib->get_task_count() == tasklib->task_text_chinese.size());

	// check tasklib name
	assert(tasklib->library_name == task_lib_name);

	// check compiler
	assert(std::find(supported_compiler.begin(), supported_compiler.end(), tasklib->compiler) != supported_compiler.end());
}
void UnixTaskbook::print_task_info(int task_num, std::string language_option)
{
	if (task_num > tasklib->get_task_count() || task_num <= 0)
	{
		LOG_ERROR("Exceeds the number of tasks!\nThe maximum number of %s is %d", task_lib_name.substr(0, tasklib->library_name.size() - 3).c_str(), tasklib->get_task_count());
	}
	if (print_option)
	{
		LOG_MESSAGE("                           ---------------------")
		std::cout << BLAK << "==========================| "
				  << "TASK INFO" << std::setw(10) << task_name << " |=========================" << RESET << std::endl;
		LOG_MESSAGE("                           ---------------------\n");
	}
	else
	{
		std::cout << BLAK << "==========================| "
				  << "TASK INFO" << std::setw(10) << task_name << " |=========================" << RESET << std::endl;
	}

	if (language_option.size() == 0)
	{
		language_option = "ru";
	}
	transform(language_option.begin(), language_option.end(), language_option.begin(), ::tolower);

	if (language_option == "ru" || language_option == "russian")
	{
		// std::cout << tasklib->get_task_info(task_num, 0) << std::endl;
		utilities::normalized_output_text(tasklib->get_task_info(task_num, 0), 120);
	}
	else if (language_option == "ch" || language_option == "chinese")
	{
		utilities::normalized_output_text(tasklib->get_task_info(task_num, 1), 85);
	}
	else if (language_option == "en" || language_option == "english")
	{
		utilities::normalized_output_text(tasklib->get_task_info(task_num, 2), 70);
	}

	LOG_MESSAGE("%s", utilities::divider.c_str());
}

void UnixTaskbook::parse_task_name(const std::string pre_task_name)
{
	if (pre_task_name.find("/") != std::string::npos && pre_task_name.find(".c") != std::string::npos)
	{
		// get task name without path and extension
		this->task_name = pre_task_name.substr(pre_task_name.find_last_of("/") + 1, pre_task_name.find_last_of(".") - pre_task_name.find_last_of("/") - 1);
		this->task_program_path = pre_task_name;
	}
	else if (pre_task_name.find("/") == std::string::npos && task_name.find(".c") != std::string::npos)
	{
		// get task name without extension
		this->task_name = pre_task_name.substr(0, pre_task_name.find_last_of("."));
		this->task_program_path = "./" + pre_task_name;
	}
	else if (pre_task_name.find("/") != std::string::npos && task_name.find(".c") == std::string::npos)
	{
		// get task name without path
		this->task_name = pre_task_name.substr(pre_task_name.find_last_of("/") + 1);
		this->task_program_path = pre_task_name + ".c";
	}
	else
	{
		this->task_name = pre_task_name;
		this->task_program_path = "./" + pre_task_name + ".c";
	}

	std::string numerics("0123456789");
	std::string::size_type pos = this->task_name.find_first_of(numerics);
#if defined __linux__
	task_lib_name = std::string("libutb") + this->task_name.substr(0, pos) + ".so";
#elif defined __APPLE__
	task_lib_name = std::string("libutb") + this->task_name.substr(0, pos) + ".dylib";
#endif
	task_num = atoi(this->task_name.substr(pos).c_str());
}
void UnixTaskbook::parse_command(int argc, char *argv[])
{
	command_parser.add<std::string>("task", 't', "tasks to view/check", false, "");
	command_parser.add<std::string>("language", 'l', "language to describe the task info", false, "ru");
	// command_parser.add<std::string>("program", 'p', "checked program(TaskGroupNumber.c), when specifying this parameter, you can not specify the -t parameter", false, "");
	command_parser.add<std::string>("directory", 'd', "check all programs in the directory, -p -t parameters are invalid after using this parameter", false, "");
	command_parser.add("showtest", 's', "show all test when checking");
	command_parser.add("help", 'h', "display this help and exit");

	command_parser.footer("Development of a system for automatic verification of educational tasks in Linux.");

	if (argc == 1)
	{
		std::cerr << command_parser.usage();
		exit(EXIT_FAILURE);
	}

	command_parser.parse_check(argc, argv);
	task_name = command_parser.get<std::string>("task");
	language_option = command_parser.get<std::string>("language");
	// program = command_parser.get<std::string>("program");
	check_dir = command_parser.get<std::string>("directory");
	print_option = command_parser.exist("showtest");

	std::string utb_show_mode;
	if (getenv("UTB_SHOW_MODE") != NULL)
	{
		utb_show_mode = std::string(getenv("UTB_SHOW_MODE"));
	}
	if (utb_show_mode.size() != 0)
	{

		transform(utb_show_mode.begin(), utb_show_mode.end(), utb_show_mode.begin(), ::tolower);
		if (utb_show_mode == "true")
		{
			print_option = true;
		}
		else if (utb_show_mode == "false")
		{
			print_option = false;
		}
	}
}
void UnixTaskbook::parse_compile_argv(std::string program, char **&compile_argv)
{
	size_t compile_argc = tasklib->compile_argv.size();

	compile_argv = new char *[compile_argc + 2];

	for (size_t i = 0; i < compile_argc; i++)
	{
		compile_argv[i] = new char[100];
		if (tasklib->compile_argv[i].size() == 0)
		{
			strcpy(compile_argv[i], program.c_str());
			continue;
		}
		strcpy(compile_argv[i], tasklib->compile_argv[i].c_str());
	}

	compile_argv[compile_argc] = new char[100];
	strcpy(compile_argv[compile_argc], compile_out.c_str());

	compile_argv[compile_argc + 1] = NULL;
}
void UnixTaskbook::compile_program(const std::string &program)
{
	if (!utilities::exists_file(program))
	{
		// LOG_ERROR("Error: Checked program %s not found\n", program.c_str());
		exit(1);
	}

	compile_log = std::string(program.substr(0, strrchr(program.c_str(), '.') - program.c_str()));
	compile_out = compile_log;
	compile_log += "." + tasklib->compiler + "log";
	compile_out += ".out";

	// compare the changetime with the last compile time
	if (utilities::exists_file(compile_out))
	{
		struct stat file_stat, out_stat;
		stat(program.c_str(), &file_stat);
		stat(compile_out.c_str(), &out_stat);
		if (file_stat.st_mtime <= out_stat.st_mtime)
		{
			return;
		}
	}

	int file_log = open(compile_log.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (!file_log)
	{
		LOG_ERROR("Error during creation log-file: ");
	}
	if (print_option)
	{
		LOG_PROCESS("                            -------------------");
		LOG_PROCESS(">>>>>>>>>>>>>>>>>>>>>>>>>>>| Compiling program |>>>>>>>>>>>>>>>>>>>>>>>>>>>");
		LOG_PROCESS("                            -------------------\n");
	}
	else
	{
		LOG_PROCESS(">>>>>>>>>>>>>>>>>>>>>>>>>>>| Compiling program |>>>>>>>>>>>>>>>>>>>>>>>>>>>");
	}

	unlink(compile_out.c_str());

	pid_t pid = fork();
	if (pid == 0)
	{
		dup2(file_log, STDERR_FILENO);
		close(file_log);

		char **compile_argv;
		parse_compile_argv(program, compile_argv);

		execvp(tasklib->compiler.c_str(), compile_argv);
		if (print_option)
		{
			LOG_INFO("                              ----------------------------------")
			LOG_INFO("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<| An error occurred while Compiling |<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
			LOG_ERROR("                              ----------------------------------\n");
		}
		else
		{
			LOG_ERROR("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<| An error occurred while Compiling |<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
		}
	}
	close(file_log);

	int status;
	pid = waitpid(pid, &status, 0);
	if (pid < 0)
	{
		if (print_option)
		{
			LOG_INFO("                              ----------------------------------")
			LOG_INFO("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<| An error occurred while Compiling |<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
			LOG_ERROR("                              ----------------------------------\n");
		}
		else
		{
			LOG_ERROR("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<| An error occurred while Compiling |<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
		}
	}

	if (!utilities::exists_file(compile_out))
	{
		utilities::show_file(compile_log, "", 0);
		if (print_option)
		{
			LOG_INFO("                             ---------------")
			LOG_INFO("<<<<<<<<<<<<<<<<<<<<<<<<<<<<| Compile error |<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
			LOG_ERROR("                             ---------------\n");
		}
		else
		{
			LOG_ERROR("<<<<<<<<<<<<<<<<<<<<<<<<<<<<| Compile error |<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
		}
	}

	struct stat statbuf;
	stat(compile_log.c_str(), &statbuf);
	if (statbuf.st_size > 0)
	{
		utilities::show_file(compile_log, "", 0);
		if (print_option)
		{
			LOG_WARN("  			     -----------------");
			LOG_WARN("<<<<<<<<<<<<<<<<<<<<<<<<<<<<| Compile warning |<<<<<<<<<<<<<<<<<<<<<<<<<<<");
			LOG_WARN("  			     -----------------\n");
		}
		else
		{
			LOG_WARN("<<<<<<<<<<<<<<<<<<<<<<<<<<<<| Compile warning |<<<<<<<<<<<<<<<<<<<<<<<<<<<");
		}
	}
	else
	{
		unlink(compile_log.c_str());
		if (print_option)
		{
			LOG_SUCCESS(" 		        ---------------------------");
			LOG_SUCCESS("<<<<<<<<<<<<<<<<<<<<<<<| Compilation is successful |<<<<<<<<<<<<<<<<<<<<<<");
			LOG_SUCCESS(" 		        ---------------------------\n");
		}
		else
		{
			LOG_SUCCESS("<<<<<<<<<<<<<<<<<<<<<<<| Compilation is successful |<<<<<<<<<<<<<<<<<<<<<<");
		}
	}
}
void UnixTaskbook::create_test()
{
	tasklib->utb_generate_task_test(task_num);
	tasklib->utb_generate_task_control(task_num);
}
void UnixTaskbook::parse_execute_argv(char **&execute_argv)
{
	size_t execute_argc = tasklib->get_execute_argv().size();
	execute_argv = new char *[execute_argc + 2];

	execute_argv[0] = new char[100];
	strcpy(execute_argv[0], compile_out.c_str());

	for (size_t i = 1; i < execute_argc + 1; i++)
	{
		execute_argv[i] = new char[100];
		strcpy(execute_argv[i], tasklib->execute_argv[i - 1].c_str());
	}
	execute_argv[execute_argc + 1] = NULL;
}
void UnixTaskbook::execute_program()
{
	// std::cout << "Program output:\n"
	//		  << "-------------------------------------------" << std::endl;

	pid_t pid = fork();
	if (pid == 0)
	{
		char **execute_argv;
		parse_execute_argv(execute_argv);
#if 1
		for (size_t i = 0; i < tasklib->execute_argv.size() + 1; i++)
		{
			std::cout << BLAK << execute_argv[i] << " ";
		}
		std::cout << std::endl;
#endif
		dup2(tasklib->output, STDOUT_FILENO);
		execvp(compile_out.c_str(), execute_argv);
		LOG_ERROR("Error when running program %s", compile_out.c_str());
	}
	int status;
	pid = waitpid(pid, &status, 0);

	// std::cout << "\n-------------------------------------------" << std::endl;
	if (pid < 0)
	{
		LOG_ERROR("Error during running: %s", compile_out.c_str());
	}
}
int UnixTaskbook::check_program_result(int test_num, bool print_option)
{
	/*
	LOG_PROCESS(" ------------------");
	LOG_PROCESS("| Checking results |");
	LOG_PROCESS(" ------------------\n");
	*/
	int status = tasklib->utb_check_program(test_num);

	switch (status)
	{
	case 0:
		if (print_option || test_num == tasklib->total_test_count - 1)
		{
			tasklib->utb_print_extra_info(task_num);
			utilities::show_file(tasklib->test_files[0], "Output results from the file: ", 2);
		}
		if (print_option)
		{
			LOG_SUCCESS("\n                             ----------------")
			LOG_SUCCESS("<<<<<<<<<<<<<<<<<<<<<<<<<<<<| Correct result |<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
			LOG_SUCCESS("                             ----------------\n");
		}
		else
		{
			LOG_SUCCESS("<<<<<<<<<<<<<<<<<<<<<<<<<<<<| Correct result |<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
		}
		break;
	default:
		tasklib->utb_print_extra_info(task_num);
		utilities::show_file(tasklib->test_files[0], "Output results from the file: ", 2);
		if (print_option)
		{
			LOG_INFO("\n                             --------------")
			LOG_INFO("<<<<<<<<<<<<<<<<<<<<<<<<<<<<| Wrong result |<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
			LOG_INFO("                             --------------\n");
		}
		else
		{
			LOG_INFO("<<<<<<<<<<<<<<<<<<<<<<<<<<<<| Wrong result |<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
		}

		utilities::show_file(tasklib->control_file, "Correct results must be as follows:", 1);
	}
	return status;
}
void UnixTaskbook::upload_program(const std::string &program)
{
	if (print_option)
	{
		LOG_PROCESS("\n                            -------------------");
		LOG_PROCESS(">>>>>>>>>>>>>>>>>>>>>>>>>>>| Uploading program |>>>>>>>>>>>>>>>>>>>>>>>>>>>");
		LOG_PROCESS("                            -------------------\n");
	}
	else
	{
		LOG_PROCESS(">>>>>>>>>>>>>>>>>>>>>>>>>>>| Uploading program |>>>>>>>>>>>>>>>>>>>>>>>>>>>");
	}
	std::string username = getenv("UTB_USERNAME");
	std::string password = getenv("UTB_PASSWORD");
	/*
	initService(is_online);
	if (is_online)
	{
		sendFile(program.c_str());
	}
	*/
	std::string command = R"(LOGIN_URL=114.132.220.211:8000/accounts/login/
YOUR_USER=)";
	command += username + "\n" + R"(YOUR_PASS=)";
	command += password + "\n" + R"(COOKIES=cookies.txt
CURL_BIN="curl -s -c $COOKIES -b $COOKIES -e $LOGIN_URL"

$CURL_BIN $LOGIN_URL > /dev/null
CSRF=$(grep 'csrf' $COOKIES | awk '{print $NF}')
DJANGO_TOKEN="csrfmiddlewaretoken=$CSRF"

$CURL_BIN \
    -d "$DJANGO_TOKEN&username=$YOUR_USER&password=$YOUR_PASS" \
    -X POST $LOGIN_URL

$CURL_BIN \
    --cookie "csrftoken=${CSRF}" \
    -F "csrfmiddlewaretoken=${CSRF}" \)";
	command += "\n    ";
	command += R"(-F "file=@)" + task_program_path + R"(" \
    -F "username=${YOUR_USER}" \
    --url '114.132.220.211:8000/upload/'
	rm -f $COOKIES
	)";
	// printf("%s\n", command.c_str());
	system(command.c_str());
	if (print_option)
	{
		LOG_SUCCESS("\n                            -------------------");
		LOG_SUCCESS("<<<<<<<<<<<<<<<<<<<<<<<<<<<<| Uploaded program |<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
		LOG_SUCCESS("                            -------------------\n");
	}
	else
	{
		LOG_SUCCESS("<<<<<<<<<<<<<<<<<<<<<<<<<<<<| Uploaded program |<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
	}
}
// check all program files in the directory
void UnixTaskbook::check_program_dir(const std::string &dir)
{
	// get directory pure name
	std::string dir_pure_name = dir;
	std::string::size_type pos_slash = dir_pure_name.find_last_of("/");
	if (pos_slash != std::string::npos)
	{
		dir_pure_name = dir_pure_name.substr(pos_slash + 1);
	}
	std::string dir_result_file = dir_pure_name + "_result.txt";
	std::vector<std::string> dir_tasks_passed;
	std::vector<std::string> dir_tasks_failed;
	std::ofstream result_file(dir_result_file, std::ios::out);
	auto start = std::chrono::system_clock::now();

	if (print_option)
	{
		LOG_PROCESS("                   -------------------------------------");
		LOG_PROCESS(">>>>>>>>>>>>>>>>>>| Checking program files in directory |>>>>>>>>>>>>>>>>>");
		LOG_PROCESS("                   -------------------------------------\n");
	}
	else
	{
		LOG_PROCESS(">>>>>>>>>>>>>>>>>>| Checking program files in directory |>>>>>>>>>>>>>>>>>");
	}

	utilities::get_files_in_dir(dir, files);

	// check all files by using execute_run
	int count = 0;
	for (size_t i = 0; i < files.size(); i++)
	{
		if (files[i].find(".c") == std::string::npos)
		{
			continue;
		}
		std::string numerics("0123456789");
		std::string::size_type pos = task_name.find_first_of(numerics);

		if (command_parser.exist("task") && files[i].find(task_name.substr(0, pos)) == std::string::npos && task_name != "*")
		{
			// std::cout << "Skipping file: " << files[i] << std::endl;
			// std::cout << "It is not a program for task: " << task_name.substr(0, pos) << std::endl;
			continue;
		}
		std::string program = dir + "/" + files[i];
		if (print_option)
		{
			LOG_PROCESS("\n                           --------------------");
			LOG_PROCESS(">>>>>>>>>>>>>>>>>>>>>>>>>>| Checking program %d |>>>>>>>>>>>>>>>>>>>>>>>>>>", count + 1);
			LOG_PROCESS("                           --------------------\n");
		}
		else
		{
			LOG_PROCESS(">>>>>>>>>>>>>>>>>>>>>>>>>>| Checking program %d |>>>>>>>>>>>>>>>>>>>>>>>>>>", count + 1);
		}

		int status = execute_run(program);
		if (status == 0)
		{
			dir_tasks_passed.push_back(task_name);
		}
		else
		{
			dir_tasks_failed.push_back(task_name);
		}
		count++;
	}
	auto end = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsed_seconds = end - start;
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);
	result_file << "=======================Checking program files in " << dir_pure_name << "=====================\n";
	// total passed tasks
	result_file << "TOTAL PASSED TASKS：" << dir_tasks_passed.size() << std::endl;
	// list all passed tasks
	result_file << "PASSED TASKS：" << std::endl;
	for (size_t i = 0; i < dir_tasks_passed.size(); i++)
	{
		result_file << dir_tasks_passed[i] << std::endl;
	}
	result_file << utilities::divider << std::endl;
	// total failed tasks
	result_file << "TOTAL FAILED TASKS：" << dir_tasks_failed.size() << std::endl;
	// list all failed tasks
	result_file << "FAILED TASKS：" << std::endl;
	for (size_t i = 0; i < dir_tasks_failed.size(); i++)
	{
		result_file << dir_tasks_failed[i] << std::endl;
	}
	result_file << utilities::divider << std::endl;
	// total time
	result_file << "TOTAL TIME：" << elapsed_seconds.count() << " s" << std::endl;
	// end time
	result_file << "END TIME：" << std::ctime(&end_time);
	result_file.close();
	if (print_option)
	{
		LOG_SUCCESS("\n                      ===============================");
		LOG_SUCCESS("<<<<<<<<<<<<<<<<<<<<<| Finish checking the directory |<<<<<<<<<<<<<<<<<<<<<");
		LOG_SUCCESS("                      ===============================\n");
	}
	else
	{
		LOG_SUCCESS("<<<<<<<<<<<<<<<<<<<<<| Finish checking the directory |<<<<<<<<<<<<<<<<<<<<<");
	}
}
int UnixTaskbook::execute_run(const std::string pre_task_name)
{
	int status = 0;

	srand(time(nullptr));

	parse_task_name(pre_task_name);

	load_task_lib();

	print_task_info(task_num, language_option);
	/*
		if (program.size() == 0)
		{
			LOG_ERROR("Need to be checked program name or directory");
		}
	*/
	compile_program(task_program_path);

	for (int i = 0; i < tasklib->total_test_count; i++)
	{
		if (print_option)
		{
			LOG_PROCESS("\n                             ----------------");
			LOG_PROCESS(">>>>>>>>>>>>>>>>>>>>>>>>>>>>| Running test %d |>>>>>>>>>>>>>>>>>>>>>>>>>>>>", i + 1);
			LOG_PROCESS("                             ----------------\n");
		}
		else
		{
			LOG_PROCESS(">>>>>>>>>>>>>>>>>>>>>>>>>>>>| Running test %d |>>>>>>>>>>>>>>>>>>>>>>>>>>>>", i + 1);
		}

		create_test();
		execute_program();
		status = check_program_result(i, print_option);
		if (status != 0)
		{
			return status;
		}

		// remove test files and control file
		system("rm *.tst");
	}
	if (print_option)
	{
		LOG_SUCCESS("\n                     ===============================");
		LOG_SUCCESS("====================| Testing successfully finished |======================");
		LOG_SUCCESS("                     ===============================\n");
	}
	else
	{
		LOG_SUCCESS("====================| Testing successfully finished |======================");
	}

	std::string utb_service;
	if (getenv("UTB_SERVICE") != NULL)
	{
		utb_service = std::string(getenv("UTB_SERVICE"));
	}
	if (utb_service.size() != 0)
	{

		transform(utb_service.begin(), utb_service.end(), utb_service.begin(), ::tolower);
		if (utb_service == "true")
		{
			upload_program(task_program_path);
		}
	}
	return status;
}
void UnixTaskbook::run()
{
	if (check_dir.size() > 0)
	{
		check_program_dir(check_dir);
	}
	else
	{
		execute_run(task_name);
	}
}