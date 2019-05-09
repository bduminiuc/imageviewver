#include <QDirIterator>

#include "imageviewer.h"

ImageViewer::ImageViewer()
{

}

bool ImageViewer::openDirectory(const QString &path)
{
    QDirIterator it(path, formats, QDir::Files, QDirIterator::Subdirectories);

    while (it.hasNext()){
        mImageList.append(it.next());
    }

    if (hasImages()) {
        mCurrentIterator = mImageList.begin();
        return true;
    }

    return false;
}

void ImageViewer::closeDirectory()
{
    mImageList.clear();
}

QString ImageViewer::next()
{
    if (mCurrentIterator == mImageList.end() - 1) {
        mCurrentIterator = mImageList.begin();
    }
    else {
        mCurrentIterator++;
    }

    return (*mCurrentIterator)->getPath();
}

QString ImageViewer::prev()
{
    if (mCurrentIterator == mImageList.begin()) {
        mCurrentIterator = mImageList.end() - 1;
    }
    else {
        mCurrentIterator--;
    }

    return (*mCurrentIterator)->getPath();
}

Image* ImageViewer::getCurrentImage()
{
    return *mCurrentIterator;
}

bool ImageViewer::hasImages()
{
    return ! mImageList.isEmpty();
}

int ImageViewer::imagesCount()
{
    return mImageList.size();
}

int ImageViewer::getCurrentIndex()
{
    return mCurrentIterator - mImageList.begin() + 1;
}
