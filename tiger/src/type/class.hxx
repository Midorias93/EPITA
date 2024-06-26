/**
 ** \file type/class.hxx
 ** \brief Inline methods for type::Class.
 */
#pragma once

#include <iostream>

#include <misc/algorithm.hh>
#include <type/class.hh>

namespace type
{
  inline const Class::attrs_type& Class::attrs_get() const { return attrs_; }

  inline const Attribute* Class::attr_find(misc::symbol key) const
  {
    for (const Class* cur = this; cur; cur = cur->super_get())
      {
        const Attribute* attr = cur->owned_attr_find(key);
        if (attr)
          return attr;
      }
    return nullptr;
  }

  inline const Method* Class::meth_find(misc::symbol key) const
  {
    for (const Class* cur = this; cur; cur = cur->super_get())
      {
        const Method* meth = cur->owned_meth_find(key);
        if (meth)
          return meth;
      }
    return nullptr;
  }

  inline const Attribute* Class::owned_attr_find(misc::symbol key) const
  {
    for (const Attribute& at : attrs_get())
      if (at.name_get() == key)
        return &at;
    return nullptr;
  }

  inline const Method* Class::owned_meth_find(misc::symbol key) const
  {
    for (const Method* m : meths_get())
      if (m->name_get() == key)
        return m;
    return nullptr;
  }

  inline void Class::attr_add(const Attribute& attr)
  {
    attrs_.emplace_back(attr);
  }

  inline void Class::attr_add(const ast::VarDec* def)
  {
    attrs_.emplace_back(def);
  }

  inline const Class::meths_type& Class::meths_get() const { return meths_; }

  inline void Class::meth_add(const Method* meth) { meths_.emplace_back(meth); }

  inline bool Class::has_data() const { return !attrs_.empty(); }

  inline const Class* Class::super_get() const { return super_; }

  inline void Class::super_set(const Class* super) { super_ = super; }

} // namespace type
