#include "tasklib.hpp"

int TaskLib::get_task_count() const
{
	return task_count;
}

std::string TaskLib::get_task_text(int task_num, int language_option) const
{
	switch (language_option)
	{
	case 0:
		return task_text_russian[task_num];
	case 1:
		return task_text_chinese[task_num];
	default:
		return task_text_russian[task_num];
	}
}