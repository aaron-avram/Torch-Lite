#include <stdio.h>
#include <tensor.h>
#include "_parent.h"
#include "_topo.h"


void topo_add(TopoList* topo, Tensor* t)
{
    TopoNode* new = malloc(sizeof(TopoNode));
    new->cur = t;

    // Handle NULL case
    if (topo == NULL)
    {
        topo = malloc(sizeof(TopoList*));
    }

    // Handle empty case
    if (topo->head == NULL)
    {
        topo->head = new;
    }

    else
    {
        new->next = malloc(sizeof(TopoNode));
        new->next = &(topo->head);
        topo->head = new;
    }
}

Tensor* topo_pop(TopoList* topo)
{
    // Handle NULL and empty cases
    if (topo == NULL || topo->head == NULL)
    {
        return NULL;
    }

    else
    {
        Tensor* out = topo->head->cur;
        topo->head = topo->head->next;
        return out;
    }
}

bool topo_empty(TopoList* topo) 
{
    return topo == NULL || topo->head == NULL;
}

TopoList* build_topo(Tensor* t) {
    _topo_reset_tensor(t); // hard reset visited flags
    TopoList* topo = malloc(sizeof(TopoList)); // Initialize topo
    _build_topo(t, topo); // build topo

    return topo;
}

void _topo_reset_tensor(Tensor* t)
{
    if (t != NULL)
    {
        set_visited(t, false);
        ParentSet* parents = get_parents(t);
        if (parents != NULL) {

            Tensor* parent1 = parents->parent1;
            Tensor* parent2 = parents->parent2;
            if (parent1 != NULL)
            {
                _topo_reset_tensor(t);
            }

            if (parent2 != NULL) {
                _topo_reset_tensor(t);
            }
        }
    }
}

void _build_topo(Tensor* t, TopoList* topo)
{
    ParentSet* parents = get_parents(t);
    set_visited(t, true);

    if (parents != NULL)
    {
        Tensor* parent1 = parents->parent1;
        Tensor* parent2 = parents->parent2;
        if (parent1 != NULL && is_visited(parent1) == false)
        {
            _build_topo(parent1, topo);
        }

        if (parent2 != NULL && is_visited(parent2) == false) {
            _build_topo(parent2, topo);
        }
    }
    topo_add(topo, t);
}

void del_topo(TopoList* topo)
{
    if (topo != NULL)
    {
        _del_next(topo->head);
    }
}

void _del_next(TopoNode* node)
{
    TopoNode* cur = node;
    TopoNode* temp = NULL;
    while (cur != NULL)
    {
        temp = cur->next;
        free(cur); // Only free container
        cur = temp;
    }
}