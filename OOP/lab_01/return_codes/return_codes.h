#ifndef RETURN_CODES_H
#define RETURN_CODES_H

#include <QMessageBox>

enum return_codes
{
    SUCCESS,
    ERROR_MEM_ALLOC,
    ERROR_EMPTY_FIELD,
    ERROR_INVALID_COMMAND,
    ERROR_FILE_OPEN,
    ERROR_FILE_READ,
    ERROR_FILE_WRITE,
    ERROR_FILE_NAME,
    ERROR_POINTS_SIZE,
    ERROR_EMPTY_DATA,
    ERROR_FIGURE_NOT_LOADED,
    ERROR_EDGES_SIZE,
    ERROR_WRONG_SCENE,
};

using return_codes_t = enum return_codes;

void error_show(return_codes_t code);

#endif // RETURN_CODES_H
