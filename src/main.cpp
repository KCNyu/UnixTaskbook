#include "tasklib.hpp"
#include <iostream>
#include <dlfcn.h>
int main()
{
	using std::cerr;
	using std::cout;
	// load the triangle library
	void * tasklib = dlopen("libtaskB.so", RTLD_LAZY);
	if (!tasklib)
	{
		cerr << "Cannot load library: " << dlerror() << '\n';
		return 1;
	}
	// reset errors
	dlerror();
	// load the symbols
	create_t *create_tasklib = (create_t *)dlsym(tasklib, "create");
	const char *dlsym_error = dlerror();
	if (dlsym_error)
	{
		cerr << "Cannot load symbol create: " << dlsym_error << '\n';
		return 1;
	}
	destroy_t *destroy_tasklib = (destroy_t *)dlsym(tasklib, "destroy");
	dlsym_error = dlerror();
	if (dlsym_error)
	{
		cerr << "Cannot load symbol destroy: " << dlsym_error << '\n';
		return 1;
	}
	// create an instance of the class
	TaskLib *task = create_tasklib();
	// use the class
	cout << task->get_task_text(5,0);
	// destroy the class
	destroy_tasklib(task);
	// unload the triangle library
	dlclose(tasklib);
}