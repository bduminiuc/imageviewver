#include "image.h"

Image::Image(const QString &path) :
    mPath(path),
    mChecked(false)
{

}

const QString& Image::getPath() const
{
    return mPath;
}

bool Image::isChecked() const
{
    return mChecked;
}

void Image::setChecked(bool checked)
{
    mChecked = checked;
}
