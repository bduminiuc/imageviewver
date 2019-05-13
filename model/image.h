#ifndef IMAGE_H
#define IMAGE_H

#include <QString>

class Image
{
public:
    Image();
    Image(const QString &path);

    bool isMarked() const;
    void setMarked(bool marked);

    QString getPath()     const;
    QString getFileName() const;
    qint64  getFileSize() const;

private:
    bool mMarked = false;
    QString mPath;
};

#endif // IMAGE_H
