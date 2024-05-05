#include "president.hh"

#include <iostream>

void President::handle_request(int level)
{
    if (level <= 9)
    {
        std::cout << "President handles\n";
        return;
    }
    this->forward_request(level);
}
