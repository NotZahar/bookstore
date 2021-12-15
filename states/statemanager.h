#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <QMap>
#include <QList>

#include "../bookstore.h"
#include "./states/entranceState/entrance.h"
#include "./states/clientState/clientsworkbench.h"
#include "./states/storekeeperState/storekeepersworkbench.h"
#include "./states/dpoperatorState/dpoperatorsworkbench.h"
#include "./states/administratorState/administratorsworkbench.h"

class StateManager : public QObject
{
    Q_OBJECT

public:
    StateManager() = delete;
    explicit StateManager(int initialStateId);
    ~StateManager();

private slots:
    void stateIsFinished(int newStateId, QList<QVariant> data);

private:
    static State *createState(int stateId);

private:
    QMap<int, State *> states;
    int currentStateId;
};

#endif // STATEMANAGER_H
