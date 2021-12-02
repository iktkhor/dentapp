#ifndef ADMINMENU_H
#define ADMINMENU_H

#include <QMainWindow>
#include <QWidget>
//#include <QHeaderView>
#include <iostream>
#include <vector>
#include <set>

#include "database.h"
#include "adddoctor.h"
#include "addsession.h"

namespace Ui {
class AdminMenu;
}

class AdminMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminMenu(QWidget *parent = nullptr);
    ~AdminMenu();

signals:
    void entryWindow();
    void update();

public slots:
    void update_sessions();

private slots:
    void on_log_out_clicked();

    void on_add_session_clicked();

    void on_change_tables_clicked();

    void on_delete_acc_clicked();

    void on_add_doctor_clicked();

    void on_delete_session_clicked();

    void on_cancel_app_clicked();

    void on_sessions_table_cellClicked(int row, int column);

    void on_users_table_cellClicked(int row, int column);

private:
    Ui::AdminMenu *ui;
    DataBase db;
    AddDoctor *add_doctor;
    AddSession *add_session;

    void update_users();
    void fill_table_sessions(std::vector<Session> sessions);
    void fill_table_users(std::vector<User> users);   
    void set_enabled_buttons(bool b);
};

#endif // ADMINMENU_H
