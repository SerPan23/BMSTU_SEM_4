#ifndef COMMAND_H
#define COMMAND_H

class Command
{
public:
    Command() = default;
    virtual ~Command() = default;
    virtual void execute() = 0;
};

#endif // COMMAND_H
