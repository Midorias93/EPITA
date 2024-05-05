#include "int_container.hh"

#include <iostream>
#include <memory>

MyIntContainer::MyIntContainer(size_t size)
{
    this->current_size_ = 0;
    this->max_size_ = size;
    this->elems_ = std::make_unique<int[]>(size);
}

void MyIntContainer::print() const
{
    for (size_t i = 0; i < this->current_size_ - 1; i++)
    {
        std::cout << this->elems_[i] << " | ";
    }
    std::cout << this->elems_[this->current_size_ - 1] << "\n";
}

size_t MyIntContainer::get_len() const
{
    return this->current_size_;
}

bool MyIntContainer::add(int elem)
{
    if (this->current_size_ >= this->max_size_)
        return false;
    this->elems_[current_size_++] = elem;
    return true;
}

std::optional<int> MyIntContainer::pop()
{
    if (this->current_size_ == 0)
        return std::nullopt;
    int value = this->elems_[--this->current_size_];
    return value;
}

std::optional<int> MyIntContainer::get(size_t position) const
{
    if (position >= this->current_size_)
        return std::nullopt;
    return this->elems_[position];
}

std::optional<size_t> MyIntContainer::find(int elem) const
{
    size_t i = 0;
    while (i < this->current_size_ && this->elems_[i] != elem)
    {
        i++;
    }
    if (this->elems_[i] == elem)
        return i;
    else
        return std::nullopt;
}

void MyIntContainer::sort()
{
    size_t i;
    int key;
    int j;
    for (i = 1; i < this->current_size_; i++)
    {
        key = this->elems_[i];
        j = i - 1;
        while (j >= 0 && this->elems_[j] > key)
        {
            this->elems_[j + 1] = this->elems_[j];
            j = j - 1;
        }
        this->elems_[j + 1] = key;
    }
}

bool MyIntContainer::is_sorted() const
{
    if (this->current_size_ == 0)
        return true;
    int min = this->elems_[0];
    size_t i = 1;
    while (this->current_size_ > i && this->elems_[i] >= min)
    {
        min = this->elems_[i];
        i++;
    }
    if (i == this->current_size_)
        return true;
    else
        return false;
}
