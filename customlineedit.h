#ifndef CUSTOMLINEEDIT_H
#define CUSTOMLINEEDIT_H

#include <QLineEdit>
#include <QFocusEvent>

class CustomLineEdit : public QLineEdit
{
public:
    CustomLineEdit(QWidget *parent=0): QLineEdit(parent){};
signals:
    void clicked(CustomLineEdit* click);
protected:
    void mousePressEvent(QMouseEvent*);
};

#endif // CUSTOMLINEEDIT_H
