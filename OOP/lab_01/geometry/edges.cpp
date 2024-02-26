#include "edges.h"

return_codes_t edges_alloc(edges_t &edges)
{
    if (edges.size <= 0)
        return ERROR_EDGES_SIZE;

    edge_t *tmp = (edge_t *) malloc(edges.size * sizeof(edge_t));

    if (!tmp)
        return ERROR_MEM_ALLOC;

    edges.data = tmp;

    return SUCCESS;
}

void edges_free(edges_t &edges)
{
    free(edges.data);
    edges_set_default(edges);
}

void edges_set_default(edges_t &edges)
{
    edges.data = NULL;
    edges.size = 0;
}

return_codes_t edges_fread(edges_t &edges, FILE *in)
{
    if (in == NULL)
        return ERROR_FILE_OPEN;

    return_codes_t rc = edges_count_fread(edges, in);
    if (!rc)
    {
        rc = edges_alloc(edges);
        if (!rc)
        {
            rc = edges_data_fread(edges, in);
            if (rc)
                edges_free(edges);
        }
    }

    return rc;
}

return_codes_t edges_count_fread(edges_t &edges, FILE *in)
{
    if (in == NULL)
        return ERROR_FILE_OPEN;
    else if (fscanf(in, "%d", &edges.size) != 1)
        return ERROR_FILE_READ;
    else if (edges.size <= 0)
        return ERROR_EDGES_SIZE;

    return SUCCESS;
}

return_codes_t edges_data_fread(edges_t &edges, FILE *in)
{
    return_codes_t rc = SUCCESS;
    if (in == NULL)
        rc = ERROR_FILE_OPEN;
    else if (edges.size <= 0)
        rc = ERROR_EDGES_SIZE;
    else if (!edges.data)
        rc = ERROR_MEM_ALLOC;
    else
        for (int i = 0; rc == SUCCESS && i < edges.size; i++)
            rc = edge_fread(edges.data[i], in);

    return rc;
}

return_codes_t edges_fwrite(edges_t &edges, FILE *out)
{
    return_codes_t rc = SUCCESS;
    if (!edges.data)
        rc = ERROR_EMPTY_DATA;
    else if (fprintf(out, "%d\n", edges.size) < 0)
        rc = ERROR_FILE_WRITE;
    else
        for (int i = 0; rc == SUCCESS && i < edges.size; i++)
            rc = edge_fwrite(edges.data[i], out);
    return rc;
}
