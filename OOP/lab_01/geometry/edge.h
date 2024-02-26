#ifndef EDGE_H
#define EDGE_H

#include "return_codes.h"

struct edge
{
    int first_point_index;
    int second_point_index;
};

using edge_t = struct edge;

return_codes_t edge_fread(edge_t &edge, FILE *in);
return_codes_t edge_fwrite(edge_t &edge, FILE *out);

#endif // EDGE_H
