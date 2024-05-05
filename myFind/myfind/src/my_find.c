#include "my_find.h"

#include <libgen.h>

#include "option.h"
#include "parchemin/parchemin.h"
#include "parcour.h"

int main(int argc, char *argv[])
{
    if (argc >= 1)
    {
        test list_f[] = { print, name, type, newer, user, group, delete };
        parcour list_p[] = { parcourD, parcourH, parcourL, parcourP };
        struct info info = {
            .depart = 1, .action = -1, .option = 3, .erreur = 0
        };
        option_search(&info, argc, argv);
        struct parchemin *parchemin = init_parchemin(&info, argc, argv);
        struct fifo *file = fait_la_file(&info, argc, argv);
        if (info.erreur == 1)
        {
            fprintf(stderr, "parsing : erreur argument invalid\n");
            destroy_parchemin(parchemin);
            return 1;
        }
        struct ast *ast = file == NULL ? NULL : shuting_yard(&info, file);
        if (info.erreur == 1)
        {
            fprintf(stderr, "ast : erreur invalide AST\n");
            ast_destroy(ast);
            destroy_parchemin(parchemin);
            return 1;
        }
        for (int i = 0; i < parchemin->size; i++)
        {
            if (list_p[info.option](&info, ast, parchemin->chemins[i], list_f))
            {
                ast_destroy(ast);
                destroy_parchemin(parchemin);
                fprintf(stderr,
                        "simple_ls : erreur lors de la lecture des fichiers\n");
                return 1;
            }
        }
        ast_destroy(ast);
        destroy_parchemin(parchemin);
        return 0;
    }
}
