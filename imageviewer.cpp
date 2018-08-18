#include "imageviewer.h"

ImageViewer::ImageViewer()
{

}

bool ImageViewer::openDirectory(const string &path)
{
    directory = path;
    return true;
}

void ImageViewer::closeDirectory()
{
    directory = "";
    i = 0;
}

bool ImageViewer::isOpened()
{
    return ! directory.empty();
}

string ImageViewer::next()
{
    if (i == stub_images.size() - 1)
        i = 0;
    else
        i++;

    return stub_images[i];
}

string ImageViewer::prev()
{
    if (i == 0)
        i = stub_images.size() - 1;
    else
        i--;

    return stub_images[i];
}

string ImageViewer::current()
{
    return stub_images[i];
}
