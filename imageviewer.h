#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <string>
#include <vector>

using namespace std;

class ImageViewer
{
public:
    ImageViewer();

    string next();
    string prev();
    string current();

private:
    vector<string> stub_images {
        "images/Copy_24x24.png",
        "images/59Xt_3MUvkk.jpg",
        "images/2016-07-18-17-19-47-393.jpg",
        "images/Next_24x24.png",
        "images/Picture-Viewer-icon.ico",
        "images/Open_24x24.png",
        "images/Previous_24x24.png",
        "images/Remove_24x24.png",
        "images/Zoom In_24x24.png",
    };

    size_t i = 0;
};

#endif // IMAGEVIEWER_H
