// -*- C++ -*-

%module tiger_desugar

%import "tiger_ast.i"

%{
  #include <desugar/libdesugar.hh>
  #include <ast/all.hh>
  #include "swig_real_type.hh"
%}

%rename(desugar) ast_desugar;
%rename(raw_desugar) ast_raw_desugar;

%inline {
ast::Ast* ast_desugar(const ast::Ast& tree,
                        bool desugar_for = false,
                        bool desugar_string_cmp = false)
{
  return desugar::desugar<ast::Ast>(tree, desugar_for, desugar_string_cmp);
}
ast::Ast* ast_raw_desugar(const ast::Ast& tree,
                          bool desugar_for = false,
                          bool desugar_string_cmp = false)
{
  return desugar::raw_desugar<ast::Ast>(tree, desugar_for, desugar_string_cmp);
}
}

