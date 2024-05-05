#!/bin/sh

[ -z "$1" ] && echo "$0: Missing input file" && exit
[ -z "$2" ] && echo "$0: Missing output file" && exit

input=$1
output=$2

awk 'BEGIN {
      print("#include \"parse/tiger-driver.hh\"");
      print("");
      print("namespace parse");
      print("{");
      print("  const char* TigerDriver::prelude () const");
      print("  {");
      print("    return");
      printf("R\"(");
    }
    /^#(<<|>>)/ {
      next;
    }
    {
      print($0);
    }
    END {
      print(")\";");
      print("  }");
      print("} // namespace parse");
    }' "$input" > "$output".tmp

mv "$output".tmp "$output"
