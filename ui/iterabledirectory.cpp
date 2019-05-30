#include "iterabledirectory.h"

#include <QDirIterator>
#include <QDebug>

IterableDirectory::IterableDirectory(QObject *parent) :
    QObject(parent)
{

}

void IterableDirectory::open(const QString &directory)
{
    mDirectory = QDir(directory);
    scan();
    emit itemChanged(getAbsoluteFilePath());
}

void IterableDirectory::open(const QDir &directory)
{
    mDirectory = directory;
    scan();
    emit itemChanged(getAbsoluteFilePath());
}

void IterableDirectory::setNameFilters(const QStringList &nameFilters)
{
    mNameFilters = nameFilters;
}

IterableDirectory::size_type IterableDirectory::count() const
{
    return mFiles.size();
}

IterableDirectory::iterator IterableDirectory::begin()
{
    return mFiles.begin();
}

IterableDirectory::iterator IterableDirectory::end()
{
    return mFiles.end();
}

IterableDirectory::const_iterator IterableDirectory::cbegin() const
{
    return mFiles.cbegin();
}

IterableDirectory::const_iterator IterableDirectory::cend() const
{
    return mFiles.cend();
}

QString IterableDirectory::getCurrent() const
{
    return getAbsoluteFilePath();
}

int IterableDirectory::getCurrentNumber() const
{
    return mCurrentIterator - mFiles.cbegin() + 1;
}

void IterableDirectory::next()
{
    if ((mCurrentIterator + 1) == mFiles.end()) {
        mCurrentIterator = mFiles.begin();
    }
    else {
        mCurrentIterator++;
    }

    emit itemChanged(getAbsoluteFilePath());
}

void IterableDirectory::previous()
{
    if (mCurrentIterator == mFiles.begin()) {
        mCurrentIterator = mFiles.end() - 1;
    }
    else {
        mCurrentIterator--;
    }

    emit itemChanged(getAbsoluteFilePath());
}

void IterableDirectory::scan()
{
    QString path = mDirectory.path();
    QDirIterator it(path, mNameFilters, QDir::Files, QDirIterator::Subdirectories);

    if (! it.hasNext()) {
        std::string message = path.toStdString() + " does not contain files";
        throw std::runtime_error(message);
    }

    while(it.hasNext()) {
        QString filePath = mDirectory.relativeFilePath(it.next());
        mFiles.append(filePath);
    }

    mCurrentIterator = mFiles.begin();
}

QString IterableDirectory::getAbsoluteFilePath() const
{
    return mDirectory.path() + QDir::separator() + *mCurrentIterator;
}
