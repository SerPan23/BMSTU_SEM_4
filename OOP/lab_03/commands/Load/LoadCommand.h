#ifndef LOADCOMMAND_H
#define LOADCOMMAND_H

#include "Command.h"

#include <string>

class LoadCommand : public Command {};

class LoadMeshCommand : public LoadCommand
{
public:
    LoadMeshCommand() = delete;
    explicit LoadMeshCommand(const std::string& path);

    void execute() override;
    int getResult() override;

private:
    std::string path_;
    int result;
};

#endif // LOADCOMMAND_H
