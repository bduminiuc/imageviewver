#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QStringList>

#include "imagelist.h"
#include "filesystemmanager.h"

using namespace std;

class ImageViewer : public QObject
{
    Q_OBJECT

public:
    ImageViewer(QObject *parent = nullptr);
    bool openDirectory(const QString & dir);
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

signals:
    void updated();

public slots:
    void scanFinished(const ImageList &files);

private:
    QStringList getCheckedImages();
    void eraseCheckedImages();

    ImageList mImageList;

    ImageList::iterator mCurrentIterator;
    FileSystemManager filesystem;
};

#endif // IMAGEVIEWER_H
