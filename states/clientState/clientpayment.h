#ifndef CLIENTPAYMENT_H
#define CLIENTPAYMENT_H

#include <QWidget>
#include <QSql>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>

namespace Ui {
class ClientPayment;
}

class ClientPayment : public QWidget
{
    Q_OBJECT

public:
    explicit ClientPayment(QWidget *parent = nullptr);
    ~ClientPayment();

    void setOrderId(int orderId);

signals:
    void backFromClientPaymentWasChosen(bool orderWasPaidFor);

private slots:
    void backFromClientPaymentIsChosen(bool c);
    void paymentIsChosen(bool c);

private:
    int getPointId(QString address);

private:
    Ui::ClientPayment *ui;

    const int impossiblePointId;
    int currentOrderId;
};

#endif // CLIENTPAYMENT_H
