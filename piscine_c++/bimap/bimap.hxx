#pragma once
#include "bimap.hh"

template <typename Lhs, typename Rhs>
bool Bimap<Lhs, Rhs>::insert(const Lhs& vl, const Rhs& vr)
{
    if (this->rhs_.contains(vr) || this->lhs_.contains(vl))
        return false;
    this->lhs_.insert({ vl, vr });
    this->rhs_.insert({ vr, vl });
    return true;
}

template <typename Lhs, typename Rhs>
bool Bimap<Lhs, Rhs>::insert(const Rhs& vr, const Lhs& vl)
{
    if (this->lhs_.contains(vl) || this->rhs_.contains(vr))
        return false;
    this->lhs_.insert({ vl, vr });
    this->rhs_.insert({ vr, vl });
    return true;
}

template <typename Lhs, typename Rhs>
std::size_t Bimap<Lhs, Rhs>::erase(const Lhs& vl)
{
    auto begin = this->rhs_.begin();
    auto end = this->rhs_.end();
    while (begin != end)
    {
        if (begin->second == vl)
            begin = this->rhs_.erase(begin);
        else
            ++begin;
    }
    return this->lhs_.erase(vl);
}
template <typename Lhs, typename Rhs>
std::size_t Bimap<Lhs, Rhs>::erase(const Rhs& vr)
{
    auto begin = this->lhs_.begin();
    auto end = this->lhs_.end();
    while (begin != end)
    {
        if (begin->second == vr)
            begin = this->lhs_.erase(begin);
        else
            ++begin;
    }
    return this->rhs_.erase(vr);
}
template <typename Lhs, typename Rhs>
std::size_t Bimap<Lhs, Rhs>::size() const
{
    return this->lhs_.size();
}
template <typename Lhs, typename Rhs>
void Bimap<Lhs, Rhs>::clear()
{
    this->lhs_.clear();
    this->rhs_.clear();
}
template <typename Lhs, typename Rhs>
const typename Bimap<Lhs, Rhs>::mapLhs& Bimap<Lhs, Rhs>::get_lhs() const
{
    return this->lhs_;
}

template <typename Lhs, typename Rhs>
const typename Bimap<Lhs, Rhs>::mapRhs& Bimap<Lhs, Rhs>::get_rhs() const
{
    return this->rhs_;
}
template <typename Lhs, typename Rhs>
typename Bimap<Lhs, Rhs>::iteratorLhs Bimap<Lhs, Rhs>::find(const Lhs& vl) const
{
    return this->lhs_.find(vl);
}
template <typename Lhs, typename Rhs>
typename Bimap<Lhs, Rhs>::iteratorRhs Bimap<Lhs, Rhs>::find(const Rhs& vr) const
{
    return this->rhs_.find(vr);
}
