#include "filesystemmanager.h"

#include <QDirIterator>
#include <QFileInfo>


FileSystemManager::FileSystemManager(QObject *parent) :
    QObject(parent),
    mFormats({"*.jpg", "*.png", "*.bmp", "*.ico"})
{
    connect(this, &FileSystemManager::rescan, this, &FileSystemManager::scanDirectory);
}

void FileSystemManager::setScanFormats(const QStringList &formats)
{
    mFormats = formats;
}

void FileSystemManager::copyFiles(const QStringList &srcFiles, const QString &dstDir)
{
    for(auto oldPath: srcFiles) {
        QString newPath = getNewFilePath(oldPath, dstDir);
        QFile::copy(oldPath, newPath);
    }
}

void FileSystemManager::moveFiles(const QStringList &srcFiles, const QString &dstDir)
{
    for(auto oldPath: srcFiles) {
        QString newPath = getNewFilePath(oldPath, dstDir);
        QFile::rename(oldPath, newPath);
    }
}

void FileSystemManager::removeFiles(const QStringList &files)
{
    for(auto path: files) {
        QFile::remove(path);
    }
}

void FileSystemManager::scanDirectory(const QString &dir)
{
    QDirIterator it(dir, mFormats, QDir::Files, QDirIterator::Subdirectories);
    ImageList files;

    if (it.hasNext()) {
        mScannedDir = dir;
    }

    while(it.hasNext()) {
        files.append(it.next());
    }

    emit scanFinished(files);
}

QString FileSystemManager::getNewFilePath(const QString &oldPath, const QString &newDir)
{
    QFileInfo fileinfo(oldPath);
    return newDir + QDir::separator() + fileinfo.fileName();
}
