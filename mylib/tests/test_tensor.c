#include <tensor.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// Test creating a scalar
void test_tensor_create_scalar() {
    double* val = malloc(sizeof(double));
    *val = 42.0;
    Tensor *t = tensor_scalar(val, true, DOUBLE); 
    double *data = (double*) get_data(t);
    assert(*data == *val);
    free_tensor(t, true);
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

    Tensor *c = add(a, b);
    double *cdata = (double*) get_data(c);

    assert(*cdata == 7.0);

    free_tensor(a, true);
    free_tensor(b, true);
    free_tensor(c, true);

    printf("test_tensor_add_scalar passed!\n");
}

// Test freeing twice is safe (if your tensor_free is written defensively)
void test_tensor_double_free() {
    double* val = malloc(sizeof(double));
    *val = 99.0;
    Tensor *t = tensor_scalar(val, true, DOUBLE);
    free_tensor(t, true);
    free_tensor(t, true); // should do nothing / not crash if free sets pointers to NULL
    printf("test_tensor_double_free passed!\n");
}

int main(void) {
    test_tensor_create_scalar();
    test_tensor_add_scalar();
    test_tensor_double_free();
    printf("All scalar tensor tests passed!\n");
    return 0;
}
