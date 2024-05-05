#include "person.hh"

#include <iostream>

Person::Person(const std::string& name, unsigned int age)
    : name_(name)
    , age_(age)
{}

std::string Person::get_name() const
{
    return this->name_;
}

unsigned int Person::get_age() const
{
    return this->age_;
}

void Person::set_name(const std::string& new_name)
{
    this->name_ = new_name;
}

void Person::set_age(const unsigned int new_age)
{
    this->age_ = new_age;
}
