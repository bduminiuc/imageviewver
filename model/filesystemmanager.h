#ifndef FILESYSTEMMANAGER_H
#define FILESYSTEMMANAGER_H

#include <QObject>

class FileSystemManager : public QObject
{
    Q_OBJECT
public:
    explicit FileSystemManager(QObject *parent = nullptr);

signals:

public slots:
};

#endif // FILESYSTEMMANAGER_H
