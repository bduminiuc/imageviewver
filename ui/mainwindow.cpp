#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    model(new QFileSystemModel(this))
{
    ui->setupUi(this);

    QStringList nameFilters = {"*.jpg", "*.png", "*.ico"};

    //model->setRootPath("");
    model->setNameFilters(nameFilters);
    model->setNameFilterDisables(false);
    model->iconProvider()->setOptions(QFileIconProvider::DontUseCustomDirectoryIcons);

    addAction(ui->actionOpen);

    //connect(ui->treeView, &QTreeView::doubleClicked, this, &MainWindow::on_treeView_doubleClicked);
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

    model->setRootPath(path);
    ui->labelRootPath->setText(path);

    if (! path.isEmpty()) {
        const QModelIndex rootIndex = model->index(QDir::cleanPath(path));

        if (rootIndex.isValid())
            ui->treeView->setRootIndex(rootIndex);

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
    qDebug() << "Double click";
}
