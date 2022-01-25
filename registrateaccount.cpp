#include "registrateaccount.h"
#include "ui_registrateaccount.h"

RegistrateAccount::RegistrateAccount(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegistrateAccount)
{
    ui->setupUi(this);
    this->setWindowTitle("Регистрация пользователя");

    db.connect_to_database();

    qs = db.questions();
    fill_questions();
}

RegistrateAccount::~RegistrateAccount()
{
    delete ui;
}


void RegistrateAccount::on_back_clicked()
{
    if (QMessageBox::Yes == QMessageBox::question(this,
                                        "Предупреждение",
                                        "Вы уверены, что хотите вернуться назад?",
                                        QMessageBox::Yes|QMessageBox::No)) {
        close_window();
    }
}

void RegistrateAccount::on_end_reg_clicked()
{
    if (check_required_fields()) {
       db.registrate_user(new User(ui->lineEdit_name->text(), ui->lineEdit_login->text(), ui->lineEdit_password->text(),
                                   ui->comboBox_secret_questions->currentIndex(), ui->lineEdit_secret_question_answer->text(), "Client"));

       close_window();
    }
}

bool RegistrateAccount::check_required_fields(){

    if (ui->lineEdit_name->text().length() < 3) {
        QMessageBox::information(this, "Предупреждение", "Имя не может быть таким коротким");
        return false;
    }
    if (db.is_login_exist(ui->lineEdit_login->text())) {
        QMessageBox::information(this, "Предупреждение", "Такой логин уже существует");
        return false;
    }
    else if (ui->lineEdit_login->text().length() < 5) {
        QMessageBox::information(this, "Предупреждение", "Ваш логин слишком короткий \nминимальная длина - 5 символов");
        return false;
    } else if (ui->lineEdit_login->text().length() > 15) {
        QMessageBox::information(this, "Предупреждение", "Ваш логин слишком длинный \nмаксимальная длина - 15 символов");
        return false;
    }
    if (ui->lineEdit_password->text().length() < 8) {
        QMessageBox::information(this, "Предупреждение", "Ваш пароль слишком короткий \nминимальная длина - 8 символов");
        return false;
    } else if (ui->lineEdit_password->text().length() > 15) {
        QMessageBox::information(this, "Предупреждение", "Ваш пароль слишком короткий \nмаксимальная длина - 15 символов");
        return false;
    }

    if (ui->lineEdit_password->text() != ui->lineEdit_password_repeat->text()) {
        QMessageBox::information(this, "Предупреждение", "Вы неправильно повторили пароль");
        return false;
    }

    if (ui->lineEdit_secret_question_answer->text() == "") {
        QMessageBox::information(this, "Предупреждение", "Вы не ввели ответ на секретный вопрос");
        return false;
    }

    return true;
}

void RegistrateAccount::fill_questions() {
    for (int i(0); i < qs.size(); i++) {
       ui->comboBox_secret_questions->addItem(qs[i]);
    }
}

void RegistrateAccount::close_window() {
    clear_ui();
    this->close();
    emit entryWindow();
}

void RegistrateAccount::clear_ui() {
    ui->lineEdit_login->setText("");
    ui->lineEdit_name->setText("");
    ui->lineEdit_password->setText("");
    ui->lineEdit_password_repeat->setText("");
    ui->lineEdit_secret_question_answer->setText("");
    ui->comboBox_secret_questions->setCurrentIndex(0);
}
