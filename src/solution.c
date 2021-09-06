
#include "solution.h"

static void solution_remove_space(char *str)
{
    char *src, *dst;
    for (src = dst = str; *src != SOL_STR_NULL; src++)
    {
        *dst = *src;
        if (*dst != ' ')
            dst++;
    }
    *dst = SOL_STR_NULL;
}

static char solution_get_sign(const pr_item_t value)
{
    return (value >= 0) ? SOL_STR_PLUS : SOL_STR_SPACE;
}

static char *solution_get_fmt(unsigned c)
{
    switch (c)
    {
    case 0:
        return SOL_FMT_0;
        break;
    case 1:
        return SOL_FMT_1;
        break;
    default:
        return SOL_FMT_N;
        break;
    }
}

pr_vector_t solution_get(pr_vector_t *mat, minfo_t *minfo)
{
    pr_vector_t sol;
    sol = malloc(sizeof(pr_item_t) * minfo->nbcol);
    mat_get_col(mat, minfo, minfo->nbcol - 1, &sol);
    return sol;
}

void solution_get_str(pr_vector_t sol, minfo_t *minfo, char *str)
{
    unsigned c = 0;
    snprintf(str, (size_t)SOL_MAXLEN, solution_get_fmt(c), sol[c]);
    for (c = 1; c < minfo->nbcol - 1; c++)
        snprintf(str + strlen(str),
                 (size_t)SOL_MAXLEN,
                 solution_get_fmt(c),
                 solution_get_sign(sol[c]),
                 sol[c],
                 c);
    solution_remove_space(str);
}

void solution_print(pr_vector_t *mat, minfo_t *minfo, FILE *stream)
{
    pr_vector_t sol = solution_get(mat, minfo);
    char str[SOL_MAXLEN];
    solution_get_str(sol, minfo, str);
    solution_remove_space(str);
    fprintf(stream, "%s\n", str);
    free(sol);
}