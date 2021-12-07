#ifndef STATE_H
#define STATE_H

#include <QObject>
#include <QList>
#include <QVariant>

class State : public QObject
{
    Q_OBJECT

public:
    ~State() = default;

    virtual void setThisStateAsCurrent(QList<QVariant> data) = 0;

signals:
    void stateWasFinished(int newStateId, QList<QVariant> data);

protected:
    State() = default;
};

#endif // STATE_H
