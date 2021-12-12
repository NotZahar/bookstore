#ifndef EMPLOYEESSIGNUP_H
#define EMPLOYEESSIGNUP_H

#include <QWidget>

namespace Ui {
class EmployeesSignUp;
}

class EmployeesSignUp : public QWidget
{
    Q_OBJECT

public:
    explicit EmployeesSignUp(QWidget *parent = nullptr);
    ~EmployeesSignUp();

signals:
    void administratorExitedFromEmployeesSignUp();

private slots:
    void administratorExitsFromSystemButtonIsPushed(bool c);

private:
    Ui::EmployeesSignUp *ui;
};

#endif // EMPLOYEESSIGNUP_H
