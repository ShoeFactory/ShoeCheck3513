#ifndef ENTRYTOTALADDDIALOG_H
#define ENTRYTOTALADDDIALOG_H

#include <QDialog>
#include "entrytotaledittreemodel.h"
#include "entrytotaledittreeview.h"
namespace Ui {
class EntryTotalAddDialog;
}

class EntryTotalAddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EntryTotalAddDialog(EntryTotalEditTreeModel *model, QStringList selectItemChains, QWidget *parent = 0);
    ~EntryTotalAddDialog();


private slots:
    void on_pushButton_ok_clicked();
    void on_pushButton_cancel_clicked();

private:
    Ui::EntryTotalAddDialog *ui;
    EntryTotalEditTreeModel *treeModel;
};

#endif // ENTRYTOTALADDDIALOG_H
