#ifndef EDGES_H
#define EDGES_H

#include "edge.h"

struct edges
{
    edge_t *data;
    int size;
};

using edges_t = struct edges;

return_codes_t edges_alloc(edges_t &edges);
void edges_free(edges_t &edges);

edges_t edges_set_default();

return_codes_t edges_fread(edges_t &edges, FILE *in);
return_codes_t edges_fwrite(const edges_t &edges, FILE *out);

#endif // EDGES_H
