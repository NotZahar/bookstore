#ifndef ENTRANCE_H
#define ENTRANCE_H

#include "state.h"

class Entrance : public State
{
    Q_OBJECT

public:
    Entrance();
    ~Entrance();

    void setThisStateAsCurrent(QList<QVariant> data);

private slots:

private:
    int userRole;

    QWidget *currentView;

    void changeView(QWidget *view);
};

#endif // ENTRANCE_H
