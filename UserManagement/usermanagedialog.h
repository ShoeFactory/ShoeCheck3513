#ifndef USERMANAGEDIALOG_H
#define USERMANAGEDIALOG_H

#include <QDialog>
#include <QShowEvent>

namespace Ui {
class UserManageDialog;
}

class UserManageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UserManageDialog(QWidget *parent = 0);
    ~UserManageDialog();

protected:
    void showEvent(QShowEvent*);

private:
    Ui::UserManageDialog *ui;
};

#endif // USERMANAGEDIALOG_H
