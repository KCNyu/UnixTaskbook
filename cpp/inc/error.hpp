#ifndef ERROR_HPP
#define ERROR_HPP

#include <iostream>
#include <dlfcn.h>
#include "color.hpp"

void dlopen_error_handle(void *handle, const char *message);
void dlsym_error_handle(const char *error_message, const char *message);

#endif