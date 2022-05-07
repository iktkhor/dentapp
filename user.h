#ifndef USER_H
#define USER_H

#include <QString>

/*!
* \brief Класс для отображения стуктуры User
*/
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
    int get_session_id();

    void set_name(QString name);
    void set_login(QString login);
    void set_password(QString password);
    void set_sec_ques_answer(QString ans);
    void set_sec_ques(int sec_ques);
    void set_role(QString r);
    void set_session_id(int session_id);

private:
    QString name;
    QString login;
    QString password;
    QString sec_ques_answer;
    Role role;
    int sec_ques;
    int session_id;
};

#endif // USER_H
