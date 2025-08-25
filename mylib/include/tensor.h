/**
 * NOTES
 * -- ONLY SCALAR VALUED ATM
 * -- ONLY DOUBLE TYPE SUPPORTED ATM
 */

#include <stdbool.h>

#ifndef TENSOR_H
#define TENSOR_H

/**
 * Tensor Object
 * value can be numeric or an array
 * grad is of same type as value
 * dtype is the underlying type in the tensor
 * kind is the way the tensor stores data: scalar-valued or array-valued
 * parents is a set of the Tensors that created the tensor
 * op is the type of operation used to create the tensor
 */
typedef struct Tensor Tensor;

/**
 * Supported Tensor Operations
 */
enum TensorOp {
    NONE, MUL, ADD, DIV, SUB
};

/**
 * Supported Tensor Datatypes
 * FOR NOW ONLY USING DOUBLE
 */
enum TensorScalar {
    INT, 
    UNSIGNED_INT,
    LONG, 
    UNSIGNED_LONG, 
    LONG_LONG, 
    UNSIGNED_LONG_LONG, 
    FLOAT, 
    DOUBLE, 
    LONG_DOUBLE
};

/**
 * Supported Tensor container types
 */
enum TensorKind {
    SCALAR, ARRAY
};

// Error codes
typedef enum {
    TENSOR_OK = 0,
    TENSOR_ALLOC_ERR,
    TENSOR_DTYPE_ERR,
    TENSOR_UNKNOWN_ERROR
} TensorErrorCode;

/**
 * Initialize a Tensor Scalar
 * Value object to create tensor with
 * Storing gradient is optional
 */
Tensor* tensor_scalar(void* value, bool requires_grad, enum TensorScalar dtype);

/**
 * Free tensor
 * If deep then free children as well
 */
void free_tensor(Tensor* t, bool deep);

/**
 * Return the tensors data
 */
void* get_data(Tensor* t);

/**
 * Return if a tensor is visited in a topo sort
 */
bool is_visited(Tensor* t);

/**
 * Set a tensor's visited state
 */
void set_visited(Tensor* t, bool v);

/**
 * Add two tensors to create a new one
 * Return the Tensor
 */
Tensor* add(Tensor* t1, Tensor* t2);

TensorErrorCode tensorLastError(void);
const char* tensorLastErrorMsg(void);

#endif
