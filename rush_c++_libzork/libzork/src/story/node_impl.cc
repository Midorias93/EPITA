#include "story/node_impl.hh"

#include <cstddef>
#include <fstream>
#include <libzork/story/node.hh>

#include "exceptions.hh"
#include "story/choice.hh"

namespace libzork::story
{
    NodeImpl::NodeImpl(std::string name, std::string text)
        : name_(name)
        , text_(text)
    {}

    const std::string& NodeImpl::get_name() const
    {
        return this->name_;
    }

    const std::string& NodeImpl::get_text() const
    {
        return this->text_;
    }

    const Node* NodeImpl::make_choice(size_t index) const
    {
        if (index >= this->choices_.size() || this->choices_.size() == 0)
            return nullptr;
        return this->choices_[index].get_node();
    }

    std::vector<std::string> NodeImpl::list_choices(bool check_conditions) const
    {
        (void)check_conditions;
        std::vector<std::string> text_choice;
        for (const Choice& choice : this->choices_)
        {
            text_choice.push_back(choice.get_text());
        }
        return text_choice;
    }
    std::vector<std::string> NodeImpl::list_name() const
    {
        std::vector<std::string> text_choice;
        for (const Choice& choice : this->choices_)
        {
            text_choice.push_back(choice.get_node()->get_name());
        }
        return text_choice;
    }

    void NodeImpl::add_choice(
        const Node* other, const std::string& text,
        std::vector<std::unique_ptr<vars::Condition>> conditions,
        std::vector<std::unique_ptr<vars::Action>> operations)
    {
        this->choices_.push_back(Choice(other, text));
        (void)conditions;
        (void)operations;
    }

} // namespace libzork::story
