#ifndef CLIENTSIGNUP_H
#define CLIENTSIGNUP_H

#include <QWidget>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>

#include "../../bookstore.h"

namespace Ui {
class ClientSignUp;
}

class ClientSignUp : public QWidget
{
    Q_OBJECT

public:
    explicit ClientSignUp(QWidget *parent = nullptr);
    ~ClientSignUp();

    void clearView();

signals:
    void backFromClientSignUpWasChosen();

private slots:
    void backFromClientSignUpButtonIsPushed(bool c);
    void clientSignUpButtonIsPushed(bool c);

private:
    Ui::ClientSignUp *ui;
};

#endif // CLIENTSIGNUP_H
