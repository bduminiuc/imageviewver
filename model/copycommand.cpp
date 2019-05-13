#include "copycommand.h"

#include <QFile>

CopyCommand::CopyCommand(const QString &srcFile, const QString &dstFile) :
    mSrcFile(srcFile),
    mDstFile(dstFile)
{
}

void CopyCommand::execute()
{
    if (QFile::exists(mSrcFile)) {
        QFile::copy(mSrcFile, mDstFile);
    }
}

void CopyCommand::undo()
{
    if (QFile::exists(mDstFile)) {
        QFile::remove(mDstFile);
    }
}
