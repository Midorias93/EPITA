/**
 ** \file bind/renamer.hh
 ** \brief Implementation of bind::Renamer.
 */

#pragma once

#include <ast/default-visitor.hh>
#include <ast/non-object-visitor.hh>

namespace bind
{
  /// Perform identifier renaming within an AST (in place),
  /// without support for objects.
  class Renamer
    : public ast::DefaultVisitor
    , public ast::NonObjectVisitor
  {
  public:
    using super_type = ast::DefaultVisitor;

    // Import overloaded virtual functions.
    using super_type::operator();

    void operator()(ast::VarDec& e) override;
    void operator()(ast::FunctionDec& e) override;
    void operator()(ast::TypeDec& e) override;
    void operator()(ast::SimpleVar& e) override;
    void operator()(ast::CallExp& e) override;

    // DONE: Some code was deleted here.

    // Visit methods.
    /// \brief Process a declaration body or a usage site.
    ///
    /// \a def is the definition site of \e (must be equal to
    /// \a e if it is a Dec node).
    template <class E, class Def> void visit(E& e, const Def* def);

    /// \name Visiting definition sites.
    /// \{
    // DONE: Some code was deleted here.
    /// \}

    /// \name Visiting usage sites.
    /// \{
    // DONE: Some code was deleted here.
    /// \}

  private:
    // DONE: Some code was deleted here.
  };

} // namespace bind

#include <bind/renamer.hxx>
