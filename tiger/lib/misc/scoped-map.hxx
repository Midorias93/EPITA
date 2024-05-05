/** \file misc/scoped-map.hxx
 ** \brief Implementation of misc::scoped_map.
 */

#pragma once

#include <sstream>
#include <stdexcept>
#include <type_traits>

#include <ranges>
#include <misc/algorithm.hh>
#include <misc/contract.hh>
#include <misc/indent.hh>

namespace misc
{
  // TODO: Some code was deleted here.
    template <typename Key, typename Data>
    scoped_map<Key, Data>::scoped_map() {
        maps_.push_back(std::map<Key, Data>(cur_));
        cur_.clear();
    }

    template <typename Key, typename Data>
    void scoped_map<Key, Data>::put(const Key& key, const Data& value)
    {
        cur_[key] = value;
    }

    template <typename Key, typename Data>
    Data scoped_map<Key, Data>::get(const Key& key) const
    requires(isPointer<Data>)
    {
        std::map<Key, Data> tmp = cur_;
        if (cur_.find(key) != cur_.end())
            return cur_.find(key)->second;
        for (size_t i = maps_.size() - 1; i > 0; i--)
        {
            std::map<Key, Data> tmp = maps_[i];
            if (tmp.find(key) != tmp.end())
                return tmp.find(key)->second;
        }
        return nullptr;
    }

    template <typename Key, typename Data>
    Data scoped_map<Key, Data>::get(const Key& key) const
    requires (!isPointer<Data>)
    {
        std::map<Key, Data> tmp = cur_;
        if (cur_.find(key) != cur_.end())
            return cur_.find(key)->second;
        for (size_t i = maps_.size() - 1; i > 0; i--)
        {
            std::map<Key, Data> tmp = maps_[i];
            if (tmp.find(key) != tmp.end())
                return tmp.find(key)->second;
        }
        throw std::range_error("damn pas trouve la key la\n");;
    }

    template <typename Key, typename Data>
    Data scoped_map<Key, Data>::get_current(const Key& key) const
    requires(isPointer<Data>)
    {
        std::map<Key, Data> tmp = cur_;
        if (cur_.find(key) != cur_.end())
            return cur_.find(key)->second;
        return nullptr;
    }

    template <typename Key, typename Data>
    Data scoped_map<Key, Data>::get_current(const Key& key) const
    requires (!isPointer<Data>)
    {
        std::map<Key, Data> tmp = cur_;
        if (cur_.find(key) != cur_.end())
            return cur_.find(key)->second;
        throw std::range_error("damn pas trouve la key la\n");;
    }

    template <typename Key, typename Data>
    Data scoped_map<Key, Data>::get_hosts(const Key& key) const
    requires(isPointer<Data>)
    {
        for (size_t i = maps_.size() - 1; i > 0; i--)
        {
            std::map<Key, Data> tmp = maps_[i];
            if (tmp.find(key) != tmp.end())
                return tmp.find(key)->second;
        }
        return nullptr;
    }

    template <typename Key, typename Data>
    Data scoped_map<Key, Data>::get_hosts(const Key& key) const
    requires (!isPointer<Data>)
    {
        for (size_t i = maps_.size() - 1; i > 0; i--)
        {
            std::map<Key, Data> tmp = maps_[i];
            if (tmp.find(key) != tmp.end())
                return tmp.find(key)->second;
        }
        throw std::range_error("damn pas trouve la key la\n");;
    }

    template <typename Key, typename Data>
    void scoped_map<Key, Data>::scope_begin()
    {
        maps_.push_back(std::map<Key, Data>(cur_));
        cur_.clear();
    }

    template <typename Key, typename Data>
    std::ostream& scoped_map<Key, Data>::dump(std::ostream& ostr) const
    {
        size_t indent = 0;
        for (auto i: maps_)
        {
            for (size_t k = 0; k < indent; k++)
                ostr << "   ";
            ostr << "{\n";
            for (auto j: i)
            {
                for (size_t k = 0; k < indent; k++)
                    ostr << "   ";
                ostr << j.first << " = " << j.second << '\n';
            }
            indent++;
        }
        while (indent > 0)
        {
            for (size_t k = 0; k < indent; k++)
                ostr << "   ";
            ostr << "}";
            indent--;
        }

    }

    template <typename Key, typename Data>
    void scoped_map<Key, Data>::scope_end()
    {
        cur_.clear();
        if (maps_.size() > 0)
        {
            cur_ = maps_.at(maps_.size() - 1);
            maps_.pop_back();
        }
    }

  template <typename Key, typename Data>
  inline std::ostream& operator<<(std::ostream& ostr,
                                  const scoped_map<Key, Data>& tbl)
  {
    return tbl.dump(ostr);
  }

} // namespace misc
