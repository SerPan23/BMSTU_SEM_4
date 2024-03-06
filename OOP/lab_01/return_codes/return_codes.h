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
    ERROR_WRONG_POINT_INDEX,
};

using return_codes_t = enum return_codes;

//TODO: get_return_text_msg with struct
//struct enum msg_type and title + msg
enum msg_type
{
    INFORMATION,
    CRITICAL,
};

using msg_type_t = enum msg_type;

struct error_msg
{
    msg_type_t type;
    char *title;
    char *text;
};

using error_msg_t = struct error_msg;

error_msg_t get_error_msg(return_codes_t code);

#endif // RETURN_CODES_H
