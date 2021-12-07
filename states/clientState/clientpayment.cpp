#include "clientpayment.h"
#include "ui_clientpayment.h"

ClientPayment::ClientPayment(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientPayment)
{
    ui->setupUi(this);
}

ClientPayment::~ClientPayment()
{
    delete ui;
}
