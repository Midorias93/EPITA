#pragma once

#include <iostream>
#include <libzork/story/node.hh>
#include <memory>
#include <vector>

namespace libzork::story
{
    class Choice
    {
    public:
        Choice(const Node* node, const std::string text);
        const Node* get_node() const;
        const std::string get_text() const;

    private:
        const Node* node_;
        const std::string text_;
    };
} // namespace libzork::story
