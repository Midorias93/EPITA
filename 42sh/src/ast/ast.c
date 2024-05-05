#include "ast.h"

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *ast_new(enum ast_type type)
{
    switch (type)
    {
    case AST_INPUT:
        return calloc(1, sizeof(struct ast_input));
    case AST_LIST:
        return calloc(1, sizeof(struct ast_list));
    case AST_ANDOR:
        return calloc(1, sizeof(struct ast_andor));
    case AST_PIPELINE:
        return calloc(1, sizeof(struct ast_pipeline));
    case AST_CMD:
        return calloc(1, sizeof(struct ast_cmd));
    case AST_SIMPLECMD:
        return calloc(1, sizeof(struct ast_simplecmd));
    case AST_SHELLCMD:
        return calloc(1, sizeof(struct ast_shellcmd));
    case AST_FUNCDEC:
        return calloc(1, sizeof(struct ast_funcdec));
    case AST_REDIR:
        return calloc(1, sizeof(struct ast_redir));
    case AST_PREFIX:
        return calloc(1, sizeof(struct ast_prefix));
    case AST_ELEMENT:
        return calloc(1, sizeof(struct ast_element));
    case AST_COMPOUND:
        return calloc(1, sizeof(struct ast_compound));
    case AST_FOR:
        return calloc(1, sizeof(struct ast_for));
    case AST_WHILE:
        return calloc(1, sizeof(struct ast_while));
    case AST_UNTIL:
        return calloc(1, sizeof(struct ast_until));
    case AST_IF:
        return calloc(1, sizeof(struct ast_if));
    case AST_ELSE:
        return calloc(1, sizeof(struct ast_else));
    }

    return NULL;
}

void free_andor(struct ast_andor *ast);
static void free_compound(struct ast_compound *ast)
{
    if (!ast)
        return;

    for (int i = 0; i < ast->nb; i++)
        free_andor(ast->andor[i]);

    free(ast->andor);
    free(ast->data);
    free(ast);
}

static void free_for(struct ast_for *ast)
{
    if (!ast)
        return;

    free(ast->word);

    for (int i = 0; i < ast->nb; i++)
        free(ast->words[i]);

    free(ast->words);
    free_compound(ast->compound);
    free(ast);
}

static void free_while(struct ast_while *ast)
{
    if (!ast)
        return;

    free_compound(ast->condition);
    free_compound(ast->compound);
    free(ast);
}

static void free_until(struct ast_until *ast)
{
    if (!ast)
        return;

    free_compound(ast->condition);
    free_compound(ast->compound);
    free(ast);
}

static void free_else(struct ast_else *ast)
{
    if (!ast)
        return;

    free_compound(ast->condition);
    free_compound(ast->compound);
    free_else(ast->else_clause);
    free(ast);
}

static void free_if(struct ast_if *ast)
{
    if (!ast)
        return;

    free_compound(ast->condition);
    free_compound(ast->compound);
    free_else(ast->else_clause);
    free(ast);
}

void free_redir(struct ast_redir *ast)
{
    if (!ast)
        return;

    if (ast->redir)
        free(ast->redir);

    if (ast->word)
        free(ast->word);

    free(ast);
}

void free_prefix(struct ast_prefix *ast)
{
    if (!ast)
        return;

    if (!ast->is_redir)
        free(ast->child);
    else
        free_redir(ast->child);

    free(ast);
}

void free_shellcmd(struct ast_shellcmd *ast)
{
    if (!ast)
        return;

    switch (ast->child_type)
    {
    case AST_COMPOUND:
        free_compound(ast->child);
        break;
    case AST_FOR:
        free_for(ast->child);
        break;
    case AST_WHILE:
        free_while(ast->child);
        break;
    case AST_UNTIL:
        free_until(ast->child);
        break;
    case AST_IF:
        free_if(ast->child);
        break;
    default:
        break;
    }

    free(ast);
    return;
}

static void free_funcdec(struct ast_funcdec *ast)
{
    if (!ast || ast->is_check)
        return;

    free_shellcmd(ast->child);
    free(ast->word);
    free(ast);
}

void free_element(struct ast_element *ast)
{
    if (!ast)
        return;

    if (!ast->is_redir)
        free(ast->child);
    else
        free_redir(ast->child);

    free(ast);
}

static void free_simplecmd(struct ast_simplecmd *ast)
{
    if (!ast)
        return;

    for (size_t i = 0; i < ast->nb_prefix; i++)
        free_prefix(ast->prefix[i]);

    if (ast->prefix)
        free(ast->prefix);

    free(ast->word);

    for (size_t i = 0; i < ast->nb_element; i++)
        free_element(ast->elements[i]);

    if (ast->elements)
        free(ast->elements);

    free(ast);
}

void free_cmd(struct ast_cmd *ast)
{
    if (!ast)
        return;

    for (size_t i = 0; i < ast->nb; i++)
        free_redir(ast->redir[i]);

    if (ast->type == SIMPLE)
        free_simplecmd(ast->cmd);
    else if (ast->type == SHELL)
        free_shellcmd(ast->cmd);
    else
        free_funcdec(ast->cmd);

    free(ast);
}

static void free_pipeline(struct ast_pipeline *ast)
{
    if (!ast)
        return;

    for (size_t i = 0; i < ast->nb; i++)
        free_cmd(ast->cmd[i]);

    free(ast->cmd);
    free(ast);
}

void free_andor(struct ast_andor *ast)
{
    if (!ast)
        return;

    for (size_t i = 0; i < ast->nb; i++)
        free_pipeline(ast->pipeline[i]);

    free(ast->pipeline);
    free(ast->data);
    free(ast);
}

static void free_list(struct ast_list *ast)
{
    if (!ast)
        return;

    for (size_t i = 0; i < ast->nb; i++)
        free_andor(ast->andor[i]);

    free(ast->andor);
    free(ast->data);
    free(ast);
}

void ast_free(struct ast_input *ast)
{
    if (!ast)
        return;

    free_list(ast->list);

    free(ast);
}

static void print_andor(struct ast_andor *ast, int *j);
static void print_compound(struct ast_compound *ast, int *j)
{
    if (!ast)
        return;

    int x = *j;
    for (int i = 0; i < ast->nb; i++)
    {
        *j += 1;
        printf("\tcompound%d -- andor%d\n", x, *j);
        print_andor(ast->andor[i], j);
    }
}

static void print_for(struct ast_for *ast, int *j)
{
    if (!ast)
        return;

    int x = *j;
    *j += 1;
    printf("\tfor%d -- compound%d [ label=\"inside\" ]\n", x, *j);
    print_compound(ast->compound, j);
}

static void print_while(struct ast_while *ast, int *j)
{
    if (!ast)
        return;

    int x = *j;
    *j += 1;
    printf("\twhile%d -- compound%d [ label=\"condition\" ]\n", x, *j);
    print_compound(ast->condition, j);

    *j += 1;
    printf("\twhile%d -- compound%d [ label=\"inside\" ]\n", x, *j);
    print_compound(ast->compound, j);
}

static void print_until(struct ast_until *ast, int *j)
{
    if (!ast)
        return;

    int x = *j;
    *j += 1;
    printf("\tuntil%d -- compound%d [ label=\"condition\" ]\n", x, *j);
    print_compound(ast->condition, j);

    *j += 1;
    printf("\tuntil%d -- compound%d [ label=\"inside\" ]\n", x, *j);
    print_compound(ast->compound, j);
}

static void print_else(struct ast_else *ast, int *j)
{
    if (!ast)
        return;

    int x = *j;
    if (!ast->is_else)
    {
        *j += 1;
        printf("\telse%d -- compound%d [ label=\"condition\" ]\n", x, *j);
        print_compound(ast->condition, j);
    }

    *j += 1;
    printf("\telse%d -- compound%d [ label=\"inside\" ]\n", x, *j);
    print_compound(ast->compound, j);

    if (!ast->is_else)
    {
        *j += 1;
        printf("\telse%d -- compound%d [ label=\"else\" ]\n", x, *j);
        print_else(ast->else_clause, j);
    }
}

static void print_if(struct ast_if *ast, int *j)
{
    if (!ast)
        return;

    int x = *j;
    *j += 1;
    printf("\tif%d -- compound%d [ label=\"condition\" ]\n", x, *j);
    print_compound(ast->condition, j);

    *j += 1;
    printf("\tif%d -- compound%d [ label=\"inside\" ]\n", x, *j);
    print_compound(ast->compound, j);

    if (ast->else_clause)
    {
        *j += 1;
        printf("\tif%d -- else%d [ label=\"else\" ]\n", x, *j);
        print_else(ast->else_clause, j);
    }
}

static void print_redir(struct ast_redir *ast, int *j)
{
    if (!ast)
        return;

    char c = (char)((int)'0' + ast->io_number);
    char *str = calloc(strlen(ast->redir) + strlen(ast->word) + 3, 1);
    str[0] = c;
    strcat(str, ast->redir);
    strcat(str, " ");
    strcat(str, ast->word);

    printf("\tredir%d [ xlabel=\"%s\" ]\n", *j, str);
    free(str);
}

static void print_prefix(struct ast_prefix *ast, int *j)
{
    if (!ast)
        return;

    int x = *j;
    if (!ast->is_redir)
        printf("\tprefix%d [ xlabel=\"%s\" ]\n", x, (char *)ast->child);
    else
    {
        *j += 1;
        printf("\tprefix%d -- redir%d\n", x, *j);
        print_redir(ast->child, j);
    }
}

static void print_shellcmd(struct ast_shellcmd *ast, int *j)
{
    if (!ast)
        return;

    int x = *j;
    switch (ast->child_type)
    {
    case AST_COMPOUND:
        *j += 1;
        printf("\tshell%d -- compound%d\n", x, *j);
        print_compound(ast->child, j);
        break;
    case AST_FOR:
        *j += 1;
        printf("\tshell%d -- for%d\n", x, *j);
        print_for(ast->child, j);
        break;
    case AST_WHILE:
        *j += 1;
        printf("\tshell%d -- while%d\n", x, *j);
        print_while(ast->child, j);
        break;
    case AST_UNTIL:
        *j += 1;
        printf("\tshell%d -- until%d\n", x, *j);
        print_until(ast->child, j);
        break;
    case AST_IF:
        *j += 1;
        printf("\tshell%d -- if%d\n", x, *j);
        print_if(ast->child, j);
        break;
    default:
        break;
    }
}

void print_funcdec(struct ast_funcdec *ast, int *j)
{
    if (!ast)
        return;

    int x = *j;
    *j += 1;
    printf("\tfuncdec%d -- shell%d\n", x, *j);
    printf("\tfuncdec%d [ xlabel=\"%s\" ]\n", x, ast->word);
    print_shellcmd(ast->child, j);
}

static void print_element(struct ast_element *ast, int *j)
{
    if (!ast)
        return;

    int x = *j;
    if (!ast->is_redir)
        printf("\telement%d [ xlabel=\"%s\" ]\n", x, (char *)ast->child);
    else
    {
        *j += 1;
        printf("\telement%d -- redir%d\n", x, *j);
        print_redir(ast->child, j);
    }
}

static void print_simplecmd(struct ast_simplecmd *ast, int *j)
{
    if (!ast)
        return;

    int x = *j;
    for (size_t i = 0; i < ast->nb_prefix; i++)
    {
        *j += 1;
        printf("\tsimple%d -- prefix%d\n", x, *j);
        print_prefix(ast->prefix[i], j);
    }

    if (ast->is_word)
        printf("\tsimple%d [ xlabel=\"%s\" ]\n", x, ast->word);

    for (size_t i = 0; i < ast->nb_element; i++)
    {
        *j += 1;
        printf("\tsimple%d -- element%d\n", x, *j);
        print_element(ast->elements[i], j);
    }
}

static void print_cmd(struct ast_cmd *ast, int *j)
{
    if (!ast)
        return;

    int x = *j;
    for (size_t i = 0; i < ast->nb; i++)
    {
        *j += 1;
        printf("\tcmd%d -- redir%d\n", x, *j);
        print_redir(ast->redir[i], j);
    }

    *j += 1;
    if (ast->type == SIMPLE)
    {
        printf("\tcmd%d -- simple%d\n", x, *j);
        print_simplecmd(ast->cmd, j);
    }
    else if (ast->type == SHELL)
    {
        printf("\tcmd%d -- shell%d\n", x, *j);
        print_shellcmd(ast->cmd, j);
    }
    else
    {
        printf("\tcmd%d -- funcdec%d\n", x, *j);
        print_funcdec(ast->cmd, j);
    }
}

static void print_pipeline(struct ast_pipeline *ast, int *j)
{
    if (!ast)
        return;

    int x = *j;
    for (size_t i = 0; i < ast->nb; i++)
    {
        *j += 1;
        printf("\tpipeline%d -- cmd%d", x, *j);
        if (ast->is_neg)
            printf("\tpipeline%d [ xlabel=\"!\" ]", x);
        printf("\n");
        print_cmd(ast->cmd[i], j);
    }
}

static void print_andor(struct ast_andor *ast, int *j)
{
    if (!ast)
        return;

    int x = *j;
    for (size_t i = 0; i < ast->nb; i++)
    {
        *j += 1;
        printf("\tandor%d -- pipeline%d\n", x, *j);
        if (i < ast->nb - 1)
        {
            printf("\tpipeline%d -- pipeline%d [ label=\"", *j, *j + 1);
            if (ast->data[i] == TOKEN_ANDAND)
                printf("&&\" ]\n");
            else
                printf("||\" ]\n");
        }
        print_pipeline(ast->pipeline[i], j);
    }
}

static void print_list(struct ast_list *ast, int *j)
{
    if (!ast)
        return;

    int x = *j;
    for (size_t i = 0; i < ast->nb; i++)
    {
        *j += 1;
        printf("\tlist%d -- andor%d\n", x, *j);
        if (i < ast->nb - 1)
        {
            printf("\tandor%d -- andor%d [ label=\"", *j, *j + 1);
            if (ast->data[i] == TOKEN_POINTV)
                printf(";\" ]\n");
            else
                printf("&\" ]\n");
        }
        print_andor(ast->andor[i], j);
    }
}

void ast_print(struct ast_input *ast)
{
    printf("strict graph {\n");
    if (ast)
    {
        printf("\tinput1 -- list2\n");
        int i = 2;
        print_list(ast->list, &i);
    }

    printf("}\n");
}
