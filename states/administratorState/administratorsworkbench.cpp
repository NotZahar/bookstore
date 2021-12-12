#include "administratorsworkbench.h"

AdministratorsWorkBench::AdministratorsWorkBench() :
    employeesSignUpView(new EmployeesSignUp()),
    currentView(employeesSignUpView)
{
    currentView->show();

    QObject::connect(employeesSignUpView, &EmployeesSignUp::administratorExitedFromEmployeesSignUp, this, &AdministratorsWorkBench::administratorExitsFromEmployeesSignUp);
}

AdministratorsWorkBench::~AdministratorsWorkBench()
{
    delete employeesSignUpView;
}

void AdministratorsWorkBench::setThisStateAsCurrent(QList<QVariant>)
{
    employeesSignUpView->updateEmployeesTable();
    currentView->show();
}

void AdministratorsWorkBench::administratorExitsFromEmployeesSignUp()
{
    currentView->hide();
    emit stateWasFinished(Bookstore::states::entrance, {});
}

void AdministratorsWorkBench::changeView(QWidget *view)
{
    currentView->hide();
    currentView = view;
    currentView->show();
}
