#ifndef SESSION_H
#define SESSION_H

#include <QString>
#include <QDateTime>

class Session
{
public:
    Session();
    Session(QString doctor_id, int cabinet, QString data, QString time);
    Session(int id, QString doctor_id, QString client_id, int cabinet, QString data, QString time, bool is_busy);

    int get_id();
    QString get_doctor_id();
    QString get_client_id();
    QString get_data();
    QString get_time();
    int get_cabinet();
    bool get_is_busy();

    void set_id(int id);
    void set_doctor_id(QString doctor_id);
    void set_client_id(QString client_id);
    void set_data(QString data);
    void set_time(QString time);
    void set_cabinet(int cabinet);
    void set_is_busy(bool b);

private:
    int id;
    QString doctor_id;
    QString client_id;
    QString data;
    QString time;
    int cabinet;
    bool is_busy;

};

#endif // SESSION_H
