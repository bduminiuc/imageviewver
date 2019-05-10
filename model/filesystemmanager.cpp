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

void FileSystemManager::copy(const QString &srcFile, const QString &dstDir)
{
    QString newPath = getNewFilePath(srcFile, dstDir);
    QFile::copy(srcFile, newPath);
}

void FileSystemManager::move(const QString &srcFile, const QString &dstDir)
{
    QString newPath = getNewFilePath(srcFile, dstDir);
    QFile::rename(srcFile, newPath);
}

void FileSystemManager::remove(const QString &file)
{
    QFile::remove(file);
}

void FileSystemManager::copyFiles(const QStringList &srcFiles, const QString &dstDir)
{
    for(auto oldPath: srcFiles) {
        copy(oldPath, dstDir);
    }
}

void FileSystemManager::moveFiles(const QStringList &srcFiles, const QString &dstDir)
{
    for(auto oldPath: srcFiles) {
        move(oldPath, dstDir);
    }
}

void FileSystemManager::removeFiles(const QStringList &files)
{
    for(auto path: files) {
        remove(path);
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
