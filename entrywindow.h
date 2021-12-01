#ifndef ENTRYWINDOW_H
#define ENTRYWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QDebug>
#include <QMessageBox>

#include "registrateaccount.h"
#include "remindpassword.h"
#include "clickablelabel.h"
#include "clientmenu.h"
#include "database.h"
#include "adminmenu.h"
#include "doctormenu.h"

QT_BEGIN_NAMESPACE
namespace Ui { class EntryWindow; }
QT_END_NAMESPACE

class EntryWindow : public QMainWindow
{
    Q_OBJECT

public:
    EntryWindow(QWidget *parent = nullptr);
    ~EntryWindow();

signals:
    void send_data(User* user);
    void update_table();

private slots:
    void on_entry_clicked();

    void on_remind_pass_clicked();

    void on_reg_acc_clicked();

    void on_checkBox_show_pass_stateChanged(int arg1);

private:
    Ui::EntryWindow *ui;
    RegistrateAccount *reg_acc_window;
    RemindPassword *rem_pass_window;
    ClientMenu *client_menu_window;
    AdminMenu *admin_menu_window;
    DoctorMenu *doctor_menu_window;
    DataBase db;
    bool is_pass_vis;
};
#endif // ENTRYWINDOW_H
