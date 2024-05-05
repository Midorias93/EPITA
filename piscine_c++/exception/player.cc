#include "player.hh"

#include "invalid_argument.hh"

Player::Player(const std::string& name, unsigned int age, int guess)
    : name_(name)
    , age_(age)
    , guess_(guess)
{
    // FIXME
    if (name == "")
    {
        throw InvalidArgumentException("Name can't be empty.");
    }
    if (age > 150)
    {
        throw InvalidArgumentException("Sorry gramp, too old to play.");
    }
}

int Player::get_guess() const
{
    return guess_;
}

std::ostream& operator<<(std::ostream& os, const Player& p)
{
    return os << p.name_ << '(' << p.age_ << ')';
}
