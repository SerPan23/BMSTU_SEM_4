#ifndef BASEEXCEPTION_H
#define BASEEXCEPTION_H

#include <exception>
#include <string>


class BaseException : public std::exception {
protected:
    std::string errorMsg;

public:
    BaseException(const std::string &file, const int line, const std::string &msg = "Error!")
    {
        time_t currTime = time(nullptr);
        auto localTime = localtime(&currTime);
        this->errorMsg = msg
            + "\nFile: " + file
            + "\nLine: " + std::to_string(line)
            + "\nTime: " + asctime(localTime);
    }

    const char *what() const noexcept override {
        return this->errorMsg.c_str();
    }
};

#endif // BASEEXCEPTION_H
