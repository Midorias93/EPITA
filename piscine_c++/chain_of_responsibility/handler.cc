#include "handler.hh"

#include <iostream>

Handler::Handler(Handler* next)
    : next_(next)
{}

void Handler::set_successor(Handler* h)
{
    this->next_ = h;
}

void Handler::forward_request(int level)
{
    if (next_ != nullptr)
    {
        next_->handle_request(level);
        return;
    }
    std::cout << "Nobody can handle this request\n";
}
