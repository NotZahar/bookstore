#ifndef CLIENTPAYMENT_H
#define CLIENTPAYMENT_H

#include <QWidget>

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
    void backFromClientPaymentWasChosen();

private slots:
    void backFromClientPaymentIsChosen(bool c);

private:
    Ui::ClientPayment *ui;

    int currentOrderId;
};

#endif // CLIENTPAYMENT_H
