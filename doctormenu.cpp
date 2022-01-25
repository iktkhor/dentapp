#include "doctormenu.h"
#include "ui_doctormenu.h"

DoctorMenu::DoctorMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DoctorMenu)
{
    ui->setupUi(this);
    this->setWindowTitle("Меню доктора");

    db.connect_to_database();
}

DoctorMenu::~DoctorMenu()
{
    delete ui;
}

void DoctorMenu::update_sessions()
{
    ui->sessions->setRowCount(0);
    ui->sessions->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for (auto session : db.doctor_sessions(current_user->get_login())) {
        int ind = ui->sessions->rowCount();
        ui->sessions->insertRow(ind);

        QString cabinet;
        cabinet.setNum(session.get_cabinet());
        QString client = (session.get_client_id() == "") ? "" : db.pull_user_name(session.get_client_id());

        ui->sessions->setItem(ind, 0, new QTableWidgetItem(client));
        ui->sessions->setItem(ind, 1, new QTableWidgetItem(session.get_data()));
        ui->sessions->setItem(ind, 2, new QTableWidgetItem(session.get_time()));
        ui->sessions->setItem(ind, 3, new QTableWidgetItem(cabinet));
    }
}

void DoctorMenu::on_exit_clicked()
{
    this->hide();
    emit entryWindow();
}

void DoctorMenu::recieve_data(User* user) {
    current_user = user;
    update_sessions();
}
