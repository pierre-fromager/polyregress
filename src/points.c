
#include "points.h"

void points_init(pr_vector_t *data, points_t *points, mi_item_t nbPoints)
{
    mi_item_t c;
    for (c = 0; c < nbPoints; c++)
    {
        const int i = (int)c / 2;
        if (c % 2 == 0)
            (*points)[i].x = (*data)[c];
        else
            (*points)[i].y = (*data)[c];
    }
}