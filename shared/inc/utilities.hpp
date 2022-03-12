#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>
#include "color.hpp"
namespace utilities
{
#define MAX_SIZE 65535

    bool exists_file(std::string filename);
    void show_file(const char *name, const char *comment, int filetype);
    void show_file(std::string name, const char *comment, int filetype);
    ssize_t read_line(int fd, void *sbuf, size_t sbufsize);
    int compare_file(const char *name1, const char *name2);
    int compare_file(std::string name1, std::string name2);
    std::string generate_random_name(size_t length);
    void init_random_test_files_name(std::vector<std::string> &test_files, size_t test_file_count);
}
#endif