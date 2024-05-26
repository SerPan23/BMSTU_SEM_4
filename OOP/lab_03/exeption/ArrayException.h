#ifndef ARRAYEXCEPTION_H
#define ARRAYEXCEPTION_H

#include "BaseException.h"

class IndexException : public BaseException {
public:
    explicit IndexException(const std::string &file, const int line, const std::string &msg) :
        BaseException(file, line, msg)
    {
        this->errorMsg = "IndexError: " + this->errorMsg;
    }
};

class DeleteException : public BaseException {
public:
    explicit DeleteException(const std::string &file, const int line, const std::string &msg) :
        BaseException(file, line, msg)
    {
        this->errorMsg = "DeleteError: " + this->errorMsg;
    }
};

#endif // ARRAYEXCEPTION_H
