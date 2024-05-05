#include "evaluate.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "../builtin/builtin.h"
#include "../exec/exec.h"
#include "../expansion/expansion.h"
#include "../my-redir/my_redir.h"
#include "../parser/parser.h"

static int evaluate_andor(struct ast_andor *ast, struct variable *list,
                          struct function *fnc, int is_breakable);
static int evaluate_compound(struct ast_compound *ast, struct variable *list,
                             struct function *fnc, int is_breakable)
{
    int value = -1;
    for (int i = 0; i < ast->nb; i++)
    {
        value = evaluate_andor(ast->andor[i], list, fnc, is_breakable);
        if (value == EXIT)
            return EXIT;
        if (value >= BREAK_TO_END)
        {
            if (is_breakable)
                return value;
            // fprintf(stderr, "eval_else: break/continue is only for loops
            // \n");
        }
    }

    return value;
}

static int evaluate_else(struct ast_else *ast, struct variable *list,
                         struct function *fnc, int is_breakable)
{
    if (ast->is_else)
        return evaluate_compound(ast->compound, list, fnc, is_breakable);

    int value = evaluate_compound(ast->condition, list, fnc, is_breakable);
    if (value == EXIT)
        return EXIT;
    if (value >= BREAK_TO_END)
    {
        if (is_breakable)
            return value;
        // fprintf(stderr, "eval_else: break/continue is only for loops \n");
    }
    if (!value)
        return evaluate_compound(ast->compound, list, fnc, is_breakable);

    else if (ast->else_clause)
        return evaluate_else(ast->else_clause, list, fnc, is_breakable);

    return 0;
}

static int evaluate_if(struct ast_if *ast, struct variable *list,
                       struct function *fnc, int is_breakable)
{
    int value = evaluate_compound(ast->condition, list, fnc, is_breakable);
    if (value == EXIT)
        return EXIT;
    if (value >= BREAK_TO_END)
    {
        if (is_breakable)
            return value;
        // fprintf(stderr, "eval_if: break/continue is only for loops \n");
    }

    if (!value)
        return evaluate_compound(ast->compound, list, fnc, is_breakable);

    else if (ast->else_clause)
        return evaluate_else(ast->else_clause, list, fnc, is_breakable);

    return 0;
}

static int evaluate_until(struct ast_until *ast, struct variable *list,
                          struct function *fnc, int is_breakable)
{
    int value;
    while ((value = evaluate_compound(ast->condition, list, fnc, is_breakable))
               != BREAK
           && value != EXIT && value > 0)
    {
        value = evaluate_compound(ast->compound, list, fnc, is_breakable);

        if (value == EXIT)
            return EXIT;
        if (value == BREAK_TO_END)
        {
            return value;
        }
        if (is_break(value))
        {
            return get_correct_value(value);
        }
        if (is_continue(value))
        {
            if (is_breakable == 1 || value == CONTINUE)
                continue;
            return get_correct_value(value);
        }
    }

    return 0;
}

static int evaluate_for(struct ast_for *ast, struct variable *list,
                        struct function *fnc, int is_breakable)
{
    for (int i = 0; i < ast->nb; i++)
    {
        // Create variable
        special_append(list, ast->word, ast->words[i]);

        // Evaluate compound
        int value = evaluate_compound(ast->compound, list, fnc, is_breakable);
        if (value == EXIT)
            return EXIT;
        if (value == BREAK_TO_END)
        {
            return value;
        }
        if (is_break(value))
        {
            return get_correct_value(value);
        }
        if (is_continue(value))
        {
            if (is_breakable == 1 || value == CONTINUE)
                continue;
            return get_correct_value(value);
        }
    }

    return 0;
}

static int evaluate_while(struct ast_while *ast, struct variable *list,
                          struct function *fnc, int is_breakable)
{
    int value;
    while ((value = evaluate_compound(ast->condition, list, fnc, is_breakable))
               != BREAK
           && value != EXIT && value == 0)
    {
        value = evaluate_compound(ast->compound, list, fnc, is_breakable);
        if (value == EXIT)
            return EXIT;
        if (value == BREAK_TO_END)
        {
            return value;
        }
        if (is_break(value))
        {
            return get_correct_value(value);
        }
        if (is_continue(value))
        {
            if (is_breakable == 1 || value == CONTINUE)
                continue;
            return get_correct_value(value);
        }
    }

    return 0;
}

static int evaluate_funcdec(struct ast_funcdec *ast, struct function *fnc)
{
    ast->is_check = 1;
    add_function(fnc, ast, ast->word);
    return 0;
}

int evaluate_shellcmd(struct ast_shellcmd *ast, struct variable *list,
                      struct function *fnc, int is_breakable)
{
    int value = -1;
    switch (ast->child_type)
    {
    case AST_COMPOUND:
        if (!ast->is_subshell)
            value = evaluate_compound((struct ast_compound *)ast->child, list,
                                      fnc, is_breakable);
        else
        {
            struct variable *newV = copy_var(list);
            struct function *newF = copy_func(fnc);
            value = evaluate_compound((struct ast_compound *)ast->child, newV,
                                      newF, is_breakable);
            free_variable(newV);
            free_function(newF);
        }
        break;
    case AST_FOR:
        value = evaluate_for((struct ast_for *)ast->child, list, fnc,
                             is_breakable + 1);
        break;
    case AST_WHILE:
        value = evaluate_while((struct ast_while *)ast->child, list, fnc,
                               is_breakable + 1);
        break;
    case AST_UNTIL:
        value = evaluate_until((struct ast_until *)ast->child, list, fnc,
                               is_breakable + 1);
        break;
    case AST_IF:
        value =
            evaluate_if((struct ast_if *)ast->child, list, fnc, is_breakable);
        break;
    default:
        break;
    }

    if (value >= 0 && value < 500)
        special_append(list, "?", "0");
    else if (value < 0)
        special_append(list, "?", "1");

    return value;
}

static char **get_args(struct ast_simplecmd *ast)
{
    int nb = 1;
    for (size_t i = 0; i < ast->nb_element; i++)
    {
        if (!ast->elements[i]->is_redir)
            nb++;
    }

    char **args = calloc(nb + 1, sizeof(char *));
    args[0] = malloc(strlen(ast->word) + 1);
    strcpy(args[0], ast->word);
    int j = 1;
    for (size_t i = 0; i < ast->nb_element; i++)
    {
        if (!ast->elements[i]->is_redir)
        {
            args[j] = malloc(strlen(ast->elements[i]->child) + 1);
            strcpy(args[j], ast->elements[i]->child);
            j++;
        }
    }

    return args;
}

static int evaluate_prefix(struct ast_prefix *ast, struct variable *list)
{
    append_variable(list, ast->child);
    return 0;
}

static int evaluate_redir(struct redir_tree *tree, int is_open)
{
    if (!tree)
        return 0;

    if (is_open)
    {
        if (!strcmp(tree->token, ">"))
        {
            if (my_redir_single_left_chevron_open(tree))
                return 1;

            return evaluate_redir(tree->next, is_open);
        }
        if (!strcmp(tree->token, "<"))
        {
            if (my_redir_single_right_chevron_open(tree))
                return 1;

            return evaluate_redir(tree->next, is_open);
        }
        if (!strcmp(tree->token, ">>"))
        {
            if (my_redir_double_left_chevron_open(tree))
                return 1;

            return evaluate_redir(tree->next, is_open);
        }
        if (!strcmp(tree->token, ">&"))
        {
            if (my_redir_single_left_chevron_and_open(tree))
                return 1;

            return evaluate_redir(tree->next, is_open);
        }
        if (!strcmp(tree->token, "<&"))
        {
            if (my_redir_single_right_chevron_and_open(tree))
                return 1;

            return evaluate_redir(tree->next, is_open);
        }
        if (!strcmp(tree->token, ">|"))
        {
            if (my_redir_single_left_chevron_pipe_open(tree))
                return 1;

            return evaluate_redir(tree->next, is_open);
        }
        if (!strcmp(tree->token, "<>"))
        {
            if (my_redir_right_and_left_chevron_open(tree))
                return 1;

            return evaluate_redir(tree->next, is_open);
        }

        return -1;
    }

    my_redir_close(tree);

    return 0;
}

static int evaluate_simplecmd(struct ast_simplecmd *ast, struct variable *list,
                              struct function *fnc)
{
    for (size_t i = 0; i < ast->nb_prefix; i++)
    {
        if (!ast->prefix[i]->is_redir)
        {
            int r = evaluate_prefix(ast->prefix[i], list);
            if (r < 0)
                return r;
        }
    }

    char **args = NULL;
    if (ast->is_word)
    {
        struct redir_tree *tree = NULL;
        for (size_t i = 0; i < ast->nb_prefix; i++)
        {
            if (ast->prefix[i]->is_redir)
                tree =
                    add_tree((struct ast_redir *)ast->prefix[i]->child, tree);
        }
        for (size_t i = 0; i < ast->nb_element; i++)
        {
            if (ast->elements[i]->is_redir)
                tree =
                    add_tree((struct ast_redir *)ast->elements[i]->child, tree);
        }

        if (evaluate_redir(tree, 1) < 0)
            return -1;

        args = get_args(ast);
        if (my_expand(args, list) == -1)
            goto error;

        int value = my_exec(list, args, fnc);
        fflush(NULL);

        for (int i = 0; args[i] != NULL; i++)
            free(args[i]);
        free(args);

        if (evaluate_redir(tree, 0) < 0)
            return -1;
        free_redir_tree(tree);

        return value;
    }

    return 0;

error:
    if (args)
        free(args);
    fprintf(stderr, "evaluate_simplecmd: can't expand\n");
    return -1;
}

static int evaluate_cmd(struct ast_cmd *ast, struct variable *list,
                        struct function *fnc, int is_breakable)
{
    if (ast->type == SIMPLE)
        return evaluate_simplecmd((struct ast_simplecmd *)ast->cmd, list, fnc);

    struct redir_tree *tree = NULL;
    for (size_t i = 0; i < ast->nb; i++)
        tree = add_tree(ast->redir[i], tree);

    int value = evaluate_redir(tree, 1);
    if (value < 0)
        return value;

    if (ast->type == SHELL)
        value = evaluate_shellcmd((struct ast_shellcmd *)ast->cmd, list, fnc,
                                  is_breakable);
    else
        value = evaluate_funcdec(ast->cmd, fnc);
    if (value < 0)
        return value;

    if (evaluate_redir(tree, 0) < 0)
        return -1;
    free_redir_tree(tree);

    return value;
}

static int pipe_loop(struct ast_pipeline *ast, struct variable *list,
                     struct function *fnc, int is_breakable)
{
    int fd[2];
    int fdd = 0;
    int status;
    int return_value = 0;
    for (size_t i = 0; i < ast->nb; i++)
    {
        pipe(fd);
        pid_t pid = fork();

        // Error
        if (pid == -1)
        {
            fprintf(stderr, "mypipe: fork failed.\n");
            return 1;
        }

        // Child
        if (pid == 0)
        {
            dup2(fdd, 0);
            if (i < ast->nb - 1)
                dup2(fd[1], 1);
            close(fd[0]);

            int value = evaluate_cmd(ast->cmd[i], list, fnc, is_breakable);
            if (value == EXIT)
                _exit(EXIT);
            if (value >= BREAK_TO_END)
            {
                if (is_breakable)
                    _exit(value);
            }
            if (ast->is_neg)
            {
                if (value >= 500)
                    _exit(value);
                if (value == 0)
                    special_append(list, "?", "1");
                else
                    special_append(list, "?", "0");

                _exit(!value);
            }
            else
                _exit(value);
        }
        else
        {
            waitpid(pid, &status, 0);

            if (WIFEXITED(status))
                return_value = WEXITSTATUS(status);
            char buffer[128] = { 0 };
            special_append(list, "?", my_itoa(return_value, buffer));

            close(fd[1]);
            fdd = fd[0];
        }
    }

    return return_value;
}

static int evaluate_pipeline(struct ast_pipeline *ast, struct variable *list,
                             struct function *fnc, int is_breakable)
{
    if (ast->nb == 1)
    {
        int value = evaluate_cmd(ast->cmd[0], list, fnc, is_breakable);
        if (value == EXIT)
        {
            return EXIT;
        }
        if (value >= BREAK_TO_END)
        {
            if (is_breakable)
            {
                return value;
            }
            // fprintf(stderr,
            //"eval_pipeline: break/continue is only for loops \n");
        }
        if (ast->is_neg)
        {
            if (value >= 500)
                return value;
            if (value == 0)
                special_append(list, "?", "1");
            else
                special_append(list, "?", "0");

            return !value;
        }
        else
        {
            return value;
        }
    }

    return pipe_loop(ast, list, fnc, is_breakable);
}

static int evaluate_andor(struct ast_andor *ast, struct variable *list,
                          struct function *fnc, int is_breakable)
{
    int value = evaluate_pipeline(ast->pipeline[0], list, fnc, is_breakable);
    if (value == EXIT)
        return EXIT;
    if (value >= BREAK_TO_END)
    {
        if (is_breakable)
            return value;
        // fprintf(stderr, "eval_andor: break/continue is only for loops \n");
    }

    for (size_t i = 1; i < ast->nb; i++)
    {
        if (ast->data[i - 1] == TOKEN_ANDAND)
        {
            if (value == 0)
            {
                value = evaluate_pipeline(ast->pipeline[i], list, fnc,
                                          is_breakable);
            }
        }
        else
        {
            if (value != 0)
            {
                value = evaluate_pipeline(ast->pipeline[i], list, fnc,
                                          is_breakable);
            }
        }

        if (value == EXIT)
            return EXIT;
        if (value >= BREAK_TO_END)
        {
            if (is_breakable)
                return value;
            // fprintf(stderr, "eval_andor: break/continue is only for loops
            // \n");
        }
    }

    return value;
}

static int evaluate_list(struct ast_list *ast, struct variable *list,
                         struct function *fnc)
{
    int value = -1;

    if (!ast)
        return 0;

    for (size_t i = 0; i < ast->nb; i++)
    {
        value = evaluate_andor(ast->andor[i], list, fnc, 0);
        if (value == EXIT)
            return EXIT;
        // if (value >= BREAK_TO_END)
        // fprintf(stderr, "eval_list: break/continue is only for loops \n");
    }

    return value;
}

int evaluate(struct ast_input *ast, struct variable *list, struct function *fnc)
{
    if (!ast)
        return 1;

    return evaluate_list(ast->list, list, fnc);
}
