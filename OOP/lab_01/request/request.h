#ifndef REQUEST_H
#define REQUEST_H

#include "return_codes.h"
#include "request_data.h"

#include "figure.h"
#include "draw.h"

enum action
{
    MOVE,
    ROTATE,
    SCALE,
    SAVE,
    LOAD,
    DRAW,
    QUIT
};

using action_t = enum action;

struct request
{
    action_t action;
    union
    {
        const char *filename;
        move_data_t move;
        rotate_data_t rotate;
        scale_data_t scale;
        draw_view_t view;
    };
};

using request_t = struct request;

return_codes_t request_manager(request_t &request);

#endif // REQUEST_H
