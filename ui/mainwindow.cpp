#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QBitmap>
#include <QDebug>


void changePixmapColor(QPixmap &pixmap, const QColor &color)
{
    QBitmap mask = pixmap.createMaskFromColor(QColor("transparent"));
    pixmap.fill(color);
    pixmap.setMask(mask);
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    model(new QFileSystemModel(this))
{
    ui->setupUi(this);
    //treeView = new CustomTreeView(ui->centralWidget);

    QStringList nameFilters = {"*.jpg", "*.png", "*.ico"};

    model->setRootPath("");
    //model->setFilter(QDir::Dirs | QDir::Files);
    model->setNameFilters(nameFilters);
    model->setNameFilterDisables(false);
    model->iconProvider()->setOptions(QFileIconProvider::DontUseCustomDirectoryIcons);

    ui->treeView->setModel(model);

    ui->treeView->move(400, 50);
    //ui->treeView->setCountTotal(50);
    //ui->treeView->setCountMarked(20);
    ui->treeView->setModel(model);

    ui->treeView->hideColumn(1);
    ui->treeView->hideColumn(2);
    ui->treeView->hideColumn(3);

    addAction(ui->actionOpen);
/*
    QPixmap buttonIcon(":/icons/images/baseline-check-24px.svg");
    changePixmapColor(buttonIcon, QColor("blue"));

    //buttonIcon.fill(QColor("red"));
    QIcon icon(buttonIcon);

    ui->pushButton->setIcon(icon);
    ui->pushButton->setIconSize(buttonIcon.rect().size());*/
}

MainWindow::~MainWindow()
{
    delete ui;
}
/*
void MainWindow::on_pushButton_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this, "Caption");

    model->setRootPath(path);

    if (! path.isEmpty()) {
        const QModelIndex rootIndex = model->index(QDir::cleanPath(path));

        if (rootIndex.isValid())
            ui->treeView->setRootIndex(rootIndex);
    }

    ui->treeView->expandAll();
}
*/

void MainWindow::on_actionOpen_triggered()
{
    qDebug() << "action open";
}
