#include "addsession.h"
#include "ui_addsession.h"

AddSession::AddSession(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddSession)
{
    ui->setupUi(this);
    this->setWindowTitle("Добавление записей");

    db.connect_to_database();
}

AddSession::~AddSession()
{
    delete ui;
}

void AddSession::on_add_clicked()
{
    if (check_fields()) {
       for (int i(0); i < ui->count->value(); i++) {
           QString time_start;
           time_start.setNum(ui->hours->text().toInt() + i);
           QString time_end;
           time_end.setNum(ui->hours->text().toInt() + i + 1);
           QString time = time_start + ":" + ui->mins->text() + " - " + time_end + ":" + ui->mins->text();
           QString data = ui->date->date().toString("yyyy-MM-dd");
           int cabinet = ui->cabinet->text().toInt();

           QString login = doctors[ui->doctor->currentIndex() - 1].get_login();
           db.add_session(new Session(login, cabinet, data, time));
       }

       emit update();
       clear_ui();
    }
}

void AddSession::on_back_clicked()
{
    clear_ui();
    this->close();
}

bool AddSession::check_fields() {
    if (ui->doctor->currentIndex() == 0) {
        QMessageBox::information(this, "Предупреждение", "Вы не выбрали доктора");
        return false;
    }
    if (ui->date->text() == "") {
        QMessageBox::information(this, "Предупреждение", "Вы не ввели дату");
        return false;
    }
    if (ui->hours->text() == "" && ui->mins->text() == "") {
        QMessageBox::information(this, "Предупреждение", "Вы не ввели полностью время начала");
        return false;
    }

    return true;
}

void AddSession::update_ui() {
    doctors = db.users("Doctor");
    ui->doctor->clear();

    ui->doctor->addItem("");
    for (auto doctor : doctors) {
        ui->doctor->addItem(doctor.get_name());
    }

    ui->date->setMinimumDate(QDate::currentDate());
}

void AddSession::clear_ui() {
    ui->doctor->setCurrentIndex(0);
    ui->date->clear();
    ui->hours->setText("");
    ui->mins->setText("");
    ui->count->setValue(1);
}


