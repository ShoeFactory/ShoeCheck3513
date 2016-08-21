#include "entrymanagedialog.h"
#include "ui_entrymanagedialog.h"
#include <QDesktopWidget>
#include <QPushButton>

#pragma execution_character_set("utf-8")

EntryManageDialog::EntryManageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EntryManageDialog)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setWindowTitle("检测项管理");

    entrySingle = new EntrySingle(this);
    entryTotal  = new EntryTotal(this);

    ui->tabWidget_erroritem->addTab(entryTotal,  "统一整理");
    ui->tabWidget_erroritem->addTab(entrySingle, "单项整理");

    connect(ui->pushButton_ok, &QPushButton::clicked, this, &EntryManageDialog::on_ok);
    connect(ui->pushButton_cancel, &QPushButton::clicked, this, &EntryManageDialog::on_cancel);
    connect(ui->pushButton_apply, &QPushButton::clicked, this, &EntryManageDialog::on_apply);
}

EntryManageDialog::~EntryManageDialog()
{
    delete ui;
}

void EntryManageDialog::showEvent(QShowEvent *)
{
    move((QApplication::desktop()->width()-width())/2,
         (QApplication::desktop()->height()-height())/3);
}

void EntryManageDialog::on_ok()
{
    on_apply();
    accept();
}

void EntryManageDialog::on_cancel()
{
    entrySingle->on_cancel();
    entryTotal->on_cancel();
    hide();
}

void EntryManageDialog::on_apply()
{
    entrySingle->on_apply();
    entryTotal->on_apply();
}
