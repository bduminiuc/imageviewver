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

    model->setNameFilters(nameFilters);
    model->setNameFilterDisables(false);
    model->iconProvider()->setOptions(QFileIconProvider::DontUseCustomDirectoryIcons);

    addAction(ui->actionOpen);
    addAction(ui->actionNext);
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
        initializeTreeView();
    }

    QDir currentDirectory(path);

    model->setRootPath(currentDirectory.path());
    ui->labelRootPath->setText(currentDirectory.path());

    if (! path.isEmpty()) {

        const QModelIndex rootIndex = model->index(QDir::cleanPath(path));

        if (rootIndex.isValid()) {
            ui->treeView->setRootIndex(rootIndex);

            files = currentDirectory.entryList(nameFilters, QDir::Files);
            QStringList::iterator begin = files.begin();

            QString imagePath =currentDirectory.path() + QDir::separator() + *begin;

            QModelIndex index = model->index(imagePath);

            if (index.isValid()) {
                setImage(imagePath);
                ui->treeView->setCurrentIndex(index);
            }
        }

        ui->treeView->expandAll();
    }
}

void MainWindow::initializeTreeView()
{
    ui->treeView->setModel(model);

    ui->treeView->hideColumn(1);
    ui->treeView->hideColumn(2);
    ui->treeView->hideColumn(3);
}

void MainWindow::on_treeView_doubleClicked(const QModelIndex &index)
{
    QFileInfo fileInfo = model->fileInfo(index);

    if (fileInfo.isFile()) {
        QString absPath = fileInfo.absoluteFilePath();
        setImage(absPath);
        ui->treeView->setCurrentIndex(index);
    }
}

void MainWindow::setImage(const QString &path)
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
    mCurrentImage = path;
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
    QModelIndex index = ui->treeView->currentIndex();
    QModelIndex next = index.sibling(index.row() + 1, index.column());

    qDebug() << model->fileInfo(next).isFile();
    qDebug() << model->rowCount();

    ui->treeView->setCurrentIndex(next);

    /*int indexIncrement = 0;

    do {
        indexIncrement += 1;
        next = index.sibling(index.row() + indexIncrement, index.column());
    }
    while (! model->fileInfo(next).isFile());
    */

}

void MainWindow::on_actionPrev_triggered()
{

}
