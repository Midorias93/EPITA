/**
 ** \file ast/object-exp.hh
 ** \brief Declaration of ast::ObjectExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/name-ty.hh>

namespace ast
{
  /// ObjectExp.
  class ObjectExp : public Exp
  {
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct an ObjectExp node.
    ObjectExp(const Location& location, NameTy* type_name);
    ObjectExp(const ObjectExp&) = delete;
    ObjectExp& operator=(const ObjectExp&) = delete;
    /// Destroy an ObjectExp node.
    /** \} */

    /// \name Visitors entry point.
    /// \{ */
    /// Accept a const visitor \a v.
    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;
    /// \}

    /** \name Accessors.
     ** \{ */
    /// Return name of the class from which the object is instantiated.
    const NameTy& type_name_get() const;
    /// Return name of the class from which the object is instantiated.
    NameTy& type_name_get();
    /** \} */

  protected:
    /// Name of the class from which the object is instantiated.
    NameTy* type_name_;
  };
} // namespace ast
#include <ast/object-exp.hxx>
