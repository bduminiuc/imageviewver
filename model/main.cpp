#include <QCoreApplication>

#include "directory.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Directory directory({"*.png", "*.jpg", "*.ico"});

    directory.open("C:/Users/host/Documents/imageviewer/images");

    std::cout << directory.count() << std::endl;

    return a.exec();
}
