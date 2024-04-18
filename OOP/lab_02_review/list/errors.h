#ifndef ERRORS_H
#define ERRORS_H

#include <exception>
#include <string>

class BaseError : public std::exception
{
public:
    BaseError(const std::string &time,
              const std::string &filename,
              const std::string &classname,
              const int line,
              const std::string &info)
    {
        error_msg = "\nTime: " + time +
                    "File: " + filename +
                    "\nClass: " + classname +
                    "\nLine: " + std::to_string(line) +
                    "\nInfo: " + info;
    }

    virtual const char *what() const noexcept override
    {
        return error_msg.c_str();
    }

protected:
    std::string error_msg;
};

class MemoryError : public BaseError
{
public:
    MemoryError(const std::string &time,
                const std::string &filename,
                const std::string &classname,
                const int line,
                std::string info = "Memory allocation error!\n"): 
        BaseError(time, filename, classname, line, info){};
};

class EmptyList : public BaseError
{
public:
    EmptyList(const std::string &time,
              const std::string &filename,
              const std::string &classname,
              const int line,
              std::string info = "List is empty!\n"): 
        BaseError(time, filename, classname, line, info){};
};

class InvalidIterator : public BaseError
{
public:
    InvalidIterator(const std::string &time,
              const std::string &filename,
              const std::string &classname,
              const int line,
              std::string info = "Invalid iterator!\n"): 
        BaseError(time, filename, classname, line, info){};
};

class InvalidPointer : public BaseError
{
public:
    InvalidPointer(const std::string &time,
              const std::string &filename,
              const std::string &classname,
              const int line,
              std::string info = "Invalid pointer!\n"): 
        BaseError(time, filename, classname, line, info){};
};

class InvalidSize : public BaseError
{
public:
    InvalidSize(const std::string &time,
              const std::string &filename,
              const std::string &classname,
              const int line,
              std::string info = "Passed size is invalid!\n"): 
        BaseError(time, filename, classname, line, info){};
};

#endif