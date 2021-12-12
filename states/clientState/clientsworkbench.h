#ifndef CLIENTSWORKBENCH_H
#define CLIENTSWORKBENCH_H

#include "clientshomepage.h"
#include "clientsshoppage.h"
#include "clientpayment.h"
#include "../state.h"
#include "../../bookstore.h"

class ClientsWorkBench : public State
{
    Q_OBJECT

public:
    ClientsWorkBench();
    ~ClientsWorkBench();

    void setThisStateAsCurrent(QList<QVariant> data);

private slots:
    void clientWantsToShop();
    void clientExitsFromHomePage();
    void orderIsMade(int orderId);
    void backFromClientShopIsChosen();
    void backFromClientPaymentIsChosen(bool orderWasPaidFor);

private:
    void changeView(QWidget *view);

private:
    ClientsHomePage *clientsHomePageView;
    ClientsShopPage *clientsShopPageView;
    ClientPayment *clientPaymentView;

    QWidget *currentView;
};

#endif // CLIENTSWORKBENCH_H
