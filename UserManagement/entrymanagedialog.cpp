#include "entrymanagedialog.h"
#include "ui_entrymanagedialog.h"
#include <QDesktopWidget>

EntryManageDialog::EntryManageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EntryManageDialog)
{
    ui->setupUi(this);
}

EntryManageDialog::~EntryManageDialog()
{
    delete ui;
}

void EntryManageDialog::showEvent(QShowEvent *)
{
    move((QApplication::desktop()->width()-width())/2,
         (QApplication::desktop()->height()-height())/2);
}
