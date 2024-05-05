#include "ast.h"

struct ast *init_ast(struct token *data)
{
    struct ast *ast = malloc(sizeof(struct ast));
    if (ast == NULL)
    {
        return NULL;
    }
    ast->data = data;
    ast->left = NULL;
    ast->right = NULL;
    return ast;
}

struct ast *ajout(struct fifo_ast *file, struct token *token)
{
    if (file->size < 2)
    {
        return NULL;
    }
    else
    {
        struct ast *ast = init_ast(token);
        struct ast *ast1 = fifo_ast_head(file);
        fifo_ast_pop_mais_pas_free(file);
        struct ast *ast2 = fifo_ast_head(file);
        fifo_ast_pop_mais_pas_free(file);
        ast->left = ast1;
        ast->right = ast2;
        return ast;
    }
}

void ast_print(struct ast *ast)
{
    if (ast == NULL)
    {
        return;
    }
    ast_print(ast->left);
    print_token(ast->data);
    ast_print(ast->right);
}

void ast_destroy(struct ast *ast)
{
    if (ast == NULL)
    {
        return;
    }
    ast_destroy(ast->left);
    ast_destroy(ast->right);
    free(ast->data);
    free(ast);
}

static int is_not_opperator(int type)
{
    if (type == OR || type == AND || type == P_G || type == P_D
        || type == P_EXCLA)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

static int is_an_opperator(int type)
{
    if (type == OR || type == AND || type == P_EXCLA)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

static int do_magic(struct stack **stack, struct fifo_ast *file_output)
{
    struct token *token = stack_peek(*stack);
    if (token->type == P_EXCLA)
    {
        *stack = stack_pop(*stack);
        if (file_output->size >= 1)
        {
            fifo_ast_head(file_output)->data->negation =
                !fifo_ast_head(file_output)->data->negation;
            return 0;
        }
        return 1;
    }
    struct ast *ast = ajout(file_output, stack_peek(*stack));
    if (ast != NULL)
    {
        fifo_ast_push(file_output, ast);
        *stack = stack_pop_mais_pas_free(*stack);
    }
    else
    {
        return 1;
    }
    return 0;
}

int check_presedance(int type1, int type2)
{
    if (type1 == P_G)
    {
        return 0;
    }
    else if (type1 > type2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

static struct ast *erreur(struct info *info, struct stack **stack,
                          struct fifo *file, struct fifo_ast *file_output)
{
    info->erreur = 1;
    stack_destroy(*stack);
    fifo_destroy(file);
    fifo_ast_destroy(file_output);
    return NULL;
}

struct ast *shuting_yard(struct info *info, struct fifo *file)
{
    struct token *token;
    struct ast *ast = NULL;
    struct fifo_ast *file_output = fifo_ast_init();
    struct stack *stack = NULL;
    int tpg = 0;
    if (file == NULL)
    {
        info->erreur = 1;
        return NULL;
    }
    while (file->head != NULL)
    {
        token = fifo_head(file);
        fifo_pop_mais_pas_free(file);
        if (is_not_opperator(token->type))
        {
            ast = init_ast(token);
            fifo_ast_push(file_output, ast);
        }
        if (is_an_opperator(token->type))
        {
            while (stack != NULL
                   && check_presedance(stack_peek(stack)->type, token->type))
            {
                if (do_magic(&stack, file_output))
                {
                    free(token);
                    return erreur(info, &stack, file, file_output);
                }
            }
            stack = stack_push(stack, token);
        }
        if (token->type == P_G)
        {
            stack = stack_push(stack, token);
        }
        if (token->type == P_D)
        {
            free(token);
            while (stack != NULL && stack_peek(stack)->type != P_G)
            {
                if (do_magic(&stack, file_output))
                {
                    return erreur(info, &stack, file, file_output);
                }
            }
            tpg = stack_peek(stack)->type == P_G ? 1 : tpg;
            stack = stack_pop(stack);
            if (tpg == 0)
            {
                return erreur(info, &stack, file, file_output);
            }
            tpg = 1;
        }
    }
    while (stack != NULL)
    {
        if (stack_peek(stack)->type == P_G || do_magic(&stack, file_output))
        {
            return erreur(info, &stack, file, file_output);
        }
    }
    free(stack);
    free(file);
    struct ast *save = fifo_ast_head(file_output);
    fifo_ast_pop_mais_pas_free(file_output);
    if (file_output->size != 0)
    {
        info->erreur = 1;
        fifo_ast_destroy(file_output);
        return NULL;
    }
    free(file_output);
    return save;
}
