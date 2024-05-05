/**
 ** \file ast/seq-exp.hh
 ** \brief Declaration of ast::SeqExp.
 */

#pragma once

#include <ast/exp.hh>

namespace ast
{
  /// SeqExp.
  class SeqExp : public Exp
  {
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a SeqExp node.
    SeqExp(const Location& location, exps_type* exps);
    SeqExp(const SeqExp&) = delete;
    SeqExp& operator=(const SeqExp&) = delete;
    /// Destroy a SeqExp node.
    ~SeqExp() override;
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
    /// Return list of expressions.
    const exps_type& exps_get() const;
    /// Return list of expressions.
    exps_type& exps_get();
    /** \} */

  protected:
    /// List of expressions.
    exps_type* exps_;
  };
} // namespace ast
#include <ast/seq-exp.hxx>
