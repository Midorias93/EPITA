// -*- C++ -*-

%module tiger_type

%include "std_string.i"

%include "misc/singleton.hh"

%{
  #include "helper.hh"
  #include <type/libtype.hh>
  #include <misc/singleton.hh>

  #include <type/fwd.hh>
  #include <type/type.hh>
  #include <type/array.hh>
  #include <type/builtin-types.hh>
  #include <type/class.hh>
  #include <type/field.hh>
  #include <type/function.hh>
  #include <type/method.hh>
  #include <type/named.hh>
  #include <type/nil.hh>
  #include <type/record.hh>

  #include <type/visitor.hh>
  #include <type/pretty-printer.hh>
%}

%typemap(ret) type::Type* {
  $result = _get_swig_real_type_type(*$1);
}

%warnfilter(401);

%include "type/fwd.hh"
%include "type/type.hh"

%extend type::Type
{
  std::string __str__() const
  {
    std::ostringstream o;
    o << *$self;
    return o.str();
  }
}
%{
namespace {
  using namespace type;
  class SwigTypeVisitor : public ConstVisitor
  {
    public:
      PyObject *result;

#define STHELPER(TYPE) STCONVERT(TYPE, p_type__ ## TYPE)
    STHELPER(Array)
    STHELPER(Class)
    STHELPER(Function)
    STHELPER(Int)
    STHELPER(Method)
    STHELPER(Named)
    STHELPER(Nil)
    STHELPER(Record)
    STHELPER(String)
    STHELPER(Void)
#undef STHELPER
  };
} // namespace
%}
%inline %{
PyObject *_get_swig_real_type_type(const type::Type& e)
{
  SwigTypeVisitor stv;
  e.accept(stv);
  return stv.result;
}
%}


%include "type/array.hh"
%include "type/builtin-types.hh"
%include "type/class.hh"
%include "type/field.hh"
%include "type/function.hh"
%include "type/method.hh"
%include "type/named.hh"
%include "type/nil.hh"
%include "type/record.hh"

%include "type/libtype.hh"
