#pragma once

#include <libzork/runner/smart.hh>

namespace libzork::runner
{

    class SmartRunnerImpl : public SmartRunner
    {
    public:
        void process_input() override;
        int count_synonyms(const std::string& left,
                           const std::string& right) const override;
    };

} // namespace libzork::runner
