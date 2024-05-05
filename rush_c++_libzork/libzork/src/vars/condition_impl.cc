#include "vars/condition_impl.hh"

#include <algorithm>
#include <map>

#include "exceptions.hh"

namespace libzork::vars
{

    bool ConditionImpl::apply() const
    {
        throw NotImplemented();
    }

} // namespace libzork::vars
