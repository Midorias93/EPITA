#define _DEFAULT_SOURCE

#include "test.h"

#include <fnmatch.h>
#include <grp.h>
#include <libgen.h>
#include <pwd.h>
#include <string.h>
#include <sys/stat.h>

int type(struct token *token, char *path)
{
    int res = 0;
    struct stat stat;
    int a = lstat(path, &stat);
    if (a == -1)
    {
        return 0;
    }
    if (token->negation == 1)
    {
        res = !res;
    }
    if (strcmp(token->parametre, "b") == 0 && S_ISBLK(stat.st_mode))
    {
        return !res;
    }
    else if (strcmp(token->parametre, "c") == 0 && S_ISCHR(stat.st_mode))
    {
        return !res;
    }
    else if (strcmp(token->parametre, "d") == 0 && S_ISDIR(stat.st_mode))
    {
        return !res;
    }
    else if (strcmp(token->parametre, "f") == 0 && S_ISFIFO(stat.st_mode))
    {
        return !res;
    }
    else if (strcmp(token->parametre, "l") == 0 && S_ISLNK(stat.st_mode))
    {
        return !res;
    }
    else if (strcmp(token->parametre, "p") == 0 && S_ISREG(stat.st_mode))
    {
        return !res;
    }
    else if (strcmp(token->parametre, "s") == 0 && S_ISSOCK(stat.st_mode))
    {
        return !res;
    }
    else
    {
        return res;
    }
}

int name(struct token *token, char *path)
{
    if (token->negation == 1)
    {
        return fnmatch(token->parametre, basename(path), 0);
    }
    else
    {
        return !fnmatch(token->parametre, basename(path), 0);
    }
}

int newer(struct token *token, char *path)
{
    struct stat stat_p;
    struct stat stat_token;
    if (lstat(path, &stat_p) == -1)
    {
        return 0;
    }
    if (lstat(token->parametre, &stat_token) == -1)
    {
        return 0;
    }
    if (stat_token.st_mtim.tv_sec < stat_p.st_mtim.tv_sec)
    {
        return 1;
    }
    else if (stat_token.st_mtim.tv_sec == stat_p.st_mtim.tv_sec)
    {
        if (stat_token.st_mtim.tv_nsec < stat_p.st_mtim.tv_nsec)
        {
            return 1;
        }
    }
    return 0;
}

int group(struct token *token, char *path)
{
    struct stat stat_p;
    if (stat(path, &stat_p) == -1)
    {
        return 0;
    }
    struct group *grp = getgrnam(token->parametre);
    if (grp == NULL)
    {
        return 0;
    }
    if (stat_p.st_gid == grp->gr_gid)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int user(struct token *token, char *path)
{
    struct stat stat_p;
    if (stat(path, &stat_p) == -1)
    {
        return 0;
    }
    struct passwd *pwd = getpwnam(token->parametre);
    if (pwd == NULL)
    {
        return 0;
    }
    if (stat_p.st_uid == pwd->pw_uid)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int evaluate(struct ast *ast, char *path, test *list_f)
{
    if (ast->data->type == OR)
    {
        if (ast->data->negation == 1)
        {
            if (!(evaluate(ast->left, path, list_f)))
            {
                return 1;
            }
            else if (!(evaluate(ast->right, path, list_f)))
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            if (evaluate(ast->left, path, list_f))
            {
                return 1;
            }
            else if (evaluate(ast->right, path, list_f))
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
    else if (ast->data->type == AND)
    {
        if (ast->data->negation == 1)
        {
            if (!(evaluate(ast->left, path, list_f)))
            {
                if (!(evaluate(ast->right, path, list_f)))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                return 0;
            }
        }
        else
        {
            if (evaluate(ast->left, path, list_f))
            {
                if (evaluate(ast->right, path, list_f))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            else
            {
                return 0;
            }
        }
    }
    else
    {
        return list_f[ast->data->type](ast->data, path);
    }
}
