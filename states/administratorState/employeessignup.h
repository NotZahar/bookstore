#ifndef EMPLOYEESSIGNUP_H
#define EMPLOYEESSIGNUP_H

#include <QWidget>
#include <QSql>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QStringList>
#include <vector>
#include <utility>

#include "../../bookstore.h"

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

public slots:
    void updateEmployeesTable();

private slots:
    void administratorExitsFromSystemButtonIsPushed(bool c);
    void insertButtonIsPushed(bool c);
    void deleteIsStarted(bool c);
    void searchIsStarted(bool c);

private:
    Ui::EmployeesSignUp *ui;

    QSqlTableModel *employeesAccountsModel;
    const std::vector<std::pair<QString, QString>> employeeTableColumnNames;
};

#endif // EMPLOYEESSIGNUP_H
