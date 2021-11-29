#include "adddoctor.h"
#include "ui_adddoctor.h"

AddDoctor::AddDoctor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDoctor)
{
    //clear_ui();
    ui->setupUi(this);

    db.connect_to_database();
}

AddDoctor::~AddDoctor()
{
    delete ui;
}

void AddDoctor::on_add_clicked()
{
    if (check_fields()) {
        db.registrate_doctor(new User(ui->name->text(), ui->login->text(), ui->password->text(), "Doctor"));
        clear_ui();
        emit update();
    }
}

void AddDoctor::on_back_clicked()
{
    this->close();
}

bool AddDoctor::check_fields() {
    if (db.is_login_exist(ui->login->text())) {
        QMessageBox::information(this, "Предупреждение", "Такой логин уже существует");
        return false;
    }
    if (ui->password->text().length() < 8) {
        QMessageBox::information(this, "Предупреждение", "Пароль слишком короткий \nминимальная длина - 8 символов");
        return false;
    }

    return true;
}

void AddDoctor::clear_ui() {
    ui->name->setText("");
    ui->login->setText("");
    ui->password->setText("");

}
