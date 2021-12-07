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

QString SignIn::getEmail()
{
    return ui->lineEdit->text();
}

void SignIn::acceptButtonIsPushed(bool)
{
    QSqlQuery signInQuery(QSqlDatabase::database("main connection"));
    QString signInQueryString = "SELECT * FROM %1 WHERE (email = :email AND upassword = :upassword);";
    signInQuery.prepare(signInQueryString.arg(getTableName()));
    signInQuery.bindValue(":email", ui->lineEdit->text());
    signInQuery.bindValue(":upassword", ui->lineEdit_2->text());

    if (!signInQuery.exec())
    {
        QMessageBox::warning(nullptr, "проблема с подключением к базе данных", "ошибка запроса");
        return;
    }

    if (signInQuery.next())
    {
        emit userSignedIn();
    }
    else
    {
        QMessageBox::critical(nullptr, "ошибка авторизации", "неверный email или пароль");
        return;
    }
}

void SignIn::clientSignUpButtonIsPushed(bool)
{
    emit clientSignUpWasChosen();
}

void SignIn::backFromSignInButtonIsPushed(bool)
{
    emit backFromSignInWasChosen();
}

QString SignIn::getTableName()
{
    switch (userRole)
    {
    case Bookstore::users::client:
        return "customer";
    case Bookstore::users::storekeeper:
        return "employee";
    case Bookstore::users::dpoperator:
        return "employee";
    case Bookstore::users::administrator:
        return "administrator";
    default:
        return "";
    }
}
