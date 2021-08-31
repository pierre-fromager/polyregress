
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

static char solution_get_sign(double value)
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

void solution_print(gj_vector *mat, minfo_t *minfo)
{
    gj_vector sol;
    unsigned c;
    const size_t sol_asize = sizeof(double) * minfo->nbcol;
    sol = malloc(sol_asize);
    mat_get_col(mat, minfo, minfo->nbcol - 1, &sol);
    char str[SOL_MAXLEN];
    for (c = 0; c < minfo->nbcol - 1; c++)
        if (c == 0)
            snprintf(
                str,
                (size_t)SOL_MAXLEN,
                solution_get_fmt(c),
                sol[c]);
        else
        {
            snprintf(
                str + strlen(str),
                (size_t)SOL_MAXLEN,
                solution_get_fmt(c),
                solution_get_sign(sol[c]),
                sol[c],
                c);
        }
    solution_remove_space(str);
    printf("%s\n", str);
    free(sol);
}