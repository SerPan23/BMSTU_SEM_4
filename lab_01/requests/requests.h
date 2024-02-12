#ifndef REQUESTS_H
#define REQUESTS_H

#include "return_codes.h"

enum command
{
    CALCULATE,
    QUIT
};

struct calculate
{
    double kx;
    double ky;
};

using calculate_t = struct calculate;

struct request
{
    enum command command;
    union
    {
        drawview_t view;
        calculate_t calc;
    };
};

using request_t = struct request;

return_codes_t manager_actions(request_t &request);

#endif // COMMANDS_H
