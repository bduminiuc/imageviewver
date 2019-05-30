#include "customtreeview.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QDebug>

CustomTreeView::CustomTreeView(QWidget *parent) :
    QWidget(parent),
    mTreeView(new QTreeView(this)),
    mCaptionTotal(new QLabel(this)),
    mCaptionMarked(new QLabel(this)),
    mCountTotal(new QLabel(this)),
    mCountMarked(new QLabel(this))
{
    QHBoxLayout *row1 = new QHBoxLayout;
    row1->addStretch();
    row1->addWidget(mCaptionTotal);
    row1->addWidget(mCountTotal);

    QHBoxLayout *row2 = new QHBoxLayout;
    row2->addStretch();
    row2->addWidget(mCaptionMarked);
    row2->addWidget(mCountMarked);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(row1);
    layout->addLayout(row2);
    layout->addWidget(mTreeView);

    mCaptionTotal->setText("Всего файлов: ");
    mCaptionMarked->setText("Выбрано файлов: ");

    mCountTotal->setText("0");
    mCountMarked->setText("0");

    mTreeView->setHeaderHidden(true);

    this->setLayout(layout);
}

void CustomTreeView::hideColumn(int column)
{
    mTreeView->hideColumn(column);
}

void CustomTreeView::setCountTotal(int count)
{
    mCountTotal->setText(QString::number(count));
}


void CustomTreeView::setCountMarked(int count)
{
    mCountMarked->setText(QString::number(count));
}

void CustomTreeView::setModel(QFileSystemModel *model)
{
    mTreeView->setModel(model);
}
