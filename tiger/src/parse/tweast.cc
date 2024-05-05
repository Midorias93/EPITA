/**
 ** \file parse/tweast.cc
 ** \brief Implementation of parse::Tweast.
 */

#include <sstream>

#include <parse/tweast.hh>

namespace parse
{
  unsigned Tweast::count_ = 0;

  Tweast::Tweast()
    : Tweast("")
  {}

  Tweast::Tweast(const std::string& str)
    : MetavarMap<ast::Exp>::MetavarMap("exp")
    , MetavarMap<ast::Var>::MetavarMap("lvalue")
    , MetavarMap<ast::NameTy>::MetavarMap("namety")
    , MetavarMap<ast::ChunkList>::MetavarMap("chunks")
    , input_(str)
  {}

  std::string Tweast::input_get() const { return input_.str(); }

  std::ostream& Tweast::dump(std::ostream& ostr) const
  {
    ostr << "input = \"" << input_.str() << "\"" << misc::iendl;

    MetavarMap<ast::Exp>::dump(ostr);
    MetavarMap<ast::Var>::dump(ostr);
    MetavarMap<ast::NameTy>::dump(ostr);
    MetavarMap<ast::ChunkList>::dump(ostr);

    return ostr << misc::decendl;
  }

  std::ostream& operator<<(std::ostream& ostr, const Tweast& in)
  {
    return in.dump(ostr);
  }

} // namespace parse
