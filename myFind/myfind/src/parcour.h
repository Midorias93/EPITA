#ifndef PARCOUR_H
#define PARCOUR_H

#include "test.h"

typedef int (*parcour)(struct info *info, struct ast *ast, char *path,
                       test list_t[]);

int parcourP(struct info *info, struct ast *ast, char *path, test list_t[]);
int parcourH(struct info *info, struct ast *ast, char *path, test list_t[]);
int parcourL(struct info *info, struct ast *ast, char *path, test list_t[]);
int parcourD(struct info *info, struct ast *ast, char *path, test list_t[]);
#endif // PARCOUR_H
