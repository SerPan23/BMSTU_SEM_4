#include "request.h"

return_codes_t request_manager(request_t &request)
{
    static figure_t figure = figure_create();

    return_codes_t rc = SUCCESS;

    switch (request.action)
    {
        case MOVE:
            rc = figure_move(figure, request.move);
            break;
        case ROTATE:
            rc = figure_rotate(figure, request.rotate);
            break;
        case SCALE:
            rc = figure_scale(figure, request.scale);
            break;
        case SAVE:
            rc = figure_save(figure, request.filename);
            break;
        case LOAD:
            rc = figure_load(figure, request.filename);
            break;
        case DRAW:
            rc = draw_figure(figure, request.view);
            break;
        case QUIT:
            figure_free(figure);
            break;
        default:
            rc =  ERROR_INVALID_COMMAND;
    }

    return rc;
}
