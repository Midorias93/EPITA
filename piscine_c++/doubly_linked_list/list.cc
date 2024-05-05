#include "list.hh"

#include <iostream>
#include <memory>

List::List()
{
    this->nb_elts_ = 0;
    this->first_ = nullptr;
    this->last_ = this->first_;
}

void List::push_front(int i)
{
    std::shared_ptr<Node> new_node = std::make_shared<Node>(i);
    if (this->nb_elts_++ == 0)
    {
        this->first_ = new_node;
        this->last_ = this->first_;
        return;
    }

    new_node->set_next(this->first_);
    this->first_->set_prev(new_node);
    this->first_ = new_node;
}

void List::push_back(int i)
{
    std::shared_ptr<Node> new_node = std::make_shared<Node>(i);
    if (this->nb_elts_++ == 0)
    {
        this->last_ = new_node;
        this->first_ = this->last_;
        return;
    }

    new_node->set_prev(this->last_);
    this->last_->set_next(new_node);
    this->last_ = new_node;
}

std::optional<int> List::pop_front()
{
    if (this->nb_elts_ == 0)
        return std::nullopt;
    int value = this->first_->get_val();
    this->first_ = this->first_->get_next();
    this->nb_elts_--;
    return value;
}

std::optional<int> List::pop_back()
{
    if (this->nb_elts_ == 0)
        return std::nullopt;
    int value = this->last_->get_val();
    this->last_ = this->last_->get_prev();
    this->nb_elts_--;
    return value;
}

void List::print(std::ostream& os) const
{
    if (this->nb_elts_ == 0)
        return;
    std::shared_ptr<Node> save = this->first_;
    for (size_t i = 1; i < this->nb_elts_; i++)
    {
        os << save->get_val() << " ";
        save = save->get_next();
    }
    os << save->get_val();
}

size_t List::length() const
{
    return this->nb_elts_;
}
