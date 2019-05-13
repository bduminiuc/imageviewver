#ifndef REMOVECOMMAND_H
#define REMOVECOMMAND_H

#include <QString>

#include "command.h"


class RemoveCommand : public Command
{
public:
    RemoveCommand(const QString &file);

    void execute();

private:
    QString mFile;
};

#endif // REMOVECOMMAND_H
