#include "clientpayment.h"
#include "ui_clientpayment.h"

ClientPayment::ClientPayment(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientPayment),
    impossiblePointId(-1),
    currentOrderId(impossiblePointId)
{
    ui->setupUi(this);

    QObject::connect(ui->pushButton, &QPushButton::clicked, this, &ClientPayment::backFromClientPaymentIsChosen);
    QObject::connect(ui->pushButton_2, &QPushButton::clicked, this, &ClientPayment::paymentIsChosen);
}

ClientPayment::~ClientPayment()
{
    delete ui;
}

void ClientPayment::setOrderId(int orderId)
{
    currentOrderId = orderId;
}

void ClientPayment::backFromClientPaymentIsChosen(bool)
{ 
    emit backFromClientPaymentWasChosen(false);
}

void ClientPayment::paymentIsChosen(bool)
{
    QString changeCurrentOrderQueryString = "UPDATE ordering SET "
                                            "orderdate = curdate(), "
                                            "ordertime = curtime(), "
                                            "orderstatus = 'На складе', "
                                            "paymentmethod = '%1', "
                                            "deliverypoint = %2 "
                                            "WHERE orderid = %3;";
    QSqlQuery changeCurrentQuery(QSqlDatabase::database("main connection"));
    if (!changeCurrentQuery.exec(changeCurrentOrderQueryString
                                 .arg(ui->comboBox->currentText())
                                 .arg(getPointId(ui->comboBox_2->currentText()))
                                 .arg(currentOrderId)))
    {
        QMessageBox::warning(nullptr, "проблема с подключением к базе данных", "ошибка запроса");
        return;
    }

    emit backFromClientPaymentWasChosen(true);
}

int ClientPayment::getPointId(QString address)
{
    QString getPointIdQueryString = "SELECT pointid FROM deliverypoint WHERE address = '%1';";

    QSqlQuery getPointIdQuery(QSqlDatabase::database("main connection"));
    if (!getPointIdQuery.exec(getPointIdQueryString.arg(address)))
    {
        QMessageBox::warning(nullptr, "проблема с подключением к базе данных", "ошибка запроса");
        return impossiblePointId;
    }

    int pointId = impossiblePointId;
    if (getPointIdQuery.next())
    {
        pointId = getPointIdQuery.value("pointid").toInt();
    }

    return pointId;
}
