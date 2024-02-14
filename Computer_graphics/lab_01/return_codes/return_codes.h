#ifndef RETURN_CODES_H
#define RETURN_CODES_H

#include <QMessageBox>

enum return_codes{
    SUCCESS,
    COMMAND_UNDEFINED,
    ERROR_INVALID_COORDS,
    ERROR_MEM_ALLOC,
    ERROR_ARR_EMPTY,
    ERROR_INVALID_INDEX,
    ERROR_SCENE_WRONG,
};

using return_codes_t = enum return_codes;

void error_msg(return_codes_t code);

#endif // RETURN_CODES_H
