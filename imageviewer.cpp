#include <QDirIterator>

#include "imageviewer.h"

ImageViewer::ImageViewer()
{

}

bool ImageViewer::openDirectory(const QString &path)
{
    directory = path;
    //directory = "E:/git-workspace/qt/";

    QDirIterator it(directory, formats, QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext())
        images.push_back(it.next().toUtf8().constData());

    return true;
}

void ImageViewer::closeDirectory()
{
    directory = "";
    images.clear();
    i = 0;
}

bool ImageViewer::isOpened()
{
    return ! directory.isEmpty();
}

QString ImageViewer::next()
{
    if (i == images.size() - 1)
        i = 0;
    else
        i++;

    return images[i];
}

QString ImageViewer::prev()
{
    if (i == 0)
        i = images.size() - 1;
    else
        i--;

    return images[i];
}

QString ImageViewer::current()
{
    return images[i];
}

bool ImageViewer::hasImages()
{
    return ! images.empty();
}

int ImageViewer::count()
{
    return images.size();
}

int ImageViewer::currentIdx()
{
    return i + 1;
}
