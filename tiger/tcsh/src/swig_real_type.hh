#ifndef SWIG_REAL_TYPE_HH
#define SWIG_REAL_TYPE_HH

#include "helper.hh"

namespace {
  using namespace ast;
  class SwigAstTypeVisitor : public ConstVisitor
  {
    public:
      PyObject *result;
    SwigAstTypeVisitor() : GenVisitor<misc::constify_traits>() {}
    ~SwigAstTypeVisitor() {}

#define STHELPER(TYPE) STCONVERT(TYPE, p_ast__ ## TYPE)
    STHELPER(ArrayExp)
    STHELPER(ArrayTy)
    STHELPER(AssignExp)
    STHELPER(Ast)
    STHELPER(BreakExp)
    STHELPER(CallExp)
    STHELPER(CastExp)
    STHELPER(ChunkList)
    STHELPER(ClassTy)
    STHELPER(Field)
    STHELPER(FieldInit)
    STHELPER(FieldVar)
    STHELPER(ForExp)
    STHELPER(FunctionDec)
    STHELPER(IfExp)
    STHELPER(IntExp)
    STHELPER(LetExp)
    STHELPER(MethodCallExp)
    STHELPER(MethodDec)
    STHELPER(NameTy)
    STHELPER(NilExp)
    STHELPER(ObjectExp)
    STHELPER(OpExp)
    STHELPER(RecordExp)
    STHELPER(RecordTy)
    STHELPER(SeqExp)
    STHELPER(SimpleVar)
    STHELPER(StringExp)
    STHELPER(SubscriptVar)
    STHELPER(TypeDec)
    STHELPER(VarDec)
    STHELPER(WhileExp)
#undef STHELPER

#define STCHUNKHELPER(TYPE)                                                    \
    STCONVERT(TYPE ## Chunk, p_ast__ChunkT_ast__ ## TYPE ## Dec_t)
    STCHUNKHELPER(Function)
    STCHUNKHELPER(Method)
    STCHUNKHELPER(Type)
    STCHUNKHELPER(Var)
#undef STCHUNKHELPER
  };
} // namespace

PyObject *get_swig_real_ast_type(const ast::Ast& e)
{
  SwigAstTypeVisitor stv;
  e.accept(stv);
  return stv.result;
}

#endif /* ! SWIG_REAL_TYPE_HH */
