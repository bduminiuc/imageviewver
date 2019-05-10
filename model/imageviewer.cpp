#include <QDirIterator>
#include <QFileInfo>

#include <QDebug>

#include "imageviewer.h"

ImageViewer::ImageViewer(QObject *parent) :
    QObject (parent)
{
    connect(&filesystem, &FileSystemManager::scanFinished,
            this, &ImageViewer::scanFinished);
}

bool ImageViewer::openDirectory(const QString &dir)
{
    filesystem.scanDirectory(dir);

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

void ImageViewer::copyChecked(const QString &dir)
{
    QStringList checkedImages = getCheckedImages();
    filesystem.copyFiles(checkedImages, dir);
}

void ImageViewer::moveChecked(const QString &dir)
{
    QStringList checkedImages = getCheckedImages();
    filesystem.moveFiles(checkedImages, dir);
    eraseCheckedImages();
}

void ImageViewer::removeChecked()
{
    QStringList checkedImages = getCheckedImages();
    filesystem.removeFiles(checkedImages);
    eraseCheckedImages();
}

Image* ImageViewer::next()
{
    if (mCurrentIterator == mImageList.end() - 1) {
        mCurrentIterator = mImageList.begin();
    }
    else {
        mCurrentIterator++;
    }

    return *mCurrentIterator;
}

Image* ImageViewer::prev()
{
    if (mCurrentIterator == mImageList.begin()) {
        mCurrentIterator = mImageList.end() - 1;
    }
    else {
        mCurrentIterator--;
    }

    return *mCurrentIterator;
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

void ImageViewer::setCheckedAll(bool checked)
{
    for (auto iter = mImageList.begin(); iter != mImageList.end(); iter++) {
        (*iter)->setChecked(checked);
    }
}

void ImageViewer::scanFinished(const ImageList &files)
{
    mImageList = files;

    if (! files.isEmpty()) {
        mCurrentIterator = mImageList.begin();
    }

    emit updated();
}

QStringList ImageViewer::getCheckedImages()
{
    QStringList checkedImages;

    for (auto iter = mImageList.begin(); iter != mImageList.end(); iter++) {
        Image *image = *iter;

        if (image->isChecked()) {
            checkedImages.append(image->getPath());
        }
    }

    return checkedImages;
}

void ImageViewer::eraseCheckedImages()
{
    for (auto iter = mImageList.begin(); iter != mImageList.end(); ) {
        Image *image = *iter;

        if (image->isChecked()) {
            iter = mImageList.erase(iter);
        }
        else {
            iter++;
        }
    }
}

int ImageViewer::getCurrentIndex()
{
    return mCurrentIterator - mImageList.begin() + 1;
}
