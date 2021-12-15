#include "dpoperatorsworkbench.h"

DPOperatorsWorkBench::DPOperatorsWorkBench() :
    dpOperatorsHomePageView(new DPOperatorsHomePage()),
    dpView(nullptr),
    currentView(dpOperatorsHomePageView)
{
    currentView->show();

    QObject::connect(dpOperatorsHomePageView, &DPOperatorsHomePage::operatorExitedFromHomePage, this, &DPOperatorsWorkBench::operatorExitsFromHomePage);
    QObject::connect(dpOperatorsHomePageView, &DPOperatorsHomePage::operatorWantedToGoToDP, this, &DPOperatorsWorkBench::operatorWantsToGoToDP);
}

DPOperatorsWorkBench::~DPOperatorsWorkBench()
{
    delete dpOperatorsHomePageView;

    if (dpView != nullptr)
    {
        delete dpView;
    }
}

void DPOperatorsWorkBench::setThisStateAsCurrent(QList<QVariant> data)
{
    dpOperatorsHomePageView->displayDPOperatorData(data);
    currentView->show();
}

void DPOperatorsWorkBench::operatorExitsFromHomePage()
{
    currentView->hide();
    emit stateWasFinished(Bookstore::states::entrance, {});
}

void DPOperatorsWorkBench::operatorWantsToGoToDP(QString DPAddress)
{
    if (dpView == nullptr)
    {
        dpView = new DP();
        QObject::connect(dpView, &DP::backFromDPWasChosen, this, &DPOperatorsWorkBench::backFromDPIsChosen);
    }

    dpView->setDPAdress(DPAddress);
    dpView->updateOrdersTable();
    changeView(dpView);
}

void DPOperatorsWorkBench::backFromDPIsChosen()
{
    changeView(dpOperatorsHomePageView);
}

void DPOperatorsWorkBench::changeView(QWidget *view)
{
    currentView->hide();
    currentView = view;
    currentView->show();
}
