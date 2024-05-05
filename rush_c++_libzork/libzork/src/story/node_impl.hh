#pragma once

#include <libzork/story/node.hh>

#include "choice.hh"

namespace libzork::story
{

    class NodeImpl : public Node
    {
    public:
        NodeImpl(std::string name, std::string script_path);
        ~NodeImpl() override = default;

        const std::string& get_name() const override;
        const std::string& get_text() const override;

        const Node* make_choice(std::size_t index) const override;
        std::vector<std::string>
        list_choices(bool check_conditions = true) const override;
        std::vector<std::string> list_name() const;
        void add_choice(
            const Node* other, const std::string& text,
            std::vector<std::unique_ptr<vars::Condition>> conditions = {},
            std::vector<std::unique_ptr<vars::Action>> operations = {})
            override;

    private:
        std::string name_;
        std::string text_;
        std::vector<Choice> choices_;
    };

} // namespace libzork::story
