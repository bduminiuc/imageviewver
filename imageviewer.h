#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QStringList>

using namespace std;

class ImageViewer
{
public:
    ImageViewer();
    bool openDirectory(const QString & path);
    void closeDirectory();
    bool isOpened();

    QString next();
    QString prev();
    QString current();

    bool hasImages();
    int count();
    int currentIdx();

private:
    QString directory;
    QStringList formats {
        "*.jpg",
        "*.png",
        "*.bmp",
        "*.ico",
    };

    QStringList images;

    int i = 0;
};

#endif // IMAGEVIEWER_H
