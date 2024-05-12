#ifndef FACADE_H
#define FACADE_H

#include <memory>

#include "Command.h"

class Facade
{
public:
    void execute(const std::shared_ptr<Command> &command) {command->execute();};
};


#endif // FACADE_H
