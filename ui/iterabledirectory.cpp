#include "iterabledirectory.h"

#include <QDirIterator>


IterableDirectory::IterableDirectory(QObject *parent) :
    QObject(parent)
{

}

void IterableDirectory::open(const QString &directory)
{
    mDirectory = QDir(directory);
    scan();
}

void IterableDirectory::open(const QDir &directory)
{
    mDirectory = directory;
    scan();
}

void IterableDirectory::setNameFilters(const QStringList &nameFilters)
{
    mNameFilters = nameFilters;
}

IterableDirectory::size_type IterableDirectory::count() const
{
    return mFiles.size();
}

QString IterableDirectory::getCurrent() const
{
    return getAbsoluteFilePath();
}

int IterableDirectory::getCurrentNumber() const
{
    return mCurrentIterator - mFiles.cbegin() + 1;
}

void IterableDirectory::setCurrentItem(const QString &absPath)
{
    QString relPath = mDirectory.relativeFilePath(absPath);

    if (mFiles.contains(relPath)) {
        setCurrentIterator(std::find(mFiles.begin(), mFiles.end(), relPath));
    }
    else {
        throw std::string("mFiles does not contain ") + absPath.toStdString();
    }
}

void IterableDirectory::next()
{
    if ((mCurrentIterator + 1) == mFiles.end()) {
        setCurrentIterator(mFiles.begin());
    }
    else {
        setCurrentIterator(mCurrentIterator + 1);
    }
}

void IterableDirectory::previous()
{
    if (mCurrentIterator == mFiles.begin()) {
        setCurrentIterator(mFiles.end() - 1);
    }
    else {
        setCurrentIterator(mCurrentIterator - 1);
    }
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

    setCurrentIterator(mFiles.begin());
}

void IterableDirectory::setCurrentIterator(IterableDirectory::const_iterator current)
{
    mCurrentIterator = current;
    emit itemChanged(getAbsoluteFilePath());
}

QString IterableDirectory::getAbsoluteFilePath() const
{
    return mDirectory.path() + QDir::separator() + *mCurrentIterator;
}
