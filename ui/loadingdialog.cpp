#include "loadingdialog.h"
#include "ui_loadingdialog.h"

LoadingDialog::LoadingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoadingDialog)
{
    ui->setupUi(this);

    connect(ui->pushButtonCancel, &QPushButton::clicked, this, &LoadingDialog::reject);
}

LoadingDialog::~LoadingDialog()
{
    delete ui;
}

void LoadingDialog::setCurrentItemText(const QString &text)
{
    ui->labelCurrentItem->setText(text);
}

void LoadingDialog::setOperationTitle(const QString &title)
{
    ui->labelOperationName->setText(title);
}

void LoadingDialog::setRange(int minimum, int maximum)
{
    ui->progressBar->setRange(minimum, maximum);
}

void LoadingDialog::setValue(int progressValue)
{
    ui->progressBar->setValue(progressValue);
}
