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
    updateCheckedImages();
    disconnect(&watcher, &QFutureWatcher<void>::finished, this, &ImageViewer::eraseCheckedImages);

    watcher.setFuture(QtConcurrent::map(mCheckedImages, [this, dir](const Image *image) {
        this->filesystem.copy(image->getPath(), dir);
    }));
}

void ImageViewer::moveChecked(const QString &dir)
{
    updateCheckedImages();
    connect(&watcher, &QFutureWatcher<void>::finished, this, &ImageViewer::eraseCheckedImages);

    watcher.setFuture(QtConcurrent::map(mCheckedImages, [this, dir](const Image *image) {
        this->filesystem.move(image->getPath(), dir);
    }));
}

void ImageViewer::removeChecked()
{
    updateCheckedImages();
    connect(&watcher, &QFutureWatcher<void>::finished, this, &ImageViewer::eraseCheckedImages);

    watcher.setFuture(QtConcurrent::map(mCheckedImages, [this](const Image *image) {
        this->filesystem.remove(image->getPath());
    }));
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

QFutureWatcher<void> *ImageViewer::getWatcher()
{
    return &watcher;
}

void ImageViewer::scanFinished(const ImageList &files)
{
    mImageList = files;

    if (! files.isEmpty()) {
        mCurrentIterator = mImageList.begin();
    }

    emit updated();
}

void ImageViewer::updateCheckedImages()
{
    for (auto iter = mImageList.begin(); iter != mImageList.end(); iter++) {
        Image *image = *iter;

        if (image->isChecked()) {
            mCheckedImages.push_back(image);
        }
    }
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

    mCheckedImages.clear();
}

int ImageViewer::getCurrentIndex()
{
    return mCurrentIterator - mImageList.begin() + 1;
}
