#include "tasklib.hpp"

class TaskB : public TaskLib
{
public:
	TaskB();
};

extern "C" TaskLib *create()
{
	return new TaskB;
}
extern "C" void destroy(TaskLib *t)
{
	delete t;
}