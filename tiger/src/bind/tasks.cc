/**
 ** \file bind/tasks.cc
 ** \brief Bind module tasks implementation.
 */

// DONE: Some code was deleted here.

#include <iostream>

#include <ast/libast.hh>
#include <ast/tasks.hh>
#include <bind/libbind.hh>
#include <ast/fwd.hh>
#define DEFINE_TASKS 1
#include <bind/tasks.hh>
#undef DEFINE_TASKS
#include <misc/xalloc.hh>

namespace bind::tasks {
  void bindings_compute() { bind::bind_compute(*ast::tasks::the_program); }
  void bindings_display() { ast::bindings_display(std::cout) = true; }
  void renamer_compute() { bind::renamer(*ast::tasks::the_program); }
}
