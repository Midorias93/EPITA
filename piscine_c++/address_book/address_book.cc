#include "address_book.hh"

#include <iostream>

bool AddressBook::add(const std::string& full_name, const std::string& email,
                      const std::string& number)
{
    if (full_name == "")
        return false;
    auto contact_detail = ContactDetails::makeDetails(number, email);
    if (!contact_detail.has_value())
        return false;
    this->map.insert({ full_name, contact_detail.value() });
    return true;
}

std::vector<ContactDetails> AddressBook::find(const std::string& full_name)
{
    auto [first, seconde] = this->map.equal_range(full_name);
    std::vector<ContactDetails> vect;
    while (first != seconde)
    {
        vect.push_back(first->second);
        first++;
    }
    return vect;
}

std::size_t AddressBook::count(const std::string& full_name)
{
    return this->find(full_name).size();
}
bool AddressBook::remove(const std::string& full_name, std::size_t index)
{
    auto it = this->map.find(full_name);
    for (size_t i = 0; i < index; i++)
    {
        it++;
    }

    if (it != this->map.end() && it->first == full_name)
    {
        this->map.erase(it);
        return true;
    }
    return false;
}
void AddressBook::remove_all(const std::string& full_name)
{
    auto it = this->map.find(full_name);
    while (it != this->map.end() && it->first == full_name)
    {
        this->map.erase(it);
        it++;
    }
}
std::ostream& operator<<(std::ostream& os, const AddressBook& b)
{
    os << b.map.size() << " contact(s) in the address book.\n";
    for (auto it : b.map)
    {
        os << "- " << it.first << ": " << it.second;
    }
    return os;
}
