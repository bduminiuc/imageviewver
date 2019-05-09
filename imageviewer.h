#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QStringList>

#include "imagelist.h"

using namespace std;

class ImageViewer
{
public:
    ImageViewer();
    bool openDirectory(const QString & path);
    void closeDirectory();

    void copyChecked(const QString &dir);
    void moveChecked(const QString &dir);
    void removeChecked();

    Image* next();
    Image* prev();

    Image* getCurrentImage();
    int getCurrentIndex();

    bool hasImages();
    int imagesCount();

private:
    QStringList formats {
        "*.jpg",
        "*.png",
        "*.bmp",
        "*.ico",
    };

    ImageList mImageList;

    ImageList::iterator mCurrentIterator;
};

#endif // IMAGEVIEWER_H
