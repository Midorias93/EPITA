#pragma once

#include <source_location>
#include <stdexcept>

namespace libzork
{

    class NotImplemented : public std::runtime_error
    {
    public:
        NotImplemented(const std::source_location location =
                           std::source_location::current());
    };

} // namespace libzork
