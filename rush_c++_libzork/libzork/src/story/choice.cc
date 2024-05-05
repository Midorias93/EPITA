#include "choice.hh"

namespace libzork::story
{

    Choice::Choice(const Node* node, const std::string text)
        : node_(node)
        , text_(text)
    {}
    const Node* Choice::get_node() const
    {
        return this->node_;
    }

    const std::string Choice::get_text() const
    {
        return this->text_;
    }
} // namespace libzork::story
