#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QLabel>
#include <QScrollArea>
#include <QImageReader>
#include <QMessageBox>
#include <QCheckBox>

#include "imageviewer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    enum SwitchDirection {SWITCH_LEFT, SWITCH_RIGHT};

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

    void resizeEvent (QResizeEvent * event);

private:
    void initInterface();
    void setImage(Image*);
    void switchImage(SwitchDirection direction);
    QSize getCurrentSize();
    void setViewStatusBarMsg(int current, int total);

    Ui::MainWindow *ui;

    ImageViewer mImageViewer;
    Image* mCurrentImage;

    QLabel *imageLabel;
    QScrollArea *scrollArea;
    QCheckBox *checkBoxChecked;

};

#endif // MAINWINDOW_H
