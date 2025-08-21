/**
Topological sort helper structs and functions
*/

#include <tensor.h>;

#ifndef TOPO_H
#define TOPO_H

typedef struct TopoNode
{
    Tensor* cur;
    TopoNode* next;
} TopoNode;

typedef struct TopoList
{
    TopoNode* head;
} TopoList;

void topo_add(TopoList* topo, Tensor* t);
Tensor* topo_pop(TopoList* topo);
bool topo_empty(TopoList* topo);
TopoList* build_topo(Tensor* t);

#endif