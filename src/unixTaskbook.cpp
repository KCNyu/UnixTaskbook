#include "unixTaskbook.hpp"

UnixTaskbook::UnixTaskbook(int argc, char *argv[])
{
	// parse
	parse_command(argc, argv);
	parse_task_name();

	// load the task library
	handle = dlopen(tasklib_name.c_str(), RTLD_LAZY);
	dlopen_error_handle(handle, "Cannot load library: ");

	// load the create symbols
	create_t *create_tasklib = (create_t *)dlsym(handle, "create");
	dlsym_error_handle(dlerror(), "Cannot load symbol create: ");

	// create an instance of the class
	tasklib = create_tasklib();

	// check validity
	check_task_lib();
}
UnixTaskbook::~UnixTaskbook()
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
	assert(tasklib->library_name == tasklib_name);

	// check complier
	assert(std::find(supported_complier.begin(), supported_complier.end(), tasklib->complier) != supported_complier.end());
}
void UnixTaskbook::print_task_info(int task_num, std::string language_option)
{
	if (task_num > tasklib->get_task_count() || task_num <= 0)
	{
		LOG_ERROR("Exceeds the number of tasks!\nThe maximum number of %s is %d", tasklib_name.substr(0, tasklib->library_name.size() - 3).c_str(), tasklib->get_task_count());
	}

	std::cout << "============================================" << std::endl;
	std::cout << BLUE << "TASK INFO:" << RESET << std::endl;

	if (language_option.size() == 0)
	{
		language_option = "ru";
	}
	transform(language_option.begin(), language_option.end(), language_option.begin(), ::tolower);

	if (language_option == "ru" || language_option == "russian")
	{
		std::cout << tasklib->get_task_info(task_num, 0) << std::endl;
	}
	else if (language_option == "ch" || language_option == "chinese")
	{
		std::cout << tasklib->get_task_info(task_num, 1) << std::endl;
	}

	std::cout << "============================================" << std::endl;
}

void UnixTaskbook::parse_task_name()
{
	if (task_name.size() == 0)
	{
		LOG_ERROR("Input the taskname");
	}
	std::string numerics("0123456789");
	std::string::size_type pos = task_name.find_first_of(numerics);

	tasklib_name = std::string("libtask") + task_name.substr(0, pos) + ".so";

	task_num = atoi(task_name.substr(pos).c_str());
}
void UnixTaskbook::parse_command(int argc, char *argv[])
{
	command_parser.add<std::string>("taskname", 't', "display the taskInfo", false, "");
	command_parser.add<std::string>("language", 'l', "language be displayed <support [ru] [ch]>", false, "ru");
	command_parser.add<std::string>("program", 'p', "check single program", false, "");
	command_parser.add<std::string>("directory", 'd', "check all programs in the directory", false, "");
	command_parser.add("help", 'h', "display this help and exit");

	command_parser.footer("Development of a system for automatic verification of educational tasks in Linux.\nMandatory arguments to long options are mandatory for short options too.");

	if (argc == 1)
	{
		std::cerr << command_parser.usage();
		exit(EXIT_FAILURE);;
	}

	command_parser.parse_check(argc, argv);
	task_name = command_parser.get<std::string>("taskname");
	language_option = command_parser.get<std::string>("language");
	program = command_parser.get<std::string>("program");
}
void UnixTaskbook::parse_complie_argv(char **&complie_argv)
{
	size_t complie_argc = tasklib->complie_argv.size();

	complie_argv = new char *[complie_argc + 2];

	for (size_t i = 0; i < complie_argc; i++)
	{
		complie_argv[i] = new char[100];
		if (tasklib->complie_argv[i].size() == 0)
		{
			strcpy(complie_argv[i], program.c_str());
			continue;
		}
		strcpy(complie_argv[i], tasklib->complie_argv[i].c_str());
	}

	complie_argv[complie_argc] = new char[100];
	strcpy(complie_argv[complie_argc], complie_out.c_str());

	complie_argv[complie_argc + 1] = NULL;
}
void UnixTaskbook::complie_program(std::string program)
{
	if (!utilities::exists_file(program))
	{
		LOG_ERROR("Error: Checked program %s not found\n", program.c_str());
	}

	// return if the program is already compiled
	if (program.find(".out") != std::string::npos)
	{
		complie_out = program;
		return;
	}

	complie_log = std::string(program.substr(0, strrchr(program.c_str(), '.') - program.c_str()));
	complie_out = complie_log;
	complie_log += "." + tasklib->complier + "log";
	complie_out += ".out";

	int file_log = open(complie_log.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (!file_log)
	{
		LOG_ERROR("Error during creation log-file: ");
	}

	std::cout << BLUE << "-1-Compilation..." << RESET << std::endl;
	unlink(complie_out.c_str());

	pid_t pid = fork();
	if (pid == 0)
	{
		dup2(file_log, STDERR_FILENO);
		close(file_log);

		char **complie_argv;
		parse_complie_argv(complie_argv);

		execvp(tasklib->complier.c_str(), complie_argv);
		LOG_ERROR("Error when running %s: ", tasklib->complier.c_str());
	}
	close(file_log);

	int status;
	pid = waitpid(pid, &status, 0);
	if (pid < 0)
	{
		LOG_ERROR("Error during compilation: ");
	}

	if (!utilities::exists_file(complie_out))
	{
		LOG_INFO("Error: Compiler outputs some error messages (see file %s):", complie_log.c_str());
		utilities::show_file(complie_log, "", 0);
		exit(EXIT_FAILURE);
	}

	struct stat statbuf;
	stat(complie_log.c_str(), &statbuf);
	if (statbuf.st_size > 0)
	{
		LOG_WARN("Compiler outputs some warnings (see file %s):", complie_log.c_str());
		utilities::show_file(complie_log, "", 0);
		LOG_WARN("Compilation is partially successful.");
	}
	else
	{
		unlink(complie_log.c_str());
		LOG_SUCCESS("Compilation is successful.");
	}
}
void UnixTaskbook::create_test(std::string program)
{
	tasklib->generate_task_test(task_num);
	tasklib->generate_task_control(task_num);
}
void UnixTaskbook::parse_execute_argv(char **&execute_argv)
{
	size_t execute_argc = tasklib->get_execute_argv().size();
	execute_argv = new char *[execute_argc + 2];

	execute_argv[0] = new char[100];
	strcpy(execute_argv[0], complie_out.c_str());

	for (size_t i = 1; i < execute_argc + 1; i++)
	{
		execute_argv[i] = new char[100];
		strcpy(execute_argv[i], tasklib->execute_argv[i - 1].c_str());
	}
	execute_argv[execute_argc + 1] = NULL;
}
void UnixTaskbook::execute_program(std::string program)
{
	std::cout << "Program output:\n"
			  << "-------------------------------------------" << std::endl;

	pid_t pid = fork();
	if (pid == 0)
	{
		char **execute_argv;
		parse_execute_argv(execute_argv);
#if 0
		for (size_t i = 0; i < tasklib->execute_argv.size() + 1; i++)
		{
			std::cout << execute_argv[i] << " ";
		}
		std::cout << std::endl;
#endif
		dup2(tasklib->output, STDOUT_FILENO);
		execvp(complie_out.c_str(), execute_argv);
		LOG_ERROR("Error when running program %s", complie_out.c_str());
	}
	int status;
	pid = waitpid(pid, &status, 0);

	std::cout << "\n-------------------------------------------" << std::endl;
	if (pid < 0)
	{
		LOG_ERROR("Error during running: %s", complie_out.c_str());
	}
}
void UnixTaskbook::check_program_result(std::string program)
{
	LOG_PROCESS("Checking results...");

	switch (tasklib->check_program(task_num))
	{
	case 0:
		LOG_SUCCESS("Correct results.");
		break;
	default:
		LOG_INFO("Wrong result");
		utilities::show_file(tasklib->control_file, "Correct results must be as follows:", 1);
		exit(EXIT_FAILURE);
	}
}
void UnixTaskbook::upload_program(std::string program)
{
	LOG_PROCESS("Uploading program...");

	initService();
	sendFile(program.c_str());

}
void UnixTaskbook::run()
{
	srand(time(nullptr));

	print_task_info(task_num, language_option);

	if (program.size() == 0)
	{
		LOG_ERROR("Need to be checked program name or directory");
	}

	complie_program(program);

	for (int i = 0; i < tasklib->total_test_count; i++)
	{
		create_test(program);
		tasklib->print_extral_info(task_num);
		execute_program(program);
		check_program_result(program);

		// remove test files and control file
		system("rm *.tst");
	}

	LOG_SUCCESS("Testing successfully finished.");

	upload_program(program);
}