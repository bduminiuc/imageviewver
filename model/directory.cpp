#include "directory.h"

#include <QDirIterator>


Directory::Directory(const QStringList &formats) :
    mFormats(formats)
{
}

void Directory::open(const QString &path)
{
    mPath = path;

    scan();
}

void Directory::close()
{
    mImages.clear();
    mPath = "";
}

void Directory::scan()
{
    QDirIterator it(mPath, mFormats, QDir::Files, QDirIterator::Subdirectories);

    if (! it.hasNext()) {
        throw FilesNotFoundException();
    }

    while(it.hasNext()) {
        QString path = it.next();
        mImages.push_back(Image(path));
    }

    emit scanned();
}

Directory::iterator Directory::begin()
{
    return mImages.begin();
}

Directory::iterator Directory::end()
{
    return mImages.end();
}

Directory::const_iterator Directory::cbegin() const
{
    return mImages.cbegin();
}

Directory::const_iterator Directory::cend() const
{
    return mImages.cend();
}

QString Directory::getPath() const
{
    return mPath;
}


/*****************************
 *
 *****************************/
Directory::FilesNotFoundException *Directory::FilesNotFoundException::clone() const
{
    return new FilesNotFoundException(*this);
}

void Directory::FilesNotFoundException::raise() const
{
    throw *this;
}
