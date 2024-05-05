#include "runner/smart_impl.hh"

#include <cassert>
#include <fstream>
#include <functional>
#include <iostream>
#include <libzork/exceptions.hh>
#include <regex>
#include <set>
#include <yaml-cpp/yaml.h>

#include "exceptions.hh"
#include "story/story_impl.hh"

namespace libzork::runner
{

    void SmartRunnerImpl::process_input()
    {
        throw NotImplemented();
    }

    int SmartRunnerImpl::count_synonyms(const std::string& left,
                                        const std::string& right) const
    {
        (void)left;
        (void)right;
        throw NotImplemented();
    }

} // namespace libzork::runner
