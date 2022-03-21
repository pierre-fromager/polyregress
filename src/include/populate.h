
/**
 * @file populate.h
 * @author Pierre Fromager (info@pier-infor.fr)
 * @brief Points elementary structures and operations
 * @version 0.1
 * @date 2021-08-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _POLYREG_POPULATE_
#define _POLYREG_POPULATE_

#define MSG_ERR_POINTS "Error: data not in form of x,y pairs.\n"
#define MSG_ERR_DEGREE "Warning: polynomial degree %x > nb points %x.\n"
#define DELIM " "
#define LINE_BUF_SIZE 128

#include <matrix.h>

void populate_data(pr_vector_t *rawArray, mi_item_t *datacpt, mi_item_t *degree, FILE *stream,char *separator);
void populate_check(mi_item_t datacpt, mi_item_t degree);

#endif // _POLYREG_POPULATE_