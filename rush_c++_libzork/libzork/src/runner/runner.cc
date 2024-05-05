#include <libzork/runner/runner.hh>

#include "exceptions.hh"

namespace libzork::runner
{

    Runner::Runner(std::unique_ptr<story::Story> story)
    {
        (void)story;
        throw NotImplemented();
    }

} // namespace libzork::runner
