
/**
 * @file typedefs.h
 * @author Pierre Fromager (info@pier-infor.fr)
 * @brief Types declaration
 * @version 0.1
 * @date 2021-08-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _POLYREG_TYPEDEFS_
#define _POLYREG_TYPEDEFS_

typedef struct arguments_s
{
    char *args[1];
    char *separator;
    int debug;
} arguments_t;

typedef struct minfo_s *minfo_ptr_t;
typedef struct minfo_s minfo_t;

typedef double pr_item_t;
typedef unsigned mi_item_t;

struct minfo_s
{
    mi_item_t degree, nbcol, nbrow, nbpoints;
    minfo_ptr_t (*set_dim)(minfo_t *);
};

typedef pr_item_t *pr_vector_t;

typedef struct point_s
{
    pr_item_t x;
    pr_item_t y;
} point_t;

typedef point_t *points_t;

#endif // _POLYREG_TYPEDEFS_