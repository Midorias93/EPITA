/**
 ** \file parse/metavar-map.hxx
 ** \brief Implementation of parse::MetavarMap.
 */

#pragma once

#include <sstream>
#include <string>

#include <misc/contract.hh>
#include <misc/indent.hh>
#include <parse/metavar-map.hh>

namespace parse
{
  template <typename Data>
  MetavarMap<Data>::MetavarMap(const std::string& name)
    : name_(name)
    , map_()
  {}

  template <typename Data> MetavarMap<Data>::~MetavarMap()
  {
    // At this point, every metavariable should have been taken from the map.
    assertion(map_.empty()) << *this << "not empty, aborting.\n";
  }

  template <typename Data>
  std::string MetavarMap<Data>::show(unsigned key) const
  {
    return '_' + name_ + '(' + std::to_string(key) + ')';
  }

  template <typename Data>
  std::ostream& MetavarMap<Data>::dump(std::ostream& ostr) const
  {
    ostr << "MetavarMap<" << name_ << "> = [";

    if (map_.empty())
      return ostr << " ]" << misc::iendl;

    ostr << misc::incindent;

    for (const auto& [k, v] : map_)
      ostr << misc::iendl << show(k) << " -> " << v;

    return ostr << misc::decendl << "]" << misc::iendl;
  }

  template <typename Data>
  std::string MetavarMap<Data>::append_(unsigned& count, Data* data)
  {
    map_[count] = data;
    return show(count++);
  }

  template <typename Data> Data* MetavarMap<Data>::take_(unsigned key)
  {
    return map_.take(key);
  }

  template <typename Data>
  std::ostream& operator<<(std::ostream& ostr, const MetavarMap<Data>& m)
  {
    return m.dump(ostr);
  }

} // namespace parse
