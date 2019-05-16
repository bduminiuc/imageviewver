#include "removecommand.h"

#include <QFile>


RemoveCommand::RemoveCommand(const QString &file) :
    mFile(file)
{

}

void RemoveCommand::execute()
{
    if (QFile::exists(mFile)) {
        QFile::remove(mFile);
    }
}
