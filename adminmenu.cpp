#include "adminmenu.h"
#include "ui_adminmenu.h"

AdminMenu::AdminMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminMenu)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    this->setWindowTitle("Меню админа");

    db.connect_to_database();

    add_doctor = new AddDoctor(this);
    add_session = new AddSession(this);

    connect(add_doctor, &AddDoctor::update, this, &AdminMenu::update_users);

    connect(add_session, &AddSession::update, this, &AdminMenu::update_sessions);

    connect(this, &AdminMenu::update, add_session, &AddSession::update_ui);
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
    emit update();
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
        auto login = ui->users_table->item(row, 1)->text();
        removed_users.insert(login);
    }

    for (auto user : removed_users) {
        db.remove_user(user);
        db.remove_session(user);
    }

    update_users();
}

void AdminMenu::on_delete_session_clicked() {

    QList<QTableWidgetItem*> selectedItems = ui->sessions_table->selectedItems();
    std::set<int> selected_rows;

    for (auto item : selectedItems) {
        selected_rows.insert(item->row());
    }

    for (auto row : selected_rows) {
        QString id = ui->sessions_table->item(row, 0)->text();
        db.remove_session(id.toInt());
    }

    update_sessions();
}


void AdminMenu::on_cancel_app_clicked() {
    QList<QTableWidgetItem*> selectedItems = ui->sessions_table->selectedItems();
    std::set<int> selected_rows;

    for (auto item : selectedItems) {
        selected_rows.insert(item->row());
    }

    for (auto row : selected_rows) {
        QString id = ui->sessions_table->item(row, 0)->text();

        if (db.pull_session_is_busy(id.toInt())) {
            db.update_session(id.toInt());
        }
    }

    update_sessions();
}

void AdminMenu::on_add_doctor_clicked() {
    add_doctor->show();
}

void AdminMenu::on_change_tables_clicked() {
    if (ui->stackedWidget->currentIndex() == 0) {
        ui->change_tables->setText("Управление сеансами");
        set_enabled_buttons(false);
        ui->stackedWidget->setCurrentIndex(1);
        update_users();
    } else {
        ui->change_tables->setText("Управление аккаунтами");
        set_enabled_buttons(true);
        ui->stackedWidget->setCurrentIndex(0);
        update_sessions();
    }

}

void AdminMenu::update_sessions() {
    ui->sessions_table->setRowCount(0);
    ui->sessions_table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->sessions_table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    ui->sessions_table->horizontalHeader()->setSectionResizeMode(6, QHeaderView::Stretch);

    for (auto session : db.sessions()) {
        int ind = ui->sessions_table->rowCount();
        ui->sessions_table->insertRow(ind);

        QString id;
        id.setNum(session.get_id());
        QString cabinet;
        cabinet.setNum(session.get_cabinet());
        QString doc_name = db.pull_user_name(session.get_doctor_id());

        ui->sessions_table->setItem(ind, 0, new QTableWidgetItem(id));
        ui->sessions_table->setItem(ind, 1, new QTableWidgetItem(doc_name));
        ui->sessions_table->setItem(ind, 2, new QTableWidgetItem(session.get_client_id()));
        ui->sessions_table->setItem(ind, 3, new QTableWidgetItem(session.get_data()));
        ui->sessions_table->setItem(ind, 4, new QTableWidgetItem(session.get_time()));
        ui->sessions_table->setItem(ind, 5, new QTableWidgetItem(cabinet));
        ui->sessions_table->setItem(ind, 6, new QTableWidgetItem(session.get_is_busy() ? "да" : "нет"));
    }
}

void AdminMenu::update_users() {
    ui->users_table->setRowCount(0);
    ui->users_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->users_table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);

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

void AdminMenu::on_sessions_table_cellClicked(int row, int column) {
    ui->sessions_table->selectRow(row);
}


void AdminMenu::on_users_table_cellClicked(int row, int column)
{
    ui->users_table->selectRow(row);
}
