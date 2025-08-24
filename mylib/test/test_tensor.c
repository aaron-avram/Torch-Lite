#include "tensor.h"
#include <assert.h>
#include <stdio.h>

// Test creating a scalar
void test_tensor_create_scalar() {
    double* val = malloc(sizeof(double));
    *val = 42.0;
    Tensor *t = tensor_create(val, true, DOUBLE); 
    double *data = tensor_get_data(t);
    assert(*data == *val);
    tensor_free(t);
    free(val);
    printf("test_tensor_create_scalar passed!\n");
}

// Test addition of two scalars
void test_tensor_add_scalar() {
    double* val1 = malloc(sizeof(double));
    *val1 = 3.0;
    double* val2 = malloc(sizeof(double));
    *val2 = 4.0;

    Tensor *a = tensor_scalar(val1, true, DOUBLE);
    Tensor *b = tensor_scalar(val2, true, DOUBLE);

    Tensor *c = tensor_add(a, b);
    double *cdata = tensor_get_data(c);

    assert(*cdata == 7.0);

    tensor_free(a);
    tensor_free(b);
    tensor_free(c);

    free(val1);
    free(val2);

    printf("test_tensor_add_scalar passed!\n");
}

// Test freeing twice is safe (if your tensor_free is written defensively)
void test_tensor_double_free() {
    double* val = malloc(sizeof(double));
    *val = 99.0;
    Tensor *t = tensor_create(val, true, DOUBLE);
    tensor_free(t);
    tensor_free(t); // should do nothing / not crash if free sets pointers to NULL
    printf("test_tensor_double_free passed!\n");

    free(val);
}

int main(void) {
    test_tensor_create_scalar();
    test_tensor_add_scalar();
    test_tensor_double_free();
    printf("All scalar tensor tests passed!\n");
    return 0;
}
