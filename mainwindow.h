#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QLabel>
#include <QScrollArea>
#include <QImageReader>

#include "imageviewer.h"

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
    void initInterface();
    void setImage(const QString &);

    Ui::MainWindow *ui;
    ImageViewer imgViewer;
    QLabel *imageLabel;
    QScrollArea *scrollArea;
};

#endif // MAINWINDOW_H
