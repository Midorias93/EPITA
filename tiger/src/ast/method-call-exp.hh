/**
 ** \file ast/method-call-exp.hh
 ** \brief Declaration of ast::MethodCallExp.
 */

#pragma once

#include <ast/call-exp.hh>
#include <ast/method-dec.hh>
#include <ast/var.hh>

namespace ast
{
  /** \class ast::MethodCallExp
   ** \brief Method call.
   **
   ** A method call is \em not a function call in the strict sense
   ** of object-oriented programming.  Inheritance is used as a
   ** factoring tool here.
   */

  class MethodCallExp : public CallExp
  {
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a MethodCallExp node.
    MethodCallExp(const Location& location,
                  misc::symbol name,
                  exps_type* args,
                  Var* object);
    MethodCallExp(const MethodCallExp&) = delete;
    MethodCallExp& operator=(const MethodCallExp&) = delete;
    /// Destroy a MethodCallExp node.
    ~MethodCallExp() override;
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
    /// Return the object on which the method is called.
    const Var& object_get() const;
    /// Return the object on which the method is called.
    Var& object_get();

    const MethodDec* def_get() const;
    MethodDec* def_get();
    void def_set(MethodDec*);
    /** \} */

  protected:
    /// The object on which the method is called.
    Var* object_;
    /// Definition site.
    MethodDec* def_ = nullptr;
  };
} // namespace ast
#include <ast/method-call-exp.hxx>
