/**
 ** \file bind/binder.cc
 ** \brief Implementation for bind/binder.hh.
 */

#include <ast/all.hh>
#include <bind/binder.hh>

#include <misc/contract.hh>
#include <misc/scoped-map.hh>

namespace bind
{
  /*-----------------.
  | Error handling.  |
  `-----------------*/


  /// The error handler.
  const misc::error& Binder::error_get() const { return error_; }

  // DONE: Some code was deleted here.

  //DONE: faire les cas d'erreur

  misc::scoped_map<misc::symbol, ast::VarDec*> scoped_map_var;
  misc::scoped_map<misc::symbol, ast::FunctionDec*> scoped_map_func;
  misc::scoped_map<misc::symbol, ast::TypeDec*> scoped_map_type;

  void Binder::operator()(ast::LetExp& e) {
    scoped_map_var.scope_begin();
    scoped_map_func.scope_begin();
    scoped_map_type.scope_begin();
    e.chunks_get().accept(*this);
    e.body_get().accept(*this);
    scoped_map_var.scope_end();
    scoped_map_func.scope_end();
    scoped_map_type.scope_end();

  }

    void Binder::operator()(ast::VarChunk& e) {
      auto decs = e.decs_get();
      auto count = 0;
      auto duplacate = false;
        for (auto a : decs) {
            count = 0;
            for (auto b : decs) {
                if (a->name_get() == b->name_get())
                    count++;
            }
            if (count > 1) {
                duplacate = true;
                break;
            }
        }
        if (duplacate)
            this->error_ << "Binding error : VarChunk : redefinition\n" << misc::error::error_type::bind;

        chunk_visit<ast::VarChunk>(e);

    }

  void Binder::operator()(ast::VarDec& e) {
    scoped_map_var.put(e.name_get(), &e);
    this->accept(e.type_name_get());
    this->accept(e.init_get());
  }

  void Binder::operator()(ast::FunctionChunk& e) {
      auto decs = e.decs_get();
      auto count = 0;
      auto duplacate = false;
      for (auto a : decs) {
          count = 0;
          for (auto b : decs) {
              if (a->name_get() == b->name_get())
                  count++;
          }
          if (count > 1) {
              duplacate = true;
              break;
          }
      }
      if (duplacate)
          this->error_ << "Binding error : FunctionChunk : redefinition\n" << misc::error::error_type::bind;

      for(auto a : e.decs_get()) {
          scoped_map_func.put(a->name_get(), a);
      }

      chunk_visit<ast::FunctionChunk>(e);
  }

  void Binder::operator()(ast::FunctionDec& e) {
    scoped_map_var.scope_begin();
    scoped_map_func.scope_begin();
    scoped_map_type.scope_begin();

    e.formals_get().accept(*this);

    if (e.result_get())
        e.result_get()->accept(*this);
    if (e.body_get())
      e.body_get()->accept(*this);
    scoped_map_var.scope_end();
    scoped_map_func.scope_end();
    scoped_map_type.scope_end();
  }

  void Binder::operator()(ast::TypeChunk& e) {
      auto decs = e.decs_get();
      auto count = 0;
      auto duplacate = false;
      for (auto a : decs) {
          count = 0;
          for (auto b : decs) {
              if (a->name_get() == b->name_get())
                  count++;
          }
          if (count > 1) {
              duplacate = true;
              break;
          }
      }
      if (duplacate)
          this->error_ << "Binding error : TypeChunk : redefinition\n" << misc::error::error_type::bind;

      for(auto a : e.decs_get()) {
          scoped_map_type.put(a->name_get(), a);
      }

      chunk_visit<ast::TypeChunk>(e);

  }

  void Binder::operator()(ast::TypeDec& e) {
    e.ty_get().accept(*this);
  }

  void Binder::operator()(ast::SimpleVar& e) {
      auto a = scoped_map_var.get(e.name_get());
      if (a) {
          e.def_set(a);
      }
      else {
          this->error_ << "Binding error : SimpleVar\n" << misc::error::error_type::bind;
      }


  }

  void Binder::operator() (ast::CallExp& e) {
    auto a = scoped_map_func.get(e.name_get());
    if (a) {
        e.def_set(a);
    }
    else {
        this->error_ << e.location_get() << " : Binding error : CallExp\n" << misc::error::error_type::bind;
    }
    for (auto a: e.args_get()) {
      a->accept(*this);
      }
  }


  void Binder::operator()(ast::NameTy &e) {
        auto a = scoped_map_type.get(e.name_get());
        if (a)
            e.def_set(a);
        else
        {
            if (e.name_get().get() != "int" && e.name_get().get() != "string") {
                this->error_ << e.location_get() << " : Binding error : NameTy\n" << misc::error::error_type::bind;
            }
        }
  }

  void Binder::operator()(ast::BreakExp& e) {
      // peut faut faire quelque chose
  }


} // namespace bind
