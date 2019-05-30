#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QImageReader>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    model(new QFileSystemModel(this))
{
    ui->setupUi(this);

    QStringList nameFilters = {"*.jpg", "*.png", "*.ico"};

    mDirectory.setNameFilters(nameFilters);

    model->setNameFilters(nameFilters);
    model->setNameFilterDisables(false);
    model->iconProvider()->setOptions(QFileIconProvider::DontUseCustomDirectoryIcons);

    addAction(ui->actionOpen);
    addAction(ui->actionNext);

    connect(&mDirectory, &IterableDirectory::itemChanged, this, &MainWindow::changeImage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString path = QFileDialog::getExistingDirectory(this, "Выберите папку");

    if (path == "") {
        return;
    }

    if (! ui->treeView->model()) {
        ui->treeView->setModel(model);

        ui->treeView->hideColumn(1);
        ui->treeView->hideColumn(2);
        ui->treeView->hideColumn(3);
    }

    model->setRootPath(path);
    ui->labelRootPath->setText(path);

    if (! path.isEmpty()) {

        const QModelIndex rootIndex = model->index(QDir::cleanPath(path));

        if (rootIndex.isValid()) {
            ui->treeView->setRootIndex(rootIndex);

            mDirectory.open(path);
        }

        ui->treeView->expandAll();
    }
}

void MainWindow::on_treeView_doubleClicked(const QModelIndex &index)
{
    /*QFileInfo fileInfo = model->fileInfo(index);

    if (fileInfo.isFile()) {
        QString absPath = fileInfo.absoluteFilePath();
        setImage(absPath);
        ui->treeView->setCurrentIndex(index);
    }*/
}

void MainWindow::changeImage(const QString &path)
{
    // reading of current image
    QImageReader reader(path);
    reader.setAutoTransform(true);

    QImage currentImage(reader.read());

    if (currentImage.isNull()) {
        return;
    }

    ui->labelImage->setPixmap(QPixmap::fromImage(currentImage));
    fitImageToScreen();

    ui->labelImage->adjustSize();

    // switch treeView current index
    QModelIndex index = model->index(path);
    if (index.isValid()) {
        ui->treeView->setCurrentIndex(index);
    }

    // update current status label
    ui->labelStatusCount->setText(QString::number(mDirectory.getCurrentNumber())
                                  + " из "
                                  + QString::number(mDirectory.count()));
}

void MainWindow::fitImageToScreen()
{
    QSize currentSize(ui->scrollArea->width() - 25, ui->scrollArea->height() - 25);
    const QPixmap *currentPixmap = ui->labelImage->pixmap();

    bool needScaleWidth  = currentPixmap->width()  > currentSize.width();
    bool needScaleHeight = currentPixmap->height() > currentSize.height();

    if (needScaleWidth || needScaleHeight) {
        ui->labelImage->setPixmap(currentPixmap->scaled(currentSize, Qt::KeepAspectRatio));
        ui->labelImage->adjustSize();
    }
}

void MainWindow::on_actionNext_triggered()
{
    mDirectory.next();
}

void MainWindow::on_actionPrev_triggered()
{
    mDirectory.previous();
}
