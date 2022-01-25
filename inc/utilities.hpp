#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include "header.hpp"

bool fileexists(std::string filename);
void show_file(const char *name, const char *comment, int filetype);
ssize_t read_line(int fd, void *sbuf, size_t sbufsize);

#endif