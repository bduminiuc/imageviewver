#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <string>
#include <vector>

#include <QDirIterator>

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

private:
    QString directory;
    QStringList formats {
        "*.jpg",
        "*.png",
        "*.bmp",
        "*.ico",
    };

    QStringList images;
    /*
    QStringList images {
        "E:/git-workspace/qt/image-viewer/images/Copy_24x24.png",
        "E:/git-workspace/qt/image-viewer/images/59Xt_3MUvkk.jpg",
        "E:/git-workspace/qt/image-viewer/images/2016-07-18-17-19-47-393.jpg",
        "E:/git-workspace/qt/image-viewer/images/Next_24x24.png",
        "E:/git-workspace/qt/image-viewer/images/Picture-Viewer-icon.ico",
        "E:/git-workspace/qt/image-viewer/images/Open_24x24.png",
        "E:/git-workspace/qt/image-viewer/images/Previous_24x24.png",
        "E:/git-workspace/qt/image-viewer/images/Remove_24x24.png",
        "E:/git-workspace/qt/image-viewer/images/Zoom In_24x24.png",
    };
    */

    int i = 0;
};

#endif // IMAGEVIEWER_H
