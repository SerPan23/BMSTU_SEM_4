#include "return_codes.h"

error_msg_t get_error_msg(return_codes_t code)
{
    error_msg_t msg;
    switch (code)
    {
        case ERROR_FILE_OPEN:
            msg = {
                CRITICAL,
                "Ошибка!",
                "Не удалось открыть файл!"
            };
            break;
        case ERROR_FILE_READ:
            msg = {
                CRITICAL,
                "Ошибка!",
                "Не удалось прочитать файл!"
            };
            break;
        case ERROR_FILE_WRITE:
            msg = {
                CRITICAL,
                "Ошибка!",
                "При записи файла даны некорректные данные!"
            };
            break;
        case ERROR_FILE_NAME:
            msg = {
                CRITICAL,
                "Ошибка!",
                "Не корректно задано имя файла!"
            };
            break;
        case ERROR_MEM_ALLOC:
            msg = {
                CRITICAL,
                "Ошибка!",
                "Не удалось выделить память!"
            };
            break;
        case ERROR_POINTS_SIZE:
            msg = {
                CRITICAL,
                "Ошибка!",
                "Количествово точек в файле должно быть больше 0!"
            };
            break;
        case ERROR_EDGES_SIZE:
            msg = {
                CRITICAL,
                "Ошибка!",
                "Количествово ребер в файле должно быть больше 0!"
            };
            break;
        case ERROR_WRONG_SCENE:
            msg = {
                CRITICAL,
                "Ошибка!",
                "При попытке нарисовать, фигуру произошла ошибка!"
            };
            break;
        case ERROR_EMPTY_DATA:
            msg = {
                INFORMATION,
                "Информация!",
                "Нет данных фигуры для записи!"
            };
            break;
        case ERROR_FIGURE_NOT_LOADED:
            msg = {
                INFORMATION,
                "Информация!",
                "Фигура не загружена!"
            };
            break;
        case ERROR_WRONG_POINT_INDEX:
            msg = {
                CRITICAL,
                "Ошибка!",
                "Не корректна задана фигура!"
            };
            break;
        default:
            msg = {
                CRITICAL,
                "Ошибка!",
                "Что-то пошло не так!"
            };
    }

    return msg;
}
