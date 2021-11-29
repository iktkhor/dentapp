#ifndef DOCTORMENU_H
#define DOCTORMENU_H

#include <QMainWindow>

namespace Ui {
class DoctorMenu;
}

class DoctorMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit DoctorMenu(QWidget *parent = nullptr);
    ~DoctorMenu();

signals:
    void entryWindow();

private slots:
    void on_exit_clicked();

private:
    Ui::DoctorMenu *ui;
};

#endif // DOCTORMENU_H
