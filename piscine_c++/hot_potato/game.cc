#include "game.hh"

#include <iostream>
#include <memory>
#include <stdexcept>

void Game::add_player(const std::string& name, size_t nb_presses)
{
    this->players_.push_back(Player(name, nb_presses));
}

void Game::play(int bomb_ticks)
{
    if (this->players_.size() < 2)
        throw std::runtime_error("pas assez de joueur");
    std::unique_ptr<Bomb> bomb = std::make_unique<Bomb>(bomb_ticks);
    this->players_[0].set_bomb(std::move(bomb));
    int current_palyer = 0;
    int next_player = 1;
    while (1)
    {
        this->players_[current_palyer].press_bomb();
        if (this->players_[current_palyer].is_dead())
        {
            std::cout << this->players_[current_palyer].get_name()
                      << " has exploded.\n";
            return;
        }
        next_player = (current_palyer + 1) % this->players_.size();
        this->players_[current_palyer].pass_bomb(this->players_[next_player]);
        current_palyer = next_player;
    }
}
