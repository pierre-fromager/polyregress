
#include "populate.h"

void populate_data(gj_vector *rawArray, unsigned *datacpt, unsigned *degree)
{
    uint8_t degree_set = 0;
    char bufin[LINE_BUF_SIZE];
    while (fgets(bufin, LINE_BUF_SIZE, stdin))
    {
        char *value = strtok(bufin, DELIM);
        while (value)
        {
            if (degree_set == 0) {
                (*degree) = (unsigned)atoi(value);
                //(*degree) = strtoul(value, &valptr, 10);
                degree_set = 1;
                //value = strtok(NULL, DELIM);
            }                
            else
                (*rawArray)[(*datacpt)++] = atof(value);
            value = strtok(NULL, DELIM);
            //(*datacpt)++;
        }
    }
}

void populate_check(unsigned datacpt, unsigned degree)
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
