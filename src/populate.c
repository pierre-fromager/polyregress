
#include "populate.h"

void populate_data(pr_vector_t *rawArray, mi_item_t *datacpt, mi_item_t *degree, FILE *stream,char *separator)
{
    uint8_t degree_set = 0;
    char bufin[LINE_BUF_SIZE];
    while (fgets(bufin, LINE_BUF_SIZE, stream))
    {
        char *value = strtok(bufin, separator);
        while (value)
        {
            if (degree_set == 0)
            {
                (*degree) = (mi_item_t)atoi(value);
                degree_set = 1;
            }
            else
                (*rawArray)[(*datacpt)++] = atof(value);
            value = strtok(NULL, separator);
        }
    }
}

void populate_check(mi_item_t datacpt, mi_item_t degree)
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
