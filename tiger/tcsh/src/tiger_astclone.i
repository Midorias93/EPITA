// -*- C++ -*-

%module tiger_astclone

%import "tiger_ast.i"

%{
  #include <astclone/libastclone.hh>
  #include "swig_real_type.hh"
%}
%inline
{
  ast::Ast* clone(const ast::Ast& tree)
  {
    return astclone::clone<ast::Ast>(tree);
  }
}
