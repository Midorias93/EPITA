#include "soldier.hh"

#include <iostream>

Soldier::Soldier()
{
    this->health_point = 15;
    this->damage_point = 3;
    this->crie = "No pity for losers!\n";
}

void Soldier::attack(Soldier& s)
{
    s.health_point -= this->damage_point;
}

void Soldier::print_state() const
{
    std::cout << "I have " << this->health_point << " health points.\n";
}

void Soldier::scream() const
{
    std::cout << this->crie;
}
