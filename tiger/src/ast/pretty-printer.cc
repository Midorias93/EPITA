/**
 ** \file ast/pretty-printer.cc
 ** \brief Implementation of ast::PrettyPrinter.
 */

#include <ast/all.hh>
#include <ast/libast.hh>
#include <ast/pretty-printer.hh>
#include <misc/escape.hh>
#include <misc/indent.hh>
#include <misc/separator.hh>

#include <type/class.hh>

namespace ast
{
    // Anonymous namespace: these functions are private to this file.
    namespace {
        /// Output \a e on \a ostr.
        inline std::ostream &operator<<(std::ostream &ostr, const Escapable &e) {

            if (escapes_display(ostr) && e.escape_get()) {
                ostr << "/* escaping */ ";
            }

            return ostr;
        }

        /// \brief Output \a e on \a ostr.
        ///
        /// Used to factor the output of the name declared,
        /// and its possible additional attributes.
        inline std::ostream &operator<<(std::ostream &ostr, const Dec &e) {
            ostr << e.name_get();
            if (bindings_display(ostr))
                ostr << " /* " << &e << " */";
            return ostr;
        }
    }
    
    PrettyPrinter::PrettyPrinter(std::ostream& ostr)
            : ostr_(ostr)
    {}

    void PrettyPrinter::operator()(const FieldVar& e)
    {
        // DONE
        ostr_ <<  e.var_get() << "." << e.name_get();
    }

    /* Foo[10]. */
    void PrettyPrinter::operator()(const SubscriptVar& e)
    {
        ostr_ << e.var_get() << '[' << misc::incindent << e.index_get()
              << misc::decindent << ']';
    }
    void PrettyPrinter::operator()(const SimpleVar& e)
    {
        auto def = e.def_get();
        if (def)
          ostr_ << static_cast<const Dec&>(*def) << misc::iendl;
        else
            ostr_ << e.name_get() << misc::iendl;
          /* ostr_ << e.name_get(); */

    }

    void PrettyPrinter::operator()(const CastExp& e)
    {
        ostr_ << "_cast(" << e.exp_get() << ", " << e.ty_get() << ')';
    }

    void PrettyPrinter::operator()(const NilExp& e)
    {
        ostr_ << "nil";
    }
    void PrettyPrinter::operator()(const IntExp& e)
    {
        ostr_ << e.value_get();
    }
    void PrettyPrinter::operator()(const StringExp& e)
    {
        ostr_ << e.value_get();
    }
    void PrettyPrinter::operator()(const CallExp& e)
    {
        auto def = e.def_get();
        if (def)
          ostr_ << static_cast<const Dec&>(*def);
        else
          ostr_ << e.name_get();
        ostr_<< "(";
        auto expvect = e.args_get();
        auto size = expvect.size();
        for (long unsigned int i = 1; i < size; i++)
        {
            ostr_ << *expvect[i - 1] << ", ";
        }
        if (size != 0)
        {
            ostr_ << *expvect[size - 1];
        }
        ostr_ << ")" << misc::iendl;
    }
    void PrettyPrinter::operator()(const OpExp& e)
    {
        ostr_ << "(";
        ostr_ << e.left_get();
        ostr_ << " " << str(e.oper_get()) << " ";
        ostr_ << e.right_get();
        ostr_ << ")" << misc::iendl;
    }

    void PrettyPrinter::operator()(const RecordExp& e)
    {
        ostr_ << e.type_name_get() << " " << "{";
        auto fieldvct = e.fields_get();
        auto size = fieldvct.size();
        if (size > 1)
        {
            for (long unsigned int i = 0; i < size - 1; i++)
            {
                ostr_ << *fieldvct[i] << ", ";

            }
        }
        if (size != 0)
        {
            ostr_ << *fieldvct[size - 1];
        }
        ostr_ << "}";
    }
    void PrettyPrinter::operator()(const SeqExp& e)
    {
        auto expvct = e.exps_get();
        auto size = expvct.size();
        if (size == 0)
        {
            ostr_ << "()";
            return;
        }
        if (size == 1)
        {
            ostr_ << "(";
            ostr_ << *expvct[0];
            ostr_ << ")" << misc::iendl;
          return;
        }
        ostr_ << "(" << misc::incendl;
        for (long unsigned int i = 1; i < size; i++)
        {
            ostr_ << *expvct[i - 1] << ";" << misc::iendl;
        }
        ostr_ << *expvct[size - 1] << misc::decendl;
        ostr_ << ")" << misc::iendl;
    }
    void PrettyPrinter::operator()(const AssignExp& e)
    {
        ostr_ << e.var_get() << " := " << e.exp_get();
    }
    void PrettyPrinter::operator()(const IfExp& e)
    {
        /* ostr_ << "("; */
        ostr_ << "if " << e.test_get() << misc::incendl;
        ostr_ << "then " << e.thenclause_get() << misc::iendl;
        ostr_ << "else " << e.elseclause_get() << misc::decendl;
        /* ostr_ << ")"; */
    }
    void PrettyPrinter::operator()(const WhileExp& e)
    {
        ostr_ << "while " << e.test_get() << " do" << misc::incendl;
        ostr_ << e.body_get() << misc::decendl;
    }
    void PrettyPrinter::operator()(const ForExp& e)
    {
        ostr_ << "for ";
        ostr_ << static_cast<const Dec&>(e.vardec_get());

        if (e.vardec_get().type_name_get() != nullptr)
            ostr_ << " : " << *e.vardec_get().type_name_get(); //<< misc::iendl;
        if (e.vardec_get().init_get() != nullptr)
            ostr_ << " := " << *e.vardec_get().init_get(); //<< misc::iendl;

        ostr_<< " to " << e.hi_get() << " do" << misc::incendl;
        ostr_ << e.body_get() << misc::decendl;
    }
    void PrettyPrinter::operator()(const BreakExp&)
    {
        ostr_ << "break";
    }
    void PrettyPrinter::operator()(const LetExp& e)
    {
        ostr_ << "let" << misc::incendl;
        ostr_ << e.chunks_get();
        ostr_ << "in" << misc::incendl;
        ostr_ << e.body_get() << misc::decendl;
        ostr_ << "end";
        ostr_ << misc::iendl;
    }
    void PrettyPrinter::operator()(const ArrayExp& e)
    {
        ostr_ << e.type_name_get() << "[" << e.size_get() << "] of " << e.init_get();
    }
    void PrettyPrinter::operator()(const FieldInit& e)
    {
        ostr_ << e.name_get() << " = " << e.init_get();
    }
    /*
    void PrettyPrinter::operator()(const ChunkList& e)
    {
        for (auto chunk : e.chunks_get())
            ostr_ << chunk;
    }
    */
    void PrettyPrinter::operator()(const VarChunk& e)
    {
      ostr_ << misc::separate(e.decs_get(), ", ");

    }
    void PrettyPrinter::operator()(const VarDec& e)
    {


        ostr_ << "var ";

        ostr_ << static_cast<const Escapable&>(e);

        ostr_ << static_cast<const Dec&>(e);
        if (e.type_name_get() != nullptr)
          ostr_ << " : " << *e.type_name_get(); //<< misc::iendl;
      if (e.init_get() != nullptr)
        ostr_ << " := " << *e.init_get() << misc::iendl; //<< misc::iendl;
    }
    void PrettyPrinter::operator()(const FunctionChunk& e)
    {
        chunk_visit<FunctionChunk>(e);
    }
    void PrettyPrinter::operator()(const FunctionDec& e)
    {
        if (e.body_get() == nullptr)
        {
            ostr_ << "primitive " << e << "(";
            auto decs = e.formals_get().decs_get();
            for (long unsigned int i = 1; i < decs.size(); i++)
            {
              ostr_ << static_cast<const Dec&>(*decs[i - 1]);
              if (decs[i - 1]->type_name_get() != nullptr)
              {
                ostr_ << " : " << *decs[i - 1]->type_name_get();
              }
              ostr_ << " ,";
            }
            if (decs.size() != 0)
            {
              ostr_ << static_cast<const Dec&>(*decs[decs.size() - 1]);
              if (decs[decs.size() - 1]->type_name_get() != nullptr)
              {
                ostr_ << " : "
                      << *decs[decs.size() - 1]->type_name_get();
              }
            }

            ostr_ << ")";

            if (e.result_get() != nullptr)
            {
                ostr_ << " : " << *e.result_get();
            }
            ostr_ << misc::iendl;
        }
        else
        {
            ostr_ << "function " << e << "(";

          auto decs = e.formals_get().decs_get();
          for (long unsigned int i = 1; i < decs.size(); i++)
          {
            ostr_ << static_cast<const Dec&>(*decs[i - 1]);
            if (decs[i - 1]->type_name_get() != nullptr)
            {
              ostr_ << " : " << *decs[i - 1]->type_name_get();
            }
            ostr_ << " ,";
          }
          if (decs.size() != 0)
          {
            ostr_ << static_cast<const Dec&>(*decs[decs.size() - 1]);
            if (decs[decs.size() - 1]->type_name_get() != nullptr)
            {
              ostr_ << " : "
                    << *decs[decs.size() - 1]->type_name_get();
            }
          }

          ostr_ << ")" << misc::iendl;

            if (e.result_get() != nullptr)
            {
                ostr_ << " : " << *e.result_get();
            }
            ostr_ << " = " << misc::incendl << *e.body_get() << misc::decindent;
        }
    }
    void PrettyPrinter::operator()(const TypeChunk& e)
    {
        chunk_visit<TypeChunk>(e);
    }
    void PrettyPrinter::operator()(const TypeDec& e)
    {
        ostr_ <<  "type " << e << " = " << e.ty_get() << misc::iendl;
    }
    void PrettyPrinter::operator()(const NameTy& e)
    {
        auto def = e.def_get();
        if (def)
          ostr_ << *e.def_get();
        else
          if(bindings_display(ostr_))
            ostr_ << e.name_get() << " /* 0 */";
          else
            ostr_ << e.name_get();
    }
    void PrettyPrinter::operator()(const RecordTy& e)
    {
        ostr_ << "{";
        auto fieldvct = e.fields_get();
        auto size = fieldvct.size();
        if (size > 1)
        {
            for (long unsigned int i = 0; i < size - 1; i++)
            {
                ostr_ << *fieldvct[i] << ", ";
            }
        }
        if (size != 0)
        {
            ostr_ << *fieldvct[size - 1];
        }
        ostr_ << "}";
    }
    void PrettyPrinter::operator()(const ArrayTy& e)
    {
        ostr_ << "array of " << e.base_type_get();
    }
    void PrettyPrinter::operator()(const Field& e)
    {
        ostr_ << e.name_get() << " : " << e.type_name_get();
    }

} // namespace ast

