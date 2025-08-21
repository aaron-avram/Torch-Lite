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
    TopoList* topo = malloc(sizeof(TopoList));
    _build_topo(t, topo);

    return topo;
}

void _build_topo(Tensor* t, TopoList* topo)
{
    ParentSet* parents = get_parents(t);

    if (parents == NULL || (parents->parent1 == NULL && parents->parent2 == NULL))
    {
        topo_add(topo, t);
    }

    else
    {
       if (parents->parent1 != NULL)
       {
            _build_topo(parents->parent1, topo);
       }

       if (parents->parent2 != NULL)
       {
            _build_topo(parents->parent2, topo);
       }
    }
}
