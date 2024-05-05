#include "node.hh"

Node::Node(int v)
    : val_(v)
{}

int Node::get_val() const
{
    return this->val_;
}

void Node::set_val(int val)
{
    this->val_ = val;
}

std::shared_ptr<Node> Node::get_next() const
{
    return this->next_;
}
void Node::set_next(std::shared_ptr<Node> next)
{
    this->next_ = next;
}

std::shared_ptr<Node> Node::get_prev() const
{
    return this->prev_.lock();
}

void Node::set_prev(std::shared_ptr<Node> prev)
{
    this->prev_ = prev;
}
