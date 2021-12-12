#ifndef ADMINISTRATORSWORKBENCH_H
#define ADMINISTRATORSWORKBENCH_H

#include "employeessignup.h"
#include "../state.h"
#include "../../bookstore.h"

class AdministratorsWorkBench : public State
{
    Q_OBJECT

public:
    AdministratorsWorkBench();
    ~AdministratorsWorkBench();

    void setThisStateAsCurrent(QList<QVariant> data);

private slots:
    void administratorExitsFromEmployeesSignUp();

private:
    EmployeesSignUp *employeesSignUpView;

    QWidget *currentView;

    void changeView(QWidget *view);
};

#endif // ADMINISTRATORSWORKBENCH_H
