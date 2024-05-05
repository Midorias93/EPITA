#include "bomb.hh"

#include <iostream>
#include <stdexcept>

Bomb::Bomb(int ticks)
{
    if (ticks <= 0)
        throw std::runtime_error("ticks <= 0\n");
    this->count_ = 0;
    this->max_ticks_ = ticks;
}

void Bomb::tick()
{
    if (this->count_ >= this->max_ticks_)
        throw std::runtime_error("the bomb have already explode\n");
    if (this->count_++ % 2 == 0)
        std::cout << "Tic!\n";
    else
        std::cout << "Tac!\n";
}

bool Bomb::has_exploded() const
{
    return this->count_ >= max_ticks_;
}
