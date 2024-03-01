#include "edge.h"

return_codes_t edge_fread(edge_t &edge, FILE *in)
{
    if (in == NULL)
        return ERROR_FILE_OPEN;

    if (fscanf(in, "%d %d", &edge.first_point_index, &edge.second_point_index) != 2)
        return ERROR_FILE_READ;

    return SUCCESS;
}

return_codes_t edge_fwrite(const edge_t &edge, FILE *out)
{
    if (out == NULL)
        return ERROR_FILE_OPEN;

    if (fprintf(out, "%d %d\n", edge.first_point_index, edge.second_point_index) < 0)
        return ERROR_FILE_WRITE;

    return SUCCESS;
}
