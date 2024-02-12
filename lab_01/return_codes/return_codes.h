#ifndef RETURN_CODES_H
#define RETURN_CODES_H

#include <QMessageBox>

enum return_codes{
    SUCCESS,
    COMMAND_UNDEFINED,
    ERROR_INVALID_COORDS,
};

using return_codes_t = enum return_codes;

void error_msg(return_codes_t code);

#endif // RETURN_CODES_H
