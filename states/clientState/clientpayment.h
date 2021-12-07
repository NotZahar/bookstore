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

private:
    Ui::ClientPayment *ui;
};

#endif // CLIENTPAYMENT_H
