
#include "populate.h"

void populate_data(gj_vector *rawArray, int *datacpt, int *degree)
{
    char bufin[LINE_BUF_SIZE];
    while (fgets(bufin, LINE_BUF_SIZE, stdin))
    {
        char *value = strtok(bufin, DELIM);
        while (value)
        {
            if ((*datacpt) == -1)
                (*degree) = atoi(value);
            else
                (*rawArray)[(*datacpt)] = atof(value);
            value = strtok(NULL, DELIM);
            (*datacpt)++;
        }
    }
}

void populate_check(int datacpt, int degree)
{
    if (datacpt % 2 != 0)
    {
        printf(MSG_ERR_POINTS);
        exit(EXIT_FAILURE);
    }

    if (degree + 1 > datacpt / 2)
    {
        printf(MSG_ERR_DEGREE, degree, datacpt / 2);
        exit(EXIT_FAILURE);
    }
}
