#include "clientsworkbench.h"

ClientsWorkBench::ClientsWorkBench() :
    clientsHomePageView(new ClientsHomePage()),
    clientsShopPageView(nullptr),
    currentView(clientsHomePageView)
{
    currentView->show();

    //QObject::connect(readerHomePageView, &ReaderHomePage::readerWantedToLibrary, this, &ReadersWorkBench::readerWantsToLibrary);
    //QObject::connect(readerHomePageView, &ReaderHomePage::readerExitedFromHomePage, this, &ReadersWorkBench::readerExitFromHomePage);
}

ClientsWorkBench::~ClientsWorkBench()
{
    delete clientsHomePageView;

    if (clientsShopPageView != nullptr)
    {
        delete clientsShopPageView;
    }
}


