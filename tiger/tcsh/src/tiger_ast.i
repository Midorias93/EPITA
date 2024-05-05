// -*- C++ -*-

%module tiger_ast

%include "std_string.i"
%include "std_vector.i"
%include "std_list.i"
%include "std_except.i"

%{
  #include "helper.hh"
  #include <sstream>
  #include <fstream>
  #include <ast/visitor.hh>
  #include <ast/object-visitor.hh>
  #include <ast/default-visitor.hh>
  #include <ast/all.hh>
  #include <ast/libast.hh>
  #include <common.hh>
%}

%typemap(ret) ast::Ast* {
  $result = get_swig_real_ast_type(*$1);
}
%apply ast::Ast* { ast::ChunkInterface*, ast::Exp*, ast::Dec*, ast::Ty*, ast::Var* }
%apply ast::Ast* { ast::Ast&, ast::ChunkInterface&, ast::Exp&, ast::Dec&, ast::Ty&, ast::Var& }

%include "common.hh"
%include "ast/fwd.hh"

%include "ast/location.hh"

%include "ast/ast.hh"

%extend ast::Ast
{
  std::string __str__() const
  {
    std::ostringstream o;
    o << *$self;
    return o.str();
  }
  bool operator==(const ast::Ast& o) const
  {
    return $self == &o;
  }
}

%extend ast::OpExp {
  %pythoncode %{
    def oper_str_get(self) -> "std::string":
        return _tiger_ast.str(self.oper_get())

    @staticmethod
    def oper_names():
        return { getattr(_tiger_ast, t): t[len("OpExp_Oper_"):] for t in dir(_tiger_ast) if t.startswith("OpExp_Oper_") }

    def oper_name_get(self) -> "std::string":
        return OpExp.oper_names()[self.oper_get()]
  %}
}

%extend ast::Typable
{
  %pythoncode %{
    def type_get(self) -> "type::Type const *":
        import tiger_type
        return tiger_type._get_swig_real_type_type(_tiger_ast.Typable_type_get(self))
    %}
}

// Visitors.
%include "ast/visitor.hh"
%template(AstConstVisitor) ast::GenVisitor<misc::constify_traits>;
%template(AstVisitor) ast::GenVisitor<misc::id_traits>;
%warnfilter(401);

%{
#include "swig_real_type.hh"
%}

%define HELPER(TYPE, SUPER_TYPE)
    void operator()(const ast::##TYPE & e) override
    {
      CallbackVisitor_Argument arg{++id_, #TYPE, &e};
      auto obj = make_argument_dict(arg);
      call_callback(parent_obj_, obj);

      auto save_arg = parent_arg_;
      auto save_obj = parent_obj_;
      parent_arg_ = arg;
      parent_obj_ = obj;
      SUPER_TYPE##::operator()(e);
      parent_arg_ = save_arg;
      parent_obj_ = save_obj;
    }
%enddef

%warnfilter(451) CallbackVisitor_Argument::name;
%inline
{
  ast::Ast* ast_upcast(ast::ChunkList* a)
  {
    return static_cast<ast::Ast *>(a);
  }

#ifdef SWIGPYTHON

  struct CallbackVisitor_Argument
  {
    int id{};
    const char* name{};
    const ast::Ast* ast{};
  };

  class CallbackVisitor
    : public ast::DefaultConstVisitor
    , public ast::ObjectConstVisitor
  {
  public:
    using super_type = ast::DefaultVisitor;

    CallbackVisitor(PyObject* pyfunc)
      : GenVisitor<misc::constify_traits>()
    {
      Py_XINCREF(pyfunc);
      this->callback_ = pyfunc;
    }
    ~CallbackVisitor() {}

    PyObject* make_argument_dict(const CallbackVisitor_Argument& a)
    {
      std::ostringstream o;
      if (a.ast) o << *a.ast;
      std::string name(a.name);
      std::string dec_name;
      if (auto dec = dynamic_cast<const ast::Dec*>(a.ast))
        dec_name = std::string(dec->name_get());
      auto s = o.str();
      PyObject *obj = get_swig_real_ast_type(*a.ast);
      return Py_BuildValue("{s:i,s:s,s:s,s:s,s:O}",
                           "id", a.id,
                           "name", name.c_str(),
                           "string", s.c_str(),
                           "dec", dec_name.c_str(),
                           "ast", obj);
    }

    PyObject* call_callback(PyObject* from, PyObject* to) const
    {
      auto arglist = Py_BuildValue("(OO)", from ? from : Py_None, to ? to : Py_None);
      auto result = PyObject_CallObject(this->callback_, arglist);
      Py_DECREF(arglist);
      return result;
    }

    HELPER(ArrayExp, ast::DefaultConstVisitor)
    HELPER(ArrayTy, ast::DefaultConstVisitor)
    HELPER(AssignExp, ast::DefaultConstVisitor)
    HELPER(Ast, ast::DefaultConstVisitor)
    HELPER(BreakExp, ast::DefaultConstVisitor)
    HELPER(CallExp, ast::DefaultConstVisitor)
    HELPER(CastExp, ast::DefaultConstVisitor)
    HELPER(ChunkList, ast::DefaultConstVisitor)
    HELPER(Field, ast::DefaultConstVisitor)
    HELPER(FieldInit, ast::DefaultConstVisitor)
    HELPER(FieldVar, ast::DefaultConstVisitor)
    HELPER(ForExp, ast::DefaultConstVisitor)
    HELPER(FunctionChunk, ast::DefaultConstVisitor)
    HELPER(FunctionDec, ast::DefaultConstVisitor)
    HELPER(IfExp, ast::DefaultConstVisitor)
    HELPER(IntExp, ast::DefaultConstVisitor)
    HELPER(LetExp, ast::DefaultConstVisitor)
    HELPER(NameTy, ast::DefaultConstVisitor)
    HELPER(NilExp, ast::DefaultConstVisitor)
    HELPER(OpExp, ast::DefaultConstVisitor)
    HELPER(RecordExp, ast::DefaultConstVisitor)
    HELPER(RecordTy, ast::DefaultConstVisitor)
    HELPER(SeqExp, ast::DefaultConstVisitor)
    HELPER(SimpleVar, ast::DefaultConstVisitor)
    HELPER(StringExp, ast::DefaultConstVisitor)
    HELPER(SubscriptVar, ast::DefaultConstVisitor)
    HELPER(TypeChunk, ast::DefaultConstVisitor)
    HELPER(TypeDec, ast::DefaultConstVisitor)
    HELPER(VarChunk, ast::DefaultConstVisitor)
    HELPER(VarDec, ast::DefaultConstVisitor)
    HELPER(WhileExp, ast::DefaultConstVisitor)

    HELPER(ClassTy, ast::ObjectConstVisitor)
    HELPER(MethodChunk, ast::ObjectConstVisitor)
    HELPER(MethodCallExp, ast::ObjectConstVisitor)
    HELPER(MethodDec, ast::ObjectConstVisitor)
    HELPER(ObjectExp, ast::ObjectConstVisitor)

  private:
    PyObject* callback_{};

    int id_{};
    CallbackVisitor_Argument parent_arg_{};
    PyObject* parent_obj_{};
  };

  ast::ConstVisitor* get_callback_visitor(PyObject* pyfunc)
  {
    if (!PyCallable_Check(pyfunc)) {
      PyErr_SetString(PyExc_TypeError, "Need a callable object!");
      return NULL;
    }

    return new CallbackVisitor(pyfunc);
  }

#endif
}

// Types.
%include "ast/escapable.hh"
%include "ast/typable.hh"
%include "ast/type-constructor.hh"

%include "ast/field.hh"
%include "ast/field-init.hh"

// Exps.
%include "ast/exp.hh"
%include "ast/array-exp.hh"
%include "ast/assign-exp.hh"
%include "ast/break-exp.hh"
%include "ast/call-exp.hh"
%include "ast/cast-exp.hh"
%include "ast/for-exp.hh"
%include "ast/if-exp.hh"
%include "ast/int-exp.hh"
%include "ast/let-exp.hh"
%include "ast/method-call-exp.hh"
%include "ast/nil-exp.hh"
%include "ast/object-exp.hh"
%include "ast/op-exp.hh"
%include "ast/record-exp.hh"
%include "ast/seq-exp.hh"
%include "ast/string-exp.hh"
%include "ast/while-exp.hh"

// Vars.
%include "ast/var.hh"
%include "ast/simple-var.hh"
%include "ast/field-var.hh"
%include "ast/subscript-var.hh"

// Tys.
%include "ast/ty.hh"
%include "ast/name-ty.hh"
%include "ast/record-ty.hh"
%include "ast/array-ty.hh"
%include "ast/class-ty.hh"

// ChunkInterface.
%ignore ast::Chunk::operator[];
%include "ast/chunk-interface.hh"
%include "ast/dec.hh"
%include "ast/function-dec.hh"
%include "ast/method-dec.hh"
%include "ast/var-dec.hh"
%include "ast/type-dec.hh"
%include "ast/chunk-list.hh"
%include "ast/chunk.hh"

%extend ast::Chunk
{
  int __len__()
  {
    return std::distance((*$self).begin(), (*$self).end());
  }

  D* __getitem__(int pos) throw(std::out_of_range)
  {
    int size = std::distance((*$self).begin(), (*$self).end());
    if (pos >= size || pos < -size)
        throw std::out_of_range("trying to access chunk item");
    auto front = (*$self).begin();
    std::advance(front, pos >= 0 ? pos : size + pos);
    return *front;
  }
}

%template(FunctionChunk) ast::Chunk<ast::FunctionDec>;
%template(MethodChunk) ast::Chunk<ast::MethodDec>;
%template(TypeChunk) ast::Chunk<ast::TypeDec>;
%template(VarChunk) ast::Chunk<ast::VarDec>;
%template(exps_type)std::vector<ast::Exp*>;
%template(fieldinits_type) std::vector<ast::FieldInit*>;
%template(fields_type) std::vector<ast::Field*>;

%extend ast::ChunkList
{
  int __len__()
  {
    return std::distance((*$self).begin(), (*$self).end());
  }

  ast::ChunkInterface* __getitem__(int pos)
  {
    int size = std::distance((*$self).begin(), (*$self).end());
    if (pos >= size || pos < -size)
        throw std::out_of_range("trying to access chunk item");
    auto front = (*$self).begin();
    std::advance(front, pos >= 0 ? pos : size + pos);
    return *front;
  }
}

%include "ast/libast.hh"
