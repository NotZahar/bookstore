#ifndef ENTRANCE_H
#define ENTRANCE_H

#include "userchoice.h"
#include "signin.h"
#include "clientsignup.h"
#include "../state.h"

class Entrance : public State
{
    Q_OBJECT

public:
    Entrance();
    ~Entrance();

    void setThisStateAsCurrent(QList<QVariant> data);

private slots:
    void userRoleIsChosen(int userRole);
    void clientSignUpIsChosen();
    void backFromSignInIsChosen();
    void backFromClientSignUpIsChosen();
    void userSignedInSystem();

private:
    void changeView(QWidget *view);

private:
    int userRole;

    UserChoice *userChoiceView;
    SignIn *signInView;
    ClientSignUp *clientSignUpView;

    QWidget *currentView;
};

#endif // ENTRANCE_H
