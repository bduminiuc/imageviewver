#ifndef MOVECOMMAND_H
#define MOVECOMMAND_H

#include <QString>

#include "command.h"
#include "undoable.h"


class MoveCommand : public Command, public Undoable
{
public:
    MoveCommand(const QString &srcFile, const QString &dstFile);

    void execute();
    void undo();

private:
    QString mSrcFile;
    QString mDstFile;
};

#endif // MOVECOMMAND_H
