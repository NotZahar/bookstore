#include "entrance.h"

Entrance::Entrance() :
    userRole(Bookstore::users::impossibleUserRole),
    userChoiceView(new UserChoice()),
    currentView(userChoiceView)
{
    currentView->show();
    QObject::connect(userChoiceView, &UserChoice::userRoleIsChosen, this, &Entrance::userRoleIsChosen);
}

Entrance::~Entrance()
{
    delete userChoiceView;
}

void Entrance::setThisStateAsCurrent(QList<QVariant>)
{
    currentView = userChoiceView;
    currentView->show();
}

void Entrance::userRoleIsChosen(int)
{

}

void Entrance::changeView(QWidget *view)
{
    currentView->hide();
    currentView = view;
    currentView->show();
}
