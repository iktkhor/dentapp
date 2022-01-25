#include "remindpassword.h"
#include "ui_remindpassword.h"

RemindPassword::RemindPassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RemindPassword)
{
    ui->setupUi(this);
    this->setWindowTitle("Напоминание пароля");
    change_buttons_enable(false);
    clear_ui();

    db.connect_to_database();
}

RemindPassword::~RemindPassword()
{
    delete ui;
}

void RemindPassword::on_show_secret_question_clicked()
{
    if (db.is_login_exist(ui->login->text())) {
        int ind = db.pull_user_question(ui->login->text());

        ui->secret_qustion->setText(db.pull_question(ind));
        change_buttons_enable(true);
    } else {
        QMessageBox::information(this, "Предупреждение"
                                     , "Аккаунта с таким логином не существует");
    }
}

void RemindPassword::on_change_pass_clicked()
{
    if (db.is_secret_answer_right(ui->login->text(), ui->sec_ques_answer->text())) {
        ui->stackedWidget->setCurrentIndex(1);
    } else {
        QMessageBox::information(this, "Предупреждение"
                                     , "Вы ввели неправильный ответ на вопрос");
    }
}

void RemindPassword::on_update_password_clicked()
{
    if (check_new_password()) {
        db.update_user_password(ui->login->text(), ui->new_password->text());
        close_window();
    }
}

bool RemindPassword::check_new_password() {
    if (ui->new_password->text() == db.pull_user_password(ui->login->text())) {
        if (QMessageBox::Yes == QMessageBox::question(this,
                                            "Предупреждение",
                                            "Ваш пароль совпадает с текущим\n желаете вернуться в меню входа?",
                                            QMessageBox::Yes|QMessageBox::No)) {
            close_window();
        } else {
            return false;
        }
    }
    if (ui->new_password->text().length() < 8) {
        QMessageBox::information(this, "Предупреждение",
                                 "Ваш пароль слишком короткий \nминимальная длина - 8 символов");
        return false;
    } else if (ui->new_password->text().length() > 15) {
        QMessageBox::information(this, "Предупреждение",
                                 "Ваш пароль слишком короткий \nмаксимальная длина - 15 символов");
        return false;
    }
    if (ui->new_password->text() != ui->new_password_repeat->text()) {
        QMessageBox::information(this, "Предупреждение", "Вы неправильно повторили пароль");
        return false;
    }

    return true;
}

void RemindPassword::on_back_clicked()
{
    if (QMessageBox::Yes == QMessageBox::question(this,
                                        "Предупреждение",
                                        "Вы уверены, что хотите вернуться назад?",
                                        QMessageBox::Yes|QMessageBox::No)) {
        close_window();
    }
}

void RemindPassword::on_back_to_menu_clicked()
{
    if (QMessageBox::Yes == QMessageBox::question(this,
                                        "Предупреждение",
                                        "Вы уверены, что хотите вернуться назад?",
                                        QMessageBox::Yes|QMessageBox::No)) {
        close_window();
    }
}

void RemindPassword::close_window() {
    change_buttons_enable(false);
    clear_ui();
    this->close();
    emit entryWindow();
}

void RemindPassword::clear_ui() {
    ui->login->setText("");
    ui->sec_ques_answer->setText("");
    ui->secret_qustion->setText("");
    ui->new_password->setText("");
    ui->new_password_repeat->setText("");
    ui->stackedWidget->setCurrentIndex(0);
}

void RemindPassword::change_buttons_enable(bool b) {
    ui->change_pass->setEnabled(b);
    ui->sec_ques_answer->setEnabled(b);
}
