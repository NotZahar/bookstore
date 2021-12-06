#include "clientsignup.h"
#include "ui_clientsignup.h"

ClientSignUp::ClientSignUp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientSignUp)
{
    ui->setupUi(this);
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
