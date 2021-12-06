#ifndef USERCHOICE_H
#define USERCHOICE_H

#include <QWidget>

#include "bookstore.h"

namespace Ui {
class UserChoice;
}

class UserChoice : public QWidget
{
    Q_OBJECT

public:
    explicit UserChoice(QWidget *parent = nullptr);
    ~UserChoice();

signals:
    void userRoleIsChosen(int u);

private slots:
    void administratorRoleIsChosen(bool c);
    void dpoperatorRoleIsChosen(bool c);
    void storekeeperRoleIsChosen(bool c);
    void clientRoleIsChosen(bool c);

private:
    Ui::UserChoice *ui;
};

#endif // USERCHOICE_H
