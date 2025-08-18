#include <tensor.h>

#ifndef _PARENT_H
#define _PARENT_H

/**
 * Parent Set
 * Only supports 0, 1 or 2 parents
 * Stored as two tensor pointers
 */
typedef struct ParentSet ParentSet;

struct ParentSet
{
    Tensor* parent1;
    Tensor* parent2;
};

#endif
