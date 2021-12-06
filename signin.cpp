#include "signin.h"
#include "ui_signin.h"

SignIn::SignIn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignIn),
    userRole(Bookstore::users::impossibleUserRole)
{
    ui->setupUi(this);

    QObject::connect(ui->pushButton, &QPushButton::clicked, this, &SignIn::acceptButtonIsPushed);
    QObject::connect(ui->pushButton_2, &QPushButton::clicked, this, &SignIn::backFromSignInButtonIsPushed);
    QObject::connect(ui->pushButton_3, &QPushButton::clicked, this, &SignIn::clientSignUpButtonIsPushed);
}

SignIn::~SignIn()
{
    delete ui;
}

void SignIn::clearView()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
}

void SignIn::setUserRole(int uRole)
{
    userRole = uRole;
}

void SignIn::acceptButtonIsPushed(bool)
{
    // !!!!!!!!!
    emit userSignedIn();
}

void SignIn::clientSignUpButtonIsPushed(bool)
{
    emit clientSignUpWasChosen();
}

void SignIn::backFromSignInButtonIsPushed(bool)
{
    emit backFromSignInWasChosen();
}
