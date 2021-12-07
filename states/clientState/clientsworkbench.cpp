#include "clientsworkbench.h"

ClientsWorkBench::ClientsWorkBench() :
    clientsHomePageView(new ClientsHomePage()),
    clientsShopPageView(nullptr),
    clientPaymentView(nullptr),
    currentView(clientsHomePageView)
{
    currentView->show();

    QObject::connect(clientsHomePageView, &ClientsHomePage::clientWantedToShop, this, &ClientsWorkBench::clientWantsToShop);
    QObject::connect(clientsHomePageView, &ClientsHomePage::clientExitedFromHomePage, this, &ClientsWorkBench::clientExitsFromHomePage);
}

ClientsWorkBench::~ClientsWorkBench()
{
    delete clientsHomePageView;

    if (clientsShopPageView != nullptr)
    {
        delete clientsShopPageView;
    }

    if (clientPaymentView != nullptr)
    {
        delete clientPaymentView;
    }
}

void ClientsWorkBench::setThisStateAsCurrent(QList<QVariant> data)
{
    clientsHomePageView->displayClientData(data);
    currentView->show();
}

void ClientsWorkBench::clientWantsToShop()
{
    if (clientsShopPageView == nullptr)
    {
        clientsShopPageView = new ClientsShopPage();
        QObject::connect(clientsShopPageView, &ClientsShopPage::backFromClientShopWasChosen, this, &ClientsWorkBench::backFromClientShopIsChosen);
        QObject::connect(clientsShopPageView, &ClientsShopPage::clientPaymentWasChosen, this, &ClientsWorkBench::clientPaymentIsChosen);
    }

    changeView(clientsShopPageView);
}

void ClientsWorkBench::clientExitsFromHomePage()
{
    currentView->hide();
    emit stateWasFinished(Bookstore::states::entrance, {});
}

void ClientsWorkBench::clientPaymentIsChosen()
{
    if (clientPaymentView == nullptr)
    {
        clientPaymentView = new ClientPayment();
        QObject::connect(clientPaymentView, &ClientPayment::backFromClientPaymentWasChosen, this, &ClientsWorkBench::backFromClientPaymentIsChosen);
    }

    changeView(clientPaymentView);
}

void ClientsWorkBench::backFromClientShopIsChosen()
{
    clientsHomePageView->displayClientData({clientsHomePageView->getEmail()});
    changeView(clientsHomePageView);
}

void ClientsWorkBench::backFromClientPaymentIsChosen()
{
    changeView(clientsShopPageView);
}

void ClientsWorkBench::changeView(QWidget *view)
{
    currentView->hide();
    currentView = view;
    currentView->show();
}
