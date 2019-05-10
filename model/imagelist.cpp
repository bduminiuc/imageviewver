#include "imagelist.h"

ImageList::ImageList()
{

}

ImageList::ImageList(const ImageList &obj)
{
    *this = obj;
}

ImageList::~ImageList()
{
    clear();
}

void ImageList::append(const QString &imagePath)
{
    mImages.append(new Image(imagePath));
}

void ImageList::append(const Image &image)
{
    mImages.append(new Image(image));
}

ImageList::iterator ImageList::erase(ImageList::iterator iter)
{
    Image *image = *iter;
    delete image;

    return mImages.erase(iter);
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

ImageList &ImageList::operator=(const ImageList &right) {
    //проверка на самоприсваивание
    if (this == &right) {
        return *this;
    }

    for (auto image : right.mImages) {
        append(*image);
    }

    return *this;
}
