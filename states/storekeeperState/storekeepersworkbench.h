#ifndef STOREKEEPERSWORKBENCH_H
#define STOREKEEPERSWORKBENCH_H

#include "storekeepershomepage.h"
#include "storekeepersbooks.h"
#include "skwarehouse.h"
#include "../state.h"
#include "../../bookstore.h"

class StoreKeepersWorkBench : public State
{
    Q_OBJECT

public:
    StoreKeepersWorkBench();
    ~StoreKeepersWorkBench();

    void setThisStateAsCurrent(QList<QVariant> data);

private slots:
    void storeKeeperExitsFromHomePage();
    void storeKeeperWantsToGoToWarehouse();
    void storeKeeperWantsToGoToBooks();
    void backFromSKWarehouseIsChosen();
    void backFromSKBooksIsChosen();

private:
    void changeView(QWidget *view);

private:
    StoreKeepersHomePage *storeKeepersHomePageView;
    StoreKeepersBooks *booksView;
    SKWarehouse *warehouseView;

    QWidget *currentView;
};

#endif // STOREKEEPERSWORKBENCH_H
