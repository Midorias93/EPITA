#include "store/store_impl.hh"

#include <libzork/story/story.hh>
#include <yaml-cpp/yaml.h>

#include "exceptions.hh"
#include "story/story_impl.hh"

namespace libzork::store
{
    StoreImpl::StoreImpl(){};

    const story::Node* StoreImpl::get_active_node() const
    {
        return this->node_;
    }

    void StoreImpl::set_active_node(const story::Node* node)
    {
        this->node_ = node;
    }

    bool StoreImpl::has_variable(const std::string& name) const
    {
        (void)name;
        throw NotImplemented();
    }

    int StoreImpl::get_variable(const std::string& name) const
    {
        (void)name;
        throw NotImplemented();
    }

    void StoreImpl::set_variable(const std::string& name, int value)
    {
        (void)name;
        (void)value;
        throw NotImplemented();
    }

} // namespace libzork::store
