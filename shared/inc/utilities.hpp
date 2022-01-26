#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include "color.hpp"

bool file_exists(std::string filename);
void show_file(const char *name, const char *comment, int filetype);
ssize_t read_line(int fd, void *sbuf, size_t sbufsize);

#endif