#ifndef ENTRYMANAGEDIALOG_H
#define ENTRYMANAGEDIALOG_H

#include <QDialog>
#include <QShowEvent>

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

private:
    Ui::EntryManageDialog *ui;
};

#endif // ENTRYMANAGEDIALOG_H
