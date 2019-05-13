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
        throw FilesByFormatNotFoundException();
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

Directory::size_type Directory::count() const
{
    return mImages.size();
}


/*****************************
 *
 *****************************/
Directory::FilesByFormatNotFoundException *Directory::FilesByFormatNotFoundException::clone() const
{
    return new FilesByFormatNotFoundException(*this);
}

void Directory::FilesByFormatNotFoundException::raise() const
{
    throw *this;
}
