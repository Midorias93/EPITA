/**
 ** \file ast/field-var.hh
 ** \brief Declaration of ast::FieldVar.
 */

#pragma once

#include <ast/var.hh>
#include <misc/symbol.hh>

namespace ast
{
  /// FieldVar.
  class FieldVar : public Var
  {
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a FieldVar node.
    FieldVar(const Location& location, Var* var, misc::symbol name);
    FieldVar(const FieldVar&) = delete;
    FieldVar& operator=(const FieldVar&) = delete;
    /// Destroy a FieldVar node.
    ~FieldVar() override;
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
    /// Return the record that holds the field.
    const Var& var_get() const;
    /// Return the record that holds the field.
    Var& var_get();
    /// Return the field's name.
    misc::symbol name_get() const;
    /// Set the field's name.
    void name_set(misc::symbol);
    /// Return handle the number of the field in the record that holds it.
    int index_get() const;
    /// Set handle the number of the field in the record that holds it.
    void index_set(int);
    /** \} */

  protected:
    /// The record that holds the field.
    Var* var_;
    /// The field's name.
    misc::symbol name_;
    /// Handle the number of the field in the record that holds it.
    int index_ = -1;
  };
} // namespace ast
#include <ast/field-var.hxx>
