#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mCurrentImage(nullptr),
    imageLabel(new QLabel),
    scrollArea(new QScrollArea),
    checkBoxChecked(new QCheckBox),
    loadingDialog(new LoadingDialog(this))
{
    ui->setupUi(this);
    initInterface();

    connect(&mImageViewer, &ImageViewer::updated, this, &MainWindow::update);

    QFutureWatcher<void> *watcher = mImageViewer.getWatcher();

    connect(watcher, &QFutureWatcher<void>::finished, loadingDialog, &LoadingDialog::close);
    connect(loadingDialog, &LoadingDialog::rejected, watcher, &QFutureWatcher<void>::cancel);
    connect(watcher,  &QFutureWatcher<void>::progressRangeChanged, loadingDialog, &LoadingDialog::setRange);
    connect(watcher, &QFutureWatcher<void>::progressValueChanged,  loadingDialog, &LoadingDialog::setValue);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::open()
{
    // open directory path
    QString directoryPath = QFileDialog::getExistingDirectory(this, "Directory Dialog", "");

    if (directoryPath.isEmpty())
        // if user press CANCEL in FileDialog
        return;

    close_all();
    mImageViewer.openDirectory(directoryPath);

    /*if (mImageViewer.hasImages()) {
        setImage(mImageViewer.getCurrentImage());
        setViewStatusBarMsg(mImageViewer.getCurrentIndex(), mImageViewer.imagesCount());
    }
    else {
        QMessageBox::critical(this, "Ошибка", "В выбранной папке нет изображений! Откройте папку с изображениями.");
        open();
    }*/
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
    if (mCurrentImage) {
        mCurrentImage->setChecked(ui->action_mark->isChecked());
    }
}

void MainWindow::move()
{
    QString directoryPath = QFileDialog::getExistingDirectory(this, "Directory Dialog", "");

    if (directoryPath.isEmpty())
        // if user press CANCEL in FileDialog
        return;

    loadingDialog->setWindowTitle("Перемещение");
    loadingDialog->setOperationTitle("Перемещение");
    loadingDialog->setCurrentItemText("Перемещение элементов...");

    mImageViewer.moveChecked(directoryPath);
    loadingDialog->show();
}

void MainWindow::copy()
{
    QString directoryPath = QFileDialog::getExistingDirectory(this, "Directory Dialog", "");

    if (directoryPath.isEmpty())
        // if user press CANCEL in FileDialog
        return;

    loadingDialog->setWindowTitle("Копирование");
    loadingDialog->setOperationTitle("Копирование");
    loadingDialog->setCurrentItemText("Копирование элементов...");

    mImageViewer.copyChecked(directoryPath);
    loadingDialog->show();
}

void MainWindow::remove()
{
    loadingDialog->setWindowTitle("Удаление");
    loadingDialog->setOperationTitle("Удаление");
    loadingDialog->setCurrentItemText("Удаление элементов...");

    mImageViewer.removeChecked();
    loadingDialog->show();
}

void MainWindow::about()
{
    ui->statusBar->showMessage("About action");
}

void MainWindow::next()
{
    switchImage(SWITCH_RIGHT);
}

void MainWindow::prev()
{
    switchImage(SWITCH_LEFT);
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
    connect(ui->action_next, &QAction::triggered, this, &MainWindow::next);
    connect(ui->action_prev, &QAction::triggered, this, &MainWindow::prev);
}

void MainWindow::setImage(Image *image)
{
    if (!image) {
        return;
    }

    // reading of current image
    QImageReader reader(image->getPath());
    reader.setAutoTransform(true);

    QImage currentImage(reader.read());

    if (currentImage.isNull()) {
        return;
    }

    imageLabel->setPixmap(QPixmap::fromImage(currentImage));
    on_action_fit_to_screen_triggered();

    imageLabel->adjustSize();
    imageLabel->setVisible(true);

    ui->action_mark->setChecked(image->isChecked());

    mCurrentImage = image;

    setWindowTitle(image->getPath() + " - ImageViewer");
}

void MainWindow::switchImage(SwitchDirection direction)
{
    if (!mImageViewer.hasImages()){
        return;
    }

    switch(direction)
    {
        case SWITCH_LEFT:
            mImageViewer.prev();
            break;

        case SWITCH_RIGHT:
            mImageViewer.next();
            break;
    }

    setImage(mImageViewer.getCurrentImage());
    setViewStatusBarMsg(mImageViewer.getCurrentIndex(), mImageViewer.imagesCount());
}

void MainWindow::setViewStatusBarMsg(int current, int total)
{
    QString message = QString::number(current) + " из " + QString::number(total);
    ui->statusBar->showMessage(message);
}

void MainWindow::resizeEvent(QResizeEvent*)
{
    if (mCurrentImage) {
        setImage(mCurrentImage);
    }
}

void MainWindow::update()
{
    if (mImageViewer.hasImages()) {
        setImage(mImageViewer.getCurrentImage());
        setViewStatusBarMsg(mImageViewer.getCurrentIndex(), mImageViewer.imagesCount());
    }
    else {
        QMessageBox::critical(this, "Ошибка",
                              "В выбранной папке нет изображений! Откройте папку с изображениями.");
        open();
    }
}

void MainWindow::on_action_fit_to_screen_triggered()
{
    QSize currentSize(scrollArea->width() - 10, scrollArea->height() - 10);
    const QPixmap *currentPixmap = imageLabel->pixmap();

    bool needScaleWidth  = currentPixmap->width()  > currentSize.width();
    bool needScaleHeight = currentPixmap->height() > currentSize.height();

    if (needScaleWidth || needScaleHeight) {
        imageLabel->setPixmap(currentPixmap->scaled(currentSize, Qt::KeepAspectRatio));
        imageLabel->adjustSize();
    }
}
