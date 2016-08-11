#include <QDesktopWidget>
#include <QtSql>
#include <QtWidgets>

#include "usermanagedialog.h"
#include "ui_usermanagedialog.h"
#include "dbhelper.h"
#include "changepasswddialog.h"

#pragma execution_character_set("utf-8")


UserManageDialog::UserManageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserManageDialog)
{
    ui->setupUi(this);

    button_addUser = new QPushButton("新建",this);
    button_removeUser = new QPushButton("删除", this);
    button_changePasswd = new QPushButton("改密", this);
    changePasswdDialog = new ChangePasswdDialog(this);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(button_addUser);
    vbox->addWidget(button_removeUser);
    vbox->addWidget(button_changePasswd);
    vbox->addStretch();

    //! [model view]

    userTableModel = new QSqlRelationalTableModel(this);
    userTableModel->setTable("users");
    userTableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

    userTableModel->setRelation(3, QSqlRelation("userroles", "id", "name"));

    userTableModel->setHeaderData(0, Qt::Horizontal, tr("编号"));
    userTableModel->setHeaderData(1, Qt::Horizontal, tr("姓名"));
    userTableModel->setHeaderData(2, Qt::Horizontal, tr("密码"));
    userTableModel->setHeaderData(3, Qt::Horizontal, tr("角色"));
    userTableModel->setHeaderData(4, Qt::Horizontal, tr("电话"));

    userTableModel->select();

    userTableView = new QTableView(this);
    userTableView->setModel(userTableModel);
    userTableView->setItemDelegate(new QSqlRelationalDelegate(userTableView));

    //userTableView->setColumnEditAble(0, false);  //编号不可编辑 可惜没有这个函数 要自己写代理
    //userTablwView->setSelectionModel()           //选中id时     希望能选中整行 （删除和改密码）
    //userTableView->setTextAlignment(Qt::center); //文字居中显示 可惜没有这个函数 要自己写代理

    //userTableView->setColumnHidden(2, true); //密码列不显示
    userTableView->verticalHeader()->setHidden(true);

    //userTableView->setSelectionMode ( QAbstractItemView::SingleSelection); //设置选择模式，选择单行

    userTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    userTableView->horizontalHeader()->setStretchLastSection(true);

    //! [end model view]

    button_ok = new QPushButton("确认", this);
    button_ok->setDefault(true);
    button_cancel = new QPushButton("取消", this);
    button_apply = new QPushButton("应用", this);
    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addStretch();
    hbox->addWidget(button_ok);
    hbox->addWidget(button_cancel);
    hbox->addWidget(button_apply);

    QGridLayout *grid = new QGridLayout(this);
    grid->addWidget(userTableView, 0, 0, 2, 3);
    grid->addLayout(vbox, 0, 3, 2, 1);
    grid->addLayout(hbox, 2, 0, 1, 4);
    setLayout(grid);

    setWindowTitle(tr("用户管理"));


    uniqueUserId = userTableModel->rowCount();

    connect(button_addUser, &QPushButton::clicked, this, &UserManageDialog::on_addUser);
    connect(button_removeUser, &QPushButton::clicked, this, &UserManageDialog::on_removeUser);
    connect(button_changePasswd, &QPushButton::clicked, this, &UserManageDialog::on_changePasswd);


    connect(button_ok, SIGNAL(clicked()), this, SLOT(on_ok()));
    connect(button_cancel, SIGNAL(clicked()), this, SLOT(on_cancel()));
    connect(button_apply, SIGNAL(clicked()), this, SLOT(on_apply()));
}

UserManageDialog::~UserManageDialog()
{
    delete ui;
}

void UserManageDialog::showEvent(QShowEvent *)
{
    move((QApplication::desktop()->width()-width())/2,
         (QApplication::desktop()->height()-height())/2);

    userTableModel->select();
}

int UserManageDialog::generateNewUserId()
{
    return ++uniqueUserId;
}

void UserManageDialog::on_addUser()
{
    int id = generateNewUserId() ;
    QSqlRecord record;

    QSqlField f1("id", QVariant::Int);
    QSqlField f2("name", QVariant::String);
    QSqlField f3("passwd", QVariant::String);
    QSqlField f4("role", QVariant::Int);
    QSqlField f5("telephone", QVariant::String);

    f1.setValue(QVariant(id));
    f2.setValue(QVariant(QString()));

    f3.setValue(QVariant(DB_HELPER->getMD5String("123")));
    f4.setValue(QVariant().fromValue(2));
    f5.setValue(QVariant(QString()));

    record.append(f1);
    record.append(f2);
    record.append(f3);
    record.append(f4);
    record.append(f5);

    bool inserted = userTableModel->insertRecord(-1, record);
    if(!inserted)
    {
        QMessageBox::critical(this, "新添用户失败", "向模型中添加新用户失败");
    }
}

void UserManageDialog::on_removeUser()
{
    QModelIndexList selection = userTableView->selectionModel()->selectedRows(0);

    if (!selection.empty()) {
        QModelIndex idIndex = selection.at(0);
        userTableModel->removeRow(idIndex.row());

    } else {
        QMessageBox::information(this, tr("Delete user"),
                                 tr("Select the user you want to delete."));
    }
}

void UserManageDialog::on_changePasswd()
{
    QModelIndexList selection = userTableView->selectionModel()->selectedRows(0);

    if (!selection.empty()) {
        QModelIndex idIndex = selection.at(0);
        int id = idIndex.data().toInt();

        int rowId = idIndex.row();

        QModelIndex nameIndex =  userTableModel->index(rowId, 1);
        QString name = nameIndex.data().toString();

        QModelIndex passwdIndex = userTableModel->index(rowId, 2);

        QString title = QString("改密 %1号：%2").arg(id).arg(name);
        changePasswdDialog->setTitle(title);

        if(QDialog::Accepted ==  changePasswdDialog->exec())
        {
            QString newPasswdMd5 = DB_HELPER->getMD5String(changePasswdDialog->getNewPasswd());
            userTableModel->setData(passwdIndex, QVariant(newPasswdMd5));
        }

    } else {
        QMessageBox::information(this, tr("Change Password"),
                                 tr("Select the user you want to change password."));
    }
}

void UserManageDialog::on_ok()
{
    on_apply();
    accept();
}

void UserManageDialog::on_cancel()
{
    userTableModel->revertAll();
    hide();
}

void UserManageDialog::on_apply()
{
    userTableModel->database().transaction();
    if (userTableModel->submitAll()) {
        userTableModel->database().commit();
    } else {
        userTableModel->database().rollback();
        QMessageBox::warning(this, tr("Error commit"),
                             tr("The database reported an error: %1")
                             .arg(userTableModel->lastError().text()));
    }
}
