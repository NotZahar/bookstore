#include "employeessignup.h"
#include "ui_employeessignup.h"

EmployeesSignUp::EmployeesSignUp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EmployeesSignUp),
    employeesAccountsModel(nullptr),
    employeeTableColumnNames{{"код сотрудника", "employeeid"},
                             {"код отдела", "department"},
                             {"должность", "appointment"},
                             {"фамилия", "surname"},
                             {"имя", "uname"},
                             {"отчество", "patronymic"},
                             {"дата рождения", "birthdate"},
                             {"домашний адрес", "homeaddress"},
                             {"номер телефона", "phone"},
                             {"email", "email"},
                             {"пароль", "upassword"},
                             {"примечания", "note"}}
{
    ui->setupUi(this);

    QObject::connect(ui->pushButton, &QPushButton::clicked, this, &EmployeesSignUp::deleteIsStarted);
    QObject::connect(ui->pushButton_2, &QPushButton::clicked, this, &EmployeesSignUp::administratorExitsFromSystemButtonIsPushed);
    QObject::connect(ui->pushButton_3, &QPushButton::clicked, this, &EmployeesSignUp::searchIsStarted);
    QObject::connect(ui->pushButton_4, &QPushButton::clicked, this, &EmployeesSignUp::insertButtonIsPushed);

    // initialize and select
    employeesAccountsModel = new QSqlTableModel(this, QSqlDatabase::database("main connection"));
    employeesAccountsModel->setTable("employee");

    for (int i = 0, j = 0; i < employeesAccountsModel->columnCount(); ++i, ++j)
    {
        employeesAccountsModel->setHeaderData(i, Qt::Horizontal, employeeTableColumnNames[j].first);
    }

    employeesAccountsModel->setSort(0, Qt::AscendingOrder);
    employeesAccountsModel->setEditStrategy(QSqlTableModel::OnFieldChange);

    if (!employeesAccountsModel->select())
    {
        QMessageBox::warning(nullptr, "не получилось обратиться к базе данных", employeesAccountsModel->lastError().text());
        return;
    }

    ui->tableView->setModel(employeesAccountsModel);
    ui->tableView->repaint();
}

EmployeesSignUp::~EmployeesSignUp()
{
    delete ui;
}

void EmployeesSignUp::updateEmployeesTable()
{
    if (!employeesAccountsModel->select())
    {
        QMessageBox::warning(nullptr, "не получилось обратиться к базе данных", employeesAccountsModel->lastError().text());
        return;
    }

    ui->tableView->repaint();
}

void EmployeesSignUp::administratorExitsFromSystemButtonIsPushed(bool)
{
    emit administratorExitedFromEmployeesSignUp();
}

void EmployeesSignUp::insertButtonIsPushed(bool)
{
    QString insertEmployeeQueryString = "INSERT INTO employee (employeeid, "
                                        "department, appointment, surname, "
                                        "uname, patronymic, birthdate, "
                                        "homeaddress, phone, email, "
                                        "upassword, note) "
                                        "VALUES (%1, %2, '%3', '%4', '%5', '%6', "
                                        "'%7', '%8', '%9', '%10', '%11', '%12');";
    QSqlQuery insertEmployeeQuery(QSqlDatabase::database("main connection"));
    if (!insertEmployeeQuery.exec(insertEmployeeQueryString
                                  .arg(ui->lineEdit->text())
                                  .arg(ui->lineEdit_2->text())
                                  .arg(ui->lineEdit_3->text())
                                  .arg(ui->lineEdit_4->text())
                                  .arg(ui->lineEdit_5->text())
                                  .arg(ui->lineEdit_6->text())
                                  .arg(ui->lineEdit_7->text())
                                  .arg(ui->lineEdit_8->text())
                                  .arg(ui->lineEdit_9->text())
                                  .arg(ui->lineEdit_10->text())
                                  .arg(ui->lineEdit_11->text())
                                  .arg(ui->lineEdit_12->text())))
    {
        QMessageBox::warning(nullptr, "проблема с подключением к базе данных", "ошибка запроса");
        return;
    }

    updateEmployeesTable();
}

void EmployeesSignUp::deleteIsStarted(bool)
{
    int deleteCount = employeesAccountsModel->rowCount();
    for (int i = 0; i < deleteCount; ++i)
    {
        employeesAccountsModel->removeRows(0, 1);

        if (!employeesAccountsModel->submitAll())
        {
            QMessageBox::warning(nullptr, "ошибка при работе с базой данных", employeesAccountsModel->lastError().text());
            return;
        }

        employeesAccountsModel->select();
    }

    ui->tableView->repaint();
}

void EmployeesSignUp::searchIsStarted(bool)
{
    employeesAccountsModel->setFilter(ui->comboBox->currentText() == "все" ?
                                          QString("employeeid LIKE '%%1%' OR "
                                          "department LIKE '%%1%' OR "
                                          "appointment LIKE '%%1%' OR "
                                          "surname LIKE '%%1%' OR "
                                          "uname LIKE '%%1%' OR "
                                          "patronymic LIKE '%%1%' OR "
                                          "birthdate LIKE '%%1%' OR "
                                          "homeaddress LIKE '%%1%' OR "
                                          "phone LIKE '%%1%' OR "
                                          "email LIKE '%%1%' OR "
                                          "upassword LIKE '%%1%' OR "
                                          "note LIKE '%%1%'")
                                          .arg(ui->lineEdit_13->text())
                                        : QString("%1 LIKE '%%2%'")
                                          .arg(employeeTableColumnNames[ui->comboBox->currentIndex() - 1].second)
                                          .arg(ui->lineEdit_13->text()));

    updateEmployeesTable();
}
