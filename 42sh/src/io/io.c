#define _POSIX_C_SOURCE 200809L
#include "io.h"

#include <stdio.h>
#include <stdlib.h>

static void lexer_input_modif(char *line, struct lexer *lexer,
                              ssize_t size_line);

FILE *io_setup_lexer(const char *path, struct lexer *lexer)
{
    if (!lexer->stream)
    {
        FILE *stream = stdin;
        if (path != NULL)
        {
            stream = fopen(path, "r");
            if (!stream)
                return NULL;
        }
        lexer->stream = stream;
        return stream;
    }
    else
    {
        return lexer->stream;
    }
}

static void lexer_input_modif(char *line, struct lexer *lexer,
                              ssize_t size_line)
{
    if (lexer->input != NULL)
    {
        free(lexer->input);
    }
    lexer->input = line;
    lexer->pos = 0;
    lexer->max_pos = size_line;
}

int io_getline(struct lexer *lexer)
{
    if (lexer->stream == NULL)
    {
        return -1;
    }
    size_t size_buffer = 0;
    char *line = NULL;
    ssize_t size_line = getdelim(&line, &size_buffer, '\n', lexer->stream);
    if (size_line == -1)
    {
        if (lexer->input != NULL)
        {
            free(lexer->input);
        }
        free(line);
        lexer->input = NULL;
        return -1;
    }
    else
    {
        lexer_input_modif(line, lexer, size_line);
        return 0;
    }
}

void io_close(FILE *stream)
{
    if (stream && stream != stdin)
    {
        fclose(stream);
    }
}
