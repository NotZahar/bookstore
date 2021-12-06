#include "entrance.h"

Entrance::Entrance() :
    userRole(Bookstore::users::impossibleUserRole),
    userChoiceView(new UserChoice()),
    signInView(nullptr),
    clientSignUpView(nullptr),
    currentView(userChoiceView)
{
    currentView->show();
    QObject::connect(userChoiceView, &UserChoice::userRoleIsChosen, this, &Entrance::userRoleIsChosen);
}

Entrance::~Entrance()
{
    delete userChoiceView;

    if (signInView != nullptr)
    {
        delete signInView;
    }

    if (clientSignUpView != nullptr)
    {
        delete clientSignUpView;
    }
}

void Entrance::setThisStateAsCurrent(QList<QVariant>)
{
    currentView = signInView;
    currentView->show();
}

void Entrance::userRoleIsChosen(int uRole)
{
    if (signInView == nullptr)
    {
        signInView = new SignIn();
        QObject::connect(signInView, &SignIn::clientSignUpWasChosen, this, &Entrance::clientSignUpIsChosen);
        QObject::connect(signInView, &SignIn::backFromSignInWasChosen, this, &Entrance::backFromSignInIsChosen);
        QObject::connect(signInView, &SignIn::userSignedIn, this, &Entrance::userSignedInSystem);
    }

    signInView->clearView();
    if (clientSignUpView != nullptr)
    {
        clientSignUpView->clearView();
    }

    userRole = uRole;
    signInView->setUserRole(userRole);

    changeView(signInView);
}

void Entrance::clientSignUpIsChosen()
{
    if (userRole == Bookstore::users::client)
    {
        if (clientSignUpView == nullptr)
        {
            clientSignUpView = new ClientSignUp();
            //QObject::connect(signUpReaderView, &SignUpReader::backFromSignUpReaderWasChosen, this, &Entrance::backFromSignUpReaderIsChosen);
        }
        changeView(clientSignUpView);
    }
}

void Entrance::backFromSignInIsChosen()
{
    changeView(userChoiceView);
}

/*void Entrance::backFromClientSignUpIsChosen()
{

}*/

void Entrance::userSignedInSystem()
{
    // !!!!!!!!!!!
}

void Entrance::changeView(QWidget *view)
{
    currentView->hide();
    currentView = view;
    currentView->show();
}
