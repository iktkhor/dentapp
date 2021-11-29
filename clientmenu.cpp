#include "clientmenu.h"
#include "ui_clientmenu.h"

ClientMenu::ClientMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClientMenu)
{
    ui->setupUi(this);
    settings = new Settings();

    db.connect_to_database();

    connect(this, SIGNAL(send_data(User*)), settings, SLOT(recieve_data(User*)));

    connect(settings, &Settings::send_data, this, &ClientMenu::recieve_data);
}

ClientMenu::~ClientMenu()
{
    delete ui;
}

void ClientMenu::on_log_out_clicked()
{
    this->close();
    emit entryWindow();
}

void ClientMenu::on_change_user_data_clicked()
{
    settings->exec();
    emit send_data(current_user);
}

void ClientMenu::recieve_data(User* user) {
    current_user = user;
}

