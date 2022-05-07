#ifndef REGISTRATEACCOUNT_H
#define REGISTRATEACCOUNT_H

#include <QDialog>
#include <QMessageBox>

#include "database.h"
#include "user.h"

namespace Ui {
class RegistrateAccount;
}
/*!
* \brief Класс для отображения меню регистрации нового аккаунта
*
* С помощью данного класса происходит отображение меню регистрации нового аккаунта, в котором можно
* создать новый пользовательский аккаунт, которому будет присвоена роль "Клиент"
*/
class RegistrateAccount : public QDialog
{
    Q_OBJECT

public:
    explicit RegistrateAccount(QWidget *parent = nullptr);
    ~RegistrateAccount();
    /*!
     * \brief Метод, проверяющий правильность заполнения всех полей
     */
    bool check_required_fields();
    void fill_user();

signals:
    void entryWindow();

private slots:
    void on_end_reg_clicked();

    void on_back_clicked();

private:
    Ui::RegistrateAccount *ui;
    DataBase db;
    QList<QString> qs;

    void fill_questions();
    void close_window();
    void clear_ui();
};

#endif // REGISTRATEACCOUNT_H
