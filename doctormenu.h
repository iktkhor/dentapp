#ifndef DOCTORMENU_H
#define DOCTORMENU_H

#include <QMainWindow>

#include "database.h"

namespace Ui {
class DoctorMenu;
}

class DoctorMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit DoctorMenu(QWidget *parent = nullptr);
    ~DoctorMenu();

signals:
    void entryWindow();

private slots:
    void on_exit_clicked();

public slots:
    void recieve_data(User* user);

private:
    Ui::DoctorMenu *ui;
    DataBase db;
    User *current_user;

    void update_sessions();
};

#endif // DOCTORMENU_H
