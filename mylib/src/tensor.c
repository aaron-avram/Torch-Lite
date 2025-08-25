#include <tensor.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "_parent.h"
#include "_topo.h"
#include "tensor_internal.h"

void _free_tensor(Tensor* t);

struct Tensor
{
    void* value;
    void* grad;
    enum TensorScalar dtype;
    enum TensorKind kind;
    ParentSet* parents;
    enum TensorOp op;
    bool visited;
};

Tensor* tensor_scalar(void* value, bool requires_grad, enum TensorScalar dtype)
{
    Tensor* t = malloc(sizeof(Tensor));
    t->value = value;
    if (requires_grad == true)
    {
        t->grad = malloc(sizeof(void));
    }
    t->dtype = dtype;
    t->parents = NULL;
    t->op = NONE;

    return t;
}

void free_tensor(Tensor* t, bool deep) 
{
    if (!t) return;

    if (deep == false)
    {
        if (t->grad)
        {
            free(t->grad);
            t->grad = NULL;
        }
        
        if (t->value)
        {
            free(t->value);
            t->value = NULL;
        }

        if (t->parents)
        {
            free(t->parents);
            t->parents = NULL;
        }
        free(t);
    }

    else
    {
        _free_tensor(t);
    }
}

void _free_tensor(Tensor *t) {
    TopoList *topo = build_topo(t);

    // Phase 1: collect into an array
    size_t count = 0;
    
    Tensor **nodes = malloc(count * sizeof(Tensor*));
    size_t i = 0;
    for (TopoNode *cur = topo->head; cur; cur = cur->next) {
        nodes[i++] = cur->cur;
    }

    // Phase 2: free each tensor
    for (i = 0; i < count; i++) {
        free_tensor(nodes[i], false);
    }

    free(nodes);
    del_topo(topo);
}


void* get_data(Tensor* t)
{
    return t->value;
}

ParentSet* get_parents(Tensor* t) 
{
    return t->parents;
}

bool is_visited(Tensor* t)
{
    return t->visited;
}

void set_visited(Tensor* t, bool v)
{
    t->visited = v;
}



// ASSUMING ONLY DOUBLES
Tensor* add(Tensor* t1, Tensor* t2) 
{
    Tensor* out = malloc(sizeof(Tensor));

    // Compute new value
    double* val1 = (double*) t1->value;
    double* val2 = (double*) t2->value;
    double* out_val = malloc(sizeof(double));
    *out_val = *val1 + *val2;

    // Build Parent Set
    ParentSet* parents = malloc(sizeof(ParentSet));
    parents->parent1 = t1;
    parents->parent2 = t2;

    out->value = out_val;
    out->dtype=DOUBLE; // USE promotion later
    out->parents = parents;
    out->op = ADD;
    return out;

}
