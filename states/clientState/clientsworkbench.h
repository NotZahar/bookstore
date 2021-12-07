#ifndef CLIENTSWORKBENCH_H
#define CLIENTSWORKBENCH_H

#include "clientshomepage.h"
#include "clientsshoppage.h"
#include "clientpayment.h"
#include "../state.h"
#include "bookstore.h"

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
    void clientPaymentIsChosen();
    void backFromClientShopIsChosen();
    void backFromClientPaymentIsChosen();

private:
    ClientsHomePage *clientsHomePageView;
    ClientsShopPage *clientsShopPageView;
    ClientPayment *clientPaymentView;

    QWidget *currentView;

    void changeView(QWidget *view);
};

#endif // CLIENTSWORKBENCH_H
