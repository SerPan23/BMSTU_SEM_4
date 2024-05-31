#ifndef CASTEXCEPTION_H
#define CASTEXCEPTION_H

#include "BaseException.h"

class WrongTypeException : public BaseException {
public:
    explicit WrongTypeException(const std::string &file, const int line, const std::string &msg) :
        BaseException(file, line, msg)
    {
        this->errorMsg = "WrongCastTypeError: " + this->errorMsg;
    }
};

#endif // CASTEXCEPTION_H
