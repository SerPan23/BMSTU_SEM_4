#include "return_codes.h"

void error_show(return_codes_t code)
{
    switch (code)
    {

        case ERROR_FILE_OPEN:
            QMessageBox::critical(NULL, "Ошибка!", "Не удалось открыть файл!");
            break;
        case ERROR_FILE_READ:
            QMessageBox::critical(NULL, "Ошибка!", "Не удалось прочитать файл!");
            break;
        case ERROR_FILE_WRITE:
            QMessageBox::critical(NULL, "Ошибка!", "При записи файла даны некорректные данные!");
            break;
        case ERROR_FILE_NAME:
            QMessageBox::critical(NULL, "Ошибка!", "Не корректно задано имя файла!");
            break;
        case ERROR_MEM_ALLOC:
            QMessageBox::critical(NULL, "Ошибка!", "Не удалось выделить память!");
            break;
        case ERROR_POINTS_SIZE:
            QMessageBox::critical(NULL, "Ошибка!", "Количествово точек в файле должно быть больше 0!");
            break;
        case ERROR_EDGES_SIZE:
            QMessageBox::critical(NULL, "Ошибка!", "Количествово ребер в файле должно быть больше 0!");
            break;
        case ERROR_WRONG_SCENE:
            QMessageBox::critical(NULL, "Ошибка!", "При попытке нарисовать, фигуру произошла ошибка!");
            break;
        case ERROR_EMPTY_DATA:
            QMessageBox::information(NULL, "Информация!", "Нет данных фигуры для записи!");
            break;
        case ERROR_FIGURE_NOT_LOADED:
            QMessageBox::information(NULL, "Информация!", "Фигура не загружена!");
            break;
        default:
            QMessageBox::critical(NULL, "Ошибка!", "Что-то пошло не так");
    }
}
