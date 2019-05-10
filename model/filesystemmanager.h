#ifndef FILESYSTEMMANAGER_H
#define FILESYSTEMMANAGER_H

#include <QObject>

#include "imagelist.h"

class FileSystemManager : public QObject
{
    Q_OBJECT
public:
    explicit FileSystemManager(QObject *parent = nullptr);

    void setScanFormats(const QStringList &formats);

    void copy(const QString &srcFile, const QString &dstDir);

    void copyFiles(const QStringList &srcFiles, const QString &dstDir);
    void moveFiles(const QStringList &srcFiles, const QString &dstDir);
    void removeFiles(const QStringList &files);

signals:
    void rescan(const QString &dir);
    void scanFinished(const ImageList &files);

public slots:
    void scanDirectory(const QString &dir);

private:
    QString getNewFilePath(const QString &oldPath, const QString &newDir);

    QString mScannedDir;
    QStringList mFormats;
};

#endif // FILESYSTEMMANAGER_H
