#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QFileIconProvider>

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

private:
    void fitImageToScreen();
    void setImage(const QString &path);
    void initializeTreeView();

    Ui::MainWindow *ui;

    QFileSystemModel *model;
    QString mCurrentImage;

    QStringList files;
    QStringList nameFilters = {"*.jpg", "*.png", "*.ico"};
};

#endif // MAINWINDOW_H
