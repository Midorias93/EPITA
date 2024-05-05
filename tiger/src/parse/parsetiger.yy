                                                                // -*- C++ -*-
%require "3.8"
%language "c++"
// Set the namespace name to `parse', instead of `yy'.
%define api.prefix {parse}
%define api.namespace {parse}
%define api.parser.class {parser}
%define api.value.type variant
%define api.token.constructor

// We use a GLR parser because it is able to handle Shift-Reduce and
// Reduce-Reduce conflicts by forking and testing each way at runtime. GLR
// permits, by allowing few conflicts, more readable and maintainable grammars.
%glr-parser
%skeleton "glr2.cc"

// In TC, we expect the GLR to resolve one Shift-Reduce and zero Reduce-Reduce
// conflict at runtime. Use %expect and %expect-rr to tell Bison about it.
%expect 1
%expect-rr 0

%define parse.error verbose
%defines
%debug
// Prefix all the tokens with TOK_ to avoid colisions.
%define api.token.prefix {TOK_}

/* We use pointers to store the filename in the locations.  This saves
   space (pointers), time (no deep copy), but leaves the problem of
   deallocation.  This would be a perfect job for a misc::symbol
   object (passed by reference), however Bison locations require the
   filename to be passed as a pointer, thus forcing us to handle the
   allocation and deallocation of this object.

   Nevertheless, all is not lost: we can still use a misc::symbol
   object to allocate a flyweight (constant) string in the pool of
   symbols, extract it from the misc::symbol object, and use it to
   initialize the location.  The allocated data will be freed at the
   end of the program (see the documentation of misc::symbol and
   misc::unique).  */
%define api.filename.type {const std::string}
%locations

/*---------------------.
| Support for tokens.  |
`---------------------*/
%code requires
{
#include <string>
#include <misc/algorithm.hh>
#include <misc/separator.hh>
#include <misc/symbol.hh>
#include <parse/fwd.hh>
# include <parse/tiger-factory.hh>

  // Pre-declare parse::parse to allow a ``reentrant'' parsing within
  // the parser.
  namespace parse
  {
    ast_type parse(Tweast& input);
  }
}

// The parsing context.
%param { ::parse::TigerDriver& td }
%parse-param { ::parse::Lexer& lexer }

%printer { yyo << $$; } <int> <std::string> <misc::symbol>;

%token <std::string>    STRING "string"
%token <misc::symbol>   ID     "identifier"
%token <int>            INT    "integer"


/*--------------------------------.
| Support for the non-terminals.  |
`--------------------------------*/

%code requires
{
# include <ast/fwd.hh>
// Provide the declarations of the following classes for the
// %destructor clauses below to work properly.
# include <ast/exp.hh>
# include <ast/var.hh>
# include <ast/ty.hh>
# include <ast/name-ty.hh>
# include <ast/field.hh>
# include <ast/field-init.hh>
# include <ast/function-dec.hh>
# include <ast/type-dec.hh>
# include <ast/var-dec.hh>
# include <ast/chunk.hh>
# include <ast/chunk-list.hh>
}

  // FIXME: Some code was deleted here (Printers and destructors).

/*-----------------------------------------.
| Code output in the implementation file.  |
`-----------------------------------------*/

%code
{
# include <parse/tweast.hh>
# include <misc/separator.hh>
# include <misc/symbol.hh>
# include <ast/all.hh>
# include <ast/libast.hh>

  namespace
  {

    /// Get the metavar from the specified map.
    template <typename T>
    T*
    metavar(parse::TigerDriver& td, unsigned key)
    {
      parse::Tweast* input = td.input_;
      return input->template take<T>(key);
    }

  }
}

%code
{
  #include <parse/scantiger.hh>  // header file generated with reflex --header-file
  #undef yylex
  #define yylex lexer.lex  // Within bison's parse() we should invoke lexer.lex(), not the global lex()
}

// Definition of the tokens, and their pretty-printing.
%token AND          "&"
       ARRAY        "array"
       ASSIGN       ":="
       BREAK        "break"
       CAST         "_cast"
       CLASS        "class"
       COLON        ":"
       COMMA        ","
       DIVIDE       "/"
       DO           "do"
       DOT          "."
       ELSE         "else"
       END          "end"
       EQ           "="
       EXTENDS      "extends"
       FOR          "for"
       FUNCTION     "function"
       GE           ">="
       GT           ">"
       IF           "if"
       IMPORT       "import"
       IN           "in"
       LBRACE       "{"
       LBRACK       "["
       LE           "<="
       LET          "let"
       LPAREN       "("
       LT           "<"
       MINUS        "-"
       METHOD       "method"
       NE           "<>"
       NEW          "new"
       NIL          "nil"
       OF           "of"
       OR           "|"
       PLUS         "+"
       PRIMITIVE    "primitive"
       RBRACE       "}"
       RBRACK       "]"
       RPAREN       ")"
       SEMI         ";"
       THEN         "then"
       TIMES        "*"
       TO           "to"
       TYPE         "type"
       VAR          "var"
       WHILE        "while"
       EOF 0        "end of file"

%type <ast::Exp*>             exp

%type <ast::ChunkList*>       chunks
%type <ast::ChunkInterface*>           chunk


%type <ast::TypeChunk*>       tychunk
%type <ast::FunctionChunk*>     funchunk
%type <ast::FunctionDec*>     fundec

%type <ast::VarChunk*>          varchunk
%type <ast::VarDec*>          vardec

%type <ast::TypeDec*>         tydec

%type <ast::NameTy*>          typeid
%type <ast::Ty*>              ty

%type <ast::Field*>           tyfield
%type <ast::VarDec*>          tyfield.2

%type <ast::fields_type*>     tyfields tyfields.1

%type <ast::VarChunk*>     tyfields.2 tyfields.3


%type <ast::fieldinits_type*> exp.1 exp.2
%type <ast::exps_type*>       exp.3
%type <ast::exps_type*>       exp.4

%type <ast::exps_type*>       exps
%type <ast::exps_type*>       exps.1

%type <ast::Var*>            lvalue


// Solving conflicts on:
// let type foo = bar
//     type baz = bat
// which can be understood as a list of two TypeChunk containing
// a unique TypeDec each, or a single TypeChunk containing two TypeDec.
// We want the latter.

%precedence CHUNKS
%precedence TYPE
%precedence FUNCTION
%precedence PRIMITIVE
%precedence ASSIGN
%precedence DO
%precedence OF
%precedence THEN
%precedence ELSE
%left AND OR
%nonassoc GE LE GT LT NE EQ
%left PLUS MINUS
%left DIVIDE TIMES

%start program

%%
program:
  /* Parsing a source program.  */
  exp
   { td.ast_ = $1; }
| /* Parsing an imported file.  */
  chunks
   { td.ast_ = $1; }
;

exps:
    %empty { $$ = make_exps_type(); }
    | exp exps.1   { $$ = $2; $$->insert($$->begin(), $1); }
    ;

exps.1:
    %empty { $$ = make_exps_type(); }
    | SEMI exp exps.1 { $$ = $3; $$->insert($$->begin(), $2); }
    ;

%token EXP "_exp";
exp:
  NIL { $$ = make_NilExp(@$); }
  | INT { $$ = make_IntExp(@$, $1); }
  | STRING { $$ = make_StringExp(@$, $1); }
  | ID LBRACK exp RBRACK OF exp {$$ = make_ArrayExp(@$, make_NameTy(@$, $1), $3, $6); }
  | ID LBRACE exp.2 RBRACE {$$  = make_RecordExp(@$, make_NameTy(@$, $1), $3); }
  | NAMETY "(" INT ")" LBRACK exp RBRACK OF exp {$$ = make_ArrayExp(@$, metavar<ast::NameTy>(td, $3), $6, $9); }
  | NAMETY "(" INT ")" LBRACE exp.2 RBRACE {$$  = make_RecordExp(@$, metavar<ast::NameTy>(td, $3), $6); }
  | lvalue { $$ = $1; }
  | ID LPAREN exp.3 RPAREN { $$ = make_CallExp(@$, $1, $3); }
  | MINUS exp {
        Tweast in;
        in << "0 - " << $2;
        $$ = td.parse(in);
  }
  | exp PLUS exp { $$ = make_OpExp(@$, $1, ast::OpExp::Oper::add, $3); }
  | exp MINUS exp { $$ = make_OpExp(@$, $1, ast::OpExp::Oper::sub, $3); }
  | exp TIMES exp { $$ = make_OpExp(@$, $1, ast::OpExp::Oper::mul, $3); }
  | exp DIVIDE exp { $$ = make_OpExp(@$, $1, ast::OpExp::Oper::div, $3); }
  | exp EQ exp { $$ = make_OpExp(@$, $1, ast::OpExp::Oper::eq, $3); }
  | exp NE exp { $$ = make_OpExp(@$, $1, ast::OpExp::Oper::ne, $3); }
  | exp GE exp { $$ = make_OpExp(@$, $1, ast::OpExp::Oper::ge, $3); }
  | exp GT exp { $$ = make_OpExp(@$, $1, ast::OpExp::Oper::gt, $3); }
  | exp LE exp { $$ = make_OpExp(@$, $1, ast::OpExp::Oper::le, $3); }
  | exp LT exp { $$ = make_OpExp(@$, $1, ast::OpExp::Oper::lt, $3); }
  | exp AND exp {
        Tweast in;
        in << "if " << $1 << " then " << "\n" << $3 << "<> 0" <<
        "else\n" << "0";
        $$ = td.parse(in);
  }
  | exp OR exp {
        Tweast in;
        in << "if " << $1 << " then " << "1" << " else " << $3 << " <> 0";
        $$ = td.parse(in);
  }

  | LPAREN exps RPAREN {  $$ =  make_SeqExp(@$, $2); }
  | lvalue ASSIGN exp { $$ = make_AssignExp(@$, $1, $3); }
  | IF exp THEN exp ELSE exp { $$ = make_IfExp(@$, $2, $4, $6); }
  | IF exp THEN exp { $$ = make_IfExp(@$, $2, $4); }
  | WHILE exp DO exp { $$ = make_WhileExp(@$, $2, $4); }
  | FOR ID ASSIGN exp TO exp DO exp { $$ = make_ForExp(@$, make_VarDec(@$, $2, nullptr, $4), $6, $8); }
  | BREAK { $$ = make_BreakExp(@$); }
  | LET chunks IN exps END { $$ = make_LetExp(@$, $2, make_SeqExp(@$, $4)); }
  | EXP "(" INT ")" { $$ = metavar<ast::Exp>(td, $3); } // ADDITIONAL
  | CAST "(" exp "," ty ")" { $$ = make_CastExp(@$, $3, $5); } // ADDITIONAL
  ;

exp.1:
    %empty {$$ = make_Fieldinits_type();}
    | COMMA ID EQ exp exp.1 { $$ = $5; $$->emplace_back(make_FieldInit(@$, $2, $4)); }
    ;
exp.2:
    %empty { $$ = make_Fieldinits_type(); }
    | ID EQ exp exp.1 { $$ = $4; $$->emplace_back(make_FieldInit(@$, $1, $3));}
    ;
exp.3:
    %empty { $$ = make_exps_type(); }
    | exp exp.4 { $$ = $2; $$->insert($$->begin(), $1); }
    ;
exp.4:
    %empty { $$ = make_exps_type(); }
    | COMMA exp exp.4 { $$ = $3; $$->insert($$->begin(),$2); }
    ;

%token LVALUE "_lvalue";
lvalue:
    ID  { $$ = make_SimpleVar(@$, $1); }
    | lvalue DOT ID { $$ = make_FieldVar(@$, $1, $3); }
    | lvalue LBRACK exp RBRACK { $$ = make_SubscriptVar(@$, $1, $3); }
    | LVALUE "(" INT ")" { $$ = metavar<ast::Var>(td, $3); } // ADDITIONAL
    ;


/*---------------.
| Declarations.  |
`---------------*/

%token CHUNKS "_chunks";
chunks:
  /* Chunks are contiguous series of declarations of the same type
     (TypeDec, FunctionDec...) to which we allow certain specfic behavior like
     self referencing.
     They are held by a ChunkList, that can be empty, like in this case:
        let
        in
            ..
        end
     which is why we end the recursion with a %empty. */
  %empty                 { $$ = make_ChunkList(@$); }
 | chunk   chunks        { $$ = $2; $$->push_front($1); }
 | CHUNKS "(" INT ")" chunks { $$ = metavar<ast::ChunkList>(td, $3); $$->splice_back(*$5); }
 | IMPORT STRING chunks    { $$ = td.parse_import($2, @$); $$->splice_back(*$3); }
;

chunk:
    tychunk             { $$ = $1; }
    | funchunk          { $$ = $1; }
    | varchunk          { $$ = $1; }
    ;

funchunk:
    fundec %prec CHUNKS              { $$ = make_FunctionChunk(@1); $$->push_front(*$1); }
    |fundec funchunk                  { $$ = $2; $$->push_front(*$1); }
    ;


fundec:
    FUNCTION ID LPAREN tyfields.2 RPAREN EQ exp { $$ = make_FunctionDec(@$, $2, $4, nullptr, $7);}
    | FUNCTION ID LPAREN tyfields.2 RPAREN COLON typeid EQ exp { $$ = make_FunctionDec(@$, $2, $4, $7, $9);}
    | PRIMITIVE ID LPAREN tyfields.2 RPAREN COLON typeid { $$ = make_FunctionDec(@$, $2, $4, $7, nullptr);}
    | PRIMITIVE ID LPAREN tyfields.2 RPAREN  { $$ = make_FunctionDec(@$, $2, $4, nullptr, nullptr);}
    ;

varchunk:
    vardec              { $$ = make_VarChunk(@$); $$->emplace_back(*$1);}
    ;

vardec:
    VAR ID COLON typeid ASSIGN exp   { $$ = make_VarDec(@$, $2, $4, $6);}
    |VAR ID ASSIGN exp                { $$ = make_VarDec(@$, $2, nullptr, $4);}
    ;


/*--------------------.
| Type Declarations.  |
`--------------------*/

tychunk:
  /* Use `%prec CHUNKS' to do context-dependent precedence and resolve a
     shift-reduce conflict. */
  tydec %prec CHUNKS  { $$ = make_TypeChunk(@1); $$->push_front(*$1); }
| tydec tychunk       { $$ = $2; $$->push_front(*$1); }
;

tydec:
  "type" ID "=" ty { $$ = make_TypeDec(@$, $2, $4); }
;

ty:
  typeid               { $$ = $1; }
| "{" tyfields "}"     { $$ = make_RecordTy(@$, $2); }
| "array" "of" typeid  { $$ = make_ArrayTy(@$, $3); }
;

tyfields:
  %empty               { $$ = make_fields_type(); }
| tyfields.1           { $$ = $1; }
;



tyfields.1:
  tyfields.1 "," tyfield { $$ = $1; $$->emplace_back($3); }
| tyfield                { $$ = make_fields_type($1); }
;

tyfields.2:
  %empty               { $$ = make_VarChunk(@$); }
| tyfields.3           { $$ = $1; }
;



tyfields.3:
  tyfields.3 "," tyfield.2 { $$ = $1; $$->emplace_back(*$3); }
| tyfield.2                { $$ = make_VarChunk(@$); $$->emplace_back(*$1); }
;

tyfield:
  ID ":" typeid     { $$ = make_Field(@$, $1, $3); }
;

tyfield.2:
  ID ":" typeid     { $$ = make_VarDec(@$, $1, $3, nullptr); }
;


%token NAMETY "_namety";
typeid:
  ID                    { $$ = make_NameTy(@$, $1); }
  /* This is a metavariable. It it used internally by TWEASTs to retrieve
     already parsed nodes when given an input to parse. */
| NAMETY "(" INT ")"    { $$ = metavar<ast::NameTy>(td, $3); }
;


%%

void
parse::parser::error(const location_type& l, const std::string& m)
{
//not finished

  td.error_ << misc::error::error_type::parse        \
  << td.location_                         \
  << ":Parsing error\n";            \
  //<< misc::escape(text()) << "'\n";       \
  //std::cerr << "gramatical error\n";
  //_exit(3);
}
