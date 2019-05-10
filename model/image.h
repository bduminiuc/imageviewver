#ifndef IMAGE_H
#define IMAGE_H

#include <QString>

class Image
{
public:
    Image(const QString &path);

    const QString& getPath() const;

    bool isChecked() const;

    void setChecked(bool checked);

private:
    QString mPath;
    bool mChecked;
};

#endif // IMAGE_H
