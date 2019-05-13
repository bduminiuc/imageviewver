#include "image.h"

#include <QFileInfo>


Image::Image()
{
}

Image::Image(const QString &path) :
    mPath(path)
{
}

bool Image::isMarked() const
{
    return mMarked;
}

void Image::setMarked(bool marked)
{
    mMarked = marked;
}

QString Image::getPath() const
{
    return mPath;
}

QString Image::getFileName() const
{
    return QFileInfo(mPath).fileName();
}

qint64 Image::getFileSize() const
{
    return QFileInfo(mPath).size();
}
