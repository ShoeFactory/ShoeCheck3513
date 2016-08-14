#ifndef ENTRYSINGLE_H
#define ENTRYSINGLE_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QTableView;
class QSqlTableModel;
class QPushButton;
QT_END_NAMESPACE

class EntrySingle : public QWidget
{
    Q_OBJECT
public:
    explicit EntrySingle(QWidget *parent = 0);
    void on_cancel();
    void on_apply();

protected:
    void showEvent(QShowEvent *);
private slots:
    void on_add_shoeType();
    void on_add_errorType();
    void on_add_errorItem();

    void on_remove_shoeType();
    void on_remove_errorType();
    void on_remove_errorItem();

private:
    QSqlTableModel *tableModel_shoeTypes;
    QSqlTableModel *tableModel_errorTypes;
    QSqlTableModel *tableModel_errorItems;

    QTableView *tableView_shoeTypes;
    QTableView *tableView_errorTypes;
    QTableView *tableView_errorItems;

    QPushButton * button_shoeType_add;
    QPushButton * button_shoeType_remove;
    QPushButton * button_errorType_add;
    QPushButton * button_errorType_remove;
    QPushButton * button_errorItem_add;
    QPushButton * button_errorItem_remove;

    int  uniqueShoeTypeID;
    int  uniqueErrorTypeID;
    int  uniqueErrorItemID;
    int getUniqueShoeTypeId();
    int getUniqueErrorTypeId();
    int getUniqueErrorItemId();

    QPushButton *button_ok;
    QPushButton *button_cancel;
    QPushButton *button_apply;
};

#endif // ENTRYSINGLE_H
