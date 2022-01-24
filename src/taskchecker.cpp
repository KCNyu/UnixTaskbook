#include "taskchecker.hpp"

TaskChecker::TaskChecker(int argc, char *argv[])
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
TaskChecker::~TaskChecker()
{
	// load the destroy symbols
	destroy_t *destroy_tasklib = (destroy_t *)dlsym(handle, "destroy");
	dlsym_error_handle(dlerror(), "Cannot load symbol destroy: ");

	// destroy the class
	destroy_tasklib(tasklib);

	// unload the task library
	dlclose(handle);
}
void TaskChecker::check_task_lib()
{
	// check task count
	assert(tasklib->get_task_count() == tasklib->task_text_russian.size());
	assert(tasklib->get_task_count() == tasklib->task_text_chinese.size());

	// check tasklib name
	assert(tasklib->library_name.find("libtask") == 0);
	assert(tasklib->library_name.substr(tasklib->library_name.size() - 3) == ".so");

	// check complier
	assert(std::find(supported_complier.begin(), supported_complier.end(), tasklib->complier) != supported_complier.end());
}
void TaskChecker::print_task_info(int task_num, std::string language_option)
{
	if (task_num >= tasklib->get_task_count())
	{
		std::cout << RED << "Exceeds the number of tasks!" << std::endl;
		std::cout << "The maximum number of " << tasklib_name.substr(0, tasklib->library_name.size() - 3) << " is " << tasklib->get_task_count() << RESET << std::endl;
		exit(1);
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
		std::cout << tasklib->get_task_info(task_num, 0);
	}
	else if (language_option == "ch" || language_option == "chinese")
	{
		std::cout << tasklib->get_task_info(task_num, 1);
	}

	std::cout << "============================================" << std::endl;
}

void TaskChecker::print_default_help()
{
	std::cout << BLUE << "Usage: TaskChecker [OPTION]... [FILE]..." << RESET << std::endl;
	std::cout << "Development of a system for automatic verification of educational tasks in Linux." << std::endl;
	std::cout << "Mandatory arguments to long options are mandatory for short options too." << std::endl;
	std::cout << "-t, --taskname		  display the taskInfo" << std::endl;
	std::cout << "-l, --language		  language be displayed  <default Russian> <support [ru] [ch]>" << std::endl;
	std::cout << "-p, --program		  check single program" << std::endl;
	std::cout << "-d, --directory		  check all programs in the directory" << std::endl;
	std::cout << "-h, --help		  display this help and exit" << std::endl;
}
void TaskChecker::parse_task_name()
{
	if (task_name.size() == 0)
	{
		LOG_ERROR("Input the taskname");
	}
	std::string numerics("0123456789");
	std::string::size_type pos = task_name.find_first_of(numerics);

	tasklib_name = std::string("libtask") + task_name.substr(0, pos) + ".so";

	task_num = atoi(task_name.substr(pos).c_str()) - 1;
}
void TaskChecker::parse_command(int argc, char *argv[])
{
	if (argc == 1)
	{
		print_default_help();
		exit(0);
	}
	bool flag = false;
	for (int i = 1; i < argc; i++)
	{
		if (flag)
		{
			flag = false;
			continue;
		}
		if (VALID_ARG("-t", "--taskname"))
		{
			if (VALID_I(i))
			{
				task_name = argv[i + 1];
				flag = true;
			}
		}
		else if (VALID_ARG("-l", "--language"))
		{
			if (VALID_I(i))
			{
				language_option = argv[i + 1];
				flag = true;
			}
		}
		else if (VALID_ARG("-p", "--program"))
		{
			if (VALID_I(i))
			{
				program = argv[i + 1];
				flag = true;
			}
		}
		else if (VALID_ARG("-d", "--directory"))
		{
		}
		else if (VALID_ARG("-h", "--help"))
		{
			print_default_help();
			exit(0);
		}
		else
		{
			LOG_ERROR("Error: invalid option '%s'", argv[i]);
		}
	}
}
void TaskChecker::parse_complie_argv(char **&complie_argv)
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
void TaskChecker::complie_program(std::string program)
{
	if (!fileexists(program))
	{
		LOG_ERROR("Error: Checked program %s not found\n", program.c_str());
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
		dup2(file_log, 2);
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
	if (!fileexists(complie_out))
	{
		LOG_INFO("Error: Compiler outputs some error messages (see file %s):", complie_log.c_str());
		show_file(complie_log.c_str(), "", 0);
		exit(1);
	}
	struct stat statbuf;
	stat(complie_log.c_str(), &statbuf);
	if (statbuf.st_size > 0)
	{
		LOG_WARN("Compiler outputs some warnings (see file %s):", complie_log.c_str());
		show_file(complie_log.c_str(), "", 0);
		LOG_WARN("Compilation is partially successful.");
	}
	else
	{
		unlink(complie_log.c_str());
		LOG_SUCCESS("Compilation is successful.");
	}
}
void TaskChecker::run()
{
	print_task_info(task_num, language_option);
	if (program.size() != 0)
	{
		complie_program(program);
	}
}