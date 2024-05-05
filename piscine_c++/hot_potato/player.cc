#include "player.hh"

#include <iostream>

Player::Player(const std::string& name, size_t nb_presses)
    : name_(name)
    , nb_presses_(nb_presses)
{
    this->bomb_ = nullptr;
}

void Player::pass_bomb(Player& receiver)
{
    if (this->bomb_ == nullptr || receiver.bomb_ != nullptr)
        throw std::runtime_error("probleme de bombe\n");
    std::cout << this->get_name() << " passes the bomb to "
              << receiver.get_name() << ".\n";
    receiver.bomb_ = std::move(this->bomb_);
}

void Player::press_bomb()
{
    if (this->bomb_ == nullptr)
        throw std::runtime_error("the player don't have the bomb");
    size_t presse = 0;
    while (!this->bomb_->has_exploded() && presse++ != this->nb_presses_)
    {
        this->bomb_->tick();
    }
}

void Player::set_bomb(std::unique_ptr<Bomb> bomb)
{
    this->bomb_ = std::move(bomb);
}

const std::string& Player::get_name() const
{
    return this->name_;
}

bool Player::has_bomb() const
{
    return this->bomb_ != nullptr;
}

bool Player::is_dead() const
{
    if (this->has_bomb())
    {
        return this->bomb_->has_exploded();
    }
    return false;
}
