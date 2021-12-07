#include "clientsignup.h"
#include "ui_clientsignup.h"

ClientSignUp::ClientSignUp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientSignUp)
{
    ui->setupUi(this);

    QObject::connect(ui->pushButton, &QPushButton::clicked, this, &ClientSignUp::backFromClientSignUpButtonIsPushed);
    QObject::connect(ui->pushButton_2, &QPushButton::clicked, this, &ClientSignUp::clientSignUpButtonIsPushed);
}

ClientSignUp::~ClientSignUp()
{
    delete ui;
}

void ClientSignUp::clearView()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
    ui->lineEdit_7->clear();
}

void ClientSignUp::backFromClientSignUpButtonIsPushed(bool)
{
    clearView();
    emit backFromClientSignUpWasChosen();
}

void ClientSignUp::clientSignUpButtonIsPushed(bool)
{
    if (ui->lineEdit_6->text() != ui->lineEdit_7->text())
    {
        ui->lineEdit_6->clear();
        ui->lineEdit_7->clear();
        QMessageBox::critical(nullptr, "ошибка ввода", "пароли не совпадают");
        return;
    }

    QSqlQuery checkQuery(QSqlDatabase::database("main connection"));
    QString checkQueryString = "SELECT * FROM customer WHERE (phone = '%1' OR email = '%2');";

    if (!checkQuery.exec(checkQueryString
                         .arg(ui->lineEdit_4->text())
                         .arg(ui->lineEdit_5->text())))
    {
        QMessageBox::warning(nullptr, "проблема с подключением к базе данных", "ошибка запроса");
        return;
    }

    if (checkQuery.next())
    {
        QMessageBox::critical(nullptr, "ошибка ввода", "пользователь с такими телефоном или email уже зарегистрирован");
        return;
    }

    QSqlQuery signUpQuery(QSqlDatabase::database("main connection"));
    QString signUpQueryString = "INSERT INTO customer (surname, uname, patronymic, phone, email, upassword) "
                                "VALUES (:surname, :uname, :patronymic, :phone, :email, :upassword);";
    signUpQuery.prepare(signUpQueryString);
    signUpQuery.bindValue(":surname", (ui->lineEdit->text().isEmpty() ? QVariant(QVariant::String) : ui->lineEdit->text()));
    signUpQuery.bindValue(":uname", ui->lineEdit_2->text());
    signUpQuery.bindValue(":patronymic", (ui->lineEdit_3->text().isEmpty() ? QVariant(QVariant::String) : ui->lineEdit_3->text()));
    signUpQuery.bindValue(":phone", (ui->lineEdit_4->text().isEmpty() ? QVariant(QVariant::String) : ui->lineEdit_4->text()));
    signUpQuery.bindValue(":email", ui->lineEdit_5->text());
    signUpQuery.bindValue(":upassword", ui->lineEdit_6->text());

    if (!signUpQuery.exec())
    {
        QMessageBox::warning(nullptr, "проблема с подключением к базе данных", "ошибка запроса");
        return;
    }

    QMessageBox::information(nullptr, "регистрация нового пользователя", "новый пользователь зарегистрирован");
}
