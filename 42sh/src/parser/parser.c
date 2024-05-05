#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static enum parser_status parse_list(struct ast_list **res,
                                     struct lexer *lexer);
static enum parser_status parse_and_or(struct ast_andor **res,
                                       struct lexer *lexer);
static enum parser_status parse_pipeline(struct ast_pipeline **res,
                                         struct lexer *lexer);
static enum parser_status parse_command(struct ast_cmd **res,
                                        struct lexer *lexer);
static enum parser_status parse_simple_command(struct ast_simplecmd **res,
                                               struct lexer *lexer);
static enum parser_status parse_element(struct ast_element **res,
                                        struct lexer *lexer);
static enum parser_status parse_shell_command(struct ast_shellcmd **res,
                                              struct lexer *lexer);
static enum parser_status parse_funcdec(struct ast_funcdec **res,
                                        struct lexer *lexer);
static enum parser_status parse_rule_if(struct ast_if **res,
                                        struct lexer *lexer);
static enum parser_status parse_else_clause(struct ast_else **res,
                                            struct lexer *lexer);
static enum parser_status parse_compound_list(struct ast_compound **res,
                                              struct lexer *lexer);
static enum parser_status parse_rule_for(struct ast_for **res,
                                         struct lexer *lexer);
static enum parser_status parse_redirection(struct ast_redir **res,
                                            struct lexer *lexer);
static enum parser_status parse_rule_while(struct ast_while **res,
                                           struct lexer *lexer);
static enum parser_status parse_rule_until(struct ast_until **res,
                                           struct lexer *lexer);
static enum parser_status parse_prefix(struct ast_prefix **res,
                                       struct lexer *lexer);

int number_args(char **args)
{
    if (!args)
        return 1;

    int i = 0;
    while (args[i] != NULL)
        i++;

    return i + 1;
}

enum parser_status parse(struct ast_input **res, struct lexer *lexer)
{
    *res = ast_new(AST_INPUT);
    // First case
    if (lexer_peek(lexer).type == TOKEN_EOF)
    {
        lexer_pop(lexer);
        return PARSER_OK;
    }

    if (lexer_peek(lexer).type == TOKEN_NEWLINE)
    {
        lexer_skip(lexer);
        return PARSER_OK;
    }

    if (parse_list(&(*res)->list, lexer) == PARSER_UNEXPECTED_TOKEN)
        return PARSER_UNEXPECTED_TOKEN;

    if (lexer_peek(lexer).type == TOKEN_EOF)
    {
        lexer_pop(lexer);
        return PARSER_OK;
    }

    if (lexer_peek(lexer).type == TOKEN_NEWLINE)
    {
        lexer_skip(lexer);
        return PARSER_OK;
    }

    fprintf(stderr, "parser: parse: no TOKEN_EOF find.\n");
    return PARSER_UNEXPECTED_TOKEN;
}

static enum parser_status parse_list(struct ast_list **res, struct lexer *lexer)
{
    (*res) = ast_new(AST_LIST);
    (*res)->nb = 1;
    (*res)->andor = malloc((*res)->nb * sizeof(struct ast_andor *));

    if (parse_and_or(&(*res)->andor[0], lexer) == PARSER_UNEXPECTED_TOKEN)
        return PARSER_UNEXPECTED_TOKEN;

    if (lexer_peek(lexer).type == TOKEN_POINTV)
    {
        while (lexer_peek(lexer).type == TOKEN_POINTV)
        {
            lexer_skip(lexer);

            (*res)->nb++;
            (*res)->andor =
                realloc((*res)->andor, (*res)->nb * sizeof(struct ast_andor *));

            (*res)->nb_data++;
            (*res)->data = realloc((*res)->data,
                                   (*res)->nb_data * sizeof(enum token_type));
            (*res)->data[(*res)->nb_data - 1] = TOKEN_POINTV;

            if (parse_and_or(&(*res)->andor[(*res)->nb - 1], lexer)
                == PARSER_UNEXPECTED_TOKEN)
            {
                free_andor((*res)->andor[(*res)->nb - 1]);
                (*res)->nb--;
                (*res)->andor = realloc(
                    (*res)->andor, (*res)->nb * sizeof(struct ast_andor *));
                break;
            }
        }
    }

    return PARSER_OK;
}

static enum parser_status parse_and_or(struct ast_andor **res,
                                       struct lexer *lexer)
{
    (*res) = ast_new(AST_ANDOR);
    (*res)->nb = 1;
    (*res)->pipeline = malloc((*res)->nb * sizeof(struct ast_pipeline *));

    if (parse_pipeline(&(*res)->pipeline[0], lexer) == PARSER_UNEXPECTED_TOKEN)
        return PARSER_UNEXPECTED_TOKEN;

    while (lexer_peek(lexer).type == TOKEN_ANDAND
           || lexer_peek(lexer).type == TOKEN_OROR)
    {
        // lexer_skip(lexer);

        (*res)->nb++;
        (*res)->pipeline =
            realloc((*res)->pipeline, (*res)->nb * sizeof(struct ast_pipeline));

        (*res)->data =
            realloc((*res)->data, ((*res)->nb - 1) * sizeof(enum token_type));
        (*res)->data[(*res)->nb - 2] = lexer_skip(lexer).type;

        while (lexer_peek(lexer).type == TOKEN_NEWLINE)
            lexer_skip(lexer);

        if (parse_pipeline(&(*res)->pipeline[(*res)->nb - 1], lexer)
            == PARSER_UNEXPECTED_TOKEN)
            return PARSER_UNEXPECTED_TOKEN;
    }

    return PARSER_OK;
}

static enum parser_status parse_pipeline(struct ast_pipeline **res,
                                         struct lexer *lexer)
{
    (*res) = ast_new(AST_CMD);

    if (lexer_peek(lexer).type == TOKEN_NEG)
    {
        (*res)->is_neg = 1;
        lexer_skip(lexer);
    }

    (*res)->nb = 1;
    (*res)->cmd = malloc(sizeof(struct ast_cmd));

    if (parse_command(&(*res)->cmd[0], lexer) == PARSER_UNEXPECTED_TOKEN)
        return PARSER_UNEXPECTED_TOKEN;

    while (lexer_peek(lexer).type == TOKEN_PIPE)
    {
        lexer_skip(lexer);

        (*res)->nb++;
        (*res)->cmd = realloc((*res)->cmd, (*res)->nb * sizeof(struct ast_cmd));

        while (lexer_peek(lexer).type == TOKEN_NEWLINE)
            lexer_skip(lexer);

        if (parse_command(&(*res)->cmd[(*res)->nb - 1], lexer)
            == PARSER_UNEXPECTED_TOKEN)
            return PARSER_UNEXPECTED_TOKEN;
    }

    return PARSER_OK;
}

static enum parser_status parse_command(struct ast_cmd **res,
                                        struct lexer *lexer)
{
    (*res) = ast_new(AST_CMD);
    (*res)->type = FUNCTION;

    if (parse_funcdec((struct ast_funcdec **)&(*res)->cmd, lexer) == PARSER_OK)
    {
        ((struct ast_funcdec *)(*res)->cmd)->is_check = 0;

        struct ast_redir *redir = NULL;
        while (parse_redirection(&redir, lexer) != PARSER_UNEXPECTED_TOKEN)
        {
            (*res)->nb++;
            (*res)->redir = realloc((*res)->redir,
                                    ((*res)->nb) * sizeof(struct ast_redir *));
            (*res)->redir[(*res)->nb - 1] = redir;
        }

        if (redir)
            free_redir((redir));
        return PARSER_OK;
    }

    free_cmd((*res));
    (*res) = ast_new(AST_CMD);
    (*res)->type = SIMPLE;
    if (parse_simple_command((struct ast_simplecmd **)&(*res)->cmd, lexer)
        == PARSER_OK)
        return PARSER_OK;

    free_cmd((*res));
    (*res) = ast_new(AST_CMD);
    (*res)->type = SHELL;

    if (parse_shell_command((struct ast_shellcmd **)&(*res)->cmd, lexer)
        == PARSER_OK)
    {
        struct ast_redir *redir = NULL;
        while (parse_redirection(&redir, lexer) != PARSER_UNEXPECTED_TOKEN)
        {
            (*res)->nb++;
            (*res)->redir = realloc((*res)->redir,
                                    ((*res)->nb) * sizeof(struct ast_redir *));
            (*res)->redir[(*res)->nb - 1] = redir;
        }

        if (redir)
            free_redir((redir));

        return PARSER_OK;
    }

    return PARSER_UNEXPECTED_TOKEN;
}

static enum parser_status parse_funcdec(struct ast_funcdec **res,
                                        struct lexer *lexer)
{
    (*res) = ast_new(AST_FUNCDEC);

    struct token token = lexer_peek(lexer);
    if (token.type != TOKEN_WORD)
        return PARSER_UNEXPECTED_TOKEN;

    token = lexer_pop(lexer);
    (*res)->word = token.args;

    if (lexer_pop(lexer).type != TOKEN_LEFT_PAR)
    {
        if (lexer->current_tok.type != TOKEN_EOF
            && lexer->current_tok.type != TOKEN_ERROR)
        {
            lexer->pos -= strlen(lexer->current_tok.args);
            free(lexer->current_tok.args);
        }

        while (lexer->input[lexer->pos - 1] == ' ')
            lexer->pos--;

        if (token.type != TOKEN_EOF && token.type != TOKEN_ERROR)
            lexer->pos -= strlen(token.args);

        return PARSER_UNEXPECTED_TOKEN;
    }

    free(lexer->current_tok.args);

    if (lexer_skip(lexer).type != TOKEN_RIGHT_PAR)
        return PARSER_UNEXPECTED_TOKEN;

    while (lexer_peek(lexer).type == TOKEN_NEWLINE)
        lexer_skip(lexer);

    return parse_shell_command(&(*res)->child, lexer);
}

static enum parser_status parse_simple_command_else(struct ast_simplecmd **res,
                                                    struct lexer *lexer,
                                                    struct ast_prefix *prefix)
{
    (*res)->nb_prefix++;
    (*res)->prefix =
        realloc((*res)->prefix, (*res)->nb_prefix * sizeof(struct ast_prefix));
    (*res)->prefix[0] = prefix;
    prefix = NULL;
    while (parse_prefix(&prefix, lexer) != PARSER_UNEXPECTED_TOKEN)
    {
        (*res)->nb_prefix++;
        (*res)->prefix = realloc((*res)->prefix,
                                 (*res)->nb_prefix * sizeof(struct ast_prefix));
        (*res)->prefix[(*res)->nb_prefix - 1] = prefix;
        prefix = NULL;
    }

    free_prefix(prefix);

    if (lexer_peek(lexer).type == TOKEN_WORD)
    {
        struct token token = lexer_pop(lexer);
        (*res)->is_word = 1;
        (*res)->word = token.args;

        struct ast_element *element = NULL;
        while (parse_element(&element, lexer) != PARSER_UNEXPECTED_TOKEN)
        {
            (*res)->nb_element++;
            (*res)->elements =
                realloc((*res)->elements,
                        (*res)->nb_element * sizeof(struct ast_element *));
            (*res)->elements[(*res)->nb_element - 1] = element;
            element = NULL;
        }
        free_element(element);
        return PARSER_OK;
    }
    return PARSER_OK;
}
static enum parser_status parse_simple_command(struct ast_simplecmd **res,
                                               struct lexer *lexer)
{
    (*res) = ast_new(AST_SIMPLECMD);
    struct ast_prefix *prefix = NULL;
    if (parse_prefix(&prefix, lexer) == PARSER_UNEXPECTED_TOKEN)
    {
        free_prefix(prefix);

        if (lexer_peek(lexer).type == TOKEN_WORD)
        {
            struct token token = lexer_pop(lexer);
            (*res)->is_word = 1;
            (*res)->word = token.args;

            struct ast_element *element = NULL;
            while (parse_element(&element, lexer) != PARSER_UNEXPECTED_TOKEN)
            {
                (*res)->nb_element++;
                (*res)->elements =
                    realloc((*res)->elements,
                            (*res)->nb_element * sizeof(struct ast_element *));
                (*res)->elements[(*res)->nb_element - 1] = element;
                element = NULL;
            }
            free_element(element);
            return PARSER_OK;
        }

        return PARSER_UNEXPECTED_TOKEN;
    }
    else
        return parse_simple_command_else(res, lexer, prefix);
}

int stop_word(enum token_type type)
{
    switch (type)
    {
    case TOKEN_PIPE:
    case TOKEN_ANDAND:
    case TOKEN_OROR:
    case TOKEN_POINTV:
    case TOKEN_EOF:
    case TOKEN_NEWLINE:
    case TOKEN_ERROR:
    case TOKEN_RIGHT_PAR:
        // case TOKEN_AND:
        return 1;
    default:
        return 0;
    }
}

static enum parser_status parse_element(struct ast_element **res,
                                        struct lexer *lexer)
{
    *res = ast_new(AST_ELEMENT);
    struct token token = lexer_peek(lexer);
    if (stop_word(token.type))
        return PARSER_UNEXPECTED_TOKEN;

    if (parse_redirection((struct ast_redir **)&(*res)->child, lexer)
        == PARSER_OK)
    {
        (*res)->is_redir = 1;
        return PARSER_OK;
    }

    free_redir((*res)->child);
    token = lexer_pop(lexer);
    (*res)->child = token.args;
    return PARSER_OK;
}

static enum parser_status parse_prefix(struct ast_prefix **res,
                                       struct lexer *lexer)
{
    *res = ast_new(AST_PREFIX);
    if (lexer_peek(lexer).type == TOKEN_ASSIGNMENT_WORD)
    {
        struct token token = lexer_pop(lexer);
        (*res)->child = token.args;

        return PARSER_OK;
    }

    (*res)->is_redir = 1;
    return parse_redirection((struct ast_redir **)&(*res)->child, lexer);
}

static enum parser_status parse_redirection(struct ast_redir **res,
                                            struct lexer *lexer)
{
    *res = ast_new(AST_REDIR);
    (*res)->io_number = -1;
    if (lexer_peek(lexer).type == TOKEN_IONUMBER)
    {
        struct token token = lexer_pop(lexer);
        (*res)->io_number = atoi(token.args);
        free(token.args);
    }

    if (lexer_peek(lexer).type != TOKEN_REDIRECTION)
        return PARSER_UNEXPECTED_TOKEN;

    struct token token = lexer_pop(lexer);
    (*res)->redir = token.args;

    if (lexer_peek(lexer).type != TOKEN_WORD)
        return PARSER_UNEXPECTED_TOKEN;

    token = lexer_pop(lexer);
    (*res)->word = token.args;

    return PARSER_OK;
}

static enum parser_status parse_shell_command_rule(struct ast_shellcmd **res,
                                                   struct lexer *lexer)
{
    (*res)->child_type = AST_IF;
    if (parse_rule_if((struct ast_if **)&(*res)->child, lexer) == PARSER_OK)
        return PARSER_OK;

    free_shellcmd((*res));
    (*res) = ast_new(AST_SHELLCMD);

    (*res)->child_type = AST_WHILE;
    if (parse_rule_while((struct ast_while **)&(*res)->child, lexer)
        == PARSER_OK)
        return PARSER_OK;

    free_shellcmd((*res));
    (*res) = ast_new(AST_SHELLCMD);

    (*res)->child_type = AST_UNTIL;
    if (parse_rule_until((struct ast_until **)&(*res)->child, lexer)
        == PARSER_OK)
        return PARSER_OK;

    free_shellcmd((*res));
    (*res) = ast_new(AST_SHELLCMD);

    (*res)->child_type = AST_FOR;
    if (parse_rule_for((struct ast_for **)&(*res)->child, lexer) == PARSER_OK)
        return PARSER_OK;

    free_shellcmd((*res));
    (*res) = ast_new(AST_SHELLCMD);

    return PARSER_UNEXPECTED_TOKEN;
}

static enum parser_status parse_shell_command(struct ast_shellcmd **res,
                                              struct lexer *lexer)
{
    (*res) = ast_new(AST_SHELLCMD);

    if (lexer_peek(lexer).type == TOKEN_LEFT_PAR)
    {
        (*res)->child_type = AST_COMPOUND;
        (*res)->is_subshell = 1;
        lexer_skip(lexer);

        if (parse_compound_list((struct ast_compound **)&(*res)->child, lexer)
            == PARSER_UNEXPECTED_TOKEN)
            return PARSER_UNEXPECTED_TOKEN;

        if (lexer_peek(lexer).type != TOKEN_RIGHT_PAR)
            return PARSER_UNEXPECTED_TOKEN;

        lexer_skip(lexer);

        return PARSER_OK;
    }

    if (lexer_peek(lexer).type == TOKEN_LEFT_BRACKET)
    {
        (*res)->child_type = AST_COMPOUND;
        lexer_skip(lexer);

        if (parse_compound_list((struct ast_compound **)&(*res)->child, lexer)
            == PARSER_UNEXPECTED_TOKEN)
            return PARSER_UNEXPECTED_TOKEN;

        if (lexer_peek(lexer).type != TOKEN_RIGHT_BRACKET)
            return PARSER_UNEXPECTED_TOKEN;

        lexer_skip(lexer);

        return PARSER_OK;
    }

    return parse_shell_command_rule(res, lexer);
}

static enum parser_status parse_rule_if(struct ast_if **res,
                                        struct lexer *lexer)
{
    *res = ast_new(AST_IF);
    if (lexer_peek(lexer).type != TOKEN_IF)
        return PARSER_UNEXPECTED_TOKEN;

    lexer_skip(lexer);

    if (parse_compound_list(&(*res)->condition, lexer)
        == PARSER_UNEXPECTED_TOKEN)
        return PARSER_UNEXPECTED_TOKEN;

    if (lexer_peek(lexer).type != TOKEN_THEN)
        return PARSER_UNEXPECTED_TOKEN;

    lexer_skip(lexer);

    if (parse_compound_list(&(*res)->compound, lexer)
        == PARSER_UNEXPECTED_TOKEN)
        return PARSER_UNEXPECTED_TOKEN;

    parse_else_clause(&(*res)->else_clause, lexer);

    if (lexer_peek(lexer).type != TOKEN_FI)
        return PARSER_UNEXPECTED_TOKEN;

    lexer_skip(lexer);

    return PARSER_OK;
}

static enum parser_status parse_else_clause(struct ast_else **res,
                                            struct lexer *lexer)
{
    struct token token = lexer_peek(lexer);
    if (token.type == TOKEN_ELSE)
    {
        *res = ast_new(AST_ELSE);
        (*res)->is_else = 1;
        lexer_skip(lexer);
        if (parse_compound_list(&(*res)->compound, lexer)
            == PARSER_UNEXPECTED_TOKEN)
            return PARSER_UNEXPECTED_TOKEN;

        return PARSER_OK;
    }
    else if (token.type == TOKEN_ELIF)
    {
        *res = ast_new(AST_ELSE);
        lexer_skip(lexer);

        if (parse_compound_list(&(*res)->condition, lexer)
            == PARSER_UNEXPECTED_TOKEN)
            return PARSER_UNEXPECTED_TOKEN;

        if (lexer_peek(lexer).type != TOKEN_THEN)
            return PARSER_UNEXPECTED_TOKEN;

        lexer_skip(lexer);

        if (parse_compound_list(&(*res)->compound, lexer)
            == PARSER_UNEXPECTED_TOKEN)
            return PARSER_UNEXPECTED_TOKEN;

        parse_else_clause(&(*res)->else_clause, lexer);

        return PARSER_OK;
    }

    return PARSER_UNEXPECTED_TOKEN;
}

static enum parser_status parse_rule_until(struct ast_until **res,
                                           struct lexer *lexer)
{
    *res = ast_new(AST_UNTIL);

    if (lexer_peek(lexer).type != TOKEN_UNTIL)
        return PARSER_UNEXPECTED_TOKEN;

    lexer_skip(lexer);

    if (parse_compound_list(&(*res)->condition, lexer)
        == PARSER_UNEXPECTED_TOKEN)
        return PARSER_UNEXPECTED_TOKEN;

    if (lexer_peek(lexer).type != TOKEN_DO)
        return PARSER_UNEXPECTED_TOKEN;

    lexer_skip(lexer);

    if (parse_compound_list(&(*res)->compound, lexer)
        == PARSER_UNEXPECTED_TOKEN)
        return PARSER_UNEXPECTED_TOKEN;

    if (lexer_peek(lexer).type != TOKEN_DONE)
        return PARSER_UNEXPECTED_TOKEN;

    lexer_skip(lexer);

    return PARSER_OK;
}

static enum parser_status parse_rule_while(struct ast_while **res,
                                           struct lexer *lexer)
{
    *res = ast_new(AST_WHILE);

    if (lexer_peek(lexer).type != TOKEN_WHILE)
        return PARSER_UNEXPECTED_TOKEN;

    lexer_skip(lexer);

    if (parse_compound_list(&(*res)->condition, lexer)
        == PARSER_UNEXPECTED_TOKEN)
        return PARSER_UNEXPECTED_TOKEN;

    if (lexer_peek(lexer).type != TOKEN_DO)
        return PARSER_UNEXPECTED_TOKEN;

    lexer_skip(lexer);

    if (parse_compound_list(&(*res)->compound, lexer)
        == PARSER_UNEXPECTED_TOKEN)
        return PARSER_UNEXPECTED_TOKEN;

    if (lexer_peek(lexer).type != TOKEN_DONE)
        return PARSER_UNEXPECTED_TOKEN;

    lexer_skip(lexer);

    return PARSER_OK;
}

static enum parser_status parse_rule_for(struct ast_for **res,
                                         struct lexer *lexer)
{
    *res = ast_new(AST_FOR);

    if (lexer_peek(lexer).type != TOKEN_FOR)
        return PARSER_UNEXPECTED_TOKEN;

    lexer_skip(lexer);

    if (lexer_peek(lexer).type != TOKEN_WORD)
        return PARSER_UNEXPECTED_TOKEN;

    struct token token = lexer_pop(lexer);
    (*res)->word = token.args;

    if (lexer_peek(lexer).type == TOKEN_POINTV)
        lexer_skip(lexer);

    else
    {
        while (lexer_peek(lexer).type == TOKEN_NEWLINE)
            lexer_skip(lexer);

        if (lexer_peek(lexer).type == TOKEN_IN)
        {
            lexer_skip(lexer);

            while (lexer_peek(lexer).type == TOKEN_WORD)
            {
                struct token token = lexer_pop(lexer);
                (*res)->nb++;
                (*res)->words =
                    realloc((*res)->words, (*res)->nb * sizeof(struct word *));
                (*res)->words[(*res)->nb - 1] = token.args;
            }

            if (lexer_peek(lexer).type != TOKEN_POINTV
                && lexer_peek(lexer).type != TOKEN_NEWLINE)
                return PARSER_UNEXPECTED_TOKEN;

            lexer_skip(lexer);
        }
    }

    while (lexer_peek(lexer).type == TOKEN_NEWLINE)
        lexer_skip(lexer);

    if (lexer_peek(lexer).type != TOKEN_DO)
        return PARSER_UNEXPECTED_TOKEN;

    lexer_skip(lexer);

    if (parse_compound_list(&(*res)->compound, lexer)
        == PARSER_UNEXPECTED_TOKEN)
        return PARSER_UNEXPECTED_TOKEN;

    if (lexer_peek(lexer).type != TOKEN_DONE)
        return PARSER_UNEXPECTED_TOKEN;

    lexer_skip(lexer);

    return PARSER_OK;
}

static enum parser_status parse_compound_list(struct ast_compound **res,
                                              struct lexer *lexer)
{
    *res = ast_new(AST_COMPOUND);
    (*res)->nb++;
    (*res)->andor = malloc((*res)->nb * sizeof(struct ast_andor *));

    while (lexer_peek(lexer).type == TOKEN_NEWLINE)
        lexer_skip(lexer);

    if (parse_and_or(&(*res)->andor[0], lexer) == PARSER_UNEXPECTED_TOKEN)
        return PARSER_UNEXPECTED_TOKEN;

    while (1)
    {
        struct token token = lexer_peek(lexer);
        if (token.type == TOKEN_POINTV || token.type == TOKEN_NEWLINE)
        {
            token = lexer_skip(lexer);
            (*res)->nb_data++;
            (*res)->data =
                realloc((*res)->data, (*res)->nb * sizeof(enum token_type));
            (*res)->data[(*res)->nb_data - 1] = token.type;

            while (lexer_peek(lexer).type == TOKEN_NEWLINE)
                lexer_skip(lexer);

            (*res)->nb++;
            (*res)->andor =
                realloc((*res)->andor, (*res)->nb * sizeof(struct ast_andor *));
            if (parse_and_or(&(*res)->andor[(*res)->nb - 1], lexer)
                == PARSER_UNEXPECTED_TOKEN)
            {
                free_andor((*res)->andor[(*res)->nb - 1]);
                (*res)->nb--;
                (*res)->andor = realloc(
                    (*res)->andor, (*res)->nb * sizeof(struct ast_andor *));

                return PARSER_OK;
            }
        }
        else if (token.type == TOKEN_ERROR)
            return PARSER_UNEXPECTED_TOKEN;
        else
            return PARSER_OK;
    }
}
