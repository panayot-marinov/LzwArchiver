#ifndef PATH_UTILS_HPP
#define PATH_UTILS_HPP

#include <string>
using std::string;

class PathUtils
{
public:
    static string extractFileName(const string &path);
    static string extractDirectoryName(const string &path);
    static string leftTrim(const string& path);
};

#endif