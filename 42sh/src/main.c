#include <stdlib.h>
#include <string.h>

#include "evaluate/evaluate.h"
#include "exec/exec.h"
#include "function/function.h"
#include "io/io.h"
#include "lexer/lexer.h"
#include "lexer/token.h"
#include "parser/parser.h"
#include "variable/variable.h"

struct wrp
{
    struct lexer *lexer;
    struct ast_input *ast;
    struct function *fnc;
    struct variable *list;
};

static void free_all(struct wrp *wrp)
{
    if (wrp->fnc)
        free_function(wrp->fnc);

    if (wrp->list)
        free_variable(wrp->list);

    if (wrp->lexer)
    {
        io_close(wrp->lexer->stream);
        lexer_free(wrp->lexer);
    }

    if (wrp->ast)
        ast_free(wrp->ast);
}

static int lexer_init(int argc, char *argv[], struct wrp *wrp)
{
    if (argc == 1)
        wrp->lexer = lexer_new_fd(NULL);

    else if (argc > 2 && !strcmp(argv[1], "-c"))
    {
        if (argc == 2)
        {
            fprintf(stderr, "42sh: -c: option requires an argument");
            return -1;
        }

        else
            wrp->lexer = lexer_new(argv[2]);
    }

    else
    {
        wrp->lexer = lexer_new_fd(argv[1]);
        argument_variable(wrp->list, argv, argc, 1);
        if (!wrp->lexer)
            return -2;
    }

    if (!wrp->lexer)
    {
        free_variable(wrp->list);
        return 0;
    }

    return 1;
}

static int while_loop(struct wrp *wrp, int print)
{
    int return_value = 0;

    while (lexer_peek(wrp->lexer).type != TOKEN_EOF)
    {
        enum parser_status status = parse(&wrp->ast, wrp->lexer);

        if (status != PARSER_OK)
            return -42;

        if (print)
            ast_print(wrp->ast);

        if ((return_value = evaluate(wrp->ast, wrp->list, wrp->fnc)) == -1)
            fprintf(stderr, "evaluate: error evaluate\n");
        else if (return_value == -127)
            fprintf(stderr, "evaluate: command does not exists\n");
        else if (return_value == EXIT)
        {
            ast_free(wrp->ast);
            wrp->ast = NULL;
            break;
        }

        ast_free(wrp->ast);
        wrp->ast = NULL;
    }

    return return_value;
}

static int wrapped(struct wrp *wrp, int print, int argc, char *argv[])
{
    int lexer_value;
    if ((lexer_value = lexer_init(argc, argv, wrp)) <= 0)
    {
        if (lexer_value == 0)
            return 0;

        else if (lexer_value == -1)
            goto error_no_input;

        else if (lexer_value == -2)
            goto error_no_file;
    }

    int return_value = while_loop(wrp, print);

    if (return_value == -1)
        goto error_evaluate;

    else if (return_value == -127)
        goto error_command;

    else if (return_value == -42)
        goto error_parse;

    char *ret = give_variable(wrp->list, "?", 1);
    if (ret)
        return_value = atoi(ret);

    free_all(wrp);

    return return_value;

error_evaluate:
    free_all(wrp);
    // fprintf(stderr, "evaluate: error evaluate\n");
    return 1;
error_parse:
    free_all(wrp);
    fprintf(stderr, "parse: error parsing\n");
    return 2;
error_command:
    free_all(wrp);
    // fprintf(stderr, "evaluate: command does not exists\n");
    return 127;
error_no_input:
    free_all(wrp);
    fprintf(stderr, "42sh: need an input after -c\n");
    return 2;
error_no_file:
    free_all(wrp);
    fprintf(stderr, "42sh: file does not exist\n");
    return 127;
}

int main(int argc, char *argv[])
{
    struct ast_input *ast = NULL;
    struct lexer *lexer = NULL;
    struct variable *list = init_variable();
    struct function *fnc = calloc(1, sizeof(struct function));

    int print = 0;

    if (argc > 1 && !strcmp(argv[1], "--pretty-print"))
    {
        print = 1;
        for (int i = 1; i < argc - 1; i++)
            argv[i] = argv[i + 1];

        argv[argc - 1] = NULL;
        argc--;
    }

    struct wrp *wrp = malloc(sizeof(struct wrp));
    wrp->lexer = lexer;
    wrp->ast = ast;
    wrp->fnc = fnc;
    wrp->list = list;

    int ret = wrapped(wrp, print, argc, argv);

    free(wrp);

    return ret;
}
