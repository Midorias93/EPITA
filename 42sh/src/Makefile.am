bin_PROGRAMS = 42sh

SUBDIRS = \
	ast \
	builtin \
	evaluate \
	expansion \
	io \
	lexer \
	parser \
	exec \
	variable \
	my-redir \
	function

42sh_SOURCES = \
		main.c \
		ast/ast.c \
		builtin/builtin.c \
		evaluate/evaluate.c \
		expansion/expansion.c \
		lexer/lexer.c \
		parser/parser.c \
		io/io.c \
		exec/exec.c \
		variable/variable.c \
		my-redir/my_redir.c \
		my-redir/my_redir_left.c \
		my-redir/my_redir_right.c \
		function/function.c \
		ast/ast.h \
		builtin/builtin.h \
		evaluate/evaluate.h \
		expansion/expansion.h \
		lexer/lexer.h \
		parser/parser.h \
		io/io.h \
		exec/exec.h \
		variable/variable.h \
		my-redir/my_redir.h \
		function/function.h
42sh_LDADD = \
	ast/libast.a \
	builtin/libbuiltin.a \
	evaluate/libevaluate.a \
	expansion/libexpansion.a \
	io/libio.a \
	lexer/liblexer.a \
	parser/libparser.a \
	variable/libvariable.a \
	exec/libexec.a \
	my-redir/libmy_redir.a \
	function/libfunction.a
42sh_CFLAGS = -Wall -Wextra -Werror -std=c99 -pedantic -Wvla
