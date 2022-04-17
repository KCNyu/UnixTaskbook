#include "tasklib.hpp"

int TaskLib::get_task_count() const
{
	return task_count;
}
std::vector<std::string> TaskLib::get_execute_argv() const
{
	return execute_argv;
}
std::string TaskLib::get_task_info(int task_num, int language_option) const
{
	switch (language_option)
	{
	case 0:
		return task_text_russian[task_num - 1];
	case 1:
		return task_text_chinese[task_num - 1];
	case 2:
		return task_text_english[task_num - 1];
	default:
		return task_text_russian[task_num - 1];
	}
}