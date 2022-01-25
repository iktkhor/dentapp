#include "database.h"

DataBase::DataBase()
{

}

void DataBase::connect_to_database() {
    if (!QFile(QCoreApplication::applicationDirPath() + "/" DATABASE_NAME).exists()) {
        this->restore_database();
    } else {
        this->open_database();
    }
}

bool DataBase::restore_database() {
    if(this->open_database()) {
        return (this->create_tables()) ? true : false;
    } else {
        qDebug() << "Не удалось восстановить базу данных";
        return false;
    }

    return false;
}

bool DataBase::open_database() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QCoreApplication::applicationDirPath() + "/" DATABASE_NAME);

    if (db.open()) {
        return true;
    } else {
        return false;
    }
}

void DataBase::close_database() {
    db.close();
}

bool DataBase::create_tables() {
    if (!create_secret_question_table()) {
        return false;
    }
    if (!create_user_table()) {
        return false;
    }
    if (!create_sessions_table()) {
        return false;
    }

    return true;
}

bool DataBase::create_user_table() {
    QSqlQuery create_user_table;
    db.exec("PRAGMA foreign_keys = ON");

    if (!create_user_table.exec( "CREATE TABLE "  TABLE_USER  " ("
                             "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                             "name VARCHAR(255) NOT NULL, "
                             "login VARCHAR(20) NOT NULL, "
                             "password VARCHAR(20) NOT NULL, "
                             "secret_question INTEGER, "
                             "sec_ques_answer VARCHAR(20), "
                             "role VARCHAR(10) NOT NULL, "
                             "FOREIGN KEY (secret_question) REFERENCES "
                              TABLE_SECRET_QUESTIONS "(id)"
                             ")"
                )) {
        qDebug() << "DataBase: error of create " << TABLE_USER;
        qDebug() << create_user_table.lastError().text();
        return false;
    } else if (registrate_doctor(new User("Admin", "admin", "admin", "Admin"))) {
        qDebug() << "DataBase: successful created " << TABLE_USER;
        return true;
    }
}

bool DataBase::create_secret_question_table() {
    QSqlQuery create_sec_quest_table;

    if (!create_sec_quest_table.exec( "CREATE TABLE "  TABLE_SECRET_QUESTIONS  " ("
                             "id INTEGER PRIMARY KEY, "
                             "question VARCHAR(255) NOT NULL"
                             ")"
                )) {
        qDebug() << "DataBase: error of create " << TABLE_SECRET_QUESTIONS;
        qDebug() << create_sec_quest_table.lastError().text();
        return false;
    } else if (add_questions()) {
        qDebug() << "DataBase: successful created " << TABLE_SECRET_QUESTIONS;
        return true;
    }
}

bool DataBase::add_questions() {
    QSqlQuery add_question;
    QList<QString> qs;
    qs.append("");
    qs.append("Ваш любимый сериал?");
    qs.append("Ваш любимый спорт?");
    qs.append("Ваш любимый мультфильм?");
    qs.append("Ваше любимое блюдо?");
    qs.append("Ваше любимое аниме?");

    add_question.prepare("INSERT INTO " TABLE_SECRET_QUESTIONS "("
                         "id, question) VALUES (:id, :qs)");

    for (int i(0); i < qs.size(); i++) {
        add_question.bindValue(":qs", qs[i]);
        add_question.bindValue(":id", i);
        add_question.exec();
    }

    return true;
}

bool DataBase::create_sessions_table() {
    QSqlQuery create_sec_quest_table;
    db.exec("PRAGMA foreign_keys = ON");

    if (!create_sec_quest_table.exec( "CREATE TABLE " TABLE_SESSIONS " ("
                             "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                             "doctor_id VARCHAR(20) NOT NULL, "
                             "client_id VARCHAR(20), "
                             "cabinet INTEGER NOT NULL, "
                             "data VARCHAR(15) NOT NULL, "
                             "time VARCHAR(15) NOT NULL, "
                             "is_busy INTEGER NOT NULL, "
                             "FOREIGN KEY (doctor_id) REFERENCES "
                             TABLE_USER "(login), "
                             "FOREIGN KEY (client_id) REFERENCES "
                             TABLE_USER "(login)"
                             ")"
                )) {
        qDebug() << "DataBase: error of create " << TABLE_SESSIONS;
        qDebug() << create_sec_quest_table.lastError().text();
        return false;
    } else if (add_questions()) {
        qDebug() << "DataBase: successful created " << TABLE_SESSIONS;
        return true;
    }
}

bool DataBase::registrate_user(User *new_user){
    QSqlQuery reg_user;
    reg_user.prepare("INSERT INTO " TABLE_USER "("
                             "name, login, password, secret_question, sec_ques_answer, role) "
                             "VALUES (:nm, :log, :pass, :sq, :sqa, :role)");
    reg_user.bindValue(":nm", new_user->get_name());
    reg_user.bindValue(":log", new_user->get_login());
    reg_user.bindValue(":pass", new_user->get_password());
    reg_user.bindValue(":sq", new_user->get_sec_ques());
    reg_user.bindValue(":sqa", new_user->get_sec_ques_answer());
    reg_user.bindValue(":role", new_user->get_role());

    if (!reg_user.exec()) {
        qDebug() << "error create client in " << TABLE_USER;
        qDebug() << reg_user.lastError().text();
        return false;
    } else {
        qDebug() << "user successfully created in " << TABLE_USER;
        return true;
    }
}

bool DataBase::registrate_doctor(User *new_doc) {
    QSqlQuery reg_doc;
    reg_doc.prepare("INSERT INTO " TABLE_USER "("
                             "name, login, password, role) "
                             "VALUES (:nm, :log, :pass, :role)");
    reg_doc.addBindValue(new_doc->get_name());
    reg_doc.addBindValue(new_doc->get_login());
    reg_doc.addBindValue(new_doc->get_password());
    reg_doc.addBindValue(new_doc->get_role());

    if (!reg_doc.exec()) {
        qDebug() << "error create doctor in " << TABLE_USER;
        qDebug() << reg_doc.lastError().text();
        return false;
    } else {
        qDebug() << "doctor successfully created in " << TABLE_USER;
        return true;
    }
}

bool DataBase::is_login_exist(QString login) {
    QSqlQuery is_login_exist;
    is_login_exist.prepare("SELECT * FROM " TABLE_USER " "
                           "WHERE login = (:login)");
    is_login_exist.bindValue(":login", login);

    if (is_login_exist.exec()) {
        if (is_login_exist.next()) {
            return true;
        }
    }

    return false;
}

bool DataBase::is_authorize_data_right(QString login, QString password) {
    QSqlQuery is_password_right;
    is_password_right.prepare("SELECT * FROM " TABLE_USER " "
                              "WHERE login = (:login) AND password = (:password)");
    is_password_right.bindValue(":login", login);
    is_password_right.bindValue(":password", password);

    if(is_password_right.exec()) {
        if(is_password_right.next()) {
            return true;
        }
    }

    return false;
}

bool DataBase::is_secret_answer_right(QString login, QString answer) {
    QSqlQuery is_password_right;
    is_password_right.prepare("SELECT * FROM " TABLE_USER " "
                              "WHERE login = (:login) AND sec_ques_answer = (:answer)");
    is_password_right.bindValue(":login", login);
    is_password_right.bindValue(":answer", answer);

    if(is_password_right.exec()) {
        if(is_password_right.next()) {
            return true;
        }
    }

    return false;
}

QList<QString> DataBase::questions() {
    QSqlQuery pull_questions;
    QList<QString> qs;
    pull_questions.prepare("SELECT question FROM " TABLE_SECRET_QUESTIONS);

    if (pull_questions.exec()) {
        while (pull_questions.next()) {
            qs.append(pull_questions.value(0).toString());
        }

        return qs;
    }

    qDebug() << "DataBase: error of pulling questions " << TABLE_SECRET_QUESTIONS;
}

QString DataBase::pull_question(int index) {
    QSqlQuery pull_question;
    pull_question.prepare("SELECT question FROM " TABLE_SECRET_QUESTIONS " "
                          "WHERE id = (:id)");
    pull_question.bindValue(":id", index);

    if (pull_question.exec()) {
        if (pull_question.next()) {
            qDebug() << "DataBase: question value find out successfully";
            return pull_question.value(0).toString();
        }
    } else {
        qDebug() << "DataBase: error of pull value of question " << TABLE_SECRET_QUESTIONS;
        qDebug() << pull_question.lastError().text();
    }
}

std::vector<User> DataBase::users() {
    QSqlQuery pull_users;
    std::vector<User> users;
    pull_users.prepare("SELECT name, login, password, role "
                       "FROM " TABLE_USER);

    if (pull_users.exec()) {
        while (pull_users.next()) {
            users.push_back(User(pull_users.value(0).toString(), pull_users.value(1).toString(),
                                     pull_users.value(2).toString(), pull_users.value(3).toString()));
        }
        qDebug() << "users pulled successfully from " << TABLE_USER;
    } else {
        qDebug() << "DataBase: error pull users from " << TABLE_USER;
        qDebug() << pull_users.lastError().text();
    }

    return users;
}

std::vector<User> DataBase::users(QString role) {
    QSqlQuery pull_users;
    std::vector<User> users;
    pull_users.prepare("SELECT name, login, password "
                       "FROM " TABLE_USER " "
                       "WHERE role = (:rl)");
    pull_users.bindValue(":rl", role);

    if (pull_users.exec()) {
        while (pull_users.next()) {
            users.push_back(User(pull_users.value(0).toString(), pull_users.value(1).toString(),
                                     pull_users.value(2).toString(), role));
        }
        qDebug() << role << " users pulled successfully from " << TABLE_USER;
    } else {
        qDebug() << "DataBase: error pull users from " << TABLE_USER;
        qDebug() << pull_users.lastError().text();
    }

    return users;
}

User* DataBase::pull_user(QString login) {
    QSqlQuery pull_user;
    pull_user.prepare("SELECT * FROM " TABLE_USER " "
                      "WHERE login = (:log)");
    pull_user.bindValue(":log", login);

    if (pull_user.exec()) {
        if (pull_user.next()) {
            QString name = pull_user.value(1).toString();
            QString login = pull_user.value(2).toString();
            QString password = pull_user.value(3).toString();
            int sec_ques = pull_user.value(4).toInt();
            QString sec_ques_answer = pull_user.value(5).toString();
            QString role = pull_user.value(6).toString();

            return new User(name, login, password, sec_ques, sec_ques_answer, role);
        }
    } else {
       qDebug() << "DataBase: error pull user in" << TABLE_USER;
       qDebug() << pull_user.lastError().text();
    }
}

QString DataBase::pull_user_name(QString login) {
    QSqlQuery pull_pass;
    pull_pass.prepare("SELECT name FROM " TABLE_USER " "
                      "WHERE login = (:log)");
    pull_pass.bindValue(":log", login);

    if (pull_pass.exec()) {
        if (pull_pass.next()) {
            qDebug() << "DataBase: name is pulled successfully";
            return pull_pass.value(0).toString();
        }
    } else {
        qDebug() << "DataBase: error of pull password " << TABLE_USER;
        qDebug() << pull_pass.lastError().text();
    }
}

QString DataBase::pull_user_password(QString login) {
    QSqlQuery pull_pass;
    pull_pass.prepare("SELECT password FROM " TABLE_USER " "
                      "WHERE login = (:log)");
    pull_pass.bindValue(":log", login);

    if (pull_pass.exec()) {
        if (pull_pass.next()) {
            qDebug() << "DataBase: password is pulled successfully";
            return pull_pass.value(0).toString();
        }
    } else {
        qDebug() << "DataBase: error of pull password " << TABLE_USER;
        qDebug() << pull_pass.lastError().text();
    }
}

QString DataBase::pull_user_role(QString login) {
    QSqlQuery pull_role;
    pull_role.prepare("SELECT role FROM " TABLE_USER " "
                      "WHERE login = (:log)");
    pull_role.bindValue(":log", login);

    if (pull_role.exec()) {
        if (pull_role.next()) {
            qDebug() << "DataBase: role is pulled successfully" << pull_role.value(0).toString();
            return pull_role.value(0).toString();
        }
    } else {
        qDebug() << "DataBase: error of pull role " << TABLE_USER;
        qDebug() << pull_role.lastError().text();
    }
}

int DataBase::pull_user_question(QString login) {
    QSqlQuery pull_ques;
    pull_ques.prepare("SELECT secret_question FROM " TABLE_USER
                      " WHERE login = (:log)");
    pull_ques.bindValue(":log", login);

    if (pull_ques.exec()) {
        if (pull_ques.next()) {
            qDebug() << "DataBase: question id is pulled successfully";
            return pull_ques.value(0).toInt();
        }
    } else {
        qDebug() << "DataBase: error of pull id of question " << TABLE_USER;
        qDebug() << pull_ques.lastError().text();
    }
}

bool DataBase::remove_user(QString login) {
    QSqlQuery remove_user;
    remove_user.prepare("DELETE FROM " TABLE_USER " "
                        "WHERE login = (:log)");
    remove_user.addBindValue(login);

    if (remove_user.exec()) {
        qDebug() << "User is deleted";
    } else {
        qDebug() << "error User is delete";
    }
}

bool DataBase::update_user_login(QString login, QString new_login) {
    QSqlQuery update_user_login;
    update_user_login.prepare("UPDATE " TABLE_USER " "
                              "SET login = (:log) "
                              "WHERE login = (:nlog)");
    update_user_login.bindValue(":log", login);
    update_user_login.bindValue(":nlog", new_login);

    if (update_user_login.exec()) {
        qDebug() << "DataBase: login is updated" << TABLE_USER;
        return true;
    } else {
        qDebug() << "DataBase: error update login " << TABLE_USER;
        qDebug() << update_user_login.lastError().text();
        return false;
    }
}

bool DataBase::update_user_name(QString login, QString new_name) {
    QSqlQuery update_user_name;
    update_user_name.prepare("UPDATE " TABLE_USER " "
                             "SET name = (:nm) "
                              "WHERE login = (:log)");
    update_user_name.bindValue(":log", login);
    update_user_name.bindValue(":nm", new_name);

    if (update_user_name.exec()) {
        qDebug() << "DataBase: name is updated" << TABLE_USER;
        return true;
    } else {
        qDebug() << "DataBase: error update name " << TABLE_USER;
        qDebug() << update_user_name.lastError().text();
        return false;
    }
}

bool DataBase::update_user_password(QString login, QString new_pass) {
    QSqlQuery update_user_pass;
    update_user_pass.prepare("UPDATE " TABLE_USER " "
                             "SET password = (:nm) "
                             "WHERE login = (:log)");
    update_user_pass.bindValue(":log", login);
    update_user_pass.bindValue(":nm", new_pass);

    if (update_user_pass.exec()) {
        qDebug() << "DataBase: password is updated" << TABLE_USER;
        return true;
    } else {
        qDebug() << "DataBase: error update password " << TABLE_USER;
        qDebug() << update_user_pass.lastError().text();
        return false;
    }
}

bool DataBase::update_user_secret_question(QString login, int ind) {
    QSqlQuery update_user_secret_question;
    update_user_secret_question.prepare("UPDATE " TABLE_USER " "
                                        "SET secret_question = (:sq) "
                                        "WHERE login = (:log)");
    update_user_secret_question.bindValue(":log", login);
    update_user_secret_question.bindValue(":sq", ind);

    if (update_user_secret_question.exec()) {
        qDebug() << "DataBase: secret_question is updated " << TABLE_USER;
        return true;
    } else {
        qDebug() << "DataBase: error update secret_question " << TABLE_USER;
        qDebug() << update_user_secret_question.lastError().text();
        return false;
    }
}

bool DataBase::update_user_secret_question_answer(QString login, QString answer) {
    QSqlQuery update_user_secret_question_answer;
    update_user_secret_question_answer.prepare("UPDATE " TABLE_USER " "
                                               "SET sec_ques_answer = (:sqa) "
                                               "WHERE login = (:log)");
    update_user_secret_question_answer.bindValue(":log", login);
    update_user_secret_question_answer.bindValue(":sqa", answer);

    if (update_user_secret_question_answer.exec()) {
        qDebug() << "DataBase: seccer_question_answer is updated " << TABLE_USER;
        return true;
    } else {
        qDebug() << "DataBase: error update secret_question_answer " << TABLE_USER;
        qDebug() << update_user_secret_question_answer.lastError().text();
        return false;
    }
}

bool DataBase::add_session(Session *new_session) {
    QSqlQuery add_sesion;
    add_sesion.prepare("INSERT INTO " TABLE_SESSIONS "("
                       "doctor_id, cabinet, data, time, is_busy) "
                       "VALUES (:did, :cab, :dt, :tm, :isb)");
    add_sesion.addBindValue(new_session->get_doctor_id());
    add_sesion.addBindValue(new_session->get_cabinet());
    add_sesion.addBindValue(new_session->get_data());
    add_sesion.addBindValue(new_session->get_time());
    add_sesion.addBindValue(0);

    if (!add_sesion.exec()) {
        qDebug() << "error add_session in " << TABLE_SESSIONS;
        qDebug() << add_sesion.lastError().text();
        return false;
    } else {
        qDebug() << "session successfully created in " << TABLE_SESSIONS;
        return true;
    }
}

bool DataBase::remove_session(int id) {
    QSqlQuery remove_session;
    remove_session.prepare("DELETE FROM " TABLE_SESSIONS " "
                           "WHERE id = (:id)");
    remove_session.addBindValue(id);

    if (remove_session.exec()) {
        qDebug() << "Session is deleted";
    } else {
        qDebug() << "error session is not deleted";
    }
}

bool DataBase::remove_session(QString doctor) {
    QSqlQuery remove_session;
    remove_session.prepare("DELETE FROM " TABLE_SESSIONS " "
                           "WHERE doctor_id = (:d_id)");
    remove_session.addBindValue(doctor);

    if (remove_session.exec()) {
        qDebug() << "Session is deleted";
    } else {
        qDebug() << "error session is not deleted";
    }
}

std::vector<Session> DataBase::sessions() {
    QSqlQuery pull_sessions;
    std::vector<Session> sessions;
    pull_sessions.prepare("SELECT * "
                          "FROM " TABLE_SESSIONS);

    if (pull_sessions.exec()) {
        while (pull_sessions.next()) {
            sessions.push_back(Session(pull_sessions.value(0).toInt(), pull_sessions.value(1).toString(),
                                       pull_sessions.value(2).toString(), pull_sessions.value(3).toInt(),
                                       pull_sessions.value(4).toString(), pull_sessions.value(5).toString(),
                                       pull_sessions.value(6).toBool()));
        }
        qDebug() << " sessions pulled successfully from " << TABLE_SESSIONS;
    } else {
        qDebug() << "DataBase: error of pull sessions from " << TABLE_SESSIONS;
        qDebug() << pull_sessions.lastError().text();
    }

    return sessions;
}

std::vector<Session> DataBase::sessions(bool b) {
    QSqlQuery pull_sessions;
    std::vector<Session> sessions;
    pull_sessions.prepare("SELECT * "
                          "FROM " TABLE_SESSIONS " "
                          "WHERE is_busy = (:isb)");
    pull_sessions.addBindValue(b ? 1 : 0);

    if (pull_sessions.exec()) {
        while (pull_sessions.next()) {
            sessions.push_back(Session(pull_sessions.value(0).toInt(), pull_sessions.value(1).toString(),
                                       pull_sessions.value(2).toString(), pull_sessions.value(3).toInt(),
                                       pull_sessions.value(4).toString(), pull_sessions.value(5).toString(),
                                       pull_sessions.value(6).toBool()));
        }
        qDebug() << " sessions pulled successfully from " << TABLE_SESSIONS;
    } else {
        qDebug() << "DataBase: error of pull sessions from " << TABLE_SESSIONS;
        qDebug() << pull_sessions.lastError().text();
    }

    return sessions;
}

std::vector<Session> DataBase::sessions(QString login) {
    QSqlQuery pull_sessions;
    std::vector<Session> sessions;

    pull_sessions.prepare("SELECT * "
                          "FROM " TABLE_SESSIONS " "
                          "WHERE client_id = (:log)");
    pull_sessions.addBindValue(login);

    if (pull_sessions.exec()) {
        while (pull_sessions.next()) {
            sessions.push_back(Session(pull_sessions.value(0).toInt(), pull_sessions.value(1).toString(),
                                       pull_sessions.value(2).toString(), pull_sessions.value(3).toInt(),
                                       pull_sessions.value(4).toString(), pull_sessions.value(5).toString(),
                                       pull_sessions.value(6).toBool()));
        }
        qDebug() << " sessions pulled successfully from " << TABLE_SESSIONS;
    } else {
        qDebug() << "DataBase: error of pull sessions from " << TABLE_SESSIONS;
        qDebug() << pull_sessions.lastError().text();
    }

    return sessions;
}

std::vector<Session> DataBase::doctor_sessions(QString login)
{
    QSqlQuery pull_sessions;
    std::vector<Session> sessions;

    pull_sessions.prepare("SELECT * "
                          "FROM " TABLE_SESSIONS " "
                          "WHERE doctor_id = (:log)");
    pull_sessions.addBindValue(login);

    if (pull_sessions.exec()) {
        while (pull_sessions.next()) {
            sessions.push_back(Session(pull_sessions.value(0).toInt(), pull_sessions.value(1).toString(),
                                       pull_sessions.value(2).toString(), pull_sessions.value(3).toInt(),
                                       pull_sessions.value(4).toString(), pull_sessions.value(5).toString(),
                                       pull_sessions.value(6).toBool()));
        }
        qDebug() << " sessions pulled successfully from " << TABLE_SESSIONS;
    } else {
        qDebug() << "DataBase: error of pull sessions from " << TABLE_SESSIONS;
        qDebug() << pull_sessions.lastError().text();
    }

    return sessions;
}

bool DataBase::update_session(int id) {
    QSqlQuery update_session;
    update_session.prepare("UPDATE " TABLE_SESSIONS " "
                           "SET client_id = NULL, is_busy = (:isb) "
                           "WHERE id = (:id)");
    update_session.bindValue(":isb", 0);
    update_session.bindValue(":id", id);

    if (update_session.exec()) {
        qDebug() << "DataBase: session_client is updated in " << TABLE_SESSIONS;
        return true;
    } else {
        qDebug() << "DataBase: error update session_client in " << TABLE_SESSIONS;
        qDebug() << update_session.lastError().text();
        return false;
    }
}

bool DataBase::update_session(int id, QString client_id) {
    QSqlQuery update_session;
    update_session.prepare("UPDATE " TABLE_SESSIONS " "
                           "SET client_id = (:cid), is_busy = (:isb) "
                           "WHERE id = (:id)");
    update_session.bindValue(":cid", client_id);
    update_session.bindValue(":isb", 1);
    update_session.bindValue(":id", id);

    if (update_session.exec()) {
        qDebug() << "DataBase: session_client is updated in " << TABLE_SESSIONS;
        return true;
    } else {
        qDebug() << "DataBase: error update session_client in " << TABLE_SESSIONS;
        qDebug() << update_session.lastError().text();
        return false;
    }
}

bool DataBase::pull_session_is_busy(int id) {
    QSqlQuery pull_session_is_busy;
    pull_session_is_busy.prepare("SELECT is_busy "
                          "FROM " TABLE_SESSIONS " "
                          "WHERE id = (:id)");
    pull_session_is_busy.addBindValue(id);

    if (pull_session_is_busy.exec()) {
        if (pull_session_is_busy.next()) {
            return pull_session_is_busy.value(0).toBool();
        }
        qDebug() << " sessions pulled successfully from " << TABLE_SESSIONS;
    } else {
        qDebug() << "DataBase: error of pull sessions from " << TABLE_SESSIONS;
        qDebug() << pull_session_is_busy.lastError().text();
    }
}
