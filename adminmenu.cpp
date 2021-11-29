#include "adminmenu.h"
#include "ui_adminmenu.h"

AdminMenu::AdminMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminMenu)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    db.connect_to_database();

    add_doctor = new AddDoctor(this);
    add_session = new AddSession(this);

    connect(add_doctor, &AddDoctor::update, this, &AdminMenu::update_users);
}

AdminMenu::~AdminMenu()
{
    delete ui;
}

void AdminMenu::on_log_out_clicked()
{
    this->close();
    emit entryWindow();
}

void AdminMenu::on_add_session_clicked()
{
    add_session->show();
}

void AdminMenu::on_delete_acc_clicked()
{
    QList<QTableWidgetItem*> selectedItems = ui->users_table->selectedItems();
    std::set<int> selected_rows;
    std::set<QString> removed_users;

    for (auto item : selectedItems) {
        selected_rows.insert(item->row());
    }

    for (auto row : selected_rows) {
        auto article = ui->users_table->item(row, 1)->text();
        removed_users.insert(article);
    }

    for (auto user : removed_users) {
        db.remove_user(user);
    }

    update_users();
}


void AdminMenu::on_add_doctor_clicked()
{
    add_doctor->show();
}

void AdminMenu::on_change_tables_clicked()
{
    if (ui->stackedWidget->currentIndex() == 0) {
        ui->change_tables->setText("Управление сеансами");
        set_enabled_buttons(false);
        ui->stackedWidget->setCurrentIndex(1);
        update_users();
    } else {
        ui->change_tables->setText("Управление аккаунтами");
        set_enabled_buttons(true);
        ui->stackedWidget->setCurrentIndex(0);
    }

}

void AdminMenu::update_sessins() {

}

void AdminMenu::update_users() {
    ui->users_table->setRowCount(0);
    fill_table_users(db.users("Admin"));
    fill_table_users(db.users("Doctor"));
    fill_table_users(db.users("Client"));
}

void AdminMenu::fill_table_users(std::vector<User> users) {
    for (auto user : users) {
        int ind = ui->users_table->rowCount();
        ui->users_table->insertRow(ind);

        ui->users_table->setItem(ind, 0, new QTableWidgetItem(user.get_role()));
        ui->users_table->setItem(ind, 1, new QTableWidgetItem(user.get_login()));
        ui->users_table->setItem(ind, 2, new QTableWidgetItem(user.get_name()));
    }
}

void AdminMenu::set_enabled_buttons(bool b) {
    ui->cancel_app->setEnabled(b);
    ui->delete_session->setEnabled(b);
    ui->add_session->setEnabled(b);
}



