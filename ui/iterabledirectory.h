#ifndef ITERABLEDIRECTORY_H
#define ITERABLEDIRECTORY_H

#include <QDir>

class IterableDirectory : public QObject
{
    Q_OBJECT
public:
    using iterator       = QStringList::iterator;
    using const_iterator = QStringList::const_iterator;
    using size_type      = QStringList::size_type;

    explicit IterableDirectory(QObject *parent = nullptr);

    void open(const QString &directory);
    void open(const QDir &directory);

    void setNameFilters(const QStringList &nameFilters);

    size_type count() const;

private:
    iterator begin();
    iterator end();

    const_iterator cbegin() const;
    const_iterator cend()   const;

public:
    QString getCurrent() const;
    int getCurrentNumber() const;

signals:
    void itemChanged(const QString &path);

public slots:
    void next();
    void previous();


private:
    void scan();
    QString getAbsoluteFilePath() const;

    QDir mDirectory;
    QStringList mNameFilters;
    QStringList mFiles;

    const_iterator mCurrentIterator;
};

#endif // ITERABLEDIRECTORY_H
