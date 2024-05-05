/**
 ** \file ast/break-exp.hh
 ** \brief Declaration of ast::BreakExp.
 */

#pragma once

#include <ast/exp.hh>

namespace ast
{
  /// BreakExp.
  class BreakExp : public Exp
  {
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a BreakExp node.
    explicit BreakExp(const Location& location);
    BreakExp(const BreakExp&) = delete;
    BreakExp& operator=(const BreakExp&) = delete;
    /// Destroy a BreakExp node.
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
    const Exp* def_get() const;
    Exp* def_get();
    void def_set(Exp*);

    /** \} */

  protected:
    /// The loop it breaks.
    Exp* def_ = nullptr;
  };
} // namespace ast
#include <ast/break-exp.hxx>
