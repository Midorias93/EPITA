#include "vice_president.hh"

#include <iostream>

void VicePresident::handle_request(int level)
{
    if (level <= 6)
    {
        std::cout << "VicePresident handles\n";
        return;
    }
    this->forward_request(level);
}
