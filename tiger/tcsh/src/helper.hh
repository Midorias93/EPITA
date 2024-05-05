#ifndef SWIG_HELPER_H
#define SWIG_HELPER_H

#define STCONVERT(TYPE, TYPENAME)                                              \
void operator()(const TYPE & e) override                                       \
{                                                                              \
  result = SWIG_NewPointerObj(SWIG_as_voidptr(&e), SWIGTYPE_ ## TYPENAME, 0);  \
}

#define IFTYPECONVERT(TYPE, TYPENAME)                                          \
if (const TYPE* d = dynamic_cast<const TYPE*>(&e); d != nullptr)               \
{                                                                              \
  result = SWIG_NewPointerObj(SWIG_as_voidptr(&e), SWIGTYPE_ ## TYPENAME, 0);  \
}

#endif /* ! SWIG_HELPER_H */
