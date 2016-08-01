#include "usermanagedialog.h"
#include "ui_usermanagedialog.h"
#include <QDesktopWidget>

UserManageDialog::UserManageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserManageDialog)
{
    ui->setupUi(this);
}

UserManageDialog::~UserManageDialog()
{
    delete ui;
}

void UserManageDialog::showEvent(QShowEvent *)
{
    move((QApplication::desktop()->width()-width())/2,
         (QApplication::desktop()->height()-height())/2);
}
