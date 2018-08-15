#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>

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
    void open();
    void close_all();

    void zoomIn();
    void zoomOut();

    void check();
    void move();
    void copy();
    void remove();

    void about();
    void clearRecentList();

    void next();
    void prev();

private:
    Ui::MainWindow *ui;
    void initInterface();
};

#endif // MAINWINDOW_H
