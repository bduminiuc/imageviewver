#include "movecommand.h"

#include <QFile>


MoveCommand::MoveCommand(const QString &srcFile, const QString &dstFile) :
    mSrcFile(srcFile),
    mDstFile(dstFile)
{
}

void MoveCommand::execute()
{
    if (QFile::exists(mSrcFile)) {
        QFile::rename(mSrcFile, mDstFile);
    }
}

void MoveCommand::undo()
{
    if (QFile::exists(mDstFile)) {
        QFile::remove(mDstFile);
    }
}
