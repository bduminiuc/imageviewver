#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QFileIconProvider>

#include "iterabledirectory.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_treeView_doubleClicked(const QModelIndex &index);

    void on_actionNext_triggered();

    void on_actionPrev_triggered();

    void changeImage(const QString &path);

private:
    void fitImageToScreen();

    Ui::MainWindow *ui;

    QFileSystemModel *model;

    IterableDirectory mDirectory;
};

#endif // MAINWINDOW_H
