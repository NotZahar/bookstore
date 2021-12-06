#ifndef ENTRANCE_H
#define ENTRANCE_H

#include "userchoice.h"
#include "state.h"

class Entrance : public State
{
    Q_OBJECT

public:
    Entrance();
    ~Entrance();

    void setThisStateAsCurrent(QList<QVariant> data);

private slots:
    void userRoleIsChosen(int u);

private:
    int userRole;

    UserChoice* userChoiceView;

    QWidget *currentView;

    void changeView(QWidget *view);
};

#endif // ENTRANCE_H
