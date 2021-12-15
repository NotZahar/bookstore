#ifndef DPOPERATORSWORKBENCH_H
#define DPOPERATORSWORKBENCH_H

#include "dp.h"
#include "dpoperatorshomepage.h"
#include "../state.h"
#include "../../bookstore.h"

class DPOperatorsWorkBench : public State
{
    Q_OBJECT

public:
    DPOperatorsWorkBench();
    ~DPOperatorsWorkBench();

    void setThisStateAsCurrent(QList<QVariant> data);

private slots:
    void operatorExitsFromHomePage();
    void operatorWantsToGoToDP(QString DPAdress);
    void backFromDPIsChosen();

private:
    void changeView(QWidget *view);

private:
    DPOperatorsHomePage *dpOperatorsHomePageView;
    DP *dpView;

    QWidget *currentView;
};

#endif // DPOPERATORSWORKBENCH_H
