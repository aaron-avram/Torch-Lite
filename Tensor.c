#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Tensor Tensor;
typedef struct ParentSet ParentSet;

enum TensorOp {
    NONE, MUL, ADD, DIV, SUB
};

enum TensorScalar {
    INT, FLOAT, LONG, DOUBLE
};

enum TensorKind {
    SCALAR, ARRAY
};

/**
 * Tensor Object
 * value can be numeric or an array
 * grad is of same type as value
 * dtype is the underlying type in the tensor
 * kind is the way the tensor stores data: scalar-valued or array-valued
 * parents is a set of the Tensors that created the tensor
 * op is the type of operation used to create the tensor
 */
struct Tensor
{
    void* value;
    void* grad;
    enum TensorScalar dtype;
    enum TensorKind kind;
    ParentSet* parents;
    enum TensorOp op;
};

/**
 * Parent Set
 * Only supports 0, 1 or 2 parents
 */
struct ParentSet
{
    Tensor* parent1;
    Tensor* parent2;
};

int main()
{
    return 0;    
}

/**
 * Initialize a Tensor Scalar
 * Value object to create tensor with
 * Storing gradient is optional
 */
Tensor* tensor_scalar(void* value, bool requiresGrad, enum TensorScalar dtype)
{
    Tensor* t = malloc(sizeof(Tensor));
    if (requiresGrad == true)
    {
        t->grad = malloc(sizeof(void));
    }
    t->dtype = dtype;
    t->parents = NULL;
    t->op = NONE;

    return t;
}

/**
 * Add two tensors to create a new one
 * Return the Tensor
 */
Tensor* add(Tensor* t1, Tensor* t2) {
    // Need to check dtypes and kinds are valid
}