#ifndef COPYCOMMAND_H
#define COPYCOMMAND_H

#include <QString>

#include "command.h"
#include "undoable.h"

class CopyCommand : public Command, public Undoable
{
public:
    CopyCommand(const QString &srcFile, const QString &dstFile);

    void execute();
    void undo();

private:
    QString mSrcFile;
    QString mDstFile;
};

#endif // COPYCOMMAND_H
