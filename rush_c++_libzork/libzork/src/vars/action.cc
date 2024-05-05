#include <libzork/vars/action.hh>

#include "exceptions.hh"
#include "vars/action_impl.hh"

namespace libzork::vars
{

    std::unique_ptr<Action> make_action(store::Store& store,
                                        const std::string& variable,
                                        const std::string& action, int value)
    {
        (void)store;
        (void)variable;
        (void)action;
        (void)value;
        throw NotImplemented();
    }

} // namespace libzork::vars
