/**
 ** \file bind/renamer.cc
 ** \brief Implementation of bind::Renamer.
 */

#include <bind/renamer.hh>

namespace bind
{
  using namespace ast;

  // DONE: Some code was deleted here.
  bool mainFound = false;

  void Renamer::operator()(ast::VarDec& e) {
    Renamer::visit(e, &e);

    this->accept(e.type_name_get());
    this->accept(e.init_get());
  }

  void Renamer::operator()(ast::FunctionDec& e) {
    bool isMain = false;
    if (e.name_get() == misc::symbol("_main"))
    {
      mainFound = true;
      isMain = true;
    }
    e.formals_get().accept(*this);
    if (mainFound && !isMain)
    {
      Renamer::visit(e, &e);
    }

    if (e.result_get())
      e.result_get()->accept(*this);
    if(e.body_get())
      e.body_get()->accept(*this);

  }

  void Renamer::operator()(ast::TypeDec& e) {
    Renamer::visit(e, &e);
    e.ty_get().accept(*this);
  }

  void Renamer::operator()(ast::SimpleVar& e) {
    Renamer::visit(e, e.def_get());
  }

  void Renamer::operator() (ast::CallExp& e) {
    Renamer::visit(e, e.def_get());
    for (auto a : e.args_get()) {
      a->accept(*this);
    }
  }
} // namespace bind
