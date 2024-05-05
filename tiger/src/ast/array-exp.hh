/**
 ** \file ast/array-exp.hh
 ** \brief Declaration of ast::ArrayExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/name-ty.hh>

namespace ast
{
  /// ArrayExp.
  class ArrayExp : public Exp
  {
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct an ArrayExp node.
    ArrayExp(const Location& location, NameTy* type_name, Exp* size, Exp* init);
    ArrayExp(const ArrayExp&) = delete;
    ArrayExp& operator=(const ArrayExp&) = delete;
    /// Destroy an ArrayExp node.
    ~ArrayExp() override;
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
    /// Return identifier of the stored elements type.
    const NameTy& type_name_get() const;
    /// Return identifier of the stored elements type.
    NameTy& type_name_get();
    /// Return size of the array.
    const Exp& size_get() const;
    /// Return size of the array.
    Exp& size_get();
    /// Return initial value assigned to all elements of the array.
    const Exp& init_get() const;
    /// Return initial value assigned to all elements of the array.
    Exp& init_get();
    /** \} */

  protected:
    /// Identifier of the stored elements type.
    NameTy* type_name_;
    /// Size of the array.
    Exp* size_;
    /// Initial value assigned to all elements of the array.
    Exp* init_;
  };
} // namespace ast
#include <ast/array-exp.hxx>
