#include "lexer.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../io/io.h"

struct lexer *lexer_new(char *input)
{
    if (!input)
        return NULL;

    struct lexer *lex = malloc(sizeof(struct lexer));
    if (!lex)
        return NULL;
    lex->input = input;
    lex->pos = 0;
    lex->max_pos = strlen(input);
    lex->stream = NULL;

    return lex;
}

struct lexer *lexer_new_fd(char *path)
{
    struct lexer *lex = malloc(sizeof(struct lexer));
    if (!lex)
        return NULL;

    lex->input = NULL;
    lex->stream = NULL;
    lex->stream = io_setup_lexer(path, lex);

    if (lex->stream == NULL || io_getline(lex) == -1)
    {
        free(lex);
        return NULL;
    }

    lex->pos = 0;

    return lex;
}

void lexer_free(struct lexer *lexer)
{
    if (!lexer)
        return;

    if (lexer->stream)
        free(lexer->input);

    free(lexer);
}

static int is_operator(char test)
{
    if (test != '&' && test != '(' && test != ')' && test != ';' && test != '\n'
        && test != '|' && test != '<' && test != '>' && test != '!'
        && test != '{' && test != '}')
        return 0;
    else
        return 1;
}

static int is_operator_2(char *test)
{
    int return_value = 0;
    if (!strncmp(test, "&&", 2))
    {
        return_value = 1;
    }
    else if (!strncmp(test, "||", 2))
    {
        return_value = 1;
    }
    else if (!strncmp(test, "<<", 2))
    {
        return_value = 1;
    }
    else if (!strncmp(test, ">>", 2))
    {
        return_value = 1;
    }
    else if (!strncmp(test, "<&", 2))
    {
        return_value = 1;
    }
    else if (!strncmp(test, ">&", 2))
    {
        return_value = 1;
    }
    else if (!strncmp(test, "<>", 2))
    {
        return_value = 1;
    }
    else if (!strncmp(test, ">|", 2))
    {
        return_value = 1;
    }
    return return_value;
}

static int is_redirection(char *test)
{
    int return_value = 0;
    if (!strncmp(test, ">", 2))
    {
        return_value = 1;
    }
    else if (!strncmp(test, "<", 2))
    {
        return_value = 1;
    }
    else if (!strncmp(test, ">>", 3))
    {
        return_value = 1;
    }
    else if (!strncmp(test, ">&", 3))
    {
        return_value = 1;
    }
    else if (!strncmp(test, "<&", 3))
    {
        return_value = 1;
    }
    else if (!strncmp(test, ">|", 3))
    {
        return_value = 1;
    }
    else if (!strncmp(test, "<>", 3))
    {
        return_value = 1;
    }
    return return_value;
}

static int is_special_for_double_quote(char test)
{
    if (test == '$' || test == '`' || test == '\"' || test == '\\'
        || test == '\n')
        return 1;
    return 0;
}

static int get_word_single_quote(struct lexer *lexer, int *i)
{
    *i += 1;
    int j = 0;
    while (lexer->pos + *i < lexer->max_pos)
    {
        if (lexer->input[lexer->pos + (*i)++] == '\'')
        {
            j = 1;
            break;
        }
    }
    // cas : unmatched single quote
    if (!j)
        return 1;
    return 0;
}

static int get_word_dollar_bracket(struct lexer *lexer, int *i)
{
    *i += 2;
    if ((lexer->input[lexer->pos + *i] == '$'
         || lexer->input[lexer->pos + *i] == '?')
        && lexer->input[lexer->pos + *i + 1] == '}')
    {
        *i += 2;
    }
    else if (isdigit(lexer->input[lexer->pos + *i]))
    {
        int k = 0;
        int j = 0;
        while (lexer->pos + *i + k < lexer->max_pos)
        {
            if (lexer->input[lexer->pos + *i + k] == '}')
            {
                break;
            }
            if (!isdigit(lexer->input[lexer->pos + *i + k]))
            {
                j = 1;
                break;
            }
            k++;
        }
        if (j)
            return 1;
        else
        {
            *i += k + 1;
        }
    }
    else if (isalpha(lexer->input[lexer->pos + *i])
             || lexer->input[lexer->pos + *i] == '_')
    {
        *i += 1;
        while (lexer->input[lexer->pos + *i] != '}')
        {
            if (!isalnum(lexer->input[lexer->pos + *i])
                && lexer->input[lexer->pos + *i] != '_')
                return 1;
            *i += 1;
        }
        *i += 1;
    }
    else
    {
        return 1;
    }
    return 0; // 0 = OK; 1 = NULL;
}

static char *get_word_while(struct lexer *lexer, int i)
{
    while (lexer->pos + i < lexer->max_pos
           && is_operator(lexer->input[lexer->pos + i]) != 1
           && lexer->input[lexer->pos + i] != ' '
           && lexer->input[lexer->pos + i] != '\t')
    {
        if (lexer->input[lexer->pos + i] == '\\')
        {
            i += 2;
        }
        else if (lexer->input[lexer->pos + i] == '\'')
        {
            if (get_word_single_quote(lexer, &i))
                return NULL;
        }
        else if (lexer->input[lexer->pos + i] == '\"')
        {
            i++;
            int j = 0;
            while (lexer->pos + i < lexer->max_pos)
            {
                if (lexer->input[lexer->pos + i] == '\\'
                    && is_special_for_double_quote(
                        lexer->input[lexer->pos + i + 1]))
                {
                    i += 2;
                }
                else if (lexer->input[lexer->pos + i] == '\"')
                {
                    i++;
                    j = 1;
                    break;
                }
                else if (lexer->input[lexer->pos + i] == '$'
                         && lexer->input[lexer->pos + i + 1] == '{')
                {
                    if (get_word_dollar_bracket(lexer, &i))
                        return NULL;
                }
                else
                {
                    i++;
                }
            }
            if (!j)
                return NULL;
        }
        else if (lexer->input[lexer->pos + i] == '$'
                 && lexer->input[lexer->pos + i + 1] == '{')
        {
            if (get_word_dollar_bracket(lexer, &i))
                return NULL;
        }
        else
        {
            i++;
        }
    }
    char *newword = calloc(i + 1, sizeof(char));
    newword = strncpy(newword, lexer->input + lexer->pos, i);
    return newword;
}

static char *get_word(struct lexer *lexer)
{
    if (!lexer)
        return NULL;
    size_t i = 0;

    if (is_operator(lexer->input[lexer->pos + i]) != 0
        && lexer->input[lexer->pos + i] != ' '
        && lexer->input[lexer->pos + i] != '\t')
    {
        if (lexer->pos + i < lexer->max_pos
            && is_operator_2(lexer->input + lexer->pos + i))
        {
            i += 2;
        }
        else
        {
            i++;
        }
    }
    else
    {
        return get_word_while(lexer, i);
    }
    char *newword = calloc(i + 1, sizeof(char));
    newword = strncpy(newword, lexer->input + lexer->pos, i);
    return newword;
}

static int is_assignment_word(char *word)
{
    size_t pos = 0;
    if (isalpha(word[pos]) || word[pos] == '_')
    {
        pos++;
    }
    else
    {
        return 0;
    }
    while (word[pos] != '=')
    {
        if (!isalnum(word[pos]) && word[pos] != '_')
            return 0;
        pos++;
    }
    return 1;
}

static int is_ionumber(char *word, struct lexer *lexer)
{
    size_t pos = 0;
    while (isdigit(word[pos]))
    {
        pos++;
    }
    if (word[pos] != '\0')
        return 0;
    size_t len = strlen(word);
    if (lexer->input[lexer->pos + len] == '<'
        || lexer->input[lexer->pos + len] == '>')
        return 1;
    return 0;
}

static struct token get_token_2(char *word, struct lexer *lexer)
{
    struct token token;
    token.args = word;
    if (!strncmp(word, "||", 3))
        token.type = TOKEN_OROR;
    else if (!strncmp(word, "!", 2))
        token.type = TOKEN_NEG;
    else if (!strncmp(word, "for", 4))
        token.type = TOKEN_FOR;
    else if (!strncmp(word, "in", 3))
        token.type = TOKEN_IN;
    else if (!strncmp(word, "\n", 2))
        token.type = TOKEN_NEWLINE;
    else if (!strncmp(word, "{", 2))
        token.type = TOKEN_LEFT_BRACKET;
    else if (!strncmp(word, "}", 2))
        token.type = TOKEN_RIGHT_BRACKET;
    else if (!strncmp(word, "(", 2))
        token.type = TOKEN_LEFT_PAR;
    else if (!strncmp(word, ")", 2))
        token.type = TOKEN_RIGHT_PAR;
    else if (is_redirection(word))
        token.type = TOKEN_REDIRECTION;
    else
    {
        if (is_assignment_word(word))
        {
            token.type = TOKEN_ASSIGNMENT_WORD;
        }
        else if (is_ionumber(word, lexer))
        {
            token.type = TOKEN_IONUMBER;
        }
        else
        {
            token.type = TOKEN_WORD;
        }
    }
    return token;
}

static struct token get_token(struct lexer *lexer)
{
    struct token token;
    token.args = NULL;

    char *word = get_word(lexer);

    if (word == NULL)
    {
        fprintf(stderr, "lexer: Undefined case: missing quote/double quote\n");
        token.type = TOKEN_ERROR;
        return token;
    }

    token.args = word;
    if (!strncmp(word, "if", 3))
        token.type = TOKEN_IF;
    else if (!strncmp(word, "fi", 3))
        token.type = TOKEN_FI;
    else if (!strncmp(word, "elif", 5))
        token.type = TOKEN_ELIF;
    else if (!strncmp(word, "else", 5))
        token.type = TOKEN_ELSE;
    else if (!strncmp(word, "then", 5))
        token.type = TOKEN_THEN;
    else if (!strncmp(word, "until", 6))
        token.type = TOKEN_UNTIL;
    else if (!strncmp(word, "while", 6))
        token.type = TOKEN_WHILE;
    else if (!strncmp(word, "done", 5))
        token.type = TOKEN_DONE;
    else if (!strncmp(word, "do", 3))
        token.type = TOKEN_DO;
    else if (!strncmp(word, ";", 2))
        token.type = TOKEN_POINTV;
    else if (!strncmp(word, "|", 2))
        token.type = TOKEN_PIPE;
    else if (!strncmp(word, "&&", 3))
        token.type = TOKEN_ANDAND;
    else
        return get_token_2(word, lexer);
    return token;
}

static void comment_skipper(struct lexer *lexer)
{
    while (lexer->pos != lexer->max_pos && lexer->input[lexer->pos] != '\n')
    {
        lexer->pos++;
    }
}

struct token parse_input_for_tok(struct lexer *lexer)
{
    while (lexer->pos < lexer->max_pos
           && (lexer->input[lexer->pos] == ' '
               || lexer->input[lexer->pos] == '\t'))
    {
        lexer->pos++;
    }

    if (lexer->pos < lexer->max_pos && (lexer->input[lexer->pos] == '#'))
    {
        comment_skipper(lexer);
    }

    if (lexer->pos == lexer->max_pos)
    {
        if (!lexer->stream || io_getline(lexer) == -1)
        {
            struct token token;
            token.type = TOKEN_EOF;
            return token;
        }
        return parse_input_for_tok(lexer);
    }

    return get_token(lexer);
}

/*
#phllawiain
*/

struct token lexer_peek(struct lexer *lexer)
{
    if (!lexer)
    {
        struct token token;
        fprintf(stderr, "lexer: parse_input_for_tok(): lexer is null\n");
        token.type = TOKEN_ERROR;
        return token;
    }

    lexer->current_tok = parse_input_for_tok(lexer);
    if (lexer->current_tok.type != TOKEN_EOF
        && lexer->current_tok.type != TOKEN_ERROR)
        free(lexer->current_tok.args);
    lexer->current_tok.args = NULL;
    return lexer->current_tok;
}

struct token lexer_pop(struct lexer *lexer)
{
    if (!lexer)
    {
        struct token token;
        fprintf(stderr, "lexer: parse_input_for_tok(): lexer is null\n");
        token.type = TOKEN_ERROR;
        return token;
    }

    lexer->current_tok = parse_input_for_tok(lexer);
    if (lexer->current_tok.type != TOKEN_EOF
        && lexer->current_tok.type != TOKEN_ERROR)
        lexer->pos += strlen(lexer->current_tok.args);

    return lexer->current_tok;
}

struct token lexer_skip(struct lexer *lexer)
{
    if (!lexer)
    {
        struct token token;
        fprintf(stderr, "lexer: parse_input_for_tok(): lexer is null\n");
        token.type = TOKEN_ERROR;
        return token;
    }

    lexer->current_tok = parse_input_for_tok(lexer);
    if (lexer->current_tok.type != TOKEN_EOF
        && lexer->current_tok.type != TOKEN_ERROR)
    {
        lexer->pos += strlen(lexer->current_tok.args);
        free(lexer->current_tok.args);
    }
    lexer->current_tok.args = NULL;

    return lexer->current_tok;
}
