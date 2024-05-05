#include "evalexpr.h"

int is_rpn(char *str)
{
    const char *rpn = "-rpn";
    for (size_t i = 0; str[i] != 0; i++)
    {
        if (str[i] != rpn[i])
        {
            return 1;
        }
    }
    return 0;
}

static int is_int(char c)
{
    if (c >= '0' && c <= '9')
    {
        return 1;
    }
    return 0;
}

static int is_delim(char c)
{
    char *delim = "+-*/%^()";
    for (int i = 0; delim[i] != '\0'; i++)
    {
        if (c == delim[i])
        {
            return 1;
        }
    }
    return 0;
}


struct fifo *pars(char *expression)
{
    struct fifo *file = fifo_init();
    int a = 0;
    struct token nombre =
    {
        .data = 0,
        .type = 0,
    };
    struct token operateur =
    {
        .data = 0,
        .type = 1,
    };
    for (int i = 0; expression[i] != '\0'; i++)
    {
        if (is_delim(expression[i]))
        {
            if (a == 1)
            {
                fifo_push(file, nombre);
                nombre.data = 0;
                a = 0;
            }
            operateur.data = expression[i];
            fifo_push(file, operateur);
            continue;
        }
        if (is_int(expression[i]) && a == 0)
        {
            a = 1;
            nombre.data = atoi(&expression[i]);
            continue;
        }
        if (is_int(expression[i]) && a == 1)
        {
            nombre.data *= 10;
            nombre.data += atoi(&expression[i]);
            continue;
        }
        if (expression[i] == ' ' || expression[i] == '\n')
        {
            if(a == 1)
            {
                fifo_push(file, nombre);
                nombre.data = 0;
                a = 0;
            }
            continue;
        }
    }
    return file;
}

static int my_pow(int a, int b)
{
    if (b == 0)
    {
        return 1;
    }
    if (b % 2 == 0)
    {
        return my_pow(a, b / 2) * my_pow(a, b / 2);
    }
    else
    {
        return a * my_pow(a, b / 2) * my_pow(a, b / 2);
    }
}

int calculate(const char operator, struct token a, struct token b, int *error)
{
    switch(operator)
    {
        case '+':
            return a.data + b.data;
        case '-':
            return a.data - b.data;
        case '*':
            return a.data * b.data;
        case '/':
            if (b.data == 0)
            {
                *error = 3;
                return 1;
            }
            return a.data / b.data;
        case '%':
            if (b.data == 0)
            {
                *error = 3;
                return 1;
            }
            return a.data %  b.data;
        case '^':
            if (a.data < 0)
            {
                *error = 3;
                return 1;
            }
            return my_pow(a.data, b.data);
        default:
            *error = 4;
            return 1;
    };
    return 0;
}

static int affect_nombre(struct token *nombre, struct stack **stack, struct fifo *fifo, int *error)
{
    if (*stack == NULL)
    {
        *error = 2;
        fifo_destroy(fifo);
        return 1;
    }
    else
    {
        *nombre = stack_peek(*stack);
        *stack = stack_pop(*stack);
        return 0;
    }
}

int calcul_rpn(struct fifo *file, int *error)
{
    struct stack *stack = NULL;
    struct token token = fifo_head(file);
    struct token nombre1 = {.type = 0,.data = 0};
    struct token nombre2 = {.type = 0,.data = 0};
    while (fifo_pop(file))
    {
        if (token.type == 0)
        {
            stack = stack_push(stack, token);
        }
        else
        {
            if (affect_nombre(&nombre1, &stack, file, error))
            {
                return 0;
            }
            if (affect_nombre(&nombre2, &stack, file, error))
            {
                return 0;
            }
            nombre1.data = calculate(token.data, nombre2, nombre1, error);
            stack = stack_push(stack, nombre1);
        }
        if (file->head != NULL)
        {
            token = fifo_head(file);
        }
    }
    int resultat = stack_peek(stack).data;
    stack = stack_pop(stack);
    if (stack != NULL)
    {
        stack_destroy(stack);
        free(file);
        *error = 2;
        return 0;
    }
    free(file);
    return resultat;
}

int donne_prio(char c)
{
    if (c == '(' || c == ')')
    {
        return 3;
    }
    if (c == '*' || c == '/' || c == '%')
    {
        return 2;
    }
    if ( c == '+' || c == '-')
    {
        return 1;
    }
    return 0;
}

int boucle1(struct stack *stack,struct token token)
{
    if (stack != NULL)
    {
        if (donne_prio(stack_peek(stack).data) > donne_prio(token.data))
        {
            return 1;
        }
    }
    return 0;
}

int boucle2(struct stack *stack, int *error)
{
   if (stack == NULL)
   {
       *error = 2;
       return 12;
   }
   if (stack_peek(stack).data != '(')
   {
       return 1;
   }
   return 0;
}

static int is_op(char c)
{
    char *op = "+-*/%^";
    for (int i = 0; op[i] != '\0'; i++)
    {
        if (c == op[i])
        {
            return 1;
        }
    }
    return 0;
}

struct fifo *convert_standar(struct fifo *file, int *error)
{
    struct token token = fifo_head(file);
    struct stack *stack_op = NULL;
    struct token a_ajouter = {.data = 0, .type = 1};
    struct fifo *file_resultat = fifo_init();
    while (fifo_pop(file) == 1)
    {
        if (token.type == 0)
        {
            fifo_push(file_resultat, token);
            if (file->head != NULL)
            {
                token = fifo_head(file);
            }
            continue;
        }
        if (is_op(token.data))
        {
            while (boucle1(stack_op,token))
            {
                fifo_push(file_resultat, stack_peek(stack_op));
                stack_op = stack_pop(stack_op);
            }
            stack_op = stack_push(stack_op, token);
        }
        if (token.type == 1 && token.data == '(')
        {
            stack_op = stack_push(stack_op, token);
        }
        if (token.type == 1 && token.data == ')')
        {
            stack_op = stack_pop(stack_op);
            while (boucle2(stack_op, error))
            {
                fifo_push(file_resultat, stack_peek(stack_op));
                stack_op = stack_pop(stack_op);
            }
            stack_op = stack_pop(stack_op);
        }
        if (file->head != NULL)
        {
            token = fifo_head(file);
        }
    }
    while (stack_op != NULL)
    {
        a_ajouter = stack_peek(stack_op);
        stack_op = stack_pop(stack_op);
        fifo_push(file_resultat, a_ajouter);
    }
    return file_resultat;
}
