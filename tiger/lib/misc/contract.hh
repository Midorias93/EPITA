/**
 ** \file  misc/contract.hh
 ** \brief Replacement for cassert.
 **/

#pragma once

// Use GCC magic bits to specify we cannot return from these functions

#ifndef __attribute__
#  if !defined __GNUC__
#    define __attribute__(Spec) /* empty */
#  endif
#endif

[[noreturn]] void __Terminate(const char*, int, const char*);

#define die(Reason) __Terminate(__FILE__, __LINE__, Reason)
#define unreachable() die("unreachable code reached")

#ifdef NDEBUG

// This a trick use to disable assertion and co in the project. We need a stream
// in a 'else' to keep the code syntactically correct. However we do not want
// to print anything. So the 'if' is always true and does nothing.
// 'std::cerr' << "" is here to avoid warnings.
#  define __TestCondition                                                      \
    if (true)                                                                  \
      {                                                                        \
        ;                                                                      \
      }                                                                        \
    else                                                                       \
      std::cerr << ""

#  define assertion(Expr) __TestCondition
#  define invariant(Expr) __TestCondition
#  define precondition(Expr) __TestCondition
#  define postcondition(Expr) __TestCondition

#else // NDEBUG

#  define __TestCondition(CondType, Expr)                                      \
    if (Expr)                                                                  \
      {                                                                        \
        ;                                                                      \
      }                                                                        \
    else                                                                       \
      Contract(#CondType, #Expr, __FILE__, __LINE__)

#  define assertion(Expr) __TestCondition(Assertion, Expr)
#  define invariant(Expr) __TestCondition(Invariant, Expr)
#  define precondition(Expr) __TestCondition(Precondition, Expr)
#  define postcondition(Expr) __TestCondition(Postcondition, Expr)

#endif // ! NDEBUG

class Contract
{
public:
  Contract(const char* condType,
           const char* condText,
           const char* fileName,
           int fileLine);
  [[noreturn]] ~Contract();

  const char* condType;
  const char* condText;
  const char* fileName;
  int fileLine;
};

#include <misc/contract.hxx>
