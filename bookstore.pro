QT       += core gui sql

RC_FILE += resources.rc

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

SOURCES += \
    main.cpp \
    states/administratorState/administratorsworkbench.cpp \
    states/administratorState/employeessignup.cpp \
    states/clientState/clientpayment.cpp \
    states/clientState/clientshomepage.cpp \
    states/clientState/clientsshoppage.cpp \
    states/clientState/clientsworkbench.cpp \
    states/dpoperatorState/dp.cpp \
    states/dpoperatorState/dpoperatorshomepage.cpp \
    states/dpoperatorState/dpoperatorsworkbench.cpp \
    states/entranceState/clientsignup.cpp \
    states/entranceState/entrance.cpp \
    states/entranceState/signin.cpp \
    states/entranceState/userchoice.cpp \
    states/state.cpp \
    states/statemanager.cpp \
    states/storekeeperState/skwarehouse.cpp \
    states/storekeeperState/storekeepersbooks.cpp \
    states/storekeeperState/storekeepershomepage.cpp \
    states/storekeeperState/storekeepersworkbench.cpp

HEADERS += \
    bookstore.h \
    states/administratorState/administratorsworkbench.h \
    states/administratorState/employeessignup.h \
    states/clientState/clientpayment.h \
    states/clientState/clientshomepage.h \
    states/clientState/clientsshoppage.h \
    states/clientState/clientsworkbench.h \
    states/dpoperatorState/dp.h \
    states/dpoperatorState/dpoperatorshomepage.h \
    states/dpoperatorState/dpoperatorsworkbench.h \
    states/entranceState/clientsignup.h \
    states/entranceState/entrance.h \
    states/entranceState/signin.h \
    states/entranceState/userchoice.h \
    states/state.h \
    states/statemanager.h \
    states/storekeeperState/skwarehouse.h \
    states/storekeeperState/storekeepersbooks.h \
    states/storekeeperState/storekeepershomepage.h \
    states/storekeeperState/storekeepersworkbench.h

FORMS += \
    states/administratorState/employeessignup.ui \
    states/clientState/clientpayment.ui \
    states/clientState/clientshomepage.ui \
    states/clientState/clientsshoppage.ui \
    states/dpoperatorState/dp.ui \
    states/dpoperatorState/dpoperatorshomepage.ui \
    states/entranceState/clientsignup.ui \
    states/entranceState/signin.ui \
    states/entranceState/userchoice.ui \
    states/storekeeperState/skwarehouse.ui \
    states/storekeeperState/storekeepersbooks.ui \
    states/storekeeperState/storekeepershomepage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    images/mainicon.ico
