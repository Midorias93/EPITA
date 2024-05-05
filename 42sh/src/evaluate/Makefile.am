lib_LIBRARIES = libevaluate.a

libevaluate_a_SOURCES = \
	evaluate.c \
	evaluate.h \
	$(top_builddir)/src/ast/ast.h \
	$(top_builddir)/src/parser/parser.h \
	$(top_builddir)/src/expansion/expansion.h \
	$(top_builddir)/src/builtin/builtin.h
libevaluate_a_CFLAGS = -Wall -Wextra -Werror -Wvla -std=c99 -pedantic
