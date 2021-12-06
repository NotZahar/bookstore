#include "entrance.h"

Entrance::Entrance() :
    userRole(Bookstore::users::impossibleUserRole),
    userChoiceView(new UserChoice()),
    signInView(nullptr),
    signUpReaderView(nullptr),
    currentView(userChoiceView)
{
    currentView->show();
    QObject::connect(userChoiceView, &UserChoice::userRoleIsChosen, this, &Entrance::userRoleIsChosen);
}

Entrance::~Entrance()
{
    if (userChoiceView != nullptr)
    {
        delete userChoiceView;
    }

    if (signInView != nullptr)
    {
        delete signInView;
    }

    if (signUpReaderView != nullptr)
    {
        delete signUpReaderView;
    }
}

void Entrance::setThisStateAsCurrent(QList<QVariant>)
{
    currentView = signInView;
    currentView->show();
}

void Entrance::userRoleIsChosen(int u)
{
    if (signInView == nullptr)
    {
        signInView = new SignIn();
        QObject::connect(signInView, &SignIn::signUpReaderWasChosen, this, &Entrance::signUpReaderIsChosen);
        QObject::connect(signInView, &SignIn::backFromSignInWasChosen, this, &Entrance::backFromSignInIsChosen);
        QObject::connect(signInView, &SignIn::userSignedIn, this, &Entrance::userSignedInSystem);
    }

    signInView->clearView();
    if (signUpReaderView != nullptr)
    {
        signUpReaderView->clearView();
    }

    userRole = u;
    signInView->setUserRole(userRole);

    changeView(signInView);
}

void Entrance::signUpReaderIsChosen()
{
    if (signUpReaderView == nullptr)
    {
        signUpReaderView = new SignUpReader();
        QObject::connect(signUpReaderView, &SignUpReader::backFromSignUpReaderWasChosen, this, &Entrance::backFromSignUpReaderIsChosen);
    }

    if (userRole == Library::users::reader)
    {
        changeView(signUpReaderView);
    }
}

void Entrance::backFromSignInIsChosen()
{
    changeView(userChoiceView);
}

void Entrance::backFromSignUpReaderIsChosen()
{
    changeView(signInView);
}

void Entrance::userSignedInSystem()
{
    currentView->hide();
    switch (userRole)
    {
    case Library::users::reader:
    {
        emit stateWasFinished(Library::states::readersWorkBench, {signInView->getLogin()});
        break;
    }
    case Library::users::librarian:
    {
        emit stateWasFinished(Library::states::librariansWorkBench, {signInView->getLogin()});
        break;
    }
    case Library::users::administrator:
    {
        emit stateWasFinished(Library::states::administratorsWorkBench, {});
        break;
    }
    default: { break; }
    }
}

void Entrance::changeView(QWidget *view)
{
    currentView->hide();
    currentView = view;
    currentView->show();
}
