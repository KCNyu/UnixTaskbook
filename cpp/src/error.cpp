#include "error.hpp"

void dlopen_error_handle(void* handle, const char* message)
{
	if(!handle)
	{
		LOG_ERROR("%s%s",message,dlerror());
	}
}
void dlsym_error_handle(const char* error_message, const char* message)
{
	if(error_message)
	{
		LOG_ERROR("%s%s",message,error_message);
	}
}