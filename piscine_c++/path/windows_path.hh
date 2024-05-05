#pragma once
#include <string>

#include "path.hh"

class WindowsPath : public Path
{
public:
    WindowsPath(char drive);
    std::string to_string() const override;
    Path& join(const std::string& tail, bool is_file = false) override;

private:
    char drive_;
};
