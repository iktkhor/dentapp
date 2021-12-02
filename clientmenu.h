#ifndef CLIENTMENU_H
#define CLIENTMENU_H

#include <QMainWindow>
#include <QMessageBox>
#include <set>

#include "database.h"
#include "user.h"
#include "session.h"
#include "settings.h"

namespace Ui {
class ClientMenu;
}

class ClientMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClientMenu(QWidget *parent = nullptr);
    ~ClientMenu();

signals:
    void entryWindow();
    void send_data(User* current_user);

public slots:
    void recieve_data(User* user);
    void update_ui();

private slots:
    void on_log_out_clicked();

    void on_change_user_data_clicked();

    void on_change_tables_clicked();

    void on_make_delete_app_clicked();

    void on_my_apps_table_cellClicked(int row, int column);

    void on_free_apps_table_cellClicked(int row, int column);

private:
    Ui::ClientMenu *ui;
    Settings *settings;
    User *current_user;
    DataBase db;

    void update_free_apps();
    void update_my_apps();
    void make_app();
    void delete_app();
};

#endif // CLIENTMENU_H
