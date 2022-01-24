#include "error.hpp"

void dlopen_error_handle(void* handle, const char* message)
{
	if(!handle)
	{
		std::cerr << RED << message << dlerror() << '\n' << RESET;
		exit(1);
	}
}
void dlsym_error_handle(const char* error_message, const char* message)
{
	if(error_message)
	{
		std::cerr << RED << message << error_message << '\n' << RESET;
		exit(1);
	}
}