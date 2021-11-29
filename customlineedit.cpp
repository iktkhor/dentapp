#include "customlineedit.h"

void CustomLineEdit::mousePressEvent(QMouseEvent *) {
    emit clicked(this);
}

