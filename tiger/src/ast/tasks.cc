/**
 ** \file ast/tasks.cc
 ** \brief Ast Tasks implementation.
 */

#include <ast/libast.hh>
#include <misc/contract.hh>
#define DEFINE_TASKS 1
#include <ast/tasks.hh>
#undef DEFINE_TASKS

namespace ast::tasks
{
  // The abstract syntax tree.
  std::unique_ptr<ast::ChunkList> the_program(nullptr);

  void ast_display()
  {
    // `the_program' should have been set by the parse module by now.
    precondition(the_program) << "Could not dump the AST, root is null";
    std::cout << "/* == Abstract Syntax Tree. == */\n"
              << *the_program << std::endl;
  }

  void ast_dump()
  {
    // `the_program' should have been set by the parse module by now.
    precondition(the_program) << "Could not dump the AST, root is null";
    ast::dump_dot(*the_program, std::cout);
  }

} // namespace ast::tasks
