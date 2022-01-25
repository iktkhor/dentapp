#include "clientmenu.h"
#include "ui_clientmenu.h"

ClientMenu::ClientMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClientMenu)
{
    ui->setupUi(this);
    settings = new Settings();
    this->setWindowTitle("Меню клиента");

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
    emit send_data(current_user);
    settings->show();
}


void ClientMenu::on_make_delete_app_clicked()
{
    if (ui->make_delete_app->text() == "Записаться") {
        make_app();
    } else {
        delete_app();
    }
}

void ClientMenu::make_app() {
    QList<QTableWidgetItem*> selectedItems = ui->free_apps_table->selectedItems();
    std::set<int> selected_rows;

    for (auto item : selectedItems) {
        selected_rows.insert(item->row());
    }

    if (selected_rows.size() > 1) {
        QMessageBox::information(this, "Предупреждение", "Вы не можете сделать сразу 2 записи");
        return;
    }

    for (auto row : selected_rows) {
        QString id = ui->free_apps_table->item(row, 0)->text();
        db.update_session(id.toInt(), current_user->get_login());
    }

    update_free_apps();
}

void ClientMenu::delete_app() {
    QList<QTableWidgetItem*> selectedItems = ui->my_apps_table->selectedItems();
    std::set<int> selected_rows;

    for (auto item : selectedItems) {
        selected_rows.insert(item->row());
    }

    for (auto row : selected_rows) {
        QString id = ui->my_apps_table->item(row, 0)->text();
        db.update_session(id.toInt());
    }

    update_my_apps();
}

void ClientMenu::on_change_tables_clicked()
{
    if (ui->stackedWidget->currentIndex() == 0) {
        ui->change_tables->setText("Свободные записи");
        ui->make_delete_app->setText("Отменить запись");
        ui->stackedWidget->setCurrentIndex(1);
        update_my_apps();
    } else {
        ui->change_tables->setText("Мои записи");
        ui->make_delete_app->setText("Записаться");
        ui->stackedWidget->setCurrentIndex(0);
        update_free_apps();
    }
}

void ClientMenu::update_free_apps() {
    ui->free_apps_table->setRowCount(0);
    ui->free_apps_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->free_apps_table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->free_apps_table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);


    for (auto session : db.sessions(false)) {
        int ind = ui->free_apps_table->rowCount();
        ui->free_apps_table->insertRow(ind);

        QString id;
        id.setNum(session.get_id());
        QString cabinet;
        cabinet.setNum(session.get_cabinet());
        QString doc_name = db.pull_user_name(session.get_doctor_id());

        ui->free_apps_table->setItem(ind, 0, new QTableWidgetItem(id));
        ui->free_apps_table->setItem(ind, 1, new QTableWidgetItem(doc_name));
        ui->free_apps_table->setItem(ind, 2, new QTableWidgetItem(session.get_data()));
        ui->free_apps_table->setItem(ind, 3, new QTableWidgetItem(session.get_time()));
        ui->free_apps_table->setItem(ind, 4, new QTableWidgetItem(cabinet));
    }
}

void ClientMenu::update_my_apps() {
    ui->my_apps_table->setRowCount(0);
    ui->my_apps_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->my_apps_table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->my_apps_table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);

    for (auto session : db.sessions(current_user->get_login())) {
        int ind = ui->my_apps_table->rowCount();
        ui->my_apps_table->insertRow(ind);

        QString id;
        id.setNum(session.get_id());
        QString cabinet;
        cabinet.setNum(session.get_cabinet());
        QString doc_name = db.pull_user_name(session.get_doctor_id());

        ui->my_apps_table->setItem(ind, 0, new QTableWidgetItem(id));
        ui->my_apps_table->setItem(ind, 1, new QTableWidgetItem(doc_name));
        ui->my_apps_table->setItem(ind, 2, new QTableWidgetItem(session.get_data()));
        ui->my_apps_table->setItem(ind, 3, new QTableWidgetItem(session.get_time()));
        ui->my_apps_table->setItem(ind, 4, new QTableWidgetItem(cabinet));
    }
}

void ClientMenu::recieve_data(User* user) {
    current_user = user;
}

void ClientMenu::update_ui() {
    ui->stackedWidget->setCurrentIndex(0);
    ui->change_tables->setText("Мои записи");
    ui->make_delete_app->setText("Записаться");
    update_free_apps();
}

void ClientMenu::on_my_apps_table_cellClicked(int row, int column) {
    ui->my_apps_table->selectRow(row);
}

void ClientMenu::on_free_apps_table_cellClicked(int row, int column) {
    ui->free_apps_table->selectRow(row);
}

