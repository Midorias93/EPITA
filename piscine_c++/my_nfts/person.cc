#include "person.hh"

Person::Person(const std::string& name, uint money)
    : name_(name)
    , money_(money)
{}

std::vector<std::string> Person::enumerate_nfts() const
{
    std::vector<std::string> vec;
    for (const NFT& nft : this->nfts_)
        vec.push_back(*nft);
    return vec;
}

void Person::add_nft(NFT nft)
{
    this->nfts_.push_back(std::move(nft));
}

NFT Person::remove_nft(const std::string& name)
{
    auto begin = this->nfts_.begin();
    auto end = this->nfts_.end();

    while (begin != end && *begin->get() != name)
    {
        begin++;
    }
    if (begin == end)
        return create_empty_nft();
    std::string erased_name = *begin->get();
    this->nfts_.erase(begin);
    return create_nft(erased_name);
}

void Person::add_money(uint money)
{
    this->money_ += money;
}

bool Person::remove_money(uint money)
{
    if (this->money_ >= money)
    {
        this->money_ -= money;
        return true;
    }
    return false;
}

uint Person::get_money() const
{
    return this->money_;
}

const std::string& Person::get_name() const
{
    return this->name_;
}

std::ostream& operator<<(std::ostream& os, const Person& p)
{
    os << "Name: " << p.get_name() << "\n";
    os << "Money: " << p.get_money() << "\n";
    os << "NFTs:";
    for (size_t i = 0; i < p.enumerate_nfts().size(); i++)
    {
        os << " " << p.enumerate_nfts()[i];
    }
    os << "\n";
    return os;
}
