#include "clientpayment.h"
#include "ui_clientpayment.h"

ClientPayment::ClientPayment(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientPayment)
{
    ui->setupUi(this);

    QObject::connect(ui->pushButton, &QPushButton::clicked, this, &ClientPayment::backFromClientPaymentIsChosen);
}

ClientPayment::~ClientPayment()
{
    delete ui;
}

void ClientPayment::setOrderId(int orderId)
{
    currentOrderId = orderId;
}

void ClientPayment::backFromClientPaymentIsChosen(bool c)
{
    // &&&&&&&&&&
    emit backFromClientPaymentWasChosen();
}
