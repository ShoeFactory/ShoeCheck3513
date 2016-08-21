#include <QMessageBox>

#include "entrytotaladddialog.h"
#include "ui_entrytotaladddialog.h"

#pragma execution_character_set("utf-8")

EntryTotalAddDialog::EntryTotalAddDialog(EntryTotalEditTreeModel *model,  QStringList selectItemChains, QWidget *parent):
    QDialog(parent),
    ui(new Ui::EntryTotalAddDialog)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    treeModel = model;

    ui->comboBox_shoeType->setModel(model->getTableModel()->relationModel(1));
    ui->comboBox_errorType->setModel(model->getTableModel()->relationModel(2));
    ui->comboBox_errorItem->setModel(model->getTableModel()->relationModel(3));

    ui->comboBox_shoeType->setModelColumn(1);
    ui->comboBox_errorType->setModelColumn(1);
    ui->comboBox_errorItem->setModelColumn(1);

    ui->comboBox_shoeType->setCurrentText(selectItemChains.value(0));
    ui->comboBox_errorType->setCurrentText(selectItemChains.value(1));
    ui->comboBox_errorItem->setCurrentText(selectItemChains.value(2));

}

EntryTotalAddDialog::~EntryTotalAddDialog()
{
    delete ui;
}

void EntryTotalAddDialog::on_pushButton_ok_clicked()
{
    if(treeModel->insertRecordToTree(ui->comboBox_shoeType->currentText(),
                                  ui->comboBox_errorType->currentText(),
                                  ui->comboBox_errorItem->currentText()))
    {
        QMessageBox::information(this, "添加成功", "添加新的检测项目成功！");

    }
    else
    {
        QMessageBox::information(this, "添加失败", "项目已存在， 重复添加无效！");
    }
    accept();
}

void EntryTotalAddDialog::on_pushButton_cancel_clicked()
{
    accept();
}
