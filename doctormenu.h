#ifndef DOCTORMENU_H
#define DOCTORMENU_H

#include <QMainWindow>

#include "database.h"

namespace Ui {
class DoctorMenu;
}
/*!
 * \brief Класс для отображения меню доктора
 *
 * С помощью данного класса происходит отображение меню доктора, в котором можно
 * просматривать записи на сеансы, относящиеся к данному доктору
 */
class DoctorMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit DoctorMenu(QWidget *parent = nullptr);
    ~DoctorMenu();

signals:
    /*!
     * \brief Сигнал используемый для открытия меню входа
     */
    void entryWindow();

private slots:
    /*!
     * \brief Слот, который открывает меню входа
     */
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
