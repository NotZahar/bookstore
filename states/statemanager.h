#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <QMap>
#include <QList>

#include "../bookstore.h"
#include "./states/entranceState/entrance.h"
#include "./states/clientState/clientsworkbench.h"
#include "./states/storekeeperState/storekeepersworkbench.h"
#include "./states/administratorState/administratorsworkbench.h"

class StateManager : public QObject
{
    Q_OBJECT

public:
    StateManager() = delete;
    explicit StateManager(int initialStateId);
    ~StateManager();

    static State *createState(int stateId);

private slots:
    void stateIsFinished(int newStateId, QList<QVariant> data);

private:
    QMap<int, State *> states;
    int currentStateId;
};

#endif // STATEMANAGER_H
