#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDebug>

#include "directory.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    Directory dir({"*.jpg", "*.png", "*.ico"});

    QString path = QFileDialog::getExistingDirectory(this, "Caption");

    dir.open(path);

    qDebug() << dir.count();
}
