#ifndef CLIENTMENU_H
#define CLIENTMENU_H

#include <QMainWindow>

#include "database.h"
#include "user.h"
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

private slots:
    void on_log_out_clicked();

    void on_change_user_data_clicked();

private:
    Ui::ClientMenu *ui;
    Settings *settings;
    User *current_user;
    DataBase db;
};

#endif // CLIENTMENU_H
