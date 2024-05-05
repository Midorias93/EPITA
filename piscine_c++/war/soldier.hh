#pragma once
#include <iostream>

class Soldier
{
public:
    int health_point;
    int damage_point;
    std::string crie;
    Soldier();
    void attack(Soldier& s);
    void print_state() const;
    void scream() const;
};
