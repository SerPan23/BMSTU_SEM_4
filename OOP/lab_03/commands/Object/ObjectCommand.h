#ifndef OBJECTCOMMAND_H
#define OBJECTCOMMAND_H

#include "Command.h"

#include "Vector3.h"

class ObjectCommand : public Command {};

class ObjectDeleteCommand : public ObjectCommand
{
public:
    ObjectDeleteCommand() = delete;
    explicit ObjectDeleteCommand(int id);

    void execute() override;

private:
    int objectId;
};

class ObjectMoveCommand : public ObjectCommand
{
public:
    ObjectMoveCommand() = delete;
    ObjectMoveCommand(int id, const Vector3 &offset);

    void execute() override;

private:
    Vector3 offset_;
    int objectId;
};

class ObjectRotateCommand : public ObjectCommand
{
public:
    ObjectRotateCommand() = delete;

    ObjectRotateCommand(int id, const Vector3 &rotation);

    void execute() override;

private:
    Vector3 rotation_;
    int objectId;
};

class ObjectScaleCommand : public ObjectCommand
{
public:
    ObjectScaleCommand() = delete;

    ObjectScaleCommand(int id, const Vector3 &scale);

    void execute() override;

private:
    Vector3 scale_;
    int objectId;
};

#endif // OBJECTCOMMAND_H
