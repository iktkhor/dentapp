#ifndef ADDSESSION_H
#define ADDSESSION_H

#include <QDialog>
#include "database.h"

namespace Ui {
class AddSession;
}

class AddSession : public QDialog
{
    Q_OBJECT

public:
    explicit AddSession(QWidget *parent = nullptr);
    ~AddSession();

private slots:
    void on_add_clicked();

    void on_back_clicked();

private:
    Ui::AddSession *ui;
    DataBase db;

    void clear_ui();
    bool check_fields();
};

#endif // ADDSESSION_H
