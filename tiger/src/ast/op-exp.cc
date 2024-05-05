/**
 ** \file ast/op-exp.cc
 ** \brief Implementation of ast::OpExp.
 */

#include <ast/op-exp.hh>
#include <ast/visitor.hh>

namespace ast
{
  OpExp::OpExp(const Location& location,
               Exp* left,
               OpExp::Oper oper,
               Exp* right)
    : Exp(location)
    , left_(left)
    , oper_(oper)
    , right_(right)
  {}

  OpExp::~OpExp()
  {
    delete left_;
    delete right_;
  }

  void OpExp::accept(ConstVisitor& v) const { v(*this); }

  void OpExp::accept(Visitor& v) { v(*this); }
} // namespace ast

std::string str(ast::OpExp::Oper oper)
{
  static const std::unordered_map<ast::OpExp::Oper, std::string> op_str = {
    {ast::OpExp::Oper::add, "+"}, {ast::OpExp::Oper::sub, "-"},
    {ast::OpExp::Oper::mul, "*"}, {ast::OpExp::Oper::div, "/"},
    {ast::OpExp::Oper::eq, "="},  {ast::OpExp::Oper::ne, "<>"},
    {ast::OpExp::Oper::lt, "<"},  {ast::OpExp::Oper::le, "<="},
    {ast::OpExp::Oper::gt, ">"},  {ast::OpExp::Oper::ge, ">="}};

  return op_str.at(oper);
}
