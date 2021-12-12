#include "employeessignup.h"
#include "ui_employeessignup.h"

EmployeesSignUp::EmployeesSignUp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EmployeesSignUp)
{
    ui->setupUi(this);

    QObject::connect(ui->pushButton_2, &QPushButton::clicked, this, &EmployeesSignUp::administratorExitsFromSystemButtonIsPushed);
}

EmployeesSignUp::~EmployeesSignUp()
{
    delete ui;
}

void EmployeesSignUp::administratorExitsFromSystemButtonIsPushed(bool)
{
    emit administratorExitedFromEmployeesSignUp();
}
