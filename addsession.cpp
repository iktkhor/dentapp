#include "addsession.h"
#include "ui_addsession.h"

AddSession::AddSession(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddSession)
{
    ui->setupUi(this);
}

AddSession::~AddSession()
{
    delete ui;
}

void AddSession::on_add_clicked()
{

}


void AddSession::on_back_clicked()
{
    this->close();
}

