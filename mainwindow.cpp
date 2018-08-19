#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
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
    imgViewer.openDirectory(directoryPath);

    // TODO: smth like
    // if (imgViewer.hasImages())
    //     setImages();

    setImage(imgViewer.current());
}

void MainWindow::close_all()
{
    if (imgViewer.isOpened()) {
        imgViewer.closeDirectory();

        imageLabel->clear();
        imageLabel->adjustSize();
        imageLabel->setVisible(false);

        currentImagePath.clear();

        QWidget::setWindowTitle("ImageViewer");
    }
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
    setImage(imgViewer.next());
}

void MainWindow::prev()
{
    setImage(imgViewer.prev());
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

void MainWindow::setImage(const QString & path)
{
    QImageReader reader(path);
    reader.setAutoTransform(true);

    QImage currentImage(reader.read());

    if (currentImage.isNull())
        return;

    QPixmap pixmap = QPixmap::fromImage(currentImage).scaled(getCurrentSize(), Qt::KeepAspectRatio);

    imageLabel->setPixmap(pixmap);
    imageLabel->adjustSize();
    imageLabel->setVisible(true);

    currentImagePath = path;

    QWidget::setWindowTitle(path + " - ImageViewer");
}

QSize MainWindow::getCurrentSize()
{
    return QSize(QWidget::width() - 10,
                 QWidget::height() - ui->menu->height() - 2*ui->statusBar->height() - ui->menuBar->height());
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    if (!currentImagePath.isEmpty())
        setImage(currentImagePath);
}
