#include "user.h"

User::User()
{

}

User::User(QString name, QString login, QString password, QString role) {
    this->set_name(name);
    this->set_login(login);
    this->set_password(password);
    this->set_role(role);
}

User::User(QString name, QString login, QString password, int sec_ques, QString sec_ques_answer, QString role) {
    this->set_name(name);
    this->set_login(login);
    this->set_password(password);
    this->set_sec_ques(sec_ques);
    this->set_sec_ques_answer(sec_ques_answer);
    this->set_role(role);
}

QString User::get_name() {
    return name;
}

QString User::get_login() {
    return login;
}

QString User::get_password() {
    return password;
}

QString User::get_sec_ques_answer() {
    return sec_ques_answer;
}

QString User::get_role() {
    if (role == Client) {
        return "Client";
    } else if (role == Doctor) {
        return "Doctor";
    } else if (role == Admin) {
        return "Admin";
    }

    return "role is not found";
}

int User::get_sec_ques() {
    return sec_ques;
}

void User::set_name(QString name) {
    this->name = name;
}

void User::set_login(QString login) {
    this->login = login;
}

void User::set_password(QString password) {
    this->password = password;
}

void User::set_sec_ques_answer(QString ans) {
    this->sec_ques_answer = ans;
}

void User::set_sec_ques(int sec_ques) {
    this->sec_ques = sec_ques;
}

void User::set_role(QString r) {
    if (r == "Client") {
        role = Client;
    } else if (r == "Doctor") {
        role = Doctor;
    } else if (r == "Admin") {
        role = Admin;
    }
}
