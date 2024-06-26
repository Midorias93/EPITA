/**
 ** \file desugar/tasks.hh
 ** \brief Desugar module tasks.
 */

#pragma once

#include <config.h>
#include <misc/fwd.hh>
#include <task/libtask.hh>

/// Tasks of the desugar module.
namespace desugar::tasks
{
  TASK_GROUP("Desugaring and bounds-checking");

  /*-------------.
    | Desugaring.  |
    `-------------*/

  /// Enable translation of `for' loops into `while' loops.
  BOOLEAN_TASK_DECLARE("desugar-for", "desugar `for' loops", desugar_for_p, "");

  /// Enable string comparison desugaring.
  BOOLEAN_TASK_DECLARE("desugar-string-cmp",
                       "desugar string comparisons",
                       desugar_string_cmp_p,
                       "");

  /// Default the removal of syntactic sugar from the AST to Tiger
  /// (without overloading).
  DISJUNCTIVE_TASK_DECLARE("desugared",
                           "Default the removal of syntactic sugar "
                           "from the AST to Tiger (without overloading)",
                           "desugar");

  /// Remove syntactic sugar from the Ast.
  TASK_DECLARE("desugar", "desugar the AST", desugar, "types-compute rename");

  /* FIXME: Careful with this options (and with
     --raw-bounds-checks-add), as they leave the AST in a bad state
     (without bindings nor types).  For instance,

     tc --raw-desugar -H  will probably result in a SEGV.

     since hir-compute wants a type-checked AST. */

  /// Remove syntactic sugar from the AST without recomputing
  /// bindings nor types.
  TASK_DECLARE("raw-desugar",
               "desugar the AST without recomputing "
               "bindings nor types",
               raw_desugar,
               "typed rename");

} // namespace desugar::tasks
