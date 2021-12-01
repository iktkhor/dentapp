#include "entrywindow.h"
#include "ui_entrywindow.h"
#include "remindpassword.h"
#include "clickablelabel.h"


EntryWindow::EntryWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EntryWindow)
{
    ui->setupUi(this);

    reg_acc_window = new RegistrateAccount(this);
    rem_pass_window = new RemindPassword(this);
    admin_menu_window = new AdminMenu(this);
    client_menu_window = new ClientMenu(this);
    doctor_menu_window = new DoctorMenu(this);

    connect(reg_acc_window, &RegistrateAccount::entryWindow, this, &EntryWindow::show);

    connect(rem_pass_window, &RemindPassword::entryWindow, this, &EntryWindow::show);

    connect(client_menu_window, &ClientMenu::entryWindow, this, &EntryWindow::show);

    connect(admin_menu_window, &AdminMenu::entryWindow, this, &EntryWindow::show);

    connect(ui->label_rem_pass, &ClickableLabel::clicked, this, &EntryWindow::on_remind_pass_clicked);

    connect(ui->label_reg_acc, &ClickableLabel::clicked, this, &EntryWindow::on_reg_acc_clicked);

    connect(ui->button_entry, &QPushButton::clicked, this, &EntryWindow::on_entry_clicked);

    connect(this, &EntryWindow::send_data, client_menu_window, &ClientMenu::recieve_data);

    connect(this, &EntryWindow::update_table, admin_menu_window, &AdminMenu::update_sessions);

    connect(this, &EntryWindow::update_table, client_menu_window, &ClientMenu::update_ui);

    is_pass_vis = false;
    ui->lineEdit_password->setEchoMode(QLineEdit::Password);

    db.connect_to_database();

}

EntryWindow::~EntryWindow()
{
    delete ui;
}

void EntryWindow::on_entry_clicked()
{
    QString log = ui->lineEdit_login->text();
    QString pass = ui->lineEdit_password->text();

    if (db.is_authorize_data_right(log, pass)) {
        QString role = db.pull_user_role(log);

        if (role == "Client") {
            this->close();
            emit send_data(db.pull_user(log));
            emit update_table();
            ui->lineEdit_password->setText("");
            client_menu_window->show();
        } else if (role == "Doctor") {
            this->close();
            ui->lineEdit_password->setText("");
            doctor_menu_window->show();
        } else if (role == "Admin") {
            this->close();
            ui->lineEdit_password->setText("");
            emit update_table();
            admin_menu_window->show();         
        }
    } else {
        QMessageBox::information(this, "Предупреждение"
                                     , "Вы ввели неправильный логин или пароль");
    }
}

void EntryWindow::on_remind_pass_clicked()
{
    this->close();
    rem_pass_window->show();
}

void EntryWindow::on_reg_acc_clicked()
{
    this->close();
    reg_acc_window->show();
}

void EntryWindow::on_checkBox_show_pass_stateChanged(int arg1)
{
    is_pass_vis = !is_pass_vis;

    if (is_pass_vis) {
        ui->lineEdit_password->setEchoMode(QLineEdit::Normal);
    } else {
        ui->lineEdit_password->setEchoMode(QLineEdit::Password);
    }
}


