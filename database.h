#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QFile>
#include <QDebug>
#include <QCoreApplication>
#include <iostream>
#include <vector>

#include "user.h"
#include "session.h"

#define DATABASE_NAME           "dentapp.sqlite3"
#define TABLE_USER              "Users"
#define TABLE_SECRET_QUESTIONS  "SecretQuestions"
#define TABLE_SESSIONS          "Sessions"

class DataBase
{
public:
    DataBase();
    void connect_to_database();
    bool registrate_user(User *new_user);
    bool registrate_doctor(User *new_doc);
    bool is_login_exist(QString login);
    bool is_authorize_data_right(QString login, QString password);
    bool is_secret_answer_right(QString login, QString answer);

    std::vector<User> users();
    std::vector<User> users(QString role);
    User* pull_user(QString login);
    QString pull_user_name(QString login);
    QString pull_user_password(QString login);
    QString pull_user_role(QString login);
    int pull_user_question(QString login);

    bool remove_user(QString login);
    bool update_user_login(QString login, QString new_login);
    bool update_user_name(QString login, QString new_name);
    bool update_user_password(QString login, QString new_pass);
    bool update_user_secret_question(QString login, int ind);
    bool update_user_secret_question_answer(QString login, QString answer);
    bool update_user_role(QString login, QString role);

    QList<QString> questions();
    QString pull_question(int index);

    bool add_session(Session* new_session);
    bool update_session(int id);
    bool update_session(int id, QString client_id);
    bool remove_session(int id);
    bool remove_session(QString doctor);
    std::vector<Session> sessions();
    std::vector<Session> sessions(bool b);
    std::vector<Session> sessions(QString login);
    Session* pull_session(int id);
    bool pull_session_is_busy(int id);
private:
    QSqlDatabase db;

private:
    bool open_database();
    bool restore_database();
    bool create_tables();
    bool create_user_table();
    bool create_secret_question_table();
    bool create_sessions_table();
    bool add_questions();
    bool add_admin();
    void close_database();
};

#endif // DATABASE_H
