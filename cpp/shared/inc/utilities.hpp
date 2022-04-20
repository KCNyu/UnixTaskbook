#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>
#include <dirent.h>
#include <cstring>
#include <iomanip>
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
    void get_files_in_dir(std::string dir, std::vector<std::string> &files);
    size_t normalized_output(std::string s, size_t start, size_t length);
    void normalized_output_text(std::string text, size_t row_size);
    //根据utf8字符的首字节,获取utf8字符所占字节数
    uint8_t GetUtf8charByteNum(unsigned char ch);
    static std::string divider = "==========================================================================";
}
#endif