#include <libzork/runner/smart.hh>

#include "exceptions.hh"
#include "runner/smart_impl.hh"

namespace libzork::runner
{

    std::unique_ptr<SmartRunner>
    make_smart_runner(std::unique_ptr<story::Story> story,
                      const fs::path& synonyms_path, std::istream& is,
                      std::ostream& os)
    {
        (void)story;
        (void)synonyms_path;
        (void)is;
        (void)os;
        throw NotImplemented();
    }

} // namespace libzork::runner
