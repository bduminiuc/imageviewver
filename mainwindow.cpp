#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mCurrentImage(nullptr),
    imageLabel(new QLabel),
    scrollArea(new QScrollArea)
{
    ui->setupUi(this);
    initInterface();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::open()
{
    // open directory path
    QString directoryPath = QFileDialog::getExistingDirectory(nullptr, "Directory Dialog", "");

    if (directoryPath.isEmpty())
        // if user press CANCEL in FileDialog
        return;

    close_all();
    mImageViewer.openDirectory(directoryPath);

    if (mImageViewer.hasImages()) {
        setImage(mImageViewer.getCurrentImage());
        setViewStatusBarMsg(mImageViewer.getCurrentIndex(), mImageViewer.imagesCount());
    }
    else {
        QMessageBox::critical(this, "Ошибка", "В выбранной папке нет изображений! Откройте папку с изображениями.");
        open();
    }
}

void MainWindow::close_all()
{
    mImageViewer.closeDirectory();

    imageLabel->clear();
    imageLabel->adjustSize();
    imageLabel->setVisible(false);

    mCurrentImage = nullptr;

    setWindowTitle("ImageViewer");
}

void MainWindow::zoomIn()
{
    ui->statusBar->showMessage("Zoom in action");
}

void MainWindow::zoomOut()
{
    ui->statusBar->showMessage("Zoom out action");
}

void MainWindow::check()
{
    ui->statusBar->showMessage("Check action");
}

void MainWindow::move()
{
    ui->statusBar->showMessage("Move action");
}

void MainWindow::copy()
{
    ui->statusBar->showMessage("Copy action");
}

void MainWindow::remove()
{
    ui->statusBar->showMessage("Remove action");
}

void MainWindow::about()
{
    ui->statusBar->showMessage("About action");
}

void MainWindow::clearRecentList()
{
    ui->statusBar->showMessage("Clear recent list action");
}

void MainWindow::next()
{
    switchImage(true);
}

void MainWindow::prev()
{
    switchImage(false);
}

void MainWindow::initInterface()
{
    this->showMaximized();

    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    scrollArea->setAlignment(Qt::AlignCenter);
    setCentralWidget(scrollArea);

    imageLabel->setVisible(false);
    imageLabel->setBackgroundRole(QPalette::Light);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    // create connections between actions and slots
    connect(ui->action_open, &QAction::triggered, this, &MainWindow::open);
    connect(ui->action_close, &QAction::triggered, this, &MainWindow::close_all);
    connect(ui->action_zoom_in, &QAction::triggered, this, &MainWindow::zoomIn);
    connect(ui->action_zoom_out, &QAction::triggered, this, &MainWindow::zoomOut);
    connect(ui->action_mark, &QAction::triggered, this, &MainWindow::check);
    connect(ui->action_move, &QAction::triggered, this, &MainWindow::move);
    connect(ui->action_copy, &QAction::triggered, this, &MainWindow::copy);
    connect(ui->action_remove, &QAction::triggered, this, &MainWindow::remove);
    connect(ui->action_about, &QAction::triggered, this, &MainWindow::about);
    connect(ui->action_clear_recent_list, &QAction::triggered, this, &MainWindow::clearRecentList);
    connect(ui->action_next, &QAction::triggered, this, &MainWindow::next);
    connect(ui->action_prev, &QAction::triggered, this, &MainWindow::prev);
}

void MainWindow::setImage(Image *image)
{
    // reading of current image
    QImageReader reader(image->getPath());
    reader.setAutoTransform(true);

    QImage currentImage(reader.read());

    if (currentImage.isNull())
        return;

    // init pixmap to add in label
    QSize currentSize = getCurrentSize(); //ui->centralWidget->size();
    QPixmap pixmap = QPixmap::fromImage(currentImage);

    // scale pixmap if image is wider or higher than the window
    if (currentImage.width() > currentSize.width() || currentImage.height() > currentSize.height())
        imageLabel->setPixmap(pixmap.scaled(currentSize, Qt::KeepAspectRatio));
    else
        imageLabel->setPixmap(pixmap);


    imageLabel->adjustSize();
    imageLabel->setVisible(true);

    mCurrentImage = image;

    setWindowTitle(image->getPath() + " - ImageViewer");
}

// direction means next action or prev
void MainWindow::switchImage(bool direction)
{
    if (mImageViewer.hasImages()){
        setImage(direction ? mImageViewer.next() : mImageViewer.prev());
        setViewStatusBarMsg(mImageViewer.getCurrentIndex(), mImageViewer.imagesCount());
    }
}

QSize MainWindow::getCurrentSize()
{
    return QSize(scrollArea->width() - 10, scrollArea->height() - 10);
}

void MainWindow::setViewStatusBarMsg(int current, int total)
{
    ui->statusBar->showMessage(QString::number(current) +
                               " из " +
                               QString::number(total));
}

void MainWindow::resizeEvent(QResizeEvent*)
{
    if (mCurrentImage) {
        setImage(mCurrentImage);
    }
}
