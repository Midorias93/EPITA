/**
 ** \file ast/assign-exp.hh
 ** \brief Declaration of ast::AssignExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/var.hh>

namespace ast
{
  /// AssignExp.
  class AssignExp : public Exp
  {
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct an AssignExp node.
    AssignExp(const Location& location, Var* var, Exp* exp);
    AssignExp(const AssignExp&) = delete;
    AssignExp& operator=(const AssignExp&) = delete;
    /// Destroy an AssignExp node.
    ~AssignExp() override;
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
    /// Return reference to the affected variable.
    const Var& var_get() const;
    /// Return reference to the affected variable.
    Var& var_get();
    /// Return assigned value.
    const Exp& exp_get() const;
    /// Return assigned value.
    Exp& exp_get();
    /** \} */

  protected:
    /// Reference to the affected variable.
    Var* var_;
    /// Assigned value.
    Exp* exp_;
  };
} // namespace ast
#include <ast/assign-exp.hxx>
