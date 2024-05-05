#include "vars/action_impl.hh"

#include <algorithm>
#include <map>

#include "exceptions.hh"

namespace libzork::vars
{

    void ActionImpl::apply() const
    {
        throw NotImplemented();
    }

} // namespace libzork::vars
