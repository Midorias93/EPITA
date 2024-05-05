#include "provider.hh"

#include <iostream>

#include "nurturer.hh"

void Provider::harvestFood()
{
    std::cout << "Harvested " << this->luck_ << " food.\n";
    this->food_stock_ += this->luck_;
    this->food_level_ -= (this->luck_ - static_cast<int>(this->luck_)) / 2;
}

void Provider::work()
{
    if (this->stage_ == DevelopmentStage::ADULT)
    {
        if (food_stock_ > 0)
        {
            this->food_level_ +=
                this->food_stock_ - static_cast<int>(this->food_stock_);
            this->food_stock_ -=
                this->food_stock_ - static_cast<int>(this->food_stock_);
        }
        this->harvestFood();
        Worker::work();
    }
}

void Provider::transferFood(Nurturer& nurturer)
{
    if (this->food_stock_ >= 1)
    {
        nurturer.increment_food_stock_by(static_cast<int>(this->food_stock_));
        this->food_stock_ -= static_cast<int>(this->food_stock_);
        std::cout << "Transferring food.\n";
    }
}

bool Provider::communicate(std::weak_ptr<Ant> wk_receiver)
{
    if (!Ant::communicate(wk_receiver))
    {
        return false;
    }
    std::cout << "Provider initiates communication.\n";
    if (dynamic_cast<Nurturer*>(wk_receiver.lock().get()) != nullptr)
    {
        this->transferFood(dynamic_cast<Nurturer&>(*wk_receiver.lock()));
    }
    return true;
}
