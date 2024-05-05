                                                          /* -*- C++ -*- */
// %option defines the parameters with which the reflex will be launched
%option noyywrap
// To enable compatibility with bison
%option bison-complete
%option bison-cc-parser=parser
%option bison_cc_namespace=parse
%option bison-locations

%option lex=lex
// Add a param of function lex() generate in Lexer class
%option params="::parse::TigerDriver& td"
%option namespace=parse
// Name of the class generate by reflex
%option lexer=Lexer

%top{

#define YY_EXTERN_C extern "C" // For linkage rule

#include <cerrno>
#include <climits>
#include <regex>
#include <string>

#include <boost/lexical_cast.hpp>

#include <misc/contract.hh>
  // Using misc::escape is very useful to quote non printable characters.
  // For instance
  //
  //    std::cerr << misc::escape('\n') << '\n';
  //
  // reports about `\n' instead of an actual new-line character.
#include <misc/escape.hh>
#include <misc/symbol.hh>
#include <parse/parsetiger.hh>
#include <parse/tiger-driver.hh>

  // DONE: Some code was deleted here (Define YY_USER_ACTION to update locations)
#define YY_USER_ACTION td.location_.columns(yyleng);

#define TOKEN(Type)                             \
  parser::make_ ## Type(td.location_)

#define TOKEN_VAL(Type, Value)                  \
  parser::make_ ## Type(Value, td.location_)

# define CHECK_EXTENSION()                              \
  do {                                                  \
    if (!td.enable_extensions_p_)                       \
      td.error_ << misc::error::error_type::scan        \
                << td.location_                         \
                << ": invalid identifier: `"            \
                << misc::escape(text()) << "'\n";       \
  } while (false)


%}

%x SC_COMMENT_SHORT SC_STRING SC_COMMENT_LONG

/* Abbreviations.  */
int             [0-9]+
wchars          [ \t]+
eol             [\n\r]+
identifier      _main|[a-zA-Z]([a-zA-Z0-9]|_)*
oct             \\[0-9]+
x               \\x[0-9A-F][0-9A-F]
wx              \\x
%class{
  std::string str;
  int val;
  int count_comment;
}

%%
/* The rules.  */
{int}         {
                  try
                  {
                      val = std::stoi(text());
                  }
                  catch (std::invalid_argument const& ex)
                          {
                              std::cerr << "std::invalid_argument::what(): " << ex.what() << '\n'; _exit(2);
                          }
                          catch (std::out_of_range const& ex)
                          {
                              std::cerr << "std::out_of_range::what(): " << ex.what() << '\n'; _exit(2);
                          }
                  return TOKEN_VAL(INT, val);
              }

"&"           {return TOKEN(AND);}
"array"       {return TOKEN(ARRAY);}
":="          {return TOKEN(ASSIGN);}
"break"       {return TOKEN(BREAK);}
"_cast"       {return TOKEN(CAST);}
"class"       {return TOKEN(CLASS);}
":"           {return TOKEN(COLON);}
","           {return TOKEN(COMMA);}
"/"           {return TOKEN(DIVIDE);}
"do"          {return TOKEN(DO);}
"."           {return TOKEN(DOT);}
"else"        {return TOKEN(ELSE);}
"end"         {return TOKEN(END);}
"="           {return TOKEN(EQ);}
"extends"     {return TOKEN(EXTENDS);}
"for"         {return TOKEN(FOR);}
"function"    {return TOKEN(FUNCTION);}
">="          {return TOKEN(GE);}
">"           {return TOKEN(GT);}
"if"          {return TOKEN(IF);}
"import"      {return TOKEN(IMPORT);}
"in"          {return TOKEN(IN);}
"{"           {return TOKEN(LBRACE);}
"["           {return TOKEN(LBRACK);}
"<="          {return TOKEN(LE);}
"let"         {return TOKEN(LET);}
"("           {return TOKEN(LPAREN);}
"<"           {return TOKEN(LT);}
"-"           {return TOKEN(MINUS);}
"method"      {return TOKEN(METHOD);}
"<>"          {return TOKEN(NE);}
"new"         {return TOKEN(NEW);}
"nil"         {return TOKEN(NIL);}
"of"          {return TOKEN(OF);}
"|"           {return TOKEN(OR);}
"+"           {return TOKEN(PLUS);}
"primitive"   {return TOKEN(PRIMITIVE);}
"}"           {return TOKEN(RBRACE);}
"]"           {return TOKEN(RBRACK);}
")"           {return TOKEN(RPAREN);}
";"           {return TOKEN(SEMI);}
"then"        {return TOKEN(THEN);}
"*"           {return TOKEN(TIMES);}
"to"          {return TOKEN(TO);}
"type"        {return TOKEN(TYPE);}
"var"         {return TOKEN(VAR);}
"while"       {return TOKEN(WHILE);}
"_chunks"     {return TOKEN(CHUNKS);}
"_exp"        {return TOKEN(EXP);}
"_lvalue"     {return TOKEN(LVALUE);}
"_namety"     {return TOKEN(NAMETY);}
"_cast"       {return TOKEN(CAST);}


{identifier}  {
                  if (text() == "_")
                  {
                    td.error_ << misc::error::error_type::scan        \
                    << td.location_                         \
                    << ": invalid identifier: `"            \
                    << misc::escape(text()) << "'\n";       \
                  }
                  return TOKEN_VAL(ID, text());
              }

"\""          {
                  str.clear();
                  str.append("\"");
                  start(SC_STRING);
              }

<SC_STRING> {
"\""          {start(INITIAL); str.append("\""); return TOKEN_VAL(STRING, str);}
{x}           {
                std::string strc = std::string(text(), size());
                strc.erase(0, 2);
                std::stringstream ss;
                ss << std::hex << strc;
                int tmp;
                if (ss >> tmp && tmp <= 127 && tmp >= 0)
                {

                    char ctmp = tmp;
                    str += ctmp;
                }
                else
                {
                    td.error_ << misc::error::error_type::scan        \
                    << td.location_                         \
                    << ": \\x could not compute hex value to char : `"            \
                    << misc::escape(text()) << "'\n";       \
                }
              }
{wx}          {
                td.error_ << misc::error::error_type::scan        \
                << td.location_                         \
                << ": \\x with something else than [0-9A-F][0-9A-F]: `"            \
                << misc::escape(text()) << "'\n";       \
              }
\\\"          {str.append("\\\"");}
{oct}         {
                std::string str = std::string(text(), size());
                str.erase(0, 1);
                try
                {
                    val = std::stoi(str);
                }
                catch (std::invalid_argument const& ex)
                {
                    td.error_ << misc::error::error_type::scan        \
                    << td.location_                         \
                    << ": stoi invalid arg : `"            \
                    << misc::escape(text()) << "'\n";       \
                }
                catch (std::out_of_range const& ex)
                {
                    td.error_ << misc::error::error_type::scan        \
                    << td.location_                         \
                    << ": stoi out of range: `"            \
                    << misc::escape(text()) << "'\n";       \
                }
                if (val > 377 || val < 0)
                {
                    td.error_ << misc::error::error_type::scan        \
                    << td.location_                         \
                    << ": wrong octal value in str: `"            \
                    << misc::escape(text()) << "'\n";       \
                }
                str.append(text());
              }
{eol}
<<EOF>>       {
                td.error_ << misc::error::error_type::scan        \
                << td.location_                         \
                << ": unterminated string: `"            \
                << misc::escape(text()) << "'\n";       \
                start(INITIAL);
              }
.             {str.append(text());}
}

"/*"          {
                  count_comment = 1;
                  start(SC_COMMENT_LONG);
              }


<SC_COMMENT_LONG> {
"*/"          {
                count_comment -= 1;
                if (count_comment == 0)
                    start(INITIAL);
                else
                    start(SC_COMMENT_LONG);
                }


"/*"          {
                count_comment += 1;
                start(SC_COMMENT_LONG);
              }

{eol}
<<EOF>>       {
                td.error_ << misc::error::error_type::scan        \
                << td.location_                         \
                << ": unterminated comment: `"            \
                << misc::escape(text()) << "'\n";       \
                start(INITIAL);
              }
.
}

"//"          {
                  start(SC_COMMENT_SHORT);
              }

<SC_COMMENT_SHORT> {
"\n"          {start(INITIAL);}
{eol}
.
}

"\n"          {
                td.error_ << misc::error::error_type::scan        \
                << td.location_                         \
                << ": \\n outside string: `"            \
                << misc::escape(text()) << "'\n";       \
                start(INITIAL);
              }
{eol}
{oct}         {
                td.error_ << misc::error::error_type::scan        \
                << td.location_                         \
                << ": octal outside string: `"            \
                << misc::escape(text()) << "'\n";       \
                start(INITIAL);
              }
{wchars}
<<EOF>>       {return TOKEN(EOF);}
.             {
                td.error_ << misc::error::error_type::scan        \
                << td.location_                         \
                << ": invalid char found while lexing: `"            \
                << misc::escape(text()) << "'\n";       \
                start(INITIAL);
              }

%%