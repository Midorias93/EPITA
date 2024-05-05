/**
 ** \file ast/let-exp.hh
 ** \brief Declaration of ast::LetExp.
 */

#pragma once

#include <ast/chunk-list.hh>
#include <ast/exp.hh>
#include <misc/contract.hh>

namespace ast
{
  /// LetExp.
  class LetExp : public Exp
  {
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a LetExp node.
    LetExp(const Location& location, ChunkList* chunks, Exp* body);
    LetExp(const LetExp&) = delete;
    LetExp& operator=(const LetExp&) = delete;
    /// Destroy a LetExp node.
    ~LetExp() override;
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
    /// Return list of declarations.
    const ChunkList& chunks_get() const;
    /// Return list of declarations.
    ChunkList& chunks_get();
    /// Return list of instructions.
    const Exp& body_get() const;
    /// Return list of instructions.
    Exp& body_get();
    /** \} */

  protected:
    /// List of declarations.
    ChunkList* chunks_;
    /// List of instructions.
    Exp* body_;
  };
} // namespace ast
#include <ast/let-exp.hxx>
