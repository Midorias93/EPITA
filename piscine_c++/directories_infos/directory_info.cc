#include "directory_info.hh"

DirectoryInfo::DirectoryInfo(const std::string& name, size_t size,
                             uint16_t rights, const std::string& owner)
    : name_(name)
    , size_(size)
    , rights_(rights)
    , owner_(owner)
{
    this->is_valid_ = true;
}

const std::string& DirectoryInfo::get_name() const
{
    return this->name_;
}
const std::string& DirectoryInfo::get_owner() const
{
    return this->owner_;
}

size_t DirectoryInfo::get_size() const
{
    return size_;
}

uint16_t DirectoryInfo::get_rights() const
{
    return this->rights_;
}

bool DirectoryInfo::is_valid() const
{
    return is_valid_;
}
