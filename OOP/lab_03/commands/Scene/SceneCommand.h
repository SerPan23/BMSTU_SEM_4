#ifndef SCENECOMMAND_H
#define SCENECOMMAND_H

#include "Command.h"

class SceneCommand : public Command {};

class SceneRenderCommand : public SceneCommand
{
public:
    SceneRenderCommand() = default;
    void execute() override;
};

#endif // SCENECOMMAND_H
