#pragma once

#include <string>

class Person
{
public:
    // FIXME
    Person(const std::string& name, unsigned int age);
    std::string get_name() const;
    unsigned int get_age() const;
    void set_name(const std::string& new_name);
    void set_age(const unsigned int new_age);

private:
    std::string name_;
    unsigned int age_;
};
