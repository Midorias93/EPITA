#include <libzork/exceptions.hh>
#include <libzork/runner/interactive.hh>

#include "exceptions.hh"

namespace libzork::runner
{

    InteractiveRunner::InteractiveRunner(std::unique_ptr<story::Story> story,
                                         std::istream& is, std::ostream& os)
        : Runner(std::move(story))
        , is_(is)
        , os_(os)
    {}

    void InteractiveRunner::print_script() const
    {
        throw NotImplemented();
    }

    void InteractiveRunner::run()
    {
        throw NotImplemented();
    }

} // namespace libzork::runner
