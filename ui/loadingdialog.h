#ifndef LOADINGDIALOG_H
#define LOADINGDIALOG_H

#include <QDialog>

namespace Ui {
class LoadingDialog;
}

class LoadingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoadingDialog(QWidget *parent = nullptr);
    ~LoadingDialog();

    void setCurrentItemText(const QString &text);
    void setOperationTitle(const QString &title);

public slots:
    void setRange(int minimum, int maximum);
    void setValue(int progressValue);

private:
    Ui::LoadingDialog *ui;
};

#endif // LOADINGDIALOG_H
