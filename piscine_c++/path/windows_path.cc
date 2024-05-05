#include "windows_path.hh"

#include <string>

class Path;

WindowsPath::WindowsPath(char dirve)
    : drive_(dirve)
{}

Path& WindowsPath::join(const std::string& tail, bool is_file)
{
    bool has = true;
    for (char car : tail)
        if (car == ':' || car == '\"' || car == '|' || car == '?' || car == '*')
            has = false;
    if (!this->final_ && has)
    {
        this->path_.push_back(tail);
        this->final_ = is_file;
    }
    return *this;
}

std::string WindowsPath::to_string() const
{
    std::string s(1, this->drive_);

    std::string path = s + ":\\";
    for (size_t i = 1; i < this->path_.size(); i++)
    {
        path += this->path_[i - 1] + "\\";
    }
    if (this->path_.size() != 0)
    {
        path += this->path_[this->path_.size() - 1];
        if (!this->final_)
            path += "\\";
    }
    return path;
}
