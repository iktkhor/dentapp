#ifndef REMINDPASSWORD_H
#define REMINDPASSWORD_H

#include <QDialog>
#include <QMessageBox>

#include "database.h"
#include "user.h"

namespace Ui {
class RemindPassword;
}
/*!
* \brief Класс для отображения меню напоминания пароля
*
* С помощью данного класса происходит отображение меню напоминания пароля, в котором можно
* пользольватель может восстановить утерянный пароль, с помощью секретного вопроса
*/
class RemindPassword : public QDialog
{
    Q_OBJECT

public:
    explicit RemindPassword(QWidget *parent = nullptr);
    ~RemindPassword();

signals:
    /*!
     * \brief Сигнал используемый для открытия меню входа
     */
    void entryWindow();

private slots:
    void on_show_secret_question_clicked();

    void on_change_pass_clicked();

    void on_back_clicked();

    void on_update_password_clicked();

    void on_back_to_menu_clicked();

private:
    Ui::RemindPassword *ui;
    DataBase db;
    User *user;

    void close_window();
    void change_buttons_enable(bool b);
    void clear_ui();
    bool check_new_password();    
};

#endif // REMINDPASSWORD_H
