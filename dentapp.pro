QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adddoctor.cpp \
    addsession.cpp \
    adminmenu.cpp \
    clickablelabel.cpp \
    clientmenu.cpp \
    database.cpp \
    doctormenu.cpp \
    main.cpp \
    entrywindow.cpp \
    registrateaccount.cpp \
    remindpassword.cpp \
    settings.cpp \
    user.cpp

HEADERS += \
    adddoctor.h \
    addsession.h \
    adminmenu.h \
    clickablelabel.h \
    clientmenu.h \
    database.h \
    doctormenu.h \
    entrywindow.h \
    registrateaccount.h \
    remindpassword.h \
    settings.h \
    user.h

FORMS += \
    adddoctor.ui \
    addsession.ui \
    adminmenu.ui \
    clientmenu.ui \
    doctormenu.ui \
    entrywindow.ui \
    registrateaccount.ui \
    remindpassword.ui \
    settings.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
