// -*- C++ -*-

%module tiger_object

%import "tiger_ast.i"

%{
  #include <object/libobject.hh>
  #include <ast/all.hh>
  #include "swig_real_type.hh"
%}

%import "tiger_misc.i"


%include "object/fwd.hh"
%include "object/libobject.hh"
