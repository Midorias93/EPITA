/**
 ** \file ast/if-exp.hh
 ** \brief Declaration of ast::IfExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/seq-exp.hh>

namespace ast
{
  /// IfExp.
  class IfExp : public Exp
  {
  public:
    IfExp(const Location& location, Exp* test, Exp* thenclause)
      : Exp(location)
      , test_(test)
      , thenclause_(thenclause)
      , elseclause_(new SeqExp(location, new exps_type()))
    {}

  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct an IfExp node.
    IfExp(const Location& location,
          Exp* test,
          Exp* thenclause,
          Exp* elseclause);
    IfExp(const IfExp&) = delete;
    IfExp& operator=(const IfExp&) = delete;
    /// Destroy an IfExp node.
    ~IfExp() override;
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
    /// Return condition.
    const Exp& test_get() const;
    /// Return condition.
    Exp& test_get();
    /// Return instructions executed if condition is true.
    const Exp& thenclause_get() const;
    /// Return instructions executed if condition is true.
    Exp& thenclause_get();
    /// Return instructions executed if condition is false.
    const Exp& elseclause_get() const;
    /// Return instructions executed if condition is false.
    Exp& elseclause_get();
    /** \} */

  protected:
    /// Condition.
    Exp* test_;
    /// Instructions executed if condition is true.
    Exp* thenclause_;
    /// Instructions executed if condition is false.
    Exp* elseclause_;
  };
} // namespace ast
#include <ast/if-exp.hxx>
