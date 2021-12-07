QT       += core gui sql

RC_FILE += resources.rc

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

SOURCES += \
    main.cpp \
    states/clientState/clientpayment.cpp \
    states/clientState/clientshomepage.cpp \
    states/clientState/clientsshoppage.cpp \
    states/clientState/clientsworkbench.cpp \
    states/entranceState/clientsignup.cpp \
    states/entranceState/entrance.cpp \
    states/entranceState/signin.cpp \
    states/entranceState/userchoice.cpp \
    states/state.cpp \
    states/statemanager.cpp \

HEADERS += \
    bookstore.h \
    states/clientState/clientpayment.h \
    states/clientState/clientshomepage.h \
    states/clientState/clientsshoppage.h \
    states/clientState/clientsworkbench.h \
    states/entranceState/clientsignup.h \
    states/entranceState/entrance.h \
    states/entranceState/signin.h \
    states/entranceState/userchoice.h \
    states/state.h \
    states/statemanager.h \

FORMS += \
    states/clientState/clientpayment.ui \
    states/clientState/clientshomepage.ui \
    states/clientState/clientsshoppage.ui \
    states/entranceState/clientsignup.ui \
    states/entranceState/signin.ui \
    states/entranceState/userchoice.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    images/mainicon.ico
