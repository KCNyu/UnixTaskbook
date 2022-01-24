#ifndef ERROR_HPP
#define ERROR_HPP

#include <iostream>
#include <dlfcn.h>
#include "color.hpp"
#define LOG_ERROR(format, ...)                  \
	{                                       \
		fprintf(stdout, "%s" format "", \
			RED, ##__VA_ARGS__);    \
		fprintf(stdout, "\n%s", RESET); \
		exit(1);                        \
	}

void dlopen_error_handle(void *handle, const char *message);
void dlsym_error_handle(const char *error_message, const char *message);

#endif