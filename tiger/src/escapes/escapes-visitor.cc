/**
 ** \file escapes/escapes-visitor.cc
 ** \brief Implementation for escapes/escapes-visitor.hh.
 */

#include <ast/all.hh>
#include <escapes/escapes-visitor.hh>
#include <misc/contract.hh>
#include <map>

namespace escapes
{

    misc::symbol actual_function;

    void EscapesVisitor::operator()(ast::VarDec& e) {
        e.def_function_set(actual_function);
        e.escape_set(false);
        this->accept(e.type_name_get());
        this->accept(e.init_get());
    }
    void EscapesVisitor::operator()(ast::SimpleVar& e) {
        if (e.def_get()->def_function_get() != actual_function)
            e.def_get()->escape_set(true);
    }

    void EscapesVisitor::operator()(ast::FunctionDec& e) {
       actual_function = e.name_get();

        e.formals_get().accept(*this);

        if (e.result_get())
            e.result_get()->accept(*this);
        if (e.body_get())
            e.body_get()->accept(*this);
    }
} // namespace escapes
