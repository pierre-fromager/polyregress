
#include "points.h"

void points_init(pr_vector *data, points_t *points, unsigned nbPoints)
{
    unsigned c;
    for (c = 0; c < nbPoints; c++)
    {
        const int i = (int)c / 2;
        if (c % 2 == 0)
            (*points)[i].x = (*data)[c];
        else
            (*points)[i].y = (*data)[c];
    }
}