#ifndef CAMERACOMMAND_H
#define CAMERACOMMAND_H

#include "Command.h"
#include "Vector3.h"

class CameraCommand : public Command {};

class CameraNewCommand : public CameraCommand
{
public:
    CameraNewCommand() = default;

    void execute() override;
    int getResult() override;

private:
    int cameraId = -1;
};

class CameraDeleteCommand : public CameraCommand
{
public:
    CameraDeleteCommand() = delete;
    explicit CameraDeleteCommand(const int id);

    void execute() override;

private:
    int cameraId = -1;
};

class CameraSetActiveCommand : public CameraCommand
{
public:
    CameraSetActiveCommand() = delete;
    explicit CameraSetActiveCommand(const int id);

    void execute() override;

private:
    int cameraId = -1;
};

class CameraMoveCommand : public CameraCommand
{
public:
    CameraMoveCommand() = delete;
    CameraMoveCommand(const int id, Vector3 offset);

    void execute() override;

private:
    int cameraId = -1;
    Vector3 offset_;
};

class CameraRotateCommand : public CameraCommand
{
public:
    CameraRotateCommand() = delete;
    CameraRotateCommand(const int id, float xOffset, float yOffset);

    void execute() override;

private:
    int cameraId = -1;
    float xOffset_ = 0;
    float yOffset_ = 0;
};

#endif // CAMERACOMMAND_H
