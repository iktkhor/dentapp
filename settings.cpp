#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    this->setWindowTitle("Настройки профиля");

    db.connect_to_database();
    qs = db.questions();
    for (int i(0); i < qs.size(); i++) {
       ui->sec_ques->addItem(qs[i]);
    }

    set_enabled_data(false);
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_change_data_clicked()
{
    if (ui->name->isEnabled()) {
        update_ui();
        set_enabled_data(false);
        ui->change_data->setText("Изменить данные");
    } else {
        set_enabled_data(true);
        ui->change_data->setText("Прекратить редактирование");
    }
}


void Settings::on_save_data_clicked()
{
    set_enabled_data(false);
    if (ui->name->text() != current_user->get_name()) {
        db.update_user_name(current_user->get_login() ,ui->name->text());
        is_changed = true;
    }
    if (ui->password->text() != current_user->get_password()) {
        db.update_user_password(current_user->get_login(), ui->password->text());
        is_changed = true;
    }
    if (ui->sec_ques->currentIndex() != current_user->get_sec_ques()
            && ui->sec_ques_answer->text() != current_user->get_sec_ques_answer()) {
        db.update_user_secret_question(current_user->get_login(), ui->sec_ques->currentIndex());
        is_changed = true;
    }
    if (ui->login->text() != current_user->get_login()) {
        db.update_user_login(current_user->get_login(), ui->login->text());
        is_changed = true;
    }
    if (ui->sec_ques->currentIndex() != current_user->get_sec_ques()) {
        db.update_user_secret_question(current_user->get_login(), ui->sec_ques->currentIndex());
        is_changed = true;
    }
    if (ui->sec_ques_answer->text() != current_user->get_sec_ques_answer()) {
        db.update_user_secret_question_answer(current_user->get_login(), ui->sec_ques_answer->text());
        is_changed = true;
    }
    if (is_changed) {
        current_user = db.pull_user(ui->login->text());
    }

    update_ui();
}

void Settings::update_ui() {
    ui->name->setText(current_user->get_name());
    ui->login->setText(current_user->get_login());
    ui->password->setText(current_user->get_password());
    ui->sec_ques_answer->setText(current_user->get_sec_ques_answer());
}

void Settings::set_enabled_data(bool b) {
    ui->name->setEnabled(b);
    ui->login->setEnabled(b);
    ui->password->setEnabled(b);
    ui->sec_ques->setEnabled(b);
    ui->sec_ques_answer->setEnabled(b);
    ui->save_data->setEnabled(b);
}

void Settings::recieve_data(User* current_user) {
    this->current_user = current_user;
    update_ui();
}

void Settings::on_back_clicked()
{
    this->hide();

    if (is_changed) {
        emit send_data(current_user);
    }
}
