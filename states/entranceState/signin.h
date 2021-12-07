#ifndef SIGNIN_H
#define SIGNIN_H

#include <QWidget>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>

#include "../../bookstore.h"

namespace Ui {
class SignIn;
}

class SignIn : public QWidget
{
    Q_OBJECT

public:
    explicit SignIn(QWidget *parent = nullptr);
    ~SignIn();

    void clearView();
    void setUserRole(int uRole);
    QString getEmail();

signals:
    void clientSignUpWasChosen();
    void backFromSignInWasChosen();
    void userSignedIn();

private slots:
    void acceptButtonIsPushed(bool c);
    void clientSignUpButtonIsPushed(bool c);
    void backFromSignInButtonIsPushed(bool c);

private:
    Ui::SignIn *ui;

    int userRole;

    QString getTableName();
};

#endif // SIGNIN_H
