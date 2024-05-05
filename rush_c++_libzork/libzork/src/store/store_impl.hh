#pragma once

#include <libzork/store/store.hh>

namespace libzork::store
{

    class StoreImpl : public Store
    {
    public:
        StoreImpl();
        ~StoreImpl() override = default;

        const story::Node* get_active_node() const override;
        void set_active_node(const story::Node* node) override;

        bool has_variable(const std::string& name) const override;
        int get_variable(const std::string& name) const override;
        void set_variable(const std::string& name, int value) override;

    private:
        const story::Node* node_ = nullptr;
    };

} // namespace libzork::store
