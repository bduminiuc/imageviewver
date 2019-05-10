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
    /*for (auto iter = mImageList.begin(); iter != mImageList.end(); iter++) {
        Image *image = *iter;

        if (image->isChecked()) {
            QString imagePath = image->getPath();
            QFileInfo fileinfo(imagePath);

            QString filename = fileinfo.fileName();
            QString newPath = dir + QDir::separator() + filename;

            QFile::copy(imagePath, newPath);
        }
    }*/
}

void ImageViewer::moveChecked(const QString &dir)
{
    /*for (auto iter = mImageList.begin(); iter != mImageList.end();) {
        Image *image = *iter;

        if (image->isChecked()) {
            QString imagePath = image->getPath();
            QFileInfo fileinfo(imagePath);

            QString newPath = dir + QDir::separator() + fileinfo.fileName();

            QFile::rename(imagePath, newPath);
            iter = mImageList.erase(iter);
        }
        else {
            iter++;
        }
    }*/
}

void ImageViewer::removeChecked()
{
    /*for (auto iter = mImageList.begin(); iter != mImageList.end(); ) {
        Image *image = *iter;

        if (image->isChecked()) {
            QFile::remove(image->getPath());
            iter = mImageList.erase(iter);
        }
        else {
            iter++;
        }
    }*/
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

void ImageViewer::scanFinished(const ImageList &files)
{
    if (files.isEmpty()) {
        return;
    }


    mImageList = files;


    mCurrentIterator = mImageList.begin();

    emit updated();
}

int ImageViewer::getCurrentIndex()
{
    return mCurrentIterator - mImageList.begin() + 1;
}
