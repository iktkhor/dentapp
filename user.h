#ifndef USER_H
#define USER_H

#include <QString>
#include <QVariant>

class User
{
public:
    enum Role {
      Client, Doctor, Admin
    };

    User();
    User(QString name, QString login, QString password, QString role);
    User(QString name, QString login, QString password, int sec_ques, QString sec_ques_answer, QString role);
    QString get_name();
    QString get_login();
    QString get_password();
    QString get_sec_ques_answer();
    QString get_role();
    int get_sec_ques();

    void set_name(QString name);
    void set_login(QString login);
    void set_password(QString password);
    void set_sec_ques_answer(QString ans);
    void set_sec_ques(int sec_ques);
    void set_role(QString r);

private:
    QString name;
    QString login;
    QString password;
    QString sec_ques_answer;
    Role role;
    int sec_ques;
};

#endif // USER_H
