#ifndef IMAGELIST_H
#define IMAGELIST_H

#include <QList>

#include "image.h"

class ImageList
{
public:
    typedef QList<Image*>::size_type size_type;
    typedef QList<Image*>::iterator iterator;


    ImageList();
    ~ImageList();

    void append(const QString &imagePath);
    iterator erase(iterator iter);

    void clear();

    bool isEmpty() const;

    size_type size() const;

    iterator begin();
    iterator end();

private:
    QList<Image*> mImages;
};

#endif // IMAGELIST_H
