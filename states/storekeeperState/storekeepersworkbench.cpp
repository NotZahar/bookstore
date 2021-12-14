#include "storekeepersworkbench.h"

StoreKeepersWorkBench::StoreKeepersWorkBench() :
    storeKeepersHomePageView(new StoreKeepersHomePage()),
    booksView(nullptr),
    warehouseView(nullptr),
    currentView(storeKeepersHomePageView)
{
    currentView->show();

    QObject::connect(storeKeepersHomePageView, &StoreKeepersHomePage::storeKeeperExitedFromHomePage, this, &StoreKeepersWorkBench::storeKeeperExitsFromHomePage);
    QObject::connect(storeKeepersHomePageView, &StoreKeepersHomePage::goToWarehouseButtonWasPushed, this, &StoreKeepersWorkBench::storeKeeperWantsToGoToWarehouse);
    QObject::connect(storeKeepersHomePageView, &StoreKeepersHomePage::goToBooksButtonWasPushed, this, &StoreKeepersWorkBench::storeKeeperWantsToGoToBooks);
}

StoreKeepersWorkBench::~StoreKeepersWorkBench()
{
    delete storeKeepersHomePageView;

    if (booksView != nullptr)
    {
        delete booksView;
    }

    if (warehouseView != nullptr)
    {
        delete warehouseView;
    }
}

void StoreKeepersWorkBench::setThisStateAsCurrent(QList<QVariant> data)
{
    storeKeepersHomePageView->displayEmployeeData(data);
    currentView->show();
}

void StoreKeepersWorkBench::storeKeeperExitsFromHomePage()
{
    currentView->hide();
    emit stateWasFinished(Bookstore::states::entrance, {});
}

void StoreKeepersWorkBench::storeKeeperWantsToGoToWarehouse()
{
    if (warehouseView == nullptr)
    {
        warehouseView = new SKWarehouse();
        QObject::connect(warehouseView, &SKWarehouse::backFromWarehouseButtonWasPushed, this, &StoreKeepersWorkBench::backFromSKWarehouseIsChosen);
    }

    warehouseView->updateWarehouseTable();
    warehouseView->updateCartTable();
    changeView(warehouseView);
}

void StoreKeepersWorkBench::storeKeeperWantsToGoToBooks()
{
    if (booksView == nullptr)
    {
        booksView = new StoreKeepersBooks();
        QObject::connect(booksView, &StoreKeepersBooks::backFromBooksButtonWasPushed, this, &StoreKeepersWorkBench::backFromSKBooksIsChosen);
    }

    booksView->updateBooksTable();
    changeView(booksView);
}

void StoreKeepersWorkBench::backFromSKWarehouseIsChosen()
{
    changeView(storeKeepersHomePageView);
}

void StoreKeepersWorkBench::backFromSKBooksIsChosen()
{
    changeView(storeKeepersHomePageView);
}

void StoreKeepersWorkBench::changeView(QWidget *view)
{
    currentView->hide();
    currentView = view;
    currentView->show();
}
