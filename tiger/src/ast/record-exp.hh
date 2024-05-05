/**
 ** \file ast/record-exp.hh
 ** \brief Declaration of ast::RecordExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/field-init.hh>
#include <ast/name-ty.hh>

namespace ast
{
  /// RecordExp.
  class RecordExp : public Exp
  {
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a RecordExp node.
    RecordExp(const Location& location,
              NameTy* type_name,
              fieldinits_type* fields);
    RecordExp(const RecordExp&) = delete;
    RecordExp& operator=(const RecordExp&) = delete;
    /// Destroy a RecordExp node.
    ~RecordExp() override;
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
    /// Return identifier of the record type.
    const NameTy& type_name_get() const;
    /// Return identifier of the record type.
    NameTy& type_name_get();
    /// Return list of field initializations.
    const fieldinits_type& fields_get() const;
    /// Return list of field initializations.
    fieldinits_type& fields_get();
    /** \} */

  protected:
    /// Identifier of the record type.
    NameTy* type_name_;
    /// List of field initializations.
    fieldinits_type* fields_;
  };
} // namespace ast
#include <ast/record-exp.hxx>
