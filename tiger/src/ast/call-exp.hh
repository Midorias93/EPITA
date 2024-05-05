/**
 ** \file ast/call-exp.hh
 ** \brief Declaration of ast::CallExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/function-dec.hh>
#include <misc/symbol.hh>

namespace ast
{
  /// CallExp.
  class CallExp : public Exp
  {
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a CallExp node.
    CallExp(const Location& location, misc::symbol name, exps_type* args);
    CallExp(const CallExp&) = delete;
    CallExp& operator=(const CallExp&) = delete;
    /// Destroy a CallExp node.
    ~CallExp() override;
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
    /// Return identifier of the called function.
    misc::symbol name_get() const;
    /// Set identifier of the called function.
    void name_set(misc::symbol);
    /// Return list of arguments passed to the function.
    const exps_type& args_get() const;
    /// Return list of arguments passed to the function.
    exps_type& args_get();

    const FunctionDec* def_get() const;
    FunctionDec* def_get();
    void def_set(FunctionDec*);

  protected:
    /// Identifier of the called function.
    misc::symbol name_;
    /// List of arguments passed to the function.
    exps_type* args_;
    /// Definition site.
    FunctionDec* def_ = nullptr;
  };
} // namespace ast
#include <ast/call-exp.hxx>
