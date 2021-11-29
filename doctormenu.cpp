#include "doctormenu.h"
#include "ui_doctormenu.h"

DoctorMenu::DoctorMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DoctorMenu)
{
    ui->setupUi(this);
}

DoctorMenu::~DoctorMenu()
{
    delete ui;
}

void DoctorMenu::on_exit_clicked()
{
    this->close();
    emit entryWindow();
}

