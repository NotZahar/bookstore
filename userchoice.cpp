#include "userchoice.h"
#include "ui_userchoice.h"

UserChoice::UserChoice(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserChoice)
{
    ui->setupUi(this);

    QObject::connect(ui->pushButton, &QPushButton::clicked, this, &UserChoice::clientRoleIsChosen);
    QObject::connect(ui->pushButton_2, &QPushButton::clicked, this, &UserChoice::storekeeperRoleIsChosen);
    QObject::connect(ui->pushButton_3, &QPushButton::clicked, this, &UserChoice::dpoperatorRoleIsChosen);
    QObject::connect(ui->pushButton_4, &QPushButton::clicked, this, &UserChoice::administratorRoleIsChosen);
}

UserChoice::~UserChoice()
{
    delete ui;
}

void UserChoice::administratorRoleIsChosen(bool)
{
    emit userRoleIsChosen(Bookstore::users::administrator);
}

void UserChoice::dpoperatorRoleIsChosen(bool)
{
    emit userRoleIsChosen(Bookstore::users::dpoperator);
}

void UserChoice::storekeeperRoleIsChosen(bool)
{
    emit userRoleIsChosen(Bookstore::users::storekeeper);
}

void UserChoice::clientRoleIsChosen(bool)
{
    emit userRoleIsChosen(Bookstore::users::client);
}
