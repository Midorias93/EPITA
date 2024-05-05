/**
 ** \file bind/libbind.cc
 ** \brief Define exported bind functions.
 */
    #include <ast/fwd.hh>
    #include <bind/binder.hh>
    #include <bind/renamer.hh>

// FIXME: Some code was deleted here.
namespace bind
{
  void bind_compute(ast::Ast& tree)
  {
      Binder bind_compute;
      bind_compute(tree);
      if (bind_compute.error_get()) {
          auto error =  bind_compute.error_get();
          error.exit_on_error();
      }

  }


  void renamer (ast::Ast& tree) {
     Renamer rename_compute;
     rename_compute(tree);
  }
}
