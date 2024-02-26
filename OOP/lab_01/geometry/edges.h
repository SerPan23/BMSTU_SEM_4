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

void edges_set_default(edges_t &edges);

return_codes_t edges_fread(edges_t &edges, FILE *in);
return_codes_t edges_count_fread(edges_t &edges, FILE *in);
return_codes_t edges_data_fread(edges_t &edges, FILE *in);

return_codes_t edges_fwrite(edges_t &edges, FILE *out);

#endif // EDGES_H
