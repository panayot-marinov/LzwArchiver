#include "PathUtils.hpp"

string PathUtils::extractFileName(const string &path)
{
    std::string::size_type found = path.find_last_of("/\\");
    if (found != std::string::npos)
    {
        return path.substr(found + 1);
    }
    else
    { 
        return path;
    }
}

string PathUtils::extractDirectoryName(const string &path)
{
    //trim
    size_t start = path.find_first_not_of("/\\");
    std::string trimmedPath = (start == std::string::npos) ? "" : path.substr(start);
     
    std::string::size_type found = trimmedPath.find_last_of("/\\");
    if (found != std::string::npos)
    {
        return path.substr(0, found + start);
    }
    else
    { 
        return "/";
    }
}

string PathUtils::leftTrim(const string& path) {
    size_t start = path.find_first_not_of("/\\");
    std::string trimmedPath = (start == std::string::npos) ? "" : path.substr(start);

    return trimmedPath;
}