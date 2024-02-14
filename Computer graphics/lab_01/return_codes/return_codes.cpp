#include "return_codes.h"

void error_msg(return_codes_t code)
{
    switch (code)
    {
        case COMMAND_UNDEFINED:
            QMessageBox::critical(NULL, "Ошибка!", "Команда не найден!");
            break;
        case ERROR_INVALID_COORDS:
            QMessageBox::critical(NULL, "Ошибка!", "Не правильные координаты точки!");
        default:
            QMessageBox::critical(NULL, "Ошибка!", "Что-то пошло не по плану...");
            break;
    };
}
