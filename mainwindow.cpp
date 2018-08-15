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
    // open directory path
    QString directoryPath = QFileDialog::getExistingDirectory(nullptr, "Directory Dialog", "");

    if (directoryPath.isEmpty())
        return;

    close_all();

    ui->statusBar->showMessage("Directory " + directoryPath + " is opened, current file is: " + imgViewer.current().c_str());
}

void MainWindow::close_all()
{
    ui->statusBar->showMessage("Close action");
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
    string next = "Next action. Next pic is: " + imgViewer.next();
    ui->statusBar->showMessage(next.c_str());
}

void MainWindow::prev()
{
    string prev = "Prev action. Prev pic is: " + imgViewer.prev();
    ui->statusBar->showMessage(prev.c_str());
}

void MainWindow::initInterface()
{
    this->showMaximized();

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
