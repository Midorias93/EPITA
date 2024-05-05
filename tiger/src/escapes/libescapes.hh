/**
 ** \file escapes/libescapes.hh
 ** \brief Declare functions and variables exported by escapes module.
 */

#pragma once

#include <ast/fwd.hh>
#include <misc/error.hh>

/// Computing escape and static link related information.
namespace escapes
{
  /// Compute the escaping variables.
  void escapes_compute(ast::Ast& tree);

  /// This boolean is used to know whether escape pass
  /// was made
  /// FIXME: this is a dirty fix it should be replaced with a
  /// new implementation of tasks
  extern bool escaped;

} // namespace escapes
