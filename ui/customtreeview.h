#ifndef CUSTOMTREEVIEW_H
#define CUSTOMTREEVIEW_H

#include <QWidget>
#include <QTreeView>
#include <QLabel>
#include <QFileSystemModel>

class CustomTreeView : public QWidget
{
    Q_OBJECT
public:
    explicit CustomTreeView(QWidget *parent = nullptr);

    void hideColumn(int column);

signals:

public slots:
    void setCountTotal(int count);
    void setCountMarked(int count);
    void setModel(QFileSystemModel *model);

private:
    QTreeView *mTreeView;
    QLabel *mCaptionTotal;
    QLabel *mCaptionMarked;
    QLabel *mCountTotal;
    QLabel *mCountMarked;
};

#endif // CUSTOMTREEVIEW_H
