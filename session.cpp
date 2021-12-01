#include "session.h"

Session::Session()
{

}

Session::Session(QString doctor_id, int cabinet, QString data, QString time) {
    set_doctor_id(doctor_id);
    set_cabinet(cabinet);
    set_data(data);
    set_time(time);
}

Session::Session(int id, QString doctor_id, QString client_id, int cabinet, QString data, QString time, bool is_busy) {
    set_id(id);
    set_doctor_id(doctor_id);
    set_client_id(client_id);
    set_cabinet(cabinet);
    set_data(data);
    set_time(time);
    set_is_busy(is_busy);
}

int Session::get_id() {
    return id;
}

QString Session::get_doctor_id() {
    return doctor_id;
}

QString Session::get_client_id() {
    return client_id;
}

QString Session::get_time() {
    return time;
}

int Session::get_cabinet() {
    return cabinet;
}

bool Session::get_is_busy() {
    return is_busy;
}

QString Session::get_data() {
    return data;
}

void Session::set_id(int id) {
    this->id = id;
}

void Session::set_doctor_id(QString doctor_id) {
    this->doctor_id = doctor_id;
}

void Session::set_client_id(QString client_id) {
    this->client_id = client_id;
}

void Session::set_time(QString time) {
    this->time = time;
}

void Session::set_cabinet(int cabinet) {
    this->cabinet = cabinet;
}

void Session::set_is_busy(bool b) {
    is_busy = b;
}

void Session::set_data(QString data) {
    this->data = data;
}
