#ifndef LOADEXCEPTION_H
#define LOADEXCEPTION_H

#include "BaseException.h"

class FileError : public BaseException {
public:
    explicit FileError(const std::string &file, const int line, const std::string &msg) :
        BaseException(file, line, msg)
    {
        this->errorMsg = "FileError: " + this->errorMsg;
    }
};

class WrongSourceError : public BaseException {
public:
    explicit WrongSourceError(const std::string &file, const int line, const std::string &msg) :
        BaseException(file, line, msg)
    {
        this->errorMsg = "Wrong source file loaded: " + this->errorMsg;
    }
};

#endif // LOADEXCEPTION_H
