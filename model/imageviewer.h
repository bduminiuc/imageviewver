#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QStringList>
#include <QtConcurrent>

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

    void setCheckedAll(bool checked);

    QFutureWatcher<void> *getWatcher();

signals:
    void updated();

public slots:
    void scanFinished(const ImageList &files);

private slots:
    void updateCheckedImages();
    void eraseCheckedImages();

private:

    ImageList mImageList;
    QVector<Image*> mCheckedImages;

    ImageList::iterator mCurrentIterator;

    FileSystemManager filesystem;

    QFutureWatcher<void> watcher;
};

#endif // IMAGEVIEWER_H
