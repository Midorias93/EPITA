/**
 ** \file bind/libbind.hh
 ** \brief Interface of the bind module.
*/

#include <misc/scoped-map.hh>

// FIXME: Some code was deleted here.
namespace bind {

  void bind_compute(ast::Ast& tree);
  void renamer(ast::Ast& tree);

  extern misc::scoped_map<misc::symbol, ast::VarDec> scoped_map_var;
  extern misc::scoped_map<misc::symbol, ast::FunctionDec> scoped_map_func;
  extern misc::scoped_map<misc::symbol, ast::TypeDec> scoped_map_type;

}
