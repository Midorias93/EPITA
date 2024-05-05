#include "unix_path.hh"

std::string UnixPath::to_string() const
{
    std::string path = "/";
    for (size_t i = 1; i < this->path_.size(); i++)
    {
        path += this->path_[i - 1] + "/";
    }
    if (this->path_.size() != 0)
    {
        path += this->path_[this->path_.size() - 1];
        if (!this->final_)
            path += "/";
    }
    return path;
}
