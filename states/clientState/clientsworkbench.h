#ifndef CLIENTSWORKBENCH_H
#define CLIENTSWORKBENCH_H

#include "clientshomepage.h"
#include "clientsshoppage.h"
#include "../state.h"

class ClientsWorkBench : public State
{
    Q_OBJECT

public:
    ClientsWorkBench();
    ~ClientsWorkBench();

    void setThisStateAsCurrent(QList<QVariant> data);

private:
    ClientsHomePage *clientsHomePageView;
    ClientsShopPage *clientsShopPageView;

    QWidget *currentView;

    void changeView(QWidget *view);
};

#endif // CLIENTSWORKBENCH_H
