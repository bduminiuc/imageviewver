#include "imagelist.h"

ImageList::ImageList()
{

}

ImageList::~ImageList()
{
    clear();
}

void ImageList::append(const QString &imagePath)
{
    mImages.append(new Image(imagePath));
}

void ImageList::clear()
{
    if (mImages.isEmpty()) {
        return;
    }

    for (auto image : mImages) {
        delete image;
    }

    mImages.clear();
}

bool ImageList::isEmpty() const
{
    return mImages.isEmpty();
}

ImageList::size_type ImageList::size() const
{
    return mImages.size();
}

ImageList::iterator ImageList::begin()
{
    return mImages.begin();
}

ImageList::iterator ImageList::end()
{
    return mImages.end();
}
