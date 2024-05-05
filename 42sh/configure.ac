AC_INIT([42sh], [1.0], [ewan.schwaller@epita.fr])
AM_INIT_AUTOMAKE([subdir-objects] [foreign])

AC_PROG_CC
AX_COMPILER_FLAGS([], [], [], [-Wall -Wextra -Werror -std=c99 -pedantic -Wvla])

AC_PROG_RANLIB

AC_CONFIG_FILES([
    Makefile
    src/Makefile
	src/ast/Makefile
	src/builtin/Makefile
	src/evaluate/Makefile
	src/expansion/Makefile
	src/io/Makefile
	src/lexer/Makefile
	src/parser/Makefile
	src/exec/Makefile
    src/variable/Makefile
    src/my-redir/Makefile
    src/function/Makefile
    ])

AC_OUTPUT
