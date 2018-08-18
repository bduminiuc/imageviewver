#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <string>
#include <vector>

using namespace std;

class ImageViewer
{
public:
    ImageViewer();
    bool openDirectory(const string & path);
    void closeDirectory();
    bool isOpened();

    string next();
    string prev();
    string current();

private:
    string directory;
    vector<string> stub_images {
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

    size_t i = 0;
};

#endif // IMAGEVIEWER_H
