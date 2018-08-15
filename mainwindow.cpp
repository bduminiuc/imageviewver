#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
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
    close();

    // open directory path
    QString directoryPath = QFileDialog::getExistingDirectory(nullptr, "Directory Dialog", "");

    ui->statusBar->showMessage("Directory " + directoryPath + " is opened");
}

void MainWindow::close()
{
    ui->statusBar->showMessage("Closed!");
}

void MainWindow::initInterface()
{
    this->showMaximized();

    // create connections between actions and slots
    connect(ui->action_open, &QAction::triggered, this, &MainWindow::open);
    connect(ui->action_close, &QAction::triggered, this, &MainWindow::close);
}
