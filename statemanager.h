#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <QMap>
#include <QList>

#include "bookstore.h"
#include "entrance.h"

class StateManager : public QObject
{
    Q_OBJECT

public:
    StateManager() = delete;
    explicit StateManager(int initialStateId);
    ~StateManager();

    static State *createState(int stateId);

public slots:
    void stateIsFinished(int newStateId, QList<QVariant> data);

private:
    QMap<int, State *> states;
    int currentStateId;
};

#endif // STATEMANAGER_H
