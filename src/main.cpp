#include "taskchecker.hpp"
int main(int argc, char *argv[])
{
	TaskChecker taskchecker(argc, argv);
	taskchecker.print_task_info();
}