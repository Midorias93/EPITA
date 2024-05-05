* README

Tiger Abstract Syntax Tree nodes with their principal members.
Incomplete classes are tagged with a `*'.

/Ast/               (Location location)
  /Dec/             (symbol name)
    FunctionDec     (VarChunk formals, NameTy result, Exp body)
      MethodDec     ()
    TypeDec         (Ty ty)
    VarDec          (NameTy type_name, Exp init)

  /Exp/             ()
    /Var/           ()
      FieldVar      (Var var, symbol name)
      SimpleVar     (symbol name)
      SubscriptVar  (Var var, Exp index)

    ArrayExp        (NameTy type_name, Exp size, Exp init)
    AssignExp       (Var var, Exp exp)
    BreakExp        ()
    CallExp         (symbol name, exps_type args)
      MethodCallExp (Var object)
    CastExp         (Exp exp, Ty ty)
    ForExp          (VarDec vardec, Exp hi, Exp body)
    IfExp           (Exp test, Exp thenclause, Exp elseclause)
    IntExp          (int value)
    LetExp          (ChunkList chunks, Exp body)
    NilExp          ()
    ObjectExp       (NameTy type_name)
    OpExp           (Exp left, Oper oper, Exp right)
    RecordExp       (NameTy type_name, fieldinits_type fields)
    SeqExp          (exps_type exps)
    StringExp       (string value)
    WhileExp        (Exp test, Exp body)

  /Ty/              ()
    ArrayTy         (NameTy base_type)
    ClassTy         (NameTy super, ChunkList chunks)
    NameTy          (symbol name)
    RecordTy        (fields_type fields)

  ChunkList         (list_type chunks)

  Field             (symbol name, NameTy type_name)

  FieldInit         (symbol name, Exp init)


Some of these classes also inherit from other classes.

/Escapable/
  VarDec            (NameTy type_name, Exp init)

/Typable/
  /Dec/             (symbol name)
  /Exp/             ()
  /Ty/              ()

/TypeConstructor/
  /Ty/              ()
  FunctionDec       (VarChunk formals, NameTy result, Exp body)
  NilExp            ()
  TypeDec           (Ty ty)

