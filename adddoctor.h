#ifndef ADDDOCTOR_H
#define ADDDOCTOR_H

#include <QDialog>
#include <QMessageBox>

#include "user.h"
#include "database.h"

namespace Ui {
class AddDoctor;
}

class AddDoctor : public QDialog
{
    Q_OBJECT

public:
    explicit AddDoctor(QWidget *parent = nullptr);
    ~AddDoctor();

signals:
    void update();

private slots:
    void on_add_clicked();

    void on_back_clicked();

private:
    Ui::AddDoctor *ui;
    DataBase db;

    void clear_ui();
    bool check_fields();
};

#endif // ADDDOCTOR_H
