#pragma once
#include "path.hh"

class UnixPath : public Path
{
public:
    std::string to_string() const override;
};
