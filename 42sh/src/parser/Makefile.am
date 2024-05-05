lib_LIBRARIES = libparser.a

libparser_a_SOURCES = parser.c parser.h \
					  $(top_builddir)/src/lexer/lexer.h \
					  $(top_builddir)/src/ast/ast.h
libparser_a_CFLAGS = -Wall -Wextra -Werror -Wvla -std=c99 -pedantic
