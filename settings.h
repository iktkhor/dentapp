#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

#include "user.h"
#include "database.h"

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

signals:
void client_menu();
void send_data(User* user);

private slots:
    void on_change_data_clicked();

    void on_save_data_clicked();

    void recieve_data(User* current_user);

    void on_back_clicked();

private:
    Ui::Settings *ui;
    DataBase db;
    User *current_user;
    QList<QString> qs;
    bool is_changed = false;

    void set_enabled_data(bool b);
    void update_ui();
};

#endif // SETTINGS_H
