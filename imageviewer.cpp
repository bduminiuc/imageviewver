#include "imageviewer.h"

ImageViewer::ImageViewer()
{

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
