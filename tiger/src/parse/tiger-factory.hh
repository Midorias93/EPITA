/**
 ** \file parse/tiger-factory.hh
 ** \brief Declaration of parse::TigerFactory.
 */

#pragma once

#include <ast/all.hh>
#include <ast/fwd.hh>
#include <parse/location.hh>

namespace parse
{
  ast::IntExp* make_IntExp(const location& location, int num);

  ast::StringExp* make_StringExp(const location& location, std::string string);

  ast::ObjectExp* make_ObjectExp(const location& location,
                                 ast::NameTy* type_name);

  ast::CallExp* make_CallExp(const location& location,
                             misc::symbol name,
                             ast::exps_type* args);

  ast::MethodCallExp* make_MethodCallExp(const location& location,
                                         misc::symbol name,
                                         ast::exps_type* args,
                                         ast::Var* object);

  ast::RecordExp* make_RecordExp(const location& location,
                                 ast::NameTy* type_name,
                                 ast::fieldinits_type* fields);

  ast::ArrayExp* make_ArrayExp(const location& location,
                               ast::NameTy* type_name,
                               ast::Exp* size,
                               ast::Exp* init);

  ast::NilExp* make_NilExp(const location& location);

  ast::SeqExp* make_SeqExp(const location& location, ast::exps_type* exps);

  ast::AssignExp*
  make_AssignExp(const location& location, ast::Var* var, ast::Exp* exp);

  ast::IfExp* make_IfExp(const location& location,
                         ast::Exp* test,
                         ast::Exp* thenclause,
                         ast::Exp* elseclause);

  ast::IfExp*
  make_IfExp(const location& location, ast::Exp* test, ast::Exp* thenclause);

  ast::WhileExp*
  make_WhileExp(const location& location, ast::Exp* test, ast::Exp* body);

  ast::ForExp* make_ForExp(const location& location,
                           ast::VarDec* vardec,
                           ast::Exp* hi,
                           ast::Exp* body);

  ast::BreakExp* make_BreakExp(const location& location);

  ast::LetExp*
  make_LetExp(const location& location, ast::ChunkList* decs, ast::Exp* body);

  ast::OpExp* make_OpExp(const location& location,
                         ast::Exp* left,
                         ast::OpExp::Oper oper,
                         ast::Exp* right);

  ast::CastExp*
  make_CastExp(const location& location, ast::Exp* exp, ast::Ty* ty);

  ast::SimpleVar* make_SimpleVar(const location& location, misc::symbol name);

  ast::FieldVar*
  make_FieldVar(const location& location, ast::Var* var, misc::symbol name);

  ast::SubscriptVar*
  make_SubscriptVar(const location& location, ast::Var* var, ast::Exp* index);

  /* Use expansion parameter pack to handle when we have one or empty arguments */
  template <class... T> ast::exps_type* make_exps_type(T... exps);

  ast::ChunkList* make_ChunkList(const location& location);

  ast::TypeChunk* make_TypeChunk(const location& location);

  ast::TypeDec*
  make_TypeDec(const location& location, misc::symbol name, ast::Ty* ty);

  ast::RecordTy* make_RecordTy(const location& location,
                               ast::fields_type* fields);

  ast::ArrayTy* make_ArrayTy(const location& location, ast::NameTy* base_type);

  template <class... T> ast::fields_type* make_fields_type(T... types);

  ast::Field* make_Field(const location& location,
                         misc::symbol name,
                         ast::NameTy* type_name);

  ast::NameTy* make_NameTy(const location& location, misc::symbol name);

  template <class... T>
  ast::fieldinits_type* make_fieldinits_type(T... inits_types);

  ast::FieldInit*
  make_FieldInit(const location& location, misc::symbol name, ast::Exp* init);

  ast::ClassTy* make_ClassTy(const location& location,
                             ast::NameTy* super,
                             ast::ChunkList* decs);

  ast::VarChunk* make_VarChunk(const location& location);

  ast::VarDec* make_VarDec(const location& location,
                           misc::symbol name,
                           ast::NameTy* type_name,
                           ast::Exp* init);

  ast::MethodChunk* make_MethodChunk(const location& location);

  ast::MethodDec* make_MethodDec(const location& location,
                                 misc::symbol name,
                                 ast::VarChunk* formals,
                                 ast::NameTy* result,
                                 ast::Exp* body);

  ast::FunctionDec* make_FunctionDec(const location& location,
                                     misc::symbol name,
                                     ast::VarChunk* formals,
                                     ast::NameTy* result,
                                     ast::Exp* body);

  template <class... T> ast::FunctionChunk* make_FunctionChunk(T... args);
} // namespace parse

#include <parse/tiger-factory.hxx>
