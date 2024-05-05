#pragma once

#include <libzork/vars/condition.hh>

namespace libzork::vars
{

    class ConditionImpl : public Condition
    {
    public:
        ~ConditionImpl() override = default;

        bool apply() const override;
    };

} // namespace libzork::vars
