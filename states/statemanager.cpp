#include "statemanager.h"

StateManager::StateManager(int initialStateId) : states(), currentStateId(initialStateId)
{
    states.insert(currentStateId, createState(currentStateId));
    QObject::connect(states[currentStateId], &State::stateWasFinished, this, &StateManager::stateIsFinished);
}

StateManager::~StateManager()
{
    for (auto it = states.begin(); it != states.end(); ++it)
    {
        delete it.value();
    }
}

State *StateManager::createState(int stateId)
{
    switch (stateId)
    {
    case Bookstore::states::entrance:
        return new Entrance();
    case Bookstore::states::clientsWorkBench:
        return new ClientsWorkBench();
    default:
        return nullptr;
    }
}

void StateManager::stateIsFinished(int newStateId, QList<QVariant> data)
{
    currentStateId = newStateId;
    auto it = states.find(newStateId);
    if (it != states.end())
    {
        it.value()->setThisStateAsCurrent(data);
    }
    else
    {
        states.insert(currentStateId, createState(currentStateId));
        QObject::connect(states[currentStateId], &State::stateWasFinished, this, &StateManager::stateIsFinished);
        states[currentStateId]->setThisStateAsCurrent(data);
    }
}

