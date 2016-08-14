#ifndef ENTRYMANAGEDIALOG_H
#define ENTRYMANAGEDIALOG_H

#include <QDialog>
#include <QShowEvent>

class QPushButton;

#include "entrysingle.h"
#include "entrytotal.h"

namespace Ui {
class EntryManageDialog;
}

class EntryManageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EntryManageDialog(QWidget *parent = 0);
    ~EntryManageDialog();

protected:
    void showEvent(QShowEvent *);

private slots:
    void on_ok();
    void on_cancel();
    void on_apply();

private:
    Ui::EntryManageDialog *ui;
    EntrySingle *entrySingle;
    EntryTotal *entryTotal;

    QPushButton *button_ok;
    QPushButton *button_cancel;
    QPushButton *button_apply;
};

#endif // ENTRYMANAGEDIALOG_H
