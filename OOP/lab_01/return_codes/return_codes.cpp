#include "return_codes.h"

void error_show(return_codes_t code)
{
    switch (code)
    {

        case ERROR_FILE_OPEN:
            QMessageBox::critical(NULL, "Ошибка!", "Не удалось открыть файл");
            break;
        // case FILE_CLOSE_ERROR:
        //     QMessageBox::critical(NULL, "Ошибка!", "Не удалось закрыть файл");
        //     break;
        case ERROR_FILE_READ:
            QMessageBox::critical(NULL, "Ошибка!", "Не удалось прочитать файл!");
            break;
        case ERROR_FILE_WRITE:
            QMessageBox::critical(NULL, "Ошибка!", "При записи файла были даны некорректные данные!");
            break;
        case ERROR_MEM_ALLOC:
            QMessageBox::critical(NULL, "Ошибка!", "Не удалось выделить память!");
            break;
        case ERROR_POINTS_SIZE:
            QMessageBox::critical(NULL, "Ошибка!", "Кол-во точек в файле должно быть > 0!");
            break;
        case ERROR_EDGES_SIZE:
            QMessageBox::critical(NULL, "Ошибка!", "Кол-во ребер в файле должно быть > 0!");
            break;
        case ERROR_WRONG_SCENE:
            QMessageBox::critical(NULL, "Ошибка!", "При попытке нарисовать, фигуру произошла ошибка!");
            break;
        // case ERROR_EMPTY_FIELD:
        //     QMessageBox::critical(NULL, "Ошибка!", "Коэффициенты масштабирования не должны равняться 0!");
        //     break;
        case ERROR_EMPTY_DATA:
            QMessageBox::information(NULL, "Информация!", "Нет данных фигуры для записи!");
            break;
        case ERROR_FIGURE_NOT_LOADED:
            QMessageBox::information(NULL, "Информация!", "Фигура не загружена!");
            break;
        default:
            QMessageBox::critical(NULL, "Ошибка!", "Что-то пошло не по плану...");
    }
}
