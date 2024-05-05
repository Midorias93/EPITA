#include "auction.hh"

Auction::Auction(Person& organizer, NFT nft, uint initial_bid)
    : organizer_(organizer)
{
    if (nft == nullptr)
        throw std::runtime_error("nft empty");
    this->nft_ = std::move(nft);
    this->highest_bid_ = initial_bid;
    this->highest_bidder_ = nullptr;
}

bool Auction::bid(Person& person, uint money)
{
    if (money < this->highest_bid_)
        return false;

    if (!person.remove_money(money))
        return false;

    if (this->highest_bidder_ != nullptr)
        this->highest_bidder_->add_money(this->highest_bid_);
    this->highest_bid_ = money;
    this->highest_bidder_ = &person;
    return true;
}

uint Auction::get_highest_bid() const
{
    return this->highest_bid_;
}

const std::string& Auction::get_nft_name() const
{
    return *this->nft_;
}

Auction::~Auction()
{
    if (this->highest_bidder_ != nullptr)
    {
        this->highest_bidder_->add_nft(std::move(this->nft_));
        this->organizer_.add_money(this->highest_bid_);
    }
    else
        this->organizer_.add_nft(std::move(this->nft_));
}
