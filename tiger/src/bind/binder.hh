/**
 ** \file bind/binder.hh
 ** \brief Declaration of bind::Binder.
 **/

#pragma once

#include <unordered_map>

#include <ast/default-visitor.hh>
#include <ast/object-visitor.hh>

#include <misc/error.hh>
#include <misc/fwd.hh>

namespace bind
{
  /** \brief Binding identifier uses to their definitions.
   **
   ** When the \c Binder finds a declaration (of a variable/formal, function,
   ** or type), it keeps a pointer to it.  When it finds a use, it binds it
   ** to its definition, i.e., it annotates it with a pointer to the
   ** declaration.
   **
   ** The \c Binder diagnoses identifier use errors (invalid multiple
   ** definitions, unbound identifiers etc.).
   **
   ** Since identifier bindings depend on scopes, it needs an environment.
   **
   ** In the original Tiger by A. Appel, there are two namespaces: on
   ** the one hand types, and on the other hand functions and variables.
   ** Here, at EPITA, we will use three name spaces: we will allow
   ** variables and functions with the same name.
   **
   ** Moreover, object constructs make use of two additional name
   ** spaces: one for class attributes and one for methods (actually
   ** these two name spaces only live within the scope of a class).
   **
   ** Note that this Binder is mainly doing nothing: it is just
   ** interested in declarations and uses.  To avoid writing
   ** all the methods that `do nothing but walk', it derives
   ** from \c ast::DefaultVisitor.
   **/
  class Binder
    : public ast::DefaultVisitor
    , public ast::ObjectVisitor
  {
  public:
    /// Super class type.
    using super_type = ast::DefaultVisitor;
    /// Import all the overloaded \c operator() methods.
    using super_type::operator();

    /// The error handler.
    const misc::error& error_get() const;

    /* The visiting methods. */
    // DONE: Some code was deleted here.

    void operator()(ast::LetExp& e) override;
    void operator()(ast::VarDec& e) override;
    void operator()(ast::FunctionDec& e) override;
    void operator()(ast::TypeDec& e) override;
    void operator()(ast::SimpleVar& e) override;
    void operator()(ast::CallExp& e) override;
    void operator()(ast::BreakExp& e) override;
    void operator()(ast::NameTy& e) override;
    void operator()(ast::VarChunk& e) override;
    void operator()(ast::FunctionChunk& e) override;
    void operator()(ast::TypeChunk& e) override;

    // DONE don't know si faut l'override void operator()(consst ast::FunctionChunk&  e) override;


    // DONE: je sais pas si il faut faire un truc pour les types

    // ---------------- //
    // Visiting /Dec/.  //
    // ---------------- //

    /// \name Type and Function declarations
    /// \{

    /// When traversing a function (or a type) we both have to bind
    /// its body (i.e., we need to enter a new scope and push the
    /// arguments in it), *and* we have to store the function's
    /// declaration in the current scope (so that other functions can
    /// call it).

    /// We first introduce the function's name in the outer
    /// environment so that the function can call itself recursively.
    /// In the mean time, we also check for uniqueness.  Then, as a
    /// second step, we process the contents of all the functions
    /// belonging to the current chunk.

    // DONE: Some code was deleted here.
    /// \}

  protected:
    /// Binding errors handler.
    misc::error error_;

    // DONE: Some code was deleted here (More members).
  };

} // namespace bind

#include <bind/binder.hxx>
